FILE (GLOB_RECURSE compiler_SOURCES *.cpp *.cxx *.cc *.C *.c *.h *.hpp)

SET (compiler_LIBS ${Boost_LIBRARIES} ${ICU_LIBRARIES} "lib${PROJECT_NAME}" "kiwi-runtime")
SET (compiler_BIN "${PROJECT_NAME}c")

ADD_EXECUTABLE(${compiler_BIN} ${compiler_SOURCES})
TARGET_LINK_LIBRARIES(${compiler_BIN} ${compiler_LIBS})
SET_TARGET_PROPERTIES(
    ${compiler_BIN} PROPERTIES
    VERSION "${KIWI_VERSION_MAJOR}.${KIWI_VERSION_MINOR}"
    OUTPUT_NAME ${compiler_BIN}
    CLEAN_DIRECT_OUTPUT 1
)

INSTALL(TARGETS ${compiler_BIN} DESTINATION bin)
