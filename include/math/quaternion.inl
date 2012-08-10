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

#ifndef HUMMSTRUMM_ENGINE_VECTOR_INL
#define HUMMSTRUMM_ENGINE_VECTOR_INL

#include <stdexcept>

namespace hummstrumm
{
namespace engine
{
namespace math
{

// implementation of member functions
template <typename T>
Quaternion<T>::Quaternion (const Matrix3D<T> &m)
{
  // from 3d math primer - shoemake method
  T tmpW = m[0].coord.x + m[1].coord.y + m[2].coord.z;
  T tmpX = m[0].coord.x - m[1].coord.y - m[2].coord.z;
  T tmpY = m[1].coord.y - m[0].coord.x - m[2].coord.z;
  T tmpZ = m[2].coord.z - m[0].coord.x - m[1].coord.y;
      
  unsigned short biggestIndex = 0;
  T biggestTmp = tmpW;
  if (tmpX > biggestTmp)
  {
    biggestTmp = tmpX;
    biggestIndex = 1;
  }
  if (tmpY > biggestTmp)
  {
    biggestTmp = tmpY;
    biggestIndex = 2;
  }
  if (tmpZ > biggestTmp)
  {
    biggestTmp = tmpZ;
    biggestIndex = 3;
  }
  T biggestVal = sqrt(biggestTmp + 1) * 0.5;
  T mult = 0.25 / biggestVal;

  switch (biggestIndex)
  {
    case 0:
      w = biggestVal;
      v.coord.x = (m[1].coord.z - m[2].coord.y) * mult;
      v.coord.y = (m[2].coord.x - m[0].coord.z) * mult;
      v.coord.z = (m[0].coord.y - m[1].coord.x) * mult;
      break;

    case 1:
      v.coord.x = biggestVal;
      w = (m[1].coord.z - m[2].coord.y) * mult;
      v.coord.y = (m[0].coord.y - m[1].coord.x) * mult;
      v.coord.z = (m[2].coord.x - m[0].coord.z) * mult;
      break;

    case 2:
      v.coord.y = biggestVal;
      w = (m[2].coord.x - m[0].coord.z) * mult;
      v.coord.x = (m[0].coord.y - m[1].coord.x) * mult;
      v.coord.z = (m[1].coord.z - m[2].coord.y) * mult;
     break;

    case 3:
      v.coord.z = biggestVal;
      w = (m[0].coord.y - m[1].coord.x) * mult;
      v.coord.x = (m[2].coord.x - m[0].coord.z) * mult;
      v.coord.y = (m[1].coord.z - m[2].coord.y) * mult;
     break;
  }
}


template <typename T>
Quaternion<T> & 
Quaternion<T>::operator = (const Quaternion<T> &q)
{
  w = q.w;
  v = q.v;
  return *this;
}

template <typename T>
bool 
Quaternion<T>::operator == (const Quaternion<T> &q) const
{
  return w == q.w && v == q.v;
}

template <typename T>
bool 
Quaternion<T>::operator != (const Quaternion<T> &q) const
{
  return w != q.w || v != q.v;
}

template <typename T>
Quaternion<T>
Quaternion<T>::operator + (const Quaternion<T> &q) const
{
  return Quaternion<T> (w + q.w, v + q.v);
}

template <typename T>
Quaternion<T>
Quaternion<T>::operator - (const Quaternion<T> &q) const
{
  return Quaternion<T> (w - q.w, v - q.v);
}

template <typename T>
Quaternion<T> 
Quaternion<T>::operator - () const
{
  return Quaternion<T> (-w,-v);
}

template <typename T>
Quaternion<T>
Quaternion<T>::operator * (const Quaternion<T> &q) const
{
  return Quaternion<T> (w*q.w - Vec3DDot(v,q.v), w*q.v + q.w*v + Vec3DCross(v,q.v));
}

template <typename T>
Quaternion<T>
Quaternion<T>::operator * (const T &s) const
{
  return Quaternion<T> (s*w, s*v);
}

template <typename T>
Quaternion<T>
Quaternion<T>::operator / (const T &s) const
{
  if (s == 0)
    throw std::domain_error ("Quaternion division by zero.");

  T oneOverS = 1/s; 
  return Quaternion<T> (oneOverS*w,oneOverS*v);
}

template <typename T>
Quaternion<T> &
Quaternion<T>::operator += (const Quaternion<T> &q)
{
  w += q.w;
  v += q.v;  
  return *this;
}

template <typename T>
Quaternion<T> &
Quaternion<T>::operator -= (const Quaternion<T> &q)
{
  w -= q.w;
  v -= q.v;
  return *this;
}

template <typename T>
Quaternion<T> &
Quaternion<T>::operator *= (const Quaternion<T> &q)
{
  T aux;
  aux = w*q.w - Vec3DDot(v,q.v);
  v = w*q.v + q.w*v + (q.v).Vec3DCross(v);
  w = aux;
  return *this;
}

template <typename T>
Quaternion<T> &
Quaternion<T>::operator *= (const T &s)
{
  w *= s;
  v *= s;
  return *this;
}

template <typename T>
Quaternion<T> &
Quaternion<T>::operator /= (const T &s)
{
  if (s == 0)
    throw std::domain_error ("Quaternion division by zero.");

  T oneOverS = 1/s;
  w *= oneOverS;
  v *= oneOverS;
  return *this;
}

template <typename T>
void
Quaternion<T>::SetAxisAngle (const T &angle, const Vector3D<T> &axis)
{
  w = std::cos(angle/2);
  v = std::sin(angle/2)*axis;
}

template <typename T>
void 
Quaternion<T>::Identity ()
{
  w = 1;
  v.coord.x = 0;
  v.coord.y = 0;
  v.coord.z = 0;
}

template <typename T>
void 
Quaternion<T>::Conjugate ()
{
  v = -v;
}

template <typename T>
void 
Quaternion<T>::Normalize ()
{
  T qMag = QuatMagnitude(*this);
  if (qMag == 0)
    throw std::logic_error ("Quaternion magnitude is zero.");
 
  T oneOverMag = 1/qMag;
  v *= oneOverMag;
  w *= oneOverMag; 
}

// non-member functions implementation

template <typename T>
T 
QuatDot (const Quaternion<T> &n, const Quaternion<T> &q)
{
  return n.w*q.w + Vec3Dot(n.v,q.v);
}

template <typename T>
Quaternion<T>
operator * (const T &s, const Quaternion<T> &q)
{
   return Quaternion<T> (s*q.w, s*q.v); 
}

template <typename T>
Quaternion<T> 
QuatConjugate (const Quaternion<T> &q)
{
  return Quaternion<T> (q.w, -q.v);
}

template <typename T>
T 
QuatMagnitude (const Quaternion<T> &q)
{
  return std::sqrt (q.w*q.w + q.v.coord.x*q.v.coord.x + q.v.coord.y*q.v.coord.y + q.v.coord.z*q.v.coord.z);
}

template <typename T>
Quaternion<T>
QuatInverse (const Quaternion<T> &q)
{
  T quatMag = QuatMagnitude(q);
  if (quatMag == 0)
    throw std::logic_error ("Quaternion magnitude is zero.");
 
  return QuatConjugate(q) / quatMag;
}

template <typename T>
Quaternion<T>
QuatLog (const Quaternion<T> &q)
{
  T qMag = QuatMagnitude(q);
  T qvMag = Vec3DMagnitude(q.v);
  if (qMag == 0 || qvMag == 0 )
    return Quaternion<T> (log(qMag), 0, 0, 0);
  
  return Quaternion<T> (log(qMag), q.v/qvMag*acos(q.w/qMag));
}

template <typename T>
Quaternion<T>
QuatExp (const Quaternion<T> &q)
{
  T qvMag = Vec3DMagnitude(q.v);
  
  if (qvMag == 0)
    return std::exp(q.w)*Quaternion<T> (cos(qvMag), 0, 0, 0);
 
  return std::exp(q.w)*Quaternion<T> (cos(qvMag), 
                                      (q.v/qvMag) * sin(qvMag));
}

template <typename T>
Quaternion<T>
QuatPow (const Quaternion<T> &q, const Quaternion<T> &e)
{
  return QuatExp (QuatLog(q)*e);
}

template <typename T>
Quaternion<T>
QuatPow (const Quaternion<T> &q, const T &e)
{
  return QuatExp (QuatLog(q)*e);
}

template <typename T>
Quaternion<T>
QuatSlerp (const Quaternion<T> &q, const Quaternion<T> &w, const T &t)
{
  if ( t < 0 || t > 1)
    throw std::out_of_range
      ("Interpolation parameter is not in the range of [0..1]");

  Quaternion<T> aux;
  T k0, k1;
  T cosOmega = QuatDot (q,w);
  if (cosOmega < 0)
  {
    aux = -w;
    cosOmega = -cosOmega; 
  }
  // check if q and w are very close together
  // to protec against divide-by-zero
  if (cosOmega > 0.9999)
  {
    //use linear interpolation
    k0 = 1 - t;
    k1 = t;
  }
  else
  {
    T sinOmega = std::sqrt(1 - cosOmega*cosOmega);
    T omega = atan2 (sinOmega, cosOmega);
    T oneOverSinOmega = 1 / sinOmega;
    k0 = sin((1 - t) * omega) * oneOverSinOmega;
    k1 = sin(t * omega) * oneOverSinOmega;
  }
  // interpolate
  aux.w = q.w*k0 + aux.w*k1;
  aux.v.coord.x = q.v.coord.x*k0 + aux.v.coord.x*k1;
  aux.v.coord.y = q.v.coord.y*k0 + aux.v.coord.y*k1;
  aux.v.coord.z = q.v.coord.z*k0 + aux.v.coord.z*k1;
  return aux; 
}


template <typename T>
Quaternion<T>
QuatAngDisp (const Quaternion<T> &q, const Quaternion<T> &w)
{
  return QuatInverse(q) * w;
}

template <typename T>
Quaternion<T>
QuatSquad (const Quaternion<T> &q, const Quaternion<T> &w,
           const Quaternion<T> &z, const Quaternion<T> &x, const T &h)
{
  if ( h < 0 || h > 1)
    throw std::out_of_range
      ("Interpolation parameter is not in the range of [0..1]");

  return QuatSlerp(QuatSlerp(q,w,h),QuatSlerp(z,x,h),2*h(1-h));
}

}
}
}

#endif //HUMMSTRUMM_ENGINE_VECTOR_INL
