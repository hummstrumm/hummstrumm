# Humm and Strumm Engine
# Copyright (C) 2008-2014, the people listed in the AUTHORS file. 
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

list (INSERT CMAKE_MODULE_PATH 0 ${hummstrummengine_SOURCE_DIR}/cmake)

include (Version)
include (Configuration)
include (CompilerChecks)
include (Defaults)
include (Platform)
include (Uninstall)

include (CheckPackages)

include (CppCheck)
include (CTest)
include (PkgConfig)
include (SourceGroups)

include (Dist)

configure_file (${CMAKE_SOURCE_DIR}/include/config.h.in
                ${CMAKE_BINARY_DIR}/include/config.h @ONLY)

if (WITH_UNIT_TESTS)
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
set (root_HEADERS include/config.h.in include/hummstrummengine.hpp)
source_group("Header Files" FILES ${root_HEADERS})
set(hummstrummengine_SRCS ${root_HEADERS})

make_source_group ("core" "engine.cpp" "engine.hpp" "")
make_source_group ("debug" "" "profiler.hpp;utils.hpp" "profiler.inl")
make_source_group ("debug/logging"
  "streambuffer.cpp;backend.cpp;manip.cpp"
  "backend.hpp;level.hpp;manip.hpp;streambuffer.hpp"
  "backend.inl;manip.inl;streambuffer.inl")
make_source_group ("events" "windowevents.cpp" "windowevents.hpp" "")
make_source_group("system"
  "endianness.cpp"
  "endianness.hpp;memory.hpp;platform.hpp;processors.hpp"
  "endianness.inl;memory.inl;platform.inl;processors.inl")
make_source_group("types" "" "inttypes.hpp" "")
make_source_group("util" "" "optimizations.hpp;termcolors.hpp" "termcolors.inl")
make_source_group("window"
  "windowvisualinfo.cpp"
  "glext.h;glxext.h;wglext.h;windowsystem.hpp;windowvisualinfo.hpp" "")

# System specific files
if (HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS)
  make_source_group("system"
    "windows/processors.cpp;windows/memory.cpp;windows/platform.cpp" "" "")
endif ()

if (HUMMSTRUMM_ENGINE_PLATFORM_POSIX)
  make_source_group("system" "posix/platform.cpp" "" "")
  if (NOT HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX AND
      NOT HUMMSTRUMM_ENGINE_PLATFORM_BSD)
    make_source_group("system" "posix/processors.cpp;posix/memory.cpp" "" "")
  endif()
endif ()

if (HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX)
  make_source_group("system"
    "gnulinux/processors.cpp;gnulinux/memory.cpp" "" "")
endif()

if (HUMMSTRUMM_ENGINE_PLATFORM_BSD)
  make_source_group("system" "bsd/processors.cpp;bsd/memory.cpp" "" "")
endif()

# Window System specific files
if (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_X11)
  make_source_group("window" "x11/windowsystem.cpp" "" "")
endif()

if (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_WINDOWS)
  make_source_group("window" "win/windowsystem.cpp" "" "")
endif()

# Set include dirs
set (hummstrummengine_INCLUDE include/
                              lib/
                              ${CMAKE_CURRENT_BINARY_DIR}/include/
                              ${OPENGL_INCLUDE_DIR}
                              ${EIGEN3_INCLUDE_DIR})

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
                        PATTERN "*.inl")
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/include/config.h
         DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_HEADERS})

include (VariableLogging)
