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
 * CPUID Routines.
 *
 * @file    detectCPUID.c
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-05-21
 *
 */

#ifndef HUMMSTRUMM_CPUID
#define HUMMSTRUMM_CPUID

#include <limits.h>
#include <stdlib.h>
#include <string.h>

struct s3dNow
{
  unsigned m3dNow;
  unsigned m3dNowExtended;
};

struct sSSE
{
  unsigned sse;
  unsigned sse2;
  unsigned sse3;
  unsigned sse41; // sse 4.1
  unsigned sse42; // sse 4.2
  unsigned sse5;
};

struct sMMX
{
  unsigned mmx;
  unsigned mmxExtended;
};

struct sCPUFeatures
{
  struct sSSE sse;
  struct sMMX mmx;
  struct s3dNow m3dnow;
};

struct sRegisters
{
  unsigned a; // eax/rax
  unsigned b; // ebx/rbx
  unsigned c; // ecx/rcx
  unsigned d; // edx/rdx
};

struct sRegisters registers;

// Prototypes

/**
 * @brief Get n bits from positon p.
 *
 * @param x byte.
 * @param p position.
 * @param n n bits to get.
 *
 * @return  the (right adjusted) n-bit field of x that
 * begins at position p.
 */
unsigned getBits(unsigned x, int p, int n);
/**
 * @brief CPUID.
 *
 * @param cpuidOp cpuid operation mode.
 */
void cpuid(const unsigned int cpuidOp);

#endif
