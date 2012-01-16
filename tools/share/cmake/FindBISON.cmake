# - Find bison executable and provides macros to generate custom build rules
# The module defined the following variables:
#  BISON_EXECUTABLE - path to the bison program
#  BISON_VERSION - version of bison
#  BISON_FOUND - true if the program was found
# If bison is found, the module defines the macros:
#  BISON_TARGET(<Name> <YaccInput> <CodeOutput> [VERBOSE <file>]
#              [COMPILE_FLAGS <string>])
# which will create  a custom rule to generate  a parser. <YaccInput> is
# the path to  a yacc file. <CodeOutput> is the name  of the source file
# generated by bison.  A header file is also  be generated, and contains
# the  token  list.  If  COMPILE_FLAGS  option is  specified,  the  next
# parameter is  added in the bison  command line.  if  VERBOSE option is
# specified, <file> is created  and contains verbose descriptions of the
# grammar and parser. The macro defines a set of variables:
#  BISON_${Name}_DEFINED - true is the macro ran successfully
#  BISON_${Name}_INPUT - The input source file, an alias for <YaccInput>
#  BISON_${Name}_OUTPUT_SOURCE - The source file generated by bison
#  BISON_${Name}_OUTPUT_HEADER - The header file generated by bison
#  BISON_${Name}_OUTPUTS - The sources files generated by bison
#  BISON_${Name}_COMPILE_FLAGS - Options used in the bison command line
#
# Example:
# FIND_PACKAGE(BISON)
# BISON_TARGET(MyParser parser.y ${PROJECT_BINARY_DIR}/parser.cpp)
# ADD_EXECUTABLE(Foo main.cpp ${BISON_MyParser_OUTPUTS})
#

# Copyright (c) 2006, Tristan Carel
# All rights reserved.
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the University of California, Berkeley nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# $Id: FindBISON.cmake 1218 2007-03-22 22:10:45Z jmh $

SET(BISON_FOUND FALSE)

FIND_PROGRAM(BISON_EXECUTABLE bison DOC "path to the bison executable")
MARK_AS_ADVANCED(BISON_EXECUTABLE)

IF(BISON_EXECUTABLE)
  SET(BISON_FOUND TRUE)

  EXECUTE_PROCESS(COMMAND ${BISON_EXECUTABLE} --version
    OUTPUT_VARIABLE BISON_version_output
    ERROR_VARIABLE BISON_version_error
    RESULT_VARIABLE BISON_version_result
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  IF(NOT ${BISON_version_result} EQUAL 0)
    MESSAGE(SEND_ERROR "Command \"${BISON_EXECUTABLE} --version\" failed with output:\n${BISON_version_error}")
  ELSE(NOT ${BISON_version_result} EQUAL 0)
    STRING(REGEX REPLACE "^bison \\(GNU Bison\\) ([^\n]+)\n.*" "\\1"
      BISON_VERSION "${BISON_version_output}")
  ENDIF(NOT ${BISON_version_result} EQUAL 0)

  # internal macro
  MACRO(BISON_TARGET_option_verbose Name BisonOutput filename)
    LIST(APPEND BISON_TARGET_cmdopt "--verbose")
    GET_FILENAME_COMPONENT(BISON_TARGET_output_path "${BisonOutput}" PATH)
    GET_FILENAME_COMPONENT(BISON_TARGET_output_name "${BisonOutput}" NAME_WE)
    ADD_CUSTOM_COMMAND(OUTPUT ${filename}
      COMMAND ${CMAKE_COMMAND} -E copy
      "${BISON_TARGET_output_path}/${BISON_TARGET_output_name}.output"
      "${filename}"
      DEPENDS
      "${BISON_TARGET_output_path}/${BISON_TARGET_output_name}.output"
      COMMENT "[BISON][${Name}] Copying bison verbose table to ${filename}"
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    SET(BISON_${Name}_VERBOSE_FILE ${filename})
    LIST(APPEND BISON_TARGET_extraoutputs
      "${BISON_TARGET_output_path}/${BISON_TARGET_output_name}.output")
  ENDMACRO(BISON_TARGET_option_verbose)

  # internal macro
  MACRO(BISON_TARGET_option_extraopts Options)
    SET(BISON_TARGET_extraopts "${Options}")
    SEPARATE_ARGUMENTS(BISON_TARGET_extraopts)
    LIST(APPEND BISON_TARGET_cmdopt ${BISON_TARGET_extraopts})
  ENDMACRO(BISON_TARGET_option_extraopts)

  MACRO(BISON_TARGET Name BisonInput BisonOutput)
    SET(BISON_TARGET_output_header "")
    SET(BISON_TARGET_command_opt "")
    SET(BISON_TARGET_outputs "${BisonOutput}")
    IF(NOT ${ARGC} EQUAL 3 AND NOT ${ARGC} EQUAL 5 AND NOT ${ARGC} EQUAL 7)
      MESSAGE(SEND_ERROR "Usage")
    ELSE(NOT ${ARGC} EQUAL 3 AND NOT ${ARGC} EQUAL 5 AND NOT ${ARGC} EQUAL 7)
      # Parsing parameters
      IF(${ARGC} GREATER 5 OR ${ARGC} EQUAL 5)
	IF("${ARGV3}" STREQUAL "VERBOSE")
	  BISON_TARGET_option_verbose(${Name} ${BisonOutput} "${ARGV4}")
	ENDIF("${ARGV3}" STREQUAL "VERBOSE")
	IF("${ARGV3}" STREQUAL "COMPILE_FLAGS")
	  BISON_TARGET_option_extraopts("${ARGV4}")
	ENDIF("${ARGV3}" STREQUAL "COMPILE_FLAGS")
      ENDIF(${ARGC} GREATER 5 OR ${ARGC} EQUAL 5)
      IF(${ARGC} EQUAL 7)
	IF("${ARGV5}" STREQUAL "VERBOSE")
	  BISON_TARGET_option_verbose(${Name} ${BisonOutput} "${ARGV6}")
	ENDIF("${ARGV5}" STREQUAL "VERBOSE")
	IF("${ARGV5}" STREQUAL "COMPILE_FLAGS")
	  BISON_TARGET_option_extraopts("${ARGV6}")
	ENDIF("${ARGV5}" STREQUAL "COMPILE_FLAGS")
      ENDIF(${ARGC} EQUAL 7)

      # Header's name generated by bison (see option -d)
      LIST(APPEND BISON_TARGET_cmdopt "-d")
      STRING(REGEX REPLACE "^(.*)\\.c([^.]*)$" "\\1.h\\2"
	BISON_${Name}_OUTPUT_HEADER "${ARGV2}")
      LIST(APPEND BISON_TARGET_outputs "${BISON_${Name}_OUTPUT_HEADER}")

      ADD_CUSTOM_COMMAND(OUTPUT ${BISON_TARGET_outputs}
	${BISON_TARGET_extraoutputs}
	COMMAND ${BISON_EXECUTABLE} ${BISON_TARGET_cmdopt} -o ${ARGV2} ${ARGV1}
	DEPENDS ${ARGV1}
	COMMENT "[BISON][${Name}] Building parser with bison ${BISON_VERSION}"
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

      # define target variables
      SET(BISON_${Name}_DEFINED TRUE)
      SET(BISON_${Name}_INPUT ${ARGV1})
      SET(BISON_${Name}_OUTPUTS ${CMAKE_CURRENT_SOURCE_DIR}/${BISON_TARGET_outputs})
      SET(BISON_${Name}_COMPILE_FLAGS ${BISON_TARGET_cmdopt})
      SET(BISON_${Name}_OUTPUT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/${BisonOutput}")
      SET(BISON_${Name}_OUTPUT_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/${BISON_${Name}_OUTPUT_HEADER})
    ENDIF(NOT ${ARGC} EQUAL 3 AND NOT ${ARGC} EQUAL 5 AND NOT ${ARGC} EQUAL 7)
  ENDMACRO(BISON_TARGET)

ENDIF(BISON_EXECUTABLE)


IF(NOT BISON_FOUND)
  IF(NOT BISON_FIND_QUIETLY)
    MESSAGE(STATUS "BISON was not found.")
  ELSE(NOT BISON_FIND_QUIETLY)
    IF(BISON_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "BISON was not found.")
    ENDIF(BISON_FIND_REQUIRED)
  ENDIF(NOT BISON_FIND_QUIETLY)
ENDIF(NOT BISON_FOUND)

# FindBISON.cmake ends here
