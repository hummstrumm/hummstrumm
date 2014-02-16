# Humm and Strumm Engine
# Copyright (C) 2014, the people listed in the AUTHORS file. 
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

# SourceGroups.cmake -- Provides a macro that creates source groups for IDEs
# and automatically adds the files to the variable hummstrummengine_SRCS

macro (make_source_group _dir _srcs _hdrs _inls)
  string (REGEX REPLACE "/" "\\\\" _name ${_dir})

  # For source files
  foreach (_src ${_srcs})
    set (_srcpath "src/${_dir}/${_src}")
    source_group ("Source Files\\${_name}" FILES ${_srcpath})
    list (APPEND hummstrummengine_SRCS ${_srcpath})
  endforeach ()

  # For include files
  foreach (_hdr ${_hdrs})
    set (_hdrpath "include/${_dir}/${_hdr}")
    source_group("Header Files\\${_name}" FILES ${_hdrpath})
    list (APPEND hummstrummengine_SRCS ${_hdrpath})
  endforeach ()

  # For inline source files
  foreach (_inl ${_inls})
    set (_inlpath "include/${_dir}/${_inl}")
    source_group("Source Files\\${_name}" FILES ${_inlpath})
    list (APPEND hummstrummengine_SRCS ${_inlpath})
  endforeach ()
endmacro (make_source_group)