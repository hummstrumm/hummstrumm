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

# CPackSetup.cmake -- Sets the values of default variables required for CPack.

# Set the generators used by the project.
set (CPACK_GENERATOR "")
set (CPACK_SOURCE_GENERATOR "TGZ;ZIP") 

# We want top level directories in our source archives, mostly because that's
# what everyone else does.  Conformity.
set (CPACK_INCLUDE_TOPLEVEL_DIRECTORY 1)

set (CPACK_PACKAGE_DESCRIPTION_FILE ${hummstrumm_SOURCE_DIR}/README)

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY ${HUMMSTRUMM_DESCRIPTION})
set (CPACK_PACKAGE_FILE_NAME ${HUMMSTRUMM_NAME_RELEASE})
#CPACK_PACKAGE_INSTALL_DIRECTORY	 Installation directory on the target system	 CMake 2.5
#CPACK_PACKAGE_INSTALL_REGISTRY_KEY	 Registry key used when installing this project	 CMake 2.5.0
set (CPACK_PACKAGE_NAME ${HUMMSTRUMM_NAME})
set (CPACK_PACKAGE_VENDOR ${HUMMSTRUMM_VENDOR})
set (CPACK_PACKAGE_VERSION_MAJOR ${HUMMSTRUMM_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${HUMMSTRUMM_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH 0)


set (CPACK_SOURCE_IGNORE_FILES "/.svn/"
                               "/build/"
                               "~$"
                               "~.*"
                               "${CPACK_SOURCE_IGNORE_FILES}")
set (CPACK_SOURCE_PACKAGE_FILE_NAME ${HUMMSTRUMM_NAME_RELEASE})
set (CPACK_RESOURCE_FILE_LICENSE ${hummstrumm_SOURCE_DIR}/COPYING)
set (CPACK_RESOURCE_FILE_README	 ${hummstrumm_SOURCE_DIR}/README)
#set (CPACK_RESOURCE_FILE_WELCOME "")
set (CPACK_PACKAGE_VERSION ${HUMMSTRUMM_VERSION})
set (CPACK_INSTALL_COMMANDS "")

# I'll deal with this stuff later.

#if(WIN32 and not UNIX)
#  # There is a bug in NSI that does not handle full unix paths properly. Make
#  # sure there is at least one set of four (4) backlasshes.
#  set(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
#  set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
#  set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} My Famous Project")
#  set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
#set (CPACK_NSIS_URL_INFO_ABOUT ${HUMMSTRUMM_WEBSITE})
#set (CPACK_NSIS_CONTACT ${HUMMSTRUMM_CONTACT})
#  set(CPACK_NSIS_MODIFY_PATH ON)
#endif(WIN32 and not UNIX)
#
#if(UNIX)
#set (CPACK_DEBIAN_PACKAGE_MAINTAINER ${HUMMSTRUMM_VENDOR}")
#set (CPACK_PACKAGE_DESCRIPTION_SUMMARY ${HUMMSTRUMM_DESCRIPTION}")
#  set(CPACK_PACKAGE_DESCRIPTION "In a world where logic is frowned upon, two (sometimes three) heroes rise from the back alley way of a news paper corporation...\nHumm and Strumm\n...Saving the world (well, sort of) one hamburger at a time.\nJoin them as they travel throughout a psychedelic world of music, excitement, fire, junk food, stick figures, coconuts, and disco.\nThis game is fully three-dimensional, with a breath-taking musical soundtrack.\nBut, they don't have to brave it alone...usually. Also play as a fun loving bubble blower at times during their quest(s).\nThis game is completely open-source, released under the GNU GPL 3.0, which means that you can freely download, edit, and use this game however you want.")
#  set(CPACK_DEBIAN_PACKAGE_DEPENDS	"libc6 (>= 2.7-18)")
#set (CPACK_DEBIAN_PACKAGE_SECTION "Games")
#set (CPACK_DEBIAN_PACKAGE_VERSION ${HUMMSTRUMM_VERSION})

#set (CPACK_RPM_PACKAGE_SUMMARY ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
#set (CPACK_RPM_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
#set (CPACK_RPM_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION}
#set (CPACK_RPM_PACKAGE_ARCHITECTURE	 The RPM package architecture. This may be set to "noarch" if you know you are building a noarch package.	 -
#CPACK_RPM_PACKAGE_RELEASE	 The RPM package release. This is the numbering of the RPM package itself, i.e. the version of the packaging and not the version of the content (see CPACK_RPM_PACKAGE_VERSION). One may change the default value if the previous packaging was buggy and/or you want to put here a fancy Linux distro specific numbering.	 1
#CPACK_RPM_PACKAGE_LICENSE	 The RPM package license policy.	 "unknown"
#CPACK_RPM_PACKAGE_GROUP	 The RPM package group (see /usr/share/doc/rpm-*/GROUPS )	 "unknown"
#CPACK_RPM_PACKAGE_VENDOR	 The RPM package vendor	 CPACK_PACKAGE_VENDOR if set or "unknown" if not set
#CPACK_RPM_PACKAGE_DESCRIPTION	 The RPM package description	 The content of #CPACK_PACKAGE_DESCRIPTION_FILE if set or "no package description available" if not set
#CPACK_RPM_PACKAGE_REQUIRES	 May be used to set RPM dependencies. see [RPM dependencies specification]) for precise syntax. Note that you must enclose the complete requires string between quotes, for example:
#set(CPACK_RPM_PACKAGE_REQUIRES "python >= 2.5.0, cmake >= 2.8")	 -
#CPACK_RPM_PACKAGE_PROVIDES	 May be used to set the virtual packages provided by the RPM. It is somewhat complimentary to CPACK_RPM_PACKAGE_REQUIRES, but note that you do not need to list things like libraries, etc. here, since rpmbuild will figure that out by itself when generating the RPM. Most packages leave this blank. NOTE: This variable was added in cmake 2.8.1 (see [Bug9584]).	 -
#CPACK_RPM_SPEC_INSTALL_POST	 May be used to set an RPM post-install command inside the spec file. For example setting it to "/bin/true" may be used to prevent rpmbuild to strip binaries (see [Bug7435])	 -
#CPACK_RPM_SPEC_MORE_DEFINE	 May be used to add any %define lines to the generated spec file.	 -
#CPACK_RPM_USER_BINARY_SPECFILE	 May be used to specify a user provided spec file instead of generating one. This is an feature which currently needs a patch see [Bug9679]	 -
#CPACK_RPM_GENERATE_USER_BINARY_SPECFILE_TEMPLATE	 May be used to generate a template for a user provided spec file. This is an feature which currently needs a patch see [Bug9679]	 -
#CPACK_RPM_<POST/PRE>_<UN>INSTALL_SCRIPT_FILE	 The content of the specified files will be embedded in the RPM spec file in the appropriate sections. This is an feature which currently needs a patch see [Bug8988]	 -
#CPACK_RPM_PACKAGE_DEBUG
# endif(UNIX)

# Set our executable
set (CPACK_PACKAGE_EXECUTABLES "hummstrumm" "Humm and Strumm")

# Turn on the installer generator.
include (CPack)