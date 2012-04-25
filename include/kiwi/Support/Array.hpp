#ifndef KIWI_SUPPORT_ARRAY_INCLUDED
#define KIWI_SUPPORT_ARRAY_INCLUDED

#include "kiwi/config.hpp"
#include <vector>
#include <stdarg.h>

namespace kiwi {
    /// simple check if object is instance of class B
    template<typename E>
    inline std::vector<E*> makeVector(E* first, ...) {
        std::vector<E*> result;
        if (first != 0) {
            result.push_back(first);
        }
        va_list vl;
        va_start( vl, first );

        // Step through the list.
        size_t i;
        E* next = va_arg( vl, E* );
        while (next != 0) {
            result.push_back(next);
            next = va_arg( vl, E* );
        }
        va_end( vl );
        return result;
    }

    template<typename E>
    inline std::vector<E*> makeVector(E* first, std::vector<E*> last) {
        std::vector<E*> result;
        result.push_back(first);
        result.insert(result.end(), last.begin(), last.end());
        return result;
    }
}

#endif
