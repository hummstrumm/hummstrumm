// -*- c++ -*-
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
 * Checks if CPUID is present.
 *
 * @file    detectCPUID.c
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-05-21
 *
 */

int
isCPUIDPresent()
{
  #ifdef HUMMSTRUMM_PLATFORM_WIN
    #ifdef HUMMSTRUMM_ARCHITECTURE_32
      __asm 
      {
        push ecx
        pushfd
        pop eax
        mov ecx, eax
        xor eax, 200000h
        push eax
        popfd
        pushfd
        pop eax
        xor eax, ecx
        shr eax, 21
        push ecx
        popfd
        pop ecx
      }
    #elif HUMMSTRUMM_ARCHITECTURE_64
      /* @todo All 64-bit intel processors support cpuid but what about amd
       * and other processors? 
       */
      return 1;
    #else
      return 0;
    #endif
  #elif HUMMSTRUMM_PLATFORM_GNULINUX
    #ifdef HUMMSTRUMM_ARCHITECTURE_32
      asm volatile
      (
        "pushl %%ecx\n\t"
        "pushf\n\t"
        "popl %%eax\n\t"
        "movl %%eax, %%ecx\n\t"
        "xorl $0x200000, %%eax\n\t"
        "pushl %%eax\n\t"
        "popf\n\t"
        "pushf\n\t"
        "popl %%eax\n\t"
        "xorl %%ecx, %%eax\n\t"
        "shrl $21, %%eax\n\t"
        "pushl %%ecx\n\t"
        "popf\n\t"
        "popl %%ecx\n\t"
        :
        :
        : "eax", "ecx"
      );
    #elif HUMMSTRUMM_ARCHITECTURE_64
      return 1;
    #else
      return 0;
    #endif
  #else
    return 0; 
  #endif
}

int
main(int argc, char **argv)
{
  return isCPUIDPresent();
}
