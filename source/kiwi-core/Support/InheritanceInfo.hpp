/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_CASTINFO_INTERNAL
#define KIWI_SUPPORT_CASTINFO_INTERNAL

#include "kiwi/Type.hpp"
#include "MemberSet.hpp"

namespace llvm {
    class GlobalVariable;
    class Type;
}

namespace kiwi {
    class InheritanceInfo;

//==------------------------------------------------------------------------==//
    /// Dynamic table (virtual table, address map, e.t.c)
    class DynamicTable {
    public:
        /// return next position from virtual table
        int32_t nextPosition();

        /// return backend global variable
        llvm::GlobalVariable* getBackendVariable() const {
            return m_backendVariable;
        }

        /// return pointer for virtual table
        void* getPointer();

        /// size of dynamic table
        size_t size() const {
            return m_lastSize;
        }
    protected:
        /// owner info for table
        InheritanceInfo* m_owner;

        /// global variable for store pointer to vtable
        llvm::GlobalVariable* m_backendVariable;

        /// size of last vtable
        size_t m_lastSize;

        /// last position
        size_t m_lastPosition;

        /// constructor
        DynamicTable(InheritanceInfo* info);

        /// create backend variable
        void createBackendVariable(std::string name, llvm::Type* type);

        ///
        void setArrayPointer(void* newArray);
    };

    /// Dynamic address map
    class AddressMap : public DynamicTable {
    public:
        /// constructor
        AddressMap(InheritanceInfo* info);

        /// allocate new slot for field
        ///
        /// @internal
        int32_t allocaSlot(FieldPtr field);

        /// override slot for field
        ///
        /// @internal
        int32_t overrideMember(FieldPtr field, FieldPtr inherit);

        /// resize dynamic table to size
        ///
        /// @internal
        void resize(size_t size);

        ///
        void update();
        /// dump address map
        void dump();
    protected:
        int64_t *m_amap;

        size_t m_offset;
        size_t m_sizeof;
    };

//==------------------------------------------------------------------------==//
    /// Dynamic virtual table
    class VirtualTable : public DynamicTable {
    public:
        /// constructor
        VirtualTable(InheritanceInfo* info);

        /// allocate new slot for method
        ///
        /// @internal
        int32_t allocaSlot(MethodPtr method);

        /// override slot for method
        ///
        /// @internal
        int32_t overrideMember(MethodPtr method, MethodPtr inherit);

        /// set pointer to method
        ///
        /// @internal
        void updateSlot(MethodPtr method);

        /// resize dynamic table to size
        ///
        /// @internal
        void resize(size_t size);

        /// dump virtual table
        void dump();
    protected:
        void** m_vtable;
    };

//==------------------------------------------------------------------------==//
    /// Internal storage for inheritance information.
    class InheritanceInfo {
    public:
        /// constructor
        InheritanceInfo(Type* original, Type* derived);

        /// returns original type
        Type* getOriginalType() const {
            return m_original;
        }

        /// returns derived type(owner)
        Type* getDerivedType() const {
            return m_derived;
        }

        /// return dynamic address map
        AddressMap& getAddressMap() const;

        /// return dynamic virtual table
        VirtualTable& getVirtualTable() const;
    protected:
        /// Original type
        Type* m_original;

        /// Derived type(owner)
        Type* m_derived;

        /// Address map
        mutable AddressMap* m_amap;

        /// Virtual table
        mutable VirtualTable* m_vtable;
    };
}

#endif
