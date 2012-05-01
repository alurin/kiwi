/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CONFIG_INCLUDED
#define KIWI_CONFIG_INCLUDED

#include "machine.hpp"

///==--------------------------------------------------------------------------------------------------------------==///
///   Export and import declorations
///==--------------------------------------------------------------------------------------------------------------==///

#if defined _WIN32 || defined __CYGWIN__
#   define KIWI_API_IMPORT __declspec(dllimport)
#   define KIWI_API_EXPORT __declspec(dllexport)
#   define KIWI_API_LOCAL
#else
#   if __GNUC__ >= 4
#       define KIWI_API_IMPORT __attribute__ ((visibility("default")))
#       define KIWI_API_EXPORT __attribute__ ((visibility("default")))
#       define KIWI_API_LOCAL  __attribute__ ((visibility("hidden")))
#   else
#       define KIWI_API_IMPORT
#       define KIWI_API_EXPORT
#       define KIWI_API_LOCAL
#   endif
#endif

#ifdef KIWI_LIBRARY
#   ifdef KIWI_DLL_EXPORTS // defined if we are building the KIWI DLL (instead of using it)
#       define KIWI_API KIWI_API_EXPORT
#   else
#       define KIWI_API KIWI_API_IMPORT
#   endif // KIWI_DLL_EXPORTS
#endif // KIWI_DLL

/// \def KIWI_LOCAL
/// All public and exported symbols must be marked with this macros
#ifndef KIWI_LOCAL
#   define KIWI_LOCAL KIWI_API_LOCAL
#endif

/// \def KIWI_API
/// All public and exported symbols must be marked with this macros
#ifndef KIWI_API
#   define KIWI_API
#endif

/// \def KIWI_LOCAL
/// All private and hidden symbols must be marked with this macros
#ifndef KIWI_LOCAL
#   define KIWI_LOCAL
#endif

/// \def KIWI_RUNTIME
/// All internal methods mustbe marked with this macros
#ifndef KIWI_RUNTIME
#   define KIWI_RUNTIME extern "C"
#endif

///==--------------------------------------------------------------------------------------------------------------==///
///   Debug and implement declorations
///==--------------------------------------------------------------------------------------------------------------==///
#define KIWI_STRINGIFY(x) #x
#define KIWI_TOSTRING(x) KIWI_STRINGIFY(x)

/// \def KIWI_NOT_IMPLEMENT Error for development time of not implemented features
#ifdef KIWI_DEBUG
#   define KIWI_NOT_IMPLEMENT() \
        do {                                 \
            throw __FILE__ ":" KIWI_TOSTRING(__LINE__) "Not implemented";                        \
        } while (0)
#endif

///==--------------------------------------------------------------------------------------------------------------==///
///   Assert declorations
///==--------------------------------------------------------------------------------------------------------------==///
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

#endif
