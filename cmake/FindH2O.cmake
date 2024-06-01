# FindH2O.cmake - Find libh2o and its dependencies

# Locate the libh2o include directory
find_path(H2O_INCLUDE_DIR
  NAMES h2o.h
  PATHS /usr/local/include /usr/include
)

# Locate the libh2o library
find_library(H2O_LIBRARY
  NAMES h2o
  PATHS /usr/local/lib /usr/lib
)

# Find other required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUV REQUIRED libuv)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

# Print messages if any dependency is not found
if (NOT H2O_INCLUDE_DIR)
  message(FATAL_ERROR "H2O include directory not found.")
endif()

if (NOT H2O_LIBRARY)
  message(FATAL_ERROR "H2O library not found.")
endif()

# Handle the REQUIRED arguments and set H2O_FOUND to TRUE if all components are found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(H2O REQUIRED_VARS H2O_INCLUDE_DIR H2O_LIBRARY)

if (H2O_FOUND)
  set(H2O_LIBRARIES ${H2O_LIBRARY} ${LIBUV_LIBRARIES} ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES})
  set(H2O_INCLUDE_DIRS ${H2O_INCLUDE_DIR} ${LIBUV_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS})
endif()

mark_as_advanced(H2O_INCLUDE_DIR H2O_LIBRARY)
