// -*- c++ -*-
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
#define HUMMSTRUMM_ENGINE_SOURCE
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


Processors::Processors (void)
  throw ()
  : numberOfProcessors (0),
    processorStrings (0)
{  
  try
    {
      // Get the system information.
      SYSTEM_INFO systemInfo;
      GetSystemInfo (&systemInfo);

      // Find the total number of processors.
      this->numberOfProcessors = systemInfo.dwNumberOfProcessors;
      if (!this->numberOfProcessors)
        {
          throw 0;
        }

      // Allocate memory for the processor strings.
      this->processorStrings = new char * [this->numberOfProcessors];

      // This code from Visual C++ Tips Blog
      // <http://weseetips.com/tag/c-get-processor-name/>

      // Find the processor string (we can only get one on Windows...)
      int cpuInfo[4] = { -1 };
      __cpuid (cpuInfo, 0x80000000);
      unsigned int extendedIds = cpuInfo[0];

      // Get the information associated with each extended ID.
      char cpuBrandString[0x40] = { 0 };
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

      // Copy the string into the our class.
      for (int i = 0; i < this->numberOfProcessors; ++i)
        {
          this->processorStrings[i] =
            new char [std::strlen (cpuBrandString) + 1];
          std::strncpy (this->processorStrings[i],
                        cpuBrandString,
                        std::strlen (cpuBrandString));
          this->processorStrings[i][std::strlen (cpuBrandString)] = '\0';
        }

      // Look for SSE support.
      __cpuid (cpuInfo, 1);
      // MSVC Warning C4800 (Addeed '!=0' to the expressions)
      this->sse42Support = (cpuInfo[2] & (1 << 20)) != 0;
      this->sse41Support = (cpuInfo[2] & (1 << 19)) != 0;
      this->sse3Support  = (cpuInfo[2] & (1 << 0)) != 0;
      this->sse2Support  = (cpuInfo[3] & (1 << 26)) != 0;
      this->sseSupport   = (cpuInfo[3] & (1 << 25)) != 0;
    }
  catch (int i)
    {
      switch (i)
        {
        case 0:
          // Well...we didn't find any processors.  We know there has to be at
          // least one, because we are running.  Create one, and set its name to
          // unknown.  Also, we can't guarantee SSE.
          this->numberOfProcessors = 1;
          this->processorStrings = new char * [1];
          SetProcessorNameToUnknown (0);
          this->sseSupport = false;
          this->sse2Support = false;
          this->sse3Support = false;
          this->sse41Support = false;
          this->sse42Support = false;
          break;
        }
    }
}


Processors::~Processors (void)
{
  for (int i = 0; i < this->numberOfProcessors; ++i)
    {
      // Delete every string we have allocated.
      delete [] this->processorStrings[i];
    }
  delete [] this->processorStrings;
}


int
Processors::GetNumberOfProcessors (void)
  const throw ()
{
  return this->numberOfProcessors;
}


const char *
Processors::GetProcessorName (int index)
  const throw ()
{
  if (index >= 0 && index < this->numberOfProcessors)
    {
      return this->processorStrings[index];
    }
  else
    {
      return 0;
    }
}


bool
Processors::HaveSseSupport (void)
  const throw ()
{
  return this->sseSupport;
}


bool
Processors::HaveSse2Support (void)
  const throw ()
{
  return this->sse2Support;
}


bool
Processors::HaveSse3Support (void)
  const throw ()
{
  return this->sse3Support;
}


bool
Processors::HaveSse41Support (void)
  const throw ()
{
  return this->sse41Support;
}


bool
Processors::HaveSse42Support (void)
  const throw ()
{
  return this->sse42Support;
}


void
Processors::SetProcessorNameToUnknown (int index)
  throw ()
{
  if (index >= 0 && index < this->numberOfProcessors)
    {
      this->processorStrings[index] = new char [std::strlen ("Unknown") + 1];
      std::strcpy (this->processorStrings[index], "Unknown");
    }
}


}
}
}
