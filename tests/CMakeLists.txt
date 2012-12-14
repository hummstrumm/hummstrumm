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

set (hummstrummengine_INCLUDE ../include/
  ${hummstrummengine_BINARY_DIR}/include
  ${OPENGL_INCLUDE_DIR})
set (hummstrummengine_LIBS hummstrummengine
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
include_directories (${CMAKE_SOURCE_DIR}/lib)
#if (HUMMSTRUMM_WINDOWSYSTEM_X11)
#  include_directories (${X11_X11_INCLUDE_PATH})
#endif (HUMMSTRUMM_WINDOWSYSTEM_X11)


# Wraps up the machinery needed to add a test that uses TAP output
# (like a cipra unit test).
function(tap_test file_path)
  string(REPLACE "/" "_" file_path_no_dirs ${file_path})
  get_filename_component(test_name ${file_path_no_dirs} NAME_WE)
  add_executable("test_${test_name}" ${file_path})
  target_link_libraries("test_${test_name}" ${hummstrummengine_LIBS})
  add_test(NAME "test_${test_name}"
    COMMAND prove -vo --trap --normalize
    "${CMAKE_CURRENT_BINARY_DIR}/test_${test_name}")
endfunction()


tap_test(date/timezone.cpp)
tap_test(date/duration.cpp)
tap_test(date/date.cpp)
tap_test(math/quaternion.cpp)
tap_test(math/matrix.cpp)
tap_test(math/vector.cpp)
tap_test(geometry/plane.cpp)
tap_test(geometry/segment.cpp)
tap_test(geometry/boundingsphere.cpp)
tap_test(system/endianness.cpp)
tap_test(system/clock.cpp)


# non-TAP tests
add_executable(test_engine_log log.cpp)
target_link_libraries(test_engine_log ${hummstrummengine_LIBS})
add_test (NAME test_engine_log COMMAND test_engine_log)

add_executable(test_engine_timing timing.cpp)
target_link_libraries(test_engine_timing ${hummstrummengine_LIBS})
add_test (NAME test_engine_timing COMMAND test_engine_timing)

add_executable(test_engine_systemprint systemprint.cpp)
target_link_libraries(test_engine_systemprint ${hummstrummengine_LIBS})
add_test (NAME test_engine_systemprint COMMAND test_engine_systemprint)

add_executable(test_engine_window window-new.cpp)
target_link_libraries(test_engine_window ${hummstrummengine_LIBS})
add_test (NAME test_engine_window COMMAND test_engine_window)