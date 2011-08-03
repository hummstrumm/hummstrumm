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

# UnitTest.cmake -- Enables/disables unit testing based on build type and
# whether CPPUnit was found on a UNIX system (we provide it on Windows).


# Add flag for unit testing.
# If we're in a working copy, then we are probably developing, in which case,
# we should build the unit testing functionality.  Otherwise, this is a user
# distribution, and most users don't want to unit test software that really
# ought to work.
if (NOT HUMMSTRUMM_IN_WORKING_COPY)
  set (HUMMSTRUMM_UNIT_TEST OFF CACHE BOOL "Build CPPUnit tests?")
else (NOT HUMMSTRUMM_IN_WORKING_COPY)
  set (HUMMSTRUMM_UNIT_TEST ON CACHE BOOL "Build CPPUnit tests?")
endif (NOT HUMMSTRUMM_IN_WORKING_COPY)

# Check if CPPUnit exists on this platform.
if (HUMMSTRUMM_UNIT_TEST)
  find_package (CPPUnit)
  if (NOT CPPUNIT_FOUND)
    message (ERROR "CPPUnit was not found on this system.  Unit tests will be disabled.")
    set (HUMMSTRUMM_UNIT_TEST OFF)
  endif (NOT CPPUNIT_FOUND)
endif (HUMMSTRUMM_UNIT_TEST)
