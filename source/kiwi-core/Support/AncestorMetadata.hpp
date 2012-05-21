/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_ANCESTORMETADATA_INTERNAL
#define KIWI_SUPPORT_ANCESTORMETADATA_INTERNAL

#include "AddressMap.hpp"
#include "VirtualTable.hpp"
#include "kiwi/Ancestor.hpp"
#include "MemberSet.hpp"

namespace kiwi {
//==------------------------------------------------------------------------==//
    /// Internal storage for inheritance information.
    class AncestorMetadata {
    public:
        /// constructor
        AncestorMetadata(Ancestor* m_owner);

        /// destuctor
        ~AncestorMetadata();

        /// returns ancestor
        Ancestor* getAncestor() const {
            return m_owner;
        }

        /// returns original type
        TypePtr getAncestorType() const {
            return getAncestor()->getAncestorType();
        }

        /// returns derived type(owner)
        TypePtr getDerivedType() const {
            return getAncestor()->getDerivedType();
        }

        /// return dynamic address map
        AddressMap& getAddressMap() const;

        /// return dynamic virtual table
        VirtualTable& getVirtualTable() const;
    protected:
        /// Ancestor week pointer
        Ancestor* m_owner;

        /// Address map
        mutable AddressMap* m_amap;

        /// Virtual table
        mutable VirtualTable* m_vtable;
    };
}

#endif
