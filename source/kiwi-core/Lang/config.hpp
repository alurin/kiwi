#ifndef KIWI_LANG_CONFIG_INTERNAL
#define KIWI_LANG_CONFIG_INTERNAL

#include "kiwi/config.hpp"
#include "kiwi/types.hpp"
#include "kiwi/Exception.hpp"
#include "location.hh"

#define KIWI_LANG_START { try {
#define KIWI_LANG_STOP(_loc)  } catch (Exception &ex) { ex << exception_location(to_location(_loc)); throw }

namespace kiwi {
namespace lang {

    inline
    Location to_location(const location& loc) {
        Position begin(loc.begin.line, loc.begin.column);
        Position end(loc.end.line, loc.end.column);
        return Location(*(loc.begin.filename), begin, end);
    }

}}

#endif
