/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_TYPEIMPL_INTERNAL
#define KIWI_TYPEIMPL_INTERNAL

#include "kiwi/Type.hpp"
#include "Support/MemberSet.hpp"
#include "Support/AncestorMap.hpp"
#include "Support/AncestorMetadata.hpp"
#include "Support/AddressMap.hpp"
#include "Support/VirtualTable.hpp"

namespace llvm {
    class Type;
}

namespace kiwi {
    class Field;
    class Method;
    class Type;
    class ThisConverter;

//==------------------------------------------------------------------------==//

    /// Storage for internal members of type
    class TypeImpl {
        friend class Type;
    public:
        /// return owner type
        TypePtr getOwner() const {
            return m_owner->shared_from_this();
        }

        /// returns LLVM analog for variables types
        llvm::Type* getBackendVariableType() const {
            return m_backendVariableType;
        }

        /// set LLVM analog for variables types
        void setBackendVariableType(llvm::Type* type) {
            m_backendVariableType = type;
        }

        /// returns LLVM anolog for stack types
        llvm::Type* getBackendThisType() const {
            if (m_backendThisType) {
                return m_backendThisType;
            }
            return getBackendVariableType();
        }

        /// set LLVM anolog for stack types
        void setBackendThisType(llvm::Type* type) {
            m_backendThisType = type;
        }

        /// LLVM pointer to type
        llvm::GlobalVariable* getBackendPointer() {
            return m_backendPointer;
        }

        /// returns this converter
        ThisConverter* getThisConverter() const {
            return m_thisConverter;
        }

        /// set this converter
        void setThisConverter(ThisConverter* converter) {
            m_thisConverter = converter;
        }

        /// insert base type
        bool addAncestor(AncestorPtr ancestor);

        /// insert base type
        bool isAncestor(const TypePtr type) const;

        /// return information about virtual table and address map for this or
        /// original type
        AncestorMetadata* getAncestorMetadata(TypePtr type);

        /// return set of fields
        MemberSet<Field>& getFields() const;

        /// return set of methods
        MemberSet<Method>& getMethods() const;

        /// return map of accestors
        AncestorMap& getAncestors() const;

        /// returns virtual table
        StaticVirtualTable& getVirtualTable() const;

        /// returns address map
        StaticAddressMap& getAddressMap() const;

        /// Signal for complete method
        boost::signals2::signal<void (MethodPtr)> onMethodComplete;
    protected:
        /// Owner for this implementation
        Type* m_owner;

        /// map for all ancestor types
        mutable AncestorMap* m_ancestors;

        /// set of fields
        mutable MemberSet<Field>* m_fields;

        /// set of methods
        mutable MemberSet<Method>* m_methods;

        /// virtual table
        mutable StaticVirtualTable* m_virtualTable;

        /// address map
        mutable StaticAddressMap* m_addressMap;

        /// this/variable converter
        ThisConverter* m_thisConverter;

        /// LLVM analog for variables types
        llvm::Type* m_backendVariableType;

        /// LLVM anolog for stack types
        llvm::Type* m_backendThisType;

        /// LLVM pointer to type
        llvm::GlobalVariable* m_backendPointer;
    private:
        /// Constructor
        TypeImpl(Type* owner, ModulePtr module);

        /// destructor
        ~TypeImpl();
    };

}

#endif
