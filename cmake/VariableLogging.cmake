# Humm and Strumm Engine
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

# VariableLogging.cmake -- Outputs the build configuration.

# Print a nice header.
message (STATUS "")
message (STATUS "${HUMMSTRUMM_ENGINE_NAME} ${HUMMSTRUMM_ENGINE_VERSION} ")
message (STATUS "====================================================================")
message (STATUS "  ${HUMMSTRUMM_ENGNIE_DESCRIPTION}")
message (STATUS "  ${HUMMSTRUMM_ENGINE_VENDOR} <${HUMMSTRUMM_ENGINE_WEBSITE}>")
message (STATUS "")
message (STATUS "In ${CMAKE_BUILD_TYPE} mode")
message (STATUS "Building with ${CMAKE_CXX_COMPILER_ID} compiler for ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")
message (STATUS "")
message (STATUS "Features enabled:")

# Are we targetting X11?
if (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_X11)
  message (STATUS "  * X11 windowing code")
endif ()

# Are we targetting WinAPI?
if (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_WINDOWS)
  message (STATUS "  * Win native windowing code")
endif ()

# Are we building unit tests?
if (ENABLE_UNIT_TESTS)
  message (STATUS "  * Unit tests")
endif ()

# Are we generating documentation?
if (HUMMSTRUMM_ENGINE_BUILD_DOCS)
  message (STATUS "  * HTML documentation")
endif ()

# Do we have SSE support?
if (HUMMSTRUMM_ENGINE_HAVE_SSE_SUPPORT)
  message (STATUS "  * SSE support")
endif (HUMMSTRUMM_ENGINE_HAVE_SSE_SUPPORT)

message (STATUS "")
message (STATUS "This is the ${HUMMSTRUMM_ENGINE_VERSION} release of ${HUMMSTRUMM_ENGINE_NAME}.")
message (STATUS "For a list of changes in this release, see the packaged NEWS file.")
message (STATUS "For help with installation, see the packaged INSTALL file.")
message (STATUS "For your legal rights, see the packaged COPYING file.")
message (STATUS "For more information, see the packaged README file.")
message (STATUS "")
