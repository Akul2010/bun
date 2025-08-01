const log = Output.scoped(.UdpSocket, false);

const INET6_ADDRSTRLEN = if (bun.Environment.isWindows) 65 else 46;

extern fn ntohs(nshort: u16) u16;
extern fn htonl(hlong: u32) u32;
extern fn htons(hshort: u16) u16;
extern fn inet_ntop(af: c_int, src: ?*const anyopaque, dst: [*c]u8, size: c_int) ?[*:0]const u8;
extern fn inet_pton(af: c_int, src: [*c]const u8, dst: ?*anyopaque) c_int;

fn onClose(socket: *uws.udp.Socket) callconv(.C) void {
    jsc.markBinding(@src());

    const this: *UDPSocket = bun.cast(*UDPSocket, socket.user().?);
    this.closed = true;
    this.poll_ref.disable();
    _ = this.js_refcount.fetchSub(1, .monotonic);
}

fn onDrain(socket: *uws.udp.Socket) callconv(.C) void {
    jsc.markBinding(@src());

    const this: *UDPSocket = bun.cast(*UDPSocket, socket.user().?);
    const callback = this.config.on_drain;
    if (callback == .zero) return;

    const vm = jsc.VirtualMachine.get();
    const event_loop = vm.eventLoop();
    event_loop.enter();
    defer event_loop.exit();
    _ = callback.call(this.globalThis, this.thisValue, &.{this.thisValue}) catch |err| {
        this.callErrorHandler(.zero, this.globalThis.takeException(err));
    };
}

fn onData(socket: *uws.udp.Socket, buf: *uws.udp.PacketBuffer, packets: c_int) callconv(.C) void {
    jsc.markBinding(@src());

    const udpSocket: *UDPSocket = bun.cast(*UDPSocket, socket.user().?);
    const callback = udpSocket.config.on_data;
    if (callback == .zero) return;

    const globalThis = udpSocket.globalThis;

    var i: c_int = 0;
    while (i < packets) : (i += 1) {
        const peer = buf.getPeer(i);

        var addr_buf: [INET6_ADDRSTRLEN + 1:0]u8 = undefined;
        var hostname: ?[*:0]const u8 = null;
        var port: u16 = 0;
        var scope_id: ?u32 = null;

        switch (peer.family) {
            std.posix.AF.INET => {
                const peer4: *std.posix.sockaddr.in = @ptrCast(peer);
                hostname = inet_ntop(peer.family, &peer4.addr, &addr_buf, addr_buf.len);
                port = ntohs(peer4.port);
            },
            std.posix.AF.INET6 => {
                const peer6: *std.posix.sockaddr.in6 = @ptrCast(peer);
                hostname = inet_ntop(peer.family, &peer6.addr, &addr_buf, addr_buf.len);
                port = ntohs(peer6.port);
                if (peer6.scope_id != 0)
                    scope_id = peer6.scope_id;
            },
            else => continue,
        }

        if (hostname == null or port == 0) {
            continue;
        }

        const slice = buf.getPayload(i);

        const loop = udpSocket.vm.eventLoop();
        loop.enter();
        defer loop.exit();
        _ = udpSocket.js_refcount.fetchAdd(1, .monotonic);
        defer _ = udpSocket.js_refcount.fetchSub(1, .monotonic);

        const span = std.mem.span(hostname.?);
        var hostname_string = if (scope_id) |id| blk: {
            if (comptime !bun.Environment.isWindows) {
                var buffer = std.mem.zeroes([bun.c.IF_NAMESIZE:0]u8);
                if (bun.c.if_indextoname(id, &buffer) != null) {
                    break :blk bun.String.createFormat("{s}%{s}", .{ span, std.mem.span(@as([*:0]u8, &buffer)) }) catch bun.outOfMemory();
                }
            }

            break :blk bun.String.createFormat("{s}%{d}", .{ span, id }) catch bun.outOfMemory();
        } else bun.String.init(span);

        _ = callback.call(globalThis, udpSocket.thisValue, &.{
            udpSocket.thisValue,
            udpSocket.config.binary_type.toJS(slice, globalThis) catch return, // TODO: properly propagate exception upwards
            .jsNumber(port),
            hostname_string.transferToJS(globalThis),
        }) catch |err| {
            udpSocket.callErrorHandler(.zero, udpSocket.globalThis.takeException(err));
        };
    }
}

pub const UDPSocketConfig = struct {
    const This = @This();
    const handlers = .{
        .{ "data", "on_data" },
        .{ "drain", "on_drain" },
        .{ "error", "on_error" },
    };

    const ConnectConfig = struct {
        port: u16,
        address: [:0]u8,
    };

    hostname: [:0]u8,
    connect: ?ConnectConfig = null,
    port: u16,
    flags: i32,
    binary_type: jsc.ArrayBuffer.BinaryType = .Buffer,
    on_data: JSValue = .zero,
    on_drain: JSValue = .zero,
    on_error: JSValue = .zero,

    pub fn fromJS(globalThis: *JSGlobalObject, options: JSValue) bun.JSError!This {
        if (options.isEmptyOrUndefinedOrNull() or !options.isObject()) {
            return globalThis.throwInvalidArguments("Expected an object", .{});
        }

        const hostname = brk: {
            if (try options.getTruthy(globalThis, "hostname")) |value| {
                if (!value.isString()) {
                    return globalThis.throwInvalidArguments("Expected \"hostname\" to be a string", .{});
                }
                const str = value.toBunString(globalThis) catch @panic("unreachable");
                defer str.deref();
                break :brk str.toOwnedSliceZ(default_allocator) catch bun.outOfMemory();
            } else {
                break :brk default_allocator.dupeZ(u8, "0.0.0.0") catch bun.outOfMemory();
            }
        };
        defer if (globalThis.hasException()) default_allocator.free(hostname);

        const port: u16 = brk: {
            if (try options.getTruthy(globalThis, "port")) |value| {
                const number = try value.coerceToInt32(globalThis);
                if (number < 0 or number > 0xffff) {
                    return globalThis.throwInvalidArguments("Expected \"port\" to be an integer between 0 and 65535", .{});
                }
                break :brk @intCast(number);
            } else {
                break :brk 0;
            }
        };

        const flags: i32 = if (try options.getTruthy(globalThis, "flags")) |value|
            try bun.validators.validateInt32(globalThis, value, "flags", .{}, null, null)
        else
            0;

        var config = This{
            .hostname = hostname,
            .port = port,
            .flags = flags,
        };

        if (try options.getTruthy(globalThis, "socket")) |socket| {
            if (!socket.isObject()) {
                return globalThis.throwInvalidArguments("Expected \"socket\" to be an object", .{});
            }

            if (try options.getTruthy(globalThis, "binaryType")) |value| {
                if (!value.isString()) {
                    return globalThis.throwInvalidArguments("Expected \"socket.binaryType\" to be a string", .{});
                }

                config.binary_type = try jsc.ArrayBuffer.BinaryType.fromJSValue(globalThis, value) orelse {
                    return globalThis.throwInvalidArguments("Expected \"socket.binaryType\" to be 'arraybuffer', 'uint8array', or 'buffer'", .{});
                };
            }

            inline for (handlers) |handler| {
                if (try socket.getTruthyComptime(globalThis, handler.@"0")) |value| {
                    if (!value.isCell() or !value.isCallable()) {
                        return globalThis.throwInvalidArguments("Expected \"socket.{s}\" to be a function", .{handler.@"0"});
                    }
                    @field(config, handler.@"1") = value.withAsyncContextIfNeeded(globalThis);
                }
            }
        }

        defer {
            if (globalThis.hasException()) {
                if (config.connect) |connect| {
                    default_allocator.free(connect.address);
                }
            }
        }

        if (try options.getTruthy(globalThis, "connect")) |connect| {
            if (!connect.isObject()) {
                return globalThis.throwInvalidArguments("Expected \"connect\" to be an object", .{});
            }

            const connect_host_js = try connect.getTruthy(globalThis, "hostname") orelse {
                return globalThis.throwInvalidArguments("Expected \"connect.hostname\" to be a string", .{});
            };

            if (!connect_host_js.isString()) {
                return globalThis.throwInvalidArguments("Expected \"connect.hostname\" to be a string", .{});
            }

            const connect_port_js = try connect.getTruthy(globalThis, "port") orelse {
                return globalThis.throwInvalidArguments("Expected \"connect.port\" to be an integer", .{});
            };
            const connect_port = try connect_port_js.coerceToInt32(globalThis);

            const str = try connect_host_js.toBunString(globalThis);
            defer str.deref();
            const connect_host = str.toOwnedSliceZ(default_allocator) catch bun.outOfMemory();

            config.connect = .{
                .port = if (connect_port < 1 or connect_port > 0xffff) 0 else @as(u16, @intCast(connect_port)),
                .address = connect_host,
            };
        }

        config.protect();

        return config;
    }

    pub fn protect(this: This) void {
        inline for (handlers) |handler| {
            @field(this, handler.@"1").protect();
        }
    }

    pub fn unprotect(this: This) void {
        inline for (handlers) |handler| {
            @field(this, handler.@"1").unprotect();
        }
    }

    pub fn deinit(this: This) void {
        this.unprotect();
        default_allocator.free(this.hostname);
        if (this.connect) |val| {
            default_allocator.free(val.address);
        }
    }
};

pub const UDPSocket = struct {
    const This = @This();

    config: UDPSocketConfig,

    socket: *uws.udp.Socket,
    loop: *uws.Loop,

    globalThis: *JSGlobalObject,
    thisValue: JSValue = .zero,

    jsc_ref: jsc.Ref = jsc.Ref.init(),
    poll_ref: Async.KeepAlive = Async.KeepAlive.init(),
    // if marked as closed the socket pointer may be stale
    closed: bool = false,
    connect_info: ?ConnectInfo = null,
    vm: *jsc.VirtualMachine,
    js_refcount: std.atomic.Value(usize) = std.atomic.Value(usize).init(1),

    const ConnectInfo = struct {
        port: u16,
    };

    pub const js = jsc.Codegen.JSUDPSocket;
    pub const toJS = js.toJS;
    pub const fromJS = js.fromJS;
    pub const fromJSDirect = js.fromJSDirect;

    pub fn hasPendingActivity(this: *This) callconv(.C) bool {
        return this.js_refcount.load(.monotonic) > 0;
    }

    pub const new = bun.TrivialNew(@This());

    pub fn udpSocket(globalThis: *JSGlobalObject, options: JSValue) bun.JSError!JSValue {
        log("udpSocket", .{});

        const config = try UDPSocketConfig.fromJS(globalThis, options);

        const vm = globalThis.bunVM();
        var this = This.new(.{
            .socket = undefined,
            .config = config,
            .globalThis = globalThis,
            .loop = uws.Loop.get(),
            .vm = vm,
        });

        var err: i32 = 0;

        if (uws.udp.Socket.create(
            this.loop,
            onData,
            onDrain,
            onClose,
            config.hostname,
            config.port,
            config.flags,
            &err,
            this,
        )) |socket| {
            this.socket = socket;
        } else {
            this.closed = true;
            defer this.deinit();
            if (err != 0) {
                const code = @tagName(bun.sys.SystemErrno.init(@as(c_int, @intCast(err))).?);
                const sys_err = jsc.SystemError{
                    .errno = err,
                    .code = bun.String.static(code),
                    .message = bun.String.createFormat("bind {s} {s}", .{ code, config.hostname }) catch bun.outOfMemory(),
                };
                const error_value = sys_err.toErrorInstance(globalThis);
                error_value.put(globalThis, "address", try bun.String.createUTF8ForJS(globalThis, config.hostname));
                return globalThis.throwValue(error_value);
            }
            return globalThis.throw("Failed to bind socket", .{});
        }

        errdefer {
            this.socket.close();
            this.deinit();
        }

        if (config.connect) |connect| {
            const ret = this.socket.connect(connect.address, connect.port);
            if (ret != 0) {
                if (bun.sys.Maybe(void).errnoSys(ret, .connect)) |sys_err| {
                    return globalThis.throwValue(try sys_err.toJS(globalThis));
                }

                if (bun.c_ares.Error.initEAI(ret)) |eai_err| {
                    return globalThis.throwValue(eai_err.toJSWithSyscallAndHostname(globalThis, "connect", connect.address));
                }
            }
            this.connect_info = .{ .port = connect.port };
        }

        this.poll_ref.ref(vm);
        const thisValue = this.toJS(globalThis);
        thisValue.ensureStillAlive();
        this.thisValue = thisValue;
        return jsc.JSPromise.resolvedPromiseValue(globalThis, thisValue);
    }

    pub fn callErrorHandler(
        this: *This,
        thisValue: JSValue,
        err: JSValue,
    ) void {
        const callback = this.config.on_error;
        const globalThis = this.globalThis;
        const vm = globalThis.bunVM();

        if (err.isTerminationException()) {
            return;
        }
        if (callback == .zero) {
            _ = vm.uncaughtException(globalThis, err, false);
            return;
        }

        _ = callback.call(globalThis, thisValue, &.{err}) catch |e| globalThis.reportActiveExceptionAsUnhandled(e);
    }

    pub fn setBroadcast(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame) bun.JSError!JSValue {
        if (this.closed) {
            return globalThis.throwValue(try bun.sys.Maybe(void).errnoSys(@as(i32, @intCast(@intFromEnum(std.posix.E.BADF))), .setsockopt).?.toJS(globalThis));
        }

        const arguments = callframe.arguments();
        if (arguments.len < 1) {
            return globalThis.throwInvalidArguments("Expected 1 argument, got {}", .{arguments.len});
        }

        const enabled = arguments[0].toBoolean();
        const res = this.socket.setBroadcast(enabled);

        if (getUSError(res, .setsockopt, true)) |err| {
            return globalThis.throwValue(try err.toJS(globalThis));
        }

        return arguments[0];
    }

    pub fn setMulticastLoopback(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame) bun.JSError!JSValue {
        if (this.closed) {
            return globalThis.throwValue(try bun.sys.Maybe(void).errnoSys(@as(i32, @intCast(@intFromEnum(std.posix.E.BADF))), .setsockopt).?.toJS(globalThis));
        }

        const arguments = callframe.arguments();
        if (arguments.len < 1) {
            return globalThis.throwInvalidArguments("Expected 1 argument, got {}", .{arguments.len});
        }

        const enabled = arguments[0].toBoolean();
        const res = this.socket.setMulticastLoopback(enabled);

        if (getUSError(res, .setsockopt, true)) |err| {
            return globalThis.throwValue(try err.toJS(globalThis));
        }

        return arguments[0];
    }

    fn setMembership(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame, drop: bool) bun.JSError!JSValue {
        if (this.closed) {
            return globalThis.throwValue(try bun.sys.Maybe(void).errnoSys(@as(i32, @intCast(@intFromEnum(std.posix.E.BADF))), .setsockopt).?.toJS(globalThis));
        }

        const arguments = callframe.arguments();
        if (arguments.len < 1) {
            return globalThis.throwInvalidArguments("Expected 1 argument, got {}", .{arguments.len});
        }

        var addr = std.mem.zeroes(std.posix.sockaddr.storage);
        if (!try parseAddr(this, globalThis, .jsNumber(0), arguments[0], &addr)) {
            return globalThis.throwValue(try bun.sys.Maybe(void).errnoSys(@as(i32, @intCast(@intFromEnum(std.posix.E.INVAL))), .setsockopt).?.toJS(globalThis));
        }

        var interface = std.mem.zeroes(std.posix.sockaddr.storage);

        const res = if (arguments.len > 1 and try parseAddr(this, globalThis, .jsNumber(0), arguments[1], &interface)) blk: {
            if (addr.family != interface.family) {
                return globalThis.throwInvalidArguments("Family mismatch between address and interface", .{});
            }
            break :blk this.socket.setMembership(&addr, &interface, drop);
        } else this.socket.setMembership(&addr, null, drop);

        if (getUSError(res, .setsockopt, true)) |err| {
            return globalThis.throwValue(try err.toJS(globalThis));
        }

        return .true;
    }

    pub fn addMembership(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame) bun.JSError!JSValue {
        return this.setMembership(globalThis, callframe, false);
    }

    pub fn dropMembership(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame) bun.JSError!JSValue {
        return this.setMembership(globalThis, callframe, true);
    }

    fn setSourceSpecificMembership(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame, drop: bool) bun.JSError!JSValue {
        if (this.closed) {
            return globalThis.throwValue(try bun.sys.Maybe(void).errnoSys(@as(i32, @intCast(@intFromEnum(std.posix.E.BADF))), .setsockopt).?.toJS(globalThis));
        }

        const arguments = callframe.arguments();
        if (arguments.len < 2) {
            return globalThis.throwInvalidArguments("Expected 2 arguments, got {}", .{arguments.len});
        }

        var source_addr: std.posix.sockaddr.storage = undefined;
        if (!try parseAddr(this, globalThis, .jsNumber(0), arguments[0], &source_addr)) {
            return globalThis.throwValue(try bun.sys.Maybe(void).errnoSys(@as(i32, @intCast(@intFromEnum(std.posix.E.INVAL))), .setsockopt).?.toJS(globalThis));
        }

        var group_addr: std.posix.sockaddr.storage = undefined;
        if (!try parseAddr(this, globalThis, .jsNumber(0), arguments[1], &group_addr)) {
            return globalThis.throwValue(try bun.sys.Maybe(void).errnoSys(@as(i32, @intCast(@intFromEnum(std.posix.E.INVAL))), .setsockopt).?.toJS(globalThis));
        }

        if (source_addr.family != group_addr.family) {
            return globalThis.throwInvalidArguments("Family mismatch between source and group addresses", .{});
        }

        var interface: std.posix.sockaddr.storage = undefined;

        const res = if (arguments.len > 2 and try parseAddr(this, globalThis, .jsNumber(0), arguments[2], &interface)) blk: {
            if (source_addr.family != interface.family) {
                return globalThis.throwInvalidArguments("Family mismatch among source, group and interface addresses", .{});
            }
            break :blk this.socket.setSourceSpecificMembership(&source_addr, &group_addr, &interface, drop);
        } else this.socket.setSourceSpecificMembership(&source_addr, &group_addr, null, drop);

        if (getUSError(res, .setsockopt, true)) |err| {
            return globalThis.throwValue(try err.toJS(globalThis));
        }

        return .true;
    }

    pub fn addSourceSpecificMembership(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame) bun.JSError!JSValue {
        return this.setSourceSpecificMembership(globalThis, callframe, false);
    }

    pub fn dropSourceSpecificMembership(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame) bun.JSError!JSValue {
        return this.setSourceSpecificMembership(globalThis, callframe, true);
    }

    pub fn setMulticastInterface(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame) bun.JSError!JSValue {
        if (this.closed) {
            return globalThis.throwValue(try bun.sys.Maybe(void).errnoSys(@as(i32, @intCast(@intFromEnum(std.posix.E.BADF))), .setsockopt).?.toJS(globalThis));
        }

        const arguments = callframe.arguments();
        if (arguments.len < 1) {
            return globalThis.throwInvalidArguments("Expected 1 argument, got {}", .{arguments.len});
        }

        var addr: std.posix.sockaddr.storage = undefined;

        if (!try parseAddr(this, globalThis, .jsNumber(0), arguments[0], &addr)) {
            return .false;
        }

        const res = this.socket.setMulticastInterface(&addr);

        if (getUSError(res, .setsockopt, true)) |err| {
            return globalThis.throwValue(try err.toJS(globalThis));
        }

        return .true;
    }

    pub fn setTTL(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame) bun.JSError!JSValue {
        return setAnyTTL(this, globalThis, callframe, uws.udp.Socket.setUnicastTTL);
    }

    pub fn setMulticastTTL(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame) bun.JSError!JSValue {
        return setAnyTTL(this, globalThis, callframe, uws.udp.Socket.setMulticastTTL);
    }

    fn getUSError(res: c_int, tag: bun.sys.Tag, comptime use_wsa: bool) ?bun.sys.Maybe(void) {
        if (comptime bun.Environment.isWindows) {
            // setsockopt returns 0 on success, but errnoSys considers 0 to be failure on Windows.
            // This applies to some other usockets functions too.
            if (res >= 0) {
                return null;
            }

            if (comptime use_wsa) {
                if (bun.windows.WSAGetLastError()) |wsa| {
                    if (wsa != .SUCCESS) {
                        std.os.windows.ws2_32.WSASetLastError(0);
                        return bun.sys.Maybe(void).errno(wsa.toE(), tag);
                    }
                }
            }

            return bun.sys.Maybe(void).errno(@as(bun.sys.E, @enumFromInt(std.c._errno().*)), tag);
        } else {
            return bun.sys.Maybe(void).errnoSys(res, tag);
        }
    }

    fn setAnyTTL(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame, comptime function: fn (*uws.udp.Socket, i32) c_int) bun.JSError!JSValue {
        if (this.closed) {
            return globalThis.throwValue(try bun.sys.Maybe(void).errnoSys(@as(i32, @intCast(@intFromEnum(std.posix.E.BADF))), .setsockopt).?.toJS(globalThis));
        }

        const arguments = callframe.arguments();
        if (arguments.len < 1) {
            return globalThis.throwInvalidArguments("Expected 1 argument, got {}", .{arguments.len});
        }

        const ttl = try arguments[0].coerceToInt32(globalThis);
        const res = function(this.socket, ttl);

        if (getUSError(res, .setsockopt, true)) |err| {
            return globalThis.throwValue(try err.toJS(globalThis));
        }

        return JSValue.jsNumber(ttl);
    }

    pub fn sendMany(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame) bun.JSError!JSValue {
        if (this.closed) {
            return globalThis.throw("Socket is closed", .{});
        }
        const arguments = callframe.arguments_old(1);
        if (arguments.len != 1) {
            return globalThis.throwInvalidArguments("Expected 1 argument, got {}", .{arguments.len});
        }

        const arg = arguments.ptr[0];
        if (!arg.jsType().isArray()) {
            return globalThis.throwInvalidArgumentType("sendMany", "first argument", "array");
        }

        const array_len = try arg.getLength(globalThis);
        if (this.connect_info == null and array_len % 3 != 0) {
            return globalThis.throwInvalidArguments("Expected 3 arguments for each packet", .{});
        }

        const len = if (this.connect_info == null) array_len / 3 else array_len;

        var arena = std.heap.ArenaAllocator.init(bun.default_allocator);
        defer arena.deinit();
        const alloc = arena.allocator();

        var payloads = alloc.alloc([*]const u8, len) catch bun.outOfMemory();
        var lens = alloc.alloc(usize, len) catch bun.outOfMemory();
        var addr_ptrs = alloc.alloc(?*const anyopaque, len) catch bun.outOfMemory();
        var addrs = alloc.alloc(std.posix.sockaddr.storage, len) catch bun.outOfMemory();

        var iter = try arg.arrayIterator(globalThis);

        var i: u16 = 0;
        var port: JSValue = .zero;
        while (try iter.next()) |val| : (i += 1) {
            if (i >= array_len) {
                return globalThis.throwInvalidArguments("Mismatch between array length property and number of items", .{});
            }
            const slice_idx = if (this.connect_info == null) i / 3 else i;
            if (this.connect_info != null or i % 3 == 0) {
                const slice = brk: {
                    if (val.asArrayBuffer(globalThis)) |arrayBuffer| {
                        break :brk arrayBuffer.slice();
                    } else if (val.isString()) {
                        break :brk val.toString(globalThis).toSlice(globalThis, alloc).slice();
                    } else {
                        return globalThis.throwInvalidArguments("Expected ArrayBufferView or string as payload", .{});
                    }
                };
                payloads[slice_idx] = slice.ptr;
                lens[slice_idx] = slice.len;
            }
            if (this.connect_info != null) {
                addr_ptrs[slice_idx] = null;
                continue;
            }
            if (i % 3 == 1) {
                port = val;
                continue;
            }
            if (i % 3 == 2) {
                if (!try this.parseAddr(globalThis, port, val, &addrs[slice_idx])) {
                    return globalThis.throwInvalidArguments("Invalid address", .{});
                }
                addr_ptrs[slice_idx] = &addrs[slice_idx];
            }
        }
        if (i != array_len) {
            return globalThis.throwInvalidArguments("Mismatch between array length property and number of items", .{});
        }
        const res = this.socket.send(payloads, lens, addr_ptrs);
        if (getUSError(res, .send, true)) |err| {
            return globalThis.throwValue(try err.toJS(globalThis));
        }
        return JSValue.jsNumber(res);
    }

    pub fn send(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame) bun.JSError!JSValue {
        if (this.closed) {
            return globalThis.throw("Socket is closed", .{});
        }
        const arguments = callframe.arguments_old(3);
        const dst: ?Destination = brk: {
            if (this.connect_info != null) {
                if (arguments.len == 1) {
                    break :brk null;
                }
                if (arguments.len == 3) {
                    return globalThis.throwInvalidArguments("Cannot specify destination on connected socket", .{});
                }
                return globalThis.throwInvalidArguments("Expected 1 argument, got {}", .{arguments.len});
            } else {
                if (arguments.len != 3) {
                    return globalThis.throwInvalidArguments("Expected 3 arguments, got {}", .{arguments.len});
                }
                break :brk .{
                    .port = arguments.ptr[1],
                    .address = arguments.ptr[2],
                };
            }
        };

        const payload_arg = arguments.ptr[0];
        var payload_str = jsc.ZigString.Slice.empty;
        defer payload_str.deinit();
        const payload = brk: {
            if (payload_arg.asArrayBuffer(globalThis)) |array_buffer| {
                break :brk array_buffer.slice();
            } else if (payload_arg.isString()) {
                payload_str = payload_arg.asString().toSlice(globalThis, bun.default_allocator);
                break :brk payload_str.slice();
            } else {
                return globalThis.throwInvalidArguments("Expected ArrayBufferView or string as first argument", .{});
            }
        };

        var addr: std.posix.sockaddr.storage = std.mem.zeroes(std.posix.sockaddr.storage);
        const addr_ptr = brk: {
            if (dst) |dest| {
                if (!try this.parseAddr(globalThis, dest.port, dest.address, &addr)) {
                    return globalThis.throwInvalidArguments("Invalid address", .{});
                }
                break :brk &addr;
            } else {
                break :brk null;
            }
        };

        const res = this.socket.send(&.{payload.ptr}, &.{payload.len}, &.{addr_ptr});
        if (getUSError(res, .send, true)) |err| {
            return globalThis.throwValue(try err.toJS(globalThis));
        }
        return JSValue.jsBoolean(res > 0);
    }

    fn parseAddr(this: *This, globalThis: *JSGlobalObject, port_val: JSValue, address_val: JSValue, storage: *std.posix.sockaddr.storage) bun.JSError!bool {
        _ = this;
        const number = try port_val.coerceToInt32(globalThis);
        const port: u16 = if (number < 1 or number > 0xffff) 0 else @intCast(number);

        const str = try address_val.toBunString(globalThis);
        defer str.deref();
        const address_slice = try str.toOwnedSliceZ(default_allocator);
        defer default_allocator.free(address_slice);

        var addr4: *std.posix.sockaddr.in = @ptrCast(storage);
        if (inet_pton(std.posix.AF.INET, address_slice.ptr, &addr4.addr) == 1) {
            addr4.port = htons(@truncate(port));
            addr4.family = std.posix.AF.INET;
        } else {
            var addr6: *std.posix.sockaddr.in6 = @ptrCast(storage);
            addr6.scope_id = 0;

            if (str.indexOfAsciiChar('%')) |percent| {
                if (percent + 1 < str.length()) {
                    const iface_id: u32 = blk: {
                        if (comptime bun.Environment.isWindows) {
                            if (str.substring(percent + 1).toInt32()) |signed| {
                                if (std.math.cast(u32, signed)) |id| {
                                    break :blk id;
                                }
                            }
                        } else {
                            const index = std.c.if_nametoindex(address_slice[percent + 1 .. :0]);
                            if (index > 0) {
                                if (std.math.cast(u32, index)) |id| {
                                    break :blk id;
                                }
                            }
                        }
                        // "an invalid Scope gets turned into #0 (default selection)"
                        // (test-dgram-multicast-set-interface.js)
                        break :blk 0;
                    };

                    address_slice[percent] = '\x00';
                    addr6.scope_id = iface_id;
                }
            }

            if (inet_pton(std.posix.AF.INET6, address_slice.ptr, &addr6.addr) == 1) {
                addr6.port = htons(@truncate(port));
                addr6.family = std.posix.AF.INET6;
            } else {
                return false;
            }
        }

        return true;
    }

    const Destination = struct {
        port: JSValue,
        address: JSValue,
    };

    pub fn ref(this: *This, globalThis: *jsc.JSGlobalObject, _: *jsc.CallFrame) bun.JSError!JSValue {
        if (!this.closed) {
            this.poll_ref.ref(globalThis.bunVM());
        }

        return .js_undefined;
    }

    pub fn unref(this: *This, globalThis: *jsc.JSGlobalObject, _: *jsc.CallFrame) bun.JSError!JSValue {
        this.poll_ref.unref(globalThis.bunVM());

        return .js_undefined;
    }

    pub fn close(
        this: *This,
        _: *JSGlobalObject,
        _: *CallFrame,
    ) bun.JSError!JSValue {
        if (!this.closed) this.socket.close();

        return .js_undefined;
    }

    pub fn reload(this: *This, globalThis: *JSGlobalObject, callframe: *CallFrame) bun.JSError!JSValue {
        const args = callframe.arguments_old(1);

        if (args.len < 1) {
            return globalThis.throwInvalidArguments("Expected 1 argument", .{});
        }

        const options = args.ptr[0];
        const config = try UDPSocketConfig.fromJS(globalThis, options);

        config.protect();
        var previous_config = this.config;
        previous_config.unprotect();
        this.config = config;

        return .js_undefined;
    }

    pub fn getClosed(this: *This, _: *JSGlobalObject) JSValue {
        return JSValue.jsBoolean(this.closed);
    }

    pub fn getHostname(this: *This, _: *JSGlobalObject) JSValue {
        const hostname = jsc.ZigString.init(this.config.hostname);
        return hostname.toJS(this.globalThis);
    }

    pub fn getPort(this: *This, _: *JSGlobalObject) JSValue {
        if (this.closed) return .js_undefined;
        return JSValue.jsNumber(this.socket.boundPort());
    }

    fn createSockAddr(globalThis: *JSGlobalObject, address_bytes: []const u8, port: u16) JSValue {
        var sockaddr = SocketAddress.init(address_bytes, port) catch return .js_undefined;
        return sockaddr.intoDTO(globalThis);
    }

    pub fn getAddress(this: *This, globalThis: *JSGlobalObject) JSValue {
        if (this.closed) return .js_undefined;
        var buf: [64]u8 = [_]u8{0} ** 64;
        var length: i32 = 64;
        this.socket.boundIp(&buf, &length);

        const address_bytes = buf[0..@as(usize, @intCast(length))];
        const port = this.socket.boundPort();
        return createSockAddr(globalThis, address_bytes, @intCast(port));
    }

    pub fn getRemoteAddress(this: *This, globalThis: *jsc.JSGlobalObject) jsc.JSValue {
        if (this.closed) return .js_undefined;
        const connect_info = this.connect_info orelse return .js_undefined;
        var buf: [64]u8 = [_]u8{0} ** 64;
        var length: i32 = 64;
        this.socket.remoteIp(&buf, &length);

        const address_bytes = buf[0..@as(usize, @intCast(length))];
        return createSockAddr(globalThis, address_bytes, connect_info.port);
    }

    pub fn getBinaryType(
        this: *This,
        globalThis: *JSGlobalObject,
    ) JSValue {
        return switch (this.config.binary_type) {
            .Buffer => bun.String.static("buffer").toJS(globalThis),
            .Uint8Array => bun.String.static("uint8array").toJS(globalThis),
            .ArrayBuffer => bun.String.static("arraybuffer").toJS(globalThis),
            else => @panic("Invalid binary type"),
        };
    }

    pub fn finalize(this: *This) void {
        log("Finalize {*}", .{this});
        this.deinit();
    }

    pub fn deinit(this: *This) void {
        // finalize is only called when js_refcount reaches 0
        // js_refcount can only reach 0 when the socket is closed
        bun.assert(this.closed);
        this.poll_ref.disable();
        this.config.deinit();
        bun.destroy(this);
    }

    pub fn jsConnect(globalThis: *jsc.JSGlobalObject, callFrame: *jsc.CallFrame) bun.JSError!jsc.JSValue {
        const args = callFrame.arguments_old(2);

        const this = callFrame.this().as(UDPSocket) orelse {
            return globalThis.throwInvalidArguments("Expected UDPSocket as 'this'", .{});
        };

        if (this.connect_info != null) {
            return globalThis.throw("Socket is already connected", .{});
        }

        if (this.closed) {
            return globalThis.throw("Socket is closed", .{});
        }

        if (args.len < 2) {
            return globalThis.throwInvalidArguments("Expected 2 arguments", .{});
        }

        const str = try args.ptr[0].toBunString(globalThis);
        defer str.deref();
        const connect_host = str.toOwnedSliceZ(default_allocator) catch bun.outOfMemory();
        defer default_allocator.free(connect_host);

        const connect_port_js = args.ptr[1];

        if (!connect_port_js.isNumber()) {
            return globalThis.throwInvalidArguments("Expected \"port\" to be an integer", .{});
        }

        const connect_port = connect_port_js.asInt32();
        const port: u16 = if (connect_port < 1 or connect_port > 0xffff) 0 else @as(u16, @intCast(connect_port));

        if (this.socket.connect(connect_host, port) == -1) {
            return globalThis.throw("Failed to connect socket", .{});
        }
        this.connect_info = .{
            .port = port,
        };

        js.addressSetCached(callFrame.this(), globalThis, .zero);
        js.remoteAddressSetCached(callFrame.this(), globalThis, .zero);

        return .js_undefined;
    }

    pub fn jsDisconnect(globalObject: *jsc.JSGlobalObject, callFrame: *jsc.CallFrame) bun.JSError!jsc.JSValue {
        const this = callFrame.this().as(UDPSocket) orelse {
            return globalObject.throwInvalidArguments("Expected UDPSocket as 'this'", .{});
        };

        if (this.connect_info == null) {
            return globalObject.throw("Socket is not connected", .{});
        }

        if (this.closed) {
            return globalObject.throw("Socket is closed", .{});
        }

        if (this.socket.disconnect() == -1) {
            return globalObject.throw("Failed to disconnect socket", .{});
        }
        this.connect_info = null;

        return .js_undefined;
    }
};

const std = @import("std");
const uws = @import("../../../deps/uws.zig");

const bun = @import("bun");
const Async = bun.Async;
const Output = bun.Output;
const default_allocator = bun.default_allocator;

const jsc = bun.jsc;
const CallFrame = jsc.CallFrame;
const JSGlobalObject = jsc.JSGlobalObject;
const JSValue = jsc.JSValue;
const SocketAddress = jsc.API.SocketAddress;
