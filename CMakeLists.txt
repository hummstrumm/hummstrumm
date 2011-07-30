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

include (CheckWorkingCopy)
include (Defaults)
include (Version)
include (Platform)
include (MaintainerMode)
include (Uninstall)

# We want testing with CTest.
include (UnitTest)
enable_testing ()

include (CheckX11)
include (CheckGL)

# Use some flags across the entire project:
if (HUMMSTRUMM_PLATFORM_GNULINUX OR HUMMSTRUMM_PLATFORM_BSD)
  set (CMAKE_CXX_FLAGS_DEBUG "-w -g -ggdb -Wfatal-errors")
endif (HUMMSTRUMM_PLATFORM_GNULINUX OR HUMMSTRUMM_PLATFORM_BSD)
if (HUMMSTRUMM_PLATFORM_WINDOWS)
  set (CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /W 4")
endif (HUMMSTRUMM_PLATFORM_WINDOWS)


# Test for SIMD
set (HUMMSTRUMM_USE_SSE ON CACHE BOOL
     "Whether to build the engine with SSE support or not.")
set (HUMMSTRUMM_HAVE_SSE_SUPPORT OFF)

if (HUMMSTRUMM_USE_SSE)
  try_run (RUN_RESULT_VAR COMPILE_RESULT_VAR
           ${CMAKE_BINARY_DIR}
           ${CMAKE_CURRENT_SOURCE_DIR}/cmake/system/detectSSE.c
           CMAKE_FLAGS
           COMPILE_DEFINITIONS ${HUMMSTRUMM_REQUIRED_DEFINITIONS}
           COMPILE_OUTPUT_VARIABLE COMPILE_OUTPUT_VAR)
  #message (STATUS ${COMPILE_OUTPUT_VAR})
  if (${RUN_RESULT_VAR})
    set (HUMMSTRUMM_HAVE_SSE_SUPPORT ON)
    if (HUMMSTRUMM_PLATFORM_GNULINUX OR HUMMSTRUMM_PLATFORM_BSD)
      add_definitions("-msse")
      add_definitions("-msse4.1")
      add_definitions("-msse4.2")
    endif (HUMMSTRUMM_PLATFORM_GNULINUX OR HUMMSTRUMM_PLATFORM_BSD)
  endif (${RUN_RESULT_VAR})
endif (HUMMSTRUMM_USE_SSE)

configure_file (${CMAKE_SOURCE_DIR}/config.h.in
                ${CMAKE_BINARY_DIR}/engine/include/config.h @ONLY)
configure_file (${CMAKE_SOURCE_DIR}/config.h.in
                ${CMAKE_BINARY_DIR}/game/include/config.h @ONLY)

add_subdirectory (engine)
add_subdirectory (game)
add_subdirectory (res)

include (VariableLogging)
