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
#include "Support/InheritanceInfo.hpp"

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
        void insertBase(TypePtr type);

        /// insert base type
        bool isBase(const TypePtr type) const;

        /// return information about virtual table and address map for this type
        InheritanceInfo* getOriginalMetadata();

        /// return information about virtual table and address map for this or
        /// original type
        InheritanceInfo* getOriginalMetadata(TypePtr type);

        /// return set of fields
        MemberSet<Field>& fields() const {
            return *m_fields;
        }

        /// return set of methods
        MemberSet<Method>& methods() const {
            return *m_methods;
        }

        /// return iterator pointed for begin of bases
        std::set<TypePtr>::const_iterator base_begin() const {
            return m_bases.begin();
        }

        /// return iterator pointed after end of bases
        std::set<TypePtr>::const_iterator base_end() const {
            return m_bases.end();
        }

        /// Signal for complete method
        boost::signals2::signal<void (MethodPtr)> onMethodComplete;
    protected:
        /// Owner for this implementation
        Type* m_owner;

        /// set of all based types [ struct and objects ]
        std::set<TypePtr> m_bases;

        /// set of all based types [ struct and objects ]
        std::map<TypePtr, InheritanceInfo*> m_inheritances;

        /// set of fields
        MemberSet<Field>* m_fields;

        /// set of methods
        MemberSet<Method>* m_methods;

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
