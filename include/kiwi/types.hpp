/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_TYPES_HPP_INCLUDED
#define KIWI_TYPES_HPP_INCLUDED

#include "kiwi/config.hpp"
#include "string.h"
#include "stdint.h"
#include <unicode/unistr.h>

namespace kiwi {
    typedef UnicodeString   String;
    typedef std::string     Path;
    typedef std::string     Identifier;
}

#endif
