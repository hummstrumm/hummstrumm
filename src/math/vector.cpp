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

#include <stdexcept>

namespace hummstrumm
{
namespace engine
{
namespace math
{

using hummstrumm::engine::core::Engine;

#ifdef HUMMSTRUMM_HAVE_SSE_SUPPORT

Vector4D<float> &
Vector4D<float>::operator = (const Vector4D<float> &v)
{
  SIMD_LOAD_PS(v.f, xyzw);
  return *this;
}

bool 
Vector4D<float>::operator == (const Vector4D<float> &v) const
{
  return coord.x == v.coord.x 
      && coord.y == v.coord.y 
      && coord.z == v.coord.z 
      && coord.w == v.coord.w;
}

bool 
Vector4D<float>::operator != (const Vector4D<float> &v) const
{
  return coord.x != v.coord.x 
      || coord.y != v.coord.y 
      || coord.z != v.coord.z 
      || coord.w != v.coord.w;
}

Vector4D<float> 
Vector4D<float>::operator - () const
{
  return Vector4D<float> (-coord.x, -coord.y, -coord.z, -coord.w);
}

Vector4D<float> 
Vector4D<float>::operator + (const Vector4D<float> &v) const
{
  __m128 res; SIMD_ADD_PS(xyzw,v.xyzw, res);
  return Vector4D<float> (res);
}

Vector4D<float> 
Vector4D<float>::operator - (const Vector4D<float> &v) const
{
  __m128 res; SIMD_SUB_PS(xyzw,v.xyzw, res);
  return Vector4D<float> (res);
}

Vector4D<float> 
Vector4D<float>::operator * (const float &s) const
{
  __m128 res; SIMD_MULT_SCALAR(xyzw,s,res);
  return Vector4D<float> (res);
}

Vector4D<float> 
Vector4D<float>::operator / (const float &s) const
{
  if (s == 0)
    throw std::domain_error ("Vector division by zero.");

  __m128 res; SIMD_DIV_SCALAR(xyzw,s, res);
  return Vector4D<float> (res);
}

Vector4D<float> &
Vector4D<float>::operator += (const Vector4D<float> &v)
{
  SIMD_ADD_PS(xyzw,v.xyzw, xyzw);
  return *this;
}

Vector4D<float> &
Vector4D<float>::operator -= (const Vector4D<float> &v)
{
  SIMD_SUB_PS(xyzw,v.xyzw, xyzw);
  return *this;
}

Vector4D<float> &
Vector4D<float>::operator *= (const float &s)
{
  SIMD_MULT_SCALAR(xyzw,s, xyzw);
  return *this;
}

Vector4D<float> &
Vector4D<float>::operator /= (const float &s)
{
  if (s == 0)
    throw std::domain_error ("Vector division by zero.");

  SIMD_DIV_SCALAR(xyzw,s, xyzw);
  return *this;
}

void 
Vector4D<float>::Normalize ()
{
  float magSq = Vec4DMagnitude(*this);
  if (magSq == 0)
    throw std::domain_error ("Vector magnitude is zero.");

  SIMD_DIV_SCALAR(xyzw,magSq, xyzw);
}

void 
Vector4D<float>::Zero ()
{
  SIMD_SET_ZERO(xyzw);
}

template<>
float
Vec4DMagnitude (const Vector4D<float> &v)
{
  float res = 0;
  __m128 mag;
  SIMD_MAGNITUDE(v.xyzw, mag);
  SIMD_STORE_SS(&res,mag);
  return res;
}

template<>
float
Vec4DSqMagnitude (const Vector4D<float> &v)
{
  float res = 0;
  __m128 sqmag; 
  SIMD_DOT(v.xyzw,v.xyzw, sqmag)
  SIMD_STORE_SS(&res,sqmag);
  return res;
}

template<>
float
Vec4DDistance (const Vector4D<float> &v, const Vector4D<float> &k)
{
  float res = 0;
  __m128 dist;
  SIMD_DISTANCE(v.xyzw, k.xyzw, dist);
  SIMD_STORE_SS(&res, dist);
  return res;
}

template<>
float
Vec4DDot (const Vector4D<float> &v, const Vector4D<float> &k)
{
  float res = 0;
  __m128 dot;

//  Engine *engine = Engine::GetEngine ();

//  if (engine->GetProcessors()->HaveSse41Support())
//  {
//    SIMD_DOT_SSE_4(v.xyzw, k.xyzw, dot);
//  }
//  else
//  {
    SIMD_DOT(v.xyzw, k.xyzw, dot);
//  }
  SIMD_STORE_SS(&res, dot);
  return res;
}

#endif

}
}
}

