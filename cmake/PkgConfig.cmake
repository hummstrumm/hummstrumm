# Humm and Strumm Engine
# Copyright (C) 2014, the people listed in the AUTHORS file. 
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

# PkgConfig.cmake -- Configures the pkgconfig file on POSIX systems.

set (HUMMSTRUMM_ENGINE_PKGCONFIG_FILENAME
  hummstrummengine-${HUMMSTRUMM_ENGINE_VERSION}.pc)

if (HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX OR HUMMSTRUMM_ENGINE_PLATFORM_BSD)
  if ($ENV{PKG_CONFIG_PATH})
    install (FILES
      ${CMAKE_CURRENT_BINARY_DIR}/${HUMMSTRUMM_ENGINE_PKGCONFIG_FILENAME}
      DESTINATION $ENV{PKG_CONFIG_PATH})
  else ()
    install (FILES
      ${CMAKE_CURRENT_BINARY_DIR}/${HUMMSTRUMM_ENGINE_PKGCONFIG_FILENAME}
      DESTINATION lib/pkgconfig)
    message (STATUS "Be sure to set your $PKG_CONFIG_PATH variable to ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig if pkg-config can't find the Humm and Strumm engine.")
  endif ($ENV{PKG_CONFIG_PATH})
endif (HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX OR HUMMSTRUMM_ENGINE_PLATFORM_BSD)


configure_file (${CMAKE_SOURCE_DIR}/hummstrummengine.pc.in
  ${CMAKE_BINARY_DIR}/${HUMMSTRUMM_ENGINE_PKGCONFIG_FILENAME}
  @ONLY)