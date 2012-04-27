FILE (GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
SET (test_LIBS ${Boost_LIBRARIES} ${UnitTestPlusPlus_LIBRARIES} "libkiwi" "${PROJECT_NAME}-runtime")
SET (test_BIN ${PROJECT_NAME}-unittests)

ADD_EXECUTABLE(${test_BIN} ${test_SRCS})
TARGET_LINK_LIBRARIES(${test_BIN} ${test_LIBS})

ADD_CUSTOM_TARGET(check ALL "${MAINFOLDER}/bin/${test_BIN}" DEPENDS ${test_BIN} COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS})
ADD_CUSTOM_TARGET(test "${MAINFOLDER}/bin/${test_BIN}" DEPENDS ${test_BIN} COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS})

FIND_PROGRAM(VALGRIND valgrind)
IF(VALGRIND)
    ADD_CUSTOM_TARGET(
        valgrind
        COMMAND ${VALGRIND} --leak-check=full --leak-resolution=med ${MAINFOLDER}/bin/${test_BIN}
        DEPENDS ${test_BIN}
        COMMENT "Executing unit tests with valgrind checks..." VERBATIM
        SOURCES ${test_SRCS})
ENDIF(VALGRIND)

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")
