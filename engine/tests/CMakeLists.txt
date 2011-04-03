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

set (hummstrummengine_INCLUDE ../include/ ../../CPPUnit/include/)
set (hummstrummengine_LIBS hummstrummengine cppunit)

if (HUMMSTRUMM_WINDOWSYSTEM_X11)
  list (APPEND hummstrummengine_LIBS X11 GL GLU)
endif (HUMMSTRUMM_WINDOWSYSTEM_X11)
if (HUMMSTRUMM_PLATFORM_GNULINUX)
  list (APPEND hummstrummengine_LIBS rt)
  # I do not really understand why I do have to add this in here too.
  # Its already added in engine.CMakeLists.txt
  add_definitions(-msse4.1) 
endif (HUMMSTRUMM_PLATFORM_GNULINUX)

include_directories (${hummstrummengine_INCLUDE})

add_executable(test_engine_core core.cpp)
target_link_libraries(test_engine_core ${hummstrummengine_LIBS})
add_test (NAME test_engine_core COMMAND test_engine_core)

add_executable(test_engine_log log.cpp)
target_link_libraries(test_engine_log ${hummstrummengine_LIBS})
add_test (NAME test_engine_log COMMAND test_engine_log)

add_executable(test_engine_math math.cpp)
target_link_libraries(test_engine_math ${hummstrummengine_LIBS})
add_test (NAME test_engine_math COMMAND test_engine_math)

add_executable(test_engine_system system.cpp)
target_link_libraries(test_engine_system ${hummstrummengine_LIBS})
add_test (NAME test_engine_system COMMAND test_engine_system)

add_executable(test_engine_types types.cpp)
target_link_libraries(test_engine_types ${hummstrummengine_LIBS})
add_test (NAME test_engine_types COMMAND test_engine_types)

add_executable(test_engine_geometry geometry.cpp)
target_link_libraries(test_engine_geometry ${hummstrummengine_LIBS})
add_test (NAME test_engine_geometry COMMAND test_engine_geometry)

add_executable(test_engine_window window.cpp)
target_link_libraries(test_engine_window ${hummstrummengine_LIBS})
add_test (NAME test_engine_window COMMAND test_engine_window)

