# Humm and Strumm Video Game
# Copyright (C) 2008-2010, the people listed in the AUTHORS file. 
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

add_subdirectory (tests/)

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
  src/error/iterator.cpp
  src/core/type.cpp
  src/core/object.cpp
  src/core/allocationtable.cpp
  src/core/engine.cpp
  src/accessors/accessor.cpp
  src/types/date.cpp
#  src/types/character.cpp
  src/types/number.cpp
#  src/types/string.cpp
  src/system/endianness.cpp
  src/math/vector.cpp
  src/types/inttypes.cpp
  src/events/windowEvents.cpp)

# Windows-Only Source Files
if (HUMMSTRUMM_PLATFORM_WINDOWS)
  list (APPEND hummstrummengine_SRCS
        src/system/windows/processors.cpp
        src/system/windows/memory.cpp
        src/system/windows/platform.cpp
        src/system/windows/clock.cpp)
  # enable_language (ASM_MASM)
  # list (APPEND hummstrummengine_SRCS
  #      src/core/object-win64.asm)
endif (HUMMSTRUMM_PLATFORM_WINDOWS)

# GNU-only Source Files
if (HUMMSTRUMM_PLATFORM_GNULINUX)
  list (APPEND hummstrummengine_SRCS
        src/system/gnulinux/processors.cpp
        src/system/gnulinux/memory.cpp
        src/system/gnulinux/platform.cpp
        src/system/gnulinux/clock.cpp)
endif (HUMMSTRUMM_PLATFORM_GNULINUX)

if (HUMMSTRUMM_PLATFORM_BSD)
  list (APPEND hummstrummengine_SRCS
        src/system/bsd/processors.cpp
        src/system/bsd/memory.cpp
        src/system/bsd/platform.cpp
        src/system/bsd/clock.cpp)
endif (HUMMSTRUMM_PLATFORM_BSD)

# Windows-only Window System Files
if (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
#  list (APPEND hummstrummengine_SRCS
#        src/renderer/windowWindows.cpp) # Or whatever.
endif (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)

# X11-only Window System Files
if (HUMMSTRUMM_WINDOWSYSTEM_X11)
  list (APPEND hummstrummengine_SRCS
        src/renderer/windowX11.cpp)
endif (HUMMSTRUMM_WINDOWSYSTEM_X11)

set (hummstrummengine_INCLUDE include/)
if (HUMMSTRUMM_PLATFORM_GNULINUX)
  set (CMAKE_CXX_FLAGS_DEBUG "-w -g -ggdb -Wfatal-errors")
  add_definitions( -msse)
  add_definitions( -msse4.1)
  add_definitions( -msse4.2)
endif (HUMMSTRUMM_PLATFORM_GNULINUX)

include_directories (${hummstrummengine_INCLUDE})
add_library (hummstrummengine STATIC ${hummstrummengine_SRCS})

# Add documentation generation
if (HUMMSTRUMM_BUILD_DOCS)
  if (HUMMSTRUMM_BUILD_DOCS_LATEX)
    set (DOXYFILE_LATEX YES)
  else ()
    set (DOXYFILE_LATEX NO)
  endif (HUMMSTRUMM_BUILD_DOCS_LATEX)
  include (UseDoxygen OPTIONAL)
  add_dependencies (hummstrummengine doc)
endif (HUMMSTRUMM_BUILD_DOCS)

# Add directories (to be exported, too)
if (HUMMSTRUMM_PLATFORM_WINDOWS)
  set (HUMMSTRUMM_ENGINE_INSTALL_HEADERS   include)
  set (HUMMSTRUMM_ENGINE_INSTALL_LIBRARIES lib)
  set (HUMMSTRUMM_ENGINE_INSTALL_DOC       doc)
else ()
  set (HUMMSTRUMM_ENGINE_INSTALL_HEADERS
       include/hummstrummengine-${HUMMSTRUMM_VERSION_NUMBER})
  set (HUMMSTRUMM_ENGINE_INSTALL_LIBRARIES
       lib/hummstrummengine-${HUMMSTRUMM_VERSION_NUMBER})
  set (HUMMSTRUMM_ENGINE_INSTALL_DOC
       share/doc/hummstrummengine-${HUMMSTRUMM_VERSION_NUMBER})
endif (HUMMSTRUMM_PLATFORM_WINDOWS)

# Install library and header files
install (TARGETS hummstrummengine 
         ARCHIVE DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_LIBRARIES})
if (HUMMSTRUMM_BUILD_DOCS)
  if (HUMMSTRUMM_BUILD_DOCS_LATEX)
    install (FILES doc/latex/refman.pdf
             DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_DOC})
  endif (HUMMSTRUMM_BUILD_DOCS_LATEX)
  install (DIRECTORY doc/html
           DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_DOC})
endif (HUMMSTRUMM_BUILD_DOCS)
install (FILES include/hummstrummengine.hpp
         DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_HEADERS})
install (DIRECTORY ${hummstrummengine_INCLUDE}
         DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_HEADERS}
         FILES_MATCHING PATTERN "*.h"
                        PATTERN "*.hpp"
                        PATTERN "*.inl"
                        PATTERN "hummstrummengine.hpp" EXCLUDE
                        REGEX "/*[.]svn" EXCLUDE)
if (HUMMSTRUMM_PLATFORM_GNULINUX)
  if ($ENV{PKG_CONFIG_PATH})
    install (FILES hummstrummengine-${HUMMSTRUMM_VERSION_NUMBER}.pc
             DESTINATION $ENV{PKG_CONFIG_PATH})
  else ()
    install (FILES hummstrummengine-${HUMMSTRUMM_VERSION_NUMBER}.pc
             DESTINATION lib/pkgconfig)
  endif ($ENV{PKG_CONFIG_PATH})
endif (HUMMSTRUMM_PLATFORM_GNULINUX)

configure_file (${CMAKE_SOURCE_DIR}/engine/hummstrummengine.pc.in
                ${CMAKE_SOURCE_DIR}/engine/hummstrummengine-${HUMMSTRUMM_VERSION_NUMBER}.pc @ONLY)
