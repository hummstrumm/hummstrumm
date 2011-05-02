// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2011, the people listed in the AUTHORS file. 
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
#define HUMMSTRUMM_ENGINE_SOURCE
#include "hummstrummengine.hpp"

#include <cstring>
#include <cstdlib>
#include <sys/sysctl.h>
#include "cpuid.h"

namespace hummstrumm
{
namespace engine
{
namespace system
{


Memory::Memory (void)
  throw ()
  : totalMemory (0),
    freeMemory (0)
{  
  // Find the total amount of memory.
  mib[0] = CTL_HW;
  mib[1] = HW_PHYSMEM;
  length = sizeof this->totalMemory;
  sysctl (mib, 2, &this->totalMemory, &length, 0, 0);
  this->totalMemory *= 1024;

  // Algorithm for finding free memory by Ralf S. Engelschall.
  // <http://www.cyberciti.biz/files/scripts/freebsd-memory.pl.txt>

  // Find the size of each memory page.
  int pageSize;
  mib[0] = CTL_HW;
  mib[1] = HW_PAGESIZE;
  length = sizeof pageSize;
  sysctl (mib, 2, &pageSize, &length, 0, 0);

  // Find the amount of inactive memory.
  int inactive;
  mib[0] = CTL_VM;
  mib[1] = VM_INACTIVE;
  length = sizeof inactive;
  sysctl (mib, 2, &inactive, &length, 0, 0);
  inactive *= pageSize;

  // Find the amount of cache memory.
  int cache;
  mib[0] = CTL_VM;
  mib[1] = VM_CACHE;
  length = sizeof cache;
  sysctl (mib, 2, &cache, &length, 0, 0);
  cache *= pageSize;

  // Find the amount of unused memory.
  int unused;
  mib[0] = CTL_VM;
  mib[1] = VM_FREE;
  length = sizeof unused;
  sysctl (mib, 2, &unused, &length, 0, 0);
  unused *= pageSize;

  // Add them!
  this->freeMemory = inactive + cache + unused;
  this->freeMemory *= 1024;
}

Memory::~Memory (void)
{
}

int
Memory::GetTotalMemory (void)
  const throw ()
{
  return this->totalMemory;
}

int
Memory::GetFreeMemory (void)
  const throw ()
{
  return this->freeMemory;
}


}
}
}
