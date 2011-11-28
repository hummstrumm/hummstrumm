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

# MaintainerModeChecks.cmake -- Checks that the environment supports maintainer
# mode.


# Make sure that we are in a Git clone.
if (NOT HUMMSTRUMM_IN_CLONE)
  message (MESSAGE "Not in a Git clone...turning Maintainer Mode off.")
  set (HUMMSTRUMM_MAINTAINER_MODE OFF CACHE BOOL
       "In maintainer mode, extra controls are added that are useful in releasing packaging the project.")
  return ()
endif (NOT HUMMSTRUMM_IN_CLONE)


# Find CPack
get_filename_component (CMAKE_PATH ${CMAKE_COMMAND} PATH)
find_program (CPACK_COMMAND cpack ${CMAKE_PATH})
mark_as_advanced (CPACK_COMMAND)
if (CPACK_COMMAND)
  message (STATUS "Found CPack: ${CPACK_COMMAND}")
else ()
  message (WARNING "CPack not found...turning Maintainer Mode off.")
  set (HUMMSTRUMM_MAINTAINER_MODE OFF CACHE BOOL
       "In maintainer mode, extra controls are added that are useful in releasing packaging the project.")
  return ()
endif ()


# Find Git
find_package (Git)
if (GIT_FOUND)
else ()
  message (WARNING "Git not found...turning Maintainer Mode off.")
  set (HUMMSTRUMM_MAINTAINER_MODE OFF CACHE BOOL
       "In maintainer mode, extra controls are added that are useful in releasing packaging the project.")
  return ()
endif ()


# Find Perl 5
find_package (Perl 5)
if (PERL_FOUND)
  message (STATUS "Found Perl 5: ${PERL_EXECUTABLE}")
else ()
  message (WARNING "Perl 5 not found...turning Maintainer Mode off.")
  set (HUMMSTRUMM_MAINTAINER_MODE OFF CACHE BOOL
       "In maintainer mode, extra controls are added that are useful in releasing packaging the project.")
  return ()
endif ()

set (HUMMSTRUMM_MAINTAINER_MODE ON CACHE BOOL
       "In maintainer mode, extra controls are added that are useful in releasing packaging the project.")