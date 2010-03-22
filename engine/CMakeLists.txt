# Humm and Strumm Video Game
# Copyright (C) 2008-2010, the people listed in the AUTHORS file. 
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

add_subdirectory (tests/)

set (hummstrummengine_SRCS
  src/debug/log.cpp
  src/error/error.cpp
  src/error/outofmemory.cpp
  src/core/type.cpp
  src/core/object.cpp
  src/types/time.cpp)
set (hummstrummengine_INCLUDE include/)
set (CMAKE_C_FLAGS_DEBUG "-Wall -g")

include_directories (${hummstrummengine_INCLUDE})
add_library (hummstrummengine STATIC ${hummstrummengine_SRCS})
# Add documentation generation
include (UseDoxygen OPTIONAL)
add_dependencies (hummstrummengine doc)
# Install library and header files
if (WIN32)
  install (TARGETS hummstrummengine 
           ARCHIVE DESTINATION lib)
  install (FILES doc/latex/refman.pdf
           DESTINATION share/doc/)
  install (FILES include/hummstrummengine.hpp
           DESTINATION include)
  install (DIRECTORY ${hummstrummengine_INCLUDE}
           DESTINATION include/hummstrummengine
           FILES_MATCHING PATTERN "*.h"
                          PATTERN "*.hpp"
                          PATTERN "*.inl"
                          PATTERN "hummstrummengine.hpp" EXCLUDE
                          REGEX "/*[.]svn" EXCLUDE)
else()
  install (TARGETS hummstrummengine 
           ARCHIVE DESTINATION lib)
  install (FILES doc/latex/refman.pdf
           DESTINATION share/doc/hummstrummengine)
  install (FILES include/hummstrummengine.hpp
           DESTINATION include)
  install (DIRECTORY ${hummstrummengine_INCLUDE}
           DESTINATION include/hummstrummengine
           FILES_MATCHING PATTERN "*.h"
                          PATTERN "*.hpp"
                          PATTERN "*.inl"
                          PATTERN "hummstrummengine.hpp" EXCLUDE
                          REGEX "/*[.]svn" EXCLUDE)
endif()
