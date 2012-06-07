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

if (HUMMSTRUMM_UNIT_TEST)
  add_subdirectory (tests/)
endif (HUMMSTRUMM_UNIT_TEST)

# Common Source Files
set (hummstrummengine_SRCS
  src/debug/log.cpp
  src/debug/profiler.cpp
  src/error/error.cpp
  src/error/generic.cpp
  src/error/outofmemory.cpp
  src/error/outofrange.cpp
  src/error/divisionbyzero.cpp
  src/error/unicode.cpp
  src/error/memorycorruption.cpp
  src/error/invalidparam.cpp
  src/error/windowsystem.cpp
  src/error/iterator.cpp
  src/core/type.cpp
  src/core/object.cpp
  src/core/allocationtable.cpp
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

# GNU/Linux-only Source Files
if (HUMMSTRUMM_PLATFORM_GNULINUX)
  list (APPEND hummstrummengine_SRCS
        src/system/gnulinux/processors.cpp
        src/system/gnulinux/memory.cpp
        src/system/gnulinux/platform.cpp
        src/system/posix/clock.cpp)
endif (HUMMSTRUMM_PLATFORM_GNULINUX)

# *BSD-only Source Files
if (HUMMSTRUMM_PLATFORM_BSD)
  list (APPEND hummstrummengine_SRCS
        src/system/bsd/processors.cpp
        src/system/bsd/memory.cpp
        src/system/bsd/platform.cpp
        src/system/posix/clock.cpp)
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

if (HUMMSTRUMM_DEBUG)
  if (HUMMSTRUMM_COMPILER_GCC)
    add_definitions("-g")
  endif (HUMMSTRUMM_COMPILER_GCC)
endif (HUMMSTRUMM_DEBUG)

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
