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

# CppCheck.cmake -- Add a target to run cppcheck on the source code if
# ENABLE_CPPCHECK is true.

if (ENABLE_CPPCHECK)
  # The command to run cppcheck is stored in CPPCHECK_COMMAND.  See
  # ``CheckPackages.cmake'' for its definition.

  if (HUMMSTRUMM_ENGINE_COMPILER_MSVC)
    set (output_template "--template=vc")
  else ()
    set (output_template "--template=gcc") # as a default, even if not GCC
  endif()

  add_custom_target(cppcheck
    COMMAND ${CPPCHECK_COMMAND} ${output_template}
    --enable=style,performance,portability
    ${CMAKE_SOURCE_DIR}/src)
endif ()
