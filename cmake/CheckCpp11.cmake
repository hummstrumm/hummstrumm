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

if (check_cpp11_no_flags)
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
      list (APPEND CMAKE_CXX_FLAGS ${flag_to_check})
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

#   regex -- Boost if the user requests it.  Otherwise, <regex>, falling back on
#            Boost.
if (NOT ENABLE_BOOST_REGEX)
  check_include_file_cxx (regex HAVE_REGEX)
  set (regex_check_compiled FALSE)
  if (HAVE_REGEX)
    message (STATUS "Checking that compiler's regex works")
    file (WRITE
      "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/regex.cpp"
      "#include <regex>\n#include <string>\nint main() {\nstd::string str {\"Hello world\"};\nstd::regex rx{\"ello\"};\nreturn regex_match (str.begin (), str.end (), rx);\nreturn 0; }\n")
    try_run (regex_check_output regex_check_compiled
      "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp"
      "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/regex.cpp")
    if (${regex_check_compiled} MATCHES "FALSE")
      message (STATUS "Checking that compiler's regex works - not supported")
      message (STATUS "Attempting to use Boost::regex in its place...")
    else ()
      message (STATUS "Checking that compiler's regex works regex - supported")
      set (HUMMSTRUMM_ENGINE_REGEX_USE_BOOST OFF)
    endif ()
  else ()
    message (STATUS "Attempting to use Boost::regex in its place...")
  endif ()
endif ()
if (ENABLE_BOOST_REGEX OR
    NOT HAVE_REGEX OR
    ${regex_check_compiled} MATCHES "FALSE")
  find_package (Boost 1.33.0 REQUIRED COMPONENTS regex)
  if (NOT Boost_FOUND)
    message (FATAL_ERROR "You have opted to use the Boost regular expressions library, but you don't seem to have it installed on your system.  Either install the library, point CMake to your existing Boost installation, or use your compiler's C++11 <regex> library, if it works (libstdc++, used by GCC and sometimes Clang, does not yet work.")
  else ()
    set (HUMMSTRUMM_ENGINE_REGEX_USE_BOOST ON)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_REGEX_NO_LIB")
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
    link_directories (${Boost_LIBRARY_DIRS})
  endif ()
endif ()