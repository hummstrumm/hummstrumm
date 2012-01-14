# Humm and Strumm Video Game
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

# CheckCpp11.cmake -- Checks for various C++11 features that we can use.  All
# are implemented alternatively with normal C++03.

if (HUMMSTRUMM_USE_CPP11)

  if (CMAKE_COMPILER_IS_GNUCXX)
    message (STATUS "Checking that compiler supports C++11")
    file (WRITE
          "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.cpp"
          "int main() { return 0; }\n")
    try_compile(HUMMSTRUMM_CAN_USE_CPP11
                "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp"
                "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.cpp"
                COMPILE_DEFINITIONS "-DCMAKE_CXX_FLAGS=\"--std=c++0x\"")
    set (HUMMSTRUMM_USE_CPP11 ${HUMMSTRUMM_CAN_USE_CPP11})
    if (HUMMSTRUMM_CAN_USE_CPP11)
      message (STATUS "Checking that compiler supports C++11 - supported")
      list (APPEND CMAKE_CXX_FLAGS "--std=c++0x")
    else (HUMMSTRUMM_CAN_USE_CPP11)
      message (STATUS "Checking that compiler supports C++11 - not supported")
      return ()
    endif (HUMMSTRUMM_CAN_USE_CPP11)

  else (CMAKE_COMPILER_IS_GNUCXX)
    message (STATUS "Checking that compiler supports C++11")
    file (WRITE
          "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.cpp"
          "#if __cplusplus < 201103L\n#error \"C++11 not supported\"\n#endif int main() { return 0; }\n")
    try_compile(HUMMSTRUMM_CAN_USE_CPP11
                "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp"
                "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.cpp")
    set (HUMMSTRUMM_USE_CPP11 ${HUMMSTRUMM_CAN_USE_CPP11})
    if (HUMMSTRUMM_CAN_USE_CPP11)
      message (STATUS "Checking that compiler supports C++11 - supported")
    else (HUMMSTRUMM_CAN_USE_CPP11)
      message (STATUS "Checking that compiler supports C++11 - not supported")
      return ()
    endif (HUMMSTRUMM_CAN_USE_CPP11)
  endif (CMAKE_COMPILER_IS_GNUCXX)

  message (STATUS "Looking for C++11 static_assert")
  file (WRITE
        "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.cpp"
        "int main() { static_assert(1,\"This shouldn't fail.\"); }\n")
  try_compile(HUMMSTRUMM_HAVE_NATIVE_STATIC_ASSERT
              ${CMAKE_BINARY_DIR}
              "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.cpp"
              COMPILE_DEFINITIONS "-DCMAKE_CXX_FLAGS=\"" ${CMAKE_CXX_FLAGS} "\"")
  if (HUMMSTRUMM_HAVE_NATIVE_STATIC_ASSERT)
    message (STATUS "Looking for C++11 static_assert - found")
  else (HUMMSTRUMM_HAVE_NATIVE_STATIC_ASSERT)
    message (STATUS "Looking for C++11 static_assert - not found")
  endif (HUMMSTRUMM_HAVE_NATIVE_STATIC_ASSERT)

endif (HUMMSTRUMM_USE_CPP11)