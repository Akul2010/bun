const std = @import("std");
const bun = @import("bun");
const JSC = bun.JSC;

pub const JSPromiseRejectionOperation = enum(u32) {
    Reject = 0,
    Handle = 1,
};
