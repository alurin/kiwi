/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_ADDRESSMAP_INTERNAL
#define KIWI_SUPPORT_ADDRESSMAP_INTERNAL

#include "DynamicTable.hpp"

namespace kiwi {
    /// Base type for dynamic address maps
    class AddressMap {
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
        void* getPointer() const;

        /// update layout
        void update();

        /// dump dynamic table
        void dump() const;

        /// returns size of address map
        size_t size() const;
    protected:
        DynamicTable<int64_t> m_dtable;

        /// type that uses this dynamic table
        TypeWeak m_type;

        /// module owned this dynamic table
        ModuleWeak m_module;

        /// constructor
        AddressMap(TypePtr type, ModulePtr module);

        virtual void computeLayoutOffsets(
            llvm::StructType* layoutType,
            std::vector<llvm::Constant*>& positions
        ) =0;
    };

    /// Static dynamic address map for type
    class StaticAddressMap : public AddressMap {
        friend class TypeImpl;
        friend class Field;
    protected:
        // constructor
        StaticAddressMap(TypePtr owner);

        /// insert method in vtable
        void insertSlot(FieldPtr field);

        virtual void computeLayoutOffsets(
            llvm::StructType* layoutType,
            std::vector<llvm::Constant*>& positions
        );
    };

    /// Upcast dynamic address map from derived type to ancestor type
    class UpcastAddressMap : public AddressMap {
        friend class AncestorMetadata;
    public:
        /// returns derived type
        TypePtr getDerivedType() const {
            return m_derived.lock();
        }
    protected:
        TypeWeak m_derived;

        /// constructor
        UpcastAddressMap(TypePtr ancestor, TypePtr derived);

        virtual void computeLayoutOffsets(
            llvm::StructType* layoutType,
            std::vector<llvm::Constant*>& positions
        );
    };
}

#endif  /* DYNAMICTABLE_HPP */
