/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Argument.hpp"

using namespace kiwi;

// constructor
Argument::Argument(Callable* owner, TypePtr type, int32_t position)
: m_owner(owner), m_type(type) { }
