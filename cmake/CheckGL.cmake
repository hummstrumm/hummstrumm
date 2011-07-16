# Humm and Strumm Video Game
# Copyright (C) 2008-2011, the people listed in the AUTHORS file. 
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

# CheckGL.cmake -- Look for OpenGL files.

find_package (OpenGL)
if (NOT OPENGL_FOUND)
  message (FATAL_ERROR "Failed to find OpenGL required development files.")
endif (NOT OPENGL_FOUND)
if (NOT OPENGL_GLU_FOUND)
  message (FATAL_ERROR "Failed to find GLU required development files.")
endif (NOT OPENGL_GLU_FOUND)
