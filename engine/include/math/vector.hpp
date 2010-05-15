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
 * Defines and implements classes for vectors in 2,3,and 4 dimensions.
 *
 * @file    vector.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 */

#ifndef HUMMSTRUMM_ENGINE_MATH_VECTOR
#define HUMMSTRUMM_ENGINE_MATH_VECTOR

#include <vector>
#include <algorithm>
#include <cmath>

#include <error/outofrange.hpp>
#include <error/divisionbyzero.hpp>

namespace hummstrumm
{
namespace engine
{
namespace math
{

template <typename T>
class Vector2D
{
  public:
    T x,y;

    /**
     * Constructs a null Vector2D object.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    Vector2D () : x(0), y(0) {}

    /** 
     * Construct a Vector2D object. It will assign coordinates vx, 
     * and vy to x and y respectively.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param vx X coordinate.
     * @param vy Y coordinate.
     *
     */
    Vector2D (const T &vx, const T &vy) : x(vx), y(vy) {}

    /** 
     * Copy constructor for Vector2D class.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param v A 2d vector.
     *
     */ 
    Vector2D (const Vector2D<T>  &v) : x(v.x), y(v.y) {}

    /** 
     * Destructs a Vector2D object.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    ~Vector2D () {}

    /** 
     * Assignment operator. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 2d vector.
     *
     * @return This vector.
     */ 
    Vector2D<T> &operator = (const Vector2D<T> &v);

    /** 
     * Equality operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 2d vector.
     * 
     * @return Whether the vectors are equal.
     */
    bool operator == (const Vector2D<T> &v) const;

    /** 
     * Inequality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 2d vector.
     * 
     * @return Whether the vectors are different.
     */
    bool operator != (const Vector2D<T> &v) const;
    
    /** 
     * Unary minus. Negate this vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return A 2d vector.
     */
    Vector2D<T> operator - () const;
   
    /** 
     * Sum this vector with another 2d vector. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 2d vector.
     * 
     * @return A 2d vector.
     */
    Vector2D<T> operator + (const Vector2D<T> &v) const;

    /** 
     * Subtract this vector with antoher 2d vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 2d vector.
     * 
     * @return A 2d vector.
     */
    Vector2D<T> operator - (const Vector2D<T> &v) const;

    /** 
     * Multiplication of this vector with a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 2d vector.
     */
    Vector2D<T> operator * (T s) const;

    /** 
     * Division of this vector with a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 2d vector.
     */
    Vector2D<T> operator / (T s) const;

    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 2d vector.
     * 
     * @return This vector.
     */
    Vector2D<T> &operator += (const Vector2D<T> &v);

    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 2d vector.
     * 
     * @return This vector.
     */
    Vector2D<T> &operator -= (const Vector2D<T> &v);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return This vector.
     */
    Vector2D<T> &operator *= (T s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return This vector.
     */
    Vector2D<T> &operator /= (T s);

    /** 
     * Normalize this vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */
    void Normalize ();

    /** 
     * Set this vector to zero.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */
    void Zero ();

  private:

  protected:

};

template <typename T>
class Vector3D
{
  public:
    T x,y,z;

    /**
     * Constructs a null Vector3D object.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    Vector3D () : x(0), y(0), z(0) {}

    /** 
     * Construct a Vector3D object. It will assign coordinates vx, 
     * vy, and vz to x, y, and z respectively.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param vx X coordinate.
     * @param vy Y coordinate.
     * @param vz Z coordinate.
     *
     */
    Vector3D (const T &vx, const T &vy, const T &vz) 
             : x(vx), y(vy), z(vz) {}

    /** 
     * Copy constructor for Vector3D class.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param v A 3d vector.
     *
     */ 
    Vector3D (const Vector3D<T>  &v)
             : x(v.x), y(v.y), z(v.z) {}

    /** 
     * Destructs a Vector3D object.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    ~Vector3D () {}

    /** 
     * Assignment operator. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 3d vector.
     *
     * @return This vector.
     */ 
    Vector3D<T> &operator = (const Vector3D<T> &v);

    /** 
     * Equality operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 3d vector.
     * 
     * @return Whether the vectors are equal.
     */
    bool operator == (const Vector3D<T> &v) const;

    /** 
     * Inequality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 3d vector.
     * 
     * @return Whether the vectors are different.
     */
    bool operator != (const Vector3D<T> &v) const;
    
    /** 
     * Unary minus. Negate this vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return A 3d vector.
     */
    Vector3D<T> operator - () const;
   
    /** 
     * Sum this vector with another 3d vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 3d vector.
     * 
     * @return A 3d vector.
     */
    Vector3D<T> operator + (const Vector3D<T> &v) const;

    /** 
     * Subtract this vector with antoher 3d vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 3d vector.
     * 
     * @return A 3d vector.
     */
    Vector3D<T> operator - (const Vector3D<T> &v) const;

    /** 
     * Multiplication of this vector by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 3d vector.
     */
    Vector3D<T> operator * (T s) const;

    /** 
     * Division of this vector by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 3d vector.
     */
    Vector3D<T> operator / (T s) const;

    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 3d vector.
     * 
     * @return This vector.
     */
    Vector3D<T> &operator += (const Vector3D<T> &v);

    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 3d vector.
     * 
     * @return This vector.
     */
    Vector3D<T> &operator -= (const Vector3D<T> &v);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return This vector.
     */
    Vector3D<T> &operator *= (T s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return This vector.
     */
    Vector3D<T> &operator /= (T s);

    /** 
     * Normalize this vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */
    void Normalize ();

    /** 
     * Set this vector to zero.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */
    void Zero ();

  private:

  protected:

};

template <typename T>
class Vector4D
{
  public:
    T x,y,z,w;

    /**
     * Constructs a null Vector4D object.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    Vector4D () : x(0), y(0), z(0), w(0) {}

    /** 
     * Construct a Vector4D object. It will assign coordinates vx, 
     * vy,vz, and vw to x,y,z, and w respectively.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param vx X coordinate.
     * @param vy Y coordinate.
     * @param vz Z coordinate.
     * @param vw W coordinate.
     *
     */
    Vector4D (const T &vx, const T &vy, const T &vz, const T &vw)
             : x(vx), y(vy), z(vz), w(vw) {}

    /** 
     * Copy constructor for Vector4D class.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param v A 4d vector.
     *
     */ 
    Vector4D (const Vector4D<T>  &v)
             : x(v.x), y(v.y), z(v.z), w(v.w) {} 

    /** 
     * Destructs a Vector4D object.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    ~Vector4D () {}

    /** 
     * Assignment operator. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 3d vector.
     *
     * @return This vector.
     */ 
    Vector4D<T> &operator = (const Vector4D<T> &v);

    /** 
     * Equality operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 4d vector.
     * 
     * @return Whether the vectors are equal.
     */
    bool operator == (const Vector4D<T> &v) const;

    /** 
     * Inequality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 4d vector.
     * 
     * @return Whether the vectors are different.
     */
    bool operator != (const Vector4D<T> &v) const;
    
    /** 
     * Unary minus. Negate this vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return A 4d vector.
     */
    Vector4D<T> operator - () const;
   
    /** 
     * Sum this vector with another 4d vector. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 4d vector.
     * 
     * @return A 4d vector.
     */
    Vector4D<T> operator + (const Vector4D<T> &v) const;

    /** 
     * Subtract this vector with another 4d vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 4d vector.
     * 
     * @return A 4d vector.
     */
    Vector4D<T> operator - (const Vector4D<T> &v) const;

    /** 
     * Multiplication of scalar with this vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 4d vector.
     */
    Vector4D<T> operator * (T s) const;

    /** 
     * Division of a Vector4D object by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 4d vector.
     *
     */
    Vector4D<T> operator / (T s) const;

    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 4d vector.
     * 
     * @return This vector.
     */
    Vector4D<T> &operator += (const Vector4D<T> &v);

    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A 4d vector.
     * 
     * @return This vector.
     */
    Vector4D<T> &operator -= (const Vector4D<T> &v);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return This vector.
     */
    Vector4D<T> &operator *= (T s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return This vector.
     */
    Vector4D<T> &operator /= (T s);

    /** 
     * Normalize this vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */
    void Normalize ();

    /** 
     * Set this vector to zero.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */
    void Zero ();

  private:

  protected:

};

// Implementation of Vector2D,3D,4D

template <typename T>
Vector2D<T> &
Vector2D<T>::operator = (const Vector2D<T> &v)
{
  x = v.x;
  y = v.y;
  return *this;
}

template <typename T>
bool 
Vector2D<T>::operator == (const Vector2D<T> &v) const
{
  return x == v.x && y == v.y;
}

template <typename T>
bool 
Vector2D<T>::operator != (const Vector2D<T> &v) const
{
  return x != v.x || y != v.y;
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator + (const Vector2D<T> &v) const
{
  return Vector2D<T> (x + v.x, y + v.y);
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator - (const Vector2D<T> &v) const
{
  return Vector2D<T> (x - v.x, y - v.y);
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator - () const 
{
  return Vector2D<T> (-x, -y); 
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator * (T s) const
{
  return Vector2D<T> (x*s,y*s);
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator / (T s) const
{
  if (s == 0)
    THROW (DivisionByZero,"Vector division by zero.");

  T oneOverS = 1/s;
  return Vector2D<T> (x*oneOverS, y*oneOverS);
}

template <typename T>
Vector2D<T> &
Vector2D<T>::operator += (const Vector2D<T> &v)
{
  x += v.x; y +=v.y;
  return *this;
}

template <typename T>
Vector2D<T> &
Vector2D<T>::operator -= (const Vector2D<T> &v)
{
  x -= v.x; y -=v.y;
  return *this;
}

template <typename T>
Vector2D<T> &
Vector2D<T>::operator *= (T s)
{
  x *= s; y *= s;
  return *this;
}

template <typename T>
Vector2D<T> &
Vector2D<T>::operator /= (T s)
{
  if (s == 0)
    THROW (DivisionByZero,"Vector division by zero.");

  T oneOverS = 1/s;
  x *= oneOverS; y *= oneOverS;
  return *this;
}

template <typename T>
void 
Vector2D<T>::Normalize ()
{
  T magSq = Vec2DMagnitude(*this); 
  if (magSq == 0)
    THROW (DivisionByZero,"Vector magnitude is zero.");

  T oneOverMag = 1/magSq;
  x *= oneOverMag;
  y *= oneOverMag;
}

template <typename T>
void 
Vector2D<T>::Zero ()
{
  x = 0;
  y = 0;
}

template <typename T>
Vector3D<T> &
Vector3D<T>::operator = (const Vector3D<T> &v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

template <typename T>
bool 
Vector3D<T>::operator == (const Vector3D<T> &v) const
{
  return x == v.x && y == v.y && z == v.z;
}

template <typename T>
bool 
Vector3D<T>::operator != (const Vector3D<T> &v) const
{
  return x != v.x || y != v.y || z != v.z;
}

template <typename T>
Vector3D<T> 
Vector3D<T>::operator + (const Vector3D<T> &v) const
{
  return Vector3D<T> (x + v.x, y + v.y, z + v.z);
}

template <typename T>
Vector3D<T> 
Vector3D<T>::operator - (const Vector3D<T> &v) const
{
  return Vector3D<T> (x - v.x, y - v.y, z - v.z);
}

template <typename T>
Vector3D<T> 
Vector3D<T>::operator - () const 
{
  return Vector3D<T> (-x,-y, -z); 
}

template <typename T>
Vector3D<T> 
Vector3D<T>::operator * (T s) const
{
  return Vector3D<T> (x*s,y*s,z*s);
}

template <typename T>
Vector3D<T> 
Vector3D<T>::operator / (T s) const
{
  if (s == 0)
    THROW (DivisionByZero,"Vector division by zero.");

  T oneOverS = 1/s;
  return Vector3D<T> (x*oneOverS, y*oneOverS, z*oneOverS);
}

template <typename T>
Vector3D<T> &
Vector3D<T>::operator += (const Vector3D<T> &v)
{
  x += v.x; y +=v.y; z +=v.z;
  return *this;
}

template <typename T>
Vector3D<T> &
Vector3D<T>::operator -= (const Vector3D<T> &v)
{
  x -= v.x; y -=v.y; z -=v.z;
  return *this;
}

template <typename T>
Vector3D<T> &
Vector3D<T>::operator *= (T s)
{
  x *= s; y *= s; z *=s;
  return *this;
}

template <typename T>
Vector3D<T> &
Vector3D<T>::operator /= (T s)
{
  if (s == 0)
    THROW (DivisionByZero,"Vector division by zero.");

  T oneOverS = 1/s;
  x *= oneOverS; y *= oneOverS; z *= oneOverS;
  return *this;
}

template <typename T>
void 
Vector3D<T>::Normalize ()
{
  T magSq = Vec3DMagnitude(*this); 
  if (magSq == 0)
    THROW (DivisionByZero,"Vector magnitude is zero.");

  T oneOverMag = 1/magSq;
  x *= oneOverMag;
  y *= oneOverMag;
  z *= oneOverMag;
}

template <typename T>
void 
Vector3D<T>::Zero ()
{
  x = 0;
  y = 0;
  z = 0;
}

template <typename T>
Vector4D<T> &
Vector4D<T>::operator = (const Vector4D<T> &v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
  return *this;
}

template <typename T>
bool 
Vector4D<T>::operator == (const Vector4D<T> &v) const
{
  return x == v.x && y == v.y && z == v.z && w == v.w;
}

template <typename T>
bool 
Vector4D<T>::operator != (const Vector4D<T> &v) const
{
  return x != v.x || y != v.y || z != v.z || w != v.w;
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator + (const Vector4D<T> &v) const
{
  return Vector4D<T> (x + v.x, y + v.y, z + v.z, w + v.w);
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator - (const Vector4D<T> &v) const
{
  return Vector4D<T> (x - v.x, y - v.y, z - v.z, w - v.w);
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator - () const 
{
  return Vector4D<T> (-x, -y, -z, -w); 
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator * (T s) const
{
  return Vector4D<T> (x*s,y*s,z*s,w*s);
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator / (T s) const
{
  if (s == 0)
    THROW (DivisionByZero,"Vector division by zero.");

  T oneOverS = 1/s;
  return Vector4D<T> (x*oneOverS, 
                      y*oneOverS, 
                      z*oneOverS, 
                      w*oneOverS);
}

template <typename T>
Vector4D<T> &
Vector4D<T>::operator += (const Vector4D<T> &v)
{
  x += v.x; y +=v.y; z +=v.z; w +=v.w;
  return *this;
}

template <typename T>
Vector4D<T> &
Vector4D<T>::operator -= (const Vector4D<T> &v)
{
  x -= v.x; y -=v.y; z -=v.z; w -=v.w;
  return *this;
}

template <typename T>
Vector4D<T> &
Vector4D<T>::operator *= (T s)
{
  x *= s; y *= s; z *=s; w *=s;
  return *this;
}

template <typename T>
Vector4D<T> &
Vector4D<T>::operator /= (T s)
{
  if (s == 0)
    THROW (DivisionByZero,"Vector division by zero.");

  T oneOverS = 1/s;
  x *= oneOverS; y *= oneOverS; z *= oneOverS; w *= oneOverS;
  return *this;
}

template <typename T>
void 
Vector4D<T>::Normalize ()
{
  T magSq = Vec4DMagnitude(*this); 
  if (magSq == 0)
    THROW (DivisionByZero,"Vector magnitude is zero.");

  T oneOverMag = 1/magSq;
  x *= oneOverMag;
  y *= oneOverMag;
  z *= oneOverMag;
  w *= oneOverMag;
}

template <typename T>
void 
Vector4D<T>::Zero ()
{
  x = 0;
  y = 0;
  z = 0;
  w = 0;
}


// Non-member functions declarations

/** 
 * Magnitude of a vector.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 2d vector.
 * 
 * @return The magnitude of vector v.
 */
template <typename T> 
T 
Vec2DMagnitude (const Vector2D<T> &v);

/** 
 * Distance between two vectors. 
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 2d vector.
 * @param w Another 2d vector.
 * 
 * @return The distance between the vectors.
 */
template <typename T>
T 
Vec2DDistance (const Vector2D<T> &v, const Vector2D<T> &w);

/** 
 * Dot product between two 2d vectors.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 2d vector.
 * @param w Another 2d vector.
 * 
 * @return The result of the dot product between v and w.
 */
template <typename T>
T 
Vec2DDot (const Vector2D<T> &v, const Vector2D<T> &w);

/** 
 * Projection of v onto n.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 2d vector.
 * @param n Another 2d vector.
 * 
 * @return The projection of v onto n.
*/
template <typename T>
Vector2D<T>
Vec2DProjection (const Vector2D<T> &v , const Vector2D<T> &n);

/** 
 * Gets a perpendicular vector to v.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param A 2d vector.
 *
 * @return A perpendicular vector.
 */
template <typename T>
Vector2D<T> 
Vec2DPerpendicular (const Vector2D<T> &v);

/** 
 * Gets a perpendicular vector to v of unit length.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 * 
 * @param A 2d vector
 *
 * @return A perpendicular vector of unit length.
 */
template <typename T>
Vector2D<T> 
Vec2DUnitPerpendicular (const Vector2D<T> &v);

/** 
 * Vector Orthonormalization using the biased 
 * Gram-Schmidt algorithm.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 2d vector.
 *
 */
template <typename T>
void 
Orthonormalize2D (std::vector<Vector2D<T> > &v);

/** 
 * Scalar on the left multiplication, for symmetry.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param k scalar.
 * @param v A 2d vector.
 * 
 * @return A 2d vector.
 */
template <typename T>
Vector2D<T>
operator * (T k, const Vector2D<T> &v);

/** 
 * Magnitude of a vector.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 3d vector.
 * 
 * @return The magnitude of v.
 */
template <typename T> 
T 
Vec3DMagnitude (const Vector3D<T> &v);

/** 
 * Cross product.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 3d vector.
 * @param w Another 3d vector.
 * 
 * @return Cross product result.
 */
template <typename T>
Vector3D<T> 
Vec3DCross (const Vector3D<T> &v, const Vector3D<T> &w);

/** 
 * Distance between two 3d vectors. 
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 3d vector.
 * @param w Another 3d vector.
 * 
 * @return The distance between the vectors v and w.
 */
template <typename T>
T 
Vec3DDistance (const Vector3D<T> &v, const Vector3D<T> &w);

/** 
 * Dot product between two 3d vectors.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 3d vector.
 * @param w Another 3d vector.
 * 
 * @return The result of the dot product between v and w.
 */
template <typename T>
T 
Vec3DDot (const Vector3D<T> &v, const Vector3D<T> &w);

/** 
 * Projection of v onto n.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 3d vector.
 * @param n Another three dimension vector.
 * 
 * @return The projection of v onto n.
 */
template <typename T>
Vector3D<T>
Vec3DProjection (const Vector3D<T> &v , const Vector3D<T> &n);

/** 
 * Vector Orthonormalization using the biased 
 * Gram-Schmidt algorithm.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 3d vector.
 *
 */
template <typename T>
void 
Orthonormalize3D (std::vector<Vector3D<T> > &v);

/** 
 * Scalar on the left multiplication, for symmetry.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param k scalar.
 * @param v A 3d vector.
 * 
 * @return A 3d vector.
 */
template <typename T>
Vector3D<T>
operator * (T k, const Vector3D<T> &v);

/** 
 * Magnitude of a 4d vector.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 4d vector.
 * 
 * @return The magnitude of vector v.
 */
template <typename T> 
T 
Vec4DMagnitude (const Vector4D<T> &v);

/** 
 * Distance between two 4d vectors. 
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 4d vector.
 * @param k Another 4d vector.
 * 
 * @return The distance between the vectors.
 */
template <typename T>
T 
Vec4DDistance (const Vector4D<T> &v, const Vector4D<T> &k);

/** 
 * Dot product between two 4d vectors.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 4d vector.
 * @param w Another 4d vector.
 * 
 * @return The result of the dot product between v and w.
 */
template <typename T>
T 
Vec4DDot (const Vector4D<T> &v, const Vector4D<T> &w);

/** 
 * Projection of v onto n.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 4d vector.
 * @param n Another four dimension vector.
 * 
 * @return The projection of v onto n.
 */
template <typename T>
Vector4D<T>
Vec4DProjection (const Vector4D<T> &v , const Vector4D<T> &n);

/** 
 * Vector Orthonormalization using the biased 
 * Gram-Schmidt algorithm.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v A 4d vector.
 */
template <typename T>
void 
Orthonormalize4D (std::vector<Vector4D<T> > &v);

/** 
 * Scalar on the left multiplication, for symmetry.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param k scalar.
 * @param v A 4d vector.
 * 
 * @return A 4d vector.
 */
template <typename T>
Vector4D<T>
operator * (T k, const Vector4D<T> &v);

// Non-member implementations

template<typename T> 
T 
Vec2DMagnitude (const Vector2D<T> &v)
{
  return std::sqrt (v.x*v.x + v.y*v.y);
}

template<typename T>
T 
Vec2DDistance (const Vector2D<T> &v, const Vector2D<T> &w)
{
  T dx = v.x - w.x;
  T dy = v.y - w.y;
  return std::sqrt (dx*dx + dy*dy);
}

template <typename T>
T 
Vec2DDot (const Vector2D<T> &v, const Vector2D<T> &w)
{
  return v.x*w.x + v.y*w.y;
}

template <typename T>
Vector2D<T>
Vec2DProjection (const Vector2D<T> &v, const Vector2D<T> &n)
{
  T nDotProd = Vec2DDot(n,n);
  if (nDotProd == 0)
    THROW (DivisionByZero,"Vector division by zero.");

  return n * (Vec2DDot(v,n)/nDotProd); 
}

template <typename T>
Vector2D<T> 
Vec2DPerpendicular (const Vector2D<T> &v)
{
  return Vector2D<T> (v.y,-v.x);
}

template <typename T>
Vector2D<T> 
Vec2DUnitPerpendicular (const Vector2D<T> &v)
{
  T vMag = Vec2DMagnitude(v);
  if (vMag == 0)
    THROW (DivisionByZero,"Vector division by zero.");

  return Vec2DPerpendicular(v)/vMag;
}


template <typename T>
void 
Orthonormalize2D (std::vector<Vector2D<T> > &v)
{
  if (v.size() > 2)
    THROW (OutOfRange,"Cannot Orthonormalize more than 2 vectors");

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
operator * (T k, const Vector2D<T> &v)
{
  return Vector2D<T> (k*v.x,k*v.y);
}

template<typename T> 
T 
Vec3DMagnitude (const Vector3D<T> &v)
{
  return std::sqrt (v.x*v.x  + v.y*v.y + v.z*v.z);
}

template<typename T>
Vector3D<T> 
Vec3DCross (const Vector3D<T> &v, const Vector3D<T> &w)
{
  return Vector3D<T> (v.y*w.z - v.z*w.y,
                      v.z*w.x - v.x*w.z,
                      v.x*w.y - v.y*w.x);
}

template<typename T>
T 
Vec3DDistance (const Vector3D<T> &v, const Vector3D<T> &w)
{
  T dx = v.x - w.x;
  T dy = v.y - w.y;
  T dz = v.z - w.z;
  return std::sqrt (dx*dx + dy*dy + dz*dz);
}

template <typename T>
T 
Vec3DDot (const Vector3D<T> &v, const Vector3D<T> &w)
{
  return v.x*w.x + v.y*w.y + v.z*w.z;
}

template <typename T>
Vector3D<T>
Vec3DProjection (const Vector3D<T> &v , const Vector3D<T> &n)
{
  T nDotProd = Vec3DDot(n,n);
  if (nDotProd == 0)
    THROW (DivisionByZero,"Vector division by zero.");

  return n * (Vec3DDot(v,n)/nDotProd);   
}

template <typename T>
void 
Orthonormalize3D (std::vector<Vector3D<T> > &v)
{
  if (v.size() > 3)
    THROW (OutOfRange,"Cannot Orthonormalize more than 3 vectors");

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
operator * (T k, const Vector3D<T> &v)
{
  return Vector3D<T> (k*v.x,k*v.y,k*v.z);
}

template<typename T> 
T 
Vec4DMagnitude (const Vector4D<T> &v)
{
  return std::sqrt (v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

template<typename T>
T 
Vec4DDistance (const Vector4D<T> &v, const Vector4D<T> &k)
{
  T dx = v.x - k.x;
  T dy = v.y - k.y;
  T dz = v.z - k.z;
  T dw = v.w - k.w;
  return std::sqrt (dx*dx + dy*dy + dw*dw);
}

template <typename T>
T 
Vec4DDot (const Vector4D<T> &v, const Vector4D<T> &w)
{
  return v.x*w.x + v.y*w.y + v.z*w.z + v.w*w.w;
}


template <typename T>
Vector4D<T>
Vec4DProjection (const Vector4D<T> &v , const Vector4D<T> &n)
{
  T nDotProd = Vec4DDot(n,n);
  if (nDotProd == 0)
    THROW (DivisionByZero,"Vector division by zero.");

  return n * (Vec4DDot(v,n)/nDotProd); 
}

template <typename T>
void 
Orthonormalize4D (std::vector<Vector4D<T> > &v)
{
  if (v.size() > 4)
    THROW (OutOfRange,"Cannot Orthonormalize more than 4 vectors");

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
operator * (T k, const Vector4D<T> &v)
{
  return Vector4D<T> (k*v.x,k*v.y,k*v.z,k*v.w);
}

}
}
}

#endif
