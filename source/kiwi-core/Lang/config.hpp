#ifndef KIWI_LANG_CONFIG_INTERNAL
#define KIWI_LANG_CONFIG_INTERNAL

#include "kiwi/config.hpp"
#include "kiwi/types.hpp"
#include "kiwi/Exception.hpp"
#include "location.hh"

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
