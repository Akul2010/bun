#include "root.h"

#include "ZigGlobalObject.h"
#include "helpers.h"
#include "JavaScriptCore/ArgList.h"
#include "JavaScriptCore/JSImmutableButterfly.h"
#include "wtf/text/Base64.h"
#include "JavaScriptCore/BuiltinNames.h"
#include "JavaScriptCore/CallData.h"
#include "JavaScriptCore/CatchScope.h"
#include "JavaScriptCore/ClassInfo.h"
#include "JavaScriptCore/CodeBlock.h"
#include "JavaScriptCore/Completion.h"
#include "JavaScriptCore/DeferredWorkTimer.h"
#include "JavaScriptCore/Error.h"
#include "JavaScriptCore/ErrorInstance.h"
#include "JavaScriptCore/Exception.h"
#include "JavaScriptCore/ExceptionScope.h"
#include "JavaScriptCore/FunctionConstructor.h"
#include "JavaScriptCore/FunctionPrototype.h"
#include "JavaScriptCore/GetterSetter.h"
#include "JavaScriptCore/GlobalObjectMethodTable.h"
#include "JavaScriptCore/Heap.h"
#include "JavaScriptCore/Identifier.h"
#include "JavaScriptCore/InitializeThreading.h"
#include "JavaScriptCore/InternalFieldTuple.h"
#include "JavaScriptCore/InternalFunction.h"
#include "JavaScriptCore/JSArray.h"
#include "JavaScriptCore/JSCast.h"
#include "JavaScriptCore/JSCJSValue.h"
#include "JavaScriptCore/JSGlobalProxyInlines.h"
#include "JavaScriptCore/JSInternalPromise.h"
#include "JavaScriptCore/JSLock.h"
#include "JavaScriptCore/JSMap.h"
#include "JavaScriptCore/JSMicrotask.h"
#include "JavaScriptCore/JSModuleLoader.h"
#include "JavaScriptCore/JSModuleNamespaceObject.h"
#include "JavaScriptCore/JSModuleNamespaceObjectInlines.h"
#include "JavaScriptCore/JSModuleRecord.h"
#include "JavaScriptCore/JSNativeStdFunction.h"
#include "JavaScriptCore/JSObject.h"
#include "JavaScriptCore/JSObjectInlines.h"
#include "JavaScriptCore/JSPromise.h"
#include "JavaScriptCore/JSScriptFetchParameters.h"
#include "JavaScriptCore/JSSourceCode.h"
#include "JavaScriptCore/JSString.h"
#include "JavaScriptCore/JSWeakMap.h"
#include "JavaScriptCore/LazyClassStructure.h"
#include "JavaScriptCore/LazyClassStructureInlines.h"
#include "JavaScriptCore/ObjectConstructor.h"
#include "JavaScriptCore/JSBasePrivate.h"
#include "JavaScriptCore/ScriptExecutable.h"
#include "JavaScriptCore/ScriptFetchParameters.h"
#include "JavaScriptCore/SourceOrigin.h"
#include "JavaScriptCore/StackFrame.h"
#include "JavaScriptCore/StackVisitor.h"
#include "JavaScriptCore/VM.h"
#include "AddEventListenerOptions.h"
#include "AsyncContextFrame.h"
#include "BunClientData.h"
#include "BunObject.h"
#include "GeneratedBunObject.h"
#include "BunPlugin.h"
#include "BunProcess.h"
#include "BunWorkerGlobalScope.h"
#include "CallSite.h"
#include "CallSitePrototype.h"
#include "JSCommonJSModule.h"
#include "JSCommonJSExtensions.h"
#include "ConsoleObject.h"
#include "DOMWrapperWorld-class.h"
#include "ErrorStackTrace.h"
#include "IDLTypes.h"
#include "ImportMetaObject.h"
#include "JS2Native.h"
#include "JSAbortAlgorithm.h"
#include "JSAbortController.h"
#include "JSAbortSignal.h"
#include "JSBroadcastChannel.h"
#include "JSBuffer.h"
#include "JSBufferList.h"
#include "webcore/JSMIMEBindings.h"
#include "JSByteLengthQueuingStrategy.h"
#include "JSCloseEvent.h"
#include "JSCommonJSExtensions.h"
#include "JSCountQueuingStrategy.h"
#include "JSCustomEvent.h"
#include "JSDOMConvertBase.h"
#include "JSDOMConvertUnion.h"
#include "JSDOMException.h"
#include "JSDOMFile.h"
#include "JSDOMFormData.h"
#include "JSDOMURL.h"
#include "JSEnvironmentVariableMap.h"
#include "JSErrorEvent.h"
#include "JSEvent.h"
#include "JSEventEmitter.h"
#include "JSEventListener.h"
#include "JSEventTarget.h"
#include "JSFetchHeaders.h"
#include "JSFFIFunction.h"
#include "webcore/JSMIMEParams.h"
#include "webcore/JSMIMEType.h"
#include "JSMessageChannel.h"
#include "JSMessageEvent.h"
#include "JSMessagePort.h"
#include "JSNextTickQueue.h"
#include "JSPerformance.h"
#include "JSPerformanceEntry.h"
#include "JSPerformanceMark.h"
#include "JSPerformanceMeasure.h"
#include "JSPerformanceObserver.h"
#include "JSPerformanceObserverEntryList.h"
#include "JSReadableByteStreamController.h"
#include "JSReadableStream.h"
#include "JSReadableStreamBYOBReader.h"
#include "JSReadableStreamBYOBRequest.h"
#include "JSReadableStreamDefaultController.h"
#include "JSReadableStreamDefaultReader.h"
#include "JSSink.h"
#include "JSSocketAddressDTO.h"
#include "JSSQLStatement.h"
#include "JSStringDecoder.h"
#include "JSTextEncoder.h"
#include "JSTextEncoderStream.h"
#include "JSTextDecoderStream.h"
#include "JSTransformStream.h"
#include "JSTransformStreamDefaultController.h"
#include "JSURLSearchParams.h"
#include "JSWasmStreamingCompiler.h"
#include "JSWebSocket.h"
#include "JSWorker.h"
#include "JSWritableStream.h"
#include "JSWritableStreamDefaultController.h"
#include "JSWritableStreamDefaultWriter.h"
#include "libusockets.h"
#include "ModuleLoader.h"
#include "napi_external.h"
#include "napi_handle_scope.h"
#include "napi_type_tag.h"
#include "napi.h"
#include "NodeHTTP.h"
#include "NodeVM.h"
#include "Performance.h"
#include "ProcessBindingConstants.h"
#include "ProcessBindingTTYWrap.h"
#include "ReadableStream.h"
#include "SerializedScriptValue.h"
#include "StructuredClone.h"
#include "WebCoreJSBuiltins.h"
#include "webcrypto/JSCryptoKey.h"
#include "webcrypto/JSSubtleCrypto.h"
#include "ZigGeneratedClasses.h"
#include "ZigSourceProvider.h"
#include "UtilInspect.h"
#include "Base64Helpers.h"
#include "wtf/text/OrdinalNumber.h"
#include "ErrorCode.h"
#include "v8/shim/GlobalInternals.h"
#include "EventLoopTask.h"
#include "NodeModuleModule.h"
#include <JavaScriptCore/JSCBytecodeCacheVersion.h>
#include "JSPerformanceServerTiming.h"
#include "JSPerformanceResourceTiming.h"
#include "JSPerformanceTiming.h"
#include "JSX509Certificate.h"
#include "JSSign.h"
#include "JSVerify.h"
#include "JSHmac.h"
#include "JSHash.h"
#include "JSDiffieHellman.h"
#include "JSDiffieHellmanGroup.h"
#include "JSECDH.h"
#include "JSCipher.h"
#include "JSKeyObject.h"
#include "JSSecretKeyObject.h"
#include "JSPublicKeyObject.h"
#include "JSPrivateKeyObject.h"
#include "webcore/JSMIMEParams.h"
#include "JSNodePerformanceHooksHistogram.h"
#include "JSS3File.h"
#include "S3Error.h"
#include "ProcessBindingBuffer.h"
#include "NodeValidator.h"
#include "ProcessBindingFs.h"
#include "ProcessBindingHTTPParser.h"
#include "node/NodeTimers.h"
#include "JSConnectionsList.h"
#include "JSHTTPParser.h"

#include "JSBunRequest.h"
#include "ServerRouteList.h"

#if ENABLE(REMOTE_INSPECTOR)
#include "JavaScriptCore/RemoteInspectorServer.h"
#endif

#include "NodeFSStatBinding.h"
#include "NodeFSStatFSBinding.h"
#include "NodeDirent.h"

#if !OS(WINDOWS)
#include <dlfcn.h>
#endif

#ifdef __APPLE__
#include <sys/sysctl.h>
#elif defined(__linux__)
// for sysconf
#include <unistd.h>
#endif

using namespace Bun;

BUN_DECLARE_HOST_FUNCTION(Bun__NodeUtil__jsParseArgs);
BUN_DECLARE_HOST_FUNCTION(BUN__HTTP2__getUnpackedSettings);
BUN_DECLARE_HOST_FUNCTION(BUN__HTTP2_getPackedSettings);
BUN_DECLARE_HOST_FUNCTION(BUN__HTTP2_assertSettings);

JSC_DECLARE_HOST_FUNCTION(jsFunctionMakeAbortError);

using JSGlobalObject = JSC::JSGlobalObject;
using Exception = JSC::Exception;
using JSValue = JSC::JSValue;
using JSString = JSC::JSString;
using JSModuleLoader = JSC::JSModuleLoader;
using JSModuleRecord = JSC::JSModuleRecord;
using Identifier = JSC::Identifier;
using SourceOrigin = JSC::SourceOrigin;
using JSObject = JSC::JSObject;
using JSNonFinalObject = JSC::JSNonFinalObject;
namespace JSCastingHelpers = JSC::JSCastingHelpers;

constexpr size_t DEFAULT_ERROR_STACK_TRACE_LIMIT = 10;

// #include <iostream>

Structure* createMemoryFootprintStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject);

#ifndef BUN_WEBKIT_VERSION
#ifndef ASSERT_ENABLED
#warning "BUN_WEBKIT_VERSION is not defined. WebKit's cmakeconfig.h is supposed to define that. If you're building a release build locally, ignore this warning. If you're seeing this warning in CI, please file an issue."
#endif

#define WEBKIT_BYTECODE_CACHE_HASH_KEY __TIMESTAMP__
#else
#define WEBKIT_BYTECODE_CACHE_HASH_KEY BUN_WEBKIT_VERSION
#endif
static consteval unsigned getWebKitBytecodeCacheVersion()
{
    return WTF::SuperFastHash::computeHash(WEBKIT_BYTECODE_CACHE_HASH_KEY);
}
#undef WEBKIT_BYTECODE_CACHE_HASH_KEY

extern "C" unsigned getJSCBytecodeCacheVersion()
{
    return getWebKitBytecodeCacheVersion();
}

extern "C" void JSCInitialize(const char* envp[], size_t envc, void (*onCrash)(const char* ptr, size_t length), bool evalMode)
{
    static bool has_loaded_jsc = false;
    // NOLINTBEGIN
    if (has_loaded_jsc)
        return;
    has_loaded_jsc = true;
    JSC::Config::enableRestrictedOptions();

    std::set_terminate([]() { Zig__GlobalObject__onCrash(); });
    WTF::initializeMainThread();

#if ASAN_ENABLED && OS(LINUX)
    {
        JSC::Options::AllowUnfinalizedAccessScope scope;

        // ASAN interferes with JSC's signal handlers
        JSC::Options::useWasmFaultSignalHandler() = false;
        JSC::Options::useWasmFastMemory() = false;
    }
#endif

    JSC::initialize();
    {

        JSC::Options::AllowUnfinalizedAccessScope scope;

        JSC::Options::useConcurrentJIT() = true;
        // JSC::Options::useSigillCrashAnalyzer() = true;
        JSC::Options::useWasm() = true;
        JSC::Options::useSourceProviderCache() = true;
        // JSC::Options::useUnlinkedCodeBlockJettisoning() = false;
        JSC::Options::exposeInternalModuleLoader() = true;
        JSC::Options::useSharedArrayBuffer() = true;
        JSC::Options::useJIT() = true;
        JSC::Options::useBBQJIT() = true;
        JSC::Options::useJITCage() = false;
        JSC::Options::useShadowRealm() = true;
        JSC::Options::useV8DateParser() = true;
        JSC::Options::useMathSumPreciseMethod() = true;
        JSC::Options::evalMode() = evalMode;
        JSC::Options::heapGrowthSteepnessFactor() = 1.0;
        JSC::Options::heapGrowthMaxIncrease() = 2.0;
        JSC::dangerouslyOverrideJSCBytecodeCacheVersion(getWebKitBytecodeCacheVersion());

#ifdef BUN_DEBUG
        JSC::Options::showPrivateScriptsInStackTraces() = true;
#endif

        if (envc > 0) [[likely]] {
            while (envc--) {
                const char* env = (const char*)envp[envc];
                // need to check for \0 so we might as well make this single pass
                // strlen would check the end of the string
                if (!(env[0] == 'B' && env[1] == 'U' && env[2] == 'N' && env[3] == '_' && env[4] == 'J' && env[5] == 'S' && env[6] == 'C' && env[7] == '_')) [[likely]] {
                    continue;
                }

                if (!JSC::Options::setOption(env + 8)) [[unlikely]] {
                    onCrash(env, strlen(env));
                }
            }
        }
        JSC::Options::assertOptionsAreCoherent();
    }

    // NOLINTEND
}

extern "C" void* Bun__getVM();

extern "C" void Bun__setDefaultGlobalObject(Zig::GlobalObject* globalObject);

static JSValue formatStackTraceToJSValue(JSC::VM& vm, Zig::GlobalObject* globalObject, JSC::JSGlobalObject* lexicalGlobalObject, JSC::JSObject* errorObject, JSC::JSArray* callSites)
{
    auto scope = DECLARE_THROW_SCOPE(vm);

    // default formatting
    size_t framesCount = callSites->length();

    WTF::StringBuilder sb;

    auto errorMessage = errorObject->getIfPropertyExists(lexicalGlobalObject, vm.propertyNames->message);
    RETURN_IF_EXCEPTION(scope, {});
    if (errorMessage) {
        auto* str = errorMessage.toString(lexicalGlobalObject);
        RETURN_IF_EXCEPTION(scope, {});
        if (str->length() > 0) {
            auto value = str->view(lexicalGlobalObject);
            RETURN_IF_EXCEPTION(scope, {});
            sb.append("Error: "_s);
            sb.append(value.data);
        } else {
            sb.append("Error"_s);
        }
    } else {
        sb.append("Error"_s);
    }

    for (size_t i = 0; i < framesCount; i++) {
        sb.append("\n    at "_s);

        JSC::JSValue callSiteValue = callSites->getIndex(lexicalGlobalObject, i);
        RETURN_IF_EXCEPTION(scope, {});

        if (CallSite* callSite = JSC::jsDynamicCast<CallSite*>(callSiteValue)) {
            callSite->formatAsString(vm, lexicalGlobalObject, sb);
            RETURN_IF_EXCEPTION(scope, {});
        } else {
            // This matches Node.js / V8's behavior
            // It can become "at [object Object]" if the object is not a CallSite
            auto* str = callSiteValue.toString(lexicalGlobalObject);
            RETURN_IF_EXCEPTION(scope, {});
            auto value = str->value(lexicalGlobalObject);
            RETURN_IF_EXCEPTION(scope, {});
            sb.append(value.data);
        }
    }

    return jsString(vm, sb.toString());
}

static JSValue formatStackTraceToJSValue(JSC::VM& vm, Zig::GlobalObject* globalObject, JSC::JSGlobalObject* lexicalGlobalObject, JSC::JSObject* errorObject, JSC::JSArray* callSites, JSValue prepareStackTrace)
{
    auto scope = DECLARE_THROW_SCOPE(vm);
    auto stackStringValue = formatStackTraceToJSValue(vm, globalObject, lexicalGlobalObject, errorObject, callSites);
    RETURN_IF_EXCEPTION(scope, {});

    if (prepareStackTrace && prepareStackTrace.isObject()) {
        JSC::CallData prepareStackTraceCallData = JSC::getCallData(prepareStackTrace);

        if (prepareStackTraceCallData.type != JSC::CallData::Type::None) {
            // In Node, if you console.log(error.stack) inside Error.prepareStackTrace
            // it will display the stack as a formatted string, so we have to do the same.
            errorObject->putDirect(vm, vm.propertyNames->stack, stackStringValue, 0);

            JSC::MarkedArgumentBuffer arguments;
            arguments.append(errorObject);
            arguments.append(callSites);

            JSC::JSValue result = profiledCall(
                lexicalGlobalObject,
                JSC::ProfilingReason::Other,
                prepareStackTrace,
                prepareStackTraceCallData,
                lexicalGlobalObject->m_errorStructure.constructor(globalObject),
                arguments);

            RETURN_IF_EXCEPTION(scope, stackStringValue);

            if (result.isUndefinedOrNull()) {
                result = jsUndefined();
            }

            return result;
        }
    }

    return stackStringValue;
}

static JSValue formatStackTraceToJSValueWithoutPrepareStackTrace(JSC::VM& vm, Zig::GlobalObject* globalObject, JSC::JSGlobalObject* lexicalGlobalObject, JSC::JSObject* errorObject, JSC::JSArray* callSites)
{
    JSValue prepareStackTrace = {};
    if (lexicalGlobalObject->inherits<Zig::GlobalObject>()) {
        if (auto prepare = globalObject->m_errorConstructorPrepareStackTraceValue.get()) {
            prepareStackTrace = prepare;
        }
    } else {
        auto scope = DECLARE_CATCH_SCOPE(vm);

        auto* errorConstructor = lexicalGlobalObject->m_errorStructure.constructor(globalObject);
        prepareStackTrace = errorConstructor->getIfPropertyExists(lexicalGlobalObject, JSC::Identifier::fromString(vm, "prepareStackTrace"_s));
        CLEAR_IF_EXCEPTION(scope);
    }

    return formatStackTraceToJSValue(vm, globalObject, lexicalGlobalObject, errorObject, callSites, prepareStackTrace);
}

WTF::String Bun::formatStackTrace(
    JSC::VM& vm,
    Zig::GlobalObject* globalObject,
    JSC::JSGlobalObject* lexicalGlobalObject,
    const WTF::String& name,
    const WTF::String& message,
    OrdinalNumber& line,
    OrdinalNumber& column,
    WTF::String& sourceURL,
    Vector<JSC::StackFrame>& stackTrace,
    JSC::JSObject* errorInstance)
{
    WTF::StringBuilder sb;

    if (!name.isEmpty()) {
        sb.append(name);
        if (!message.isEmpty()) {
            sb.append(": "_s);
            sb.append(message);
        }
    } else if (!message.isEmpty()) {
        sb.append(message);
    }

    // FIXME: why can size == 6 and capacity == 0?
    // https://discord.com/channels/876711213126520882/1174901590457585765/1174907969419350036
    size_t framesCount = stackTrace.size();

    bool hasSet = false;
    void* bunVM = nullptr;
    const auto getBunVM = [&]() -> void* {
        if (!bunVM) {
            bunVM = clientData(vm)->bunVM;
        }
        return bunVM;
    };

    if (errorInstance) {
        if (JSC::ErrorInstance* err = jsDynamicCast<JSC::ErrorInstance*>(errorInstance)) {
            if (err->errorType() == ErrorType::SyntaxError && (stackTrace.isEmpty() || stackTrace.at(0).sourceURL(vm) != err->sourceURL())) {
                // There appears to be an off-by-one error.
                // The following reproduces the issue:
                // /* empty comment */
                // "".test(/[a-0]/);
                auto originalLine = WTF::OrdinalNumber::fromOneBasedInt(err->line());

                ZigStackFrame remappedFrame = {};
                memset(&remappedFrame, 0, sizeof(ZigStackFrame));

                remappedFrame.position.line_zero_based = originalLine.zeroBasedInt();
                remappedFrame.position.column_zero_based = 0;

                String sourceURLForFrame = err->sourceURL();

                // If it's not a Zig::GlobalObject, don't bother source-mapping it.
                if (globalObject && !sourceURLForFrame.isEmpty()) {
                    // https://github.com/oven-sh/bun/issues/3595
                    if (!sourceURLForFrame.isEmpty()) {
                        remappedFrame.source_url = Bun::toStringRef(sourceURLForFrame);
                        // This ensures the lifetime of the sourceURL is accounted for correctly
                        Bun__remapStackFramePositions(getBunVM(), &remappedFrame, 1);

                        sourceURLForFrame = remappedFrame.source_url.toWTFString();
                    }
                }

                // there is always a newline before each stack frame line, ensuring that the name + message
                // exist on the first line, even if both are empty
                sb.append("\n"_s);

                sb.append("    at <parse> ("_s);

                sb.append(remappedFrame.source_url.toWTFString());

                if (remappedFrame.remapped) {
                    errorInstance->putDirect(vm, builtinNames(vm).originalLinePublicName(), jsNumber(originalLine.oneBasedInt()), PropertyAttribute::DontEnum | 0);
                    hasSet = true;
                    line = remappedFrame.position.line();
                }

                if (remappedFrame.remapped) {
                    sb.append(':');
                    sb.append(remappedFrame.position.line().oneBasedInt());
                } else {
                    sb.append(':');
                    sb.append(originalLine.oneBasedInt());
                }

                sb.append(')');
            }
        }
    }

    if (framesCount == 0) {
        ASSERT(stackTrace.isEmpty());
        return sb.toString();
    }

    sb.append("\n"_s);

    for (size_t i = 0; i < framesCount; i++) {
        StackFrame& frame = stackTrace.at(i);
        unsigned int flags = static_cast<unsigned int>(FunctionNameFlags::AddNewKeyword);

        // -- get the data we need to render the text --
        JSC::JSGlobalObject* globalObjectForFrame = lexicalGlobalObject;
        if (frame.hasLineAndColumnInfo()) {
            auto* callee = frame.callee();
            if (callee) {
                if (auto* object = callee->getObject()) {
                    globalObjectForFrame = object->globalObject();
                }
            }
        }

        WTF::String functionName = Zig::functionName(vm, globalObjectForFrame, frame, !errorInstance, &flags);
        OrdinalNumber originalLine = {};
        OrdinalNumber originalColumn = {};
        OrdinalNumber displayLine = {};
        OrdinalNumber displayColumn = {};
        WTF::String sourceURLForFrame;

        if (frame.hasLineAndColumnInfo()) {
            ZigStackFrame remappedFrame = {};
            LineColumn lineColumn = frame.computeLineAndColumn();
            originalLine = OrdinalNumber::fromOneBasedInt(lineColumn.line);
            originalColumn = OrdinalNumber::fromOneBasedInt(lineColumn.column);
            displayLine = originalLine;
            displayColumn = originalColumn;

            remappedFrame.position.line_zero_based = originalLine.zeroBasedInt();
            remappedFrame.position.column_zero_based = originalColumn.zeroBasedInt();

            sourceURLForFrame = Zig::sourceURL(vm, frame);

            bool isDefinitelyNotRunninginNodeVMGlobalObject = globalObject == globalObjectForFrame;

            bool isDefaultGlobalObjectInAFinalizer = (globalObject && !lexicalGlobalObject && !errorInstance);
            if (isDefinitelyNotRunninginNodeVMGlobalObject || isDefaultGlobalObjectInAFinalizer) {
                // https://github.com/oven-sh/bun/issues/3595
                if (!sourceURLForFrame.isEmpty()) {
                    remappedFrame.source_url = Bun::toStringRef(sourceURLForFrame);

                    // This ensures the lifetime of the sourceURL is accounted for correctly
                    Bun__remapStackFramePositions(getBunVM(), &remappedFrame, 1);

                    sourceURLForFrame = remappedFrame.source_url.toWTFString();
                }
            }

            displayLine = remappedFrame.position.line();
            displayColumn = remappedFrame.position.column();

            if (!hasSet) {
                hasSet = true;
                line = remappedFrame.position.line();
                column = remappedFrame.position.column();
                sourceURL = sourceURLForFrame;

                if (remappedFrame.remapped) {
                    if (errorInstance) {
                        errorInstance->putDirect(vm, builtinNames(vm).originalLinePublicName(), jsNumber(originalLine.oneBasedInt()), PropertyAttribute::DontEnum | 0);
                        errorInstance->putDirect(vm, builtinNames(vm).originalColumnPublicName(), jsNumber(originalColumn.oneBasedInt()), PropertyAttribute::DontEnum | 0);
                    }
                }
            }
        }

        if (functionName.isEmpty()) {
            if (flags & (static_cast<unsigned int>(FunctionNameFlags::Eval) | static_cast<unsigned int>(FunctionNameFlags::Function))) {
                functionName = "<anonymous>"_s;
            }
        }

        if (sourceURLForFrame.isEmpty()) {
            if (flags & static_cast<unsigned int>(FunctionNameFlags::Builtin)) {
                sourceURLForFrame = "native"_s;
            } else {
                sourceURLForFrame = "unknown"_s;
            }
        }

        // --- actually render the text ---

        sb.append("    at "_s);

        if (!functionName.isEmpty()) {
            sb.append(functionName);
            sb.append(" ("_s);
        }

        if (!sourceURLForFrame.isEmpty()) {
            sb.append(sourceURLForFrame);
            if (displayLine.zeroBasedInt() > 0 || displayColumn.zeroBasedInt() > 0) {
                sb.append(':');
                sb.append(displayLine.oneBasedInt());

                if (displayColumn.zeroBasedInt() > 0) {
                    sb.append(':');
                    sb.append(displayColumn.oneBasedInt());
                }
            }
        }

        if (!functionName.isEmpty()) {
            sb.append(')');
        }

        if (i != framesCount - 1) {
            sb.append("\n"_s);
        }
    }

    return sb.toString();
}

// error.stack calls this function
static String computeErrorInfoWithoutPrepareStackTrace(
    JSC::VM& vm,
    Zig::GlobalObject* globalObject,
    JSC::JSGlobalObject* lexicalGlobalObject,
    Vector<StackFrame>& stackTrace,
    OrdinalNumber& line,
    OrdinalNumber& column,
    String& sourceURL,
    JSObject* errorInstance)
{
    auto scope = DECLARE_THROW_SCOPE(vm);
    WTF::String name = "Error"_s;
    WTF::String message;

    if (errorInstance) {
        // Note that we are not allowed to allocate memory in here. It's called inside a finalizer.
        if (auto* instance = jsDynamicCast<ErrorInstance*>(errorInstance)) {
            if (!lexicalGlobalObject) {
                lexicalGlobalObject = errorInstance->globalObject();
            }
            name = instance->sanitizedNameString(lexicalGlobalObject);
            RETURN_IF_EXCEPTION(scope, {});
            message = instance->sanitizedMessageString(lexicalGlobalObject);
            RETURN_IF_EXCEPTION(scope, {});
        }
    }

    if (!globalObject) [[unlikely]] {
        globalObject = defaultGlobalObject();
    }

    return Bun::formatStackTrace(vm, globalObject, lexicalGlobalObject, name, message, line, column, sourceURL, stackTrace, errorInstance);
}

static JSValue computeErrorInfoWithPrepareStackTrace(JSC::VM& vm, Zig::GlobalObject* globalObject, JSC::JSGlobalObject* lexicalGlobalObject, Vector<StackFrame>& stackFrames, OrdinalNumber& line, OrdinalNumber& column, String& sourceURL, JSObject* errorObject, JSObject* prepareStackTrace)
{
    auto scope = DECLARE_THROW_SCOPE(vm);

    JSCStackTrace stackTrace = JSCStackTrace::fromExisting(vm, stackFrames);

    // Note: we cannot use tryCreateUninitializedRestricted here because we cannot allocate memory inside initializeIndex()
    MarkedArgumentBuffer callSites;

    // Create the call sites (one per frame)
    GlobalObject::createCallSitesFromFrames(globalObject, lexicalGlobalObject, stackTrace, callSites);

    // We need to sourcemap it if it's a GlobalObject.

    for (int i = 0; i < stackTrace.size(); i++) {
        ZigStackFrame frame = {};
        auto& stackFrame = stackFrames.at(i);
        String sourceURLForFrame = Zig::sourceURL(vm, stackFrame);

        // When you use node:vm, the global object can be different on a
        // per-frame basis. We should sourcemap the frames which are in Bun's
        // global object, and not sourcemap the frames which are in a different
        // global object.
        JSGlobalObject* globalObjectForFrame = lexicalGlobalObject;

        if (stackFrame.hasLineAndColumnInfo()) {
            auto* callee = stackFrame.callee();
            // https://github.com/oven-sh/bun/issues/17698
            if (callee) {
                if (auto* object = callee->getObject()) {
                    globalObjectForFrame = object->globalObject();
                }
            }
        }

        if (globalObjectForFrame == globalObject) {
            if (JSCStackFrame::SourcePositions* sourcePositions = stackTrace.at(i).getSourcePositions()) {
                frame.position.line_zero_based = sourcePositions->line.zeroBasedInt();
                frame.position.column_zero_based = sourcePositions->column.zeroBasedInt();
            } else {
                frame.position.line_zero_based = -1;
                frame.position.column_zero_based = -1;
            }

            if (!sourceURLForFrame.isEmpty()) {
                frame.source_url = Bun::toStringRef(sourceURLForFrame);

                // This ensures the lifetime of the sourceURL is accounted for correctly
                Bun__remapStackFramePositions(globalObject->bunVM(), &frame, 1);

                sourceURLForFrame = frame.source_url.toWTFString();
            }
        }

        auto* callsite = jsCast<CallSite*>(callSites.at(i));

        if (!sourceURLForFrame.isEmpty())
            callsite->setSourceURL(vm, jsString(vm, sourceURLForFrame));

        if (frame.remapped) {
            callsite->setLineNumber(frame.position.line());
            callsite->setColumnNumber(frame.position.column());
        }
    }

    JSArray* callSitesArray = JSC::constructArray(globalObject, globalObject->arrayStructureForIndexingTypeDuringAllocation(JSC::ArrayWithContiguous), callSites);
    RETURN_IF_EXCEPTION(scope, {});

    RELEASE_AND_RETURN(scope, formatStackTraceToJSValue(vm, globalObject, lexicalGlobalObject, errorObject, callSitesArray, prepareStackTrace));
}

static String computeErrorInfoToString(JSC::VM& vm, Vector<StackFrame>& stackTrace, OrdinalNumber& line, OrdinalNumber& column, String& sourceURL)
{

    Zig::GlobalObject* globalObject = nullptr;
    JSC::JSGlobalObject* lexicalGlobalObject = nullptr;

    return computeErrorInfoWithoutPrepareStackTrace(vm, globalObject, lexicalGlobalObject, stackTrace, line, column, sourceURL, nullptr);
}

static JSValue computeErrorInfoToJSValueWithoutSkipping(JSC::VM& vm, Vector<StackFrame>& stackTrace, OrdinalNumber& line, OrdinalNumber& column, String& sourceURL, JSObject* errorInstance)
{
    Zig::GlobalObject* globalObject = nullptr;
    JSC::JSGlobalObject* lexicalGlobalObject = nullptr;
    lexicalGlobalObject = errorInstance->globalObject();
    globalObject = jsDynamicCast<Zig::GlobalObject*>(lexicalGlobalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);

    // Error.prepareStackTrace - https://v8.dev/docs/stack-trace-api#customizing-stack-traces
    if (!globalObject) {
        // node:vm will use a different JSGlobalObject
        globalObject = defaultGlobalObject();
        if (!globalObject->isInsideErrorPrepareStackTraceCallback) {
            auto* errorConstructor = lexicalGlobalObject->m_errorStructure.constructor(lexicalGlobalObject);
            auto prepareStackTrace = errorConstructor->getIfPropertyExists(lexicalGlobalObject, Identifier::fromString(vm, "prepareStackTrace"_s));
            RETURN_IF_EXCEPTION(scope, {});
            if (prepareStackTrace) {
                if (prepareStackTrace.isCell() && prepareStackTrace.isObject() && prepareStackTrace.isCallable()) {
                    globalObject->isInsideErrorPrepareStackTraceCallback = true;
                    auto result = computeErrorInfoWithPrepareStackTrace(vm, globalObject, lexicalGlobalObject, stackTrace, line, column, sourceURL, errorInstance, prepareStackTrace.getObject());
                    globalObject->isInsideErrorPrepareStackTraceCallback = false;
                    RELEASE_AND_RETURN(scope, result);
                }
            }
        }
    } else if (!globalObject->isInsideErrorPrepareStackTraceCallback) {
        if (JSValue prepareStackTrace = globalObject->m_errorConstructorPrepareStackTraceValue.get()) {
            if (prepareStackTrace) {
                if (prepareStackTrace.isCallable()) {
                    globalObject->isInsideErrorPrepareStackTraceCallback = true;
                    auto result = computeErrorInfoWithPrepareStackTrace(vm, globalObject, lexicalGlobalObject, stackTrace, line, column, sourceURL, errorInstance, prepareStackTrace.getObject());
                    globalObject->isInsideErrorPrepareStackTraceCallback = false;
                    RELEASE_AND_RETURN(scope, result);
                }
            }
        }
    }

    String result = computeErrorInfoWithoutPrepareStackTrace(vm, globalObject, lexicalGlobalObject, stackTrace, line, column, sourceURL, errorInstance);
    RETURN_IF_EXCEPTION(scope, {});
    return jsString(vm, result);
}

static JSValue computeErrorInfoToJSValue(JSC::VM& vm, Vector<StackFrame>& stackTrace, OrdinalNumber& line, OrdinalNumber& column, String& sourceURL, JSObject* errorInstance)
{
    return computeErrorInfoToJSValueWithoutSkipping(vm, stackTrace, line, column, sourceURL, errorInstance);
}

static String computeErrorInfoWrapperToString(JSC::VM& vm, Vector<StackFrame>& stackTrace, unsigned int& line_in, unsigned int& column_in, String& sourceURL)
{
    OrdinalNumber line = OrdinalNumber::fromOneBasedInt(line_in);
    OrdinalNumber column = OrdinalNumber::fromOneBasedInt(column_in);

    auto scope = DECLARE_CATCH_SCOPE(vm);
    WTF::String result = computeErrorInfoToString(vm, stackTrace, line, column, sourceURL);
    if (scope.exception()) {
        // TODO: is this correct? vm.setOnComputeErrorInfo doesnt appear to properly handle a function that can throw
        // test/js/node/test/parallel/test-stream-writable-write-writev-finish.js is the one that trips the exception checker
        scope.clearException();
        result = WTF::emptyString();
    }

    line_in = line.oneBasedInt();
    column_in = column.oneBasedInt();

    return result;
}

static JSValue computeErrorInfoWrapperToJSValue(JSC::VM& vm, Vector<StackFrame>& stackTrace, unsigned int& line_in, unsigned int& column_in, String& sourceURL, JSObject* errorInstance)
{
    OrdinalNumber line = OrdinalNumber::fromOneBasedInt(line_in);
    OrdinalNumber column = OrdinalNumber::fromOneBasedInt(column_in);

    JSValue result = computeErrorInfoToJSValue(vm, stackTrace, line, column, sourceURL, errorInstance);

    line_in = line.oneBasedInt();
    column_in = column.oneBasedInt();

    return result;
}

static void checkIfNextTickWasCalledDuringMicrotask(JSC::VM& vm)
{
    auto* globalObject = defaultGlobalObject();
    if (auto queue = globalObject->m_nextTickQueue.get()) {
        globalObject->resetOnEachMicrotaskTick();
        queue->drain(vm, globalObject);
    }
}

static void cleanupAsyncHooksData(JSC::VM& vm)
{
    auto* globalObject = defaultGlobalObject();
    globalObject->m_asyncContextData.get()->putInternalField(vm, 0, jsUndefined());
    globalObject->asyncHooksNeedsCleanup = false;
    if (!globalObject->m_nextTickQueue) {
        vm.setOnEachMicrotaskTick(&checkIfNextTickWasCalledDuringMicrotask);
        checkIfNextTickWasCalledDuringMicrotask(vm);
    } else {
        vm.setOnEachMicrotaskTick(nullptr);
    }
}

GlobalObject* GlobalObject::create(JSC::VM& vm, JSC::Structure* structure)
{
    GlobalObject* ptr = new (NotNull, JSC::allocateCell<GlobalObject>(vm)) GlobalObject(vm, structure, &globalObjectMethodTable());
    ptr->finishCreation(vm);
    return ptr;
}

GlobalObject* GlobalObject::create(JSC::VM& vm, JSC::Structure* structure, uint32_t scriptExecutionContextId)
{
    GlobalObject* ptr = new (NotNull, JSC::allocateCell<GlobalObject>(vm)) GlobalObject(vm, structure, scriptExecutionContextId, &globalObjectMethodTable());
    ptr->finishCreation(vm);
    return ptr;
}

GlobalObject* GlobalObject::create(JSC::VM& vm, JSC::Structure* structure, const JSC::GlobalObjectMethodTable* methodTable)
{
    GlobalObject* ptr = new (NotNull, JSC::allocateCell<GlobalObject>(vm)) GlobalObject(vm, structure, methodTable);
    ptr->finishCreation(vm);
    return ptr;
}

GlobalObject* GlobalObject::create(JSC::VM& vm, JSC::Structure* structure, uint32_t scriptExecutionContextId, const JSC::GlobalObjectMethodTable* methodTable)
{
    GlobalObject* ptr = new (NotNull, JSC::allocateCell<GlobalObject>(vm)) GlobalObject(vm, structure, scriptExecutionContextId, methodTable);
    ptr->finishCreation(vm);
    return ptr;
}

JSC::Structure* GlobalObject::createStructure(JSC::VM& vm)
{
    auto* structure = JSC::Structure::create(vm, nullptr, jsNull(), JSC::TypeInfo(JSC::GlobalObjectType, StructureFlags & ~IsImmutablePrototypeExoticObject), info());
    structure->setTransitionWatchpointIsLikelyToBeFired(true);
    return structure;
}

void Zig::GlobalObject::resetOnEachMicrotaskTick()
{
    auto& vm = this->vm();
    if (this->asyncHooksNeedsCleanup) {
        vm.setOnEachMicrotaskTick(&cleanupAsyncHooksData);
    } else {
        if (this->m_nextTickQueue) {
            vm.setOnEachMicrotaskTick(nullptr);
        } else {
            vm.setOnEachMicrotaskTick(&checkIfNextTickWasCalledDuringMicrotask);
        }
    }
}

extern "C" size_t Bun__reported_memory_size;

// executionContextId: -1 for main thread
// executionContextId: maxInt32 for macros
// executionContextId: >-1 for workers
extern "C" JSC::JSGlobalObject* Zig__GlobalObject__create(void* console_client, int32_t executionContextId, bool miniMode, bool evalMode, void* worker_ptr)
{
    auto heapSize = miniMode ? JSC::HeapType::Small : JSC::HeapType::Large;
    RefPtr<JSC::VM> vmPtr = JSC::VM::tryCreate(heapSize);
    if (!vmPtr) [[unlikely]] {
        BUN_PANIC("Failed to allocate JavaScriptCore Virtual Machine. Did your computer run out of memory? Or maybe you compiled Bun with a mismatching libc++ version or compiler?");
    }
    vmPtr->refSuppressingSaferCPPChecking();
    JSC::VM& vm = *vmPtr;
    // This must happen before JSVMClientData::create
    vm.heap.acquireAccess();
    JSC::JSLockHolder locker(vm);

    {
        const char* disable_stop_if_necessary_timer = getenv("BUN_DISABLE_STOP_IF_NECESSARY_TIMER");
        // Keep stopIfNecessaryTimer enabled by default when either:
        // - `--smol` is passed
        // - The machine has less than 4GB of RAM
        bool shouldDisableStopIfNecessaryTimer = !miniMode;

        if (disable_stop_if_necessary_timer) {
            const char value = disable_stop_if_necessary_timer[0];
            if (value == '0') {
                shouldDisableStopIfNecessaryTimer = false;
            } else if (value == '1') {
                shouldDisableStopIfNecessaryTimer = true;
            }
        }

        if (shouldDisableStopIfNecessaryTimer) {
            vm.heap.disableStopIfNecessaryTimer();
        }

        // This is used to tell us in the crash reporter how much RSS the system has.
        //
        // JSC already calls this inside JSC::VM::tryCreate and it's cached
        // internally, so there's little cost to calling this multiple times.
        Bun__reported_memory_size = WTF::ramSize();
    }

    // Every JS VM's RunLoop should use Bun's RunLoop implementation
    ASSERT(vmPtr->runLoop().kind() == WTF::RunLoop::Kind::Bun);

    WebCore::JSVMClientData::create(&vm, Bun__getVM());

    const auto createGlobalObject = [&]() -> Zig::GlobalObject* {
        if (executionContextId == std::numeric_limits<int32_t>::max() || executionContextId > 1) [[unlikely]] {
            auto* structure = Zig::GlobalObject::createStructure(vm);
            if (!structure) [[unlikely]] {
                return nullptr;
            }
            return Zig::GlobalObject::create(
                vm,
                structure,
                static_cast<ScriptExecutionContextIdentifier>(executionContextId));
        } else if (evalMode) {
            auto* structure = Zig::EvalGlobalObject::createStructure(vm);
            if (!structure) [[unlikely]] {
                return nullptr;
            }
            return Zig::EvalGlobalObject::create(
                vm,
                structure,
                &Zig::EvalGlobalObject::globalObjectMethodTable());

        } else {
            auto* structure = Zig::GlobalObject::createStructure(vm);
            if (!structure) [[unlikely]] {
                return nullptr;
            }
            return Zig::GlobalObject::create(
                vm,
                structure);
        }
    };

    auto* globalObject = createGlobalObject();
    if (!globalObject) [[unlikely]] {
        BUN_PANIC("Failed to allocate JavaScript global object. Did your computer run out of memory?");
    }

    globalObject->setConsole(console_client);
    globalObject->isThreadLocalDefaultGlobalObject = true;
    globalObject->setStackTraceLimit(DEFAULT_ERROR_STACK_TRACE_LIMIT); // Node.js defaults to 10
    Bun__setDefaultGlobalObject(globalObject);
    JSC::gcProtect(globalObject);

    vm.setOnComputeErrorInfo(computeErrorInfoWrapperToString);
    vm.setOnComputeErrorInfoJSValue(computeErrorInfoWrapperToJSValue);
    vm.setOnEachMicrotaskTick([](JSC::VM& vm) -> void {
        // if you process.nextTick on a microtask we need this
        auto* globalObject = defaultGlobalObject();
        if (auto queue = globalObject->m_nextTickQueue.get()) {
            globalObject->resetOnEachMicrotaskTick();
            queue->drain(vm, globalObject);
            return;
        }
    });

    if (executionContextId > -1) {
        const auto initializeWorker = [&](WebCore::Worker& worker) -> void {
            auto& options = worker.options();

            if (options.env.has_value()) {
                HashMap<String, String> map = WTFMove(*std::exchange(options.env, std::nullopt));
                auto size = map.size();

                // In theory, a GC could happen before we finish putting all the properties on the object.
                // So we use a MarkedArgumentBuffer to ensure that the strings are not collected and we immediately put them on the object.
                MarkedArgumentBuffer strings;
                strings.ensureCapacity(size);
                for (const auto& value : map.values()) {
                    strings.append(jsString(vm, value));
                }

                auto env = JSC::constructEmptyObject(globalObject, globalObject->objectPrototype(), size >= JSFinalObject::maxInlineCapacity ? JSFinalObject::maxInlineCapacity : size);
                size_t i = 0;
                for (auto k : map) {
                    // They can have environment variables with numbers as keys.
                    // So we must use putDirectMayBeIndex to handle that.
                    env->putDirectMayBeIndex(globalObject, JSC::Identifier::fromString(vm, WTFMove(k.key)), strings.at(i++));
                }
                globalObject->m_processEnvObject.set(vm, globalObject, env);
            }

            // Ensure that the TerminationException singleton is constructed. Workers need this so
            // that we can request their termination from another thread. For the main thread, we
            // can delay this until we are actually requesting termination (until and unless we ever
            // do need to request termination from another thread).
            vm.ensureTerminationException();
            // Make the VM stop sooner once terminated (e.g. microtasks won't run)
            vm.forbidExecutionOnTermination();
        };

        if (auto* worker = static_cast<WebCore::Worker*>(worker_ptr)) {
            initializeWorker(*worker);
        }
    }

    return globalObject;
}

JSC_DEFINE_HOST_FUNCTION(functionFulfillModuleSync,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::CallFrame* callFrame))
{
    Zig::GlobalObject* globalObject = jsCast<Zig::GlobalObject*>(lexicalGlobalObject);

    auto& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);
    JSC::JSValue keyAny = callFrame->argument(0);
    JSC::JSString* moduleKeyString = keyAny.toString(globalObject);
    RETURN_IF_EXCEPTION(scope, {});
    auto moduleKey = moduleKeyString->value(globalObject);
    RETURN_IF_EXCEPTION(scope, {});

    RETURN_IF_EXCEPTION(scope, {});

    if (moduleKey->endsWith(".node"_s)) {
        throwException(globalObject, scope, createTypeError(globalObject, "To load Node-API modules, use require() or process.dlopen instead of importSync."_s));
        return {};
    }

    auto specifier = Bun::toString(moduleKey);
    ErrorableResolvedSource res;
    res.success = false;
    // zero-initialize entire result union. zeroed BunString has BunStringTag::Dead, and zeroed
    // EncodedJSValues are empty, which our code should be handling
    memset(&res.result, 0, sizeof res.result);

    JSValue result = Bun::fetchESMSourceCodeSync(
        globalObject,
        moduleKeyString,
        &res,
        &specifier,
        &specifier,
        nullptr);

    if (scope.exception() || !result) {
        RELEASE_AND_RETURN(scope, JSValue::encode(JSC::jsUndefined()));
    }

    globalObject->moduleLoader()->provideFetch(globalObject, keyAny, jsCast<JSC::JSSourceCode*>(result)->sourceCode());
    RELEASE_AND_RETURN(scope, JSValue::encode(JSC::jsUndefined()));
}

extern "C" void* Zig__GlobalObject__getModuleRegistryMap(JSC::JSGlobalObject* arg0)
{
    if (JSC::JSObject* loader = JSC::jsDynamicCast<JSC::JSObject*>(arg0->moduleLoader())) {
        JSC::JSMap* map = JSC::jsDynamicCast<JSC::JSMap*>(
            loader->getDirect(arg0->vm(), JSC::Identifier::fromString(arg0->vm(), "registry"_s)));

        JSC::JSMap* cloned = map->clone(arg0, arg0->vm(), arg0->mapStructure());
        JSC::gcProtect(cloned);

        return cloned;
    }

    return nullptr;
}

extern "C" bool Zig__GlobalObject__resetModuleRegistryMap(JSC::JSGlobalObject* globalObject,
    void* map_ptr)
{
    if (map_ptr == nullptr)
        return false;
    JSC::JSMap* map = reinterpret_cast<JSC::JSMap*>(map_ptr);
    auto& vm = JSC::getVM(globalObject);
    if (JSC::JSObject* obj = JSC::jsDynamicCast<JSC::JSObject*>(globalObject->moduleLoader())) {
        auto identifier = JSC::Identifier::fromString(globalObject->vm(), "registry"_s);

        if (JSC::JSMap* oldMap = JSC::jsDynamicCast<JSC::JSMap*>(
                obj->getDirect(globalObject->vm(), identifier))) {

            vm.finalizeSynchronousJSExecution();

            obj->putDirect(globalObject->vm(), identifier,
                map->clone(globalObject, globalObject->vm(), globalObject->mapStructure()));

            // vm.deleteAllLinkedCode(JSC::DeleteAllCodeEffort::DeleteAllCodeIfNotCollecting);
            // JSC::Heap::PreventCollectionScope(vm.heap);
            oldMap->clear(globalObject);
            JSC::gcUnprotect(oldMap);
            // vm.heap.completeAllJITPlans();

            // vm.forEachScriptExecutableSpace([&](auto &spaceAndSet) {
            //   JSC::HeapIterationScope heapIterationScope(vm.heap);
            //   auto &set = spaceAndSet.set;
            //   set.forEachLiveCell([&](JSC::HeapCell *cell, JSC::HeapCell::Kind) {
            //     if (JSC::ModuleProgramExecutable *executable =
            //           JSC::jsDynamicCast<JSC::ModuleProgramExecutable *>(cell)) {
            //       executable->clearCode(set);
            //     }
            //   });
            // });

            // globalObject->vm().heap.deleteAllUnlinkedCodeBlocks(
            //   JSC::DeleteAllCodeEffort::PreventCollectionAndDeleteAllCode);
        }
    }
    // map
    // }
    return true;
}

#define WEBCORE_GENERATED_CONSTRUCTOR_GETTER(ConstructorName)                                                                                                       \
    JSValue ConstructorName##ConstructorCallback(VM& vm, JSObject* lexicalGlobalObject)                                                                             \
    {                                                                                                                                                               \
        return WebCore::JS##ConstructorName::getConstructor(vm, JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject));                                              \
    }                                                                                                                                                               \
    JSC_DEFINE_CUSTOM_GETTER(ConstructorName##_getter,                                                                                                              \
        (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,                                                                                  \
            JSC::PropertyName))                                                                                                                                     \
    {                                                                                                                                                               \
        return JSC::JSValue::encode(WebCore::JS##ConstructorName::getConstructor(lexicalGlobalObject->vm(), JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject))); \
    }

String GlobalObject::defaultAgentClusterID()
{
    return makeString(WebCore::Process::identifier().toUInt64(), "-default"_s);
}

String GlobalObject::agentClusterID() const
{
    // TODO: workers
    // if (is<SharedWorkerGlobalScope>(scriptExecutionContext()))
    //     return makeString(WProcess::identifier().toUInt64(), "-sharedworker");
    return defaultAgentClusterID();
}

namespace Zig {

using namespace WebCore;

static JSGlobalObject* deriveShadowRealmGlobalObject(JSGlobalObject* globalObject)
{
    auto& vm = JSC::getVM(globalObject);
    Zig::GlobalObject* shadow = Zig::GlobalObject::create(
        vm,
        Zig::GlobalObject::createStructure(vm),
        ScriptExecutionContext::generateIdentifier());
    shadow->setConsole(shadow);

    return shadow;
}

extern "C" int Bun__VM__scriptExecutionStatus(void*);
JSC::ScriptExecutionStatus Zig::GlobalObject::scriptExecutionStatus(JSC::JSGlobalObject* globalObject, JSC::JSObject*)
{
    switch (Bun__VM__scriptExecutionStatus(jsCast<Zig::GlobalObject*>(globalObject)->bunVM())) {
    case 0:
        return JSC::ScriptExecutionStatus::Running;
    case 1:
        return JSC::ScriptExecutionStatus::Suspended;
    case 2:
        return JSC::ScriptExecutionStatus::Stopped;
    default: {
        RELEASE_ASSERT_NOT_REACHED();
    }
    }
}
const JSC::GlobalObjectMethodTable& GlobalObject::globalObjectMethodTable()
{
    static const JSC::GlobalObjectMethodTable table = {
        &supportsRichSourceInfo,
        &shouldInterruptScript,
        &javaScriptRuntimeFlags,
        nullptr, // &queueMicrotaskToEventLoop, // queueTaskToEventLoop
        nullptr, // &shouldInterruptScriptBeforeTimeout,
        &moduleLoaderImportModule, // moduleLoaderImportModule
        &moduleLoaderResolve, // moduleLoaderResolve
        &moduleLoaderFetch, // moduleLoaderFetch
        &moduleLoaderCreateImportMetaProperties, // moduleLoaderCreateImportMetaProperties
        &moduleLoaderEvaluate, // moduleLoaderEvaluate
        &promiseRejectionTracker, // promiseRejectionTracker
        &reportUncaughtExceptionAtEventLoop,
        &currentScriptExecutionOwner,
        &scriptExecutionStatus,
        nullptr, // reportViolationForUnsafeEval
        nullptr, // defaultLanguage
        &compileStreaming,
        &instantiateStreaming,
        &Zig::deriveShadowRealmGlobalObject,
        &codeForEval, // codeForEval
        &canCompileStrings, // canCompileStrings
        &trustedScriptStructure, // trustedScriptStructure
    };
    return table;
}

const JSC::GlobalObjectMethodTable& EvalGlobalObject::globalObjectMethodTable()
{
    static const JSC::GlobalObjectMethodTable table = {
        &supportsRichSourceInfo,
        &shouldInterruptScript,
        &javaScriptRuntimeFlags,
        // &queueMicrotaskToEventLoop, // queueTaskToEventLoop
        nullptr,
        nullptr, // &shouldInterruptScriptBeforeTimeout,
        &moduleLoaderImportModule, // moduleLoaderImportModule
        &moduleLoaderResolve, // moduleLoaderResolve
        &moduleLoaderFetch, // moduleLoaderFetch
        &moduleLoaderCreateImportMetaProperties, // moduleLoaderCreateImportMetaProperties
        &moduleLoaderEvaluate, // moduleLoaderEvaluate
        &promiseRejectionTracker, // promiseRejectionTracker
        &reportUncaughtExceptionAtEventLoop,
        &currentScriptExecutionOwner,
        &scriptExecutionStatus,
        nullptr, // reportViolationForUnsafeEval
        nullptr, // defaultLanguage
        &compileStreaming,
        &instantiateStreaming,
        &Zig::deriveShadowRealmGlobalObject,
        &codeForEval, // codeForEval
        &canCompileStrings, // canCompileStrings
        &trustedScriptStructure, // trustedScriptStructure
    };
    return table;
}

GlobalObject::GlobalObject(JSC::VM& vm, JSC::Structure* structure, const JSC::GlobalObjectMethodTable* methodTable)
    : Base(vm, structure, methodTable)
    , m_bunVM(Bun__getVM())
    , m_constructors(makeUnique<WebCore::DOMConstructors>())
    , m_world(static_cast<JSVMClientData*>(vm.clientData)->normalWorld())
    , m_worldIsNormal(true)
    , m_builtinInternalFunctions(vm)
    , m_scriptExecutionContext(new WebCore::ScriptExecutionContext(&vm, this))
    , globalEventScope(adoptRef(*new Bun::WorkerGlobalScope(m_scriptExecutionContext)))
{
    // m_scriptExecutionContext = globalEventScope.m_context;
    mockModule = Bun::JSMockModule::create(this);
    globalEventScope->m_context = m_scriptExecutionContext;
}

GlobalObject::GlobalObject(JSC::VM& vm, JSC::Structure* structure, WebCore::ScriptExecutionContextIdentifier contextId, const JSC::GlobalObjectMethodTable* methodTable)
    : Base(vm, structure, methodTable)
    , m_bunVM(Bun__getVM())
    , m_constructors(makeUnique<WebCore::DOMConstructors>())
    , m_world(static_cast<JSVMClientData*>(vm.clientData)->normalWorld())
    , m_worldIsNormal(true)
    , m_builtinInternalFunctions(vm)
    , m_scriptExecutionContext(new WebCore::ScriptExecutionContext(&vm, this, contextId))
    , globalEventScope(adoptRef(*new Bun::WorkerGlobalScope(m_scriptExecutionContext)))
{
    // m_scriptExecutionContext = globalEventScope.m_context;
    mockModule = Bun::JSMockModule::create(this);
    globalEventScope->m_context = m_scriptExecutionContext;
}

GlobalObject::~GlobalObject()
{
    if (auto* ctx = scriptExecutionContext()) {
        ctx->removeFromContextsMap();
        ctx->deref();
    }
}

void GlobalObject::destroy(JSCell* cell)
{
    static_cast<GlobalObject*>(cell)->GlobalObject::~GlobalObject();
}

WebCore::ScriptExecutionContext* GlobalObject::scriptExecutionContext() const
{
    return m_scriptExecutionContext;
}

void GlobalObject::reportUncaughtExceptionAtEventLoop(JSGlobalObject* globalObject,
    JSC::Exception* exception)
{
    Bun__reportUnhandledError(globalObject, JSValue::encode(JSValue(exception)));
}

extern "C" void Bun__handleHandledPromise(Zig::GlobalObject* JSGlobalObject, JSC::JSPromise* promise);

void GlobalObject::promiseRejectionTracker(JSGlobalObject* obj, JSC::JSPromise* promise,
    JSC::JSPromiseRejectionOperation operation)
{
    // Zig__GlobalObject__promiseRejectionTracker(
    //     obj, prom, reject == JSC::JSPromiseRejectionOperation::Reject ? 0 : 1);

    // Do this in C++ for now
    auto* globalObj = static_cast<GlobalObject*>(obj);
    switch (operation) {
    case JSPromiseRejectionOperation::Reject:
        globalObj->m_aboutToBeNotifiedRejectedPromises.append(JSC::Strong<JSPromise>(obj->vm(), promise));
        break;
    case JSPromiseRejectionOperation::Handle:
        bool removed = globalObj->m_aboutToBeNotifiedRejectedPromises.removeFirstMatching([&](Strong<JSPromise>& unhandledPromise) {
            return unhandledPromise.get() == promise;
        });
        if (removed) break;
        // The promise rejection has already been notified, now we need to queue it for the rejectionHandled event
        Bun__handleHandledPromise(globalObj, promise);
        break;
    }
}

void GlobalObject::setConsole(void* console)
{
    this->setConsoleClient(new Bun::ConsoleObject(console));
}

JSC_DEFINE_CUSTOM_GETTER(errorConstructorPrepareStackTraceGetter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    if (thisObject->m_errorConstructorPrepareStackTraceValue) {
        return JSValue::encode(thisObject->m_errorConstructorPrepareStackTraceValue.get());
    }

    return JSValue::encode(thisObject->m_errorConstructorPrepareStackTraceInternalValue.get(thisObject));
}

JSC_DEFINE_CUSTOM_SETTER(errorConstructorPrepareStackTraceSetter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::EncodedJSValue encodedValue, JSC::PropertyName property))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    JSValue value = JSValue::decode(encodedValue);
    if (value == thisObject->m_errorConstructorPrepareStackTraceInternalValue.get(thisObject)) {
        thisObject->m_errorConstructorPrepareStackTraceValue.clear();
    } else {
        thisObject->m_errorConstructorPrepareStackTraceValue.set(vm, thisObject, value);
    }

    return true;
}

#pragma mark - Globals

JSC_DEFINE_CUSTOM_GETTER(globalOnMessage,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(JSValue::decode(thisValue));
    return JSValue::encode(eventHandlerAttribute(thisObject->eventTarget(), eventNames().messageEvent, thisObject->world()));
}

JSC_DEFINE_CUSTOM_GETTER(globalOnError,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(JSValue::decode(thisValue));
    return JSValue::encode(eventHandlerAttribute(thisObject->eventTarget(), eventNames().errorEvent, thisObject->world()));
}

JSC_DEFINE_CUSTOM_SETTER(setGlobalOnMessage,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::EncodedJSValue encodedValue, JSC::PropertyName property))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    JSValue value = JSValue::decode(encodedValue);
    auto* thisObject = jsCast<Zig::GlobalObject*>(JSValue::decode(thisValue));
    setEventHandlerAttribute<JSEventListener>(thisObject->eventTarget(), eventNames().messageEvent, value, *thisObject);
    vm.writeBarrier(thisObject, value);
    ensureStillAliveHere(value);
    return true;
}

JSC_DEFINE_CUSTOM_SETTER(setGlobalOnError,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::EncodedJSValue encodedValue, JSC::PropertyName property))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    JSValue value = JSValue::decode(encodedValue);
    auto* thisObject = jsCast<Zig::GlobalObject*>(JSValue::decode(thisValue));
    setEventHandlerAttribute<JSEventListener>(thisObject->eventTarget(), eventNames().errorEvent, value, *thisObject);
    vm.writeBarrier(thisObject, value);
    ensureStillAliveHere(value);
    return true;
}

WebCore::EventTarget& GlobalObject::eventTarget()
{
    return globalEventScope;
}

JSC_DEFINE_CUSTOM_GETTER(functionLazyLoadStreamPrototypeMap_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        thisObject->readableStreamNativeMap());
}

JSC_DEFINE_CUSTOM_GETTER(JSBuffer_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    return JSC::JSValue::encode(JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject)->JSBufferConstructor());
}

// This macro defines the getter needed for ZigGlobalObject.lut.h
// "<ClassName>ConstructorCallback" is a PropertyCallback
// it also defines "<ClassName>_getter" which is the getter for a JSC::CustomGetterSetter
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(AbortController);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(AbortSignal);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(BroadcastChannel);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(ByteLengthQueuingStrategy)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(CloseEvent);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(CountQueuingStrategy)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(CryptoKey);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(CustomEvent);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(DOMException);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(DOMFormData);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(DOMURL);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(ErrorEvent);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(Event);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(EventTarget);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(FetchHeaders);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(MessageChannel);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(MessageEvent);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(MessagePort);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(Performance);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(PerformanceEntry);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(PerformanceMark);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(PerformanceMeasure);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(PerformanceObserver);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(PerformanceObserverEntryList)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(PerformanceResourceTiming)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(PerformanceServerTiming)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(PerformanceTiming)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(ReadableByteStreamController)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(ReadableStream)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(ReadableStreamBYOBReader)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(ReadableStreamBYOBRequest)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(ReadableStreamDefaultController)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(ReadableStreamDefaultReader)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(SubtleCrypto);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(TextEncoder);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(TextEncoderStream);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(TextDecoderStream);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(TransformStream)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(TransformStreamDefaultController)
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(URLSearchParams);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(WebSocket);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(Worker);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(WritableStream);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(WritableStreamDefaultController);
WEBCORE_GENERATED_CONSTRUCTOR_GETTER(WritableStreamDefaultWriter);

JSC_DEFINE_HOST_FUNCTION(functionGetSelf,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    return JSValue::encode(globalObject->globalThis());
}

JSC_DEFINE_HOST_FUNCTION(functionSetSelf,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    auto& vm = JSC::getVM(globalObject);
    JSC::JSValue value = callFrame->argument(0);
    // Chrome DevTools:
    //   > Object.getOwnPropertyDescriptor(globalThis, "self")
    //   < {enumerable: true, configurable: true, get: ƒ, set: ƒ}
    //   > globalThis.self = 123
    //   < 123
    //   > Object.getOwnPropertyDescriptor(globalThis, "self")
    //   < {value: 123, writable: true, enumerable: true, configurable: true}
    globalObject->putDirect(vm, WebCore::builtinNames(vm).selfPublicName(), value, 0);
    return JSValue::encode(value);
}

JSC_DEFINE_HOST_FUNCTION(functionQueueMicrotask,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::CallFrame* callFrame))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);

    JSValue callback = callFrame->argument(0);
    V::validateFunction(scope, lexicalGlobalObject, callback, "callback"_s);
    RETURN_IF_EXCEPTION(scope, {});

    auto* globalObject = defaultGlobalObject(lexicalGlobalObject);
    JSC::JSValue asyncContext = globalObject->m_asyncContextData.get()->getInternalField(0);

    // This is a JSC builtin function
    lexicalGlobalObject->queueMicrotask(globalObject->performMicrotaskFunction(), callback, asyncContext,
        JSC::JSValue {}, JSC::JSValue {});

    return JSC::JSValue::encode(JSC::jsUndefined());
}

using MicrotaskCallback = void (*)(void*);

JSC_DEFINE_HOST_FUNCTION(functionNativeMicrotaskTrampoline,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    // Do not use JSCell* here because the GC will try to visit it.
    double cellPtr = callFrame->uncheckedArgument(0).asNumber();
    double callbackPtr = callFrame->uncheckedArgument(1).asNumber();

    void* cell = reinterpret_cast<void*>(std::bit_cast<uintptr_t>(cellPtr));
    auto* callback = reinterpret_cast<MicrotaskCallback>(std::bit_cast<uintptr_t>(callbackPtr));
    callback(cell);
    return JSValue::encode(jsUndefined());
}

JSC_DEFINE_HOST_FUNCTION(functionStructuredClone, (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    auto& vm = JSC::getVM(globalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);

    if (callFrame->argumentCount() == 0) {
        throwTypeError(globalObject, throwScope, "structuredClone requires 1 argument"_s);
        return {};
    }

    JSC::JSValue value = callFrame->argument(0);
    JSC::JSValue options = callFrame->argument(1);

    Vector<JSC::Strong<JSC::JSObject>> transferList;

    if (options.isObject()) {
        JSC::JSObject* optionsObject = options.getObject();
        JSC::JSValue transferListValue = optionsObject->get(globalObject, vm.propertyNames->transfer);
        RETURN_IF_EXCEPTION(throwScope, {});
        if (transferListValue.isObject()) {
            JSC::JSObject* transferListObject = transferListValue.getObject();
            if (auto* transferListArray = jsDynamicCast<JSC::JSArray*>(transferListObject)) {
                for (unsigned i = 0; i < transferListArray->length(); i++) {
                    JSC::JSValue transferListValue = transferListArray->get(globalObject, i);
                    RETURN_IF_EXCEPTION(throwScope, {});
                    if (transferListValue.isObject()) {
                        JSC::JSObject* transferListObject = transferListValue.getObject();
                        transferList.append(JSC::Strong<JSC::JSObject>(vm, transferListObject));
                    }
                }
            }
        }
    }

    Vector<RefPtr<MessagePort>> ports;
    ExceptionOr<Ref<SerializedScriptValue>> serialized = SerializedScriptValue::create(*globalObject, value, WTFMove(transferList), ports);
    if (serialized.hasException()) {
        WebCore::propagateException(*globalObject, throwScope, serialized.releaseException());
        RELEASE_AND_RETURN(throwScope, {});
    }
    throwScope.assertNoException();

    JSValue deserialized = serialized.releaseReturnValue()->deserialize(*globalObject, globalObject, ports);
    RETURN_IF_EXCEPTION(throwScope, {});

    return JSValue::encode(deserialized);
}

JSC_DEFINE_HOST_FUNCTION(functionBTOA,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    auto& vm = JSC::getVM(globalObject);
    auto throwScope = DECLARE_THROW_SCOPE(globalObject->vm());

    if (callFrame->argumentCount() == 0) {
        JSC::throwTypeError(globalObject, throwScope, "btoa requires 1 argument (a string)"_s);
        return {};
    }

    JSValue arg0 = callFrame->uncheckedArgument(0);
    WTF::String encodedString = arg0.toWTFString(globalObject);
    RETURN_IF_EXCEPTION(throwScope, JSC::JSValue::encode(JSC::JSValue {}));

    if (encodedString.isEmpty()) {
        return JSC::JSValue::encode(JSC::jsEmptyString(vm));
    }

    if (!encodedString.containsOnlyLatin1()) {
        throwException(globalObject, throwScope, createDOMException(globalObject, InvalidCharacterError));
        return {};
    }

    // Reminder: btoa() is for Byte Strings
    // Specifically: latin1 byte strings
    // That means even though this looks like the wrong thing to do,
    // we should be converting to latin1, not utf8.
    if (!encodedString.is8Bit()) {
        std::span<LChar> ptr;
        unsigned length = encodedString.length();
        auto dest = WTF::String::tryCreateUninitialized(length, ptr);
        if (dest.isNull()) [[unlikely]] {
            throwOutOfMemoryError(globalObject, throwScope);
            return {};
        }
        WTF::StringImpl::copyCharacters(ptr, encodedString.span16());
        encodedString = WTFMove(dest);
    }

    unsigned length = encodedString.length();
    RELEASE_AND_RETURN(
        throwScope,
        Bun__encoding__toString(
            encodedString.span8().data(),
            length,
            globalObject,
            static_cast<uint8_t>(WebCore::BufferEncodingType::base64)));
}

JSC_DEFINE_HOST_FUNCTION(functionATOB,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    auto& vm = JSC::getVM(globalObject);
    auto throwScope = DECLARE_THROW_SCOPE(globalObject->vm());

    if (callFrame->argumentCount() == 0) {
        JSC::throwTypeError(globalObject, throwScope, "atob requires 1 argument (a string)"_s);
        return {};
    }

    WTF::String encodedString = callFrame->uncheckedArgument(0).toWTFString(globalObject);
    RETURN_IF_EXCEPTION(throwScope, JSC::JSValue::encode(JSC::JSValue {}));

    auto result = Bun::Base64::atob(encodedString);
    if (result.hasException()) {
        throwException(globalObject, throwScope, createDOMException(*globalObject, result.releaseException()));
        return {};
    }

    RELEASE_AND_RETURN(throwScope, JSValue::encode(jsString(vm, result.releaseReturnValue())));
}

JSC_DEFINE_HOST_FUNCTION(functionReportError,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    switch (callFrame->argumentCount()) {
    case 0: {
        return JSC::JSValue::encode(JSC::jsUndefined());
    }
    default: {
        Bun__reportError(globalObject, JSC::JSValue::encode(callFrame->argument(0)));
    }
    }

    return JSC::JSValue::encode(JSC::jsUndefined());
}

extern "C" JSC::EncodedJSValue ArrayBuffer__fromSharedMemfd(int64_t fd, JSC::JSGlobalObject* globalObject, size_t byteOffset, size_t byteLength, size_t totalLength, JSC::JSType type)
{

// Windows doesn't have mmap
// This code should pretty much only be called on Linux.
#if !OS(WINDOWS)
    auto ptr = mmap(nullptr, totalLength, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    if (ptr == MAP_FAILED) {
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    auto buffer = ArrayBuffer::createFromBytes({ reinterpret_cast<const uint8_t*>(reinterpret_cast<char*>(ptr) + byteOffset), byteLength }, createSharedTask<void(void*)>([ptr, totalLength](void* p) {
        munmap(ptr, totalLength);
    }));

    if (type == JSC::Uint8ArrayType) {
        auto uint8array = JSC::JSUint8Array::create(globalObject, globalObject->m_typedArrayUint8.get(globalObject), WTFMove(buffer), 0, byteLength);
        return JSValue::encode(uint8array);
    }

    if (type == JSC::ArrayBufferType) {

        Structure* structure = globalObject->arrayBufferStructure(JSC::ArrayBufferSharingMode::Default);

        if (!structure) [[unlikely]] {
            return JSC::JSValue::encode(JSC::JSValue {});
        }

        return JSValue::encode(JSC::JSArrayBuffer::create(globalObject->vm(), structure, WTFMove(buffer)));
    } else {
        RELEASE_ASSERT_NOT_REACHED();
    }
#else
    return JSC::JSValue::encode(JSC::JSValue {});
#endif
}

extern "C" JSC::EncodedJSValue Bun__createArrayBufferForCopy(JSC::JSGlobalObject* globalObject, const void* ptr, size_t len)
{
    auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
    auto arrayBuffer = JSC::ArrayBuffer::tryCreateUninitialized(len, 1);

    if (!arrayBuffer) [[unlikely]] {
        JSC::throwOutOfMemoryError(globalObject, scope);
        return {};
    }

    if (len > 0)
        memcpy(arrayBuffer->data(), ptr, len);

    RELEASE_AND_RETURN(scope, JSValue::encode(JSC::JSArrayBuffer::create(globalObject->vm(), globalObject->arrayBufferStructure(JSC::ArrayBufferSharingMode::Default), WTFMove(arrayBuffer))));
}

extern "C" JSC::EncodedJSValue Bun__allocUint8ArrayForCopy(JSC::JSGlobalObject* globalObject, size_t len, void** ptr)
{
    auto scope = DECLARE_THROW_SCOPE(globalObject->vm());

    JSC::JSUint8Array* array = JSC::JSUint8Array::createUninitialized(globalObject, globalObject->m_typedArrayUint8.get(globalObject), len);
    RETURN_IF_EXCEPTION(scope, {});

    *ptr = array->vector();

    return JSValue::encode(array);
}

extern "C" JSC::EncodedJSValue Bun__allocArrayBufferForCopy(JSC::JSGlobalObject* lexicalGlobalObject, size_t len, void** ptr)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);
    auto* globalObject = defaultGlobalObject(lexicalGlobalObject);

    auto* subclassStructure = globalObject->JSBufferSubclassStructure();
    auto buf = JSC::JSUint8Array::createUninitialized(lexicalGlobalObject, subclassStructure, len);
    RETURN_IF_EXCEPTION(scope, {});

    *ptr = buf->vector();

    return JSValue::encode(buf);
}

extern "C" JSC::EncodedJSValue Bun__createUint8ArrayForCopy(JSC::JSGlobalObject* globalObject, const void* ptr, size_t len, bool isBuffer)
{
    VM& vm = globalObject->vm();
    auto scope = DECLARE_THROW_SCOPE(vm);

    auto* subclassStructure = isBuffer ? static_cast<Zig::GlobalObject*>(globalObject)->JSBufferSubclassStructure() : globalObject->typedArrayStructureWithTypedArrayType<TypeUint8>();
    JSC::JSUint8Array* array = JSC::JSUint8Array::createUninitialized(globalObject, subclassStructure, len);
    RETURN_IF_EXCEPTION(scope, {});

    if (len > 0 && ptr != nullptr)
        memcpy(array->vector(), ptr, len);

    RELEASE_AND_RETURN(scope, JSValue::encode(array));
}

extern "C" JSC::EncodedJSValue Bun__makeArrayBufferWithBytesNoCopy(JSC::JSGlobalObject* globalObject, const void* ptr, size_t len, JSTypedArrayBytesDeallocator deallocator, void* deallocatorContext)
{
    auto& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);

    auto buffer = ArrayBuffer::createFromBytes({ static_cast<const uint8_t*>(ptr), len }, createSharedTask<void(void*)>([=](void* p) {
        if (deallocator) deallocator(p, deallocatorContext);
    }));

    JSArrayBuffer* jsBuffer = JSArrayBuffer::create(vm, globalObject->arrayBufferStructure(ArrayBufferSharingMode::Default), WTFMove(buffer));
    RETURN_IF_EXCEPTION(scope, {});
    return JSValue::encode(jsBuffer);
}

extern "C" JSC::EncodedJSValue Bun__makeTypedArrayWithBytesNoCopy(JSC::JSGlobalObject* globalObject, TypedArrayType ty, const void* ptr, size_t len, JSTypedArrayBytesDeallocator deallocator, void* deallocatorContext)
{
    auto& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);

    auto buffer_ = ArrayBuffer::createFromBytes({ static_cast<const uint8_t*>(ptr), len }, createSharedTask<void(void*)>([=](void* p) {
        if (deallocator) deallocator(p, deallocatorContext);
    }));
    RefPtr<ArrayBuffer>&& buffer = WTFMove(buffer_);
    if (!buffer) {
        throwOutOfMemoryError(globalObject, scope);
        return {};
    }

    unsigned elementByteSize = elementSize(ty);
    size_t offset = 0;
    size_t length = len / elementByteSize;
    bool isResizableOrGrowableShared = buffer->isResizableOrGrowableShared();

    switch (ty) {
#define JSC_TYPED_ARRAY_FACTORY(type) \
    case Type##type:                  \
        RELEASE_AND_RETURN(scope, JSValue::encode(JS##type##Array::create(globalObject, globalObject->typedArrayStructure(Type##type, isResizableOrGrowableShared), WTFMove(buffer), offset, length)));
#undef JSC_TYPED_ARRAY_CHECK
        FOR_EACH_TYPED_ARRAY_TYPE_EXCLUDING_DATA_VIEW(JSC_TYPED_ARRAY_FACTORY)
    case NotTypedArray:
    case TypeDataView:
        ASSERT_NOT_REACHED();
    }

    return {};
}

JSC_DECLARE_HOST_FUNCTION(functionCreateUninitializedArrayBuffer);
JSC_DEFINE_HOST_FUNCTION(functionCreateUninitializedArrayBuffer,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    size_t len = static_cast<size_t>(JSC__JSValue__toInt64(JSC::JSValue::encode(callFrame->argument(0))));
    auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
    auto arrayBuffer = JSC::ArrayBuffer::tryCreateUninitialized(len, 1);

    if (!arrayBuffer) [[unlikely]] {
        JSC::throwOutOfMemoryError(globalObject, scope);
        return {};
    }

    RELEASE_AND_RETURN(scope, JSValue::encode(JSC::JSArrayBuffer::create(globalObject->vm(), globalObject->arrayBufferStructure(JSC::ArrayBufferSharingMode::Default), WTFMove(arrayBuffer))));
}

static inline JSC::EncodedJSValue jsFunctionAddEventListenerBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, Zig::GlobalObject* castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->globalEventScope;
    if (callFrame->argumentCount() < 2) [[unlikely]]
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto type = convert<IDLAtomStringAdaptor<IDLDOMString>>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, {});
    EnsureStillAliveScope argument1 = callFrame->uncheckedArgument(1);
    auto listener = convert<IDLNullable<IDLEventListener<JSEventListener>>>(*lexicalGlobalObject, argument1.value(), *castedThis, [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwArgumentMustBeObjectError(lexicalGlobalObject, scope, 1, "listener"_s, "EventTarget"_s, "addEventListener"_s); });
    RETURN_IF_EXCEPTION(throwScope, {});
    EnsureStillAliveScope argument2 = callFrame->argument(2);
    auto options = argument2.value().isUndefined() ? false : convert<IDLUnion<IDLDictionary<AddEventListenerOptions>, IDLBoolean>>(*lexicalGlobalObject, argument2.value());
    RETURN_IF_EXCEPTION(throwScope, {});
    auto result = JSValue::encode(WebCore::toJS<IDLUndefined>(*lexicalGlobalObject, throwScope, [&]() -> decltype(auto) { return impl->addEventListenerForBindings(WTFMove(type), WTFMove(listener), WTFMove(options)); }));
    RETURN_IF_EXCEPTION(throwScope, {});
    vm.writeBarrier(&static_cast<JSObject&>(*castedThis), argument1.value());
    return result;
}

JSC_DEFINE_HOST_FUNCTION(jsFunctionAddEventListener, (JSGlobalObject * lexicalGlobalObject, CallFrame* callFrame))
{
    return jsFunctionAddEventListenerBody(lexicalGlobalObject, callFrame, jsDynamicCast<Zig::GlobalObject*>(lexicalGlobalObject));
}

static inline JSC::EncodedJSValue jsFunctionRemoveEventListenerBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, Zig::GlobalObject* castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->globalEventScope;
    if (callFrame->argumentCount() < 2) [[unlikely]]
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto type = convert<IDLAtomStringAdaptor<IDLDOMString>>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, {});
    EnsureStillAliveScope argument1 = callFrame->uncheckedArgument(1);
    auto listener = convert<IDLNullable<IDLEventListener<JSEventListener>>>(*lexicalGlobalObject, argument1.value(), *castedThis, [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwArgumentMustBeObjectError(lexicalGlobalObject, scope, 1, "listener"_s, "EventTarget"_s, "removeEventListener"_s); });
    RETURN_IF_EXCEPTION(throwScope, {});
    EnsureStillAliveScope argument2 = callFrame->argument(2);
    auto options = argument2.value().isUndefined() ? false : convert<IDLUnion<IDLDictionary<EventListenerOptions>, IDLBoolean>>(*lexicalGlobalObject, argument2.value());
    RETURN_IF_EXCEPTION(throwScope, {});
    auto result = JSValue::encode(WebCore::toJS<IDLUndefined>(*lexicalGlobalObject, throwScope, [&]() -> decltype(auto) { return impl->removeEventListenerForBindings(WTFMove(type), WTFMove(listener), WTFMove(options)); }));
    RETURN_IF_EXCEPTION(throwScope, {});
    vm.writeBarrier(&static_cast<JSObject&>(*castedThis), argument1.value());
    return result;
}

JSC_DEFINE_HOST_FUNCTION(jsFunctionRemoveEventListener, (JSGlobalObject * lexicalGlobalObject, CallFrame* callFrame))
{
    return jsFunctionRemoveEventListenerBody(lexicalGlobalObject, callFrame, jsDynamicCast<Zig::GlobalObject*>(lexicalGlobalObject));
}

static inline JSC::EncodedJSValue jsFunctionDispatchEventBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, Zig::GlobalObject* castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->globalEventScope;
    if (callFrame->argumentCount() < 1) [[unlikely]]
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto event = convert<IDLInterface<Event>>(*lexicalGlobalObject, argument0.value(), [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwArgumentTypeError(lexicalGlobalObject, scope, 0, "event"_s, "EventTarget"_s, "dispatchEvent"_s, "Event"_s); });
    RETURN_IF_EXCEPTION(throwScope, {});
    RELEASE_AND_RETURN(throwScope, JSValue::encode(WebCore::toJS<IDLBoolean>(*lexicalGlobalObject, throwScope, impl->dispatchEventForBindings(*event))));
}

JSC_DEFINE_HOST_FUNCTION(jsFunctionDispatchEvent, (JSGlobalObject * lexicalGlobalObject, CallFrame* callFrame))
{
    return jsFunctionDispatchEventBody(lexicalGlobalObject, callFrame, jsDynamicCast<Zig::GlobalObject*>(lexicalGlobalObject));
}

JSC_DEFINE_CUSTOM_GETTER(getterSubtleCrypto, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return JSValue::encode(static_cast<Zig::GlobalObject*>(lexicalGlobalObject)->subtleCrypto());
}

extern "C" JSC::EncodedJSValue ExpectMatcherUtils_createSigleton(JSC::JSGlobalObject* lexicalGlobalObject);

// Do nothing.
// This is consistent with Node.js
// This makes libraries polyfilling `globalThis.crypto.subtle` not throw.
JSC_DEFINE_CUSTOM_SETTER(setterSubtleCrypto,
    (JSC::JSGlobalObject*, JSC::EncodedJSValue,
        JSC::EncodedJSValue, JSC::PropertyName))
{
    return true;
}

JSC_DECLARE_HOST_FUNCTION(makeGetterTypeErrorForBuiltins);
JSC_DECLARE_HOST_FUNCTION(makeDOMExceptionForBuiltins);
JSC_DECLARE_HOST_FUNCTION(createWritableStreamFromInternal);
JSC_DECLARE_HOST_FUNCTION(getInternalWritableStream);
JSC_DECLARE_HOST_FUNCTION(isAbortSignal);

JSC_DEFINE_HOST_FUNCTION(makeGetterTypeErrorForBuiltins, (JSGlobalObject * globalObject, CallFrame* callFrame))
{
    ASSERT(callFrame);
    ASSERT(callFrame->argumentCount() == 2);
    VM& vm = globalObject->vm();
    DeferTermination deferScope(vm);
    auto scope = DECLARE_CATCH_SCOPE(vm);

    auto interfaceName = callFrame->uncheckedArgument(0).getString(globalObject);
    scope.assertNoException();
    auto attributeName = callFrame->uncheckedArgument(1).getString(globalObject);
    scope.assertNoException();

    auto error = static_cast<ErrorInstance*>(createTypeError(globalObject, JSC::makeDOMAttributeGetterTypeErrorMessage(interfaceName.utf8().data(), attributeName)));
    error->setNativeGetterTypeError();
    return JSValue::encode(error);
}

JSC_DEFINE_HOST_FUNCTION(makeDOMExceptionForBuiltins, (JSGlobalObject * globalObject, CallFrame* callFrame))
{
    ASSERT(callFrame);
    ASSERT(callFrame->argumentCount() == 2);

    auto& vm = JSC::getVM(globalObject);
    DeferTermination deferScope(vm);
    auto scope = DECLARE_CATCH_SCOPE(vm);

    auto codeValue = callFrame->uncheckedArgument(0).getString(globalObject);
    scope.assertNoException();

    auto message = callFrame->uncheckedArgument(1).getString(globalObject);
    scope.assertNoException();

    ExceptionCode code { TypeError };
    if (codeValue == "AbortError"_s)
        code = AbortError;
    auto value = createDOMException(globalObject, code, message);

    EXCEPTION_ASSERT(!scope.exception() || vm.hasPendingTerminationException());

    return JSValue::encode(value);
}

JSC_DEFINE_HOST_FUNCTION(getInternalWritableStream, (JSGlobalObject*, CallFrame* callFrame))
{
    ASSERT(callFrame);
    ASSERT(callFrame->argumentCount() == 1);

    auto* writableStream = jsDynamicCast<JSWritableStream*>(callFrame->uncheckedArgument(0));
    if (!writableStream) [[unlikely]]
        return JSValue::encode(jsUndefined());
    return JSValue::encode(writableStream->wrapped().internalWritableStream());
}

JSC_DEFINE_HOST_FUNCTION(createWritableStreamFromInternal, (JSGlobalObject * globalObject, CallFrame* callFrame))
{
    ASSERT(callFrame);
    ASSERT(callFrame->argumentCount() == 1);
    ASSERT(callFrame->uncheckedArgument(0).isObject());

    auto* jsDOMGlobalObject = JSC::jsCast<JSDOMGlobalObject*>(globalObject);
    auto internalWritableStream = InternalWritableStream::fromObject(*jsDOMGlobalObject, *callFrame->uncheckedArgument(0).toObject(globalObject));
    return JSValue::encode(toJSNewlyCreated(globalObject, jsDOMGlobalObject, WritableStream::create(WTFMove(internalWritableStream))));
}

JSC_DEFINE_HOST_FUNCTION(addAbortAlgorithmToSignal, (JSGlobalObject * globalObject, CallFrame* callFrame))
{
    ASSERT(callFrame);
    ASSERT(callFrame->argumentCount() == 2);

    auto& vm = JSC::getVM(globalObject);
    auto* abortSignal = jsDynamicCast<JSAbortSignal*>(callFrame->uncheckedArgument(0));
    if (!abortSignal) [[unlikely]]
        return JSValue::encode(JSValue(JSC::JSValue::JSFalse));

    Ref<AbortAlgorithm> abortAlgorithm = JSAbortAlgorithm::create(vm, callFrame->uncheckedArgument(1).getObject());

    auto algorithmIdentifier = AbortSignal::addAbortAlgorithmToSignal(abortSignal->wrapped(), WTFMove(abortAlgorithm));
    return JSValue::encode(JSC::jsNumber(algorithmIdentifier));
}

JSC_DEFINE_HOST_FUNCTION(removeAbortAlgorithmFromSignal, (JSGlobalObject*, CallFrame* callFrame))
{
    ASSERT(callFrame);
    ASSERT(callFrame->argumentCount() == 2);

    auto* abortSignal = jsDynamicCast<JSAbortSignal*>(callFrame->uncheckedArgument(0));
    if (!abortSignal) [[unlikely]]
        return JSValue::encode(JSValue(JSC::JSValue::JSFalse));

    AbortSignal::removeAbortAlgorithmFromSignal(abortSignal->wrapped(), callFrame->uncheckedArgument(1).asUInt32());
    return JSValue::encode(JSC::jsUndefined());
}

JSC_DEFINE_HOST_FUNCTION(isAbortSignal, (JSGlobalObject*, CallFrame* callFrame))
{
    ASSERT(callFrame->argumentCount() == 1);
    return JSValue::encode(jsBoolean(callFrame->uncheckedArgument(0).inherits<JSAbortSignal>()));
}
static inline std::optional<JSC::JSValue> invokeReadableStreamFunction(JSC::JSGlobalObject* lexicalGlobalObject, const JSC::Identifier& identifier, JSC::JSValue thisValue, const JSC::MarkedArgumentBuffer& arguments)
{
    JSC::VM& vm = lexicalGlobalObject->vm();
    auto scope = DECLARE_THROW_SCOPE(vm);
    JSC::JSLockHolder lock(vm);

    auto function = lexicalGlobalObject->get(lexicalGlobalObject, identifier);
    scope.assertNoExceptionExceptTermination();
    if (scope.exception()) [[unlikely]]
        return {};
    ASSERT(function.isCallable());

    auto callData = JSC::getCallData(function);
    auto result = JSC::call(lexicalGlobalObject, function, callData, thisValue, arguments);
#if ASSERT_ENABLED
    if (scope.exception()) [[unlikely]] {
        Bun__reportError(lexicalGlobalObject, JSValue::encode(scope.exception()));
    }
#endif
    EXCEPTION_ASSERT(!scope.exception() || vm.hasPendingTerminationException());
    RETURN_IF_EXCEPTION(scope, {});
    return result;
}
extern "C" bool ReadableStream__tee(JSC::EncodedJSValue possibleReadableStream, Zig::GlobalObject* globalObject, JSC::EncodedJSValue* possibleReadableStream1, JSC::EncodedJSValue* possibleReadableStream2)
{
    auto* readableStream = jsDynamicCast<JSReadableStream*>(JSC::JSValue::decode(possibleReadableStream));
    if (!readableStream) [[unlikely]]
        return false;

    auto lexicalGlobalObject = globalObject;
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto* clientData = static_cast<JSVMClientData*>(vm.clientData);
    auto& privateName = clientData->builtinFunctions().readableStreamInternalsBuiltins().readableStreamTeePrivateName();
    auto scope = DECLARE_THROW_SCOPE(vm);

    MarkedArgumentBuffer arguments;
    arguments.append(readableStream);
    arguments.append(JSC::jsBoolean(true));
    ASSERT(!arguments.hasOverflowed());
    auto returnedValue = invokeReadableStreamFunction(lexicalGlobalObject, privateName, JSC::jsUndefined(), arguments);
    RETURN_IF_EXCEPTION(scope, false);
    if (!returnedValue) return false;

    auto results = Detail::SequenceConverter<IDLAny>::convert(*lexicalGlobalObject, *returnedValue);
    RETURN_IF_EXCEPTION(scope, false);

    ASSERT(results.size() == 2);
    *possibleReadableStream1 = JSValue::encode(results[0]);
    *possibleReadableStream2 = JSValue::encode(results[1]);
    return true;
}

extern "C" void ReadableStream__cancel(JSC::EncodedJSValue possibleReadableStream, Zig::GlobalObject* globalObject)
{
    auto* readableStream = jsDynamicCast<JSReadableStream*>(JSC::JSValue::decode(possibleReadableStream));
    if (!readableStream) [[unlikely]]
        return;

    if (!ReadableStream::isLocked(globalObject, readableStream)) {
        return;
    }

    WebCore::Exception exception { AbortError };
    ReadableStream::cancel(*globalObject, readableStream, exception);
}

extern "C" void ReadableStream__detach(JSC::EncodedJSValue possibleReadableStream, Zig::GlobalObject* globalObject)
{
    auto value = JSC::JSValue::decode(possibleReadableStream);
    if (value.isEmpty() || !value.isCell())
        return;

    auto* readableStream = static_cast<JSReadableStream*>(value.asCell());
    if (!readableStream) [[unlikely]]
        return;
    readableStream->setNativePtr(globalObject->vm(), jsNumber(-1));
    readableStream->setNativeType(0);
    readableStream->setDisturbed(true);
}
extern "C" bool ReadableStream__isDisturbed(JSC::EncodedJSValue possibleReadableStream, Zig::GlobalObject* globalObject);
extern "C" bool ReadableStream__isDisturbed(JSC::EncodedJSValue possibleReadableStream, Zig::GlobalObject* globalObject)
{
    ASSERT(globalObject);
    return ReadableStream::isDisturbed(globalObject, jsDynamicCast<WebCore::JSReadableStream*>(JSC::JSValue::decode(possibleReadableStream)));
}

extern "C" bool ReadableStream__isLocked(JSC::EncodedJSValue possibleReadableStream, Zig::GlobalObject* globalObject);
extern "C" bool ReadableStream__isLocked(JSC::EncodedJSValue possibleReadableStream, Zig::GlobalObject* globalObject)
{
    ASSERT(globalObject);
    WebCore::JSReadableStream* stream = jsDynamicCast<WebCore::JSReadableStream*>(JSValue::decode(possibleReadableStream));
    return stream != nullptr && ReadableStream::isLocked(globalObject, stream);
}

extern "C" int32_t ReadableStreamTag__tagged(Zig::GlobalObject* globalObject, JSC::EncodedJSValue* possibleReadableStream, void** ptr)
{
    ASSERT(globalObject);
    JSC::JSObject* object = JSValue::decode(*possibleReadableStream).getObject();
    if (!object) {
        *ptr = nullptr;
        return -1;
    }

    auto& vm = JSC::getVM(globalObject);

    if (!object->inherits<JSReadableStream>()) {
        auto throwScope = DECLARE_THROW_SCOPE(vm);
        JSValue target = object;
        JSValue fn = JSValue();
        auto* function = jsDynamicCast<JSC::JSFunction*>(object);
        if (function && !function->isHostFunction() && function->jsExecutable() && function->jsExecutable()->isAsyncGenerator()) {
            fn = object;
            target = jsUndefined();
        } else {
            auto iterable = object->getIfPropertyExists(globalObject, vm.propertyNames->asyncIteratorSymbol);
            RETURN_IF_EXCEPTION(throwScope, {});
            if (iterable && iterable.isCallable()) {
                fn = iterable;
            }
        }

        if (throwScope.exception()) [[unlikely]] {
            *ptr = nullptr;
            return -1;
        }

        if (fn.isEmpty()) {
            *ptr = nullptr;
            return -1;
        }

        auto* createIterator = globalObject->builtinInternalFunctions().readableStreamInternals().m_readableStreamFromAsyncIteratorFunction.get();

        JSC::MarkedArgumentBuffer arguments;
        arguments.append(target);
        arguments.append(fn);

        JSC::JSValue result = profiledCall(globalObject, JSC::ProfilingReason::API, createIterator, JSC::getCallData(createIterator), JSC::jsUndefined(), arguments);

        if (throwScope.exception()) [[unlikely]] {
            return -1;
        }

        if (!result.isObject()) {
            *ptr = nullptr;
            return -1;
        }

        object = result.getObject();

        ASSERT(object->inherits<JSReadableStream>());
        *possibleReadableStream = JSValue::encode(object);
        *ptr = nullptr;
        ensureStillAliveHere(object);
        return 0;
    }

    auto* readableStream = jsCast<JSReadableStream*>(object);

    JSValue nativePtrHandle = readableStream->nativePtr();
    if (nativePtrHandle.isEmpty() || !nativePtrHandle.isCell()) {
        *ptr = nullptr;
        return 0;
    }

    JSCell* cell = nativePtrHandle.asCell();

    if (auto* casted = jsDynamicCast<JSBlobInternalReadableStreamSource*>(cell)) {
        *ptr = casted->wrapped();
        return 1;
    }

    if (auto* casted = jsDynamicCast<JSFileInternalReadableStreamSource*>(cell)) {
        *ptr = casted->wrapped();
        return 2;
    }

    if (auto* casted = jsDynamicCast<JSBytesInternalReadableStreamSource*>(cell)) {
        *ptr = casted->wrapped();
        return 4;
    }

    return 0;
}

extern "C" JSC::EncodedJSValue ZigGlobalObject__createNativeReadableStream(Zig::GlobalObject* globalObject, JSC::EncodedJSValue nativePtr)
{
    auto& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);

    auto& builtinNames = WebCore::builtinNames(vm);

    auto function = globalObject->getDirect(vm, builtinNames.createNativeReadableStreamPrivateName()).getObject();
    JSC::MarkedArgumentBuffer arguments = JSC::MarkedArgumentBuffer();
    arguments.append(JSValue::decode(nativePtr));

    auto callData = JSC::getCallData(function);
    auto result = call(globalObject, function, callData, JSC::jsUndefined(), arguments);
    EXCEPTION_ASSERT(!!scope.exception() == !result);
    return JSValue::encode(result);
}

extern "C" JSC::EncodedJSValue Bun__Jest__createTestModuleObject(JSC::JSGlobalObject*);
extern "C" JSC::EncodedJSValue Bun__Jest__createTestPreloadObject(JSC::JSGlobalObject*);
extern "C" JSC::EncodedJSValue Bun__Jest__testPreloadObject(Zig::GlobalObject* globalObject)
{
    return JSValue::encode(globalObject->lazyPreloadTestModuleObject());
}
extern "C" JSC::EncodedJSValue Bun__Jest__testModuleObject(Zig::GlobalObject* globalObject)
{
    return JSValue::encode(globalObject->lazyTestModuleObject());
}

static inline JSC::EncodedJSValue ZigGlobalObject__readableStreamToArrayBufferBody(Zig::GlobalObject* globalObject, JSC::EncodedJSValue readableStreamValue)
{
    auto& vm = JSC::getVM(globalObject);

    auto throwScope = DECLARE_THROW_SCOPE(vm);

    auto* function = globalObject->m_readableStreamToArrayBuffer.get();
    if (!function) {
        function = JSFunction::create(vm, globalObject, static_cast<JSC::FunctionExecutable*>(readableStreamReadableStreamToArrayBufferCodeGenerator(vm)), globalObject);
        globalObject->m_readableStreamToArrayBuffer.set(vm, globalObject, function);
    }

    JSC::MarkedArgumentBuffer arguments = JSC::MarkedArgumentBuffer();
    arguments.append(JSValue::decode(readableStreamValue));

    auto callData = JSC::getCallData(function);
    JSValue result = call(globalObject, function, callData, JSC::jsUndefined(), arguments);

    JSC::JSObject* object = result.getObject();

    if (!result || result.isUndefinedOrNull()) [[unlikely]]
        return JSValue::encode(result);

    if (!object) [[unlikely]] {
        auto throwScope = DECLARE_THROW_SCOPE(vm);
        throwTypeError(globalObject, throwScope, "Expected object"_s);
        return {};
    }

    JSC::JSPromise* promise = JSC::jsDynamicCast<JSC::JSPromise*>(object);
    if (!promise) [[unlikely]] {
        auto throwScope = DECLARE_THROW_SCOPE(vm);
        throwTypeError(globalObject, throwScope, "Expected promise"_s);
        return {};
    }

    RELEASE_AND_RETURN(throwScope, JSC::JSValue::encode(promise));
}

extern "C" JSC::EncodedJSValue ZigGlobalObject__readableStreamToArrayBuffer(Zig::GlobalObject* globalObject, JSC::EncodedJSValue readableStreamValue)
{
    return ZigGlobalObject__readableStreamToArrayBufferBody(static_cast<Zig::GlobalObject*>(globalObject), readableStreamValue);
}

extern "C" JSC::EncodedJSValue ZigGlobalObject__readableStreamToBytes(Zig::GlobalObject* globalObject, JSC::EncodedJSValue readableStreamValue)
{
    auto& vm = JSC::getVM(globalObject);

    auto throwScope = DECLARE_THROW_SCOPE(vm);

    auto* function = globalObject->m_readableStreamToBytes.get();
    if (!function) {
        function = JSFunction::create(vm, globalObject, static_cast<JSC::FunctionExecutable*>(readableStreamReadableStreamToBytesCodeGenerator(vm)), globalObject);
        globalObject->m_readableStreamToBytes.set(vm, globalObject, function);
    }

    JSC::MarkedArgumentBuffer arguments = JSC::MarkedArgumentBuffer();
    arguments.append(JSValue::decode(readableStreamValue));

    auto callData = JSC::getCallData(function);
    JSValue result = call(globalObject, function, callData, JSC::jsUndefined(), arguments);

    JSC::JSObject* object = result.getObject();

    if (!result || result.isUndefinedOrNull()) [[unlikely]]
        return JSValue::encode(result);

    if (!object) [[unlikely]] {
        auto throwScope = DECLARE_THROW_SCOPE(vm);
        throwTypeError(globalObject, throwScope, "Expected object"_s);
        return {};
    }

    JSC::JSPromise* promise = JSC::jsDynamicCast<JSC::JSPromise*>(object);
    if (!promise) [[unlikely]] {
        auto throwScope = DECLARE_THROW_SCOPE(vm);
        throwTypeError(globalObject, throwScope, "Expected promise"_s);
        return {};
    }

    RELEASE_AND_RETURN(throwScope, JSC::JSValue::encode(promise));
}

extern "C" JSC::EncodedJSValue ZigGlobalObject__readableStreamToText(Zig::GlobalObject* globalObject, JSC::EncodedJSValue readableStreamValue)
{
    auto& vm = JSC::getVM(globalObject);

    JSC::JSFunction* function = nullptr;
    if (auto readableStreamToText = globalObject->m_readableStreamToText.get()) {
        function = readableStreamToText;
    } else {
        function = JSFunction::create(vm, globalObject, static_cast<JSC::FunctionExecutable*>(readableStreamReadableStreamToTextCodeGenerator(vm)), globalObject);

        globalObject->m_readableStreamToText.set(vm, globalObject, function);
    }

    JSC::MarkedArgumentBuffer arguments = JSC::MarkedArgumentBuffer();
    arguments.append(JSValue::decode(readableStreamValue));

    auto callData = JSC::getCallData(function);
    return JSC::JSValue::encode(call(globalObject, function, callData, JSC::jsUndefined(), arguments));
}

extern "C" JSC::EncodedJSValue ZigGlobalObject__readableStreamToFormData(Zig::GlobalObject* globalObject, JSC::EncodedJSValue readableStreamValue, JSC::EncodedJSValue contentTypeValue)
{
    auto& vm = JSC::getVM(globalObject);

    JSC::JSFunction* function = nullptr;
    if (auto readableStreamToFormData = globalObject->m_readableStreamToFormData.get()) {
        function = readableStreamToFormData;
    } else {
        function = JSFunction::create(vm, globalObject, static_cast<JSC::FunctionExecutable*>(readableStreamReadableStreamToFormDataCodeGenerator(vm)), globalObject);

        globalObject->m_readableStreamToFormData.set(vm, globalObject, function);
    }

    JSC::MarkedArgumentBuffer arguments = JSC::MarkedArgumentBuffer();
    arguments.append(JSValue::decode(readableStreamValue));
    arguments.append(JSValue::decode(contentTypeValue));

    auto callData = JSC::getCallData(function);
    return JSC::JSValue::encode(call(globalObject, function, callData, JSC::jsUndefined(), arguments));
}

extern "C" JSC::EncodedJSValue ZigGlobalObject__readableStreamToJSON(Zig::GlobalObject* globalObject, JSC::EncodedJSValue readableStreamValue)
{
    auto& vm = JSC::getVM(globalObject);

    JSC::JSFunction* function = nullptr;
    if (auto readableStreamToJSON = globalObject->m_readableStreamToJSON.get()) {
        function = readableStreamToJSON;
    } else {
        function = JSFunction::create(vm, globalObject, static_cast<JSC::FunctionExecutable*>(readableStreamReadableStreamToJSONCodeGenerator(vm)), globalObject);

        globalObject->m_readableStreamToJSON.set(vm, globalObject, function);
    }

    JSC::MarkedArgumentBuffer arguments = JSC::MarkedArgumentBuffer();
    arguments.append(JSValue::decode(readableStreamValue));

    auto callData = JSC::getCallData(function);
    return JSC::JSValue::encode(call(globalObject, function, callData, JSC::jsUndefined(), arguments));
}

extern "C" JSC::EncodedJSValue ZigGlobalObject__readableStreamToBlob(Zig::GlobalObject* globalObject, JSC::EncodedJSValue readableStreamValue)
{
    auto& vm = JSC::getVM(globalObject);

    JSC::JSFunction* function = nullptr;
    if (auto readableStreamToBlob = globalObject->m_readableStreamToBlob.get()) {
        function = readableStreamToBlob;
    } else {
        function = JSFunction::create(vm, globalObject, static_cast<JSC::FunctionExecutable*>(readableStreamReadableStreamToBlobCodeGenerator(vm)), globalObject);

        globalObject->m_readableStreamToBlob.set(vm, globalObject, function);
    }

    JSC::MarkedArgumentBuffer arguments = JSC::MarkedArgumentBuffer();
    arguments.append(JSValue::decode(readableStreamValue));

    auto callData = JSC::getCallData(function);
    return JSC::JSValue::encode(call(globalObject, function, callData, JSC::jsUndefined(), arguments));
}

extern "C" napi_env ZigGlobalObject__makeNapiEnvForFFI(Zig::GlobalObject* globalObject)
{
    return globalObject->makeNapiEnvForFFI();
}

JSC_DECLARE_HOST_FUNCTION(functionReadableStreamToArrayBuffer);
JSC_DEFINE_HOST_FUNCTION(functionReadableStreamToArrayBuffer, (JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    auto& vm = JSC::getVM(globalObject);

    if (callFrame->argumentCount() < 1) [[unlikely]] {
        auto throwScope = DECLARE_THROW_SCOPE(vm);
        throwTypeError(globalObject, throwScope, "Expected at least one argument"_s);
        return {};
    }

    auto readableStreamValue = callFrame->uncheckedArgument(0);
    return ZigGlobalObject__readableStreamToArrayBufferBody(static_cast<Zig::GlobalObject*>(globalObject), JSValue::encode(readableStreamValue));
}

JSC_DECLARE_HOST_FUNCTION(functionReadableStreamToBytes);
JSC_DEFINE_HOST_FUNCTION(functionReadableStreamToBytes, (JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    auto& vm = JSC::getVM(globalObject);

    if (callFrame->argumentCount() < 1) [[unlikely]] {
        auto throwScope = DECLARE_THROW_SCOPE(vm);
        throwTypeError(globalObject, throwScope, "Expected at least one argument"_s);
        return {};
    }

    auto readableStreamValue = callFrame->uncheckedArgument(0);
    return ZigGlobalObject__readableStreamToBytes(static_cast<Zig::GlobalObject*>(globalObject), JSValue::encode(readableStreamValue));
}

JSC_DEFINE_HOST_FUNCTION(jsFunctionPerformMicrotask, (JSGlobalObject * globalObject, CallFrame* callframe))
{
    auto& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_CATCH_SCOPE(vm);

    auto job = callframe->argument(0);
    if (!job || job.isUndefinedOrNull()) [[unlikely]] {
        return JSValue::encode(jsUndefined());
    }

    auto callData = JSC::getCallData(job);
    MarkedArgumentBuffer arguments;

    if (callData.type == CallData::Type::None) [[unlikely]] {
        return JSValue::encode(jsUndefined());
    }

    JSValue result;
    WTF::NakedPtr<JSC::Exception> exceptionPtr;

    JSValue restoreAsyncContext = {};
    InternalFieldTuple* asyncContextData = nullptr;
    auto setAsyncContext = callframe->argument(1);
    if (!setAsyncContext.isUndefined()) {
        asyncContextData = globalObject->m_asyncContextData.get();
        restoreAsyncContext = asyncContextData->getInternalField(0);
        asyncContextData->putInternalField(vm, 0, setAsyncContext);
    }

    size_t argCount = callframe->argumentCount();
    switch (argCount) {
    case 3: {
        arguments.append(callframe->uncheckedArgument(2));
        break;
    }
    case 4: {
        arguments.append(callframe->uncheckedArgument(2));
        arguments.append(callframe->uncheckedArgument(3));
        break;
    }
    default:
        break;
    }

    JSC::profiledCall(globalObject, ProfilingReason::API, job, callData, jsUndefined(), arguments, exceptionPtr);

    if (asyncContextData) {
        asyncContextData->putInternalField(vm, 0, restoreAsyncContext);
    }

    if (auto* exception = exceptionPtr.get()) {
        Bun__reportUnhandledError(globalObject, JSValue::encode(exception));
    }

    return JSValue::encode(jsUndefined());
}

JSC_DEFINE_HOST_FUNCTION(jsFunctionPerformMicrotaskVariadic, (JSGlobalObject * globalObject, CallFrame* callframe))
{
    auto& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_CATCH_SCOPE(vm);

    auto job = callframe->argument(0);
    if (!job || job.isUndefinedOrNull()) {
        return JSValue::encode(jsUndefined());
    }

    auto callData = JSC::getCallData(job);
    MarkedArgumentBuffer arguments;
    if (callData.type == CallData::Type::None) [[unlikely]] {
        return JSValue::encode(jsUndefined());
    }

    JSArray* array = jsCast<JSArray*>(callframe->argument(1));
    unsigned length = array->length();
    for (unsigned i = 0; i < length; i++) {
        arguments.append(array->getIndex(globalObject, i));
    }

    JSValue result;
    WTF::NakedPtr<JSC::Exception> exceptionPtr;
    JSValue thisValue = jsUndefined();

    if (callframe->argumentCount() > 3) {
        thisValue = callframe->argument(3);
    }

    JSValue restoreAsyncContext = {};
    InternalFieldTuple* asyncContextData = nullptr;
    auto setAsyncContext = callframe->argument(2);
    if (!setAsyncContext.isUndefined()) {
        asyncContextData = globalObject->m_asyncContextData.get();
        restoreAsyncContext = asyncContextData->getInternalField(0);
        asyncContextData->putInternalField(vm, 0, setAsyncContext);
    }

    JSC::profiledCall(globalObject, ProfilingReason::API, job, callData, thisValue, arguments, exceptionPtr);

    if (asyncContextData) {
        asyncContextData->putInternalField(vm, 0, restoreAsyncContext);
    }

    if (auto* exception = exceptionPtr.get()) {
        Bun__reportUnhandledError(globalObject, JSValue::encode(exception));
    }

    return JSValue::encode(jsUndefined());
}

void GlobalObject::createCallSitesFromFrames(Zig::GlobalObject* globalObject, JSC::JSGlobalObject* lexicalGlobalObject, JSCStackTrace& stackTrace, MarkedArgumentBuffer& callSites)
{
    /* From v8's "Stack Trace API" (https://github.com/v8/v8/wiki/Stack-Trace-API):
     * "To maintain restrictions imposed on strict mode functions, frames that have a
     * strict mode function and all frames below (its caller etc.) are not allow to access
     * their receiver and function objects. For those frames, getFunction() and getThis()
     * will return undefined."." */
    bool encounteredStrictFrame = false;

    // TODO: is it safe to use CallSite structure from a different JSGlobalObject? This case would happen within a node:vm
    JSC::Structure* callSiteStructure = globalObject->callSiteStructure();
    size_t framesCount = stackTrace.size();

    for (size_t i = 0; i < framesCount; i++) {
        CallSite* callSite = CallSite::create(lexicalGlobalObject, callSiteStructure, stackTrace.at(i), encounteredStrictFrame);

        if (!encounteredStrictFrame) {
            encounteredStrictFrame = callSite->isStrict();
        }

        callSites.append(callSite);
    }
}

JSC_DEFINE_HOST_FUNCTION(errorConstructorFuncAppendStackTrace, (JSC::JSGlobalObject * lexicalGlobalObject, JSC::CallFrame* callFrame))
{
    GlobalObject* globalObject = static_cast<GlobalObject*>(lexicalGlobalObject);
    auto& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);

    JSC::ErrorInstance* source = jsDynamicCast<JSC::ErrorInstance*>(callFrame->argument(0));
    JSC::ErrorInstance* destination = jsDynamicCast<JSC::ErrorInstance*>(callFrame->argument(1));

    if (!source || !destination) {
        throwTypeError(lexicalGlobalObject, scope, "First & second argument must be an Error object"_s);
        return {};
    }

    if (!destination->stackTrace()) {
        destination->captureStackTrace(vm, globalObject, 1);
    }

    if (source->stackTrace()) {
        destination->stackTrace()->appendVector(*source->stackTrace());
        source->stackTrace()->clear();
    }

    return JSC::JSValue::encode(jsUndefined());
}

JSC_DEFINE_HOST_FUNCTION(jsFunctionDefaultErrorPrepareStackTrace, (JSGlobalObject * lexicalGlobalObject, CallFrame* callFrame))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);
    auto* globalObject = defaultGlobalObject(lexicalGlobalObject);

    auto errorObject = jsDynamicCast<JSC::ErrorInstance*>(callFrame->argument(0));
    auto callSites = jsDynamicCast<JSC::JSArray*>(callFrame->argument(1));
    if (!errorObject) {
        throwTypeError(lexicalGlobalObject, scope, "First argument must be an Error object"_s);
        return {};
    }

    JSValue result = formatStackTraceToJSValue(vm, globalObject, lexicalGlobalObject, errorObject, callSites, jsUndefined());

    RETURN_IF_EXCEPTION(scope, {});

    return JSC::JSValue::encode(result);
}

JSC_DEFINE_CUSTOM_GETTER(errorInstanceLazyStackCustomGetter, (JSGlobalObject * globalObject, JSC::EncodedJSValue thisValue, PropertyName))
{
    auto& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);
    auto* errorObject = jsDynamicCast<ErrorInstance*>(JSValue::decode(thisValue));

    // This shouldn't be possible.
    if (!errorObject) {
        return JSValue::encode(jsUndefined());
    }

    OrdinalNumber line;
    OrdinalNumber column;
    String sourceURL;
    auto stackTrace = errorObject->stackTrace();
    if (stackTrace == nullptr) {
        return JSValue::encode(jsUndefined());
    }

    JSValue result = computeErrorInfoToJSValue(vm, *stackTrace, line, column, sourceURL, errorObject);
    stackTrace->clear();
    errorObject->setStackFrames(vm, {});
    RETURN_IF_EXCEPTION(scope, {});
    errorObject->putDirect(vm, vm.propertyNames->stack, result, 0);
    return JSValue::encode(result);
}

JSC_DEFINE_CUSTOM_SETTER(errorInstanceLazyStackCustomSetter, (JSGlobalObject * globalObject, JSC::EncodedJSValue thisValue, JSC::EncodedJSValue value, PropertyName))
{
    auto& vm = JSC::getVM(globalObject);
    JSValue decodedValue = JSValue::decode(thisValue);
    if (auto* object = decodedValue.getObject()) {
        object->putDirect(vm, vm.propertyNames->stack, JSValue::decode(value), 0);
    }

    return true;
}

JSC_DEFINE_HOST_FUNCTION(errorConstructorFuncCaptureStackTrace, (JSC::JSGlobalObject * lexicalGlobalObject, JSC::CallFrame* callFrame))
{
    GlobalObject* globalObject = static_cast<GlobalObject*>(lexicalGlobalObject);
    auto& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);

    JSC::JSValue objectArg = callFrame->argument(0);
    if (!objectArg.isObject()) {
        return JSC::JSValue::encode(throwTypeError(lexicalGlobalObject, scope, "invalid_argument"_s));
    }

    JSC::JSObject* errorObject = objectArg.asCell()->getObject();
    JSC::JSValue caller = callFrame->argument(1);

    size_t stackTraceLimit = globalObject->stackTraceLimit().value();
    if (stackTraceLimit == 0) {
        stackTraceLimit = DEFAULT_ERROR_STACK_TRACE_LIMIT;
    }

    WTF::Vector<JSC::StackFrame> stackTrace;
    JSCStackTrace::getFramesForCaller(vm, callFrame, errorObject, caller, stackTrace, stackTraceLimit);

    if (auto* instance = jsDynamicCast<JSC::ErrorInstance*>(errorObject)) {
        instance->setStackFrames(vm, WTFMove(stackTrace));
        if (instance->hasMaterializedErrorInfo()) {
            const auto& propertyName = vm.propertyNames->stack;
            VM::DeletePropertyModeScope scope(vm, VM::DeletePropertyMode::IgnoreConfigurable);
            DeletePropertySlot slot;
            JSObject::deleteProperty(instance, globalObject, propertyName, slot);
            if (auto* zigGlobalObject = jsDynamicCast<Zig::GlobalObject*>(globalObject)) {
                instance->putDirectCustomAccessor(vm, vm.propertyNames->stack, zigGlobalObject->m_lazyStackCustomGetterSetter.get(zigGlobalObject), JSC::PropertyAttribute::CustomAccessor | 0);
            } else {
                instance->putDirectCustomAccessor(vm, vm.propertyNames->stack, CustomGetterSetter::create(vm, errorInstanceLazyStackCustomGetter, errorInstanceLazyStackCustomSetter), JSC::PropertyAttribute::CustomAccessor | 0);
            }
        }
    } else {
        OrdinalNumber line;
        OrdinalNumber column;
        String sourceURL;
        JSValue result = computeErrorInfoToJSValue(vm, stackTrace, line, column, sourceURL, errorObject);
        RETURN_IF_EXCEPTION(scope, {});
        errorObject->putDirect(vm, vm.propertyNames->stack, result, 0);
    }

    return JSC::JSValue::encode(JSC::jsUndefined());
}

extern "C" JSC::EncodedJSValue CryptoObject__create(JSGlobalObject*);
JSC_DEFINE_CUSTOM_GETTER(moduleNamespacePrototypeGetESModuleMarker, (JSGlobalObject * globalObject, JSC::EncodedJSValue encodedThisValue, PropertyName))
{
    JSValue thisValue = JSValue::decode(encodedThisValue);
    JSModuleNamespaceObject* moduleNamespaceObject = jsDynamicCast<JSModuleNamespaceObject*>(thisValue);
    if (!moduleNamespaceObject || moduleNamespaceObject->m_hasESModuleMarker != WTF::TriState::True) {
        return JSC::JSValue::encode(jsUndefined());
    }

    return JSC::JSValue::encode(jsBoolean(true));
}

JSC_DEFINE_CUSTOM_SETTER(moduleNamespacePrototypeSetESModuleMarker, (JSGlobalObject * globalObject, JSC::EncodedJSValue encodedThisValue, JSC::EncodedJSValue encodedValue, PropertyName))
{
    auto& vm = JSC::getVM(globalObject);
    JSValue thisValue = JSValue::decode(encodedThisValue);
    JSModuleNamespaceObject* moduleNamespaceObject = jsDynamicCast<JSModuleNamespaceObject*>(thisValue);
    if (!moduleNamespaceObject) {
        return false;
    }
    auto scope = DECLARE_THROW_SCOPE(vm);
    JSValue value = JSValue::decode(encodedValue);
    WTF::TriState triState = value.toBoolean(globalObject) ? WTF::TriState::True : WTF::TriState::False;
    moduleNamespaceObject->m_hasESModuleMarker = triState;
    return true;
}

void GlobalObject::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(info()));

    m_commonStrings.initialize();
    m_http2CommonStrings.initialize();

    Bun::addNodeModuleConstructorProperties(vm, this);
    m_JSNodeHTTPServerSocketStructure.initLater(
        [](const Initializer<Structure>& init) {
            init.set(Bun::createNodeHTTPServerSocketStructure(init.vm, init.owner));
        });

    m_JSDirentClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            Bun::initJSDirentClassStructure(init);
        });

    m_JSX509CertificateClassStructure.initLater([](LazyClassStructure::Initializer& init) {
        setupX509CertificateClassStructure(init);
    });

    m_JSSignClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            setupJSSignClassStructure(init);
        });

    m_JSVerifyClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            setupJSVerifyClassStructure(init);
        });

    m_JSDiffieHellmanClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            Bun::setupDiffieHellmanClassStructure(init);
        });

    m_JSDiffieHellmanGroupClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            Bun::setupDiffieHellmanGroupClassStructure(init);
        });

    m_JSECDHClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            Bun::setupECDHClassStructure(init);
        });

    m_JSHmacClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            setupJSHmacClassStructure(init);
        });

    m_JSHashClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            setupJSHashClassStructure(init);
        });

    m_JSCipherClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            setupCipherClassStructure(init);
        });

    m_JSKeyObjectClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            setupKeyObjectClassStructure(init);
        });

    m_JSSecretKeyObjectClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            setupSecretKeyObjectClassStructure(init);
        });

    m_JSPublicKeyObjectClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            setupPublicKeyObjectClassStructure(init);
        });

    m_JSPrivateKeyObjectClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            setupPrivateKeyObjectClassStructure(init);
        });

    m_JSMIMEParamsClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            WebCore::setupJSMIMEParamsClassStructure(init);
        });

    m_JSMIMETypeClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            WebCore::setupJSMIMETypeClassStructure(init);
        });

    m_JSConnectionsListClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            setupConnectionsListClassStructure(init);
        });

    m_JSHTTPParserClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            setupHTTPParserClassStructure(init);
        });

    m_JSNodePerformanceHooksHistogramClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            Bun::setupJSNodePerformanceHooksHistogramClassStructure(init);
        });

    m_lazyStackCustomGetterSetter.initLater(
        [](const Initializer<CustomGetterSetter>& init) {
            init.set(CustomGetterSetter::create(init.vm, errorInstanceLazyStackCustomGetter, errorInstanceLazyStackCustomSetter));
        });

    m_JSDOMFileConstructor.initLater(
        [](const Initializer<JSObject>& init) {
            JSObject* fileConstructor = Bun::createJSDOMFileConstructor(init.vm, init.owner);
            init.set(fileConstructor);
        });

    m_cryptoObject.initLater(
        [](const Initializer<JSObject>& init) {
            JSC::JSGlobalObject* globalObject = init.owner;
            JSObject* crypto = JSValue::decode(CryptoObject__create(globalObject)).getObject();
            crypto->putDirectCustomAccessor(
                init.vm,
                Identifier::fromString(init.vm, "subtle"_s),
                JSC::CustomGetterSetter::create(init.vm, getterSubtleCrypto, setterSubtleCrypto),
                PropertyAttribute::DontDelete | 0);

            init.set(crypto);
        });

    m_lazyTestModuleObject.initLater(
        [](const Initializer<JSObject>& init) {
            JSC::JSGlobalObject* globalObject = init.owner;

            JSValue result = JSValue::decode(Bun__Jest__createTestModuleObject(globalObject));
            init.set(result.toObject(globalObject));
        });

    m_lazyPreloadTestModuleObject.initLater(
        [](const Initializer<JSObject>& init) {
            JSC::JSGlobalObject* globalObject = init.owner;

            JSValue result = JSValue::decode(Bun__Jest__createTestPreloadObject(globalObject));
            init.set(result.toObject(globalObject));
        });

    m_testMatcherUtilsObject.initLater(
        [](const Initializer<JSObject>& init) {
            JSValue result = JSValue::decode(ExpectMatcherUtils_createSigleton(init.owner));
            init.set(result.toObject(init.owner));
        });

    m_JSS3FileStructure.initLater(
        [](const Initializer<Structure>& init) {
            init.set(Bun::createJSS3FileStructure(init.vm, init.owner));
        });

    m_S3ErrorStructure.initLater(
        [](const Initializer<Structure>& init) {
            init.set(Bun::createS3ErrorStructure(init.vm, init.owner));
        });

    m_commonJSModuleObjectStructure.initLater(
        [](const Initializer<Structure>& init) {
            init.set(Bun::createCommonJSModuleStructure(static_cast<Zig::GlobalObject*>(init.owner)));
        });

    m_JSSocketAddressDTOStructure.initLater(
        [](const Initializer<Structure>& init) {
            init.set(Bun::JSSocketAddressDTO::createStructure(init.vm, init.owner));
        });

    m_JSSQLStatementStructure.initLater(
        [](const Initializer<Structure>& init) {
            init.set(WebCore::createJSSQLStatementStructure(init.owner));
        });

    m_V8GlobalInternals.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, v8::shim::GlobalInternals>::Initializer& init) {
            init.set(
                v8::shim::GlobalInternals::create(
                    init.vm,
                    v8::shim::GlobalInternals::createStructure(init.vm, init.owner),
                    jsDynamicCast<Zig::GlobalObject*>(init.owner)));
        });

    m_JSStatsClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            Bun::initJSStatsClassStructure(init);
        });

    m_JSStatsBigIntClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            Bun::initJSBigIntStatsClassStructure(init);
        });

    m_JSStatFSClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            Bun::initJSStatFSClassStructure(init);
        });

    m_JSStatFSBigIntClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            Bun::initJSBigIntStatFSClassStructure(init);
        });

    m_memoryFootprintStructure.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, Structure>::Initializer& init) {
            init.set(
                createMemoryFootprintStructure(
                    init.vm, static_cast<Zig::GlobalObject*>(init.owner)));
        });

    m_errorConstructorPrepareStackTraceInternalValue.initLater(
        [](const Initializer<JSFunction>& init) {
            init.set(JSFunction::create(init.vm, init.owner, 2, "ErrorPrepareStackTrace"_s, jsFunctionDefaultErrorPrepareStackTrace, ImplementationVisibility::Public));
        });

    // Change prototype from null to object for synthetic modules.
    m_moduleNamespaceObjectStructure.initLater(
        [](const Initializer<Structure>& init) {
            JSObject* moduleNamespacePrototype = JSC::constructEmptyObject(init.owner);
            moduleNamespacePrototype->putDirectCustomAccessor(init.vm, init.vm.propertyNames->__esModule, CustomGetterSetter::create(init.vm, moduleNamespacePrototypeGetESModuleMarker, moduleNamespacePrototypeSetESModuleMarker), PropertyAttribute::DontEnum | PropertyAttribute::DontDelete | PropertyAttribute::CustomAccessor | 0);
            init.set(JSModuleNamespaceObject::createStructure(init.vm, init.owner, moduleNamespacePrototype));
        });

    m_vmModuleContextMap.initLater(
        [](const Initializer<JSWeakMap>& init) {
            init.set(JSWeakMap::create(init.vm, init.owner->weakMapStructure()));
        });

    m_JSBufferSubclassStructure.initLater(
        [](const Initializer<Structure>& init) {
            auto scope = DECLARE_CATCH_SCOPE(init.vm);
            auto* globalObject = static_cast<Zig::GlobalObject*>(init.owner);
            auto* baseStructure = globalObject->typedArrayStructureWithTypedArrayType<JSC::TypeUint8>();
            JSC::Structure* subclassStructure = JSC::InternalFunction::createSubclassStructure(globalObject, globalObject->JSBufferConstructor(), baseStructure);
            scope.assertNoExceptionExceptTermination();
            init.set(subclassStructure);
        });
    m_JSResizableOrGrowableSharedBufferSubclassStructure.initLater(
        [](const Initializer<Structure>& init) {
            auto scope = DECLARE_CATCH_SCOPE(init.vm);
            auto* globalObject = static_cast<Zig::GlobalObject*>(init.owner);
            auto* baseStructure = globalObject->resizableOrGrowableSharedTypedArrayStructureWithTypedArrayType<JSC::TypeUint8>();
            JSC::Structure* subclassStructure = JSC::InternalFunction::createSubclassStructure(globalObject, globalObject->JSBufferConstructor(), baseStructure);
            scope.assertNoExceptionExceptTermination();
            init.set(subclassStructure);
        });
    m_performMicrotaskFunction.initLater(
        [](const Initializer<JSFunction>& init) {
            init.set(JSFunction::create(init.vm, init.owner, 4, "performMicrotask"_s, jsFunctionPerformMicrotask, ImplementationVisibility::Public));
        });

    m_performMicrotaskVariadicFunction.initLater(
        [](const Initializer<JSFunction>& init) {
            init.set(JSFunction::create(init.vm, init.owner, 4, "performMicrotaskVariadic"_s, jsFunctionPerformMicrotaskVariadic, ImplementationVisibility::Public));
        });

    m_utilInspectFunction.initLater(
        [](const Initializer<JSFunction>& init) {
            auto scope = DECLARE_THROW_SCOPE(init.vm);
            JSValue nodeUtilValue = jsCast<Zig::GlobalObject*>(init.owner)->internalModuleRegistry()->requireId(init.owner, init.vm, Bun::InternalModuleRegistry::Field::NodeUtil);
            RETURN_IF_EXCEPTION(scope, );
            RELEASE_ASSERT(nodeUtilValue.isObject());
            auto prop = nodeUtilValue.getObject()->getIfPropertyExists(init.owner, Identifier::fromString(init.vm, "inspect"_s));
            RETURN_IF_EXCEPTION(scope, );
            ASSERT(prop);
            init.set(jsCast<JSFunction*>(prop));
        });

    m_utilInspectOptionsStructure.initLater(
        [](const Initializer<Structure>& init) {
            init.set(Bun::createUtilInspectOptionsStructure(init.vm, init.owner));
        });

    m_nodeErrorCache.initLater(
        [](const Initializer<JSObject>& init) {
            auto* structure = ErrorCodeCache::createStructure(
                init.vm,
                init.owner);

            init.set(ErrorCodeCache::create(init.vm, structure));
        });

    m_utilInspectStylizeColorFunction.initLater(
        [](const Initializer<JSFunction>& init) {
            auto scope = DECLARE_THROW_SCOPE(init.vm);
            JSC::MarkedArgumentBuffer args;
            args.append(jsCast<Zig::GlobalObject*>(init.owner)->utilInspectFunction());
            RETURN_IF_EXCEPTION(scope, );

            JSC::JSFunction* getStylize = JSC::JSFunction::create(init.vm, init.owner, utilInspectGetStylizeWithColorCodeGenerator(init.vm), init.owner);
            RETURN_IF_EXCEPTION(scope, );

            JSC::CallData callData = JSC::getCallData(getStylize);
            NakedPtr<JSC::Exception> returnedException = nullptr;
            auto result = JSC::profiledCall(init.owner, ProfilingReason::API, getStylize, callData, jsNull(), args, returnedException);
            RETURN_IF_EXCEPTION(scope, );

            if (returnedException) {
                throwException(init.owner, scope, returnedException.get());
            }
            RETURN_IF_EXCEPTION(scope, );
            init.set(jsCast<JSFunction*>(result));
        });

    m_utilInspectStylizeNoColorFunction.initLater(
        [](const Initializer<JSFunction>& init) {
            init.set(JSC::JSFunction::create(init.vm, init.owner, utilInspectStylizeWithNoColorCodeGenerator(init.vm), init.owner));
        });

    m_wasmStreamingConsumeStreamFunction.initLater(
        [](const Initializer<JSFunction>& init) {
            init.set(JSC::JSFunction::create(init.vm, init.owner, wasmStreamingConsumeStreamCodeGenerator(init.vm), init.owner));
        });

    m_nativeMicrotaskTrampoline.initLater(
        [](const Initializer<JSFunction>& init) {
            init.set(JSFunction::create(init.vm, init.owner, 2, ""_s, functionNativeMicrotaskTrampoline, ImplementationVisibility::Public));
        });

    m_navigatorObject.initLater(
        [](const Initializer<JSObject>& init) {
            int cpuCount = 0;
#ifdef __APPLE__
            size_t count_len = sizeof(cpuCount);
            sysctlbyname("hw.logicalcpu", &cpuCount, &count_len, NULL, 0);
#elif OS(WINDOWS)
            SYSTEM_INFO sysinfo;
            GetSystemInfo(&sysinfo);
            cpuCount = sysinfo.dwNumberOfProcessors;
#else
            // TODO: windows
            cpuCount = sysconf(_SC_NPROCESSORS_ONLN);
#endif

            auto str = WTF::String::fromUTF8(Bun__userAgent);
            JSC::Identifier userAgentIdentifier = JSC::Identifier::fromString(init.vm, "userAgent"_s);
            JSC::Identifier hardwareConcurrencyIdentifier = JSC::Identifier::fromString(init.vm, "hardwareConcurrency"_s);

            JSC::JSObject* obj = JSC::constructEmptyObject(init.owner, init.owner->objectPrototype(), 4);
            obj->putDirect(init.vm, userAgentIdentifier, JSC::jsString(init.vm, str));
            obj->putDirect(init.vm, init.vm.propertyNames->toStringTagSymbol,
                jsNontrivialString(init.vm, "Navigator"_s), PropertyAttribute::DontEnum | PropertyAttribute::ReadOnly);

// https://developer.mozilla.org/en-US/docs/Web/API/Navigator/platform
// https://github.com/oven-sh/bun/issues/4588
#if OS(DARWIN)
            obj->putDirect(init.vm, JSC::Identifier::fromString(init.vm, "platform"_s), JSC::jsString(init.vm, String("MacIntel"_s)));
#elif OS(WINDOWS)
            obj->putDirect(init.vm, JSC::Identifier::fromString(init.vm, "platform"_s), JSC::jsString(init.vm, String("Win32"_s)));
#elif OS(LINUX)
            obj->putDirect(init.vm, JSC::Identifier::fromString(init.vm, "platform"_s), JSC::jsString(init.vm, String("Linux x86_64"_s)));
#endif

            obj->putDirect(init.vm, hardwareConcurrencyIdentifier, JSC::jsNumber(cpuCount));
            init.set(obj);
        });

    this->m_pendingVirtualModuleResultStructure.initLater(
        [](const Initializer<Structure>& init) {
            init.set(Bun::PendingVirtualModuleResult::createStructure(init.vm, init.owner, init.owner->objectPrototype()));
        });

    m_bunObject.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSObject>::Initializer& init) {
            init.set(Bun::createBunObject(init.vm, init.owner));
        });

    this->initGeneratedLazyClasses();

    m_NapiExternalStructure.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, Structure>::Initializer& init) {
            init.set(
                Bun::NapiExternal::createStructure(init.vm, init.owner, init.owner->objectPrototype()));
        });

    m_NapiPrototypeStructure.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, Structure>::Initializer& init) {
            init.set(
                Bun::NapiPrototype::createStructure(init.vm, init.owner, init.owner->objectPrototype()));
        });

    m_ServerRouteListStructure.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, Structure>::Initializer& init) {
            init.set(Bun::createServerRouteListStructure(init.vm, static_cast<Zig::GlobalObject*>(init.owner)));
        });

    m_JSBunRequestParamsPrototype.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSObject>::Initializer& init) {
            init.set(Bun::createJSBunRequestParamsPrototype(init.vm, static_cast<Zig::GlobalObject*>(init.owner)));
        });

    m_JSBunRequestStructure.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, Structure>::Initializer& init) {
            init.set(Bun::createJSBunRequestStructure(init.vm, static_cast<Zig::GlobalObject*>(init.owner)));
        });

    m_NapiHandleScopeImplStructure.initLater([](const JSC::LazyProperty<JSC::JSGlobalObject, Structure>::Initializer& init) {
        init.set(Bun::NapiHandleScopeImpl::createStructure(init.vm, init.owner));
    });

    m_NapiTypeTagStructure.initLater([](const JSC::LazyProperty<JSC::JSGlobalObject, Structure>::Initializer& init) {
        init.set(Bun::NapiTypeTag::createStructure(init.vm, init.owner));
    });

    m_napiTypeTags.initLater([](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSWeakMap>::Initializer& init) {
        init.set(JSC::JSWeakMap::create(init.vm, init.owner->weakMapStructure()));
    });

    m_cachedGlobalProxyStructure.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, Structure>::Initializer& init) {
            init.set(
                JSC::JSGlobalProxy::createStructure(init.vm, init.owner, JSC::jsNull()));
        });

    m_subtleCryptoObject.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            auto& global = *static_cast<Zig::GlobalObject*>(init.owner);

            if (!global.m_subtleCrypto) {
                global.m_subtleCrypto = &WebCore::SubtleCrypto::create(global.scriptExecutionContext()).leakRef();
            }

            init.set(toJS<IDLInterface<SubtleCrypto>>(*init.owner, global, global.m_subtleCrypto).getObject());
        });

    m_NapiClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            init.setStructure(Zig::NapiClass::createStructure(init.vm, init.global, init.global->functionPrototype()));
        });

    m_JSArrayBufferControllerPrototype.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            auto* prototype = createJSSinkControllerPrototype(init.vm, init.owner, WebCore::SinkID::ArrayBufferSink);
            init.set(prototype);
        });

    m_JSFileSinkControllerPrototype.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            auto* prototype = createJSSinkControllerPrototype(init.vm, init.owner, WebCore::SinkID::FileSink);
            init.set(prototype);
        });

    m_JSHTTPResponseController.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::Structure>::Initializer& init) {
            auto* structure = createJSSinkControllerStructure(init.vm, init.owner, WebCore::SinkID::HTTPResponseSink);
            init.set(structure);
        });

    m_JSHTTPSResponseControllerPrototype.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            auto* prototype = createJSSinkControllerPrototype(init.vm, init.owner, WebCore::SinkID::HTTPSResponseSink);
            init.set(prototype);
        });

    m_JSFetchTaskletChunkedRequestControllerPrototype.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            auto* prototype = createJSSinkControllerPrototype(init.vm, init.owner, WebCore::SinkID::NetworkSink);
            init.set(prototype);
        });

    m_performanceObject.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            auto* globalObject = static_cast<Zig::GlobalObject*>(init.owner);
            init.set(toJS(init.owner, globalObject, globalObject->performance().get()).getObject());
        });

    m_processEnvObject.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            init.set(Bun::createEnvironmentVariablesMap(static_cast<Zig::GlobalObject*>(init.owner)).getObject());
        });

    m_processObject.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, Bun::Process>::Initializer& init) {
            auto* globalObject = defaultGlobalObject(init.owner);

            auto* process = Bun::Process::create(
                *globalObject, Bun::Process::createStructure(init.vm, init.owner, WebCore::JSEventEmitter::prototype(init.vm, *globalObject)));

            init.set(process);
        });

    m_lazyReadableStreamPrototypeMap.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSMap>::Initializer& init) {
            auto* map = JSC::JSMap::create(init.vm, init.owner->mapStructure());
            init.set(map);
        });

    m_requireMap.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSMap>::Initializer& init) {
            auto* map = JSC::JSMap::create(init.vm, init.owner->mapStructure());
            init.set(map);
        });

    m_esmRegistryMap.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSMap>::Initializer& init) {
            auto* global = init.owner;
            auto& vm = init.vm;
            auto scope = DECLARE_THROW_SCOPE(vm);

            // if we get the termination exception, we'd still like to set a non-null Map so that
            // we don't segfault
            auto setEmpty = [&]() {
                ASSERT(scope.exception());
                init.set(JSC::JSMap::create(init.vm, init.owner->mapStructure()));
            };

            JSMap* registry = nullptr;
            auto loaderValue = global->getIfPropertyExists(global, JSC::Identifier::fromString(vm, "Loader"_s));
            scope.assertNoExceptionExceptTermination();
            RETURN_IF_EXCEPTION(scope, setEmpty());
            if (loaderValue) {
                auto registryValue = loaderValue.getObject()->getIfPropertyExists(global, JSC::Identifier::fromString(vm, "registry"_s));
                scope.assertNoExceptionExceptTermination();
                RETURN_IF_EXCEPTION(scope, setEmpty());
                if (registryValue) {
                    registry = jsCast<JSC::JSMap*>(registryValue);
                }
            }

            if (!registry) {
                registry = JSC::JSMap::create(init.vm, init.owner->mapStructure());
            }

            init.set(registry);
        });

    m_requireFunctionUnbound.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            init.set(
                JSFunction::create(
                    init.vm,
                    init.owner,
                    commonJSRequireCodeGenerator(init.vm),
                    init.owner->globalScope(),
                    JSFunction::createStructure(init.vm, init.owner, RequireFunctionPrototype::create(init.owner))));
        });

    m_requireResolveFunctionUnbound.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            init.set(
                JSFunction::create(
                    init.vm,
                    init.owner,
                    commonJSRequireResolveCodeGenerator(init.vm),
                    init.owner->globalScope(),
                    JSFunction::createStructure(init.vm, init.owner, RequireResolveFunctionPrototype::create(init.owner))));
        });

    m_internalModuleRegistry.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, Bun::InternalModuleRegistry>::Initializer& init) {
            init.set(
                InternalModuleRegistry::create(
                    init.vm,
                    InternalModuleRegistry::createStructure(init.vm, init.owner)));
        });

    m_processBindingBuffer.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            init.set(
                ProcessBindingBuffer::create(
                    init.vm,
                    ProcessBindingBuffer::createStructure(init.vm, init.owner)));
        });

    m_processBindingConstants.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            init.set(
                ProcessBindingConstants::create(
                    init.vm,
                    ProcessBindingConstants::createStructure(init.vm, init.owner)));
        });

    m_processBindingFs.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            init.set(
                ProcessBindingFs::create(
                    init.vm,
                    ProcessBindingFs::createStructure(init.vm, init.owner)));
        });

    m_processBindingHTTPParser.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::JSObject>::Initializer& init) {
            init.set(
                ProcessBindingHTTPParser::create(
                    init.vm,
                    ProcessBindingHTTPParser::createStructure(init.vm, init.owner)));
        });

    m_importMetaObjectStructure.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::Structure>::Initializer& init) {
            init.set(Zig::ImportMetaObject::createStructure(init.vm, init.owner));
        });

    m_importMetaBakeObjectStructure.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::Structure>::Initializer& init) {
            init.set(Zig::ImportMetaObject::createStructure(init.vm, init.owner, true));
        });

    m_asyncBoundFunctionStructure.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::Structure>::Initializer& init) {
            init.set(AsyncContextFrame::createStructure(init.vm, init.owner));
        });

    m_JSFileSinkClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            auto* prototype = createJSSinkPrototype(init.vm, init.global, WebCore::SinkID::FileSink);
            auto* structure = JSFileSink::createStructure(init.vm, init.global, prototype);
            auto* constructor = JSFileSinkConstructor::create(init.vm, init.global, JSFileSinkConstructor::createStructure(init.vm, init.global, init.global->functionPrototype()), jsCast<JSObject*>(prototype));
            init.setPrototype(prototype);
            init.setStructure(structure);
            init.setConstructor(constructor);
        });

    m_JSArrayBufferSinkClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            auto* prototype = createJSSinkPrototype(init.vm, init.global, WebCore::SinkID::ArrayBufferSink);
            auto* structure = JSArrayBufferSink::createStructure(init.vm, init.global, prototype);
            auto* constructor = JSArrayBufferSinkConstructor::create(init.vm, init.global, JSArrayBufferSinkConstructor::createStructure(init.vm, init.global, init.global->functionPrototype()), jsCast<JSObject*>(prototype));
            init.setPrototype(prototype);
            init.setStructure(structure);
            init.setConstructor(constructor);
        });

    m_JSHTTPResponseSinkClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            auto* prototype = createJSSinkPrototype(init.vm, init.global, WebCore::SinkID::HTTPResponseSink);
            auto* structure = JSHTTPResponseSink::createStructure(init.vm, init.global, prototype);
            auto* constructor = JSHTTPResponseSinkConstructor::create(init.vm, init.global, JSHTTPResponseSinkConstructor::createStructure(init.vm, init.global, init.global->functionPrototype()), jsCast<JSObject*>(prototype));
            init.setPrototype(prototype);
            init.setStructure(structure);
            init.setConstructor(constructor);
        });

    m_JSNetworkSinkClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            auto* prototype = createJSSinkPrototype(init.vm, init.global, WebCore::SinkID::NetworkSink);
            auto* structure = JSNetworkSink::createStructure(init.vm, init.global, prototype);
            auto* constructor = JSNetworkSinkConstructor::create(init.vm, init.global, JSNetworkSinkConstructor::createStructure(init.vm, init.global, init.global->functionPrototype()), jsCast<JSObject*>(prototype));
            init.setPrototype(prototype);
            init.setStructure(structure);
            init.setConstructor(constructor);
        });

    m_JSBufferClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            auto* prototype = WebCore::createBufferPrototype(init.vm, init.global);
            auto* structure = WebCore::createBufferStructure(init.vm, init.global, JSValue(prototype));
            auto* constructor = WebCore::createBufferConstructor(init.vm, init.global, jsCast<JSObject*>(prototype));
            init.setPrototype(prototype);
            init.setStructure(structure);
            init.setConstructor(constructor);
        });

    m_JSCryptoKey.initLater(
        [](const JSC::LazyProperty<JSC::JSGlobalObject, JSC::Structure>::Initializer& init) {
            Zig::GlobalObject* globalObject = static_cast<Zig::GlobalObject*>(init.owner);
            auto* prototype = JSCryptoKey::createPrototype(init.vm, *globalObject);
            auto* structure = JSCryptoKey::createStructure(init.vm, init.owner, JSValue(prototype));
            init.set(structure);
        });

    m_JSHTTPSResponseSinkClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            auto* prototype = createJSSinkPrototype(init.vm, init.global, WebCore::SinkID::HTTPSResponseSink);
            auto* structure = JSHTTPSResponseSink::createStructure(init.vm, init.global, prototype);
            auto* constructor = JSHTTPSResponseSinkConstructor::create(init.vm, init.global, JSHTTPSResponseSinkConstructor::createStructure(init.vm, init.global, init.global->functionPrototype()), jsCast<JSObject*>(prototype));
            init.setPrototype(prototype);
            init.setStructure(structure);
            init.setConstructor(constructor);
        });

    m_JSFileSinkClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            auto* prototype = createJSSinkPrototype(init.vm, init.global, WebCore::SinkID::FileSink);
            auto* structure = JSFileSink::createStructure(init.vm, init.global, prototype);
            auto* constructor = JSFileSinkConstructor::create(init.vm, init.global, JSFileSinkConstructor::createStructure(init.vm, init.global, init.global->functionPrototype()), jsCast<JSObject*>(prototype));
            init.setPrototype(prototype);
            init.setStructure(structure);
            init.setConstructor(constructor);
        });

    m_JSBufferListClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            auto* prototype = JSBufferListPrototype::create(
                init.vm, init.global, JSBufferListPrototype::createStructure(init.vm, init.global, init.global->objectPrototype()));
            auto* structure = JSBufferList::createStructure(init.vm, init.global, prototype);
            auto* constructor = JSBufferListConstructor::create(
                init.vm, init.global, JSBufferListConstructor::createStructure(init.vm, init.global, init.global->functionPrototype()), prototype);
            init.setPrototype(prototype);
            init.setStructure(structure);
            init.setConstructor(constructor);
        });

    m_callSiteStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            auto* prototype = CallSitePrototype::create(init.vm, CallSitePrototype::createStructure(init.vm, init.global, init.global->objectPrototype()), init.global);
            auto* structure = CallSite::createStructure(init.vm, init.global, prototype);
            init.setPrototype(prototype);
            init.setStructure(structure);
        });

    m_JSStringDecoderClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            auto* prototype = JSStringDecoderPrototype::create(
                init.vm, init.global, JSStringDecoderPrototype::createStructure(init.vm, init.global, init.global->objectPrototype()));
            auto* structure = JSStringDecoder::createStructure(init.vm, init.global, prototype);
            auto* constructor = JSStringDecoderConstructor::create(
                init.vm, init.global, JSStringDecoderConstructor::createStructure(init.vm, init.global, init.global->functionPrototype()), prototype);
            init.setPrototype(prototype);
            init.setStructure(structure);
            init.setConstructor(constructor);
        });

    m_JSFFIFunctionStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            init.setStructure(Zig::JSFFIFunction::createStructure(init.vm, init.global, init.global->functionPrototype()));
        });

    m_statValues.initLater([](const LazyProperty<JSC::JSGlobalObject, JSFloat64Array>::Initializer& init) {
        init.set(JSC::JSFloat64Array::create(init.owner, JSC::JSFloat64Array::createStructure(init.vm, init.owner, init.owner->objectPrototype()), 36));
    });
    m_bigintStatValues.initLater([](const LazyProperty<JSC::JSGlobalObject, JSBigInt64Array>::Initializer& init) {
        init.set(JSC::JSBigInt64Array::create(init.owner, JSC::JSBigInt64Array::createStructure(init.vm, init.owner, init.owner->objectPrototype()), 36));
    });
    m_statFsValues.initLater([](const LazyProperty<JSC::JSGlobalObject, JSFloat64Array>::Initializer& init) {
        init.set(JSC::JSFloat64Array::create(init.owner, JSC::JSFloat64Array::createStructure(init.vm, init.owner, init.owner->objectPrototype()), 7));
    });
    m_bigintStatFsValues.initLater([](const LazyProperty<JSC::JSGlobalObject, JSBigInt64Array>::Initializer& init) {
        init.set(JSC::JSBigInt64Array::create(init.owner, JSC::JSBigInt64Array::createStructure(init.vm, init.owner, init.owner->objectPrototype()), 7));
    });

    configureNodeVM(vm, this);

#if ENABLE(REMOTE_INSPECTOR)
    setInspectable(false);
#endif

    addBuiltinGlobals(vm);

    ASSERT(classInfo());
}

JSC_DEFINE_CUSTOM_GETTER(JSDOMFileConstructor_getter, (JSGlobalObject * globalObject, JSC::EncodedJSValue thisValue, PropertyName))
{
    Zig::GlobalObject* bunGlobalObject = jsCast<Zig::GlobalObject*>(globalObject);
    return JSValue::encode(
        bunGlobalObject->JSDOMFileConstructor());
}

JSC_DEFINE_CUSTOM_SETTER(JSDOMFileConstructor_setter,
    (JSC::JSGlobalObject * globalObject, JSC::EncodedJSValue thisValue,
        JSC::EncodedJSValue value, JSC::PropertyName property))
{
    if (JSValue::decode(thisValue) != globalObject) {
        return false;
    }

    auto& vm = JSC::getVM(globalObject);
    globalObject->putDirect(vm, property, JSValue::decode(value), 0);
    return true;
}

// `console.Console` or `import { Console } from 'console';`
JSC_DEFINE_CUSTOM_GETTER(getConsoleConstructor, (JSGlobalObject * globalObject, EncodedJSValue thisValue, PropertyName property))
{
    auto& vm = JSC::getVM(globalObject);
    auto console = JSValue::decode(thisValue).getObject();
    JSC::JSFunction* createConsoleConstructor = JSC::JSFunction::create(vm, globalObject, consoleObjectCreateConsoleConstructorCodeGenerator(vm), globalObject);
    JSC::MarkedArgumentBuffer args;
    args.append(console);
    JSC::CallData callData = JSC::getCallData(createConsoleConstructor);
    NakedPtr<JSC::Exception> returnedException = nullptr;
    auto result = JSC::profiledCall(globalObject, ProfilingReason::API, createConsoleConstructor, callData, console, args, returnedException);
    if (returnedException) {
        auto scope = DECLARE_THROW_SCOPE(vm);
        throwException(globalObject, scope, returnedException.get());
    }
    console->putDirect(vm, property, result, 0);
    return JSValue::encode(result);
}

// `console._stdout` is equal to `process.stdout`
JSC_DEFINE_CUSTOM_GETTER(getConsoleStdout, (JSGlobalObject * globalObject, EncodedJSValue thisValue, PropertyName property))
{
    auto& vm = JSC::getVM(globalObject);
    auto console = JSValue::decode(thisValue).getObject();
    auto global = jsCast<Zig::GlobalObject*>(globalObject);

    // instead of calling the constructor builtin, go through the process.stdout getter to ensure it's only created once.
    auto stdoutValue = global->processObject()->get(globalObject, Identifier::fromString(vm, "stdout"_s));
    if (!stdoutValue) return {};

    console->putDirect(vm, property, stdoutValue, PropertyAttribute::DontEnum | 0);
    return JSValue::encode(stdoutValue);
}

// `console._stderr` is equal to `process.stderr`
JSC_DEFINE_CUSTOM_GETTER(getConsoleStderr, (JSGlobalObject * globalObject, EncodedJSValue thisValue, PropertyName property))
{
    auto& vm = JSC::getVM(globalObject);
    auto console = JSValue::decode(thisValue).getObject();
    auto global = jsCast<Zig::GlobalObject*>(globalObject);

    // instead of calling the constructor builtin, go through the process.stdout getter to ensure it's only created once.
    auto stderrValue = global->processObject()->get(globalObject, Identifier::fromString(vm, "stderr"_s));
    if (!stderrValue) return {};

    console->putDirect(vm, property, stderrValue, PropertyAttribute::DontEnum | 0);
    return JSValue::encode(stderrValue);
}

JSC_DEFINE_HOST_FUNCTION(jsFunctionToClass, (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    // Mimick the behavior of class Foo {} for a regular JSFunction.
    auto& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);
    auto target = callFrame->argument(0).toObject(globalObject);
    auto name = callFrame->argument(1);
    JSObject* base = callFrame->argument(2).getObject();
    JSObject* prototypeBase = nullptr;
    RETURN_IF_EXCEPTION(scope, encodedJSValue());

    if (!base) {
        base = globalObject->functionPrototype();
    } else {
        auto proto = base->getIfPropertyExists(globalObject, vm.propertyNames->prototype);
        RETURN_IF_EXCEPTION(scope, encodedJSValue());
        if (proto) {
            if (auto protoObject = proto.getObject()) {
                prototypeBase = protoObject;
            }
        } else {
            JSC::throwTypeError(globalObject, scope, "Base class must have a prototype property"_s);
            return encodedJSValue();
        }
    }

    JSObject* prototype = prototypeBase ? JSC::constructEmptyObject(globalObject, prototypeBase) : JSC::constructEmptyObject(globalObject);
    RETURN_IF_EXCEPTION(scope, encodedJSValue());

    prototype->structure()->setMayBePrototype(true);
    prototype->putDirect(vm, vm.propertyNames->constructor, target, PropertyAttribute::DontEnum | 0);

    target->setPrototypeDirect(vm, base);
    target->putDirect(vm, vm.propertyNames->prototype, prototype, PropertyAttribute::DontEnum | 0);
    target->putDirect(vm, vm.propertyNames->name, name, PropertyAttribute::DontEnum | 0);

    return JSValue::encode(jsUndefined());
}

JSC_DEFINE_HOST_FUNCTION(jsFunctionCheckBufferRead, (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    auto& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);

    auto bufVal = callFrame->argument(0);
    auto offsetVal = callFrame->argument(1);
    auto byteLengthVal = callFrame->argument(2);

    ssize_t offset;
    Bun::V::validateInteger(scope, globalObject, offsetVal, "offset"_s, jsUndefined(), jsUndefined(), &offset);
    RETURN_IF_EXCEPTION(scope, {});

    if (!bufVal.isCell()) return Bun::ERR::INVALID_ARG_TYPE(scope, globalObject, "buf"_s, "Buffer"_s, bufVal);
    auto* buf = jsDynamicCast<JSC::JSArrayBufferView*>(bufVal.asCell());
    if (!buf) return Bun::ERR::INVALID_ARG_TYPE(scope, globalObject, "buf"_s, "Buffer"_s, bufVal);
    size_t byteLength = byteLengthVal.asNumber();
    ssize_t type = ((ssize_t)buf->length()) - byteLength;

    if (!(offset >= 0 && offset <= type)) {
        if (std::floor(offset) != offset) {
            Bun::V::validateNumber(scope, globalObject, offsetVal, jsUndefined(), jsUndefined(), jsUndefined());
            RETURN_IF_EXCEPTION(scope, {});
            return Bun::ERR::OUT_OF_RANGE(scope, globalObject, "offset"_s, "an integer"_s, offsetVal);
        }
        if (type < 0) return Bun::ERR::BUFFER_OUT_OF_BOUNDS(scope, globalObject, ""_s);
        return Bun::ERR::OUT_OF_RANGE(scope, globalObject, "offset"_s, makeString(">= 0 and <= "_s, type), offsetVal);
    }
    return JSValue::encode(jsUndefined());
}
extern "C" EncodedJSValue Bun__assignStreamIntoResumableSink(JSC::JSGlobalObject* globalObject, JSC::EncodedJSValue stream, JSC::EncodedJSValue sink)
{
    Zig::GlobalObject* globalThis = reinterpret_cast<Zig::GlobalObject*>(globalObject);
    return globalThis->assignStreamToResumableSink(JSValue::decode(stream), JSValue::decode(sink));
}
EncodedJSValue GlobalObject::assignStreamToResumableSink(JSValue stream, JSValue sink)
{
    auto& vm = this->vm();
    JSC::JSFunction* function = this->m_assignStreamToResumableSink.get();
    if (!function) {
        function = JSFunction::create(vm, this, static_cast<JSC::FunctionExecutable*>(readableStreamInternalsAssignStreamIntoResumableSinkCodeGenerator(vm)), this);
        this->m_assignStreamToResumableSink.set(vm, this, function);
    }

    auto callData = JSC::getCallData(function);
    JSC::MarkedArgumentBuffer arguments;
    arguments.append(stream);
    arguments.append(sink);

    WTF::NakedPtr<JSC::Exception> returnedException = nullptr;

    auto result = JSC::profiledCall(this, ProfilingReason::API, function, callData, JSC::jsUndefined(), arguments, returnedException);
    if (auto* exception = returnedException.get()) {
        return JSC::JSValue::encode(exception);
    }

    return JSC::JSValue::encode(result);
}

EncodedJSValue GlobalObject::assignToStream(JSValue stream, JSValue controller)
{
    auto& vm = this->vm();
    JSC::JSFunction* function = this->m_assignToStream.get();
    if (!function) {
        function = JSFunction::create(vm, this, static_cast<JSC::FunctionExecutable*>(readableStreamInternalsAssignToStreamCodeGenerator(vm)), this);
        this->m_assignToStream.set(vm, this, function);
    }

    auto callData = JSC::getCallData(function);
    JSC::MarkedArgumentBuffer arguments;
    arguments.append(stream);
    arguments.append(controller);

    WTF::NakedPtr<JSC::Exception> returnedException = nullptr;

    auto result = JSC::profiledCall(this, ProfilingReason::API, function, callData, JSC::jsUndefined(), arguments, returnedException);
    if (auto* exception = returnedException.get()) {
        return JSC::JSValue::encode(exception);
    }

    return JSC::JSValue::encode(result);
}

JSC::JSObject* GlobalObject::navigatorObject()
{
    return this->m_navigatorObject.get(this);
}

JSC_DEFINE_CUSTOM_GETTER(functionLazyNavigatorGetter,
    (JSC::JSGlobalObject * globalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    return JSC::JSValue::encode(static_cast<Zig::GlobalObject*>(globalObject)->navigatorObject());
}

JSC::GCClient::IsoSubspace* GlobalObject::subspaceForImpl(JSC::VM& vm)
{
    return WebCore::subspaceForImpl<GlobalObject, WebCore::UseCustomHeapCellType::Yes>(
        vm,
        [](auto& spaces) { return spaces.m_clientSubspaceForWorkerGlobalScope.get(); },
        [](auto& spaces, auto&& space) { spaces.m_clientSubspaceForWorkerGlobalScope = std::forward<decltype(space)>(space); },
        [](auto& spaces) { return spaces.m_subspaceForWorkerGlobalScope.get(); },
        [](auto& spaces, auto&& space) { spaces.m_subspaceForWorkerGlobalScope = std::forward<decltype(space)>(space); },
        [](auto& server) -> JSC::HeapCellType& { return server.m_heapCellTypeForJSWorkerGlobalScope; });
}

BUN_DECLARE_HOST_FUNCTION(WebCore__alert);
BUN_DECLARE_HOST_FUNCTION(WebCore__prompt);
BUN_DECLARE_HOST_FUNCTION(WebCore__confirm);

JSValue GlobalObject_getPerformanceObject(VM& vm, JSObject* globalObject)
{
    return jsCast<Zig::GlobalObject*>(globalObject)->performanceObject();
}

JSValue GlobalObject_getGlobalThis(VM& vm, JSObject* globalObject)
{
    return jsCast<Zig::GlobalObject*>(globalObject)->globalThis();
}

// This is like `putDirectBuiltinFunction` but for the global static list.
#define globalBuiltinFunction(vm, globalObject, identifier, function, attributes) JSC::JSGlobalObject::GlobalPropertyInfo(identifier, JSFunction::create(vm, function, globalObject), attributes)

void GlobalObject::addBuiltinGlobals(JSC::VM& vm)
{
    auto scope = DECLARE_CATCH_SCOPE(vm);
    m_builtinInternalFunctions.initialize(*this);

    auto clientData = WebCore::clientData(vm);
    auto& builtinNames = WebCore::builtinNames(vm);

    // ----- Private/Static Properties -----

    GlobalPropertyInfo staticGlobals[] = {
        GlobalPropertyInfo { builtinNames.startDirectStreamPrivateName(),
            JSC::JSFunction::create(vm, this, 1,
                String(), functionStartDirectStream, ImplementationVisibility::Public),
            PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly | 0 },

        GlobalPropertyInfo { builtinNames.lazyPrivateName(),
            JSC::JSFunction::create(vm, this, 0, "@lazy"_s, JS2Native::jsDollarLazy, ImplementationVisibility::Public),
            PropertyAttribute::ReadOnly | PropertyAttribute::DontEnum | PropertyAttribute::DontDelete | 0 },

        GlobalPropertyInfo(builtinNames.makeGetterTypeErrorPrivateName(), JSFunction::create(vm, this, 2, String(), makeGetterTypeErrorForBuiltins, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.makeDOMExceptionPrivateName(), JSFunction::create(vm, this, 2, String(), makeDOMExceptionForBuiltins, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.addAbortAlgorithmToSignalPrivateName(), JSFunction::create(vm, this, 2, String(), addAbortAlgorithmToSignal, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.removeAbortAlgorithmFromSignalPrivateName(), JSFunction::create(vm, this, 2, String(), removeAbortAlgorithmFromSignal, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.cloneArrayBufferPrivateName(), JSFunction::create(vm, this, 3, String(), cloneArrayBuffer, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.structuredCloneForStreamPrivateName(), JSFunction::create(vm, this, 1, String(), structuredCloneForStream, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.isAbortSignalPrivateName(), JSFunction::create(vm, this, 1, String(), isAbortSignal, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.getInternalWritableStreamPrivateName(), JSFunction::create(vm, this, 1, String(), getInternalWritableStream, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.createWritableStreamFromInternalPrivateName(), JSFunction::create(vm, this, 1, String(), createWritableStreamFromInternal, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.fulfillModuleSyncPrivateName(), JSFunction::create(vm, this, 1, String(), functionFulfillModuleSync, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(vm.propertyNames->builtinNames().ArrayBufferPrivateName(), arrayBufferConstructor(), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.LoaderPrivateName(), this->moduleLoader(), PropertyAttribute::DontDelete | 0),
        GlobalPropertyInfo(builtinNames.internalModuleRegistryPrivateName(), this->internalModuleRegistry(), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.processBindingConstantsPrivateName(), this->processBindingConstants(), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.requireMapPrivateName(), this->requireMap(), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly | 0),
        GlobalPropertyInfo(builtinNames.TextEncoderStreamEncoderPrivateName(), JSTextEncoderStreamEncoderConstructor(), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly | 0),
        GlobalPropertyInfo(builtinNames.makeErrorWithCodePrivateName(), JSFunction::create(vm, this, 2, String(), jsFunctionMakeErrorWithCode, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.toClassPrivateName(), JSFunction::create(vm, this, 1, String(), jsFunctionToClass, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.inheritsPrivateName(), JSFunction::create(vm, this, 1, String(), jsFunctionInherits, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.makeAbortErrorPrivateName(), JSFunction::create(vm, this, 1, String(), jsFunctionMakeAbortError, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
        GlobalPropertyInfo(builtinNames.checkBufferReadPrivateName(), JSFunction::create(vm, this, 1, String(), jsFunctionCheckBufferRead, ImplementationVisibility::Public), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly),
    };
    addStaticGlobals(staticGlobals, std::size(staticGlobals));

    // TODO: most/all of these private properties can be made as static globals.
    // i've noticed doing it as is will work somewhat but getDirect() wont be able to find them

    putDirectBuiltinFunction(vm, this, builtinNames.createFIFOPrivateName(), streamInternalsCreateFIFOCodeGenerator(vm), PropertyAttribute::Builtin | PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly);
    putDirectBuiltinFunction(vm, this, builtinNames.createEmptyReadableStreamPrivateName(), readableStreamCreateEmptyReadableStreamCodeGenerator(vm), PropertyAttribute::Builtin | PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly);
    putDirectBuiltinFunction(vm, this, builtinNames.createUsedReadableStreamPrivateName(), readableStreamCreateUsedReadableStreamCodeGenerator(vm), PropertyAttribute::Builtin | PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly);
    putDirectBuiltinFunction(vm, this, builtinNames.createNativeReadableStreamPrivateName(), readableStreamCreateNativeReadableStreamCodeGenerator(vm), PropertyAttribute::Builtin | PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly);
    putDirectBuiltinFunction(vm, this, builtinNames.requireESMPrivateName(), commonJSRequireESMCodeGenerator(vm), PropertyAttribute::Builtin | PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly);
    putDirectBuiltinFunction(vm, this, builtinNames.loadEsmIntoCjsPrivateName(), commonJSLoadEsmIntoCjsCodeGenerator(vm), PropertyAttribute::Builtin | PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly);
    putDirectBuiltinFunction(vm, this, builtinNames.internalRequirePrivateName(), commonJSInternalRequireCodeGenerator(vm), PropertyAttribute::Builtin | PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly);

    putDirectBuiltinFunction(vm, this, builtinNames.overridableRequirePrivateName(), commonJSOverridableRequireCodeGenerator(vm), 0);

    putDirectNativeFunction(vm, this, builtinNames.createUninitializedArrayBufferPrivateName(), 1, functionCreateUninitializedArrayBuffer, ImplementationVisibility::Public, NoIntrinsic, PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly);
    putDirectNativeFunction(vm, this, builtinNames.resolveSyncPrivateName(), 1, functionImportMeta__resolveSyncPrivate, ImplementationVisibility::Public, NoIntrinsic, PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly);
    putDirectNativeFunction(vm, this, builtinNames.createInternalModuleByIdPrivateName(), 1, InternalModuleRegistry::jsCreateInternalModuleById, ImplementationVisibility::Public, NoIntrinsic, PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly);

    putDirectNativeFunction(vm, this,
        builtinNames.createCommonJSModulePrivateName(),
        2,
        Bun::jsFunctionCreateCommonJSModule,
        ImplementationVisibility::Public,
        NoIntrinsic,
        PropertyAttribute::ReadOnly | PropertyAttribute::DontDelete | 0);
    putDirectNativeFunction(vm, this,
        builtinNames.evaluateCommonJSModulePrivateName(),
        2,
        Bun::jsFunctionEvaluateCommonJSModule,
        ImplementationVisibility::Public,
        NoIntrinsic,
        PropertyAttribute::ReadOnly | PropertyAttribute::DontDelete | 0);

    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().BufferPrivateName(), JSC::CustomGetterSetter::create(vm, JSBuffer_getter, nullptr), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.lazyStreamPrototypeMapPrivateName(), JSC::CustomGetterSetter::create(vm, functionLazyLoadStreamPrototypeMap_getter, nullptr), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.TransformStreamPrivateName(), CustomGetterSetter::create(vm, TransformStream_getter, nullptr), attributesForStructure(static_cast<unsigned>(PropertyAttribute::DontEnum)) | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.TransformStreamDefaultControllerPrivateName(), CustomGetterSetter::create(vm, TransformStreamDefaultController_getter, nullptr), attributesForStructure(static_cast<unsigned>(PropertyAttribute::DontEnum)) | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.ReadableByteStreamControllerPrivateName(), CustomGetterSetter::create(vm, ReadableByteStreamController_getter, nullptr), attributesForStructure(PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly) | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.ReadableStreamPrivateName(), CustomGetterSetter::create(vm, ReadableStream_getter, nullptr), attributesForStructure(PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly) | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.ReadableStreamBYOBReaderPrivateName(), CustomGetterSetter::create(vm, ReadableStreamBYOBReader_getter, nullptr), attributesForStructure(PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly) | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.ReadableStreamBYOBRequestPrivateName(), CustomGetterSetter::create(vm, ReadableStreamBYOBRequest_getter, nullptr), attributesForStructure(PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly) | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.ReadableStreamDefaultControllerPrivateName(), CustomGetterSetter::create(vm, ReadableStreamDefaultController_getter, nullptr), attributesForStructure(PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly) | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.ReadableStreamDefaultReaderPrivateName(), CustomGetterSetter::create(vm, ReadableStreamDefaultReader_getter, nullptr), attributesForStructure(PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly) | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.WritableStreamPrivateName(), CustomGetterSetter::create(vm, WritableStream_getter, nullptr), attributesForStructure(PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly) | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.WritableStreamDefaultControllerPrivateName(), CustomGetterSetter::create(vm, WritableStreamDefaultController_getter, nullptr), attributesForStructure(PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly) | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.WritableStreamDefaultWriterPrivateName(), CustomGetterSetter::create(vm, WritableStreamDefaultWriter_getter, nullptr), attributesForStructure(PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly) | PropertyAttribute::CustomValue);
    putDirectCustomAccessor(vm, builtinNames.AbortSignalPrivateName(), CustomGetterSetter::create(vm, AbortSignal_getter, nullptr), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly | PropertyAttribute::CustomValue);

    // ----- Public Properties -----

    // a direct accessor (uses js functions for get and set) cannot be on the lookup table. i think.
    putDirectAccessor(
        this,
        builtinNames.selfPublicName(),
        JSC::GetterSetter::create(
            vm,
            this,
            JSFunction::create(vm, this, 0, "get"_s, functionGetSelf, ImplementationVisibility::Public),
            JSFunction::create(vm, this, 0, "set"_s, functionSetSelf, ImplementationVisibility::Public)),
        PropertyAttribute::Accessor | 0);

    // TODO: this should be usable on the lookup table. it crashed las time i tried it
    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "onmessage"_s), JSC::CustomGetterSetter::create(vm, globalOnMessage, setGlobalOnMessage), 0);
    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "onerror"_s), JSC::CustomGetterSetter::create(vm, globalOnError, setGlobalOnError), 0);

    // ----- Extensions to Built-in objects -----

    JSC::JSObject* errorConstructor = this->errorConstructor();
    errorConstructor->putDirectNativeFunction(vm, this, JSC::Identifier::fromString(vm, "captureStackTrace"_s), 2, errorConstructorFuncCaptureStackTrace, ImplementationVisibility::Public, JSC::NoIntrinsic, PropertyAttribute::DontEnum | 0);
    errorConstructor->putDirectNativeFunction(vm, this, JSC::Identifier::fromString(vm, "appendStackTrace"_s), 2, errorConstructorFuncAppendStackTrace, ImplementationVisibility::Private, JSC::NoIntrinsic, PropertyAttribute::DontEnum | 0);
    errorConstructor->putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "prepareStackTrace"_s), JSC::CustomGetterSetter::create(vm, errorConstructorPrepareStackTraceGetter, errorConstructorPrepareStackTraceSetter), PropertyAttribute::DontEnum | PropertyAttribute::CustomValue);

    JSC::JSObject* consoleObject = this->get(this, JSC::Identifier::fromString(vm, "console"_s)).getObject();
    scope.assertNoExceptionExceptTermination();
    RETURN_IF_EXCEPTION(scope, );
    consoleObject->putDirectBuiltinFunction(vm, this, vm.propertyNames->asyncIteratorSymbol, consoleObjectAsyncIteratorCodeGenerator(vm), PropertyAttribute::Builtin | 0);
    consoleObject->putDirectBuiltinFunction(vm, this, clientData->builtinNames().writePublicName(), consoleObjectWriteCodeGenerator(vm), PropertyAttribute::Builtin | 0);
    consoleObject->putDirectCustomAccessor(vm, Identifier::fromString(vm, "Console"_s), CustomGetterSetter::create(vm, getConsoleConstructor, nullptr), PropertyAttribute::CustomValue | 0);
    consoleObject->putDirectCustomAccessor(vm, Identifier::fromString(vm, "_stdout"_s), CustomGetterSetter::create(vm, getConsoleStdout, nullptr), PropertyAttribute::DontEnum | PropertyAttribute::CustomValue | 0);
    consoleObject->putDirectCustomAccessor(vm, Identifier::fromString(vm, "_stderr"_s), CustomGetterSetter::create(vm, getConsoleStderr, nullptr), PropertyAttribute::DontEnum | PropertyAttribute::CustomValue | 0);
}

// ===================== start conditional builtin globals =====================
// These functions register globals based on runtime conditions (e.g. CLI flags,
// environment variables, etc.). See `Run.addConditionalGlobals()` in bun_js.zig
// for where these are called.

/// `globalThis.gc()` is an alias for `Bun.gc(true)`
/// Note that `vm` is a `VirtualMachine*`
extern "C" size_t Bun__gc(void* vm, bool sync);
JSC_DEFINE_HOST_FUNCTION(functionJsGc,
    (JSC::JSGlobalObject * global, JSC::CallFrame* callFrame))
{
    Zig::GlobalObject* globalObject = defaultGlobalObject(global);
    Bun__gc(globalObject->bunVM(), true);
    return JSValue::encode(jsUndefined());
}

extern "C" [[ZIG_EXPORT(nothrow)]] void JSC__JSGlobalObject__addGc(JSC::JSGlobalObject* globalObject)
{
    auto& vm = JSC::getVM(globalObject);
    globalObject->putDirectNativeFunction(vm, globalObject, JSC::Identifier::fromString(vm, "gc"_s), 0, functionJsGc, ImplementationVisibility::Public, JSC::NoIntrinsic, PropertyAttribute::DontEnum | 0);
}

// ====================== end conditional builtin globals ======================

void GlobalObject::drainMicrotasks()
{
    auto& vm = this->vm();
    if (auto nextTickQueue = this->m_nextTickQueue.get()) {
        Bun::JSNextTickQueue* queue = jsCast<Bun::JSNextTickQueue*>(nextTickQueue);
        queue->drain(vm, this);
        return;
    }

    vm.drainMicrotasks();
}

extern "C" void JSC__JSGlobalObject__drainMicrotasks(Zig::GlobalObject* globalObject)
{
    globalObject->drainMicrotasks();
}

extern "C" EncodedJSValue JSC__JSGlobalObject__getHTTP2CommonString(Zig::GlobalObject* globalObject, uint32_t hpack_index)
{
    auto value = globalObject->http2CommonStrings().getStringFromHPackIndex(hpack_index, globalObject);
    if (value != nullptr) {
        return JSValue::encode(value);
    }
    return JSValue::encode(JSValue::JSUndefined);
}

template<class Visitor, class T> static void visitGlobalObjectMember(Visitor& visitor, T& anything)
{
    anything.visit(visitor);
}

template<class Visitor, class T> static void visitGlobalObjectMember(Visitor& visitor, WriteBarrier<T>& barrier)
{
    visitor.append(barrier);
}

template<class Visitor, class T> static void visitGlobalObjectMember(Visitor& visitor, std::unique_ptr<T>& ptr)
{
    ptr->visit(visitor);
}

template<class Visitor, class T, size_t n> static void visitGlobalObjectMember(Visitor& visitor, std::array<WriteBarrier<T>, n>& barriers)
{
    visitor.append(barriers.begin(), barriers.end());
}

template<typename Visitor>
void GlobalObject::visitChildrenImpl(JSCell* cell, Visitor& visitor)
{
    GlobalObject* thisObject = jsCast<GlobalObject*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    Base::visitChildren(thisObject, visitor);

    {
        // The GC thread has to grab the GC lock even though it is not mutating the containers.
        Locker locker { thisObject->m_gcLock };

        for (auto& structure : thisObject->m_structures.values())
            visitor.append(structure);

        for (auto& guarded : thisObject->m_guardedObjects)
            guarded->visitAggregate(visitor);
    }

#define VISIT_GLOBALOBJECT_GC_MEMBER(visibility, T, name) \
    visitGlobalObjectMember(visitor, thisObject->name);
    FOR_EACH_GLOBALOBJECT_GC_MEMBER(VISIT_GLOBALOBJECT_GC_MEMBER)
#undef VISIT_GLOBALOBJECT_GC_MEMBER

    WebCore::clientData(thisObject->vm())->httpHeaderIdentifiers().visit<Visitor>(visitor);

    thisObject->visitGeneratedLazyClasses<Visitor>(thisObject, visitor);
    thisObject->visitAdditionalChildren<Visitor>(visitor);
}

extern "C" bool JSGlobalObject__setTimeZone(JSC::JSGlobalObject* globalObject, const ZigString* timeZone)
{
    auto& vm = JSC::getVM(globalObject);

    if (WTF::setTimeZoneOverride(Zig::toString(*timeZone))) {
        vm.dateCache.resetIfNecessarySlow();
        return true;
    }

    return false;
}

extern "C" void JSGlobalObject__requestTermination(JSC::JSGlobalObject* globalObject)
{
    auto& vm = JSC::getVM(globalObject);
    vm.ensureTerminationException();
    vm.setHasTerminationRequest();
}

extern "C" void JSGlobalObject__clearTerminationException(JSC::JSGlobalObject* globalObject)
{
    auto& vm = JSC::getVM(globalObject);
    // Clear the request for the termination exception to be thrown
    vm.clearHasTerminationRequest();
    // In case it actually has been thrown, clear the exception itself as well
    auto scope = DECLARE_CATCH_SCOPE(vm);
    if (scope.exception() && vm.isTerminationException(scope.exception())) {
        scope.clearException();
    }
}

extern "C" void Bun__queueTask(JSC::JSGlobalObject*, WebCore::EventLoopTask* task);
extern "C" void Bun__queueTaskWithTimeout(JSC::JSGlobalObject*, WebCore::EventLoopTask* task, int timeout);
extern "C" void Bun__queueTaskConcurrently(JSC::JSGlobalObject*, WebCore::EventLoopTask* task);
extern "C" void Bun__performTask(Zig::GlobalObject* globalObject, WebCore::EventLoopTask* task)
{
    task->performTask(*globalObject->scriptExecutionContext());
}

RefPtr<Performance> GlobalObject::performance()
{
    if (!m_performance) {
        auto* context = this->scriptExecutionContext();
        double nanoTimeOrigin = Bun__readOriginTimerStart(this->bunVM());
        auto timeOrigin = MonotonicTime::fromRawSeconds(nanoTimeOrigin / 1000.0);
        m_performance = Performance::create(context, timeOrigin);
    }

    return m_performance;
}

void GlobalObject::queueTask(WebCore::EventLoopTask* task)
{
    Bun__queueTask(this, task);
}

void GlobalObject::queueTaskOnTimeout(WebCore::EventLoopTask* task, int timeout)
{
    Bun__queueTaskWithTimeout(this, task, timeout);
}

void GlobalObject::queueTaskConcurrently(WebCore::EventLoopTask* task)
{
    Bun__queueTaskConcurrently(this, task);
}

extern "C" void Bun__handleRejectedPromise(Zig::GlobalObject* JSGlobalObject, JSC::JSPromise* promise);

void GlobalObject::handleRejectedPromises()
{
    JSC::VM& virtual_machine = vm();
    auto scope = DECLARE_CATCH_SCOPE(virtual_machine);
    do {
        auto unhandledRejections = WTFMove(m_aboutToBeNotifiedRejectedPromises);
        for (auto& promise : unhandledRejections) {
            if (promise->isHandled(virtual_machine))
                continue;

            Bun__handleRejectedPromise(this, promise.get());
            if (auto ex = scope.exception()) this->reportUncaughtExceptionAtEventLoop(this, ex);
        }
    } while (!m_aboutToBeNotifiedRejectedPromises.isEmpty());
}

DEFINE_VISIT_CHILDREN(GlobalObject);

template<typename Visitor>
void GlobalObject::visitAdditionalChildren(Visitor& visitor)
{
    GlobalObject* thisObject = this;
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    thisObject->globalEventScope->visitJSEventListeners(visitor);

    ScriptExecutionContext* context = thisObject->scriptExecutionContext();
    visitor.addOpaqueRoot(context);
}

DEFINE_VISIT_ADDITIONAL_CHILDREN(GlobalObject);

template<typename Visitor>
void GlobalObject::visitOutputConstraints(JSCell* cell, Visitor& visitor)
{
    auto* thisObject = jsCast<GlobalObject*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    Base::visitOutputConstraints(thisObject, visitor);
    thisObject->visitAdditionalChildren(visitor);
}

template void GlobalObject::visitOutputConstraints(JSCell*, AbstractSlotVisitor&);
template void GlobalObject::visitOutputConstraints(JSCell*, SlotVisitor&);

// void GlobalObject::destroy(JSCell* cell)
// {
//     jsCast<Zig::GlobalObject*>(cell)->Zig::GlobalObject::~Zig::GlobalObject();
// }

// template<typename Visitor>
// void GlobalObject::visitChildrenImpl(JSCell* cell, Visitor& visitor)
// {
//     Zig::GlobalObject* thisObject = jsCast<Zig::GlobalObject*>(cell);
//     ASSERT_GC_OBJECT_INHERITS(thisObject, info());
//     Base::visitChildren(thisObject, visitor);

//     {
//         // The GC thread has to grab the GC lock even though it is not mutating the containers.
//         Locker locker { thisObject->m_gcLock };

//         for (auto& structure : thisObject->m_structures.values())
//             visitor.append(structure);

//         for (auto& guarded : thisObject->m_guardedObjects)
//             guarded->visitAggregate(visitor);
//     }

//     for (auto& constructor : thisObject->constructors().array())
//         visitor.append(constructor);

//     thisObject->m_builtinInternalFunctions.visit(visitor);
// }

// DEFINE_VISIT_CHILDREN(Zig::GlobalObject);

void GlobalObject::reload()
{
    JSModuleLoader* moduleLoader = this->moduleLoader();
    auto& vm = this->vm();
    JSC::JSMap* registry = jsCast<JSC::JSMap*>(moduleLoader->get(
        this,
        Identifier::fromString(vm, "registry"_s)));

    registry->clear(this);
    this->requireMap()->clear(this);

    // If we run the GC every time, we will never get the SourceProvider cache hit.
    // So we run the GC every other time.
    if ((this->reloadCount++ + 1) % 2 == 0) {
        this->vm().heap.collectSync();
    }
}

extern "C" void JSC__JSGlobalObject__reload(JSC::JSGlobalObject* arg0)
{
    Zig::GlobalObject* globalObject = static_cast<Zig::GlobalObject*>(arg0);
    globalObject->reload();
}

extern "C" void JSC__JSGlobalObject__queueMicrotaskCallback(Zig::GlobalObject* globalObject, void* ptr, MicrotaskCallback callback)
{
    JSFunction* function = globalObject->nativeMicrotaskTrampoline();

    // Do not use JSCell* here because the GC will try to visit it.
    globalObject->queueMicrotask(function, JSValue(std::bit_cast<double>(reinterpret_cast<uintptr_t>(ptr))), JSValue(std::bit_cast<double>(reinterpret_cast<uintptr_t>(callback))), jsUndefined(), jsUndefined());
}

JSC::Identifier GlobalObject::moduleLoaderResolve(JSGlobalObject* jsGlobalObject,
    JSModuleLoader* loader, JSValue key,
    JSValue referrer, JSValue origin)
{
    Zig::GlobalObject* globalObject = static_cast<Zig::GlobalObject*>(jsGlobalObject);

    ErrorableString res;
    res.success = false;

    BunString keyZ;
    if (key.isString()) {
        auto moduleName = jsCast<JSString*>(key)->value(globalObject);
        if (moduleName->startsWith("file://"_s)) {
            auto url = WTF::URL(moduleName);
            if (url.isValid() && !url.isEmpty()) {
                keyZ = Bun::toStringRef(url.fileSystemPath());
            } else {
                keyZ = Bun::toStringRef(moduleName);
            }
        } else {
            keyZ = Bun::toStringRef(moduleName);
        }

    } else {
        keyZ = Bun::toStringRef(globalObject, key);
    }
    BunString referrerZ = referrer && !referrer.isUndefinedOrNull() && referrer.isString() ? Bun::toStringRef(globalObject, referrer) : BunStringEmpty;

    if (globalObject->onLoadPlugins.hasVirtualModules()) {
        if (auto resolvedString = globalObject->onLoadPlugins.resolveVirtualModule(keyZ.toWTFString(), referrerZ.toWTFString())) {
            return Identifier::fromString(globalObject->vm(), resolvedString.value());
        }
    } else {
        ASSERT(!globalObject->onLoadPlugins.mustDoExpensiveRelativeLookup);
    }

    ZigString queryString = { 0, 0 };
    Zig__GlobalObject__resolve(&res, globalObject, &keyZ, &referrerZ, &queryString);
    keyZ.deref();
    referrerZ.deref();

    if (res.success) {
        if (queryString.len > 0) {
            return JSC::Identifier::fromString(globalObject->vm(), makeString(res.result.value.toWTFString(BunString::ZeroCopy), Zig::toString(queryString)));
        }

        return Identifier::fromString(globalObject->vm(), res.result.value.toWTFString(BunString::ZeroCopy));
    } else {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        throwException(scope, res.result.err, globalObject);
        return globalObject->vm().propertyNames->emptyIdentifier;
    }
}

JSC::JSInternalPromise* GlobalObject::moduleLoaderImportModule(JSGlobalObject* jsGlobalObject,
    JSModuleLoader*,
    JSString* moduleNameValue,
    JSValue parameters,
    const SourceOrigin& sourceOrigin)
{
    auto* globalObject = static_cast<Zig::GlobalObject*>(jsGlobalObject);

    VM& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);

    {
        JSC::JSInternalPromise* result = NodeVM::importModule(globalObject, moduleNameValue, parameters, sourceOrigin);
        RETURN_IF_EXCEPTION(scope, nullptr);
        if (result) {
            return result;
        }
    }

    JSC::Identifier resolvedIdentifier;

    auto moduleName = moduleNameValue->value(globalObject);
    RETURN_IF_EXCEPTION(scope, nullptr);
    if (globalObject->onLoadPlugins.hasVirtualModules()) {
        if (auto resolution = globalObject->onLoadPlugins.resolveVirtualModule(moduleName, sourceOrigin.url().protocolIsFile() ? sourceOrigin.url().fileSystemPath() : String())) {
            resolvedIdentifier = JSC::Identifier::fromString(vm, resolution.value());

            auto result = JSC::importModule(globalObject, resolvedIdentifier, JSC::jsUndefined(), parameters, JSC::jsUndefined());
            if (scope.exception()) [[unlikely]] {
                auto* promise = JSC::JSInternalPromise::create(vm, globalObject->internalPromiseStructure());
                return promise->rejectWithCaughtException(globalObject, scope);
            }
            return result;
        }
    }

    {
        ErrorableString resolved;
        memset(&resolved, 0, sizeof(resolved));

        auto sourceURL = sourceOrigin.url();
        BunString moduleNameZ;
        String moduleStringHolder;
        if (moduleName->startsWith("file://"_s)) {
            auto url = WTF::URL(moduleName);
            if (url.isValid() && !url.isEmpty()) {
                moduleStringHolder = url.fileSystemPath();
                moduleNameZ = Bun::toStringRef(moduleStringHolder);
            } else {
                moduleNameZ = Bun::toStringRef(moduleName);
            }
        } else {
            moduleNameZ = Bun::toStringRef(moduleName);
        }

        ZigString queryString = { 0, 0 };
        String sourceOriginStringHolder;

        if (sourceURL.isEmpty()) {
            sourceOriginStringHolder = String("."_s);
        } else if (sourceURL.protocolIsFile()) {
            sourceOriginStringHolder = sourceURL.fileSystemPath();
        } else if (sourceURL.protocol() == "builtin"_s) {
            ASSERT(sourceURL.string().startsWith("builtin://"_s));
            sourceOriginStringHolder = sourceURL.string().substringSharingImpl(10 /* builtin:// */);
        } else {
            sourceOriginStringHolder = sourceURL.path().toString();
        }

        auto sourceOriginZ = Bun::toStringRef(sourceOriginStringHolder);

        Zig__GlobalObject__resolve(&resolved, globalObject, &moduleNameZ, &sourceOriginZ, &queryString);

        // If resolution failed, make sure it becomes a pending exception
        if (!resolved.success && !scope.exception()) [[unlikely]] {
            throwException(scope, resolved.result.err, globalObject);
        }

        // And convert that pending exception into a rejected promise.
        if (scope.exception()) [[unlikely]] {
            auto* promise = JSC::JSInternalPromise::create(vm, globalObject->internalPromiseStructure());
            moduleNameZ.deref();
            sourceOriginZ.deref();

            return promise->rejectWithCaughtException(globalObject, scope);
        }

        if (queryString.len == 0) {
            resolvedIdentifier = JSC::Identifier::fromString(vm, resolved.result.value.toWTFString());
        } else {
            resolvedIdentifier = JSC::Identifier::fromString(vm, makeString(resolved.result.value.toWTFString(BunString::ZeroCopy), Zig::toString(queryString)));
        }

        moduleNameZ.deref();
        sourceOriginZ.deref();
    }

    // This gets passed through the "parameters" argument to moduleLoaderFetch.
    // Therefore, we modify it in place.
    if (parameters && parameters.isObject()) {
        auto* object = parameters.toObject(globalObject);
        auto withObject = object->getIfPropertyExists(globalObject, vm.propertyNames->withKeyword);
        RETURN_IF_EXCEPTION(scope, {});
        if (withObject) {
            if (withObject.isObject()) {
                auto* with = jsCast<JSObject*>(withObject);
                auto type = with->getIfPropertyExists(globalObject, vm.propertyNames->type);
                RETURN_IF_EXCEPTION(scope, {});
                if (type) {
                    if (type.isString()) {
                        const auto typeString = type.toWTFString(globalObject);
                        parameters = JSC::JSScriptFetchParameters::create(vm, ScriptFetchParameters::create(typeString));
                    }
                }
            }
        }
    }

    auto result = JSC::importModule(globalObject, resolvedIdentifier,
        JSC::jsUndefined(), parameters, jsUndefined());
    if (scope.exception()) [[unlikely]] {
        return JSC::JSInternalPromise::rejectedPromiseWithCaughtException(globalObject, scope);
    }

    ASSERT(result);
    return result;
}

static JSC::JSInternalPromise* rejectedInternalPromise(JSC::JSGlobalObject* globalObject, JSC::JSValue value)
{
    auto& vm = JSC::getVM(globalObject);
    JSInternalPromise* promise = JSInternalPromise::create(vm, globalObject->internalPromiseStructure());
    promise->internalField(JSC::JSPromise::Field::ReactionsOrResult).set(vm, promise, value);
    promise->internalField(JSC::JSPromise::Field::Flags).set(vm, promise, jsNumber(promise->internalField(JSC::JSPromise::Field::Flags).get().asUInt32AsAnyInt() | JSC::JSPromise::isFirstResolvingFunctionCalledFlag | static_cast<unsigned>(JSC::JSPromise::Status::Rejected)));
    return promise;
}

JSC::JSInternalPromise* GlobalObject::moduleLoaderFetch(JSGlobalObject* globalObject,
    JSModuleLoader* loader, JSValue key,
    JSValue parameters, JSValue script)
{
    auto& vm = JSC::getVM(globalObject);

    auto scope = DECLARE_THROW_SCOPE(vm);

    auto moduleKeyJS = key.toString(globalObject);
    RETURN_IF_EXCEPTION(scope, {});
    auto moduleKey = moduleKeyJS->value(globalObject);
    if (scope.exception()) [[unlikely]]
        return rejectedInternalPromise(globalObject, scope.exception()->value());

    if (moduleKey->endsWith(".node"_s)) {
        return rejectedInternalPromise(globalObject, createTypeError(globalObject, "To load Node-API modules, use require() or process.dlopen instead of import."_s));
    }

    auto moduleKeyBun = Bun::toString(moduleKey);
    auto sourceString = String("undefined"_s);
    auto typeAttributeString = String();

    if (parameters && parameters.isCell()) {
        JSCell* parametersCell = parameters.asCell();
        if (parametersCell->type() == JSScriptFetchParametersType) {
            auto* obj = jsCast<JSScriptFetchParameters*>(parametersCell);
            const auto& params = obj->parameters();

            if (params.type() == ScriptFetchParameters::Type::HostDefined) {
                typeAttributeString = params.hostDefinedImportType();
            } else if (params.type() == ScriptFetchParameters::Type::JSON) {
                typeAttributeString = "json"_s;
            } else if (params.type() == ScriptFetchParameters::Type::WebAssembly) {
                typeAttributeString = "webassembly"_s;
            }
        }
    }

    auto source = Bun::toString(sourceString);
    auto typeAttribute = Bun::toString(typeAttributeString);
    ErrorableResolvedSource res;
    res.success = false;
    // zero-initialize entire result union. zeroed BunString has BunStringTag::Dead, and zeroed
    // EncodedJSValues are empty, which our code should be handling
    memset(&res.result, 0, sizeof res.result);

    JSValue result = Bun::fetchESMSourceCodeAsync(
        static_cast<Zig::GlobalObject*>(globalObject),
        moduleKeyJS,
        &res,
        &moduleKeyBun,
        &source,
        typeAttributeString.isEmpty() ? nullptr : &typeAttribute);

    RETURN_IF_EXCEPTION(scope, rejectedInternalPromise(globalObject, scope.exception()->value()));
    ASSERT(result);
    if (auto* internalPromise = JSC::jsDynamicCast<JSC::JSInternalPromise*>(result)) {
        return internalPromise;
    } else if (auto* promise = JSC::jsDynamicCast<JSC::JSPromise*>(result)) {
        return jsCast<JSC::JSInternalPromise*>(promise);
    } else {
        return rejectedInternalPromise(globalObject, result);
    }
}

JSC::JSObject* GlobalObject::moduleLoaderCreateImportMetaProperties(JSGlobalObject* globalObject,
    JSModuleLoader* loader,
    JSValue key,
    JSModuleRecord* record,
    JSValue val)
{
    return Zig::ImportMetaObject::create(globalObject, key);
}

JSC::JSValue GlobalObject::moduleLoaderEvaluate(JSGlobalObject* lexicalGlobalObject,
    JSModuleLoader* moduleLoader, JSValue key,
    JSValue moduleRecordValue, JSValue scriptFetcher,
    JSValue sentValue, JSValue resumeMode)
{

    if (scriptFetcher && scriptFetcher.isObject()) [[unlikely]] {
        return scriptFetcher;
    }

    JSC::JSValue result = moduleLoader->evaluateNonVirtual(lexicalGlobalObject, key, moduleRecordValue,
        scriptFetcher, sentValue, resumeMode);

    return result;
}

extern "C" bool Bun__VM__specifierIsEvalEntryPoint(void*, EncodedJSValue);
extern "C" void Bun__VM__setEntryPointEvalResultESM(void*, EncodedJSValue);

JSC::JSValue EvalGlobalObject::moduleLoaderEvaluate(JSGlobalObject* lexicalGlobalObject,
    JSModuleLoader* moduleLoader, JSValue key,
    JSValue moduleRecordValue, JSValue scriptFetcher,
    JSValue sentValue, JSValue resumeMode)
{
    Zig::GlobalObject* globalObject = jsCast<Zig::GlobalObject*>(lexicalGlobalObject);

    if (scriptFetcher && scriptFetcher.isObject()) [[unlikely]] {
        if (Bun__VM__specifierIsEvalEntryPoint(globalObject->bunVM(), JSValue::encode(key))) {
            Bun__VM__setEntryPointEvalResultESM(globalObject->bunVM(), JSValue::encode(scriptFetcher));
        }
        return scriptFetcher;
    }

    JSC::JSValue result = moduleLoader->evaluateNonVirtual(lexicalGlobalObject, key, moduleRecordValue,
        scriptFetcher, sentValue, resumeMode);

    if (Bun__VM__specifierIsEvalEntryPoint(globalObject->bunVM(), JSValue::encode(key))) {
        Bun__VM__setEntryPointEvalResultESM(globalObject->bunVM(), JSValue::encode(result));
    }

    return result;
}

extern "C" JSC::EncodedJSValue Zig__GlobalObject__getBodyStreamOrBytesForWasmStreaming(JSGlobalObject*, EncodedJSValue response, JSC::Wasm::StreamingCompiler* compiler);

extern "C" void JSC__Wasm__StreamingCompiler__addBytes(JSC::Wasm::StreamingCompiler* compiler, const uint8_t* spanPtr, size_t spanSize)
{
    compiler->addBytes(std::span(spanPtr, spanSize));
}

static JSC::JSPromise* handleResponseOnStreamingAction(JSGlobalObject* lexicalGlobalObject, JSC::JSValue source, JSC::Wasm::CompilerMode mode, JSC::JSObject* importObject)
{
    auto globalObject = defaultGlobalObject(lexicalGlobalObject);
    auto& vm = JSC::getVM(globalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);
    JSC::JSLockHolder locker(vm);

    auto promise = JSC::JSPromise::create(vm, globalObject->promiseStructure());
    auto sourceCode = makeSource("[wasm code]"_s, SourceOrigin(), SourceTaintedOrigin::Untainted);
    auto compiler = JSC::Wasm::StreamingCompiler::create(vm, mode, globalObject, promise, importObject, sourceCode);

    // getBodyStreamOrBytesForWasmStreaming throws the proper exception. Since this is being
    // executed in a .then(...) callback, throwing is perfectly fine.

    auto readableStreamMaybe = JSC::JSValue::decode(Zig__GlobalObject__getBodyStreamOrBytesForWasmStreaming(
        globalObject, JSC::JSValue::encode(source), compiler.ptr()));

    RETURN_IF_EXCEPTION(scope, nullptr);

    // We were able to get the slice synchronously.
    if (readableStreamMaybe.isNull()) {
        compiler->finalize(globalObject);

        // Apparently rejecting a Promise (done in JSC::Wasm::StreamingCompiler#fail) can throw
        RETURN_IF_EXCEPTION(scope, nullptr);
        return promise;
    }

    auto wrapper = WebCore::toJSNewlyCreated(globalObject, globalObject, WTFMove(compiler));
    auto builtin = globalObject->wasmStreamingConsumeStreamFunction();
    auto callData = JSC::getCallData(builtin);
    MarkedArgumentBuffer arguments;

    arguments.append(readableStreamMaybe);
    JSC::call(globalObject, builtin, callData, wrapper, arguments);
    scope.assertNoException();
    return promise;
}

JSC::JSPromise* GlobalObject::compileStreaming(JSGlobalObject* globalObject, JSC::JSValue source)
{
    return handleResponseOnStreamingAction(globalObject, source, JSC::Wasm::CompilerMode::Validation, nullptr);
}

JSC::JSPromise* GlobalObject::instantiateStreaming(JSGlobalObject* globalObject, JSC::JSValue source, JSC::JSObject* importObject)
{
    return handleResponseOnStreamingAction(globalObject, source, JSC::Wasm::CompilerMode::FullCompile, importObject);
}

GlobalObject::PromiseFunctions GlobalObject::promiseHandlerID(Zig::FFIFunction handler)
{
    if (handler == BunServe__onResolvePlugins) {
        return GlobalObject::PromiseFunctions::BunServe__Plugins__onResolve;
    } else if (handler == BunServe__onRejectPlugins) {
        return GlobalObject::PromiseFunctions::BunServe__Plugins__onReject;
    } else if (handler == Bun__HTTPRequestContext__onReject) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContext__onReject;
    } else if (handler == Bun__HTTPRequestContext__onRejectStream) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContext__onRejectStream;
    } else if (handler == Bun__HTTPRequestContext__onResolve) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContext__onResolve;
    } else if (handler == Bun__HTTPRequestContext__onResolveStream) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContext__onResolveStream;
    } else if (handler == Bun__HTTPRequestContextTLS__onReject) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextTLS__onReject;
    } else if (handler == Bun__HTTPRequestContextTLS__onRejectStream) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextTLS__onRejectStream;
    } else if (handler == Bun__HTTPRequestContextTLS__onResolve) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextTLS__onResolve;
    } else if (handler == Bun__HTTPRequestContextTLS__onResolveStream) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextTLS__onResolveStream;
    } else if (handler == Bun__HTTPRequestContextDebug__onReject) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextDebug__onReject;
    } else if (handler == Bun__HTTPRequestContextDebug__onRejectStream) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextDebug__onRejectStream;
    } else if (handler == Bun__HTTPRequestContextDebug__onResolve) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextDebug__onResolve;
    } else if (handler == Bun__HTTPRequestContextDebug__onResolveStream) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextDebug__onResolveStream;
    } else if (handler == Bun__HTTPRequestContextDebugTLS__onReject) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextDebugTLS__onReject;
    } else if (handler == Bun__HTTPRequestContextDebugTLS__onRejectStream) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextDebugTLS__onRejectStream;
    } else if (handler == Bun__HTTPRequestContextDebugTLS__onResolve) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextDebugTLS__onResolve;
    } else if (handler == Bun__HTTPRequestContextDebugTLS__onResolveStream) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextDebugTLS__onResolveStream;
    } else if (handler == Bun__HTTPRequestContextDebugTLS__onResolveStream) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextDebugTLS__onResolveStream;
    } else if (handler == Bun__HTTPRequestContextDebugTLS__onResolveStream) {
        return GlobalObject::PromiseFunctions::Bun__HTTPRequestContextDebugTLS__onResolveStream;
    } else if (handler == jsFunctionOnLoadObjectResultResolve) {
        return GlobalObject::PromiseFunctions::jsFunctionOnLoadObjectResultResolve;
    } else if (handler == jsFunctionOnLoadObjectResultReject) {
        return GlobalObject::PromiseFunctions::jsFunctionOnLoadObjectResultReject;
    } else if (handler == Bun__TestScope__onReject) {
        return GlobalObject::PromiseFunctions::Bun__TestScope__onReject;
    } else if (handler == Bun__TestScope__onResolve) {
        return GlobalObject::PromiseFunctions::Bun__TestScope__onResolve;
    } else if (handler == Bun__BodyValueBufferer__onResolveStream) {
        return GlobalObject::PromiseFunctions::Bun__BodyValueBufferer__onResolveStream;
    } else if (handler == Bun__BodyValueBufferer__onRejectStream) {
        return GlobalObject::PromiseFunctions::Bun__BodyValueBufferer__onRejectStream;
    } else if (handler == Bun__onResolveEntryPointResult) {
        return GlobalObject::PromiseFunctions::Bun__onResolveEntryPointResult;
    } else if (handler == Bun__onRejectEntryPointResult) {
        return GlobalObject::PromiseFunctions::Bun__onRejectEntryPointResult;
    } else if (handler == Bun__NodeHTTPRequest__onResolve) {
        return GlobalObject::PromiseFunctions::Bun__NodeHTTPRequest__onResolve;
    } else if (handler == Bun__NodeHTTPRequest__onReject) {
        return GlobalObject::PromiseFunctions::Bun__NodeHTTPRequest__onReject;
    } else if (handler == Bun__FileStreamWrapper__onResolveRequestStream) {
        return GlobalObject::PromiseFunctions::Bun__FileStreamWrapper__onResolveRequestStream;
    } else if (handler == Bun__FileStreamWrapper__onRejectRequestStream) {
        return GlobalObject::PromiseFunctions::Bun__FileStreamWrapper__onRejectRequestStream;
    } else if (handler == Bun__FileSink__onResolveStream) {
        return GlobalObject::PromiseFunctions::Bun__FileSink__onResolveStream;
    } else if (handler == Bun__FileSink__onRejectStream) {
        return GlobalObject::PromiseFunctions::Bun__FileSink__onRejectStream;
    } else {
        RELEASE_ASSERT_NOT_REACHED();
    }
}

napi_env GlobalObject::makeNapiEnv(const napi_module& mod)
{
    m_napiEnvs.append(std::make_unique<napi_env__>(this, mod));
    return m_napiEnvs.last().get();
}

napi_env GlobalObject::makeNapiEnvForFFI()
{
    auto out = makeNapiEnv(napi_module {
        .nm_version = 9,
        .nm_flags = 0,
        .nm_filename = "ffi://",
        .nm_register_func = nullptr,
        .nm_modname = "[ffi]",
        .nm_priv = nullptr,
        .reserved = {},
    });
    return out;
}

bool GlobalObject::hasNapiFinalizers() const
{
    for (const auto& env : m_napiEnvs) {
        if (env->hasFinalizers()) {
            return true;
        }
    }

    return false;
}

void GlobalObject::setNodeWorkerEnvironmentData(JSMap* data) { m_nodeWorkerEnvironmentData.set(vm(), this, data); }

void GlobalObject::trackFFIFunction(JSC::JSFunction* function)
{
    this->m_ffiFunctions.append(JSC::Strong<JSC::JSFunction> { vm(), function });
}
bool GlobalObject::untrackFFIFunction(JSC::JSFunction* function)
{
    for (size_t i = 0; i < this->m_ffiFunctions.size(); ++i) {
        if (this->m_ffiFunctions[i].get() == function) {
            this->m_ffiFunctions[i].clear();
            this->m_ffiFunctions.removeAt(i);
            return true;
        }
    }
    return false;
}

extern "C" void Zig__GlobalObject__destructOnExit(Zig::GlobalObject* globalObject)
{
    auto& vm = JSC::getVM(globalObject);
    if (vm.entryScope) {
        // Exiting while running JavaScript code (e.g. `process.exit()`), so we can't destroy it
        // just now. Perhaps later in this case we can defer destruction to run later.
        return;
    }
    gcUnprotect(globalObject);
    globalObject = nullptr;
    vm.heap.collectNow(JSC::Sync, JSC::CollectionScope::Full);
    vm.derefSuppressingSaferCPPChecking();
    vm.derefSuppressingSaferCPPChecking();
}

#include "ZigGeneratedClasses+lazyStructureImpl.h"
#include "ZigGlobalObject.lut.h"

const JSC::ClassInfo GlobalObject::s_info = { "GlobalObject"_s, &Base::s_info, &bunGlobalObjectTable, nullptr,
    CREATE_METHOD_TABLE(GlobalObject) };

} // namespace Zig

JSC_DEFINE_HOST_FUNCTION(jsFunctionNotImplemented, (JSGlobalObject * leixcalGlobalObject, CallFrame* callFrame))
{
    auto& vm = JSC::getVM(leixcalGlobalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);
    return throwVMError(leixcalGlobalObject, scope, "Not implemented"_s);
}

JSC_DEFINE_HOST_FUNCTION(jsFunctionCreateFunctionThatMasqueradesAsUndefined, (JSC::JSGlobalObject * leixcalGlobalObject, JSC::CallFrame* callFrame))
{
    auto& vm = JSC::getVM(leixcalGlobalObject);
    auto scope = DECLARE_THROW_SCOPE(vm);
    auto name = callFrame->argument(0).toWTFString(leixcalGlobalObject);
    scope.assertNoException();
    auto count = callFrame->argument(1).toNumber(leixcalGlobalObject);
    scope.assertNoException();
    auto* func = InternalFunction::createFunctionThatMasqueradesAsUndefined(vm, leixcalGlobalObject, count, name, jsFunctionNotImplemented);
    return JSC::JSValue::encode(func);
}
