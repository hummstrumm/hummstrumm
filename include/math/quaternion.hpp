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

/**
 * Defines and implements a quaternion.
 *
 * @file    math/quaternion.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 *
 */

#ifndef HUMMSTRUMM_ENGINE_MATH_QUATERNION_INL
#define HUMMSTRUMM_ENGINE_MATH_QUATERNION_INL

namespace hummstrumm
{
namespace engine
{
namespace math
{

/**
 * A quaternion used in rotational calculations.  Quaternions are an efficient
 * method of representing rotations of points in 4D space, and don't suffer from
 * the "Gimbal Lock" that rotational matrices do.  Mathematically, quaternions
 * are akin to complex numbers, definied by the equation:
 *
 * \f$ a + bi + cj + dk = Q\f$ in which a, b, c, and d are real numbers and \f$
 * i^2 = j^2 = k^2 = ijk = -1\f$
 *
 * Quaternions can also be represented by a 3D vector and a scalar value.
 *
 * @version 0.3
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 * @since   0.2
 */
template <typename T>
class Quaternion
{
  public:
    /// The vector part of the quaternion.
    Vector3D<T> v;
    /// The scalar part of the quaternion.
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
     * @param [in] w The scalar component w.
     * @param [in] vx The x component of vector.
     * @param [in] vy The y component of vector.
     * @param [in] vz The z component of vector.
     */
    Quaternion (const T &w, const T &vx, const T  &vy, const T &vz)
      : w(w), v(vx, vy, vz) {}
 
    /**
     * Construct a quaternion from 3x3 matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m 3x3 Matrice.
     */  
    Quaternion (const Matrix3D<T> &m);
 
    /**
     * Construct a quaternion from a vector and a scalar
     * component.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] w The scalar component w.
     * @param [in] v 3D Vector.
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
     * @param [in] q A quaternion.
     */
    Quaternion (const Quaternion<T> &q): w(q.w), v(q.v) {}

    /**
     * Assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] q A quaternion.
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
     * @param [in] q A quaternion.
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
     * @param [in] q A quaternion.
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
     * @param [in] q A quaternion.
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
     * @param [in] q A quaternion.
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
     * @param [in] q A quaternion.
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
     * @param [in] s A scalar.
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
     * @param [in] s A scalar.
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
     * @param [in] q A quaternion.
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
     * @param [in] q A quaternion.
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
     * @param [in] q A quaternion.
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
     * @param [in] s A scalar.
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
     * @param [in] s A scalar.
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
     * @param [in] angle Angle in radians to rotate about the axis.
     * @param [in] axis Rotation axis (should be normalized).
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

// non-member functions declaration

/**
 * The dot product of two quaternions
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] n A quaternion.
 * @param [in] q Another quatenrion.
 *
 * @return The dot product of n with q.
 *
 * @see Quaternion
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
 * @param [in] s A scalar.
 * @param [in] q A quaternion.
 *
 * @return The quaternion that resulted from s*q.
 *
 * @see Quaternion
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
 * @param [in] q A quaternion.
 *
 * @return The conjugate of q.
 *
 * @see Quaternion
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
 * @param [in] q A quaternion.
 *
 * @return The magnitude q.
 *
 * @see Quaternion
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
 * @param [in] q A quaternion.
 *
 * @return The inverse of q.
 *
 * @see Quaternion
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
 * @param [in] q A quaternion. Should be normalized 
 * before used in here.
 *
 * @return The logarithm of q.
 *
 * @see Quaternion
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
 * @param [in] q A quaternion. 
 *
 * @return The exponential of q.
 *
 * @see Quaternion
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
 * @param [in] q A quaternion.
 * @param [in] e Another quaternion.
 *
 * @return Quaternion q raised to e.
 *
 * @see Quaternion
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
 * @param [in] q A quaternion.
 * @param [in] e Scalar.
 *
 * @return Quaternion q raised to e.
 *
 * @see Quaternion
 */
template <typename T>
Quaternion<T> QuatPow (const Quaternion<T> &q, const T &e);

/**
 * Angular displacement between two quaternions.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] q A quaternion.
 * @param [in] w Another quaternion.
 *
 * @return The angular displacement which rotates from q to w.
 *
 * @see Quaternion
 */
template <typename T>
Quaternion<T>
QuatAngDisp (const Quaternion<T> &q, const Quaternion<T> &w);

/**
 * Spherical Linear Interpolation (Slerp).
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] q A normalized quaternion (starting orientation).
 * @param [in] w Another normalized quaternion (ending orientation).
 * @param [in] t Interpolation parameter
 *
 * @return Orientation that interpolates from q and w.
 *
 * @see Quaternion
 */
template <typename T>
Quaternion<T>
QuatSlerp (const Quaternion<T> &q, const Quaternion<T> &w, const T &t);

/**
 * Quaternion spline, squad (Spherical and quadrangle).
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] q A normalized quaternion (initial control point).
 * @param [in] w Another normalized quaternion (end control point).
 * @param [in] z A normalized quaternion (intermediate control point,  z).
 * @param [in] x Another normalized quaternion (intermediate control point,
 * x=z+1).
 * @param [in] h Interpolation parameter
 *
 * @return A cubic interpolation between q and w by amount h.
 *
 * @see Quaternion
 */
template <typename T>
Quaternion<T>
QuatSquad (const Quaternion<T> &q, const Quaternion<T> &w,
           const Quaternion<T> &z, const Quaternion<T> &x, const T &h);

}
}
}

#endif //HUMMSTRUMM_ENGINE_MATH_QUATERNION_INL
