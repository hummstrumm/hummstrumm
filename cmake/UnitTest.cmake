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

# UnitTest.cmake -- Enables/disables unit testing based on build type and
# whether CPPUnit was found on a UNIX system (we provide it on Windows).

# Check if CPPUnit exists on this platform.
if (ENABLE_UNIT_TESTS)
  find_package (CPPUnit)
  if (NOT CPPUNIT_FOUND)
    message ("CPPUnit was not found on this system.  Unit tests will be disabled.")
    set (ENABLE_UNIT_TESTS OFF)
  endif ()
endif (ENABLE_UNIT_TESTS)
