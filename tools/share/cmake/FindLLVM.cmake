##                                                                           
##                          KIWI SCRIPT LANGUAGE                             
##                                                 
##                            == DESCRIPTION ==                             
## 
##  This file contains function allowed recive C++ comiler & linker flags from
##  LLVM configurate utils
##
##  Copyright:   2009 © Kiwi Developers Group
##  Revision:    $Revision: 9 $
##  Date:        $Date: 2010-05-02 23:00:06 +0600 (Вск, 02 Май 2010) $
##  Author:      $Author: alurin $    
##  Revision:    $Id: LLVM.cmake 9 2010-05-02 17:00:06Z alurin $
##  Url:         $URL: http://svn.kronverk-group.ru/kronverk-sup/branches/php-5.2/www/LLVM.cmake $
##
##                             == LICENSE ==                                                                           
##
##  This file part of Kiwi Script language source files. Please DO NOT USE 
##  this content or part of context WITHOUT LINK to Kiwi project.
##

cmake_minimum_required(VERSION 2.6)

function(llvm_load)
    find_program(LLVM_CONFIG llvm-config)
    if (LLVM_CONFIG STREQUAL "LLVM_CONFIG-NOTFOUND")
        string(TOUPPER "${CMAKE_BUILD_TYPE}" uppercase_CMAKE_BUILD_TYPE)
        if( uppercase_CMAKE_BUILD_TYPE STREQUAL "RELEASE" )
            set(LLVM_CONFIG vendors/llvm/Release/bin/llvm-config)
        else()
            set(LLVM_CONFIG vendors/llvm/Debug/bin/llvm-config)
        endif()
    endif (LLVM_CONFIG STREQUAL "LLVM_CONFIG-NOTFOUND")
    set(LLVM_CONFIG ${LLVM_CONFIG} PARENT_SCOPE)
    message(STATUS "LLVM Config found: ${LLVM_CONFIG}")
endfunction()

function(llvm_include PROJECT LIBS)
    llvm_load()
    execute_process(
            COMMAND
                    ${LLVM_CONFIG} --cppflags
            OUTPUT_VARIABLE
                    LLVM_CPPFLAGS
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
            COMMAND
                    ${LLVM_CONFIG} --ldflags
            OUTPUT_VARIABLE
                    LLVM_LDFLAGS
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    separate_arguments(LIBS)
    execute_process(
            COMMAND
                    ${LLVM_CONFIG} --libs ${LIBS}
            OUTPUT_VARIABLE
                    LLVM_LIBS
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    separate_arguments(LLVM_LIBS)
    separate_arguments(LLVM_LDFLAGS)

    target_link_libraries(${PROJECT} ${LLVM_LIBS} ${LLVM_LDFLAGS})
    set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${LLVM_CPPFLAGS} )
    set_target_properties(${PROJECT} PROPERTIES LINK_FLAGS ${LLVM_CPPFLAGS})
endfunction(llvm_include)