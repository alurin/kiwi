# Vasiliy Sheredeko. Copyright (C) 2012. MIT license.

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (kiwi)
INCLUDE(ExternalProject)

#
# Project Properties
#
SET (KIWI_NAME "Kiwi")
SET (KIWI_CODENAME "${PROJECT_NAME}")
SET (KIWI_COPYRIGHT_YEARS "2012")
SET (KIWI_VERSION_MAJOR 0)
SET (KIWI_VERSION_MINOR 2)
SET (KIWI_VERSION_PATCH 0)
SET (KIWI_VERSION_TYPE SNAPSHOT)
SET (KIWI_VERSION_STRING "${KIWI_VERSION_MAJOR}.${KIWI_VERSION_MINOR}.${KIWI_VERSION_PATCH}-${KIWI_VERSION_TYPE}")
SET (KIWI_VENDOR_ID "com.kronverk-studio")
SET (KIWI_VENDOR_NAME "Vasiliy Sheredeko")
SET (KIWI_VENDOR_URL "kronverk-studio.ru")
SET (KIWI_ID "${KIWI_VENDOR_ID}.${PROJECT_NAME}")

#
# Debugging Options
#
SET (CMAKE_VERBOSE_MAKEFILE 0) # Use 1 for debugging, 0 for release

OPTION(Debug "Enable debug build for source" OFF )
OPTION(GC    "Build with support of libGC"   OFF ) # GC crashed C++ testes
STRING(TOUPPER CMAKE_BUILD_TYPE _TYPE)

IF( Debug OR  _TYPE STREQUAL "DEBUG")
    SET( Debug ON )
    SET( KIWI_DEBUG 1 )
    SET( CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
ELSE( Debug OR  _TYPE STREQUAL "DEBUG")
    SET( Debug OFF )
    SET( KIWI_RELEASE 1 )
    SET( CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF( Debug OR  _TYPE STREQUAL "DEBUG")

MESSAGE(STATUS "Build ${CMAKE_BUILD_TYPE} version of project")

# Options for GNU C++
if (CMAKE_COMPILER_IS_GNUCC)
    # Only support GNU C++ version 4.8 or greater
    execute_process (COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (NOT GCC_VERSION VERSION_GREATER 4.8 AND NOT GCC_VERSION VERSION_EQUAL 4.8)
        message (FATAL_ERROR
            "C++ compiler not supported C++11 standart."
            "-- Please compile with GNU C++ version 4.8 or greater"
        )
    endif (NOT GCC_VERSION VERSION_GREATER 4.8 AND NOT GCC_VERSION VERSION_EQUAL 4.8)

    # Fix x64 issues on Linux
    if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" AND NOT APPLE)
        add_definitions(-fPIC)
    endif()

    # Set compiler c++11 mode
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    # Treat all errors and warnings
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

    # Noise and noise utilities not worked without exceptions support
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")

    # Boost program options not worked without RTTI support
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")

    # Add compile flags for release mode
    set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_DEBUG} -O3 -fomit-frame-pointer")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -fomit-frame-pointer")

    # Add compile flags for debug mode
    set (CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG} -O0 -g -ggdb") #-g3 -gdwarf-4")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -ggdb") # -g3 -gdwarf-4")

    # Enable multi threaded support
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lpthread")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
endif (CMAKE_COMPILER_IS_GNUCC)


IF( CMAKE_COMPILER_IS_GNUCC AND CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
    # GC not compiled without this flags
    SET(EXTERNAL_C_FLAGS    "-fPIC")
    SET(EXTERNAL_CXX_FLAGS  "-fPIC")
ENDIF( CMAKE_COMPILER_IS_GNUCC AND CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

#
# Project Output Paths
#
SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

#
# Project Search Paths
#
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/tool")
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/thirdparty")
SET (CMAKE_MODULE_PATH "${MAINFOLDER}/tool/share/cmake")
INCLUDE_DIRECTORIES("${MAINFOLDER}/include")

#
# Locate Project Prerequisites
#
SET (Boost_ADDITIONAL_VERSIONS "1.50" "1.50.0" "1.53" "1.53.0" "1.54" "1.54.0" "1.55" "1.55.0")
FIND_PACKAGE (Boost 1.37 COMPONENTS "program_options" REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

FIND_PACKAGE (UnitTestPlusPlus REQUIRED)
INCLUDE_DIRECTORIES(${UnitTestPlusPlus_INCLUDE_DIRS})
LINK_DIRECTORIES(${UnitTestPlusPlus_LIBRARY_DIRS})

FIND_PACKAGE (ICU REQUIRED)
INCLUDE_DIRECTORIES(${ICU_INCLUDE_DIRS})
LINK_DIRECTORIES(${ICU_LIBRARIES} ${ICU_I18N_LIBRARIES})

FIND_PACKAGE (LLVM COMPONENTS "engine" "native" "jit" REQUIRED 3.0)
INCLUDE_DIRECTORIES(${LLVM_INCLUDE_DIRS})
LINK_DIRECTORIES(${LLVM_LIBRARY_DIRS})

#
# Locate External Projects
#

IF (GC)
    set(KIWI_GC TRUE)
    EXTERNALPROJECT_ADD(
        bdwgc
        PREFIX ${CMAKE_BINARY_DIR}/bdwgc
        SOURCE_DIR ${MAINFOLDER}/vendor/lib/bdwgc
        INSTALL_COMMAND ""
        CMAKE_ARGS
            -DCMAKE_C_FLAGS=${EXTERNAL_C_FLAGS}
            -DCMAKE_CXX_FLAGS=${EXTERNAL_CXX_FLAGS}
    )
    ADD_LIBRARY(gc-lib UNKNOWN IMPORTED)
    SET_PROPERTY(TARGET gc-lib PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/bdwgc/src/bdwgc-build/libgc-lib.a )
    INCLUDE_DIRECTORIES(${MAINFOLDER}/vendor/lib/bdwgc/include)
ENDIF(GC)

#
# Configure Files
#
FILE (GLOB_RECURSE CONFIGINPUTS1 include/*.in.hpp.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS2 include/*.hpp.in.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS3 source/*.in.hpp.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS4 source/*.hpp.in.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS5 test/*.in.hpp.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS6 test/*.hpp.in.cmake)
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS1}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS2}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS3}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS4}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS5}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS6}")
FOREACH (CONFIGINPUT ${CONFIGINPUTS})
    STRING (REPLACE ".in.hpp.cmake" ".hpp" CONFIGOUTPUT1 "${CONFIGINPUT}")
    STRING (REPLACE ".hpp.in.cmake" ".hpp" CONFIGOUTPUT2 "${CONFIGOUTPUT1}")
    CONFIGURE_FILE ("${CONFIGINPUT}" "${CONFIGOUTPUT2}")
ENDFOREACH (CONFIGINPUT ${CONFIGINPUTS})

#
# Add Build Targets
#
ADD_SUBDIRECTORY(source/kiwi-core)
ADD_SUBDIRECTORY(source/kiwi-runtime)
ADD_SUBDIRECTORY(source/kiwi-compiler)
ADD_SUBDIRECTORY(source/kiwi-interpreter)
ADD_SUBDIRECTORY(test)

#
# Add Install Targets
#
IF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")
    INSTALL(DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}" DESTINATION "include")
ENDIF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")

#
# Add Documentation Targets
#
CONFIGURE_FILE ("Doxyfile.in" "Doxyfile")
INCLUDE (DocumentationTargets)
