#
# this module look for apache
#
# - Find Apache 2 headers
# Find the APACHE2 includes and libraries
# This module defines
#  APACHE3_INCLUDE_DIR and APACHE2UTIL_INCLUDE_DIR, where to find httpd.h, etc.

FIND_PATH(
    APACHE2_INCLUDE_DIR httpd.h
    /usr/local/include/apache2
    /usr/local/include/apache2.2
    /usr/include/apache2
    /usr/include/apache2-2
)

#SET(APACHE2_NAMES ${APACHE2_NAMES} apache2)
#FIND_LIBRARY(APACHE2_LIBRARY
#  NAMES ${APACHE2_NAMES}
#  PATHS /usr/lib /usr/local/lib
#  )

IF (APACHE2_INCLUDE_DIR)
    SET(APACHE2_LIBRARIES ${APACHE2_LIBRARY})
    SET(APACHE2_FOUND "YES")
ELSE (APACHE2_INCLUDE_DIR)
  SET(APACHE2_FOUND "NO")
ENDIF (APACHE2_INCLUDE_DIR)

IF (APACHE2_FOUND)
   IF (NOT APACHE2_FIND_QUIETLY)
      MESSAGE(STATUS "Found Apache 2 headers: ${APACHE2_INCLUDE_DIR}")
   ENDIF (NOT APACHE2_FIND_QUIETLY)
ELSE (APACHE2_FOUND)
   IF (APACHE2_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find Apache 2 headers")
   ENDIF (APACHE2_FIND_REQUIRED)
ENDIF (APACHE2_FOUND)

MARK_AS_ADVANCED(
  APACHE2_INCLUDE_DIR
)