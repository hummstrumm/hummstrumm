# Humm and Strumm Video Game
# Copyright (C) 2008-2010, the people listed in the AUTHORS file. 
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

enable_testing ()

set (hummstrummengine_INCLUDE ../include/)

include_directories (${hummstrummengine_INCLUDE})

if (HUMMSTRUMM_PLATFORM_GNULINUX)

add_executable(test_engine_core core.cpp)
target_link_libraries(test_engine_core hummstrummengine cppunit rt)

add_test (NAME test_engine_core COMMAND test_engine_core)

add_executable(test_engine_log log.cpp)
target_link_libraries(test_engine_log hummstrummengine rt)

add_test (NAME test_engine_log COMMAND test_engine_log)

add_executable(test_engine_math math.cpp)
target_link_libraries(test_engine_math hummstrummengine cppunit rt)

add_test (NAME test_engine_math COMMAND test_engine_math)

add_executable(test_engine_endian endian.cpp)
target_link_libraries(test_engine_endian hummstrummengine rt)

add_test (NAME test_engine_endian COMMAND test_engine_endian)

add_executable(test_engine_types types.cpp)
target_link_libraries(test_engine_types hummstrummengine cppunit rt)

add_test (NAME test_engine_types COMMAND test_engine_types)

add_executable(test_engine_geometry geometry.cpp)
target_link_libraries(test_engine_geometry hummstrummengine cppunit rt)

add_test (NAME test_engine_geometry COMMAND test_engine_geometry)

#add_executable(test_engine_sqrt sqrt.cpp)
#target_link_libraries(test_engine_sqrt hummstrummengine rt)

#add_test (NAME test_engine_sqrt COMMAND test_engine_sqrt)

add_executable(test_engine_window window.cpp)
target_link_libraries(test_engine_window hummstrummengine rt X11)

add_test (NAME test_engine_window COMMAND test_engine_window)

endif (HUMMSTRUMM_PLATFORM_GNULINUX)
