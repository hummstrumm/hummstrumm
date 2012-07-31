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

# This is the CMake script that is used to build Humm and Strumm.  This script
# deals with these things:
#
#   * Creating configuration values that can be set with ``ccmake''.
#   * Detecting basic system information.
#   * Configuring CTest and CPack for unit testing and packaging, respectively.

project (hummstrumm)
cmake_minimum_required (VERSION 2.8)

set (CMAKE_MODULE_PATH ${hummstrumm_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include (Defaults)
include (CompilerChecks)
include (CheckClone)
include (Version)
include (Platform)
include (MaintainerMode)
include (Uninstall)

# We want testing with CTest.
include (UnitTest)
enable_testing ()

include (CheckPrograms)
include (CheckX11)
include (CheckGL)

# Use some flags across the entire project:
if (HUMMSTRUMM_PLATFORM_GNULINUX OR HUMMSTRUMM_PLATFORM_BSD)
  set (CMAKE_CXX_FLAGS_DEBUG "-pedantic -Wall -g -ggdb -Wfatal-errors")
endif (HUMMSTRUMM_PLATFORM_GNULINUX OR HUMMSTRUMM_PLATFORM_BSD)
if (HUMMSTRUMM_PLATFORM_WINDOWS)
  # Seems like CMAKE_CXX_FLAGS already sets "/W3" by default
  string (REGEX REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  set (CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /W4")
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
    set (HUMMSTRUMM_DOXYGEN_MACROS "${HUMMSTRUMM_DOXYGEN_MACROS} HUMMSTRUMM_HAVE_SSE_SUPPORT=")
    if (HUMMSTRUMM_PLATFORM_GNULINUX OR HUMMSTRUMM_PLATFORM_BSD)
      add_definitions("-msse")
#      add_definitions("-msse4.1")
#      add_definitions("-msse4.2")
    endif (HUMMSTRUMM_PLATFORM_GNULINUX OR HUMMSTRUMM_PLATFORM_BSD)
  endif (${RUN_RESULT_VAR})
endif (HUMMSTRUMM_USE_SSE)

configure_file (${CMAKE_SOURCE_DIR}/config.h.in
                ${CMAKE_BINARY_DIR}/engine/include/config.h @ONLY)
                configure_file (${CMAKE_SOURCE_DIR}/config.h.in
                ${CMAKE_BINARY_DIR}/game/include/config.h @ONLY)

if (HUMMSTRUMM_UNIT_TEST)
  add_subdirectory (tests/)
endif (HUMMSTRUMM_UNIT_TEST)

# Common Source Files
set (hummstrummengine_SRCS
  src/debug/logging/streambuffer.cpp
  src/debug/logging/backend.cpp
  src/debug/logging/manip.cpp
  src/debug/profiler.cpp
  src/core/engine.cpp
  src/date/timezone.cpp
  src/date/duration.cpp
  src/date/date.cpp
  src/system/endianness.cpp
  src/math/mathutils.cpp
  src/events/windowevents.cpp
  src/window/windowvisualinfo.cpp)

if (HUMMSTRUMM_HAVE_SSE_SUPPORT)
  list (APPEND hummstrummengine_SRCS
        src/math/vector.cpp)
endif (HUMMSTRUMM_HAVE_SSE_SUPPORT)

# Windows-Only Source Files
if (HUMMSTRUMM_PLATFORM_WINDOWS)
  list (APPEND hummstrummengine_SRCS
        src/system/windows/processors.cpp
        src/system/windows/memory.cpp
        src/system/windows/platform.cpp
        src/system/windows/clock.cpp)
endif (HUMMSTRUMM_PLATFORM_WINDOWS)

# POSIX Source Files
if (HUMMSTRUMM_PLATFORM_POSIX)
  list (APPEND hummstrummengine_SRCS
        src/system/posix/platform.cpp
        src/system/posix/clock.cpp
        src/system/posix/processors.cpp
        src/system/posix/memory.cpp)
endif ()

# GNU/Linux-only Source Files
if (HUMMSTRUMM_PLATFORM_GNULINUX)
  # We override the POSIX version.
  list (REMOVE_ITEM hummstrummengine_SRCS
        src/system/posix/processors.cpp
        src/system/posix/memory.cpp)
  list (APPEND hummstrummengine_SRCS
        src/system/gnulinux/processors.cpp
        src/system/gnulinux/memory.cpp)
endif (HUMMSTRUMM_PLATFORM_GNULINUX)

# *BSD-only Source Files
if (HUMMSTRUMM_PLATFORM_BSD)
  # We override the POSIX version.
  list (REMOVE_ITEM hummstrummengine_SRCS
        src/system/posix/processors.cpp
        src/system/posix/memory.cpp)
  list (APPEND hummstrummengine_SRCS
        src/system/bsd/processors.cpp
        src/system/bsd/memory.cpp)
endif (HUMMSTRUMM_PLATFORM_BSD)

if (HUMMSTRUMM_WINDOWSYSTEM_X11)
  list (APPEND hummstrummengine_SRCS
        src/window/x11/windowsystem.cpp)
endif (HUMMSTRUMM_WINDOWSYSTEM_X11)

if (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
  list (APPEND hummstrummengine_SRCS
        src/window/win/windowsystem.cpp)
endif (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)


# Set include dirs
set (hummstrummengine_INCLUDE include/
                              ${CMAKE_CURRENT_BINARY_DIR}/include/
                              ${OPENGL_INCLUDE_DIR})

include_directories (${hummstrummengine_INCLUDE})
if (HUMMSTRUMM_WINDOWSYSTEM_X11)
  include_directories (${X11_INCLUDE_DIR})
endif (HUMMSTRUMM_WINDOWSYSTEM_X11)

# Build the library.
add_library (hummstrummengine STATIC ${hummstrummengine_SRCS})



# Add directories (to be exported, too)
if (HUMMSTRUMM_PLATFORM_WINDOWS)
  set (HUMMSTRUMM_ENGINE_INSTALL_HEADERS   include)
  set (HUMMSTRUMM_ENGINE_INSTALL_LIBRARIES lib)
  set (HUMMSTRUMM_ENGINE_INSTALL_DOC       doc)
else ()
  set (HUMMSTRUMM_ENGINE_INSTALL_HEADERS
       include/hummstrummengine-${HUMMSTRUMM_VERSION})
  set (HUMMSTRUMM_ENGINE_INSTALL_LIBRARIES
       lib/hummstrummengine-${HUMMSTRUMM_VERSION})
  set (HUMMSTRUMM_ENGINE_INSTALL_DOC
       share/doc/hummstrummengine-${HUMMSTRUMM_VERSION})
endif (HUMMSTRUMM_PLATFORM_WINDOWS)

# Add documentation generation
add_subdirectory (doc)

# Install library.
install (TARGETS hummstrummengine
         ARCHIVE DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_LIBRARIES})


# Install documentation.
if (HUMMSTRUMM_BUILD_DOCS)

  if (HUMMSTRUMM_BUILD_DOCS_LATEX)
    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/doc/latex/refman.pdf
             DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_DOC})
  endif (HUMMSTRUMM_BUILD_DOCS_LATEX)

  install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html
           DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_DOC})
endif (HUMMSTRUMM_BUILD_DOCS)


# Install header files.
install (DIRECTORY include/
         DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_HEADERS}
         FILES_MATCHING PATTERN "*.h"
                        PATTERN "*.hpp"
                        PATTERN "*.inl"
                        REGEX "/*[.]svn" EXCLUDE)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/include/config.h
         DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_HEADERS})

set (HUMMSTRUMM_PKGCONFIG_FILENAME hummstrummengine-${HUMMSTRUMM_VERSION}.pc)

if (HUMMSTRUMM_PLATFORM_GNULINUX OR HUMMSTRUMM_PLATFORM_BSD)
  if ($ENV{PKG_CONFIG_PATH})
    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${HUMMSTRUMM_PKGCONFIG_FILENAME}
             DESTINATION $ENV{PKG_CONFIG_PATH})
  else ()
    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${HUMMSTRUMM_PKGCONFIG_FILENAME}
             DESTINATION lib/pkgconfig)
    message (STATUS "Be sure to set your $PKG_CONFIG_PATH variable to ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig if pkg-config can't find the Humm and Strumm engine.")
  endif ($ENV{PKG_CONFIG_PATH})
endif (HUMMSTRUMM_PLATFORM_GNULINUX OR HUMMSTRUMM_PLATFORM_BSD)


configure_file (${CMAKE_CURRENT_SOURCE_DIR}/hummstrummengine.pc.in
                ${CMAKE_CURRENT_BINARY_DIR}/${HUMMSTRUMM_PKGCONFIG_FILENAME}
                @ONLY)

include (VariableLogging)