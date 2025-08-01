#pragma once

namespace WebCore {

class ExtendedDOMClientIsoSubspaces;
class ExtendedDOMIsoSubspaces;

class DOMWrapperWorld;
}

#include "root.h"

#include "ExtendedDOMClientIsoSubspaces.h"
#include "ExtendedDOMIsoSubspaces.h"
#include "DOMIsoSubspaces.h"
#include "BunBuiltinNames.h"
// #include "WebCoreJSBuiltins.h"
// #include "WorkerThreadType.h"
#include <wtf/Function.h>
#include <wtf/HashSet.h>
#include <wtf/RefPtr.h>
#include <JavaScriptCore/WeakInlines.h>
#include <wtf/StdLibExtras.h>
#include "WebCoreJSBuiltins.h"
#include "JSCTaskScheduler.h"
#include "HTTPHeaderIdentifiers.h"
namespace Zig {
}

namespace WebCore {
using namespace JSC;
using namespace Zig;

enum class UseCustomHeapCellType { Yes,
    No };

class JSHeapData {
    WTF_MAKE_NONCOPYABLE(JSHeapData);
    WTF_DEPRECATED_MAKE_FAST_ALLOCATED(JSHeapData);
    friend class JSVMClientData;

public:
    JSHeapData(JSC::Heap&);

    static JSHeapData* ensureHeapData(JSC::Heap&);

    Lock& lock() { return m_lock; }
    ExtendedDOMIsoSubspaces& subspaces() { return *m_subspaces.get(); }

    Vector<JSC::IsoSubspace*>& outputConstraintSpaces() { return m_outputConstraintSpaces; }

    template<typename Func>
    void forEachOutputConstraintSpace(const Func& func)
    {
        for (auto* space : m_outputConstraintSpaces)
            func(*space);
    }

    JSC::IsoHeapCellType m_heapCellTypeForJSWorkerGlobalScope;
    JSC::IsoHeapCellType m_heapCellTypeForNodeVMGlobalObject;
    JSC::IsoHeapCellType m_heapCellTypeForNapiHandleScopeImpl;
    JSC::IsoHeapCellType m_heapCellTypeForBakeGlobalObject;

private:
    Lock m_lock;

private:
    std::unique_ptr<ExtendedDOMIsoSubspaces> m_subspaces;
    JSC::IsoSubspace m_domConstructorSpace;
    JSC::IsoSubspace m_domBuiltinConstructorSpace;
    JSC::IsoSubspace m_domNamespaceObjectSpace;

    Vector<JSC::IsoSubspace*> m_outputConstraintSpaces;
};

DECLARE_ALLOCATOR_WITH_HEAP_IDENTIFIER(JSVMClientData);

class JSVMClientData : public JSC::VM::ClientData {
    WTF_MAKE_NONCOPYABLE(JSVMClientData);
    WTF_DEPRECATED_MAKE_FAST_ALLOCATED_WITH_HEAP_IDENTIFIER(JSVMClientData, JSVMClientData);

public:
    explicit JSVMClientData(JSC::VM&, RefPtr<JSC::SourceProvider>);

    virtual ~JSVMClientData();

    static void create(JSC::VM*, void*);

    JSHeapData& heapData() { return *m_heapData; }
    BunBuiltinNames& builtinNames() { return m_builtinNames; }
    JSBuiltinFunctions& builtinFunctions() { return m_builtinFunctions; }

    String overrideSourceURL(const StackFrame&, const String& originalSourceURL) const
    {
        return originalSourceURL;
    }

    WebCore::DOMWrapperWorld& normalWorld() { return *m_normalWorld; }

    JSC::GCClient::IsoSubspace& domConstructorSpace() { return m_domConstructorSpace; }

    ExtendedDOMClientIsoSubspaces& clientSubspaces() { return *m_clientSubspaces.get(); }

    Vector<JSC::IsoSubspace*>& outputConstraintSpaces() { return m_outputConstraintSpaces; }

    JSC::GCClient::IsoSubspace& domBuiltinConstructorSpace() { return m_domBuiltinConstructorSpace; }

    WebCore::HTTPHeaderIdentifiers& httpHeaderIdentifiers();

    template<typename Func> void forEachOutputConstraintSpace(const Func& func)
    {
        for (auto* space : m_outputConstraintSpaces)
            func(*space);
    }

    void* bunVM;
    Bun::JSCTaskScheduler deferredWorkTimer;

private:
    bool isWebCoreJSClientData() const final { return true; }

    BunBuiltinNames m_builtinNames;
    JSBuiltinFunctions m_builtinFunctions;

    JSHeapData* m_heapData;

    RefPtr<WebCore::DOMWrapperWorld> m_normalWorld;
    JSC::GCClient::IsoSubspace m_domConstructorSpace;
    JSC::GCClient::IsoSubspace m_domBuiltinConstructorSpace;
    JSC::GCClient::IsoSubspace m_domNamespaceObjectSpace;

    std::unique_ptr<ExtendedDOMClientIsoSubspaces> m_clientSubspaces;
    Vector<JSC::IsoSubspace*> m_outputConstraintSpaces;

    std::optional<WebCore::HTTPHeaderIdentifiers> m_httpHeaderIdentifiers;
};

} // namespace WebCore

SPECIALIZE_TYPE_TRAITS_BEGIN(WebCore::JSVMClientData)
static bool isType(const JSC::VM::ClientData& clientData) { return clientData.isWebCoreJSClientData(); }
SPECIALIZE_TYPE_TRAITS_END()

namespace WebCore {

template<typename T, UseCustomHeapCellType useCustomHeapCellType, typename GetClient, typename SetClient, typename GetServer, typename SetServer>
ALWAYS_INLINE JSC::GCClient::IsoSubspace* subspaceForImpl(JSC::VM& vm, GetClient getClient, SetClient setClient, GetServer getServer, SetServer setServer, JSC::HeapCellType& (*getCustomHeapCellType)(JSHeapData&) = nullptr)
{
    auto& clientData = *downcast<JSVMClientData>(vm.clientData);
    auto& clientSubspaces = clientData.clientSubspaces();
    if (auto* clientSpace = getClient(clientSubspaces))
        return clientSpace;

    auto& heapData = clientData.heapData();
    Locker locker { heapData.lock() };

    auto& subspaces = heapData.subspaces();
    JSC::IsoSubspace* space = getServer(subspaces);
    if (!space) {
        JSC::Heap& heap = vm.heap;
        std::unique_ptr<JSC::IsoSubspace> uniqueSubspace;
        static_assert(useCustomHeapCellType == UseCustomHeapCellType::Yes || std::is_base_of_v<JSC::JSDestructibleObject, T> || T::needsDestruction == JSC::DoesNotNeedDestruction);
        if constexpr (useCustomHeapCellType == UseCustomHeapCellType::Yes)
            uniqueSubspace = makeUnique<JSC::IsoSubspace> ISO_SUBSPACE_INIT(heap, getCustomHeapCellType(heapData), T);
        else {
            if constexpr (std::is_base_of_v<JSC::JSDestructibleObject, T>)
                uniqueSubspace = makeUnique<JSC::IsoSubspace> ISO_SUBSPACE_INIT(heap, heap.destructibleObjectHeapCellType, T);
            else
                uniqueSubspace = makeUnique<JSC::IsoSubspace> ISO_SUBSPACE_INIT(heap, heap.cellHeapCellType, T);
        }
        space = uniqueSubspace.get();
        setServer(subspaces, WTFMove(uniqueSubspace));

        IGNORE_WARNINGS_BEGIN("unreachable-code")
        IGNORE_WARNINGS_BEGIN("tautological-compare")
        void (*myVisitOutputConstraint)(JSC::JSCell*, JSC::SlotVisitor&) = T::visitOutputConstraints;
        void (*jsCellVisitOutputConstraint)(JSC::JSCell*, JSC::SlotVisitor&) = JSC::JSCell::visitOutputConstraints;
        if (myVisitOutputConstraint != jsCellVisitOutputConstraint)
            heapData.outputConstraintSpaces().append(space);
        IGNORE_WARNINGS_END
        IGNORE_WARNINGS_END
    }

    auto uniqueClientSubspace = makeUnique<JSC::GCClient::IsoSubspace>(*space);
    auto* clientSpace = uniqueClientSubspace.get();
    setClient(clientSubspaces, WTFMove(uniqueClientSubspace));
    return clientSpace;
}

// template<typename T, UseCustomHeapCellType useCustomHeapCellType, typename GetClient, typename SetClient, typename GetServer, typename SetServer>
// ALWAYS_INLINE JSC::GCClient::IsoSubspace* subspaceForImpl(JSC::VM& vm, GetClient getClient, SetClient setClient, GetServer getServer, SetServer setServer, JSC::HeapCellType& (*getCustomHeapCellType)(JSHeapData&) = nullptr)
// {
//     static NeverDestroyed<JSC::IsoSubspacePerVM> perVM([](JSC::Heap& heap) {
//         return ISO_SUBSPACE_PARAMETERS(heap.destructibleObjectHeapCellType, T);
//     });
//     return &perVM.get().clientIsoSubspaceforVM(vm);
// }

static JSVMClientData* clientData(JSC::VM& vm)
{
    return downcast<JSVMClientData>(vm.clientData);
}

static inline BunBuiltinNames& builtinNames(JSC::VM& vm)
{
    return clientData(vm)->builtinNames();
}

} // namespace WebCore

inline void* bunVM(JSC::VM& vm)
{
    return WebCore::clientData(vm)->bunVM;
}

namespace WebCore {
using JSVMClientData = WebCore::JSVMClientData;
using JSHeapData = WebCore::JSHeapData;

}
