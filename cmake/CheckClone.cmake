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

# CheckClone.cmake -- Checks whether the source dir is a Git clone or
# a distribution.

message (STATUS "Check for Git repository")
if (NOT EXISTS ${hummstrummengine_SOURCE_DIR}/.git)
  message (STATUS "Check for Git repository - not found")
  set (IS_IN_CLONE OFF)
else ()
  message (STATUS "Check for Git repsotiory - found")
  set (IS_IN_CLONE ON)
endif ()
