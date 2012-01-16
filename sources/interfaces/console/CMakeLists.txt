# Configure Kiwi Console Interface

# Grab all source files
FILE(GLOB_RECURSE SOURCE_CPP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Create build executable target and link libraries
ADD_EXECUTABLE(kiwi-console ${SOURCE_CPP})
TARGET_LINK_LIBRARIES(kiwi-console kiwi-core)
SET_TARGET_PROPERTIES(kiwi-console PROPERTIES OUTPUT_NAME kiwi)