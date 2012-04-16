# - Find LLVM libraries
# The module defines the following variables:
#
#   LLVM_INCLUDE_DIRS   - include directories
#   LLVM_LIBRARY_DIRS   - library directories
#   LLVM_LIBRARIES      - llvm libraries
#   LLVM_CPPFLAGS       - C preprocessor flags
#   LLVM_CFLAGS         - C compiler flags
#   LLVM_LDFLAGS        - C++ compiler flags
#
# The minimum required version of bison can be specified using the
# standard CMake syntax, e.g. find_package(BISON 2.1.3)

SET(LLVM_FOUND FALSE)
FIND_PROGRAM(LLVM_CONFIG llvm-config)

macro(_llvm_config output separate flags)
    EXECUTE_PROCESS(
        COMMAND                     ${LLVM_CONFIG} ${flags}
        OUTPUT_VARIABLE             ${output}
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    IF(${separate})
        SEPARATE_ARGUMENTS(${output})
    ENDIF(${separate})
endmacro()

IF("${LLVM_FIND_COMPONENTS}" STREQUAL "")
    SET(LLVM_FIND_COMPONENTS "all")
ELSE("${LLVM_FIND_COMPONENTS}" STREQUAL "")
    SEPARATE_ARGUMENTS(LLVM_FIND_COMPONENTS)
ENDIF("${LLVM_FIND_COMPONENTS}" STREQUAL "")


IF (LLVM_CONFIG)
    SET(LLVM_FOUND TRUE)

    # Retrive LLVM version
    _llvm_config(_LLVM_VERSION_ 0 --version)
    STRING(REGEX REPLACE "([0-9])\\.([0-9])(\\.[0-9])?" "\\1"    LLVM_MAJOR_VERSION    ${_LLVM_VERSION_})
    STRING(REGEX REPLACE "([0-9])\\.([0-9])(\\.[0-9])?" "\\2"    LLVM_MINOR_VERSION    ${_LLVM_VERSION_})
    STRING(REGEX REPLACE "([0-9])\\.([0-9])(\\.[0-9])?" "\\1\\2" _LLVM_VERSION_        ${_LLVM_VERSION_})

    IF("${LLVM_SUBMINOR_VERSION}" STREQUAL "")
        SET(LLVM_SUBMINOR_VERSION 0)
    ENDIF("${LLVM_SUBMINOR_VERSION}" STREQUAL "")

    _llvm_config(LLVM_INCLUDE_DIRS 1  --includedir)
    _llvm_config(LLVM_LIBRARY_DIRS 1  --libdir    )
    _llvm_config(LLVM_CPPFLAGS     0  --cppflags  )
    _llvm_config(LLVM_CFLAGS       0  --cflags    )
    _llvm_config(LLVM_CXXFLAGS     0  --cxxflags  )
    _llvm_config(LLVM_LDFLAGS      1   --ldflags   )
    _llvm_config(LLVM_LIBRARIES    1   --libs ${LLVM_FIND_COMPONENTS})

    list(APPEND LLVM_LIBRARIES ${LLVM_LDFLAGS})
ENDIF (LLVM_CONFIG)

IF(LLVM_FOUND)
    IF( NOT LLVM_FIND_QUIETLY )
        MESSAGE(STATUS "Found LLVM (version ${LLVM_MAJOR_VERSION}.${LLVM_MINOR_VERSION})")
        MESSAGE(STATUS "Found LLVM header files in ${LLVM_INCLUDE_DIRS}")
        MESSAGE(STATUS "Found LLVM libraries: ${LLVM_LIBRARY_DIRS}")
    ENDIF(NOT LLVM_FIND_QUIETLY)
ELSE(LLVM_FOUND)
    IF(LLVM_FIND_REQUIRED)
        MESSAGE( FATAL_ERROR "Could not find LLVM" )
    ELSE(LLVM_FIND_REQUIRED)
        MESSAGE( STATUS "Optional package LLVM was not found" )
    ENDIF(LLVM_FIND_REQUIRED)
ENDIF(LLVM_FOUND)