#ifndef KIWI_CONFIG_INCLUDED
#define KIWI_CONFIG_INCLUDED

#include <boost/preprocessor/stringize.hpp>

/*
 * AUTO-GENERATION WARNING:
 *     This file has been automatically generated from "Application.hpp.in.cmake".
 *     DO NOT edit this file, as any changes will be automatically discarded.
 */


#cmakedefine KIWI_NAME               "@KIWI_NAME@"
#cmakedefine KIWI_CODENAME           "@KIWI_CODENAME@"
#cmakedefine KIWI_COPYRIGHT_YEARS    "@KIWI_COPYRIGHT_YEARS@"
#cmakedefine KIWI_VERSION_MAJOR      @KIWI_VERSION_MAJOR@
#cmakedefine KIWI_VERSION_MINOR      @KIWI_VERSION_MINOR@
#cmakedefine KIWI_VERSION_PATCH      @KIWI_VERSION_PATCH@
#cmakedefine KIWI_VERSION_TYPE       "@KIWI_VERSION_TYPE@"
#cmakedefine KIWI_VERSION_STRING     "@KIWI_VERSION_STRING@"
#cmakedefine KIWI_VENDOR_ID          "@KIWI_VENDOR_ID@"
#cmakedefine KIWI_VENDOR_NAME        "@KIWI_VENDOR_NAME@"
#cmakedefine KIWI_VENDOR_URL         "@KIWI_VENDOR_URL@"
#cmakedefine KIWI_ID                 "@KIWI_VENDOR_ID@"

#ifndef KIWI_NAME
#   error "Please specify the application name in the top-level CMakeLists.txt file."
#endif

#ifndef KIWI_CODENAME
#   error "Please specify the application codename in the top-level CMakeLists.txt file."
#endif

#ifndef KIWI_COPYRIGHT_YEARS
#   error "Please specify the application copyright years (years during which this application was created, edited, or modified) in the top-level CMakeLists.txt file."
#endif

#ifndef KIWI_VERSION_MAJOR
#   define KIWI_VERSOIN_MAJOR 0
#endif

#ifndef KIWI_VERSION_MINOR
#   define KIWI_VERSION_MINOR 0
#endif

#ifndef KIWI_VERSION_PATCH
#   define KIWI_VERSION_PATCH 0
#endif

#ifndef KIWI_VERSION_TYPE
#   define KIWI_VERSION_TYPE "SNAPSHOT"
#endif

#ifndef KIWI_VERSION_STRING
#   define KIWI_VERSION_STRING BOOST_PP_STRINGIZE(KIWI_VERSION_MAJOR) "." BOOST_PP_STRINGIZE(KIWI_VERSION_MINOR) "." BOOST_PP_STRINGIZE(KIWI_VERSION_PATCH) "-" KIWI_VERSION_TYPE
#endif

#ifndef KIWI_VENDOR_ID
#   error "Please specify the application vendor id in the top-level CMakeLists.txt file."
#endif

#ifndef KIWI_VENDOR_NAME
#   error "Please specify the application vendor name in the top-level CMakeLists.txt file."
#endif

#ifndef KIWI_VENDOR_URL
#   error "Please specify the application vendor URL in the top-level CMakeLists.txt file."
#endif

#ifndef KIWI_ID
#   define KIWI_ID KIWI_VENDOR_ID "." KIWI_CODENAME
#endif

#endif
