# Humm and Strumm Engine
# Copyright (C) 2008-2014, the people listed in the AUTHORS file. 
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

# CompilerChecks.cmake -- Makes sure that the compiler supports various headers,
#                         functions, and features.

include (CheckIncludeFileCXX)
include (CheckCpp11)

check_include_file_cxx (cpuid.h HAVE_CPUID_H)
check_include_file_cxx (unistd.h HAVE_UNISTD_H)
check_include_file_cxx (memory HAVE_MEMORY)

if (HUMMSTRUMM_ENGINE_COMPILER_CLANG OR HUMMSTRUMM_ENGINE_COMPILER_GCC)
  add_definitions("-msse")
  #      add_definitions("-msse4.1")
  #      add_definitions("-msse4.2")
endif ()