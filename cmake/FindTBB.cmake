# Module for locating Intel's Threading Building Blocks (TBB).
#
# Customizable variables:
#   TBB_ROOT_DIR
#     Specifies TBB's root directory.
#
# Read-only variables:
#   TBB_FOUND
#     Indicates whether the library has been found.
#
#   TBB_INCLUDE_DIRS
#      Specifies TBB's include directory.
#
#   TBB_LIBRARIES
#     Specifies TBB libraries that should be passed to target_link_libararies.
#
#   TBB_<COMPONENT>_LIBRARIES
#     Specifies the libraries of a specific <COMPONENT>.
#
#   TBB_<COMPONENT>_FOUND
#     Indicates whether the specified <COMPONENT> was found.
#
#
# Copyright (c) 2012 Sergiu Dotenco
# Copyright (c) 2014 Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTTBBLAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# 2014-02-17: modified by Patrick M. Niedzielski to add support for MSVC12.

INCLUDE (FindPackageHandleStandardArgs)

IF (CMAKE_VERSION VERSION_GREATER 2.8.7)
  SET (_TBB_CHECK_COMPONENTS FALSE)
ELSE (CMAKE_VERSION VERSION_GREATER 2.8.7)
  SET (_TBB_CHECK_COMPONENTS TRUE)
ENDIF (CMAKE_VERSION VERSION_GREATER 2.8.7)

FIND_PATH (TBB_ROOT_DIR
  NAMES include/tbb/tbb.h
  PATHS ENV TBBROOT
        ENV TBB40_INSTALL_DIR
        ENV TBB30_INSTALL_DIR
        ENV TBB22_INSTALL_DIR
        ENV TBB21_INSTALL_DIR
  DOC "TBB root directory")

FIND_PATH (TBB_INCLUDE_DIR
  NAMES tbb/tbb.h
  HINTS ${TBB_ROOT_DIR}
  PATH_SUFFIXES include
  DOC "TBB include directory")

IF (MSVC12)
  SET (_TBB_COMPILER vc12)
ELSEIF (MSVC11)
  SET (_TBB_COMPILER vc11)
ELSEIF (MSVC10)
  SET (_TBB_COMPILER vc10)
ELSEIF (MSVC90)
  SET (_TBB_COMPILER vc9)
ELSEIF (MSVC80)
  SET (_TBB_COMPILER vc8)
ELSEIF (WIN32)
  SET (_TBB_COMPILER vc_mt)
ENDIF (MSVC11)

IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
  SET (_TBB_POSSIBLE_LIB_SUFFIXES lib/intel64/${_TBB_COMPILER})
ELSE (CMAKE_SIZEOF_VOID_P EQUAL 8)
  SET (_TBB_POSSIBLE_LIB_SUFFIXES lib/ia32/${_TBB_COMPILER})
ENDIF (CMAKE_SIZEOF_VOID_P EQUAL 8)

LIST (APPEND _TBB_POSSIBLE_LIB_SUFFIXES lib/$ENV{TBB_ARCH_PLATFORM})

FIND_LIBRARY (TBB_LIBRARY_RELEASE
  NAMES tbb
  HINTS ${TBB_ROOT_DIR}
  PATH_SUFFIXES ${_TBB_POSSIBLE_LIB_SUFFIXES}
  DOC "TBB release library")

FIND_LIBRARY (TBB_LIBRARY_DEBUG
  NAMES tbb_debug
  HINTS ${TBB_ROOT_DIR}
  PATH_SUFFIXES ${_TBB_POSSIBLE_LIB_SUFFIXES}
  DOC "TBB debug library")

IF (TBB_LIBRARY_RELEASE AND TBB_LIBRARY_DEBUG)
  SET (TBB_LIBRARY optimized ${TBB_LIBRARY_RELEASE} debug ${TBB_LIBRARY_DEBUG}
    CACHE DOC "TBB library")
ELSEIF (TBB_LIBRARY_RELEASE)
  SET (TBB_LIBRARY ${TBB_LIBRARY_RELEASE} CACHE DOC "TBB library")
ENDIF (TBB_LIBRARY_RELEASE AND TBB_LIBRARY_DEBUG)

FOREACH (_TBB_COMPONENT ${TBB_FIND_COMPONENTS})
  STRING (TOUPPER ${_TBB_COMPONENT} _TBB_COMPONENT_UPPER)
  SET (_TBB_LIBRARY_BASE TBB_${_TBB_COMPONENT_UPPER}_LIBRARY)

  IF (${_TBB_COMPONENT} STREQUAL preview)
    SET (_TBB_LIBRARY_NAME tbb_${_TBB_COMPONENT})
  ELSE (${_TBB_COMPONENT} STREQUAL preview)
    SET (_TBB_LIBRARY_NAME tbb${_TBB_COMPONENT})
  ENDIF (${_TBB_COMPONENT} STREQUAL preview)

  FIND_LIBRARY (${_TBB_LIBRARY_BASE}_RELEASE
    NAMES ${_TBB_LIBRARY_NAME}
    HINTS ${TBB_ROOT_DIR}
    PATH_SUFFIXES ${_TBB_POSSIBLE_LIB_SUFFIXES}
    DOC "TBB ${_TBB_COMPONENT} release library")

  FIND_LIBRARY (${_TBB_LIBRARY_BASE}_DEBUG
    NAMES ${_TBB_LIBRARY_NAME}_debug
    HINTS ${TBB_ROOT_DIR}
    PATH_SUFFIXES ${_TBB_POSSIBLE_LIB_SUFFIXES}
    DOC "TBB ${_TBB_COMPONENT} debug library")

  MARK_AS_ADVANCED (${_TBB_LIBRARY_BASE} ${_TBB_LIBRARY_BASE}_DEBUG)

  SET (TBB_${_TBB_COMPONENT_UPPER}_FOUND TRUE)

  IF (${_TBB_LIBRARY_BASE}_DEBUG AND ${_TBB_LIBRARY_BASE}_RELEASE)
    SET (${_TBB_LIBRARY_BASE}
      debug ${${_TBB_LIBRARY_BASE}_DEBUG}
      optimized ${${_TBB_LIBRARY_BASE}_RELEASE} CACHE DOC
      "TBB ${_TBB_COMPONENT} library")
  ELSEIF (${_TBB_LIBRARY_BASE}_DEBUG)
    SET (${_TBB_LIBRARY_BASE} ${${_TBB_LIBRARY_BASE}_DEBUG})
  ELSEIF (${_TBB_LIBRARY_BASE}_RELEASE)
    SET (${_TBB_LIBRARY_BASE} ${${_TBB_LIBRARY_BASE}_RELEASE}
      CACHE DOC "TBB ${_TBB_COMPONENT} library")
  ELSE (${_TBB_LIBRARY_BASE}_DEBUG AND ${_TBB_LIBRARY_BASE}_RELEASE)
    # Component missing: record it for a later report
    LIST (APPEND _TBB_MISSING_COMPONENTS ${_TBB_COMPONENT})
    SET (TBB_${_TBB_COMPONENT_UPPER}_FOUND FALSE)
  ENDIF (${_TBB_LIBRARY_BASE}_DEBUG AND ${_TBB_LIBRARY_BASE}_RELEASE)

  SET (TBB_${_TBB_COMPONENT}_FOUND ${TBB_${_TBB_COMPONENT_UPPER}_FOUND})

  IF (${_TBB_LIBRARY_BASE})
    # setup the TBB_<COMPONENT>_LIBRARIES variable
    SET (TBB_${_TBB_COMPONENT_UPPER}_LIBRARIES ${${_TBB_LIBRARY_BASE}})
  ELSE (${_TBB_LIBRARY_BASE})
    LIST (APPEND _TBB_MISSING_LIBRARIES TBB_${_TBB_COMPONENT_UPPER}_LIBRARIES)
  ENDIF (${_TBB_LIBRARY_BASE})
ENDFOREACH (_TBB_COMPONENT ${TBB_FIND_COMPONENTS})

SET (TBB_LIBRARIES ${TBB_LIBRARY})
SET (TBB_INCLUDE_DIRS ${TBB_INCLUDE_DIR})

IF (DEFINED _TBB_MISSING_COMPONENTS AND _TBB_CHECK_COMPONENTS)
  IF (NOT TBB_FIND_QUIETLY)
    MESSAGE (STATUS "One or more TBB components were not found:")
    # Display missing components indented, each on a separate line
    FOREACH (_TBB_MISSING_COMPONENT ${_TBB_MISSING_COMPONENTS})
      MESSAGE (STATUS "  " ${_TBB_MISSING_COMPONENT})
    ENDFOREACH (_TBB_MISSING_COMPONENT ${_TBB_MISSING_COMPONENTS})
  ENDIF (NOT TBB_FIND_QUIETLY)
ENDIF (DEFINED _TBB_MISSING_COMPONENTS AND _TBB_CHECK_COMPONENTS)

# Determine library's version

SET (_TBB_VERSION_HEADER ${TBB_INCLUDE_DIR}/tbb/tbb_stddef.h)

IF (EXISTS ${_TBB_VERSION_HEADER})
  FILE (READ ${_TBB_VERSION_HEADER} _TBB_VERSION_CONTENTS)

  STRING (REGEX REPLACE ".*#define TBB_VERSION_MAJOR[ \t]+([0-9]+).*" "\\1"
    TBB_VERSION_MAJOR "${_TBB_VERSION_CONTENTS}")
  STRING (REGEX REPLACE ".*#define TBB_VERSION_MINOR[ \t]+([0-9]+).*" "\\1"
    TBB_VERSION_MINOR "${_TBB_VERSION_CONTENTS}")

  SET (TBB_VERSION ${TBB_VERSION_MAJOR}.${TBB_VERSION_MINOR})
  SET (TBB_VERSION_COMPONENTS 2)
ENDIF (EXISTS ${_TBB_VERSION_HEADER})

MARK_AS_ADVANCED (TBB_INCLUDE_DIR TBB_LIBRARY TBB_LIBRARY_RELEASE
  TBB_LIBRARY_DEBUG)

IF (NOT _TBB_CHECK_COMPONENTS)
 SET (_TBB_FPHSA_ADDITIONAL_ARGS HANDLE_COMPONENTS)
ENDIF (NOT _TBB_CHECK_COMPONENTS)

FIND_PACKAGE_HANDLE_STANDARD_ARGS (TBB REQUIRED_VARS TBB_ROOT_DIR
  TBB_INCLUDE_DIR TBB_LIBRARY ${_TBB_MISSING_LIBRARIES} VERSION_VAR TBB_VERSION
  ${_TBB_FPHSA_ADDITIONAL_ARGS})