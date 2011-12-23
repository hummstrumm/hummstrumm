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

# VariableLogging.cmake -- Outputs the build configuration.

# Print a nice header.
message (STATUS "")
message (STATUS "        ${HUMMSTRUMM_NAME} ${HUMMSTRUMM_VERSION} ")
message (STATUS "        ====================================================================")
message (STATUS "        ${HUMMSTRUMM_DESCRIPTION}")
message (STATUS "        ${HUMMSTRUMM_VENDOR} <${HUMMSTRUMM_WEBSITE}>")
message (STATUS "")
message (STATUS "        In ${CMAKE_BUILD_TYPE} mode")
message (STATUS "        Building for ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")
message (STATUS "")
message (STATUS "        Features enabled:")

# Are compiling with C++11 support?
if (HUMMSTRUMM_USE_CPP11)
  message (STATUS "          * C++11 support (experimental in many compilers)")
endif (HUMMSTRUMM_USE_CPP11)

# Are we in maintainer mode?
if (HUMMSTRUMM_MAINTAINER_MODE)
  message (STATUS "          * Maintainer mode")
endif (HUMMSTRUMM_MAINTAINER_MODE)

# Are we targetting X11?
if (HUMMSTRUMM_WINDOWSYSTEM_X11)
  message (STATUS "          * X11 windowing code")
endif (HUMMSTRUMM_WINDOWSYSTEM_X11)

# Are we targetting WinAPI?
if (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
  message (STATUS "          * Win native windowing code")
endif (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)

# Are we building unit tests?
if (HUMMSTRUMM_UNIT_TEST)
  message (STATUS "          * Unit tests")
endif (HUMMSTRUMM_UNIT_TEST)

# Are we generating documentation?
if (HUMMSTRUMM_BUILD_DOCS)
  if (HUMMSTRUMM_BUILD_DOCS_LATEX)
    message (STATUS "          * HTML and LaTeX documentation")
  else (HUMMSTRUMM_BUILD_DOCS_LATEX)
    message (STATUS "          * HTML documentation")
  endif (HUMMSTRUMM_BUILD_DOCS_LATEX)
endif (HUMMSTRUMM_BUILD_DOCS)

# Do we have SSE support?
if (HUMMSTRUMM_HAVE_SSE_SUPPORT)
  message (STATUS "          * SSE support")
endif (HUMMSTRUMM_HAVE_SSE_SUPPORT)

message (STATUS "")
message (STATUS "        This is the ${HUMMSTRUMM_VERSION} release of ${HUMMSTRUMM_NAME}.")
message (STATUS "        For a complete list of changes in this release, see the packaged")
message (STATUS "        NEWS file.")
message (STATUS "        For help with installation, see the packaged INSTALL file.")
message (STATUS "        To know your rights, see the packaged COPYING file.")
message (STATUS "        For more information, see the packaged README file.")
message (STATUS "")
