# Humm and Strumm Video Game
# Copyright (C) 2008-2011, the people listed in the AUTHORS file. 
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

# This is the CMake script that is used to build Humm and Strumm.  This script
# deals with these things:
#
#   * Creating configuration values that can be set with ``ccmake''.
#   * Detecting basic system information.
#   * Configuring CTest and CPack for unit testing and packaging, respectively.

project (hummstrumm)
cmake_minimum_required (VERSION 2.6.3)

set (CMAKE_MODULE_PATH ${hummstrumm_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include (Defaults)
include (Version)
include (Platform)
include (MaintainerMode)
include (Uninstall)

# We want testing with CTest.
enable_testing ()

# Install the system libraries we'll need.
include (InstallRequiredSystemLibraries)

# Test for SIMD
set (HUMMSTRUMM_HAVE_SSE_SUPPORT OFF)

try_run (RUN_RESULT_VAR COMPILE_RESULT_VAR
         ${CMAKE_BINARY_DIR}
         ${CMAKE_CURRENT_SOURCE_DIR}/cmake/system/detectSSE.c
         CMAKE_FLAGS
         COMPILE_DEFINITIONS ${HUMMSTRUMM_REQUIRED_DEFINITIONS}
         COMPILE_OUTPUT_VARIABLE COMPILE_OUTPUT_VAR)
if (${RUN_RESULT_VAR})
  set (HUMMSTRUMM_HAVE_SSE_SUPPORT ON)
endif (${RUN_RESULT_VAR})

configure_file (${CMAKE_SOURCE_DIR}/config.h.in
                ${CMAKE_BINARY_DIR}/engine/include/config.h @ONLY)
configure_file (${CMAKE_SOURCE_DIR}/config.h.in
                ${CMAKE_BINARY_DIR}/game/include/config.h @ONLY)
#set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
#              ${CMAKE_BINARY_DIR}/engine/include/config.h
#              ${CMAKE_BINARY_DIR}/game/include/config.h)

add_subdirectory (engine)
add_subdirectory (game)
add_subdirectory (res)

if (HUMMSTRUMM_PLATFORM_WINDOWS)
  add_subdirectory (CPPUnit)
endif (HUMMSTRUMM_PLATFORM_WINDOWS)
