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

# Dist.cmake -- Defines several targets to aid in creating distributable
# packages.

include (CPackSetup)

# TARGET: dist
# Create the specified distributable packages.
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
  ${hummstrummengine_BINARY_DIR}/${CPACK_PACKAGE_FILE_NAME}.tar.gz
  ${hummstrummengine_BINARY_DIR}/${CPACK_PACKAGE_FILE_NAME}.zip)