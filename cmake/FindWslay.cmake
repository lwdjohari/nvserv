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
#
# FindWslay.cmake - Locate wslay library
# This module defines
# WSLAY_FOUND, whether wslay is found
# WSLAY_INCLUDE_DIRS, where to find wslay headers
# WSLAY_LIBRARIES, the libraries to link against
# Linggawasistha Djohari <linggawasistha.djohari@outlook.com>, 2024

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