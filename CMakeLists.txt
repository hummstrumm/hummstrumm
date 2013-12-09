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

# This is the CMake script that is used to build the Humm and Strumm Engine.
# This script deals with these things:
#
#   * Creating configuration values that can be set with ``ccmake''.
#   * Detecting basic system information.
#   * Configuring CTest and CPack for unit testing and packaging, respectively.

project (hummstrummengine)
cmake_minimum_required (VERSION 2.8)

set (CMAKE_MODULE_PATH
  ${hummstrummengine_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include (Flags)
include (Defaults)
include (CompilerChecks)
include (CheckClone)
include (Version)
include (Platform)
include (Uninstall)

include (CheckPackages)

include (CppCheck)
include (CTest)

# Use some flags across the entire project:
if (HUMMSTRUMM_ENGINE_COMPILER_CLANG OR HUMMSTRUMM_ENGINE_COMPILER_GCC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wstrict-overflow=5")
endif ()
if (HUMMSTRUMM_ENGINE_COMPILER_MSVC)
  # Seems like CMAKE_CXX_FLAGS already sets "/W3" by default
  string (REGEX REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  set (CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /W4")
endif ()

# Test for SIMD
set (HUMMSTRUMM_ENGINE_USE_SSE ON CACHE BOOL
     "Whether to build the engine with SSE support or not.")
set (HUMMSTRUMM_ENGINE_HAVE_SSE_SUPPORT OFF)

if (HUMMSTRUMM_ENGINE_USE_SSE)
  try_run (RUN_RESULT_VAR COMPILE_RESULT_VAR
           ${CMAKE_BINARY_DIR}
           ${CMAKE_CURRENT_SOURCE_DIR}/cmake/system/detectSSE.c
           CMAKE_FLAGS
           COMPILE_DEFINITIONS ${HUMMSTRUMM_ENGINE_REQUIRED_DEFINITIONS}
           COMPILE_OUTPUT_VARIABLE COMPILE_OUTPUT_VAR)
  #message (STATUS ${COMPILE_OUTPUT_VAR})
  if (${RUN_RESULT_VAR})
    set (HUMMSTRUMM_ENGINE_HAVE_SSE_SUPPORT ON)
    set (HUMMSTRUMM_ENGINE_DOXYGEN_MACROS "${HUMMSTRUMM_ENGINE_DOXYGEN_MACROS} HUMMSTRUMM_ENGINE_HAVE_SSE_SUPPORT=")
    if (HUMMSTRUMM_ENGINE_COMPILER_CLANG OR HUMMSTRUMM_ENGINE_COMPILER_GCC)
      add_definitions("-msse")
#      add_definitions("-msse4.1")
#      add_definitions("-msse4.2")
    endif ()
  endif (${RUN_RESULT_VAR})
endif (HUMMSTRUMM_ENGINE_USE_SSE)

configure_file (${CMAKE_SOURCE_DIR}/include/config.h.in
                ${CMAKE_BINARY_DIR}/include/config.h @ONLY)

if (ENABLE_UNIT_TESTS)
  if (NOT PERL_FOUND)
    message (WARNING "Perl not found on the system.  The Perl ``prove'' "
      "command is required for unit testing.")
    set (IS_BUILDING_UNIT_TESTS OFF)
  else ()
    set (IS_BUILDING_UNIT_TESTS ON)
    enable_testing ()
    add_subdirectory (tests)
  endif ()
else ()
  set (IS_BUILDING_UNIT_TESTS ON)
endif ()

# Source Groups
#  Root
set (root_HEADERS include/config.h.in ${CMAKE_BINARY_DIR}/include/config.h include/hummstrummengine.hpp)

source_group("Header Files" FILES ${root_HEADERS})

#  Core
set (core_HEADERS include/core/engine.hpp)
set (core_SRCS src/core/engine.cpp)

source_group("Header Files\\core" FILES ${core_HEADERS})
source_group("Source Files\\core" FILES ${core_SRCS})

#  Date
set (date_HEADERS
  include/date/date.hpp
  include/date/date.inl
  include/date/duration.hpp
  include/date/duration.inl
  include/date/timezone.hpp)
set (date_SRCS
  src/date/timezone.cpp
  src/date/duration.cpp
  src/date/date.cpp)

source_group("Header Files\\date" FILES ${date_HEADERS})
source_group("Source Files\\date" FILES ${date_SRCS})

#  Debug
set (debug_HEADERS
  include/debug/logging/backend.hpp
  include/debug/logging/backend.inl
  include/debug/logging/level.hpp
  include/debug/logging/manip.hpp
  include/debug/logging/manip.inl
  include/debug/logging/streambuffer.hpp
  include/debug/logging/streambuffer.inl
  include/debug/profiler.hpp
  include/debug/profiler.inl
  include/debug/utils.hpp)
set (debug_SRCS
  src/debug/logging/streambuffer.cpp
  src/debug/logging/backend.cpp
  src/debug/logging/manip.cpp)

source_group("Header Files\\debug" FILES ${debug_HEADERS})
source_group("Source Files\\debug" FILES ${debug_SRCS})

#  Events
set (events_HEADERS include/events/windowevents.hpp)
set (events_SRCS src/events/windowevents.cpp)

source_group("Header Files\\events" FILES ${events_HEADERS})
source_group("Source Files\\events" FILES ${events_SRCS})

#  Geometry
set (geometry_HEADERS
  include/geometry/boundingbox.hpp
  include/geometry/boundingbox.inl
  include/geometry/boundingsphere.hpp
  include/geometry/boundingsphere.inl
  include/geometry/geomutils.hpp
  include/geometry/plane.hpp
  include/geometry/plane.inl
  include/geometry/segment.hpp
  include/geometry/segment.inl)

source_group("Header Files\\geometry" FILES ${geometry_HEADERS})

#  Math
set (math_HEADERS
  include/math/mathutils.hpp
  include/math/mathutils.inl
  include/math/matrix.hpp
  include/math/matrix.inl
  include/math/quaternion.hpp
  include/math/quaternion.inl
  include/math/simd.hpp
  include/math/vector.hpp
  include/math/vector.inl)
set (math_SRCS src/math/mathutils.cpp)

if (HUMMSTRUMM_ENGINE_HAVE_SSE_SUPPORT)
  list (APPEND math_SRCS
        src/math/vector.cpp)
endif (HUMMSTRUMM_ENGINE_HAVE_SSE_SUPPORT)

source_group("Header Files\\math" FILES ${math_HEADERS})
source_group("Source Files\\math" FILES ${math_SRCS})

#  System
set (system_HEADERS
  include/system/clock.hpp
  include/system/clock.inl
  include/system/endianness.hpp
  include/system/endianness.inl
  include/system/memory.hpp
  include/system/memory.inl
  include/system/platform.hpp
  include/system/platform.inl
  include/system/processors.hpp
  include/system/processors.inl)
set (system_SRCS  src/system/endianness.cpp)

source_group("Header Files\\system" FILES ${system_HEADERS})
source_group("Source Files\\system" FILES ${system_SRCS})

#  Types
set (types_HEADERS include/types/inttypes.hpp)

source_group("Header Files\\types" FILES ${types_HEADERS})

#  Util
set (util_HEADERS include/util/optimizations.hpp)

source_group("Header Files\\util" FILES ${util_HEADERS})

#  Window
set (window_HEADERS
  include/window/glext.h
  include/window/glxext.h
  include/window/wglext.h
  include/window/windowsystem.hpp
  include/window/windowvisualinfo.hpp)
set (window_SRCS src/window/windowvisualinfo.cpp)

#  Windows-Only Source Files
if (HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS)
  list (APPEND window_SRCS
        src/system/windows/processors.cpp
        src/system/windows/memory.cpp
        src/system/windows/platform.cpp
        src/system/windows/clock.cpp)
endif (HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS)

if (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_X11)
  list (APPEND window_SRCS
        src/window/x11/windowsystem.cpp)
endif (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_X11)

if (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_WINDOWS)
  list (APPEND window_SRCS
        src/window/win/windowsystem.cpp)
endif (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_WINDOWS)

# POSIX Source Files
if (HUMMSTRUMM_ENGINE_PLATFORM_POSIX)
  list (APPEND window_SRCS
        src/system/posix/platform.cpp
        src/system/posix/clock.cpp
        src/system/posix/processors.cpp
        src/system/posix/memory.cpp)
endif ()

# GNU/Linux-only Source Files
if (HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX)
  # We override the POSIX version.
  list (REMOVE_ITEM window_SRCS
        src/system/posix/processors.cpp
        src/system/posix/memory.cpp)
  list (APPEND window_SRCS
        src/system/gnulinux/processors.cpp
        src/system/gnulinux/memory.cpp)
endif (HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX)

# *BSD-only Source Files
if (HUMMSTRUMM_ENGINE_PLATFORM_BSD)
  # We override the POSIX version.
  list (REMOVE_ITEM window_SRCS
        src/system/posix/processors.cpp
        src/system/posix/memory.cpp)
  list (APPEND window_SRCS
        src/system/bsd/processors.cpp
        src/system/bsd/memory.cpp)
endif (HUMMSTRUMM_ENGINE_PLATFORM_BSD)

source_group("Header Files\\window" FILES ${window_HEADERS})
source_group("Source Files\\window" FILES ${window_SRCS})


set (hummstrummengine_SRCS
  ${root_HEADERS}
  ${util_HEADERS}
  ${core_HEADERS}
  ${core_SRCS}
  ${date_HEADERS}
  ${date_SRCS}
  ${debug_HEADERS}
  ${debug_SRCS}
  ${events_HEADERS}
  ${events_SRCS}
  ${geometry_HEADERS}
  ${math_HEADERS}
  ${math_SRCS}
  ${system_HEADERS}
  ${system_SRCS}
  ${types_HEADERS}
  ${util_HEADERS}
  ${window_HEADERS}
  ${window_SRCS})

# Set include dirs
set (hummstrummengine_INCLUDE include/
                              lib/
                              ${CMAKE_CURRENT_BINARY_DIR}/include/
                              ${OPENGL_INCLUDE_DIR})

include_directories (${hummstrummengine_INCLUDE})
if (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_X11)
  include_directories (${X11_INCLUDE_DIR})
endif (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_X11)

# Build the library.
add_library (hummstrummengine STATIC ${hummstrummengine_SRCS})

# Add directories (to be exported, too)
if (HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS)
  set (HUMMSTRUMM_ENGINE_INSTALL_HEADERS   include)
  set (HUMMSTRUMM_ENGINE_INSTALL_LIBRARIES lib)
  set (HUMMSTRUMM_ENGINE_INSTALL_DOC       doc)
else ()
  set (HUMMSTRUMM_ENGINE_INSTALL_HEADERS
       include/hummstrummengine-${HUMMSTRUMM_ENGINE_VERSION})
  set (HUMMSTRUMM_ENGINE_INSTALL_LIBRARIES
       lib/hummstrummengine-${HUMMSTRUMM_ENGINE_VERSION})
  set (HUMMSTRUMM_ENGINE_INSTALL_DOC
       share/doc/hummstrummengine-${HUMMSTRUMM_ENGINE_VERSION})
endif (HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS)

# Add documentation generation
add_subdirectory (doc)

# Install library.
install (TARGETS hummstrummengine
         ARCHIVE DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_LIBRARIES})


# Install documentation.
if (HUMMSTRUMM_ENGINE_BUILD_DOCS)
  install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html
           DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_DOC})
endif (HUMMSTRUMM_ENGINE_BUILD_DOCS)


# Install header files.
install (DIRECTORY include/
         DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_HEADERS}
         FILES_MATCHING PATTERN "*.h"
                        PATTERN "*.hpp"
                        PATTERN "*.inl"
                        REGEX "/*[.]svn" EXCLUDE)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/include/config.h
         DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_HEADERS})

set (HUMMSTRUMM_ENGINE_PKGCONFIG_FILENAME hummstrummengine-${HUMMSTRUMM_ENGINE_VERSION}.pc)

if (HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX OR HUMMSTRUMM_ENGINE_PLATFORM_BSD)
  if ($ENV{PKG_CONFIG_PATH})
    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${HUMMSTRUMM_ENGINE_PKGCONFIG_FILENAME}
             DESTINATION $ENV{PKG_CONFIG_PATH})
  else ()
    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${HUMMSTRUMM_ENGINE_PKGCONFIG_FILENAME}
             DESTINATION lib/pkgconfig)
    message (STATUS "Be sure to set your $PKG_CONFIG_PATH variable to ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig if pkg-config can't find the Humm and Strumm engine.")
  endif ($ENV{PKG_CONFIG_PATH})
endif (HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX OR HUMMSTRUMM_ENGINE_PLATFORM_BSD)


configure_file (${CMAKE_SOURCE_DIR}/hummstrummengine.pc.in
                ${CMAKE_BINARY_DIR}/${HUMMSTRUMM_ENGINE_PKGCONFIG_FILENAME}
                @ONLY)

include (VariableLogging)
