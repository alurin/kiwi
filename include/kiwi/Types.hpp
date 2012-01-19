/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_TYPES_HPP_INCLUDED
#define KIWI_TYPES_HPP_INCLUDED

#include "kiwi/Machine.hpp"

#include "string.h"
#include "stdint.h"
#include <unicode/unistr.h>

namespace kiwi {
    /// @todo Replace unicode string for other
    typedef UnicodeString String;
    typedef std::string   Path;
}

#endif