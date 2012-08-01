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

# CheckPackages.cmake -- Look for any libraries and programs we can (perhaps
# optionally) use.

# Look for cppcheck
if (ENABLE_CPPCHECK)
  find_program (CPPCHECK_COMMAND cppcheck DOC "Path to cppcheck.")
  mark_as_advanced(cppcheck_DIR)
endif ()

# Look for valgrind
if (ENABLE_VALGRIND)
  find_program (VALGRIND_COMMAND valgrind DOC "Path to valgrind.")
  mark_as_advanced(valgrind_DIR)
endif ()

# Find Perl 5
find_package (Perl 5)
if (PERL_FOUND)
  message (STATUS "Found Perl 5: ${PERL_EXECUTABLE}")
endif ()

# Find Git
find_package (Git)

# We need X11 if we're building for it.
if (HUMMSTRUMM_ENGINE_WINDOWSYSTEM_X11)
  find_package(X11)
  if (NOT X11_FOUND)
    message (FATAL_ERROR "Failed to find X11 required development files.")
  endif ()
  if (NOT X11_Xrandr_FOUND)
    message (FATAL_ERROR "Failed to find Xrandr required development files.")
  endif ()
endif ()

# We need OpenGL and GLU
find_package (OpenGL)
if (NOT OPENGL_FOUND)
  message (FATAL_ERROR "Failed to find OpenGL required development files.")
endif ()
if (NOT OPENGL_GLU_FOUND)
  message (FATAL_ERROR "Failed to find GLU required development files.")
endif ()
