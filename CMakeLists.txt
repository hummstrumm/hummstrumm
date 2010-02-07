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

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "The Humm and Strumm Free Adventure Video Game")
set(CPACK_PACKAGE_VENDOR
    "The Humm and Strumm Project")
set(CPACK_PACKAGE_DESCRIPTION_FILE
    "${CMAKE_CURRENT_SOURCE_DIR}/README")
set(CPACK_RESOURCE_FILE_LICENSE
    "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Humm and Strumm")
#if(WIN32 and not UNIX)
#  # There is a bug in NSI that does not handle full unix paths properly. Make
#  # sure there is at least one set of four (4) backlasshes.
#  set(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
#  set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
#  set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} My Famous Project")
#  set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
#  set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
#  set(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
#  set(CPACK_NSIS_MODIFY_PATH ON)
#endif(WIN32 and not UNIX)
#if(UNIX and not WIN32)
#  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Patrick Niedzielski <PatrickNiedzielski@gmail.com>")
#  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The Humm and Strumm Free Adventure Video Game")
#  set(CPACK_PACKAGE_DESCRIPTION "In a world where logic is frowned upon, two (sometimes three) heroes rise from the back alley way of a news paper corporation...\nHumm and Strumm\n...Saving the world (well, sort of) one hamburger at a time.\nJoin them as they travel throughout a psychedelic world of music, excitement, fire, junk food, stick figures, coconuts, and disco.\nThis game is fully three-dimensional, with a breath-taking musical soundtrack.\nBut, they don't have to brave it alone...usually. Also play as a fun loving bubble blower at times during their quest(s).\nThis game is completely open-source, released under the GNU GPL 3.0, which means that you can freely download, edit, and use this game however you want.")
#  set(CPACK_DEBIAN_PACKAGE_DEPENDS	"libc6 (>= 2.7-18)")
#  set(CPACK_DEBIAN_PACKAGE_SECTION	"Games")
#  set(CPACK_DEBIAN_PACKAGE_VERSION 0.1)
#endif(UNIX and not WIN32)
set(CPACK_PACKAGE_EXECUTABLES "hummstrumm" "Humm and Strumm")
include(CPack)

enable_testing()

set (HUMMSTRUMM_VERSION "Humm and Strumm, version 0.1")
set (HUMMSTRUMM_VERSION_NUMBER "0.1")

if (WIN32)
  set (HUMMSTRUMM_PLATFORM_WINDOWS ON)
  set (HUMMSTRUMM_PLATFORM_GNULINUX OFF)
  
  set (HUMMSTRUMM_WINDOWSYSYEM_WINDOWS ON)
  set (HUMMSTRUMM_WINDOWSYSYEM_X11 OFF)
  
  if (CMAKE_SIZEOF_VOID_P MATCHES "4")
    set (HUMMSTRUMM_PLATFORM_WIN32 ON)
    set (HUMMSTRUMM_PLATFORM_WIN64 OFF)
  else (CMAKE_SIZEOF_VOID_P MATCHES "4")
    if (CMAKE_SIZEOF_VOID_P MATCHES "8")
      set (HUMMSTRUMM_PLATFORM_WIN32 OFF)
      set (HUMMSTRUMM_PLATFORM_WIN64 ON)
    endif (CMAKE_SIZEOF_VOID_P MATCHES "8")
  endif (CMAKE_SIZEOF_VOID_P MATCHES "4")
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

option (COMPILE_ZLIB "Use the included zlib distribution (DEFAULT=ON)." ON)

set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

configure_file (${CMAKE_SOURCE_DIR}/config.h.in
                ${CMAKE_SOURCE_DIR}/engine/include/config.h @ONLY)
configure_file (${CMAKE_SOURCE_DIR}/engine/Doxyfile.in
                ${CMAKE_SOURCE_DIR}/engine/Doxyfile @ONLY)
configure_file (${CMAKE_SOURCE_DIR}/config.h.in
                ${CMAKE_SOURCE_DIR}/game/include/config.h @ONLY)

add_subdirectory (engine)
add_subdirectory (game)
