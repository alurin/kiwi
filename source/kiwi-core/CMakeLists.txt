FILE (GLOB_RECURSE project_SOURCES *.cpp *.hpp)

# Include bison and flex
FIND_PACKAGE(BISON REQUIRED)
FIND_PACKAGE(FLEX  REQUIRED)

BISON_TARGET(KiwiParser ${CMAKE_CURRENT_SOURCE_DIR}/lang/parser.yy  lang/parser.cpp VERBOSE ${PROJECT_BINARY_DIR}/parser.log)
FLEX_TARGET(KiwiScanner ${CMAKE_CURRENT_SOURCE_DIR}/lang/scanner.ll lang/scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY(KiwiScanner KiwiParser)

SET (project_SOURCES ${project_SOURCES} ${BISON_KiwiParser_OUTPUTS} ${FLEX_KiwiScanner_OUTPUTS})
LIST(REMOVE_ITEM project_SOURCES "lang/scanner.cpp")
LIST(REMOVE_ITEM project_SOURCES "lang/parser.cpp")
LIST(REMOVE_ITEM project_SOURCES "lang/parser.hpp")

SET (project_LIBS ${Boost_LIBRARIES} ${ICU_LIBRARIES} ${Log4Cxx_LIBRARIES} ${LLVM_LIBRARIES})
SET (project_LIB "lib${PROJECT_NAME}")

# Remove no exception from LLVM flags
STRING(REPLACE "-fno-exceptions" "" LLVM_CXXFLAGS ${LLVM_CXXFLAGS})

ADD_LIBRARY(${project_LIB} SHARED ${project_SOURCES})
TARGET_LINK_LIBRARIES(${project_LIB} ${project_LIBS})
SET_TARGET_PROPERTIES(
    ${project_LIB} PROPERTIES
    VERSION             "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}"
    OUTPUT_NAME         ${project_LIB}
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_FLAGS       ${LLVM_CXXFLAGS}
    LINK_FLAGS          ${LLVM_CXXFLAGS}
)

INSTALL(TARGETS ${project_LIB} DESTINATION lib)