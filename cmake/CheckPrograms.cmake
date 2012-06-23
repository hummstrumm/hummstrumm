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

# CheckPrograms.cmake -- Look for any programs we can (optionally?) use.

# Look for cppcheck
if (ENABLE_CPPCHECK)
  find_program (CPPCHECK_COMMAND cppcheck DOC "Path to cppcheck.")
  mark_as_advanced(cppcheck_DIR)
endif (ENABLE_CPPCHECK)

# Look for valgrind
if (ENABLE_VALGRIND)
  find_program (VALGRIND_COMMAND valgrind DOC "Path to valgrind.")
  mark_as_advanced(valgrind_DIR)
endif (ENABLE_VALGRIND)
