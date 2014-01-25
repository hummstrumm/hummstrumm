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

// This could be useful later:
// <http://www.koders.com/c/fid43214AC6EBD2CFFB339A4283E46B634666E05C22.aspx?s=vtt>

#include <cstdlib>
#include <sys/sysctl.h>
#ifdef HAVE_CPUID_H
#include "cpuid.h"
#endif

namespace hummstrummengine {
namespace system {

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
  int mib[2];
  std::size_t length;
  char *name;

  // Find the number of processors installed.
  mib[0] = CTL_HW;
  mib[1] = HW_NCPU;
  length = sizeof numberOfProcessors;
  sysctl (mib, 2, &numberOfProcessors, &length, 0, 0);
  if (!numberOfProcessors)
    {
      // Well...we didn't find any processors.  We know there has to be at
      // least one, because we are running.  Create one, and set its name to
      // unknown.  Also, we can't guarantee SSE.
      numberOfProcessors = 1;
      processorStrings.push_back (std::string ("Unknown"));
      return;
    }

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
      for (int i = 0; i < numberOfProcessors; ++i)
        {
          processorStrings.push_back (std::string ("Unknown"));
        }
    }
  else
    {
      // Set all the processor names to the value we got.
      for (int i = 0; i < numberOfProcessors; ++i)
        {
          processorStrings.push_back (std::string (name));
        }
      delete [] name;
    }

#ifdef HAVE_CPUID_H
  // Find the type of processor.
  mib[0] = CTL_HW;
  mib[1] = HW_MACHINE;
  sysctl (mib, 2, NULL, &length, NULL, 0);
  name = new char [length];
  sysctl (mib, 2, name, &length, NULL, 0);

  // Look for processors that could have SSE.
  if (name)
    {
      if (std::string (name) == "amd64" ||
          std::string (name) == "i386")
        {
          // These processors could have SSE.  Use a compiler intrinsic to
          // determine.
          unsigned int regA, regB, regC, regD;
          __get_cpuid (0x00000001, &regA, &regB, &regC, &regD);

          // Clang's name for the bits may change in the future, see
          // <http://lists.freebsd.org/pipermail/svn-src-all/2013-July/072373.html>
#if defined(__clang__)
          sse42Support = regC & bit_SSE42;
          sse41Support = regC & bit_SSE41;
#else
          sse42Support = regC & bit_SSE4_2;
          sse41Support = regC & bit_SSE4_1;
#endif
          sse3Support  = regC & bit_SSE3;
          sse2Support  = regD & bit_SSE2;
          sseSupport   = regD & bit_SSE;
        }
    }
  delete [] name;
#endif // #ifdef HAVE_CPUID_H
}

}
}
