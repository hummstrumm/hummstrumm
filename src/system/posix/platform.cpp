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
#include <sys/utsname.h>

namespace hummstrumm
{
namespace engine
{
namespace system
{


Platform::Platform ()
  /* noexcept */
{
  utsname systemName;
  if (-1 == uname (&systemName))
    {
      name = "Non-POSIX System";  // *shouldn't* happen
    }
  else
    {
      name = std::string ("")    +       // e.g.:
             systemName.sysname  + " " + // Linux
             systemName.nodename + " " + // patrick-desktop-gentoo
             systemName.release  + " " + // 3.2.1-gentoo-r2
             systemName.version  + " " + // #1 SMP PREEMPT Wed Jun 6 02:27:37...
             systemName.machine;         // x86_64
    }
}


}
}
}
