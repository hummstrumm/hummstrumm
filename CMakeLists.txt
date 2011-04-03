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

# This is the CMake script that is used to build Humm and Strumm.  This script
# deals with these things:
#
#   * Creating configuration values that can be set with ``ccmake''.
#   * Detecting basic system information.
#   * Configuring CTest and CPack for unit testing and packaging, respectively.

project (hummstrumm)
cmake_minimum_required (VERSION 2.6.3)


# We want testing with CTest.
enable_testing ()


# Version information about the game/engine.
set (HUMMSTRUMM_VERSION "Humm and Strumm, version 0.3")
set (HUMMSTRUMM_VERSION_NUMBER "0.3")


# Install the system libraries we'll need.
include (InstallRequiredSystemLibraries)


# What types of packages should we generate?
set (CPACK_GENERATOR "STGZ;SZIP")


# Information about the installer.
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY
     "The Humm and Strumm Free Adventure Video Game")
set (CPACK_PACKAGE_VENDOR
     "The Humm and Strumm Project")
set (CPACK_PACKAGE_DESCRIPTION_FILE
     "${CMAKE_CURRENT_SOURCE_DIR}/README")
set (CPACK_RESOURCE_FILE_LICENSE
     "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set (CPACK_PACKAGE_VERSION_MAJOR
     "0")
set (CPACK_PACKAGE_VERSION_MINOR
     "3")
set (CPACK_PACKAGE_INSTALL_DIRECTORY
     "hummstrumm")


# I'll deal with this stuff later.

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
#
#if(UNIX)
#  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Patrick Niedzielski <PatrickNiedzielski@gmail.com>")
#  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The Humm and Strumm Free Adventure Video Game")
#  set(CPACK_PACKAGE_DESCRIPTION "In a world where logic is frowned upon, two (sometimes three) heroes rise from the back alley way of a news paper corporation...\nHumm and Strumm\n...Saving the world (well, sort of) one hamburger at a time.\nJoin them as they travel throughout a psychedelic world of music, excitement, fire, junk food, stick figures, coconuts, and disco.\nThis game is fully three-dimensional, with a breath-taking musical soundtrack.\nBut, they don't have to brave it alone...usually. Also play as a fun loving bubble blower at times during their quest(s).\nThis game is completely open-source, released under the GNU GPL 3.0, which means that you can freely download, edit, and use this game however you want.")
#  set(CPACK_DEBIAN_PACKAGE_DEPENDS	"libc6 (>= 2.7-18)")
#  set(CPACK_DEBIAN_PACKAGE_SECTION	"Games")
#  set(CPACK_DEBIAN_PACKAGE_VERSION 0.3)
# endif(UNIX)


# Set our executable
set (CPACK_PACKAGE_EXECUTABLES "hummstrumm" "Humm and Strumm")


# Turn on the installer generator.
include (CPack)


# Check for Perl 5
find_package (Perl 5)
if (PERL_FOUND)
endif (PERL_FOUND)  


# Detect which platform we are on.  Currently, we support Windows, GNU/Linux,
# and *BSD (experimental).  *BSD is the default for any non-Linux based UNIX
# system, be it FreeBSD, OpenSolaris, GNU/Hurd, whatever.


# Windows
if (WIN32)

  # Set the platform define.
  set (HUMMSTRUMM_PLATFORM_WINDOWS ON)
  set (HUMMSTRUMM_PLATFORM_GNULINUX OFF)
  set (HUMMSTRUMM_PLATFORM_BSD OFF)

  # Add this to the string to put in the pkginfo file.
  list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS "-DHUMMSTRUMM_PLATFORM_WINDOWS ")
 
  # We need to use WinAPI.
  set (HUMMSTRUMM_WINDOWSYSYEM_WINDOWS ON)
  set (HUMMSTRUMM_WINDOWSYSTEM_X11 OFF)

  # When doxygen makes documentation, we need to tell it to make the Windows
  # documentation.
  set (HUMMSTRUMM_DOXYGEN_MACROS "HUMMSTRUMM_PLATFORM_WINDOWS=" CACHE STRING
       "The predefined macro string for Doxygen.")


# GNU/Linux
else (WIN32)
  if ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")

    # Set the platform define.
    set (HUMMSTRUMM_PLATFORM_WINDOWS OFF)
    set (HUMMSTRUMM_PLATFORM_GNULINUX ON)
    set (HUMMSTRUMM_PLATFORM_BSD OFF)

    # Add this to the string to put in the pkginfo file.
    list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS
          "-DHUMMSTRUMM_PLATFORM_GNULINUX ")

    # We need to use X11.
    set (HUMMSTRUMM_WINDOWSYSYEM_WINDOWS OFF)
    set (HUMMSTRUMM_WINDOWSYSTEM_X11 ON)

    # When doxygen makes documentation, we need to tell it to make the GNU/Linux
    # documentation.
    set (HUMMSTRUMM_DOXYGEN_MACROS "HUMMSTRUMM_PLATFORM_GNULINUX=" CACHE STRING
         "The predefined macro string for Doxygen.")


# *BSD (Actually any UNIX.  I think we use POSIX-compat things for BSD.)
  else ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    if (UNIX)

      # Set the platform define.
      set (HUMMSTRUMM_PLATFORM_WINDOWS OFF)
      set (HUMMSTRUMM_PLATFORM_GNULINUX OFF)
      set (HUMMSTRUMM_PLATFORM_BSD ON)

      # Add this to the string to put in the pkginfo file.
      list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS "-DHUMMSTRUMM_PLATFORM_BSD ")

      # We need to use X11.
      set (HUMMSTRUMM_WINDOWSYSYEM_WINDOWS OFF)
      set (HUMMSTRUMM_WINDOWSYSTEM_X11 ON)

      # When doxygen makes documentation, we need to tell it to make the *BSD
      # documentation.
      set (HUMMSTRUMM_DOXYGEN_MACROS "HUMMSTRUMM_PLATFORM_BSD=" CACHE STRING
           "The predefined macro string for Doxygen.")


    endif (UNIX)
  endif ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
endif (WIN32)

# Is this a 32-bit system or a 64-bit system?
if (CMAKE_SIZEOF_VOID_P MATCHES "4")
  # 32 bit
  set (HUMMSTRUMM_ARCHITECTURE_32 ON)
  set (HUMMSTRUMM_ARCHITECTURE_64 OFF)

else (CMAKE_SIZEOF_VOID_P MATCHES "4")
  if (CMAKE_SIZEOF_VOID_P MATCHES "8")
    # 64 bit
    set (HUMMSTRUMM_ARCHITECTURE_32 OFF)
    set (HUMMSTRUMM_ARCHITECTURE_64 ON)
    list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS
          "-DHUMMSTRUMM_ARCHITECTURE_64 ")
  endif (CMAKE_SIZEOF_VOID_P MATCHES "8")
endif (CMAKE_SIZEOF_VOID_P MATCHES "4")


# Doxygen
set (HUMMSTRUMM_BUILD_DOCS ON CACHE BOOL
     "Build documentation of the engine?")
set (HUMMSTRUMM_BUILD_DOCS_LATEX NO CACHE BOOL
     "Build documentation of the engine in LaTeX, too?")

# Log Options
set (HUMMSTRUMM_LOG_FILENAME test.log CACHE STRING
       "The file name of the log.")
set (HUMMSTRUMM_LOG_LOGLEVEL MESSAGE CACHE STRING
     "The minimum level of messages.")

# Test for SIMD
set (HUMMSTRUMM_HAVE_SSE_SUPPORT OFF)

try_run (RUN_RESULT_VAR COMPILE_RESULT_VAR
         ${CMAKE_BINARY_DIR}
         ${CMAKE_CURRENT_SOURCE_DIR}/cmake/system/detectSSE.c
         CMAKE_FLAGS
         COMPILE_DEFINITIONS ${HUMMSTRUMM_REQUIRED_DEFINITIONS}
         COMPILE_OUTPUT_VARIABLE COMPILE_OUTPUT_VAR)
if (${RUN_RESULT_VAR})
  set (HUMMSTRUMM_HAVE_SSE_SUPPORT ON)
endif (${RUN_RESULT_VAR})

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


# Add uninstall target!
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

add_custom_target (uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake")

configure_file (${CMAKE_SOURCE_DIR}/config.h.in
                ${CMAKE_SOURCE_DIR}/engine/include/config.h @ONLY)
configure_file (${CMAKE_SOURCE_DIR}/engine/Doxyfile.in
                ${CMAKE_SOURCE_DIR}/engine/Doxyfile @ONLY)
configure_file (${CMAKE_SOURCE_DIR}/config.h.in
                ${CMAKE_SOURCE_DIR}/game/include/config.h @ONLY)

add_subdirectory (engine)
add_subdirectory (game)
add_subdirectory (res)

if (HUMMSTRUMM_PLATFORM_WINDOWS)
  add_subdirectory (CPPUnit)
endif (HUMMSTRUMM_PLATFORM_WINDOWS)
