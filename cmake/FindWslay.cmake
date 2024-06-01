# FindWslay.cmake - Locate wslay library
# This module defines
#  WSLAY_FOUND, whether wslay is found
#  WSLAY_INCLUDE_DIRS, where to find wslay headers
#  WSLAY_LIBRARIES, the libraries to link against

find_path(WSLAY_INCLUDE_DIR wslay/wslay.h
  HINTS /usr/local/include /usr/include
)

find_library(WSLAY_LIBRARIES NAMES wslay
  HINTS /usr/local/lib /usr/lib/x86_64-linux-gnu
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Wslay DEFAULT_MSG WSLAY_LIBRARIES WSLAY_INCLUDE_DIR)

if(WSLAY_FOUND)
  set(WSLAY_INCLUDE_DIRS ${WSLAY_INCLUDE_DIR})
else()
  set(WSLAY_FOUND FALSE)
endif()