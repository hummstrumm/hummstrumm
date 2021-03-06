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

# This is the CTest script to submit to the dashboard at
# <http://hummstrumm.sourceforge.net/cdash>.
set(CTEST_PROJECT_NAME "Engine")
set(CTEST_NIGHTLY_START_TIME "00:00:00 EST")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "hummstrumm.sourceforge.net")
set(CTEST_DROP_LOCATION "/cdash/submit.php?project=Engine")
set(CTEST_DROP_SITE_CDASH TRUE)
