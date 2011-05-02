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

# SubversionTag.cmake -- Simplifies the creation of a release tag.

# TARGET: tag-release
# Creates a new release tag in the online Subversion repository.

set (HUMMSTRUMM_TAG_NAME "${HUMMSTRUMM_VERSION}")
add_custom_target (tag-release
                   COMMAND ${Subversion_SVN_EXECUTABLE} copy
                     https://hummstrumm.googlecode.com/svn/trunk/
                     https://hummstrumm.googlecode.com/svn/tags/${HUMMSTRUMM_TAG_NAME}
                     -m "Release, version ${HUMMSTRUMM_VERSION}")