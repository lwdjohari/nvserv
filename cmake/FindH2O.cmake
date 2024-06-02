# The MIT License (MIT)
#
# Copyright (c) 2024 Linggawasistha Djohari
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# FindH2O.cmake - Find libh2o and its dependencies
#
# This module defines
# H2O_FOUND, whether h2o is found
# H2O_INCLUDE_DIR, h2o headers location
# OPENSSL_LIBRARIES, openssl library to link against 
# LIBUV_LIBRARIES, libuv library to link against
# ZLIB_LIBRARIES, zlib library to link against
# LIBUV_INCLUDE_DIRS, libuv headers location
# OPENSSL_INCLUDE_DIR, openssl headers location 
# ZLIB_INCLUDE_DIRS, zlib headers location
#
# Notes:
# Currently not checking for mruby support for ruby scripting in h2o
#
# Linggawasistha Djohari <linggawasistha.djohari@outlook.com>, 2024

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
