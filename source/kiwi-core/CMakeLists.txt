FILE (GLOB_RECURSE project_SOURCES *.cpp *.cxx *.cc *.C *.c *.h *.hpp)

# Include bison and flex
FIND_PACKAGE(BISON REQUIRED)
FIND_PACKAGE(FLEX  REQUIRED)

# PROJECT_BINARY_DIR
BISON_TARGET(KiwiParser ${CMAKE_CURRENT_SOURCE_DIR}/lang/parser.yy lang/parser.cpp)
FLEX_TARGET(KiwiScanner ${CMAKE_CURRENT_SOURCE_DIR}/lang/scanner.ll lang/scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY(KiwiScanner KiwiParser)

SET (project_SOURCES ${project_SOURCES} ${BISON_KiwiParser_OUTPUTS} ${FLEX_KiwiScanner_OUTPUTS})
LIST(REMOVE_DUPLICATES project_SOURCES)

SET (project_LIBS ${Boost_LIBRARIES} ${ICU_LIBRARIES} ${Log4Cxx_LIBRARIES})
SET (project_LIB "lib${PROJECT_NAME}")

ADD_LIBRARY(${project_LIB} SHARED ${project_SOURCES})
TARGET_LINK_LIBRARIES(${project_LIB} ${project_LIBS})
SET_TARGET_PROPERTIES(${project_LIB} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_LIB} CLEAN_DIRECT_OUTPUT 1)

INSTALL(TARGETS ${project_LIB} DESTINATION lib)

#ignore flags for generated files
if (KIWI_DEBUG)
    set_property(SOURCE ${BISON_KiwiParser_OUTPUTS} PROPERTY COMPILE_FLAGS "-g")
endif(KIWI_DEBUG)

#ignore GCC warnings for generated files
if (CMAKE_COMPILER_IS_GNUCC)
    set_source_files_properties(
        ${BISON_KiwiParser_OUTPUTS}
        ${FLEX_KiwiScanner_OUTPUTS}
        PROPERTIES
        COMPILE_FLAGS -Wno-parentheses
    )
endif (CMAKE_COMPILER_IS_GNUCC)