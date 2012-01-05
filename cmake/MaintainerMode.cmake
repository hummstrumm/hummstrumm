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

# MaintainerMode.cmake -- Adds extra controls that are useful to maintainers.

# Check to see if we have all the things that we need in order to be in
# maintainer mode.
include (MaintainerModeChecks)

if (HUMMSTRUMM_MAINTAINER_MODE)

  # We only need these things in maintainer mode.
  include (MakeChangeLog)
  include (GitTag)
  include (Dist)
  include (UploadDownloads)

endif (HUMMSTRUMM_MAINTAINER_MODE)
