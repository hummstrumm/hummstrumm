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
 * Defines and implements a quaternion.
 *
 * @file    matrice.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 *
 */

#ifndef HUMMSTRUMM_ENGINE_MATH_QUATERNION
#define HUMMSTRUMM_ENGINE_MATH_QUATERNION

#include "error/divisionbyzero.hpp"

namespace hummstrumm
{
namespace engine
{
namespace math
{

template <typename T>
class Vector3D;

template <typename T>
class Quaternion
{
  public:
    Vector3D<T> v;
    T w;

    /**
     * Constructs an identity quaternion. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */
    Quaternion (): w(1) {}

    /**
     * Destructs a quaternion.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */
    ~Quaternion () {}

    /**
     * Construct a quaternion from vector coordinates and 
     * a scalar component.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param w The scalar component w.
     * @param vx The x component of vector.
     * @param vy The y component of vector.
     * @param vw The w component of vector.
     */
    Quaternion (const T &w, const T &vx, const T  &vy, const T &vz)
      : w(w), v(vx, vy, vz) {}
    
    /**
     * Construct a quaternion from a vector and a scalar
     * component.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param w The scalar component w.
     * @param v 3D Vector.
     */
    Quaternion (const T &w, const Vector3D<T> &v)
      : w(w), v(v) {}

    /**
     * Copy Constructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param q A quaternion.
     */
    Quaternion (const Quaternion<T> &q): w(q.w), v(q.v) {}

    /**
     * Assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param q A quaternion.
     *
     * @return This quaternion. 
     */
    Quaternion<T> &operator = (const Quaternion<T> &q);

    /**
     * Equality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param q A quaternion.
     *
     * @return Whether the quaternions are equal. 
     */
    bool operator == (const Quaternion<T> &q) const;

    /**
     * Inequality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param q A quaternion.
     *
     * @return Whether the quaternions are different. 
     */
    bool operator != (const Quaternion<T> &q) const;

    /**
     * Sum this quaternion with another quaternion.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param q A quaternion.
     *
     * @return A quaternion that is the sum of this with q.
     */
    Quaternion<T> operator + (const Quaternion<T> &q) const;

    /**
     * Negate this quaternion.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return The negation of this quaternion.
     */
    Quaternion<T> operator - () const;

    /**
     * Subtract a quaternion from this quaternion.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param q A quaternion.
     *    
     * @return A quaternion that is the subtraction of this with q.
     */
    Quaternion<T> operator - (const Quaternion<T> &q) const;

    /**
     * Multiply another quaternion to this quaternion.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param q A quaternion.
     *
     * @return A quaternion that is the multiplication of this with q.
     *
     * @note Cross Product
     */
    Quaternion<T> operator * (const Quaternion<T> &q) const;

    /**
     * Multiply a scalar to this quaternion.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s A scalar.
     *
     * @return A quaternion that is the multiplication of this with s.
     *
     */
    Quaternion<T> operator * (const T &s) const;

    /**
     * Divide this quaternion by a scalar
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s A scalar.
     *
     * @return A quaternion that is the division of this with s.
     */
    Quaternion<T> operator / (const T &s) const;

    /**
     * Combined sum of this quaternion with another quaternion.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param q A quaternion.
     *
     * @return This quaternion added with q.
     */
    Quaternion<T> &operator += (const Quaternion<T> &q);

    /**
     * Combined subtraction of this quaternion with another quaternion.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param q A quaternion.
     *    
     * @return This quaternion subtracted with q.
     */
    Quaternion<T> &operator -= (const Quaternion<T> &q);

    /**
     * Combined multiplication of this quaternion with another quaternion.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param q A quaternion.
     *
     * @return This quaternion multiplied by q. 
     */
    Quaternion<T> &operator *= (const Quaternion<T> &q);

    /**
     * Combined multiplication of a scalar with this quaternion.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s A scalar.
     *
     * @return This quaternion multiplied by s.
     */
    Quaternion<T> &operator *= (const T &s);

    /**
     * Combined division of this quaternion by a scalar
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s A scalar.
     *
     * @return This quaternion divided by s.
     */
    Quaternion<T> &operator /= (const T &s);

    /**
     * Set this quaternion using the axis-angle pair representation.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param angle Angle in radians to rotate about the axis.
     * @param axis Rotation axis (should be normalized).
     */
    void SetAxisAngle (const T &angle, const Vector3D<T> &axis);

     /**
     * Set this quaternion to identity.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     */
    void Identity ();

     /**
     * Set this quaternion to its conjugate.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     */
    void Conjugate ();

     /**
     * Normalize this quaternion.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     */
    void Normalize ();
 
  private:

  protected:


}; // end of class quaternion

// implementation of member functions

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
  return Quaternion<T> (w*q.w - Vec3DDot(v,q.v), w*q.v + q.w*v + Vec3DCross(q.v,v));
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
    THROW (DivisionByZero,"Quaternion division by zero.");

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
    THROW (DivisionByZero,"Quaternion division by zero.");

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
  v.x = 0;
  v.y = 0;
  v.z = 0;
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
    THROW (DivisionByZero,"Quaternion magnitude is zero.");
 
  T oneOverMag = 1/qMag;
  v *= oneOverMag;
  w *= oneOverMag; 
}


// non-member functions declaration

/**
 * The dot product of two quaternions
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param n A quaternion.
 * @param q Another quatenrion.
 *
 * @return The dot product of n with q.
 */
template <typename T>
T QuatDot (const Quaternion<T> &n, const Quaternion<T> &q);

/**
 * Scalar on the left multiplication, for symmetry.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param s A scalar.
 * @param q A quaternion.
 *
 * @return The quaternion that resulted from s*q.
 */
template <typename T>
Quaternion<T> operator * (const T &s, const Quaternion<T> &q);

/**
 * Get the conjugate of a quaternion.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param q A quaternion.
 *
 * @return The conjugate of q.
 */
template <typename T>
Quaternion<T> QuatConjugate (const Quaternion<T> &q);

/**
 * Get the magnitude of a quaternion.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param q A quaternion.
 *
 * @return The magnitude q.
 */
template <typename T>
T QuatMagnitude (const Quaternion<T> &q);

/**
 * Get the inverse of a quaternion.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param q A quaternion.
 *
 * @return The inverse of q.
 */
template <typename T>
Quaternion<T> QuatInverse (const Quaternion<T> &q);

/**
 * Get the logarithm of a quaternion.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param q A quaternion. Should be normalized 
 * before used in here.
 *
 * @return The logarithm of q. 
 */
template <typename T>
Quaternion<T> QuatLog (const Quaternion<T> &q);

/**
 * Get the exponential of a quaternion.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param q A quaternion. 
 *
 * @return The exponential of q.
 */
template <typename T>
Quaternion<T> QuatExp (const Quaternion<T> &q);

/**
 * Get the quaternion power.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param q A quaternion.
 * @param e Another quaternion.
 *
 * @return Quaternion q raised to e.
 */
template <typename T>
Quaternion<T> QuatPow (const Quaternion<T> &q, const Quaternion<T> &e);

/**
 * Get the quaternion exponentiation.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param q A quaternion.
 * @param e Scalar.
 *
 * @return Quaternion q raised to e.
 */
template <typename T>
Quaternion<T> QuatPow (const Quaternion<T> &q, const T &e);

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
  return std::sqrt (q.w*q.w + q.v.x*q.v.x + q.v.y*q.v.y + q.v.z*q.v.z);
}

template <typename T>
Quaternion<T>
QuatInverse (const Quaternion<T> &q)
{
  T quatMag = QuatMagnitude(q);
  if (quatMag == 0)
    THROW (DivisionByZero,"Quaternion magnitude is zero.");
 
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
  return QuatExp (e*QuatLog(q));
}

template <typename T>
Quaternion<T>
QuatPow (const Quaternion<T> &q, const T &e)
{
  return QuatExp (QuatLog(q)*e);
}

}
}
}

#endif
