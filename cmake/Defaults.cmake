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

# Defaults.cmake -- Sets several nice useful defaults for the build system.

#  We only need Debug and Release build types.
if (CMAKE_CONFIGURATION_TYPES)
  set (CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING
       "We only need two configuration types at the moment." FORCE)
endif (CMAKE_CONFIGURATION_TYPES)

# Force a selection of a build type.  It's rather important that we have one.
if (NOT CMAKE_BUILD_TYPE)
  if (NOT HUMMSTRUMM_IN_CLONE)
    set (CMAKE_BUILD_TYPE Release CACHE STRING
         "Choose the type of build, options are: Debug Release."
         FORCE)
  else (NOT HUMMSTRUMM_IN_CLONE)
    set (CMAKE_BUILD_TYPE Debug CACHE STRING
         "Choose the type of build, options are: Debug Release."
         FORCE)
  endif (NOT HUMMSTRUMM_IN_CLONE)
endif (NOT CMAKE_BUILD_TYPE)

# Gotta set some flags

# Whenever possible, use the include files in the source, instead of ones on the
# system.
set (CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)

# So we can include files in the current directory (sometimes useful)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

# Pretty Makefiles.
set (CMAKE_COLOR_MAKEFILE ON)

# Don't be verbose.
set (CMAKE_VERBOSE_MAKEFILE OFF)


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


# Add debug definitions.
# Use -DCMAKE_BUILD_TYPE=Debug with the cmake command to use them.
if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR
    CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
set (HUMMSTRUMM_DEBUG ON)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug" OR
      CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
set (HUMMSTRUMM_ENABLE_PRINTDEBUG ON CACHE BOOL
       "Whether to enable PrintDebug() and LogDebug() methods.")

# For some reason, this is not marked as advanced.  It really ought to be.
mark_as_advanced (MAKE_PROGRAM)
