FILE (GLOB_RECURSE runtime_SOURCES *.c *.h *.cpp *.hpp)

SET (runtime_LIBS ${Boost_LIBRARIES} ${ICU_LIBRARIES} icuuc icuio pthread tinfo z)
SET (runtime_LIB "${PROJECT_NAME}-runtime")

ADD_LIBRARY(${runtime_LIB} SHARED ${runtime_SOURCES})
TARGET_LINK_LIBRARIES(${runtime_LIB} ${runtime_LIBS})
SET_TARGET_PROPERTIES(
    ${runtime_LIB} PROPERTIES
    VERSION "${KIWI_VERSION_MAJOR}.${KIWI_VERSION_MINOR}"
    OUTPUT_NAME ${runtime_LIB}
    CLEAN_DIRECT_OUTPUT 1
)

IF (KIWI_GC)
    TARGET_LINK_LIBRARIES(${runtime_LIB} "gc-lib")
ENDIF(KIWI_GC)

INSTALL(TARGETS ${runtime_LIB} DESTINATION lib)
