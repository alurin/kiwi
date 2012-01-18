# Configure Kiwi Core library

find_package(LLVM)

## Distrubutive type: Debug or Release...
if (CMAKE_BUILD_TYPE STREQUAL "")
  set (CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set (KIWI_DEBUG on)
endif ()

# Grab all source files
file(GLOB_RECURSE SOURCE_CPP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

set(
    SOURCE_CPP
    ${SOURCE_CPP}
    ${CMAKE_CURRENT_SOURCE_DIR}/Script/Lexer.tab.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Script/Parser.tab.cpp
)

list(REMOVE_DUPLICATES SOURCE_CPP)

if (${KIWI_LIBRARY})
    add_definitions(-DKIWI_LIBRARY_EXPORTS)
    add_library(kiwi-core SHARED ${SOURCE_CPP})
else (${KIWI_LIBRARY})
    if (${BUILD_SHARED_LIBS})
        add_definitions(-DKIWI_LIBRARY_EXPORTS)
    endif(${BUILD_SHARED_LIBS})
    add_library(kiwi-core ${SOURCE_CPP})
endif (${KIWI_LIBRARY})


set_target_properties(kiwi-core PROPERTIES OUTPUT_NAME kiwi)
target_link_libraries(kiwi-core icuuc icuio)

llvm_load()
llvm_include(kiwi-core "engine native jit")

# Подключение бисона
message(STATUS "Configure Kiwi parser impementation")
find_program(BISON bison)

if(BISON_FOUND)
    message(FATAL_ERROR "Bison parser generator not found")
endif(BISON_FOUND)

add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/Parser.tab.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/Parser.tab.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/Parser.output
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/location.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/position.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/stack.hh
    COMMAND
        ${BISON} ARGS ${CMAKE_CURRENT_SOURCE_DIR}/Script/Parser.ypp --verbose -v --report=state,lookahead,lookahead --warnings=all
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/Parser.ypp
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/Driver.hpp
)

# Подключение флекса
find_program(FLEX flex)
if(FLEX_FOUND)
    message(FATAL_ERROR "Flex lexical generator not found")
endif(FLEX_FOUND)

add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/Lexer.tab.cpp
    COMMAND
        ${FLEX} ARGS -o${CMAKE_CURRENT_SOURCE_DIR}/Script/Lexer.tab.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Script/Lexer.ypp
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/Lexer.ypp
)

if (KIWI_DEBUG)
    set_property(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/Script/Parser.tab.cpp PROPERTY COMPILE_FLAGS "-g")
    set_property(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/Script/Lexer.tab.cpp PROPERTY COMPILE_FLAGS "-g")
endif(KIWI_DEBUG)

#ignore GCC warnings
if (CMAKE_COMPILER_IS_GNUCC)
    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/Lexer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/Lexer.tab.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Script/Parser.tab.cpp

        PROPERTIES
        COMPILE_FLAGS -Wno-parentheses
    )
endif (CMAKE_COMPILER_IS_GNUCC)