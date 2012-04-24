FILE (GLOB_RECURSE interpreter_SOURCES *.cpp *.cxx *.cc *.C *.c *.h *.hpp)

SET (interpreter_LIBS ${ICU_LIBRARIES} "lib${PROJECT_NAME}" "kiwi-runtime")
SET (interpreter_BIN "${PROJECT_NAME}")

ADD_EXECUTABLE(${interpreter_BIN} ${interpreter_SOURCES})
TARGET_LINK_LIBRARIES(${interpreter_BIN} ${interpreter_LIBS})
SET_TARGET_PROPERTIES(
    ${interpreter_BIN} PROPERTIES
    VERSION "${KIWI_VERSION_MAJOR}.${KIWI_VERSION_MINOR}"
    OUTPUT_NAME ${interpreter_BIN}
    CLEAN_DIRECT_OUTPUT 1)

INSTALL(TARGETS ${interpreter_BIN} DESTINATION bin)
