/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "DynamicTable.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Exception.hpp"
#include "kiwi/Support/Iterator.hpp"
#include "../TypeImpl.hpp"
#include "../ModuleImpl.hpp"
#include "../ContextImpl.hpp"
#include <llvm/Module.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalVariable.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/Support/TypeBuilder.h>
#include "kiwi-runtime/gc.h"
#include <stdlib.h>

using namespace kiwi;
//
//namespace {
//    /// Storage for base information about member
//    template<typename Table>
//    class VirtualSlot {
//    protected:
//        Table& m_dtable;
//
//        /// constructor
//        VirtualSlot(Table& dtable);
//    };
//
//    /// Create dynamic table slot
//    template<typename Table, typename Member>
//    class CreateSlot : public VirtualSlot<Table> {
//    public:
//        CreateSlot(Table& dtable);
//
//        void operator()(boost::shared_ptr<Member> method);
//    };
//
//    /// Override dynamic table slot
//    template<typename Table, typename Member>
//    class OverrideSlot : public VirtualSlot<Table> {
//    public:
//        OverrideSlot(Table& dtable);
//
//        void operator()(boost::shared_ptr<Member> method, boost::shared_ptr<Member> second);
//    };
//
//    /// Override dynamic table slot
//    class CompleteSlot : public VirtualSlot<VirtualTable> {
//    public:
//        CompleteSlot(VirtualTable& dtable);
//
//        void operator()(MethodPtr method);
//    };
//}
//
////==------------------------------------------------------------------------==//
///// conect event listeners for member set
//template<typename Table, typename Member>
//void connectCreateSlot(Table* table, MemberSet<Member>& members) {
//   members.onInsert.connect(CreateSlot<Table, Member>(*table));
//}
///// conect event listeners for member set
//template<typename Table>
//void connectCompleteSlot(Table* table, TypePtr type) {
//    TypeImpl* meta = type->getMetadata();
//    meta->onMethodComplete.connect(CompleteSlot(*table));
//}
//
////==------------------------------------------------------------------------==//
//template<typename Table>
//VirtualSlot<Table>::VirtualSlot(Table& dtable)
//: m_dtable(dtable) {
//}
//
//template<typename Table, typename Member>
//CreateSlot<Table, Member>::CreateSlot(Table& dtable)
//: VirtualSlot<Table>(dtable) {
//}
//
//template<typename Table, typename Member>
//OverrideSlot<Table, Member>::OverrideSlot(Table& dtable)
//: VirtualSlot<Table>(dtable) {
//}
//
//CompleteSlot::CompleteSlot(VirtualTable& dtable)
//: VirtualSlot<VirtualTable>(dtable) {
//}
//
///// Insert new slot in dynamic table
//template<typename Table, typename Member>
//void CreateSlot<Table, Member>::operator()(boost::shared_ptr<Member> member) {
//    KIWI_DUMP("Create slot " << member->getName());
//    VirtualSlot<Table>::m_dtable.insertSlot(member);
//}
//
///// Override value in slot form dynamic table
//template<typename Table, typename Member>
//void OverrideSlot<Table, Member>::operator()(boost::shared_ptr<Member> member, boost::shared_ptr<Member> second) {
//    BOOST_THROW_EXCEPTION(Exception() << exception_message("Not implemented"));
//    // VirtualSlot<Table>::m_dtable.overrideMember(member, second);
//}
//
//void CompleteSlot::operator()(MethodPtr method) {
//    KIWI_DUMP("Complete slot " << method->getName());
//    VirtualSlot<VirtualTable>::m_dtable.updateSlot(method);
//}
//
//==------------------------------------------------------------------------==//
// constructor

template<typename T>
DynamicTable<T>::DynamicTable(ModulePtr module)
: m_module(module), m_dtable(0), m_size(0), m_capacity(0) {
    /// Create stub for address map
    llvm::Module* backendModule  = module->getMetadata()->getBackendModule();
    llvm::LLVMContext& context   = backendModule->getContext();
    llvm::Type* elementType      = llvm::TypeBuilder<T, false>::get(context);
    llvm::Type* dynamicArrayType = llvm::ArrayType::get(elementType, 0);
    llvm::Type* dynamicArrayPtr  = dynamicArrayType->getPointerTo();
    llvm::Constant* nullValue    = llvm::Constant::getNullValue(dynamicArrayPtr);

    m_backendVariable = new llvm::GlobalVariable(
        *backendModule,
        dynamicArrayPtr,
        false,
        llvm::GlobalValue::PrivateLinkage,
        nullValue,
        "::_dtable"
    );
}

// destructor
template<typename T>
DynamicTable<T>::~DynamicTable() {
    delete m_dtable;
}

//////==------------------------------------------------------------------------==//
// return pointer for dynamic table
template<typename T>
void* DynamicTable<T>::getPointer() const {
    // map table to pointer
    ContextImpl* meta             = getModule()->getContext()->getMetadata();
    llvm::ExecutionEngine* engine = meta->getBackendEngine();
    return engine->getPointerToGlobal(m_backendVariable);
}

//
template<typename T>
void DynamicTable<T>::resize(size_t size) {
    if (size <= m_capacity) {
        return;
    }
    size_t lastCapacity = m_capacity;
    m_capacity = size;

    // resize dtable
    T* newTable = (T*) kiwi_malloc_atomic(sizeof(T) * m_capacity);
    if (m_dtable != 0) {
        memcpy(newTable, m_dtable, sizeof(T));
    }
    m_dtable = newTable;

    // update pointer to dtable
    void** pointer = (void**) getPointer();
    *pointer = m_dtable;
}

template<typename T>
int32_t DynamicTable<T>::nextPosition() {
    int32_t pos = m_size++;
    if (m_size >= m_capacity) {
        resize(m_size * 1.4);
    }
    return pos;
}