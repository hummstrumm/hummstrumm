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
set (CMAKE_C_FLAGS_DEBUG "-Wall -ggdb")

include_directories (${hummstrummengine_INCLUDE})
add_executable(test_engine_log log.cpp)
target_link_libraries(test_engine_log hummstrummengine)

add_test (NAME test_engine_log COMMAND test_engine_log)

add_executable(test_engine_math math.cpp)
target_link_libraries(test_engine_math hummstrummengine cppunit dl)

add_test (NAME test_engine_math COMMAND test_engine_math)
