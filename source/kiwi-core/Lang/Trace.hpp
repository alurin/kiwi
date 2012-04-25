#ifndef KIWI_LANG_TRACE_INTERNAL
#define KIWI_LANG_TRACE_INTERNAL

#ifdef KIWI_DEBUG
#   include <iostream>
#   define KIWI_TRACE_BEGIN(__name, __expr) std::cerr << __name << ":" << __expr << "\n";
#   define KIWI_TRACE_DUMP(__name, __expr)  std::cerr << "  -- [" << __name << "] " << __expr << "\n";
#else
#   define KIWI_TRACE_BEGIN(__name, __expr)
#   define KIWI_TRACE_DUMP(__name, __expr)
#endif

#endif
