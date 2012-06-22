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

#include <cstring>
#include <windows.h>
#include <intrin.h>

namespace hummstrumm
{
namespace engine
{
namespace system
{


Processors::Processors ()
  /* noexcept */
  : numberOfProcessors (0),
    processorStrings (0),
    sseSupport (false),
    sse2Support (false),
    sse3Support (false),
    sse41Support (false),
    sse42Support (false)
{  
  // Get the system information.
  SYSTEM_INFO systemInfo;
  GetSystemInfo (&systemInfo);
  
  // Find the total number of processors.
  numberOfProcessors = systemInfo.dwNumberOfProcessors;
  if (!numberOfProcessors)
    {
      // Well...we didn't find any processors.  We know there has to be at
      // least one, because we are running.  Create one, and set its name to
      // unknown.  Also, we can't guarantee SSE.
      numberOfProcessors = 1;
      processorStrings.push_back (std::string ("Unknown"));
      return;
    }


  // This code from Visual C++ Tips Blog
  // <http://weseetips.com/tag/c-get-processor-name/>

  // Find the processor string (we can only get one on Windows...)
  int cpuInfo[4] = { -1 };
  __cpuid (cpuInfo, 0x80000000);
  unsigned int extendedIds = cpuInfo[0];
  
  // Get the information associated with each extended ID.
  char cpuBrandString[0x41] = { 0 };
  for (unsigned int i = 0x80000000; i <= extendedIds; ++i)
    {
      __cpuid (cpuInfo, i);
      
      // Interpret CPU brand string and cache information.
      if  (i == 0x80000002)
        {
          std::memcpy (cpuBrandString,
                       cpuInfo,
                       sizeof cpuInfo);
        }
      else if (i == 0x80000003)
        {
          std::memcpy (cpuBrandString + 16,
                       cpuInfo,
                       sizeof cpuInfo);
        }
      else if (i == 0x80000004)
        {
          std::memcpy (cpuBrandString + 32,
                       cpuInfo,
                       sizeof cpuInfo);
        }
    }
  cpuBrandString[0x40] = '\0'; // NUL terminate it.
  
  // Copy the string into the our class.
  for (int i = 0; i < numberOfProcessors; ++i)
    {
      processorStrings.push_back (std::string (cpuBrandString));
    }
  
  // Look for SSE support.
  __cpuid (cpuInfo, 1);
  // MSVC Warning C4800 (Addeed '!=0' to the expressions)
  sse42Support = (cpuInfo[2] & (1 << 20)) != 0;
  sse41Support = (cpuInfo[2] & (1 << 19)) != 0;
  sse3Support  = (cpuInfo[2] & (1 << 0)) != 0;
  sse2Support  = (cpuInfo[3] & (1 << 26)) != 0;
  sseSupport   = (cpuInfo[3] & (1 << 25)) != 0;
}


}
}
}
