# Configure Kiwi Apache 2 Module Interface

find_package( Apache2 )
find_package( APR )

file(GLOB_RECURSE SOURCE_C RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c)
file(GLOB_RECURSE SOURCE_CPP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_library( kiwi-apache2-module SHARED ${SOURCE_C} ${SOURCE_CPP} )
target_link_libraries( kiwi-apache2-module kiwi-core ${APR_LIBRARY} )
include_directories( ${APACHE2_INCLUDE_DIR} ${APR_INCLUDE_DIR})

set_target_properties(kiwi-apache2-module
    PROPERTIES
    OUTPUT_NAME mod_kiwi
    COMPILE_FLAGS "${APR_CFLAGS} ${APR_INCLUDES}"
    LINK_FLAGS "${APR_LDFLAGS} ${APR_INCLUDES}"
)