/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "InheritanceInfo.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Exception.hpp"
#include "../TypeImpl.hpp"
#include "../ModuleImpl.hpp"
#include "../ContextImpl.hpp"
#include <llvm/Module.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalVariable.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include "kiwi-runtime/gc.h"

using namespace kiwi;

namespace {
    /// Storage for base information about member
    template<typename Table>
    class VirtualSlot {
    protected:
        Table& m_dtable;

        /// constructor
        VirtualSlot(Table& dtable);
    };

    /// Create dynamic table slot
    template<typename Table, typename Member>
    class CreateSlot : public VirtualSlot<Table> {
    public:
        CreateSlot(Table& dtable);

        void operator()(boost::shared_ptr<Member> method);
    };

    /// Override dynamic table slot
    template<typename Table, typename Member>
    class OverrideSlot : public VirtualSlot<Table> {
    public:
        OverrideSlot(Table& dtable);

        void operator()(boost::shared_ptr<Member> method, boost::shared_ptr<Member> second);
    };

    /// Override dynamic table slot
    class CompleteSlot : public VirtualSlot<VirtualTable> {
    public:
        CompleteSlot(VirtualTable& dtable);

        void operator()(MethodPtr method);
    };
}

//==------------------------------------------------------------------------==//
//
template<typename Table>
VirtualSlot<Table>::VirtualSlot(Table& dtable)
: m_dtable(dtable) {
}

template<typename Table, typename Member>
CreateSlot<Table, Member>::CreateSlot(Table& dtable)
: VirtualSlot<Table>(dtable) {
}

template<typename Table, typename Member>
OverrideSlot<Table, Member>::OverrideSlot(Table& dtable)
: VirtualSlot<Table>(dtable) {
}

CompleteSlot::CompleteSlot(VirtualTable& dtable)
: VirtualSlot<VirtualTable>(dtable) {
}

template<typename Table, typename Member>
void CreateSlot<Table, Member>::operator()(boost::shared_ptr<Member> method) {
    VirtualSlot<Table>::m_dtable.allocaSlot(method);
}

template<typename Table, typename Member>
void OverrideSlot<Table, Member>::operator()(boost::shared_ptr<Member> method, boost::shared_ptr<Member> second) {
    VirtualSlot<Table>::m_dtable.overrideMember(method, second);
}

void CompleteSlot::operator()(MethodPtr method) {
    VirtualSlot<VirtualTable>::m_dtable.updateSlot(method);
}

/// conect event listeners for member set
template<typename Table, typename Member>
void connect(Table& table, MemberSet<Member>& members, MemberSet<Member>& members2) {
    members.onInsert.connect(CreateSlot<Table, Member>(table));
    members2.onOverride.connect(OverrideSlot<Table, Member>(table));
    if (table.size() != members.size()) {
        table.resize(members.size());
        for (typename MemberSet<Member>::const_iterator i = members.begin(); i != members.end(); ++i) {
            boost::shared_ptr<Member> member = *i;
            table.allocaSlot(member);
        }
    }
}

/// resize dynamic array
template<typename T>
T* da_resize(T* array, size_t size) {
    // create new pointer
    T* newArray = (T*) kiwi_malloc_atomic(sizeof(T) * size);
    if (array != 0) {
        /// @todo add memcpy
    }
    return newArray;
}

//==------------------------------------------------------------------------==//
DynamicTable::DynamicTable(InheritanceInfo* owner)
: m_owner(owner), m_backendVariable(0), m_lastSize(0), m_lastPosition(0) {

}

int32_t DynamicTable::nextPosition() {
    return m_lastPosition++;
}

// create backend variable
void DynamicTable::createBackendVariable(std::string name, llvm::Type* type) {
    /// Create stub for address map
    llvm::Module* backendModule  = m_owner->getDerivedType()->getModule()->getMetadata()->getBackendModule();
    llvm::LLVMContext& context   = backendModule->getContext();
    llvm::Type* dynamicArrayType = llvm::ArrayType::get(type, 0);
    llvm::Type* dynamicArrayPtr  = dynamicArrayType->getPointerTo();
    llvm::Constant* nullValue    = llvm::Constant::getNullValue(dynamicArrayPtr);
    m_backendVariable            = new llvm::GlobalVariable(*backendModule, dynamicArrayPtr, false, llvm::GlobalValue::PrivateLinkage, nullValue, "::_amap");
}

void* DynamicTable::getPointer() {
    // map table to pointer
    ContextImpl* meta             = m_owner->getOriginalType()->getContext()->getMetadata();
    llvm::ExecutionEngine* engine = meta->getBackendEngine();
    return engine->getPointerToGlobal(m_backendVariable);
}

void DynamicTable::setArrayPointer(void* newArray) {
    // store pointer to new table
    void** pointer = (void**) getPointer();
    *pointer  = newArray;
}

//==------------------------------------------------------------------------==//
AddressMap::AddressMap(InheritanceInfo* owner)
: DynamicTable(owner), m_amap(0) {
    // Create stub for address map
    llvm::Module* backendModule = m_owner->getDerivedType()->getModule()->getMetadata()->getBackendModule();
    llvm::LLVMContext& context  = backendModule->getContext();
    llvm::Type* offsetType      = llvm::Type::getInt64Ty(context);
    createBackendVariable("::_amap", offsetType);
    connect(*this, owner->getOriginalType()->getMetadata()->fields(), owner->getDerivedType()->getMetadata()->fields());
}

// allocate new slot for field
int32_t AddressMap::allocaSlot(FieldPtr field) {
}

void AddressMap::update() {
    llvm::LLVMContext& context = m_owner->getOriginalType()->getContext()->getMetadata()->getBackendContext();
    llvm::Module*       module = m_owner->getOriginalType()->getModule()->getMetadata()->getBackendModule();

    // original
    if (m_owner->getOriginalType() == m_owner->getDerivedType()) {
        MemberSet<Field>& fields = m_owner->getOriginalType()->getMetadata()->fields();
        if (fields.size() == 0) {
            return;
        }

        std::vector<llvm::Type*> elements;
        elements.push_back(llvm::IntegerType::get(context, 8)->getPointerTo());
        for (MemberSet<Field>::const_iterator i = fields.begin(); i != fields.end(); ++i) {
            FieldPtr field = *i;
            elements.push_back(field->getFieldType()->getMetadata()->getBackendVariableType());
        }
        llvm::StructType* layoutType = llvm::StructType::get(context, elements, false);

        ///
        std::vector<llvm::Constant*> positions(fields.size(), 0);
        int j = 0;
        for (MemberSet<Field>::const_iterator i = fields.begin(); i != fields.end(); ++i, ++j) {
            FieldPtr field = *i;
            int32_t pos    = field->getPosition();
            if (pos == -1) {
                pos = nextPosition();
                field->setPosition(pos);
            }
            positions[pos] = llvm::ConstantExpr::getOffsetOf(layoutType, j + 1);
        }

        llvm::Type* offsetType    = llvm::IntegerType::get(context, 64);
        llvm::ArrayType* amapType = llvm::ArrayType::get(offsetType, positions.size());
        llvm::Constant* amapValue = llvm::ConstantArray::get(amapType, positions);

        // map table to pointer
        kiwi_assert(m_amap, "AMap is not nullable");
        ContextImpl* meta             = m_owner->getOriginalType()->getContext()->getMetadata();
        llvm::ExecutionEngine* engine = meta->getBackendEngine();
        engine->InitializeMemory(amapValue, m_amap);
    } else {
        BOOST_THROW_EXCEPTION(Exception() << exception_message("Not implemented"));

        MemberSet<Field>& fields = m_owner->getOriginalType()->getMetadata()->fields();
        MemberSet<Field>& owned  = m_owner->getDerivedType()->getMetadata()->fields();
        for (MemberSet<Field>::const_iterator i = fields.begin(); i != fields.end(); ++i) {
            FieldPtr field    = *i;

            // FieldPtr override = owned->
        }
    }
}

// override slot for field
int32_t AddressMap::overrideMember(FieldPtr field, FieldPtr inherit) {
    BOOST_THROW_EXCEPTION(Exception() << exception_message("Not implemented"));
}

// resize dynamic table to size
void AddressMap::resize(size_t size) {
    if (m_lastSize < size) {
        m_lastSize = size;
        m_amap     = da_resize<int64_t>(m_amap, size);
        setArrayPointer(m_amap);
    }
}

//==------------------------------------------------------------------------==//
VirtualTable::VirtualTable(InheritanceInfo* owner)
: DynamicTable(owner), m_vtable(0) {
    /// Create stub for virtual table
    llvm::Module* backendModule = m_owner->getDerivedType()->getModule()->getMetadata()->getBackendModule();
    llvm::LLVMContext& context  = backendModule->getContext();
    llvm::Type* pointerType     = llvm::Type::getInt8Ty(context)->getPointerTo();
    createBackendVariable("::_vtable", pointerType);
    connect(*this, owner->getOriginalType()->getMetadata()->methods(), owner->getDerivedType()->getMetadata()->methods());
    owner->getDerivedType()->getMetadata()->onMethodComplete.connect(CompleteSlot(*this));
}

// allocate new slot for method
int32_t VirtualTable::allocaSlot(MethodPtr method) {
    int32_t pos = method->getPosition();
    if (pos == -1) {
        pos = nextPosition();
        method->setPosition(pos);
    }

    if (pos >= size()) {
        resize(size() * 1.5);
    }
    updateSlot(method);
}

// override slot for method
int32_t VirtualTable::overrideMember(MethodPtr method, MethodPtr inherit) {
    BOOST_THROW_EXCEPTION(Exception() << exception_message("Not implemented"));
}

// set pointer to method
void VirtualTable::updateSlot(MethodPtr method) {
    int32_t pos = method->getPosition();
    kiwi_assert(pos != -1, "Position must be set before update vtable slot");

    if (m_owner->getOriginalType() == m_owner->getDerivedType()) {
        m_vtable[pos] = method->getPointerTo();
    } else {
        method = m_owner->getDerivedType()->getMetadata()->methods().find(method);
        kiwi_assert(method, "Overridable method not found");
        m_vtable[pos] = method->getPointerTo();
    }
}

// resize dynamic table to size
void VirtualTable::resize(size_t size) {
    if (m_lastSize < size) {
        m_lastSize = size;
        m_vtable   = da_resize<void*>(m_vtable, size);
        setArrayPointer(m_vtable);
    }
}

//==------------------------------------------------------------------------==//
InheritanceInfo::InheritanceInfo(Type* original, Type* derived)
: m_original(original), m_derived(derived), m_amap(0), m_vtable(0) {
}

/// return dynamic address map
AddressMap& InheritanceInfo::getAddressMap() const {
    if (!m_amap) {
        m_amap = new AddressMap(const_cast<InheritanceInfo*>(this));
    }
    return *m_amap;
}

/// return dynamic virtual table
VirtualTable& InheritanceInfo::getVirtualTable() const {
    if (!m_vtable) {
        m_vtable = new VirtualTable(const_cast<InheritanceInfo*>(this));
    }
    return *m_vtable;
}
