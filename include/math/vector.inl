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

#ifndef HUMMSTRUMM_ENGINE_MATH_VECTOR_INL
#define HUMMSTRUMM_ENGINE_MATH_VECTOR_INL

#include <stdexcept>

namespace hummstrumm
{
namespace engine
{
namespace math
{

template <typename T>
Vector2D<T> &
Vector2D<T>::operator = (const Vector2D<T> &v)
{
  coord.x = v.coord.x;
  coord.y = v.coord.y;
  return *this;
}

template <typename T>
bool 
Vector2D<T>::operator == (const Vector2D<T> &v) const
{
  return coord.x == v.coord.x && coord.y == v.coord.y;
}

template <typename T>
bool 
Vector2D<T>::operator != (const Vector2D<T> &v) const
{
  return coord.x != v.coord.x || coord.y != v.coord.y;
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator + (const Vector2D<T> &v) const
{
  return Vector2D<T> (coord.x + v.coord.x, coord.y + v.coord.y);
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator - (const Vector2D<T> &v) const
{
  return Vector2D<T> (coord.x - v.coord.x, coord.y - v.coord.y);
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator - () const 
{
  return Vector2D<T> (-coord.x, -coord.y); 
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator * (const T &s) const
{
  return Vector2D<T> (coord.x*s,coord.y*s);
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator / (const T &s) const
{
  if (s == 0)
    throw std::domain_error ("Vector division by zero.");

  T oneOverS = 1/s;
  return Vector2D<T> (coord.x*oneOverS, coord.y*oneOverS);
}

template <typename T>
Vector2D<T> &
Vector2D<T>::operator += (const Vector2D<T> &v)
{
  coord.x += v.coord.x; coord.y +=v.coord.y;
  return *this;
}

template <typename T>
Vector2D<T> &
Vector2D<T>::operator -= (const Vector2D<T> &v)
{
  coord.x -= v.coord.x; coord.y -=v.coord.y;
  return *this;
}

template <typename T>
Vector2D<T> &
Vector2D<T>::operator *= (const T &s)
{
  coord.x *= s; coord.y *= s;
  return *this;
}

template <typename T>
Vector2D<T> &
Vector2D<T>::operator /= (const T &s)
{
  if (s == 0)
    throw std::domain_error ("Vector division by zero.");

  T oneOverS = 1/s;
  coord.x *= oneOverS; coord.y *= oneOverS;
  return *this;
}

template <typename T>
void 
Vector2D<T>::Normalize ()
{
  T magSq = Vec2DMagnitude(*this); 
  if (magSq == 0)
    throw std::logic_error ("Vector magnitude is zero.");

  T oneOverMag = 1/magSq;
  coord.x *= oneOverMag;
  coord.y *= oneOverMag;
}

template <typename T>
void 
Vector2D<T>::Zero ()
{
  coord.x = 0;
  coord.y = 0;
}

template <typename T>
Vector3D<T> &
Vector3D<T>::operator = (const Vector3D<T> &v)
{
  coord.x = v.coord.x;
  coord.y = v.coord.y;
  coord.z = v.coord.z;
  return *this;
}

template <typename T>
bool 
Vector3D<T>::operator == (const Vector3D<T> &v) const
{
  return coord.x == v.coord.x && coord.y == v.coord.y && coord.z == v.coord.z;
}

template <typename T>
bool 
Vector3D<T>::operator != (const Vector3D<T> &v) const
{
  return coord.x != v.coord.x || coord.y != v.coord.y || coord.z != v.coord.z;
}

template <typename T>
Vector3D<T> 
Vector3D<T>::operator + (const Vector3D<T> &v) const
{
  return Vector3D<T> (coord.x + v.coord.x, coord.y + v.coord.y, coord.z + v.coord.z);
}

template <typename T>
Vector3D<T> 
Vector3D<T>::operator - (const Vector3D<T> &v) const
{
  return Vector3D<T> (coord.x - v.coord.x, coord.y - v.coord.y, coord.z - v.coord.z);
}

template <typename T>
Vector3D<T> 
Vector3D<T>::operator - () const 
{
  return Vector3D<T> (-coord.x, -coord.y, -coord.z); 
}

template <typename T>
Vector3D<T> 
Vector3D<T>::operator * (const T &s) const
{
  return Vector3D<T> (coord.x*s,coord.y*s,coord.z*s);
}

template <typename T>
Vector3D<T> 
Vector3D<T>::operator / (const T &s) const
{
  if (s == 0)
    throw std::domain_error ("Vector division by zero.");

  T oneOverS = 1/s;
  return Vector3D<T> (coord.x*oneOverS, coord.y*oneOverS, coord.z*oneOverS);
}

template <typename T>
Vector3D<T> &
Vector3D<T>::operator += (const Vector3D<T> &v)
{
  coord.x += v.coord.x; coord.y += v.coord.y; coord.z += v.coord.z;
  return *this;
}

template <typename T>
Vector3D<T> &
Vector3D<T>::operator -= (const Vector3D<T> &v)
{
  coord.x -= v.coord.x; coord.y -= v.coord.y; coord.z -= v.coord.z;
  return *this;
}

template <typename T>
Vector3D<T> &
Vector3D<T>::operator *= (const T &s)
{
  coord.x *= s; coord.y *= s; coord.z *=s;
  return *this;
}

template <typename T>
Vector3D<T> &
Vector3D<T>::operator /= (const T &s)
{
  if (s == 0)
    throw std::domain_error ("Vector division by zero.");

  T oneOverS = 1/s;
  coord.x *= oneOverS; coord.y *= oneOverS; coord.z *= oneOverS;
  return *this;
}

template <typename T>
void 
Vector3D<T>::Normalize ()
{
  T magSq = Vec3DMagnitude(*this); 
  if (magSq == 0)
    throw std::logic_error ("Vector magnitude is zero.");

  T oneOverMag = 1/magSq;
  coord.x *= oneOverMag;
  coord.y *= oneOverMag;
  coord.z *= oneOverMag;
}

template <typename T>
void 
Vector3D<T>::Zero ()
{
  coord.x = 0;
  coord.y = 0;
  coord.z = 0;
}

template <typename T>
Vector4D<T> &
Vector4D<T>::operator = (const Vector4D<T> &v)
{
  coord.x = v.coord.x;
  coord.y = v.coord.y;
  coord.z = v.coord.z;
  coord.w = v.coord.w;
  return *this;
}

template <typename T>
bool 
Vector4D<T>::operator == (const Vector4D<T> &v) const
{
  return coord.x == v.coord.x && coord.y == v.coord.y 
      && coord.z == v.coord.z && coord.w == v.coord.w;
}

template <typename T>
bool 
Vector4D<T>::operator != (const Vector4D<T> &v) const
{
  return coord.x != v.coord.x || coord.y != v.coord.y 
      || coord.z != v.coord.z || coord.w != v.coord.w;
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator + (const Vector4D<T> &v) const
{
  return Vector4D<T> (coord.x + v.coord.x, coord.y + v.coord.y, 
                      coord.z + v.coord.z, coord.w + v.coord.w);
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator - (const Vector4D<T> &v) const
{
  return Vector4D<T> (coord.x - v.coord.x, coord.y - v.coord.y, 
                      coord.z - v.coord.z, coord.w - v.coord.w);
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator - () const 
{
  return Vector4D<T> (-coord.x, -coord.y, -coord.z, -coord.w); 
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator * (const T &s) const
{
  return Vector4D<T> (coord.x*s,coord.y*s,coord.z*s,coord.w*s);
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator / (const T &s) const
{
  if (s == 0)
    throw std::domain_error ("Vector division by zero.");

  T oneOverS = 1/s;
  return Vector4D<T> (coord.x*oneOverS, 
                      coord.y*oneOverS, 
                      coord.z*oneOverS, 
                      coord.w*oneOverS);
}

template <typename T>
Vector4D<T> &
Vector4D<T>::operator += (const Vector4D<T> &v)
{
  coord.x += v.coord.x; coord.y +=v.coord.y; 
  coord.z += v.coord.z; coord.w +=v.coord.w;
  return *this;
}

template <typename T>
Vector4D<T> &
Vector4D<T>::operator -= (const Vector4D<T> &v)
{
  coord.x -= v.coord.x; coord.y -=v.coord.y; 
  coord.z -= v.coord.z; coord.w -=v.coord.w;
  return *this;
}

template <typename T>
Vector4D<T> &
Vector4D<T>::operator *= (const T &s)
{
  coord.x *= s; coord.y *= s; coord.z *=s; coord.w *=s;
  return *this;
}

template <typename T>
Vector4D<T> &
Vector4D<T>::operator /= (const T &s)
{
  if (s == 0)
    throw std::domain_error ("Vector division by zero.");

  T oneOverS = 1/s;
  coord.x *= oneOverS; coord.y *= oneOverS; 
  coord.z *= oneOverS; coord.w *= oneOverS;
  return *this;
}

template <typename T>
void 
Vector4D<T>::Normalize ()
{
  T magSq = Vec4DMagnitude(*this); 
  if (magSq == 0)
    throw std::logic_error ("Vector magnitude is zero.");

  T oneOverMag = 1/magSq;
  coord.x *= oneOverMag;
  coord.y *= oneOverMag;
  coord.z *= oneOverMag;
  coord.w *= oneOverMag;
}

template <typename T>
void 
Vector4D<T>::Zero ()
{
  coord.x = 0;
  coord.y = 0;
  coord.z = 0;
  coord.w = 0;
}

// Non-member implementations

template <typename T> 
T 
Vec2DMagnitude (const Vector2D<T> &v)
{
  return std::sqrt (v.coord.x*v.coord.x + v.coord.y*v.coord.y);
}

template <typename T> 
T 
Vec2DSqMagnitude (const Vector2D<T> &v)
{
  return v.coord.x*v.coord.x + v.coord.y*v.coord.y;
}

template<typename T>
T 
Vec2DDistance (const Vector2D<T> &v, const Vector2D<T> &w)
{
  T dx = v.coord.x - w.coord.x;
  T dy = v.coord.y - w.coord.y;
  return std::sqrt (dx*dx + dy*dy);
}

template<typename T>
T 
Vec2DSqDistance (const Vector2D<T> &v, const Vector2D<T> &w)
{
  T dx = v.coord.x - w.coord.x;
  T dy = v.coord.y - w.coord.y;
  return dx*dx + dy*dy;
}

template <typename T>
T 
Vec2DDot (const Vector2D<T> &v, const Vector2D<T> &w)
{
  return v.coord.x*w.coord.x + v.coord.y*w.coord.y;
}

template <typename T>
Vector2D<T>
Vec2DProjection (const Vector2D<T> &v, const Vector2D<T> &n)
{
  T nDotProd = Vec2DDot(n,n);
  if (nDotProd == 0)
    throw std::domain_error ("Vector division by zero.");

  return n * (Vec2DDot(v,n)/nDotProd); 
}

template <typename T>
Vector2D<T> 
Vec2DPerpendicular (const Vector2D<T> &v)
{
  return Vector2D<T> (v.coord.y,-v.coord.x);
}

template <typename T>
Vector2D<T> 
Vec2DUnitPerpendicular (const Vector2D<T> &v)
{
  T vMag = Vec2DMagnitude(v);
  if (vMag == 0)
    throw std::domain_error ("Vector division by zero.");

  return Vec2DPerpendicular(v)/vMag;
}


template <typename T>
void 
Orthonormalize2D (std::vector<Vector2D<T> > &v)
{
  if (v.size() > 2)
    throw std::out_of_range ("Cannot orthonormalize more than 2 vectors.");

  typename std::vector<Vector2D<T> >::iterator itForward;
  typename std::vector<Vector2D<T> >::iterator itReverse;

  for (itForward = v.begin(); itForward != v.end(); itForward++)
  {
    for (itReverse = itForward; itReverse >= v.begin(); itReverse--)
    {
      if (itReverse != itForward)
        *itForward -= Vec2DProjection(*itForward,*itReverse);
    }
    *itForward = *itForward/Vec2DMagnitude(*itForward);
  }
}


template <typename T>
Vector2D<T>
operator * (const T &k, const Vector2D<T> &v)
{
  return Vector2D<T> (k*v.coord.x,k*v.coord.y);
}

template<typename T> 
T 
Vec3DMagnitude (const Vector3D<T> &v)
{
  return std::sqrt (v.coord.x*v.coord.x  + v.coord.y*v.coord.y + v.coord.z*v.coord.z);
}

template<typename T> 
T 
Vec3DSqMagnitude (const Vector3D<T> &v)
{
  return v.coord.x*v.coord.x  + v.coord.y*v.coord.y + v.coord.z*v.coord.z;
}

template<typename T>
Vector3D<T> 
Vec3DCross (const Vector3D<T> &v, const Vector3D<T> &w)
{
  return Vector3D<T> (v.coord.y*w.coord.z - v.coord.z*w.coord.y,
                      v.coord.z*w.coord.x - v.coord.x*w.coord.z,
                      v.coord.x*w.coord.y - v.coord.y*w.coord.x);
}

template<typename T>
T 
Vec3DDistance (const Vector3D<T> &v, const Vector3D<T> &w)
{
  T dx = v.coord.x - w.coord.x;
  T dy = v.coord.y - w.coord.y;
  T dz = v.coord.z - w.coord.z;
  return std::sqrt (dx*dx + dy*dy + dz*dz);
}

template<typename T>
T 
Vec3DSqDistance (const Vector3D<T> &v, const Vector3D<T> &w)
{
  T dx = v.coord.x - w.coord.x;
  T dy = v.coord.y - w.coord.y;
  T dz = v.coord.z - w.coord.z;
  return dx*dx + dy*dy + dz*dz;
}

template <typename T>
T 
Vec3DDot (const Vector3D<T> &v, const Vector3D<T> &w)
{
  return v.coord.x*w.coord.x + v.coord.y*w.coord.y + v.coord.z*w.coord.z;
}

template <typename T>
Vector3D<T>
Vec3DProjection (const Vector3D<T> &v , const Vector3D<T> &n)
{
  T nDotProd = Vec3DDot(n,n);
  if (nDotProd == 0)
    throw std::domain_error ("Vector division by zero.");

  return n * (Vec3DDot(v,n)/nDotProd);   
}


template <typename T>
void 
Orthonormalize3D (std::vector<Vector3D<T> > &v)
{
  if (v.size() > 3)
    throw std::out_of_range ("Cannot orthonormalize more than 3 vectors.");

  typename std::vector<Vector3D<T> >::iterator itForward;
  typename std::vector<Vector3D<T> >::iterator itReverse;

  for (itForward = v.begin(); itForward != v.end(); itForward++)
  {
    for (itReverse = itForward; itReverse >= v.begin(); itReverse--)
    {
      if (itReverse != itForward)
        *itForward -= Vec3DProjection(*itForward,*itReverse);
    }
    *itForward = *itForward/Vec3DMagnitude(*itForward);
  }
}

template <typename T>
Vector3D<T>
operator * (const T &k, const Vector3D<T> &v)
{
  return Vector3D<T> (k*v.coord.x,k*v.coord.y,k*v.coord.z);
}

template<typename T> 
T 
Vec4DMagnitude (const Vector4D<T> &v)
{
  return std::sqrt (v.coord.x*v.coord.x + v.coord.y*v.coord.y 
                  + v.coord.z*v.coord.z + v.coord.w*v.coord.w);
}

template<typename T> 
T 
Vec4DSqMagnitude (const Vector4D<T> &v)
{
  return v.coord.x*v.coord.x + v.coord.y*v.coord.y 
       + v.coord.z*v.coord.z + v.coord.w*v.coord.w;
}

template<typename T>
T 
Vec4DDistance (const Vector4D<T> &v, const Vector4D<T> &k)
{
  T dx = v.coord.x - k.coord.x;
  T dy = v.coord.y - k.coord.y;
  T dz = v.coord.z - k.coord.z;
  T dw = v.coord.w - k.coord.w;
  return std::sqrt (dx*dx + dy*dy + dw*dw);
}

template<typename T>
T 
Vec4DSqDistance (const Vector4D<T> &v, const Vector4D<T> &k)
{
  T dx = v.coord.x - k.coord.x;
  T dy = v.coord.y - k.coord.y;
  T dz = v.coord.z - k.coord.z;
  T dw = v.coord.w - k.coord.w;
  return dx*dx + dy*dy + dw*dw;
}

template <typename T>
T 
Vec4DDot (const Vector4D<T> &v, const Vector4D<T> &w)
{
  return v.coord.x*w.coord.x + v.coord.y*w.coord.y 
       + v.coord.z*w.coord.z + v.coord.w*w.coord.w;
}

template <typename T>
Vector4D<T>
Vec4DProjection (const Vector4D<T> &v , const Vector4D<T> &n)
{
  T nDotProd = Vec4DDot(n,n);
  if (nDotProd == 0)
    throw std::domain_error ("Vector division by zero.");

  return n * (Vec4DDot(v,n)/nDotProd); 
}

template <typename T>
void 
Orthonormalize4D (std::vector<Vector4D<T> > &v)
{
  if (v.size() > 4)
    throw std::out_of_range ("Cannot orthonormalize more than 4 vectors.");

  typename std::vector<Vector4D<T> >::iterator itForward;
  typename std::vector<Vector4D<T> >::iterator itReverse;

  for (itForward = v.begin(); itForward != v.end(); itForward++)
  {
    for (itReverse = itForward; itReverse >= v.begin(); itReverse--)
    {
      if (itReverse != itForward)
        *itForward -= Vec4DProjection(*itForward,*itReverse);
    }
    *itForward = *itForward/Vec4DMagnitude(*itForward);
  }
}

template <typename T>
Vector4D<T>
operator * (const T &k, const Vector4D<T> &v)
{
  return Vector4D<T> (k*v.coord.x,k*v.coord.y,k*v.coord.z,k*v.coord.w);
}

}
}
}

#endif //HUMMSTRUMM_ENGINE_MATH_VECTOR_INL
