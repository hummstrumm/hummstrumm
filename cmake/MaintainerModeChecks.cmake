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


# Make sure that we are in a working copy.
message (STATUS "Check for working copy")
if (NOT EXISTS ${hummstrumm_SOURCE_DIR}/.svn)
  message (FATAL_ERROR "This source tree doesn't seem to be a working copy.  Working copies are required in maintainer mode.  Are you sure you want to be in maintainer mode?")
else (NOT EXISTS ${hummstrumm_SOURCE_DIR}/.svn)
  message (STATUS "Check for working copy - done")
endif (NOT EXISTS ${hummstrumm_SOURCE_DIR}/.svn)


# Find CPack
get_filename_component (CMAKE_PATH ${CMAKE_COMMAND} PATH)
find_program (CPACK_COMMAND cpack ${CMAKE_PATH})
mark_as_advanced (CPACK_COMMAND)
if (CPACK_COMMAND)
  message (STATUS "Found CPack: ${CPACK_COMMAND}")
else ()
 message (FATAL_ERROR "CPack was not found.  CPack is only required in maintainer mode.  Are you sure you want to be in maintainer mode?")
endif ()


# Find Subversion
find_package (Subversion)
if (Subversion_FOUND)
  message (STATUS "Found Subversion: ${Subversion_SVN_EXECUTABLE}")
else ()
  message (FATAL_ERROR "Subversion was not found. Subversion is only required in maintainer mode.  Are you sure want to be in maintainer mode?")
endif ()


# Find Perl 5
find_package (Perl 5)
if (PERL_FOUND)
  message (STATUS "Found Perl 5: ${PERL_EXECUTABLE}")
else ()
  message (FATAL_ERROR "Perl 5 was not found. Perl is only required in maintainer mode.  Are you sure want to be in maintainer mode?")
endif ()