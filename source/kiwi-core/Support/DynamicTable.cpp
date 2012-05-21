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
    T** pointer = (T**) getPointer();
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
