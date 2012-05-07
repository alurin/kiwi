/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "VirtualTable.hpp"

using namespace kiwi;

VirtualTable::VirtualTable(Type* owner, ModulePtr module)
: MemberSet<Method>(owner), m_backendVariable(0) {

}
