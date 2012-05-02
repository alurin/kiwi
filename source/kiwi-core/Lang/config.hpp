#ifndef KIWI_LANG_CONFIG_INTERNAL
#define KIWI_LANG_CONFIG_INTERNAL

#include "kiwi/config.hpp"
#include "kiwi/types.hpp"
#include "kiwi/Exception.hpp"
#include "location.hh"

#define KIWI_EXCEPTION_ADD_LOCATION(_stmt, _loc) \
    do { \
        try { \
            _stmt \
        } catch (Exception &ex) { \
            if (!boost::get_error_info<exception_location>(ex)) { \
                ex << exception_location(to_location(_loc)); \
            } \
            throw; \
        } \
    } while (false)

namespace kiwi {
namespace lang {

    inline
    Location to_location(const location& loc) {
        Position begin(loc.begin.line, loc.begin.column);
        Position end(loc.end.line, loc.end.column);
        if (loc.begin.filename) {
            return Location(*(loc.begin.filename), begin, end);
        }
        return Location("", begin, end);
    }

}}

#endif
