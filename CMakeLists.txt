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

enable_testing ()

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
set(CPACK_PACKAGE_VERSION_MINOR "2")
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
if(UNIX)
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Patrick Niedzielski <PatrickNiedzielski@gmail.com>")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The Humm and Strumm Free Adventure Video Game")
  set(CPACK_PACKAGE_DESCRIPTION "In a world where logic is frowned upon, two (sometimes three) heroes rise from the back alley way of a news paper corporation...\nHumm and Strumm\n...Saving the world (well, sort of) one hamburger at a time.\nJoin them as they travel throughout a psychedelic world of music, excitement, fire, junk food, stick figures, coconuts, and disco.\nThis game is fully three-dimensional, with a breath-taking musical soundtrack.\nBut, they don't have to brave it alone...usually. Also play as a fun loving bubble blower at times during their quest(s).\nThis game is completely open-source, released under the GNU GPL 3.0, which means that you can freely download, edit, and use this game however you want.")
  set(CPACK_DEBIAN_PACKAGE_DEPENDS	"libc6 (>= 2.7-18)")
  set(CPACK_DEBIAN_PACKAGE_SECTION	"Games")
  set(CPACK_DEBIAN_PACKAGE_VERSION 0.1)
endif(UNIX)
set(CPACK_PACKAGE_EXECUTABLES "hummstrumm" "Humm and Strumm")
include(CPack)

set (HUMMSTRUMM_VERSION "Humm and Strumm, version 0.2")
set (HUMMSTRUMM_VERSION_NUMBER "0.3")

if (WIN32)
  set (HUMMSTRUMM_PLATFORM_WINDOWS ON)
  set (HUMMSTRUMM_PLATFORM_GNULINUX OFF)
  list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS "-DHUMMSTRUMM_PLATFORM_WINDOWS ")
 
  set (HUMMSTRUMM_WINDOWSYSYEM_WINDOWS ON)
  set (HUMMSTRUMM_WINDOWSYSYEM_X11 OFF)

  set (HUMMSTRUMM_DOXYGEN_MACROS "HUMMSTRUMM_PLATFORM_WINDOWS=" CACHE STRING
       "The predefined macro string for Doxygen.")
  
else (WIN32)
  if (UNIX)

    set (HUMMSTRUMM_PLATFORM_WINDOWS OFF)
    set (HUMMSTRUMM_PLATFORM_GNULINUX ON)
    list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS "-DHUMMSTRUMM_PLATFORM_GNULINUX ")

    set (HUMMSTRUMM_WINDOWSYSYEM_WINDOWS OFF)
    set (HUMMSTRUMM_WINDOWSYSYEM_X11 ON)

    set (HUMMSTRUMM_DOXYGEN_MACROS "HUMMSTRUMM_PLATFORM_GNULINUX=" CACHE STRING
         "The predefined macro string for Doxygen.")
  endif (UNIX)
endif (WIN32)

if (CMAKE_SIZEOF_VOID_P MATCHES "4")
  set (HUMMSTRUMM_ARCHITECTURE_32 ON)
  set (HUMMSTRUMM_ARCHITECTURE_64 OFF)
  list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS "-DHUMMSTRUMM_ARCHITECTURE_32 ")

else (CMAKE_SIZEOF_VOID_P MATCHES "4")
  if (CMAKE_SIZEOF_VOID_P MATCHES "8")
    set (HUMMSTRUMM_ARCHITECTURE_32 OFF)
    set (HUMMSTRUMM_ARCHITECTURE_64 ON)
    list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS "-DHUMMSTRUMM_ARCHITECTURE_64 ")

  endif (CMAKE_SIZEOF_VOID_P MATCHES "8")
endif (CMAKE_SIZEOF_VOID_P MATCHES "4")

set (HUMMSTRUMM_BUILD_DOCS ON CACHE BOOL "Build documentation of the engine?")

# Log Options
if (HUMMSTRUMM_PLATFORM_GNULINUX)
  set (HUMMSTRUMM_LOG_FILENAME  /var/log/hummstrumm CACHE STRING
       "The file name of the log.")
else (HUMMSTRUMM_PLATFORM_GNULINUX)
  set (HUMMSTRUMM_LOG_FILENAME %APPDATA%/hummstrumm/log.txt CACHE STRING
       "The file name of the log.")
endif (HUMMSTRUMM_PLATFORM_GNULINUX)
set (HUMMSTRUMM_LOG_XMLMODE  ON      CACHE BOOL "Whether to log in XML.")
set (HUMMSTRUMM_LOG_LOGLEVEL MESSAGE CACHE STRING
     "The minimum level of messages.")


# Memory Management
set (HUMMSTRUMM_HEAP_ZERO_MEMORY
     ON CACHE BOOL
     "Whether to zero allocated memory.")


# System Aspects
include (TestBigEndian)
test_big_endian(HUMMSTRUMM_ENDIAN_BIG)
if (NOT HUMMSTRUMM_ENDIAN_BIG)
  set (HUMMSTRUMM_ENDIAN_LITTLE ON)
endif (NOT HUMMSTRUMM_ENDIAN_BIG)

# Try to detect if cpuid is available and if yes try to see
# if sse or sse2 is supported.
try_run (RUN_RESULT_VAR COMPILE_RESULT_VAR
        ${CMAKE_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/system/detectCPUID.c
        COMPILE_DEFINITIONS ${HUMMSTRUMM_REQUIRED_DEFINITIONS}
        COMPILE_OUTPUT_VARIABLE COMPILE_OUTPUT_VAR)
if (${RUN_RESULT_VAR})
  set (HUMMSTRUMM_CPUID_SUPPORT ON)
else (${RUN_RESULT_VAR})
  set (HUMMSTRUMM_CPUID_SUPPORT OFF)
endif (${RUN_RESULT_VAR})

if (HUMMSTRUMM_CPUID_SUPPORT MATCHES ON)
  try_run (RUN_RESULT_VAR COMPILE_RESULT_VAR
          ${CMAKE_BINARY_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}/cmake/system/detectSSE2.c
          CMAKE_FLAGS
            -DINCLUDE_DIRECTORIES:STRING=${CMAKE_CURRENT_SOURCE_DIR}/cmake/system/cpuid.c
          COMPILE_DEFINITIONS ${HUMMSTRUMM_REQUIRED_DEFINITIONS}
          COMPILE_OUTPUT_VARIABLE COMPILE_OUTPUT_VAR)
  if (NOT ${RUN_RESULT_VAR})
    set (HUMMSTRUMM_SSE2_SUPPORT OFF)
  else (NOT ${RUN_RESULT_VAR})
    set (HUMMSTRUMM_SSE2_SUPPORT ON) 
  endif (NOT ${RUN_RESULT_VAR})
  try_run (RUN_RESULT_VAR COMPILE_RESULT_VAR
          ${CMAKE_BINARY_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}/cmake/system/detectSSE.c
          CMAKE_FLAGS
            -DINCLUDE_DIRECTORIES:STRING=${CMAKE_CURRENT_SOURCE_DIR}/cmake/system/cpuid.c
          COMPILE_DEFINITIONS ${HUMMSTRUMM_REQUIRED_DEFINITIONS}
          COMPILE_OUTPUT_VARIABLE COMPILE_OUTPUT_VAR)
  if (NOT ${RUN_RESULT_VAR})
    set (HUMMSTRUMM_SSE_SUPPORT OFF)
  else (NOT ${RUN_RESULT_VAR})
    set (HUMMSTRUMM_SSE_SUPPORT ON) 
  endif (NOT ${RUN_RESULT_VAR})
else (HUMMSTRUMM_CPUID_SUPPORT MATCHES ON)
  set (HUMMSTRUMM_SSE2_SUPPORT OFF)
  set (HUMMSTRUMM_SSE_SUPPORT OFF)
endif (HUMMSTRUMM_CPUID_SUPPORT MATCHES ON)


set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Add debug definitions.
# Use -DCMAKE_BUILD_TYPE=Debug with the cmake command to use them.
if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR
    CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
set (HUMMSTRUMM_DEBUG ON)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug" OR
      CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
set (HUMMSTRUMM_ENABLE_PRINTDEBUG ON CACHE BOOL
       "Whether to enable PrintDebug() and LogDebug() methods.")

configure_file (${CMAKE_SOURCE_DIR}/config.h.in
                ${CMAKE_SOURCE_DIR}/engine/include/config.h @ONLY)
configure_file (${CMAKE_SOURCE_DIR}/engine/Doxyfile.in
                ${CMAKE_SOURCE_DIR}/engine/Doxyfile @ONLY)
configure_file (${CMAKE_SOURCE_DIR}/config.h.in
                ${CMAKE_SOURCE_DIR}/game/include/config.h @ONLY)

add_subdirectory (engine)
add_subdirectory (game)
