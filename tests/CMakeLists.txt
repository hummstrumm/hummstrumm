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

if (NOT IS_BUILDING_UNIT_TESTS)
  return ()
endif ()

enable_testing ()

set (hummstrummengine_INCLUDE ../include/
  ${hummstrummengine_BINARY_DIR}/include
  ${CPPUNIT_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIR})
set (hummstrummengine_LIBS hummstrummengine
  ${CPPUNIT_LIBRARIES}
  ${OPENGL_LIBRARIES})
if (HUMMSTRUMM_ENGINE_REGEX_USE_BOOST)
  list (APPEND hummstrummengine_LIBS ${Boost_LIBRARIES})
endif ()

if (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_X11)
  list (APPEND hummstrummengine_LIBS ${X11_LIBRARIES})
  list (APPEND hummstrummengine_LIBS ${X11_Xrandr_LIB})
endif (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_X11)
if (HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX)
  list (APPEND hummstrummengine_LIBS rt)
  # I do not really understand why I do have to add this in here too.
  # Its already added in engine.CMakeLists.txt

  # Commenting out -- this makes it not work on AMD systems.  Fix later.
  #   ~ Patrick, 2012-06-16
#  add_definitions("-msse4.1")
endif (HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX)

if (HUMMSTRUMM_ENGINE_COMPILER_GCC)
  add_definitions("-g")
endif (HUMMSTRUMM_ENGINE_COMPILER_GCC)

include_directories (${hummstrummengine_INCLUDE})
#if (HUMMSTRUMM_WINDOWSYSTEM_X11)
#  include_directories (${X11_X11_INCLUDE_PATH})
#endif (HUMMSTRUMM_WINDOWSYSTEM_X11)

add_executable(test_engine_log log.cpp)
target_link_libraries(test_engine_log ${hummstrummengine_LIBS})
add_test (NAME test_engine_log COMMAND test_engine_log)

add_executable(test_engine_date date.cpp)
target_link_libraries(test_engine_date ${hummstrummengine_LIBS})
add_test(NAME test_engine_date COMMAND test_engine_date)

add_executable(test_engine_math math.cpp)
target_link_libraries(test_engine_math ${hummstrummengine_LIBS})
add_test (NAME test_engine_math COMMAND test_engine_math)

add_executable(test_engine_timing timing.cpp)
target_link_libraries(test_engine_timing ${hummstrummengine_LIBS})
add_test (NAME test_engine_timing COMMAND test_engine_timing)

add_executable(test_engine_system system.cpp)
target_link_libraries(test_engine_system ${hummstrummengine_LIBS})
add_test (NAME test_engine_system COMMAND test_engine_system)

add_executable(test_engine_systemprint systemprint.cpp)
target_link_libraries(test_engine_systemprint ${hummstrummengine_LIBS})
add_test (NAME test_engine_systemprint COMMAND test_engine_systemprint)

add_executable(test_engine_geometry geometry.cpp)
target_link_libraries(test_engine_geometry ${hummstrummengine_LIBS})
add_test (NAME test_engine_geometry COMMAND test_engine_geometry)

add_executable(test_engine_window window-new.cpp)
target_link_libraries(test_engine_window ${hummstrummengine_LIBS})
add_test (NAME test_engine_window COMMAND test_engine_window)