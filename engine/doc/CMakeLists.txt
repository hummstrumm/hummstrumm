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

find_package (Doxygen)
if (DOXYGEN_FOUND)
  message (STATUS "hasugasohua")
  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
                  ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

  add_custom_target (doc
                     ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                     COMMENT "Generating API documentation with Doxygen"
                     VERBATIM)
  add_custom_command (TARGET doc
                      POST_BUILD
                      COMMAND ${CMAKE_COMMAND}
                      ARGS -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images
                           ${CMAKE_CURRENT_BINARY_DIR}/html/images
                      COMMENT "Copying images to html/images"
                      VERBATIM)

  # Install documentation, if it is made.
  install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
           DESTINATION ${HUMMSTRUMM_ENGINE_INSTALL_DOC}
           OPTIONAL)
else ()
  message (STATUS "If you want to build API documentation for the engine, install Doxygen")
endif (DOXYGEN_FOUND)