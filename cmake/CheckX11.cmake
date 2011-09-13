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

# CheckX11.cmake -- Look for X11 files if we need them.

# We need X11 if we're building for it.
if (HUMMSTRUMM_WINDOWSYSTEM_X11)
  find_package(X11)
  if (NOT X11_FOUND)
    message (FATAL_ERROR "Failed to find X11 required development files.")
  endif (NOT X11_FOUND)
  if (NOT X11_Xrandr_FOUND)
    message (FATAL_ERROR "Failed to find Xrandr required development files.")
  endif (NOT X11_Xrandr_FOUND)
endif (HUMMSTRUMM_WINDOWSYSTEM_X11)
