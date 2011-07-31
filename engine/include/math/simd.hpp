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

#ifndef HUMMSTRUMM_ENGINE_MATH_SIMD
#define HUMMSTRUMM_ENGINE_MATH_SIMD

#if defined (HUMMSTRUMM_PLATFORM_GNULINUX) && defined(HUMMSTRUMM_HAVE_SSE_SUPPORT)
#include <xmmintrin.h> //sse2
#include <smmintrin.h> //sse 4.1
#endif

#if defined (HUMMSTRUMM_PLATFORM_BSD) && defined (HUMMSTRUMM_HAVE_SSE_SUPPORT)
#include <xmmintrin.h> //sse2
#include <smmintrin.h> //sse 4.1
#endif

#if defined (HUMMSTRUMM_PLATFORM_WINDOWS) && defined(HUMMSTRUMM_HAVE_SSE_SUPPORT)
#include <mmintrin.h>
#endif

namespace hummstrumm
{
namespace engine
{
namespace math
{

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
  #define HUMMSTRUMM_ALIGN_16_GNULINUX
  #define HUMMSTRUMM_ALIGN_16_BSD
  #define HUMMSTRUMM_ALIGN_16_WINDOWS __declspec(align(16))
#endif

#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
  #define HUMMSTRUMM_ALIGN_16_GNULINUX  __attribute__ ((aligned (16)))
  #define HUMMSTRUMM_ALIGN_16_BSD
  #define HUMMSTRUMM_ALIGN_16_WINDOWS
#endif

#ifdef HUMMSTRUMM_PLATFORM_BSD
  #define HUMMSTRUMM_ALIGN_16_GNULINUX
  #define HUMMSTRUMM_ALIGN_16_BSD __attribute__ ((aligned (16)))
  #define HUMMSTRUMM_ALIGN_16_WINDOWS
#endif

#if defined(HUMMSTRUMM_HAVE_SSE_SUPPORT)
// Arithmetic
// PS acts on [0..127]
// SS acts on [0..31]
#define SIMD_MUL_PS(rin0,rin1, rout) rout = _mm_mul_ps(rin0, rin1)

#define SIMD_MUL_SS(rin0,rin1, rout) rout = _mm_mul_ss(rin0, rin1)

#define SIMD_ADD_PS(rin0,rin1, rout) rout = _mm_add_ps(rin0,rin1)

#define SIMD_SUB_PS(rin0,rin1, rout) rout = _mm_sub_ps(rin0,rin1)

#define SIMD_DIV_PS(rin0,rin1, rout) rout = _mm_div_ps(rin0,rin1)

// load/set values into register
#define SIMD_SET_PS(f0,f1,f2,f3, rout) rout = _mm_set_ps(f0,f1,f2,f3)

// Set the same value for all fields of rout
#define SIMD_SET_PS_2(value, rout) rout = _mm_set_ps(value,value,value,value)

#define SIMD_SET_SS(value, rout) rout = _mm_set_ss(value)

#define SIMD_LOAD_PS(fp, rout) rout = _mm_load_ps(fp)

#define SIMD_SET_ZERO(rout) rout = _mm_setzero_ps()

// store the rin[0..31] into address addr
#define SIMD_STORE_SS(addr,rin) _mm_store_ss(addr,rin)

// SQRT Instructions
#define SIMD_RSQRT_SS(rin, rout) rout = _mm_rsqrt_ss(rin) 

#define SIMD_SQRT_SS(rin, rout) rout = _mm_sqrt_ss(rin)          

// Comparison
#define SIMD_CMPEQ_PS(rin0, rin1, rout) rout = _mm_cmpeq_ps(rin0,rin1)

// out[0..31] = in[0..31] + in[32..63] + in[64..95] + in[96..127] 
#define SIMD_ADD_REGISTER(rin,rout)                           \
  __m128 shf_in = _mm_shuffle_ps(rin,rin,0b00110001);         \
  __m128 add_in; SIMD_ADD_PS(rin,shf_in, add_in);             \
  __m128 shf_add = _mm_shuffle_ps(add_in,add_in,0b00000010);  \
  SIMD_ADD_PS(shf_add, add_in, rout);

// out = s*in[0..31], s*in[32..63], s*in[64..95], s*in[96..127]
#define SIMD_MULT_SCALAR(rin, s, rout)                 \
  __m128 mulr; SIMD_SET_PS_2(s, mulr);                   \
  SIMD_MUL_PS(rin,mulr, rout);

// out = in[0..31]/s, s*in[32..63]/s, s*in[64..95]/s, s*in[96..127]/s
#define SIMD_DIV_SCALAR(rin, s, rout)                     \
  __m128 divr; SIMD_SET_PS_2(s, divr);                    \
  SIMD_DIV_PS(rin,divr,rout);

// out = Magntiude of rin
#define SIMD_MAGNITUDE(rin,rout)               \
  __m128 mulr; SIMD_MUL_PS(rin,rin, mulr);     \
  __m128 addr; SIMD_ADD_REGISTER(mulr, addr);  \
  SIMD_SQRT_SS(addr, rout);

#define SIMD_DOT_SSE_4(rin0, rin1, rout)  \
  rout = _mm_dp_ps(rin0, rin1, 0xf1);     \

#define SIMD_DOT(rin0, rin1, rout)                  \
  __m128 mulr; SIMD_MUL_PS(rin0,rin1, mulr);        \
  SIMD_ADD_REGISTER(mulr,rout);

#endif

}
}
}

#endif
