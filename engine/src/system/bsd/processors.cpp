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

// This could be useful later:
// <http://www.koders.com/c/fid43214AC6EBD2CFFB339A4283E46B634666E05C22.aspx?s=vtt>

#include <cstring>
#include <cstdlib>
#include <sys/sysctl.h>
#ifdef HAVE_CPUID_H
#include "cpuid.h"
#endif

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
      int mib[2];
      std::size_t length;
      char *name;

      // Find the number of processors installed.
      mib[0] = CTL_HW;
      mib[1] = HW_NCPU;
      length = sizeof this->numberOfProcessors;
      sysctl (mib, 2, &this->numberOfProcessors, &length, 0, 0);
      if (!this->numberOfProcessors)
        {
          throw 0;
        }

      // Allocate a buffer to store the strings.
      this->processorStrings = new char * [this->numberOfProcessors];

      // Find the name of the processor (we can at most get one...)
      mib[0] = CTL_HW;
      mib[1] = HW_MODEL;
      sysctl (mib, 2, NULL, &length, NULL, 0);
      name = new char [length];
      sysctl (mib, 2, name, &length, NULL, 0);

      // Set the name of the processors.
      if (!name)
        {
          // Whatever.  Just set the strings to Unknown.
          for (int i = 0; i < this->numberOfProcessors; ++i)
            {
              SetProcessorNameToUnknown (i);
            }
        }
      else
        {
          // Set all the processor names to the value we got.
          for (int i = 0; i < this->numberOfProcessors; ++i)
            {
              this->processorStrings[i] = new char [length];
              std::strncpy (this->processorStrings[i],
                            name,
                            length);
            }
        }
      delete [] name;

      // Find the type of processor.
      mib[0] = CTL_HW;
      mib[1] = HW_MACHINE;
      sysctl (mib, 2, NULL, &length, NULL, 0);
      name = new char [length];
      sysctl (mib, 2, name, &length, NULL, 0);

      // Look for processors that could have SSE.
      if (!name)
        {
          // Whatever.  Assume no SSE.
          this->sseSupport = false;
          this->sse2Support = false;
          this->sse3Support = false;
          this->sse41Support = false;
          this->sse42Support = false;
        }
      else
        {
          if (std::strcmp (name, "amd64") == 0 ||
              std::strcmp (name, "i386") == 0)
            {
#ifdef HAVE_CPUID_H
              // These processors could have SSE.  Use a compiler intrinsic to
              // determine.
              unsigned int regA, regB, regC, regD;
              __get_cpuid (0x00000001, &regA, &regB, &regC, &regD);
 
              this->sse42Support = regC & bit_SSE4_2;
              this->sse41Support = regC & bit_SSE4_1;
              this->sse3Support  = regC & bit_SSE3;
              this->sse2Support  = regD & bit_SSE2;
              this->sseSupport   = regD & bit_SSE;
#else // #ifdef HAVE_CPUID_H
              this->sse42Support = 0;
              this->sse41Support = 0;
              this->sse3Support  = 0;
              this->sse2Support  = 0;
              this->sseSupport   = 0;
#endif // #ifdef HAVE_CPUID_H
              
            }
        }
      delete [] name;
      
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
