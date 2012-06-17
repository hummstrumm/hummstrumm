// -*- mode: c++; c-file-style: hummstrumm -*-
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
 * Defines macros for using SIMD/SSE in the engine math code.
 *
 * @file    math/simd.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-08-19
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

/*
 * @def HUMMSTRUMM_ALIGN_16_UNIX
 *
 * Forces a 16 bit align on GNU/Linux and *BSD.  Only defined on these
 * platforms, so safe to use on all platforms with no side-affects.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 */
/*
 * @def HUMMSTRUMM_ALIGN_16_WINDOWS
 *
 * Forces a 16 bit align on Windows.  Only defined on Windows, so safe to
 * use on all platforms with no side-affects.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 */

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
  #define HUMMSTRUMM_ALIGN_16_UNIX
  #define HUMMSTRUMM_ALIGN_16_WINDOWS __declspec(align(16))
#endif

#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
  #define HUMMSTRUMM_ALIGN_16_UNIX  __attribute__ ((aligned (16)))
  #define HUMMSTRUMM_ALIGN_16_WINDOWS
#endif

#ifdef HUMMSTRUMM_PLATFORM_BSD
  #define HUMMSTRUMM_ALIGN_16_UNIX __attribute__ ((aligned (16)))
  #define HUMMSTRUMM_ALIGN_16_WINDOWS
#endif

#if defined(HUMMSTRUMM_HAVE_SSE_SUPPORT)
// Arithmetic
// PS acts on [0..127]
// SS acts on [0..31]

/**
 * @def SIMD_MUL_PS
 *
 * Multiplies respective scalars in two vectors.  The x-coordinates of the
 * vectors are multiplied, the y-coordinates multiplied, the z-coordinates
 * multiplied, and the w-coordinates too multiplied.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin0 The first input register.
 * @param [in]  rin1 The second input register.
 * @param [out] rout The output register.
 */
#define SIMD_MUL_PS(rin0,rin1, rout) rout = _mm_mul_ps(rin0, rin1)
/**
 * @def SIMD_MUL_SS
 *
 * Multiplies the first scalars in two vectors.  Only the first float in the
 * vectors are multiplied together.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin0 The first input register.
 * @param [in]  rin1 The second input register.
 * @param [out] rout The output register. 
 */
#define SIMD_MUL_SS(rin0,rin1, rout) rout = _mm_mul_ss(rin0, rin1)
/**
 * @def SIMD_ADD_PS
 *
 * Adds respective scalars in two vectors.  The x-coordinates of the
 * vectors are summed, the y-coordinates summed, the z-coordinates summed, and
 * the w-coordinates too summed.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin0 The first input register.
 * @param [in]  rin1 The second input register.
 * @param [out] rout The output register.
 */
#define SIMD_ADD_PS(rin0,rin1, rout) rout = _mm_add_ps(rin0,rin1)
/**
 * @def SIMD_SUB_PS
 *
 * Subtracts respective scalars in two vectors.  The x-coordinates of the
 * vectors are subtracted, the y-coordinates subtracted, the z-coordinates
 * subtracted, and the w-coordinates too subtracted.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin0 The first input register.
 * @param [in]  rin1 The second input register.
 * @param [out] rout The output register.
 */
#define SIMD_SUB_PS(rin0,rin1, rout) rout = _mm_sub_ps(rin0,rin1)
/**
 * @def SIMD_DIV_PS
 *
 * Divides respective scalars in two vectors.  The x-coordinates of the
 * vectors are divided, the y-coordinates divided, the z-coordinates divided,
 * and the w-coordinates too divided.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin0 The first input register.
 * @param [in]  rin1 The second input register.
 * @param [out] rout The output register.
 */
#define SIMD_DIV_PS(rin0,rin1, rout) rout = _mm_div_ps(rin0,rin1)

// load/set values into register
/**
 * @def SIMD_SET_PS
 *
 * Sets a register with four single-precision, floating-point values
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  f0   The first float.
 * @param [in]  f1   The second float.
 * @param [in]  f2   The third float.
 * @param [in]  f3   The fourth float.
 * @param [out] rout The output register.
 */
#define SIMD_SET_PS(f0,f1,f2,f3, rout) rout = _mm_set_ps(f0,f1,f2,f3)
/**
 * @def SIMD_SET_PS_2
 *
 * Sets all coordinates of a register to one single-precision, floating-point
 * value.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  value The floating point value.
 * @param [out] rout  The output register.
 */
#define SIMD_SET_PS_2(value, rout) rout = _mm_set_ps(value,value,value,value)
/**
 * @def SIMD_SET_SS
 *
 * Sets the first coordinate of a register to one single-precision,
 * floating-point value.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  value The floating point value.
 * @param [out] rout  The output register.
 */
#define SIMD_SET_SS(value, rout) rout = _mm_set_ss(value)
/**
 * @def SIMD_LOAD_PS
 *
 * Sets the values of a register to those stored in an array of
 * single-precision, floating-point values.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  fp   A pointer to an array of floats.
 * @param [out] rout The output register.
 */
#define SIMD_LOAD_PS(fp, rout) rout = _mm_load_ps(fp)
/**
 * @def SIMD_SET_ZERO
 *
 * Sets the values of a register to zero.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [out] rout The output register.
 */
#define SIMD_SET_ZERO(rout) rout = _mm_setzero_ps()

/**
 * @def SIMD_STORE_SS
 *
 * Stores the first floating-point value of a register into the buffer pointed
 * to by an address.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [out] addr The output address, pointing to a buffer into which to
 * store the value. 
 * @param [in] rin The input register.
 */
#define SIMD_STORE_SS(addr,rin) _mm_store_ss(addr,rin)

// SQRT Instructions
/**
 * @def SIMD_RSQRT_SS
 *
 * Computes the reciprocal of the square root of each value in the register.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin  The input register. 
 * @param [out] rout The output register.
 */
#define SIMD_RSQRT_SS(rin, rout) rout = _mm_rsqrt_ss(rin) 
/**
 * @def SIMD_SQRT_SS
 *
 * Computes the square root of each value in the register.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin  The input register. 
 * @param [out] rout The output register.
 */
#define SIMD_SQRT_SS(rin, rout) rout = _mm_sqrt_ss(rin)          

// Comparison
/**
 * @def SIMD_CMPEQ_PS
 *
 * Checks for equality with all respective components of two vector registers.
 * Each value in the output register will be either all 0 bits or 1 bits for
 * whether the values of that coordinate in each input register are inequal or
 * are equal, respectively.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin0 The first input register.
 * @param [in]  rin1 The second input register.
 * @param [out] rout The output register.
 */
#define SIMD_CMPEQ_PS(rin0, rin1, rout) rout = _mm_cmpeq_ps(rin0,rin1)

// out[0..31] = in[0..31] + in[32..63] + in[64..95] + in[96..127]
/**
 * @def SIMD_ADD_REGISTER
 *
 * Sums each component of the input vector into the first value of the output
 * vector.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin  The input register.
 * @param [out] rout The output register.
 */
#define SIMD_ADD_REGISTER(rin,rout)                                       \
  __m128 shf_in = _mm_shuffle_ps(rin,rin,_MM_SHUFFLE(1,0,3,2));           \
  __m128 add_in; SIMD_ADD_PS(rin,shf_in, add_in);                         \
  __m128 shf_add = _mm_shuffle_ps(add_in,add_in,_MM_SHUFFLE(2,3,0,1));    \
  SIMD_ADD_PS(shf_add, add_in, rout);

// out = s*in[0..31], s*in[32..63], s*in[64..95], s*in[96..127]
/**
 * @def SIMD_MULT_SCALAR
 *
 * Multiplies each coordinate of an input register by a floating point scalar.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin  The input register.
 * @param [in]  s    The scalar.
 * @param [out] rout The output register.
 */
#define SIMD_MULT_SCALAR(rin, s, rout)                 \
  __m128 mulr; SIMD_SET_PS_2(s, mulr);                 \
  SIMD_MUL_PS(rin,mulr, rout);

// out = in[0..31]/s, s*in[32..63]/s, s*in[64..95]/s, s*in[96..127]/s
/**
 * @def SIMD_DIV_SCALAR
 *
 * Divides each coordinate of an input register by a floating point scalar.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin  The input register.
 * @param [in]  s    The scalar.
 * @param [out] rout The output register.
 */
#define SIMD_DIV_SCALAR(rin, s, rout)                     \
  __m128 divr; SIMD_SET_PS_2(s, divr);                    \
  SIMD_DIV_PS(rin,divr,rout);

// out = Magntiude of rin
/**
 * @def SIMD_MAGNITUDE
 *
 * Finds the magnitude of an input vector.  The first value of the input
 * register will contain the magnitude.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin  The input register.
 * @param [out] rout The output register.
 */
#define SIMD_MAGNITUDE(rin,rout)               \
  __m128 mulr; SIMD_MUL_PS(rin,rin, mulr);     \
  __m128 addr; SIMD_ADD_REGISTER(mulr, addr);  \
  SIMD_SQRT_SS(addr, rout);

/**
 * @def SIMD_DOT_SSE_4
 *
 * Calculates the dot product of two vector registers using SSE4, in which there
 * is a built-in and fast command for it.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin0 The first input register.
 * @param [in]  rin1 The second input register.
 * @param [out] rout The output register.
 */
#define SIMD_DOT_SSE_4(rin0, rin1, rout)  \
  rout = _mm_dp_ps(rin0, rin1, 0xf1);     \

/**
 * @def SIMD_DOT
 *
 * Calculates the dot product of two vector registers.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin0 The first input register.
 * @param [in]  rin1 The second input register.
 * @param [out] rout The output register.
 */
#define SIMD_DOT(rin0, rin1, rout)                  \
  __m128 mulr; SIMD_MUL_PS(rin0,rin1, mulr);        \
  SIMD_ADD_REGISTER(mulr,rout);

/**
 * @def SIMD_DISTANCE
 *
 * Calculate the distance between two vector registers.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-18-19
 * @since  0.3
 *
 * @param [in]  rin0 The first input register.
 * @param [in]  rin1 The second input register.
 * @param [out] rout The output register.
 */
#define SIMD_DISTANCE(rin0, rin1, rout)           \
  __m128 tmp1; SIMD_SUB_PS(rin0, rin1, tmp1);     \
  __m128 tmp2; SIMD_MUL_PS(tmp1, tmp1, tmp2);     \
  SIMD_ADD_REGISTER(tmp2, tmp1);                  \
  SIMD_SQRT_SS(tmp1, rout);

#endif

}
}
}

#endif
