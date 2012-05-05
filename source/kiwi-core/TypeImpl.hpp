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
#include "Support/VirtualTable.hpp"
#include "Support/AddressMap.hpp"

namespace llvm {
    class Type;
}

namespace kiwi {
    class Field;
    class Method;
    class Type;

//==------------------------------------------------------------------------==//

    /// Storage for internal members of type
    class TypeImpl {
        friend class Type;
    public:
        /// LLVM analog
        llvm::Type* varType;

        /// insert base type
        void insertBase(TypePtr type);

        /// insert base type
        bool isBase(const TypePtr type) const;

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

        /// virtual table
        VirtualTable& getVirtualTable() {
            return *m_virtualTable;
        }

        /// address map
        AddressMap& getAddressMap() {
            return *m_addressMap;
        }
    protected:
        /// Owner for this implementation
        Type* m_owner;

        /// set of all based types [ struct and objects ]
        std::set<TypePtr> m_bases;

        /// set of fields
        MemberSet<Field>* m_fields;

        /// set of methods
        MemberSet<Method>* m_methods;

        /// virtual table
        VirtualTable* m_virtualTable;

        /// address map
        AddressMap* m_addressMap;
    private:
        /// Constructor
        TypeImpl(Type* owner);

        /// destructor
        ~TypeImpl();
    };

}

#endif
