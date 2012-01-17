#ifndef KIWI_CONFIG_HPP_INCLUDED
#define KIWI_CONFIG_HPP_INCLUDED

///==--------------------------------------------------------------------------------------------------------------==///
///   OS type declorations
///==--------------------------------------------------------------------------------------------------------------==///

#ifndef KIWI_UNIX
#   define KIWI_UNIX ${KIWI_UNIX}
#endif

#ifndef KIWI_WIN32
#   define KIWI_WIN32 ${KIWI_WIN32}
#endif

///==--------------------------------------------------------------------------------------------------------------==///
///   Build type declorations
///==--------------------------------------------------------------------------------------------------------------==///

/// \def KIWI_LIBRARY
/// All public and exported symbols must be marked with this macros
#ifndef KIWI_LIBRARY
#   define KIWI_LIBRARY ${KIWI_LIBRARY}
#endif

/// \def KIWI_DEBUG
#ifndef KIWI_DEBUG
#   define KIWI_DEBUG ${KIWI_DEBUG}
#endif

/// \def KIWI_RELEASE
#ifndef KIWI_RELEASE
#   define KIWI_RELEASE ${KIWI_RELEASE}
#endif

///==--------------------------------------------------------------------------------------------------------------==///
///   General declorations
///==--------------------------------------------------------------------------------------------------------------==///

#ifndef KIWI_NAME
#   define KIWI_NAME "${APPLICATION_NAME}"
#endif

#ifndef KIWI_CODENAME
#   define KIWI_CODENAME "${APPLICATION_CODENAME}"
#endif

#ifndef KIWI_COPYRIGHT_YEARS
#   define KIWI_COPYRIGHT_YEARS "${APPLICATION_COPYRIGHT_YEARS}"
#endif

#ifndef KIWI_VERSION_MAJOR
#   define KIWI_VERSION_MAJOR ${APPLICATION_VERSION_MAJOR}
#endif

#ifndef KIWI_VERSION_MINOR
#   define KIWI_VERSION_MINOR ${APPLICATION_VERSION_MINOR}
#endif

#ifndef KIWI_VERSION_PATCH
#   define KIWI_VERSION_PATCH ${APPLICATION_VERSION_PATCH}
#endif

#ifndef KIWI_VERSION_TYPE
#   define KIWI_VERSION_TYPE "${APPLICATION_VERSION_TYPE}"
#endif

#ifndef KIWI_VERSION_STRING
#   define KIWI_VERSION_STRING "${APPLICATION_VERSION_STRING}"
#endif

#ifndef KIWI_VENDOR_ID
#   define KIWI_VENDOR_ID "${APPLICATION_VENDOR_ID}"
#endif

#ifndef KIWI_VENDOR_NAME
#   define KIWI_VENDOR_NAME "${APPLICATION_VENDOR_NAME}"
#endif

#ifndef KIWI_VENDOR_URL
#   define KIWI_VENDOR_URL "${APPLICATION_VENDOR_URL}"
#endif

#ifndef KIWI_ID
#   define KIWI_ID "${APPLICATION_VENDOR_ID}"
#endif

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

#if KIWI_LIBRARY
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
///   Assetions
///==--------------------------------------------------------------------------------------------------------------==///

#ifndef kiwi_assert
#   include <cassert>
#   define kiwi_assert(exp) assert(exp)
#endif

#ifdef KIWI_DEBUG
#   define KIWI_DEBUG_ASSERT(exp) kiwi_assert(exp)
#else
#   define KIWI_DEBUG_ASSERT(exp) ((void)0)
#endif

#endif
