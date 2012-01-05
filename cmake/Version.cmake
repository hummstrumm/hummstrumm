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

# Version.cmake -- Contains version information about Humm and Strumm.

# Only edit the ones below:
set (HUMMSTRUMM_VERSION_MAJOR "0")
set (HUMMSTRUMM_VERSION_MINOR "4")
set (HUMMSTRUMM_NAME "Humm and Strumm")
set (HUMMSTRUMM_NAME_SHORT "hummstrumm")
set (HUMMSTRUMM_VENDOR "The Humm and Strumm Project")
set (HUMMSTRUMM_DESCRIPTION "A FOSS 3D adventure game for two players.")
set (HUMMSTRUMM_WEBSITE "http://hummstrumm.blogspot.com/")
set (HUMMSTRUMM_CONTACT "hummstrumm-user@googlegroups.com")

# These will be generated automatically from the above information.
set (HUMMSTRUMM_VERSION
     "${HUMMSTRUMM_VERSION_MAJOR}.${HUMMSTRUMM_VERSION_MINOR}")
set (HUMMSTRUMM_NAME_RELEASE "${HUMMSTRUMM_NAME_SHORT}-${HUMMSTRUMM_VERSION}")