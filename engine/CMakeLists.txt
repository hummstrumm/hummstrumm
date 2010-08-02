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
  src/core/type.cpp
  src/core/object.cpp
  src/core/heap.cpp
  src/types/date.cpp
  src/types/character.cpp
  src/types/number.cpp
  src/types/string.cpp
  src/system/endian.cpp
  src/math/vector.cpp
  src/renderer/windowX11.cpp
  src/types/inttypes.cpp)
if (HUMMSTRUMM_PLATFORM_WINDOWS)
  set (hummstrummengine_SRCS
    ${hummstrummengine_SRCS}
    src/core/object-win64.asm)
endif (HUMMSTRUMM_PLATFORM_WINDOWS)

set (hummstrummengine_INCLUDE include/)
if (HUMMSTRUMM_PLATFORM_GNULINUX)
  set (CMAKE_C_FLAGS_DEBUG "-w -g -ggdb")
endif (HUMMSTRUMM_PLATFORM_GNULINUX)

include_directories (${hummstrummengine_INCLUDE})
add_library (hummstrummengine STATIC ${hummstrummengine_SRCS})

# Add documentation generation
include (UseDoxygen OPTIONAL)

if (HUMMSTRUMM_BUILD_DOCS)
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
  install (FILES doc/latex/refman.pdf
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
