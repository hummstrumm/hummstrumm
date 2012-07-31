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

# CompilerChecks.cmake -- Makes sure that the compiler supports various headers,
#                         functions, and features.

include (CheckIncludeFileCXX)
include (CheckCpp11)

check_include_file_cxx (cpuid.h HAVE_CPUID_H)
check_include_file_cxx (unistd.h HAVE_UNISTD_H)
check_include_file_cxx ("tr1/memory" HAVE_TR1_MEMORY)
check_include_file_cxx (memory HAVE_MEMORY)