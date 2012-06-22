// -*- mode: c++; c-file-style: hummstrumm -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2012, the people listed in the AUTHORS file.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "hummstrummengine.hpp"

#include <string>
#include <windows.h>

namespace hummstrumm
{
namespace engine
{
namespace system
{


Platform::Platform ()
  /* noexcept */
  : name ("Microsoft Windows")
{  
  OSVERSIONINFOEX versionInfo;
  std::memset (&versionInfo, 0, sizeof (OSVERSIONINFOEX));
  versionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEX);

  if (0 == GetVersionEx (reinterpret_cast<OSVERSIONINFO *> (&versionInfo)))
    return; // Just use the name "Microsoft Windows", because we have some error

  switch (versionInfo.dwMajorVersion)
    {
    case 5:
      switch (versionInfo.dwMinorVersion)
        {
        case 0:
          s += (versionInfo.wProductType == VER_NT_WORKSTATION) ?
            " Windows 2000 Professional" : " Windows 2000 Server";
          break;
          
        case 1:
          s += " Windows XP";
          break;

        case 2:
          s += (versionInfo.wProductType == VER_NT_WORKSTATION) ?
            " Windows XP" : " Windows Server 2003";
          break;
          
        default:
          return;
        }
      break;

    case 6:
      switch (versionInfo.dwMinorVersion)
        {
        case 0:
          s += (versionInfo.wProductType == VER_NT_WORKSTATION) ?
            " Windows Vista " : " Windows Server 2008 ";
          break;

        case 1:
          s += (versionInfo.wProductType == VER_NT_WORSTATION) ?
            " Windows 7" :  "Windows Server 2008 R2 ";
          break;

        default:
          return;
        }
      break;

    default:
      return;
    }
}


}
}
}
