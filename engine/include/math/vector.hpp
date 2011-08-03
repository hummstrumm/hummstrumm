// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2011, the people listed in the AUTHORS file. 
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
 * @file    math/vector.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 */

#ifndef HUMMSTRUMM_ENGINE_MATH_VECTOR
#define HUMMSTRUMM_ENGINE_MATH_VECTOR

#include <vector>
#include <cmath>
#include <cstring>

namespace hummstrumm
{
namespace engine
{
namespace math
{

/**
 * Represents a two-dimensional vector.  This vector is mapped by rectangular
 * coordinates (x- and y- components), instead of by polar coordinates (r- and
 * theta- components).
 *
 * @version 0.2
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 * @since   0.2
 */
template <typename T>
class Vector2D
{
  public:
    T x, ///< The x-component.
      y; ///< The y-component.

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
     * @param [in] vx X coordinate.
     * @param [in] vy Y coordinate.
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
     * @param [in] v A 2d vector.
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
     * @param [in] v A 2d vector.
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
     * @param [in] v A 2d vector.
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
     * @param [in] v A 2d vector.
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
     * @param [in] v A 2d vector.
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
     * @param [in] v A 2d vector.
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
     * @param [in] s scalar.
     * 
     * @return A 2d vector.
     */
    Vector2D<T> operator * (const T &s) const;

    /** 
     * Division of this vector with a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return A 2d vector.
     */
    Vector2D<T> operator / (const T &s) const;

    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] v A 2d vector.
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
     * @param [in] v A 2d vector.
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
     * @param [in] s scalar.
     * 
     * @return This vector.
     */
    Vector2D<T> &operator *= (const T &s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return This vector.
     */
    Vector2D<T> &operator /= (const T &s);

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

/**
 * Represents a three-dimensional vector.  This vector is mapped by rectangular
 * coordinates (x-, y-, and z- components), instead of by spherical coordinates
 * (radius r-, elevation theta-, and azimuth phi- components).
 *
 * @version 0.2
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 * @since   0.2
 */
template <typename T>
class Vector3D
{
  public:
    T x, ///< The x component.
      y, ///< The y component.
      z; ///< The z component.

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
     * @param [in] vx X coordinate.
     * @param [in] vy Y coordinate.
     * @param [in] vz Z coordinate.
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
     * @param [in] v A 3d vector.
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
     * @param [in] v A 3d vector.
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
     * @param [in] v A 3d vector.
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
     * @param [in] v A 3d vector.
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
     * @param [in] v A 3d vector.
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
     * @param [in] v A 3d vector.
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
     * @param [in] s scalar.
     * 
     * @return A 3d vector.
     */
    Vector3D<T> operator * (const T &s) const;

    /** 
     * Division of this vector by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return A 3d vector.
     */
    Vector3D<T> operator / (const T &s) const;

    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] v A 3d vector.
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
     * @param [in] v A 3d vector.
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
     * @param [in] s scalar.
     * 
     * @return This vector.
     */
    Vector3D<T> &operator *= (const T &s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return This vector.
     */
    Vector3D<T> &operator /= (const T &s);

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

/**
 * Represents a four-dimensional vector.  This vector is mapped by rectangular
 * coordinates (x-, y-, z-, and w- components), instead of by hyperspherical
 * coordinates (radius r- and angular phi<sub>1</sub>-, phi<sub>2</sub>-, and
 * phi<sub>3</sub>- components).
 *
 * @version 0.2
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 * @since   0.2
 */
template <typename T>
class Vector4D
{
  public:
    T x, ///< The x component.
      y, ///< The y component.
      z, ///< The z component.
      w; ///< The w component.

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
     * @param [in] vx X coordinate.
     * @param [in] vy Y coordinate.
     * @param [in] vz Z coordinate.
     * @param [in] vw W coordinate.
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
     * @param [in] v A 4d vector.
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
     * @param [in] v A 3d vector.
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
     * @param [in] v A 4d vector.
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
     * @param [in] v A 4d vector.
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
     * @param [in] v A 4d vector.
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
     * @param [in] v A 4d vector.
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
     * @param [in] s scalar.
     * 
     * @return A 4d vector.
     */
    Vector4D<T> operator * (const T &s) const;
    /** 
     * Division of a Vector4D object by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return A 4d vector.
     *
     */
    Vector4D<T> operator / (const T &s) const;
    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] v A 4d vector.
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
     * @param [in] v A 4d vector.
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
     * @param [in] s scalar.
     * 
     * @return This vector.
     */
    Vector4D<T> &operator *= (const T &s);
    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return This vector.
     */
    Vector4D<T> &operator /= (const T &s);

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

#ifdef HUMMSTRUMM_HAVE_SSE_SUPPORT
/**
 * Template specialization of Vector4D for float with SSE optimization.
 *
 * @version 0.3
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-08-28
 * @since   0.3
 *
 * @see Vector4D
 */
template<>
class Vector4D<float>
{
  public:
    HUMMSTRUMM_ALIGN_16_WINDOWS union HUMMSTRUMM_ALIGN_16_UNIX {
        /// Aligned register for SIMD
        __m128 xyzw;
        struct { float x, ///< The x component.
                       y, ///< The y component.
                       z, ///< The z component.
                       w; ///< The w component.
        };
        /// As an array of floats.
        float f[4];
    };

    /**
     * Constructs a null Vector4D object.
     *
     * @author  Ricardo Tiago <Rtiago@gmail.com>
     * @date    2010-08-28
     * @since   0.3 
     */ 
    Vector4D () 
    {
      SIMD_SET_ZERO(xyzw);
    }
    /**
     * Constructs a Vector4D object from a SSE register variable.
     *
     * @author  Ricardo Tiago <Rtiago@gmail.com>
     * @date    2010-08-28
     * @since   0.3
     *
     * @param [in] r An SSE register.
     */
    Vector4D (__m128 &r): xyzw(r) { }
    /**
     * Constructs a Vector4D object from four floating point values.
     *
     * @author  Ricardo Tiago <Rtiago@gmail.com>
     * @date    2010-08-28
     * @since   0.3
     *
     * @param [in] vx The x component.
     * @param [in] vy The y component.
     * @param [in] vz The z component.
     * @param [in] vw The w component.
     */
    Vector4D (const float &vx,
              const float &vy,
              const float &vz,
              const float &vw)
    {
      SIMD_SET_PS(vw,vz,vy,vx, xyzw);
    }
    /**
     * Constructs a Vector4D object from an array of values.
     *
     * @author  Ricardo Tiago <Rtiago@gmail.com>
     * @date    2010-08-28
     * @since   0.3
     *
     * @param [in] v An array of floating point values.
     */
    Vector4D (const Vector4D<float>  &v)
             : xyzw(v.xyzw) {}
    /**
     * Destructs a Vector4D object.
     *
     * @author  Ricardo Tiago <Rtiago@gmail.com>
     * @date    2010-08-28
     * @since   0.3
     */
    virtual ~Vector4D () {}

    /** 
     * Assignment operator. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     *
     * @param [in] v A 3d vector.
     *
     * @return This vector.
     */ 
    Vector4D<float> &operator = (const Vector4D<float> &v);
    /** 
     * Equality operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     *
     * @param [in] v A 4d vector.
     * 
     * @return Whether the vectors are equal.
     */
    bool operator == (const Vector4D<float> &v) const;
    /** 
     * Inequality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     *
     * @param [in] v A 4d vector.
     * 
     * @return Whether the vectors are different.
     */
    bool operator != (const Vector4D<float> &v) const;
    /** 
     * Unary minus. Negate this vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     *
     * @return A 4d vector.
     */
    Vector4D<float> operator - () const;
    /** 
     * Sum this vector with another 4d vector. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     *
     * @param [in] v A 4d vector.
     * 
     * @return A 4d vector.
     */
    Vector4D<float> operator + (const Vector4D<float> &v) const;
    /** 
     * Subtract this vector with another 4d vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     *
     * @param [in] v A 4d vector.
     * 
     * @return A 4d vector.
     */
    Vector4D<float> operator - (const Vector4D<float> &v) const;
    /** 
     * Multiplication of scalar with this vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     *
     * @param [in] s scalar.
     * 
     * @return A 4d vector.
     */
    Vector4D<float> operator * (const float &s) const;
    /** 
     * Division of a Vector4D object by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     *
     * @param [in] s scalar.
     * 
     * @return A 4d vector.
     *
     */
    Vector4D<float> operator / (const float &s) const;
    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     *
     * @param [in] v A 4d vector.
     * 
     * @return This vector.
     */
    Vector4D<float> &operator += (const Vector4D<float> &v);
    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     *
     * @param [in] v A 4d vector.
     * 
     * @return This vector.
     */
    Vector4D<float> &operator -= (const Vector4D<float> &v);
    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     *
     * @param [in] s scalar.
     * 
     * @return This vector.
     */
    Vector4D<float> &operator *= (const float &s);
    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     *
     * @param [in] s scalar.
     * 
     * @return This vector.
     */
    Vector4D<float> &operator /= (const float &s);

    /** 
     * Normalize this vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     */
    void Normalize ();
    /** 
     * Set this vector to zero.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-08-28
     * @since 0.3
     */
    void Zero ();


  private:
  protected:
};
#endif    


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
Vector2D<T>::operator * (const T &s) const
{
  return Vector2D<T> (x*s,y*s);
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator / (const T &s) const
{
  if (s == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Vector division by zero.");

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
Vector2D<T>::operator *= (const T &s)
{
  x *= s; y *= s;
  return *this;
}

template <typename T>
Vector2D<T> &
Vector2D<T>::operator /= (const T &s)
{
  if (s == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Vector division by zero.");

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
    HUMMSTRUMM_THROW (DivisionByZero,"Vector magnitude is zero.");

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
Vector3D<T>::operator * (const T &s) const
{
  return Vector3D<T> (x*s,y*s,z*s);
}

template <typename T>
Vector3D<T> 
Vector3D<T>::operator / (const T &s) const
{
  if (s == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Vector division by zero.");

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
Vector3D<T>::operator *= (const T &s)
{
  x *= s; y *= s; z *=s;
  return *this;
}

template <typename T>
Vector3D<T> &
Vector3D<T>::operator /= (const T &s)
{
  if (s == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Vector division by zero.");

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
    HUMMSTRUMM_THROW (DivisionByZero,"Vector magnitude is zero.");

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
Vector4D<T>::operator * (const T &s) const
{
  return Vector4D<T> (x*s,y*s,z*s,w*s);
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator / (const T &s) const
{
  if (s == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Vector division by zero.");

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
Vector4D<T>::operator *= (const T &s)
{
  x *= s; y *= s; z *=s; w *=s;
  return *this;
}

template <typename T>
Vector4D<T> &
Vector4D<T>::operator /= (const T &s)
{
  if (s == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Vector division by zero.");

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
    HUMMSTRUMM_THROW (DivisionByZero,"Vector magnitude is zero.");

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
 * @param [in] v A 2d vector.
 * 
 * @return The magnitude of vector v.
 *
 * @see Vector2D 
 */
template <typename T> 
T 
Vec2DMagnitude (const Vector2D<T> &v);

/** 
 * Squared magnitude of a vector.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 2d vector.
 * 
 * @return The squared magnitude of vector v.
 *
 * @see Vector2D 
 */
template <typename T> 
T 
Vec2DSqMagnitude (const Vector2D<T> &v);

/** 
 * Distance between two vectors. 
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 2d vector.
 * @param [in] w Another 2d vector.
 * 
 * @return The distance between the vectors.
 *
 * @see Vector2D 
 */
template <typename T>
T 
Vec2DDistance (const Vector2D<T> &v, const Vector2D<T> &w);

/** 
 * Squared distance between two vectors. 
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 2d vector.
 * @param [in] w Another 2d vector.
 * 
 * @return The squared distance between the vectors.
 *
 * @see Vector2D 
 */
template <typename T>
T 
Vec2DSqDistance (const Vector2D<T> &v, const Vector2D<T> &w);

/** 
 * Dot product between two 2d vectors.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 2d vector.
 * @param [in] w Another 2d vector.
 * 
 * @return The result of the dot product between v and w.
 *
 * @see Vector2D 
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
 * @param [in] v A 2d vector.
 * @param [in] n Another 2d vector.
 * 
 * @return The projection of v onto n.
 *
 * @see Vector2D 
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
 * @param [in] v A 2d vector.
 *
 * @return A perpendicular vector.
 *
 * @see Vector2D 
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
 * @param [in] v A 2d vector
 *
 * @return A perpendicular vector of unit length.
 *
 * @see Vector2D 
 */
template <typename T>
Vector2D<T> 
Vec2DUnitPerpendicular (const Vector2D<T> &v);

// add star here when this is uncommented
/*
 * Vector Orthonormalization using the biased 
 * Gram-Schmidt algorithm.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 2d vector.
 *
 * @see Vector2D  
 */
/*
template <typename T>
void 
Orthonormalize2D (std::vector<Vector2D<T> > &v);
*/

/** 
 * Scalar on the left multiplication, for symmetry.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] k scalar.
 * @param [in] v A 2d vector.
 * 
 * @return A 2d vector.
 * 
 * @see Vector2D 
 */
template <typename T>
Vector2D<T>
operator * (const T &k, const Vector2D<T> &v);

/** 
 * Magnitude of a vector.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 3d vector.
 * 
 * @return The magnitude of v.
 *
 * @see Vector3D 
 */
template <typename T> 
T 
Vec3DMagnitude (const Vector3D<T> &v);

/** 
 * Squared Magnitude of a vector.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 3d vector.
 * 
 * @return The squared magnitude of v.
 *
 * @see Vector3D 
 */
template <typename T> 
T 
Vec3DSqMagnitude (const Vector3D<T> &v);

/** 
 * Cross product.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 3d vector.
 * @param [in] w Another 3d vector.
 * 
 * @return Cross product result.
 *
 * @see Vector3D 
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
 * @param [in] v A 3d vector.
 * @param [in] w Another 3d vector.
 * 
 * @return The distance between the vectors v and w.
 *
 * @see Vector3D 
 */
template <typename T>
T 
Vec3DDistance (const Vector3D<T> &v, const Vector3D<T> &w);

/** 
 * Squared distance between two 3d vectors. 
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 3d vector.
 * @param [in] w Another 3d vector.
 * 
 * @return The squared distance between the vectors v and w.
 *
 * @see Vector3D 
 */
template <typename T>
T 
Vec3DSqDistance (const Vector3D<T> &v, const Vector3D<T> &w);

/** 
 * Dot product between two 3d vectors.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 3d vector.
 * @param [in] w Another 3d vector.
 * 
 * @return The result of the dot product between v and w.
 *
 * @see Vector3D 
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
 * @param [in] v A 3d vector.
 * @param [in] n Another three dimension vector.
 * 
 * @return The projection of v onto n.
 *
 * @see Vector3D 
 */
template <typename T>
Vector3D<T>
Vec3DProjection (const Vector3D<T> &v , const Vector3D<T> &n);

// Add star here when uncommented and implemented.
/*
 * Vector Orthonormalization using the biased 
 * Gram-Schmidt algorithm.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 3d vector.
 *
 * @see Vector3D 
*/
/*
template <typename T>
void 
Orthonormalize3D (std::vector<Vector3D<T> > &v);
 */

/** 
 * Scalar on the left multiplication, for symmetry.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] k scalar.
 * @param [in] v A 3d vector.
 * 
 * @return A 3d vector.
 *
 * @see Vector3D 
 */
template <typename T>
Vector3D<T>
operator * (const T &k, const Vector3D<T> &v);

/** 
 * Magnitude of a 4d vector.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 4d vector.
 * 
 * @return The magnitude of vector v.
 *
 * @see Vector4D 
 */
template <typename T> 
T 
Vec4DMagnitude (const Vector4D<T> &v);

#ifdef HUMMSTRUMM_HAVE_SSE_SUPPORT
template <> 
float 
Vec4DMagnitude (const Vector4D<float> &v);
#endif

/** 
 * Squared magnitude of a 4d vector.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 4d vector.
 * 
 * @return The squared magnitude of vector v.
 *
 * @see Vector4D 
 */
template <typename T> 
T 
Vec4DSqMagnitude (const Vector4D<T> &v);


/** 
 * Distance between two 4d vectors. 
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 4d vector.
 * @param [in] k Another 4d vector.
 * 
 * @return The distance between the vectors.
 *
 * @see Vector4D  
*/
template <typename T>
T 
Vec4DDistance (const Vector4D<T> &v, const Vector4D<T> &k);

/** 
 * Squared distance between two 4d vectors. 
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 4d vector.
 * @param [in] k Another 4d vector.
 * 
 * @return The squared distance between the vectors.
 *
 * @see Vector4D 
 */
template <typename T>
T 
Vec4DSqDistance (const Vector4D<T> &v, const Vector4D<T> &k);

/** 
 * Dot product between two 4d vectors.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 4d vector.
 * @param [in] w Another 4d vector.
 * 
 * @return The result of the dot product between v and w.
 *
 * @see Vector4D 
 */
template <typename T>
T 
Vec4DDot (const Vector4D<T> &v, const Vector4D<T> &w);

#ifdef HUMMSTRUMM_HAVE_SSE_SUPPORT
template <>
float 
Vec4DDot (const Vector4D<float> &v, const Vector4D<float> &w);
#endif

/** 
 * Projection of v onto n.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 4d vector.
 * @param [in] n Another four dimension vector.
 * 
 * @return The projection of v onto n.
 *
 * @see Vector4D 
 */
template <typename T>
Vector4D<T>
Vec4DProjection (const Vector4D<T> &v , const Vector4D<T> &n);

// Add star when this is uncommented and implemented
/*
 * Vector Orthonormalization using the biased 
 * Gram-Schmidt algorithm.
 * 
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] v A 4d vector.
 */
/*
template <typename T>
void 
Orthonormalize4D (std::vector<Vector4D<T> > &v);
 */

/** 
 * Scalar on the left multiplication, for symmetry.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] k scalar.
 * @param [in] v A 4d vector.
 * 
 * @return A 4d vector.
 *
 * @see Vector4D 
 */
template <typename T>
Vector4D<T>
operator * (const T &k, const Vector4D<T> &v);

// Non-member implementations

template <typename T> 
T 
Vec2DMagnitude (const Vector2D<T> &v)
{
  return std::sqrt (v.x*v.x + v.y*v.y);
}

template <typename T> 
T 
Vec2DSqMagnitude (const Vector2D<T> &v)
{
  return v.x*v.x + v.y*v.y;
}

template<typename T>
T 
Vec2DDistance (const Vector2D<T> &v, const Vector2D<T> &w)
{
  T dx = v.x - w.x;
  T dy = v.y - w.y;
  return std::sqrt (dx*dx + dy*dy);
}

template<typename T>
T 
Vec2DSqDistance (const Vector2D<T> &v, const Vector2D<T> &w)
{
  T dx = v.x - w.x;
  T dy = v.y - w.y;
  return dx*dx + dy*dy;
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
    HUMMSTRUMM_THROW (DivisionByZero,"Vector division by zero.");

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
    HUMMSTRUMM_THROW (DivisionByZero,"Vector division by zero.");

  return Vec2DPerpendicular(v)/vMag;
}

/*
template <typename T>
void 
Orthonormalize2D (std::vector<Vector2D<T> > &v)
{
  if (v.size() > 2)
    HUMMSTRUMM_THROW (OutOfRange,"Cannot Orthonormalize more than 2 vectors");

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
*/

template <typename T>
Vector2D<T>
operator * (const T &k, const Vector2D<T> &v)
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
T 
Vec3DSqMagnitude (const Vector3D<T> &v)
{
  return v.x*v.x  + v.y*v.y + v.z*v.z;
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

template<typename T>
T 
Vec3DSqDistance (const Vector3D<T> &v, const Vector3D<T> &w)
{
  T dx = v.x - w.x;
  T dy = v.y - w.y;
  T dz = v.z - w.z;
  return dx*dx + dy*dy + dz*dz;
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
    HUMMSTRUMM_THROW (DivisionByZero,"Vector division by zero.");

  return n * (Vec3DDot(v,n)/nDotProd);   
}

/*
template <typename T>
void 
Orthonormalize3D (std::vector<Vector3D<T> > &v)
{
  if (v.size() > 3)
    HUMMSTRUMM_THROW (OutOfRange,"Cannot Orthonormalize more than 3 vectors");

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
*/

template <typename T>
Vector3D<T>
operator * (const T &k, const Vector3D<T> &v)
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
Vec4DSqMagnitude (const Vector4D<T> &v)
{
  return v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w;
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

template<typename T>
T 
Vec4DSqDistance (const Vector4D<T> &v, const Vector4D<T> &k)
{
  T dx = v.x - k.x;
  T dy = v.y - k.y;
  T dz = v.z - k.z;
  T dw = v.w - k.w;
  return dx*dx + dy*dy + dw*dw;
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
    HUMMSTRUMM_THROW (DivisionByZero,"Vector division by zero.");

  return n * (Vec4DDot(v,n)/nDotProd); 
}
/*
template <typename T>
void 
Orthonormalize4D (std::vector<Vector4D<T> > &v)
{
  if (v.size() > 4)
    HUMMSTRUMM_THROW (OutOfRange,"Cannot Orthonormalize more than 4 vectors");

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
*/

template <typename T>
Vector4D<T>
operator * (const T &k, const Vector4D<T> &v)
{
  return Vector4D<T> (k*v.x,k*v.y,k*v.z,k*v.w);
}

}
}
}

#endif
