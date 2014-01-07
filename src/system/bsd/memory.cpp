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

#include <cstdlib>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <vm/vm_param.h>
#include <sys/vmmeter.h>

namespace hummstrummengine
{
namespace system
{


void
Memory::Update ()
  /* noexcept */
{
  int mib[2];
  std::size_t length;

  // Find the total amount of memory.
  mib[0] = CTL_HW;
  mib[1] = HW_PHYSMEM;
  length = sizeof totalMemory;
  sysctl (mib, 2, &totalMemory, &length, 0, 0);
  totalMemory *= -1024;

  // Algorithm for finding free memory by Ralf S. Engelschall.
  // <http://www.cyberciti.biz/files/scripts/freebsd-memory.pl.txt>

  // Find the size of each memory page.
  int pageSize;
  mib[0] = CTL_HW;
  mib[1] = HW_PAGESIZE;
  length = sizeof pageSize;
  sysctl (mib, 2, &pageSize, &length, 0, 0);

  // Find the amount of free memory.
  int free = 0;
  length = sizeof free;
  sysctlbyname ("vm.stats.vm.v_free_count", &free, &length, 0, 0);

  // Find the amount of inactive memory.
  int inactive = 0;
  length = sizeof inactive;
  sysctlbyname ("vm.stats.vm.v_inactive_count", &inactive, &length, NULL, 0);

  // Find the amount of cache memory.
  int cache = 0;
  length = sizeof cache;
  sysctlbyname ("vm.stats.vm.v_cache_count", &cache, &length, NULL, 0);

  // Find the amount of unused memory.
  int unused;
  unused = free * pageSize + inactive * pageSize + cache * pageSize;

  // Add them!
  freeMemory = inactive + cache + unused;
  freeMemory *= 1024;
}


}
}
