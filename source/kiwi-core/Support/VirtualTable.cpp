/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "VirtualTable.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "../ModuleImpl.hpp"
#include "../ContextImpl.hpp"
#include <llvm/Module.h>
#include <llvm/Constant.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalVariable.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include "kiwi-runtime/gc.h"

using namespace kiwi;

namespace {
    class VirtualSlot {
    protected:
        VirtualTable& m_vtable;

        VirtualSlot(VirtualTable& vtable);
    };

    class CreateSlot : public VirtualSlot {
    public:
        CreateSlot(VirtualTable& vtable);

        void operator()(MethodPtr method);
    };

    class OverrideSlot : public VirtualSlot {
    public:
        OverrideSlot(VirtualTable& vtable);

        void operator()(MethodPtr method, MethodPtr second);
    };
}

VirtualSlot::VirtualSlot(VirtualTable& vtable)
: m_vtable(vtable) {
}

CreateSlot::CreateSlot(VirtualTable& vtable)
: VirtualSlot(vtable) {
}

OverrideSlot::OverrideSlot(VirtualTable& vtable)
: VirtualSlot(vtable) {
}

void CreateSlot::operator()(MethodPtr method) {
}

void OverrideSlot::operator()(MethodPtr method, MethodPtr second) {
}

VirtualTable::VirtualTable(Type* owner, ModulePtr module)
: MemberSet<Method>(owner), m_backendVariable(0), m_lastSize(0), m_lastPosition(0) {
    /// Create stub for address map
    llvm::Module* backendModule = module->getMetadata()->getBackendModule();
    llvm::LLVMContext& context  = backendModule->getContext();
    llvm::Type* offsetType      = llvm::Type::getInt8Ty(context)->getPointerTo();
    llvm::Type* vtableStub      = llvm::ArrayType::get(offsetType, 0);
    llvm::Type* vtableType      = vtableStub->getPointerTo();

    /// Store stub variable
    llvm::Constant* nullValue = llvm::Constant::getNullValue(vtableType);
    m_backendVariable = new llvm::GlobalVariable(*backendModule, vtableType, false, llvm::GlobalValue::PrivateLinkage, nullValue, "::_vtable");

    /// Structure includes
    onInsert.connect(CreateSlot(*this));
    onOverride.connect(OverrideSlot(*this));

    /// @todo add root to m_backendVariable
}

int32_t VirtualTable::nextPosition() {
    return m_lastPosition++;
}

void VirtualTable::update() {
    m_backendVariable->setName(m_owner->getName() + "::_vtable");

    if (m_lastSize != size()) {
        void** newVtable = (void**) kiwi_malloc_atomic(sizeof(void*) * size());
        int32_t loc = m_lastSize;
        for (const_iterator i = begin(); i != end(); ++i) {
            MethodPtr method = *i;
            // load position
            int32_t pos = method->getPosition();
            if (pos == -1) {
                method->setPosition(nextPosition());
            }
            // store information
            newVtable[pos] = method->getPointerTo();
        }

        // map vtable to pointer
        ContextImpl* meta             = m_owner->getContext()->getMetadata();
        llvm::ExecutionEngine* engine = meta->getBackendEngine();
        void** pointer                = (void**) engine->getPointerToGlobal(m_backendVariable);

        // store pointer to new vtable
        *pointer   = newVtable;
        m_lastSize = size();
    }
}
