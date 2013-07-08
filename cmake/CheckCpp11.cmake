# Humm and Strumm Engine
# Copyright (C) 2008-2012, the people listed in the AUTHORS file. 
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# CheckCpp11.cmake -- Checks for various C++11 features that we can use.

include (CheckCXXCompilerFlag)
include (CheckCXXSourceCompiles)
include (CheckCXXSymbolExists)
include (CheckIncludeFileCXX)

message (STATUS "Checking that compiler supports C++11")
  set (HUMMSTRUMM_ENGINE_HAVE_CPP11_SUPPORT OFF)

check_cxx_source_compiles ("#if __cplusplus < 201103L\n#error C++11 not supported\n#endif int main() { return 0; }\n" check_cpp11_compiles_with_no_flags)

if (check_cpp11_no_flags OR MSVC_VERSION GREATER 1699)
  set (HUMMSTRUMM_ENGINE_HAVE_CPP11_SUPPORT ON)
  message (STATUS "Checking that compiler supports C++11 - supported")
else ()
  set (flags_to_check "--std=c++11" "--std=c++0x")
  foreach (flag_to_check ${flags_to_check})
    # check_cpp11_flag_*, must be alphanumeric/underscores
    string (REGEX REPLACE "[^A-Z a-z 0-9]" "_" flag_variable ${flag_to_check})
    string (STRIP "${flag_variable}" flag_variable)
    set (flag_variable "check_cpp11_compiles_with_flag_${flag_variable}")

    check_cxx_compiler_flag ("${flag_to_check}" ${flag_variable})
    if (${flag_variable})
      set (HUMMSTRUMM_ENGINE_HAVE_CPP11_SUPPORT ON)
      message (STATUS "Checking that compiler supports C++11 - supported")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag_to_check}")
      break ()
    endif ()
  endforeach ()
endif ()

if (NOT HUMMSTRUMM_ENGINE_HAVE_CPP11_SUPPORT)
  message (STATUS "Checking that compiler supports C++11 - not supported")
  message (FATAL_ERROR "A compiler that supports C++11 is required.")
endif ()

# Check for specific features:
#   std::round -- MSVC doesn't yet implement it.
check_include_file_cxx (cmath HAVE_CMATH)
if (NOT HAVE_CMATH)
  message (FATAL_ERROR "Your compiler claims to be C++11 compliant, but it can't find the standard header <cmath>.  Your installation is very abnormal, incomplete, or incompatible.")
endif ()
check_cxx_source_compiles ("#include <cmath>\nint main() { return (int)std::round (0.3); }\n" HAVE_STD_ROUND)
