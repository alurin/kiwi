/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Ancestor.hpp"
#include "Support/AncestorMetadata.hpp"

using namespace kiwi;

// constructor
Ancestor::Ancestor(TypePtr derivedType, TypePtr ancestorType)
: m_derivedType(derivedType), m_ancestorType(ancestorType), m_meta(new AncestorMetadata(this)) {

}

Ancestor::~Ancestor() {
    delete m_meta;
}