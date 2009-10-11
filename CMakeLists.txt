# Humm and Strumm Video Game
# Copyright (C) 2008-2009, the people listed in the AUTHORS file. 
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

project (hummstrumm)
cmake_minimum_required (VERSION 2.6)

set (HUMMSTRUMM_VERSION "Humm and Strumm, version 0.0 (pre-alpha)")

if (WIN32)
  set (HUMMSTRUMM_PLATFORM_WINDOWS ON)
  set (HUMMSTRUMM_PLATFORM_GNULINUX OFF)
  
  set (HUMMSTRUMM_WINDOWSYSYEM_WINDOWS ON)
  set (HUMMSTRUMM_WINDOWSYSYEM_X11 OFF)
  
  if (CMAKE_SIZEOF_VOID_P EQUALS 4)
    set (HUMMSTRUMM_PLATFORM_WIN32 ON)
    set (HUMMSTRUMM_PLATFORM_WIN64 OFF)
  else (CMAKE_SIZEOF_VOID_P EQUALS 4)
    if (CMAKE_SIZEOF_VOID_P EQUALS 8)
      set (HUMMSTRUMM_PLATFORM_WIN32 OFF)
      set (HUMMSTRUMM_PLATFORM_WIN64 ON)
    endif (CMAKE_SIZEOF_VOID_P EQUALS 8)
  endif (CMAKE_SIZEOF_VOID_P EQUALS 4)
else (WIN32)
  if (UNIX)
    set (HUMMSTRUMM_PLATFORM_WINDOWS OFF)
    set (HUMMSTRUMM_PLATFORM_GNULINUX ON)
    
    set (HUMMSTRUMM_WINDOWSYSYEM_WINDOWS OFF)
    set (HUMMSTRUMM_WINDOWSYSYEM_X11 ON)
  endif (UNIX)
endif (WIN32)

option (HUMMSTRUMM_HEAP_SIZE "The game engine starting heap size." 65536)
option (HUMMSTRUMM_HEAP_EXPAND "The size by which to expand the heap." 4096)

option (HUMMSTRUMM_HEAP_BESTFIT "Enable best fit heap mode (DEFAULT=ON)." ON)
option (HUMMSTRUMM_MATH_PRECISE "Enable precise math mode (DEFAULT=ON)." ON)

configure_file (${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_SOURCE_DIR}/engine/include/config.h @ONLY)
configure_file (${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_SOURCE_DIR}/game/include/config.h @ONLY)

add_subdirectory (engine)
add_subdirectory (game)
