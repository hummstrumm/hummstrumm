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

# MakeChangeLog.cmake -- Defines the changelog target that produces a ChangeLog
# file from the Git repository.

if (PERL_FOUND AND GIT_FOUND AND IS_IN_CLONE)
  add_custom_target (changelog
    COMMAND "${PERL_EXECUTABLE}"
    "${hummstrummengine_SOURCE_DIR}/scripts/git2cl"
    ">${hummstrummengine_BINARY_DIR}/ChangeLog"
    WORKING_DIRECTORY ${hummstrummengine_SOURCE_DIR}
    COMMENT "Generating ChangeLog from git log")
endif ()