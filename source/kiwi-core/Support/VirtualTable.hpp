/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_VIRTUALTABLE_INTERNAL
#define KIWI_SUPPORT_VIRTUALTABLE_INTERNAL

#include "DynamicTable.hpp"

namespace kiwi {
    /// Base type for dynamic virtual tables
    class VirtualTable {
    public:
        /// returns type
        TypePtr getType() const {
            return m_type.lock();
        }

        /// returns module
        ModulePtr getModule() const {
            return m_module.lock();
        }

        /// return backend global variable for store dynamic table
        llvm::GlobalVariable* getBackendVariable() const;

        /// return pointer for dynamic table
        void* getNativePointer() const;

        /// dump dynamic table
        void dump() const;

        /// returns size of vtable
        size_t size() const;

        /// update method in vtable
        void updateSlot(MethodPtr method, void* px = 0);
    protected:
        DynamicTable<void*> m_dtable;

        /// type that uses this dynamic table
        TypeWeak m_type;

        /// module owned this dynamic table
        ModuleWeak m_module;

        /// constructor
        VirtualTable(TypePtr type, ModulePtr module);
    };

    /// Static dynamic virtual tables for type
    class StaticVirtualTable : public VirtualTable {
        friend class TypeImpl;
        friend class Method;
    public:
        /// fill dynamic table
        void update();
    protected:
        // constructor
        StaticVirtualTable(TypePtr owner);

        /// insert method in vtable
        void insertSlot(MethodPtr method);
    };

    /// Upcast dynamic virtual tables from derived type to ancestor type
    class UpcastVirtualTable : public VirtualTable {
        friend class AncestorMetadata;
    public:
        /// returns derived type
        TypePtr getDerivedType() const {
            return m_derived.lock();
        }

        /// fill dynamic table
        void update();
    protected:
        TypeWeak m_derived;

        /// constructor
        UpcastVirtualTable(TypePtr ancestor, TypePtr derived);
    };
}

#endif  /* DYNAMICTABLE_HPP */

