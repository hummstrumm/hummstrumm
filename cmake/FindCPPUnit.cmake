# Humm and Strumm Video Game
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


# FindCPPUnit.cmake -- A module for finding CPPUnit on UNIX systems.  Beware!
# This module uses the included CPPUnit distribution on Windows (only)!

# Variables that this module defines:
# CPPUNIT_FOUND: Whether we even can find CPPUnit.
# CPPUNIT_INCLUDE_DIR: Where the CPPUnit headers are.
# CPPUNIT_LIBRARIES: Libraries you'll need to link against for CPPUnit.


if (NOT WIN32)
  find_path (CPPUNIT_INCLUDE_DIR cppunit/TestRunner.h
             /usr/local/include
             /usr/include)

  find_library (CPPUNIT_LIBRARY
                NAMES cppunit
                PATH_SUFFIXES lib64 lib
                PATHS ${CPPUNIT_INCLUDE_DIR}/..
                       /usr/local
                       /usr)
else (NOT WIN32)
  add_subdirectory (CPPUnit)
  set (CPPUNIT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CPPUnit/include)
  set (CPPUNIT_LIBRARY     ${CMAKE_CURRENT_BINARY_DIR}/CPPUnit/cppunit.lib)
endif (NOT WIN32)

if (CPPUNIT_INCLUDE_DIR AND CPPUNIT_LIBRARY)
  set (CPPUNIT_FOUND ON)
  set (CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY} ${CMAKE_DL_LIBS})

  include (FindPackageMessage)
  find_package_message (CPPUnit "Found CPPUnit: ${CPPUNIT_LIBRARY}"
                        "[${CPPUNIT_LIBRARY}][${CPPUNIT_INCLUDE_DIR}]")
endif (CPPUNIT_INCLUDE_DIR AND CPPUNIT_LIBRARY)

mark_as_advanced (CPPUNIT_INCLUDE_DIR CPPUNIT_LIBRARY)
