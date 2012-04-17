#ifndef KIWI_CONFIG_INCLUDED
#define KIWI_CONFIG_INCLUDED

#include "string.h"
#include "stdint.h"

#include <unicode/unistr.h>

#define BOOST_NO_TYPEID

#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include <boost/enable_shared_from_this.hpp>

namespace kiwi
{
    typedef UnicodeString   String;
    typedef std::string     Path;
    typedef std::string     Identifier;
}

#endif