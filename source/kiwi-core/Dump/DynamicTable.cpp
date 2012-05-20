/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Type.hpp"
#include "kiwi/Argument.hpp"
#include "kiwi/Members.hpp"
#include <iostream>
#include "../TypeImpl.hpp"
#include "../Support/InheritanceInfo.hpp"

using namespace kiwi;

// dump information about type
void VirtualTable::dump() {
    bool isNotFirst = false;
    std::cerr << "vtable"
              << " from " << m_owner->getDerivedType()->getName()
              << " to " << m_owner->getOriginalType()->getName()
              << ": " <<  size() << "[";
    for (int i = 0; i < size(); ++i) {
        if (isNotFirst) {
            std::cerr << ", ";
        } else {
            isNotFirst = true;
        }
        std::cerr << m_vtable[i];
    }
    std::cerr << "] at " << m_vtable << std::endl;
}
