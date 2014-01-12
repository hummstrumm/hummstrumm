# Humm and Strumm Engine
# Copyright (C) 2008-2012, 2014, the people listed in the AUTHORS file. 
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

# Defaults.cmake -- Sets several nice useful defaults for the build system.

# Select RelWithDebInfo as the default build.
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
    "Default to using RelWithDebInfo as the build type." FORCE)
endif (NOT CMAKE_BUILD_TYPE)

# Prioritize include files in the source over ones on the system.
set (CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)
# So we can include files in the current directory (sometimes useful).
set (CMAKE_INCLUDE_CURRENT_DIR ON)
# Pretty Makefiles.
set (CMAKE_COLOR_MAKEFILE ON)
# Don't be verbose.
set (CMAKE_VERBOSE_MAKEFILE OFF)

# Use some flags across the entire project:
if (HUMMSTRUMM_ENGINE_COMPILER_CLANG OR
    HUMMSTRUMM_ENGINE_COMPILER_GCC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wstrict-overflow=5")
elseif (HUMMSTRUMM_ENGINE_COMPILER_MSVC)
  # Seems like CMAKE_CXX_FLAGS already sets "/W3" by default
  string (REGEX REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  set (CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /W4")
endif ()

# For some reason, this is not marked as advanced.  It really ought to be.
mark_as_advanced (MAKE_PROGRAM)
