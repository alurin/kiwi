# Configure Kiwi Console Interface

# Grab all source files
file(GLOB_RECURSE SOURCE_CPP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Create build executable target and link libraries
add_executable(kiwi-console ${SOURCE_CPP})
target_link_libraries(kiwi-console kiwi-core ${Boost_LIBRARIES})
set_target_properties(kiwi-console PROPERTIES OUTPUT_NAME kiwi)