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
#include "../Support/AncestorMetadata.hpp"

using namespace kiwi;

// dump information about type
void VirtualTable::dump() const {
   bool isNotFirst = false;
   std::cerr << "vtable [" << size() << "[";
   for (int i = 0; i < size(); ++i) {
       if (isNotFirst) {
           std::cerr << ", ";
       } else {
           isNotFirst = true;
       }
       std::cerr << m_dtable[i];
   }
   std::cerr << "] at " << m_dtable.get() << std::endl;
}

// dump information about type
void AddressMap::dump() const {
   bool isNotFirst = false;
   std::cerr << "amap " << size() << "[";
   for (int i = 0; i < size(); ++i) {
       if (isNotFirst) {
           std::cerr << ", ";
       } else {
           isNotFirst = true;
       }
       std::cerr << m_dtable[i];
   }
   std::cerr << "] at " << m_dtable.get() << std::endl;
}
