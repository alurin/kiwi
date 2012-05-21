/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "AncestorMetadata.hpp"

using namespace kiwi;

//==------------------------------------------------------------------------==//
AncestorMetadata::AncestorMetadata(Ancestor* owner)
: m_owner(owner), m_amap(0), m_vtable(0) {
}

AncestorMetadata::~AncestorMetadata() {
    delete m_amap;
    delete m_vtable;
}

/// return dynamic address map
AddressMap& AncestorMetadata::getAddressMap() const {
    if (!m_amap) {
        m_amap = new UpcastAddressMap(getAncestorType(), getDerivedType());
        m_amap->update();
    }
    return *m_amap;
}

/// return dynamic virtual table
VirtualTable& AncestorMetadata::getVirtualTable() const {
    if (!m_vtable) {
        UpcastVirtualTable* vtable
            = new UpcastVirtualTable(getAncestorType(), getDerivedType());
        m_vtable = vtable;
        vtable->update();
    }
    return *m_vtable;
}
