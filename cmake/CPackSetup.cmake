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

# CPackSetup.cmake -- Sets the values of default variables required for CPack.

get_filename_component (CMAKE_PATH ${CMAKE_COMMAND} PATH)
find_program (CPACK_COMMAND cpack ${CMAKE_PATH})
mark_as_advanced (CPACK_COMMAND)
if (CPACK_COMMAND)
  message (STATUS "Found CPack: ${CPACK_COMMAND}")
else ()
  message (WARNING "CPack not found...")
  return ()
endif ()

# Set the generators used by the project.
set (CPACK_GENERATOR "")
set (CPACK_SOURCE_GENERATOR "TGZ;ZIP") 

# We want top level directories in our source archives, mostly because that's
# what everyone else does.  Conformity.
set (CPACK_INCLUDE_TOPLEVEL_DIRECTORY 1)

set (CPACK_PACKAGE_DESCRIPTION_FILE ${hummstrummengine_SOURCE_DIR}/README)

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY ${HUMMSTRUMM_DESCRIPTION})
set (CPACK_PACKAGE_FILE_NAME ${HUMMSTRUMM_NAME_RELEASE})
#CPACK_PACKAGE_INSTALL_DIRECTORY	 Installation directory on the target system	 CMake 2.5
#CPACK_PACKAGE_INSTALL_REGISTRY_KEY	 Registry key used when installing this project	 CMake 2.5.0
set (CPACK_PACKAGE_NAME ${HUMMSTRUMM_ENGINE_NAME})
set (CPACK_PACKAGE_VENDOR ${HUMMSTRUMM_ENGINE_VENDOR})
set (CPACK_PACKAGE_VERSION_MAJOR ${HUMMSTRUMM_ENGINE_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${HUMMSTRUMM_ENGINE_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH 0)


set (CPACK_SOURCE_IGNORE_FILES "/.git/"
                               "/build/"
                               "~$"
                               "~.*"
                               "${CPACK_SOURCE_IGNORE_FILES}")
set (CPACK_SOURCE_PACKAGE_FILE_NAME ${HUMMSTRUMM_ENGINE_NAME_RELEASE})
set (CPACK_RESOURCE_FILE_LICENSE ${hummstrummengine_SOURCE_DIR}/COPYING)
set (CPACK_RESOURCE_FILE_README	 ${hummstrummengine_SOURCE_DIR}/README)
#set (CPACK_RESOURCE_FILE_WELCOME "")
set (CPACK_PACKAGE_VERSION ${HUMMSTRUMM__ENGINEVERSION})
set (CPACK_INSTALL_COMMANDS "")

# Turn on the installer generator.
include (CPack)