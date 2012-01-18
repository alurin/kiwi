/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_STRING_HPP_INCLUDED
#define KIWI_STRING_HPP_INCLUDED

#include "kiwi/Config.hpp"
#include "string.h"
#include <unicode/unistr.h>

namespace kiwi {
    /// @todo Replace unicode string for other
    typedef UnicodeString String;
    typedef std::string   Path;
}

#endif