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

# Dist.cmake -- Defines several targets to aid in creating distributable
# packages.

include (CPackSetup)

# TARGET: dist
# Create the specified distributable packages.
add_custom_target(dist COMMAND ${CMAKE_COMMAND} -E copy ${hummstrumm_BINARY_DIR}/ChangeLog ${hummstrumm_SOURCE_DIR}/ChangeLog
                       COMMAND ${CMAKE_MAKE_PROGRAM} package_source
                       COMMAND ${CMAKE_COMMAND} -E remove ${hummstrumm_SOURCE_DIR}/ChangeLog)
add_dependencies (dist changelog)
set_property (DIRECTORY APPEND PROPERTY
	      ADDITIONAL_MAKE_CLEAN_FILES ${hummstrumm_BINARY_DIR}/${CPACK_PACKAGE_FILE_NAME}.tar.gz ${hummstrumm_BINARY_DIR}/${CPACK_PACKAGE_FILE_NAME}.zip)

# TARGET: distcheck / dist-check
# Using distributable packages, make sure the installation works just fine.
add_custom_target (dist-check COMMAND ${CMAKE_COMMAND} -E make_directory ${hummstrumm_BINARY_DIR}/distcheck
                              COMMAND ${CMAKE_COMMAND} -E make_directory ${hummstrumm_BINARY_DIR}/distcheck/install
                              COMMAND ${CMAKE_COMMAND} -E chdir "${hummstrumm_BINARY_DIR}/distcheck" ${CMAKE_COMMAND} -E tar xvfz ${hummstrumm_BINARY_DIR}/${CPACK_PACKAGE_FILE_NAME}.tar.gz
                              COMMAND ${CMAKE_COMMAND} -E make_directory ${hummstrumm_BINARY_DIR}/distcheck/${CPACK_PACKAGE_FILE_NAME}/build
                              COMMAND ${CMAKE_COMMAND} -E chdir "${hummstrumm_BINARY_DIR}/distcheck/${CPACK_PACKAGE_FILE_NAME}/build" ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${hummstrumm_BINARY_DIR}/distcheck/install/ ../
                              COMMAND ${CMAKE_COMMAND} -E chdir "${hummstrumm_BINARY_DIR}/distcheck/${CPACK_PACKAGE_FILE_NAME}/build" ${MAKE_PROGRAM}
                              COMMAND ${CMAKE_COMMAND} -E chdir "${hummstrumm_BINARY_DIR}/distcheck/${CPACK_PACKAGE_FILE_NAME}/build" ${MAKE_PROGRAM} test
                              COMMAND ${CMAKE_COMMAND} -E chdir "${hummstrumm_BINARY_DIR}/distcheck/${CPACK_PACKAGE_FILE_NAME}/build" ${MAKE_PROGRAM} install
                              COMMAND ${CMAKE_COMMAND} -E chdir "${hummstrumm_BINARY_DIR}/distcheck/${CPACK_PACKAGE_FILE_NAME}/build" ${MAKE_PROGRAM} uninstall
                              COMMAND ${CMAKE_COMMAND} -E chdir "${hummstrumm_BINARY_DIR}/distcheck/${CPACK_PACKAGE_FILE_NAME}/build" ${MAKE_PROGRAM} clean
                              COMMAND ${CMAKE_COMMAND} -E remove_directory ${hummstrumm_BINARY_DIR}/distcheck)
add_dependencies (dist-check dist)
add_custom_target (distcheck)
add_dependencies (distcheck dist-check)