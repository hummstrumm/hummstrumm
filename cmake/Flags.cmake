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

# Flags.cmake -- Flags that can be turned on or off during configuration.

set (ENABLE_UNIT_TESTS ON CACHE BOOL
  "Build unit tests?")

# Note: we look for Boost if the <regex> header doesn't work.
set (ENABLE_BOOST_REGEX OFF CACHE BOOL
  "Prefer Boost regex over your compiler's <regex> header?")

set (ENABLE_TERMCOLORS ON CACHE BOOL
  "Use distributed term-colors library for cross-platform terminal colors in the log.")