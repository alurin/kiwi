#ifndef KIWI_CONFIG_INCLUDED
#define KIWI_CONFIG_INCLUDED

#include "string.h"
#include "stdint.h"

#include <unicode/unistr.h>

namespace kiwi
{
    typedef UnicodeString   String;
    typedef std::string     Path;
    typedef std::string     Identifier;
}

#endif
