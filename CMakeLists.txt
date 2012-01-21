# Vasiliy Sheredeko. Copyright (C) 2011. MIT License.

#
# Project Properties
#
cmake_minimum_required (VERSION 2.8)

project (kiwi)
set (APPLICATION_NAME "Kiwi")
set (APPLICATION_CODENAME "${PROJECT_NAME}")
set (APPLICATION_COPYRIGHT_YEARS "2012")
set (APPLICATION_COPYRIGHT_LICENSE "MIT License")
set (APPLICATION_VERSION_MAJOR 0)
set (APPLICATION_VERSION_MINOR 1)
set (APPLICATION_VERSION_PATCH 0)
set (APPLICATION_VERSION_TYPE SNAPSHOT)
set (APPLICATION_VERSION_STRING
    "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}"
)
set (APPLICATION_VENDOR_ID "ru.kronverk-studio")
set (APPLICATION_VENDOR_NAME "Vasiliy Sheredeko")
set (APPLICATION_VENDOR_URL "kronverk-studio.ru")
set (APPLICATION_ID "${APPLICATION_VENDOR_ID}.${PROJECT_NAME}")

#
# Flags for modules and project
#
option( SHARED "Enable build for core as shared library" ON )
option( DEBUG "Enable debug build for source" ON )
#option( WITH_CONSOLE "Enable build of console application " ON )
#option( WITH_APACHE2 "Enable build of Apache 2 module" ON )

#
# Flags for builds
#

if( ${SHARED} )
    set( KIWI_LIBRARY 1 )
else( ${SHARED} )
    set( KIWI_LIBRARY 0 )
endif( ${SHARED} )

if( ${DEBUG} )
    set( KIWI_DEBUG 1 )
    set( KIWI_RELEASE 0 )
    set( CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
else( ${DEBUG} )
    set( KIWI_DEBUG  0 )
    set( KIWI_RELEASE 1 )
    set( CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif( ${DEBUG} )

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#
# OS flags
#

## Operation system detect
if (UNIX)
    set( KIWI_UNIX 1 )
    if (CMAKE_COMPILER_IS_GNUCC AND KIWI_DEBUG)
        message("-- Set GNU C++ normal arguments")
        set(CMAKE_C_FLAGS           ${CMAKE_C_FLAGS}            "-g3 -gdwarf-2 -g -O0 -Wall -pedantic")
        set(CMAKE_CXX_FLAGS         "-g3 -gdwarf-2 -g -O0 -Wall -pedantic")
        set(CMAKE_EXE_LINKER_FLAGS  "-g3 -gdwarf-2 -g -O0 -Wall -pedantic")
    endif (CMAKE_COMPILER_IS_GNUCC AND KIWI_DEBUG)
else (UNIX)
    set( KIWI_UNIX 0 )
endif (UNIX)

if (WIN32)
    set( KIWI_WIN32 1 )
else()
    set( KIWI_WIN32 0 )
endif (WIN32)


if( WIN32 )
    set( KIWI_WIN32 1 )
else( WIN32 )
    set( KIWI_WIN32 0 )
endif( WIN32 )

#
# Debugging Options
#
set (CMAKE_VERBOSE_MAKEFILE 0) # Use 1 for debugging, 0 for release

#
# Project Output Paths
#
set (MAINFOLDER ${PROJECT_SOURCE_DIR})
set (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
set (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

#
# Project Search Paths
#
list (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
list (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/tools")
list (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/thirdparty")
set (CMAKE_MODULE_PATH "${MAINFOLDER}/tools/share/cmake")
include_directories("${MAINFOLDER}/include")

#
# Locate Project Prerequisites
#

# Boost
set (Boost_ADDITIONAL_VERSIONS "1.39" "1.39.0" "1.40" "1.40.0" "1.41" "1.41.0" "1.42" "1.42.0" "1.43" "1.43.0" "1.44" "1.44.0" "1.45" "1.45.0" "1.46" "1.46.0" "1.47" "1.47.0" "1.48" "1.48.0" "1.49" "1.49.0" "1.50" "1.50.0")
find_package (Boost 1.37 COMPONENTS "date_time" "filesystem" "graph" "iostreams" "program_options" "regex" "serialization" "signals" "system" "thread" "wserialization" REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# UnitTest++
find_package (UnitTestPlusPlus REQUIRED)
include_directories(${UnitTestPlusPlus_INCLUDE_DIRS})
link_directories(${UnitTestPlusPlus_LIBRARY_DIRS})

#
# Check files ane headers
#
INCLUDE (CheckIncludeFiles)
check_include_files ("stdint.h" HAVE_STDINT_H)
check_include_files ("string.h" HAVE_STRING_H)

#
# Configure Files
#
file (GLOB_RECURSE CONFIGINPUTS1 include/*.in.hpp.cmake)
file (GLOB_RECURSE CONFIGINPUTS2 include/*.hpp.in.cmake)
file (GLOB_RECURSE CONFIGINPUTS3 sources/*.in.hpp.cmake)
file (GLOB_RECURSE CONFIGINPUTS4 sources/*.hpp.in.cmake)
file (GLOB_RECURSE CONFIGINPUTS5 tests/*.in.hpp.cmake)
file (GLOB_RECURSE CONFIGINPUTS6 tests/*.hpp.in.cmake)
list (APPEND CONFIGINPUTS "${CONFIGINPUTS1}")
list (APPEND CONFIGINPUTS "${CONFIGINPUTS2}")
list (APPEND CONFIGINPUTS "${CONFIGINPUTS3}")
list (APPEND CONFIGINPUTS "${CONFIGINPUTS4}")
list (APPEND CONFIGINPUTS "${CONFIGINPUTS5}")
list (APPEND CONFIGINPUTS "${CONFIGINPUTS6}")
foreach (CONFIGINPUT ${CONFIGINPUTS})
    string (REPLACE ".in.hpp.cmake" ".hpp" CONFIGOUTPUT1 "${CONFIGINPUT}")
    string (REPLACE ".hpp.in.cmake" ".hpp" CONFIGOUTPUT2 "${CONFIGOUTPUT1}")
    configure_file ("${CONFIGINPUT}" "${CONFIGOUTPUT2}")
endforeach (CONFIGINPUT ${CONFIGINPUTS})

#
# Add Build Targets
#
add_subdirectory(sources/kiwi-core)
add_subdirectory(sources/kiwi-engine)
add_subdirectory(sources/kiwi-system)
add_subdirectory(sources/kiwi-runtime)
add_subdirectory(sources/kiwi-apache-host)
add_subdirectory(sources/kiwi-console-host)
add_subdirectory(tests)

#
# Add Install Targets
#
if (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")
    install(DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}" DESTINATION "include" FILES_MATCHING PATTERN "*.hpp")
endif (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")
include(UninstallTarget)

#
# Add Documentation Targets
#
configure_file ("Doxyfile.in" Doxyfile)
include (DocumentationTargets)


# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)


# the RPATH to be used when installing, but only if it's not a system directory
#LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
#IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
#ENDIF("${isSystemDir}" STREQUAL "-1")
