/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_DYNAMICTABLE_INTERNAL
#define KIWI_SUPPORT_DYNAMICTABLE_INTERNAL

#include "kiwi/Type.hpp"

namespace llvm {
    class GlobalVariable;
    class Type;
    class StructType;
    class Constant;
}

namespace kiwi {
    /**
     * Base for dynamic tables, e.g: virtual tables and address maps (static or
     * up-casted)
     *
     * @tparam Member   Classof member
     * @tparam T        Type for vector element
     */
    template<typename T>
    class DynamicTable {
    public:
        /// constructor
        DynamicTable(ModulePtr module);

        /// destructor
        ~DynamicTable();

        /// return backend global variable for store dynamic table
        llvm::GlobalVariable* getBackendVariable() const {
            return m_backendVariable;
        }

        /// returns module
        ModulePtr getModule() const {
            return m_module.lock();
        }

        /// return pointer for dynamic table
        void* getNativePointer() const;

        /// return position of last empty slot and move pointer to next
        int32_t nextPosition();

        /// return size of dynamic table
        size_t size() const {
            return m_size;
        }

        /// return capacity of dynamic table
        size_t capacity() const {
            return m_capacity;
        }

        /// resize dynamic table
        void resize(size_t size);

        /// accessor
        T* get() const {
            return m_dtable;
        }

        /// accessor
        T& operator[](int32_t i) {
            kiwi_assert(0 <= i && i < m_capacity, "Index is out of array bounds");
            kiwi_assert(m_dtable, "Dynamic table is not allocated");
            return m_dtable[i];
        }

        /// accessor
        const T operator[](int32_t i) const {
            kiwi_assert(0 <= i && i < m_capacity, "Index is out of array bounds");
            kiwi_assert(m_dtable, "Dynamic table is not allocated");
            return m_dtable[i];
        }
    protected:
        /// module owned this dynamic table
        ModuleWeak m_module;

        /// global variable for store pointer to dynamic table
        llvm::GlobalVariable* m_backendVariable;

        /// dynamic table
        T* m_dtable;

        /// count of slots in dynamic table
        size_t m_size;

        /// capacity of dynamic table
        size_t m_capacity;
    };

//    //==------------------------------------------------------------------------==//
//    /// Dynamic table (virtual table, address map, e.t.c)
//    class DynamicTable {
//    public:
//        /// return next position from virtual table
//        int32_t nextPosition();
//
//        /// return backend global variable
//        llvm::GlobalVariable* getBackendVariable() const {
//            return m_backendVariable;
//        }
//
//        /// return pointer for virtual table
//        void* getPointer();
//
//        /// size of dynamic table
//        size_t size() const {
//            return m_lastSize;
//        }
//    protected:
//        /// owner info for table
//        AncestorMetadata* m_owner;
//
//        /// global variable for store pointer to vtable
//        llvm::GlobalVariable* m_backendVariable;
//
//        /// size of last vtable
//        size_t m_lastSize;
//
//        /// last position
//        size_t m_lastPosition;
//
//        /// constructor
//        DynamicTable(AncestorMetadata* info);
//
//        /// create backend variable
//        void createBackendVariable(std::string name, llvm::Type* type);
//
//        /// update global variable pointer
//        void updateGlobalVariableValue(void* newArray);
//    };
//
////==------------------------------------------------------------------------==//
//    /// Dynamic address map
//    class AddressMap : public DynamicTable {
//    public:
//        /// constructor
//        AddressMap(AncestorMetadata* info);
//
//        /// allocate new slot for field
//        ///
//        /// @internal
//        int32_t allocaSlot(FieldPtr field);
//
//        /// override slot for field
//        ///
//        /// @internal
//        int32_t overrideMember(FieldPtr field, FieldPtr inherit);
//
//        /// resize dynamic table to size
//        ///
//        /// @internal
//        void resize(size_t size);
//
//        ///
//        void update();
//        /// dump address map
//        void dump();
//    protected:
//        int64_t *m_amap;
//
//        size_t m_offset;
//        size_t m_sizeof;
//    };
//
////==------------------------------------------------------------------------==//
//    /// Dynamic virtual table
//    class VirtualTable : public DynamicTable {
//    public:
//        /// constructor
//        VirtualTable(AncestorMetadata* info);
//
//        /// allocate new slot for method
//        ///
//        /// @internal
//        int32_t allocaSlot(MethodPtr method);
//
//        /// override slot for method
//        ///
//        /// @internal
//        int32_t overrideMember(MethodPtr method, MethodPtr inherit);
//
//        /// set pointer to method
//        ///
//        /// @internal
//        void updateSlot(MethodPtr method);
//
//        /// resize dynamic table to size
//        ///
//        /// @internal
//        void resize(size_t size);
//
//        /// dump virtual table
//        void dump();
//    protected:
//        void** m_vtable;
//    };
}

#endif	/* DYNAMICTABLE_HPP */

