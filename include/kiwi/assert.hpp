#ifndef KIWI_ASSERT_INCLUDED
#define KIWI_ASSERT_INCLUDED

#include "kiwi/config.hpp"

#ifdef KIWI_DEBUG
#   include <assert.h>
    /// Assertion
#   define kiwi_assert(_expr, _message) assert((_expr) && _message);
#else
    /// Dummy assert
#   define kiwi_assert(_expr, _message)
#endif

#ifdef KIWI_DEBUG
#   include <iostream>

#   define ANSI_COLOR_RED     "\x1b[31m"
#   define ANSI_COLOR_GREEN   "\x1b[32m"
#   define ANSI_COLOR_YELLOW  "\x1b[33m"
#   define ANSI_COLOR_BLUE    "\x1b[34m"
#   define ANSI_COLOR_MAGENTA "\x1b[35m"
#   define ANSI_COLOR_CYAN    "\x1b[36m"
#   define ANSI_COLOR_RESET   "\x1b[0m"

#   define KIWI_DUMP(__message) std::cerr \
            << ANSI_COLOR_MAGENTA   << __FILE__ << ":" << __LINE__ << ": " \
            << ANSI_COLOR_RED       << __message \
            << ANSI_COLOR_RESET     << std::endl
#else
#   define KIWI_DUMP(__message)
#endif

/// @todo Runtime assertion
#define kiwi_runtime_assert(_expr, _message) assert((_expr) && _message);

#endif
