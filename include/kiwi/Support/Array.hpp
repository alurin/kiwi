#ifndef KIWI_SUPPORT_ARRAY_INCLUDED
#define KIWI_SUPPORT_ARRAY_INCLUDED

#include "kiwi/Config.hpp"
#include <vector>
#include <stdarg.h>

namespace kiwi {
    /// simple check if object is instance of class B
    template<typename E>
    inline std::vector<E*> makeVector(E* first, ...) {
        std::vector<E*> result;
        va_list vl;
        va_start( vl, first );

        // Step through the list.
        size_t i;
        while(true) {
            E* next = va_arg( vl, E* );
            if (!next) break;
            result.push_back(next);
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
