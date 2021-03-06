// -*- mode: c++; c-file-style: hummstrumm -*-
/* Humm and Strumm Engine
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

#include <windows.h>

namespace hummstrummengine {
namespace system {

void
Memory::Update ()
  /* noexcept */
{
  // Get the Global Memory Status.
  MEMORYSTATUSEX memoryStatus;
  memoryStatus.dwLength = sizeof memoryStatus;
  GlobalMemoryStatusEx (&memoryStatus);
  
  // Find the total amount of memory.
  totalMemory = static_cast<int> (memoryStatus.ullTotalPhys / 1024);

  // Find the total amount of free memory.
  freeMemory = static_cast<int> (memoryStatus.ullAvailPhys / 1024);
}

}
}
