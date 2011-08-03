# Humm and Strumm Video Game
# Copyright (C) 2008-2011, the people listed in the AUTHORS file. 
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

# Platform.cmake -- Detect the platform we are compiling on.

# Detect which platform we are on.  Currently, we support Windows, GNU/Linux,
# and *BSD (experimental).  Any other UNIX system, be it Darwin, OpenSolaris,
# GNU/Hurd, whatever, are not supported at the moment.
#
# For a complete list of CMAKE_SYSTEM_NAME values, see
# <http://synergy-foss.org/pm/projects/synergy/repository/revisions/413/entry/trunk/tool/win/cmake/share/cmake-2.8/Modules/CMakeDetermineSystem.cmake>

# Windows
if ("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")

  # Set the platform define.
  set (HUMMSTRUMM_PLATFORM_WINDOWS ON)
  set (HUMMSTRUMM_PLATFORM_GNULINUX OFF)
  set (HUMMSTRUMM_PLATFORM_BSD OFF)

  # Add this to the string to put in the pkginfo file.
  list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS "-DHUMMSTRUMM_PLATFORM_WINDOWS ")
 
  # We need to use WinAPI.
  set (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS ON)
  set (HUMMSTRUMM_WINDOWSYSTEM_X11 OFF)

  # When doxygen makes documentation, we need to tell it to make the Windows
  # documentation.
  set (HUMMSTRUMM_DOXYGEN_MACROS "HUMMSTRUMM_PLATFORM_WINDOWS=" CACHE STRING
       "The predefined macro string for Doxygen.")  

# GNU/Linux
elseif ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")

  # Set the platform define.
  set (HUMMSTRUMM_PLATFORM_WINDOWS OFF)
  set (HUMMSTRUMM_PLATFORM_GNULINUX ON)
  set (HUMMSTRUMM_PLATFORM_BSD OFF)

  # Add this to the string to put in the pkginfo file.
  list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS
        "-DHUMMSTRUMM_PLATFORM_GNULINUX ")

  # We need to use X11.
  set (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS OFF)
  set (HUMMSTRUMM_WINDOWSYSTEM_X11 ON)

  # When doxygen makes documentation, we need to tell it to make the GNU/Linux
  # documentation.
  set (HUMMSTRUMM_DOXYGEN_MACROS "HUMMSTRUMM_PLATFORM_GNULINUX=" CACHE STRING
       "The predefined macro string for Doxygen.")

# *BSD
# Should this include GNU/kFreeBSD?  TODO: Do a little research on that.
elseif ("${CMAKE_SYSTEM_NAME}" MATCHES "BSD/OS" OR
        "${CMAKE_SYSTEM_NAME}" MATCHES "FreeBSD" OR
        "${CMAKE_SYSTEM_NAME}" MATCHES "NetBSD" OR
        "${CMAKE_SYSTEM_NAME}" MATCHES "OpenBSD")

  # Set the platform define.
  set (HUMMSTRUMM_PLATFORM_WINDOWS OFF)
  set (HUMMSTRUMM_PLATFORM_GNULINUX OFF)
  set (HUMMSTRUMM_PLATFORM_BSD ON)

  # Add this to the string to put in the pkginfo file.
  list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS "-DHUMMSTRUMM_PLATFORM_BSD ")

  # We need to use X11.
  set (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS OFF)
  set (HUMMSTRUMM_WINDOWSYSTEM_X11 ON)

  # When doxygen makes documentation, we need to tell it to make the *BSD
  # documentation.
  set (HUMMSTRUMM_DOXYGEN_MACROS "HUMMSTRUMM_PLATFORM_BSD=" CACHE STRING
       "The predefined macro string for Doxygen.")

# Any other UNIX (we don't support them yet).
else ()

  message (FATAL_ERROR "We don't currently support this platform.  Our supported platforms are Windows, GNU/Linux, and *BSD platforms.  Please contact the developers if you feel your platform should be supported.")

endif ()

mark_as_advanced (HUMMSTRUMM_DOXYGEN_MACROS)


# Is this a 32-bit system or a 64-bit system?
if (CMAKE_SIZEOF_VOID_P MATCHES "4")
  # 32 bit
  set (HUMMSTRUMM_ARCHITECTURE_32 ON)
  set (HUMMSTRUMM_ARCHITECTURE_64 OFF)
  list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS "-DHUMMSTRUMM_ARCHITECTURE_32 ")

else (CMAKE_SIZEOF_VOID_P MATCHES "4")
  if (CMAKE_SIZEOF_VOID_P MATCHES "8")
    # 64 bit
    set (HUMMSTRUMM_ARCHITECTURE_32 OFF)
    set (HUMMSTRUMM_ARCHITECTURE_64 ON)
    list (APPEND HUMMSTRUMM_REQUIRED_DEFINITIONS
          "-DHUMMSTRUMM_ARCHITECTURE_64 ")
  endif (CMAKE_SIZEOF_VOID_P MATCHES "8")
endif (CMAKE_SIZEOF_VOID_P MATCHES "4")
