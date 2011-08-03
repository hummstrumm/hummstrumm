// -*- c -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2010, the people listed in the AUTHORS file.
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

/**
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 */

#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
#include "cpuid.h"
#endif

#ifdef HUMMSTRUMM_PLATFORM_BSD
#include "cpuid.h"
#endif

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#include "intrin.h"
#endif

int
main(int argc, char **argv)
{
  #if defined(HUMMSTRUMM_PLATFORM_GNULINUX) || defined(HUMMSTRUMM_PLATFORM_BSD)
  unsigned int regA, regB, regC, regD;
  if (__get_cpuid(0x00000001,&regA,&regB,&regC,&regD) )
  {
    if (regD & bit_SSE)
      return 1;
  }
  #elif HUMMSTRUMM_PLATFORM_WINDOWS
  int CPUInfo[4] = {-1}
  __cpuid(CPUInfo, 1);
  if (CPUInfo[3] & (1 << 25))
    return 1; // SSE
  #endif
  return 0;
}
