// -*- c++ -*-
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

/** 
 * Defines and implements classes for square matrices.
 *
 * @file    math/matrice.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 * @see     Matrix2D
 * @see     Matrix3D
 * @see     Matrix4D
 *
 * @note This code uses column vectors.
 */

#ifndef HUMMSTRUMM_ENGINE_MATH_MATRICE
#define HUMMSTRUMM_ENGINE_MATH_MATRICE


namespace hummstrumm
{
namespace engine
{
namespace math
{


/**
 * A class representing a two-dimensional matrix.  This class is capable of
 * doing all standard matrix transforms and operations.
 *
 * @version 0.3
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 * @since   0.2
 */
template <typename T>
class Matrix2D
{

  public:
    /// The two columns, represented as vectors.
    Vector2D<T> mat2[2];

    /**
     * Constructs a null 2x2 matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    Matrix2D () {}

    /** 
     * Construct a 2x2 matrice from two vectors.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param [in] v1 First row of matrix
     * @param [in] v2 Second row of matrix.
     *
     */
    Matrix2D (const Vector2D<T> &v1, const Vector2D<T> &v2)
    {
      mat2[0] = v1;
      mat2[1] = v2;
    }

    /** 
     * Construct a 2x2 matrice from coordinates.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param [in] x1 First row X coordinate.
     * @param [in] y1 First row Y coordinate.
     * @param [in] x2 Second row X coordinate
     * @param [in] y2 Second row Y coordinate
     *
     */
    Matrix2D (const T &x1, const T &y1, const T &x2, const T &y2)
    {
      mat2[0].coord.x = x1;
      mat2[0].coord.y = y1;
      mat2[1].coord.x = x2;
      mat2[1].coord.y = y2;
    }

    /** 
     * Copy constructor. Constructs a 2x2 matrice from another 2x2
     * matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param [in] m A 2x2 matrice.
     *
     */ 
    Matrix2D (const Matrix2D<T>  &m)
    {
      mat2[0] = m[0];
      mat2[1] = m[1];
    }

    /** 
     * Destructor. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    ~Matrix2D () {}

    /** 
     * Assignment operator. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 2x2 matrice.
     *
     * @return This matrice.
     */ 
    Matrix2D<T> &operator = (const Matrix2D<T> &m);

    /** 
     * Equality operator. Check if two matrices are equal.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 2x2 matrice.
     * 
     * @return Whether the matrices are equal.
     */
    bool operator == (const Matrix2D<T> &m) const;

    /** 
     * Inequality operator. Check if two matrices are different.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 2x2 matrice.
     * 
     * @return Whether the matrices are different.
     */
    bool operator != (const Matrix2D<T> &m) const;

    /** 
     * Unary minus. Negate a 2x2 matrice. This is the same as
     * multiplying by -1.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return Negated matrice.
     */
    Matrix2D<T> operator - () const;

    /** 
     * Sum two 2x2 matrices.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 2x2 matrice.
     * 
     * @return A 2x2 matrice containing the sum of the two matrices.
     */
    Matrix2D<T> operator + (const Matrix2D<T> &m) const;

    /** 
     * Subtract two 2x2 matrices.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 2x2 matrice.
     * 
     * @return A 2x2 matrice containing the substraction of the two
     * matrices.
     */
    Matrix2D<T> operator - (const Matrix2D<T> &m) const;

    /** 
     * Multiplication of a 2x2 matrice by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return A 2x2 matrice containing the multiplication of the
     * scalar with the matrice.
     */
    Matrix2D<T> operator * (const T &s) const;

    /** 
     * Multiply this matrice with another 2x2 matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 2x2 matrice.
     *
     * @return The multiplication of this matrice with m.
     */
     Matrix2D<T> operator * (const Matrix2D<T> &m) const;

    /** 
     * Multiply this matrice with a vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] v A 2d vector.
     *
     * @return The multiplication of this matrice with v.
     */
     Vector2D<T> operator * (const Vector2D<T> &v) const;

    /** 
     * Division of a 2x2 matrice by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return A 2x2 matrice containing the division of the scalar
     * with the matrice.
     *
     */
    Matrix2D<T> operator / (const T &s) const;

    /** 
     * Return line from the matrix.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] r line to get.
     * 
     * @return Line of the matrice.
     *
     */
    Vector2D<T> operator [] (const unsigned short r) const;

    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 2x2 matrice.
     * 
     * @return This matrice added with m.
     */
    Matrix2D<T> &operator += (const Matrix2D<T> &m);

    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 2x2 matrice.
     * 
     * @return This matrice subtracted by m.
     */
    Matrix2D<T> &operator -= (const Matrix2D<T> &m);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 2x2 matrix.
     *
     * @return This matrice multiplied by m.
     */
    Matrix2D<T> &operator *= (const Matrix2D<T> &m);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     *
     * @return This matrice multiplied by s.
     */
    Matrix2D<T> &operator *= (const T &s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return This matrice divided by s.
     *
     */
    Matrix2D<T> &operator /= (const T &s);

    /** 
     * Set this matrix to the identity matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     */
    void Identity ();

    /** 
     * Calculate the determinant of this matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return The determinant of this.
     */
    T Determinant () const;

  private:

  protected:

};


/**
 * A class representing a three-dimensional matrix.  This class is capable of
 * doing all standard matrix transforms and operations.
 *
 * @version 0.3
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 * @since   0.2
 */
template <typename T>
class Matrix3D
{

  public:
    /// The three columns, represented as vectors.
    Vector3D<T> mat3[3];

    /**
     * Constructs a null 3x3 matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    Matrix3D () {}

    /** 
     * Construct a 3x3 matrice from three vectors.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param [in] v1 First row of matrix
     * @param [in] v2 Second row of matrix.
     * @param [in] v3 Third row of matrix.
     *
     */
    Matrix3D (const Vector3D<T> &v1, 
              const Vector3D<T> &v2,
              const Vector3D<T> &v3)
    {
      mat3[0] = v1;
      mat3[1] = v2;
      mat3[2] = v3;
    }

    /** 
     * Construct a 3x3 matrice from coordinates.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param [in] x1 First row X coordinate.
     * @param [in] y1 First row Y coordinate.
     * @param [in] z1 First row Z coordinate.
     * @param [in] x2 Second row X coordinate
     * @param [in] y2 Second row Y coordinate
     * @param [in] z2 Second row Z coordinate
     * @param [in] x3 Third row X coordinate
     * @param [in] y3 Third row Y coordinate
     * @param [in] z3 Third row Z coordinate
     *
     */
    Matrix3D (const T &x1, const T &y1, const T &z1,
              const T &x2, const T &y2, const T &z2,
              const T &x3, const T &y3, const T &z3)
    {
      mat3[0].coord.x = x1;
      mat3[0].coord.y = y1;
      mat3[0].coord.z = z1;

      mat3[1].coord.x = x2;
      mat3[1].coord.y = y2;
      mat3[1].coord.z = z2;

      mat3[2].coord.x = x3;
      mat3[2].coord.y = y3;
      mat3[2].coord.z = z3;
    }

    /** 
     * Construct a 3x3 matrice from a quaternion
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param [in] q Quaternion
     *
     */

    Matrix3D (const Quaternion<T> &q)
    {
      mat3[0].coord.x = 1 - 2*q.v.coord.y*q.v.coord.y - 2*q.v.coord.z*q.v.coord.z;
      mat3[0].coord.y = 2*q.v.coord.x*q.v.coord.y + 2*q.coord.w*q.v.coord.z;
      mat3[0].coord.z = 2*q.v.coord.x*q.v.coord.z - 2*q.coord.w*q.v.coord.y;

      mat3[1].coord.x = 2*q.v.coord.x*q.v.coord.y - 2*q.coord.w*q.v.coord.z;
      mat3[1].coord.y = 1 - 2*q.v.coord.x*q.v.coord.x - 2*q.v.coord.z*q.v.coord.z;
      mat3[1].coord.z = 2*q.v.coord.y*q.v.coord.z + 2*q.coord.w*q.v.coord.x;

      mat3[2].coord.x = 2*q.v.coord.x*q.v.coord.z + 2*q.coord.w*q.v.coord.y;
      mat3[2].coord.y = 2*q.v.coord.y*q.v.coord.z - 2*q.coord.w*q.v.coord.x;
      mat3[2].coord.z = 1 - 2*q.v.coord.x*q.v.coord.x - 2*q.v.coord.y*q.v.coord.y;
    }

    /** 
     * Copy constructor. Constructs a 3x3 matrice from another 3x3
     * matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param [in] m A 3x3 matrice.
     *
     */ 
    Matrix3D (const Matrix3D<T>  &m)
    {
      mat3[0] = m[0];
      mat3[1] = m[1];
      mat3[2] = m[2];
    }

    /** 
     * Destructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    ~Matrix3D () {}

    /** 
     * Assignment operator. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 3x3 matrice.
     *
     * @return This matrice.
     */ 
    Matrix3D<T> &operator = (const Matrix3D<T> &m);

    /** 
     * Equality operator. Check if two matrices are equal.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 3x3 matrice.
     * 
     * @return Whether the matrices are equal.
     */
    bool operator == (const Matrix3D<T> &m) const;

    /** 
     * Inequality operator. Check if two matrices are different.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 3x3 matrice.
     * 
     * @return Whether the matrices are different.
     */
    bool operator != (const Matrix3D<T> &m) const;

    /** 
     * Unary minus. Negate a 2x2 matrice. This is the same as
     * multiplying by -1.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return Negated matrice.
     */
    Matrix3D<T> operator - () const;

    /** 
     * Sum two 3x3 matrices.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 3x3 matrice.
     * 
     * @return A 3x3 matrice containing the sum of the two matrices.
     */
    Matrix3D<T> operator + (const Matrix3D<T> &m) const;

    /** 
     * Subtract two 3x3 matrices.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 3x3 matrice.
     * 
     * @return A 3x3 matrice containing the substraction of the two
     * matrices.
     */
    Matrix3D<T> operator - (const Matrix3D<T> &m) const;

    /** 
     * Multiplication of a 3x3 matrice by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return A 3x3 matrice containing the multiplication of the
     * scalar with the matrice.
     */
    Matrix3D<T> operator * (const T &s) const;

    /** 
     * Multiply this matrice with another 3x3 matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 3x3 matrice.
     *
     * @return A 3x3 matrice containing the multiplication of this 
     * matrice with m.
     */
    Matrix3D<T> operator * (const Matrix3D<T> &m) const;

    /** 
     * Multiply this matrice with a vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] v A 3d vector.
     *
     * @return A 3x3 matrice containing the multiplication of 
     * this matrice with v.
     */
     Vector3D<T> operator * (const Vector3D<T> &v) const;

    /** 
     * Division of a 3x3 matrice by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return A 3x3 matrice containing the division of the s
     * with this matrice.
     *
     */
    Matrix3D<T> operator / (const T &s) const;

    /** 
     * Return line from the matrix.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] r line to get.
     * 
     * @return This matrice line r.
     *
     */
    Vector3D<T> operator [] (const unsigned short r) const;

    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 3x3 matrice.
     * 
     * @return This matrice containing the sum of this with m.
     */
    Matrix3D<T> &operator += (const Matrix3D<T> &m);

    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 3x3 matrice.
     * 
     * @return This matrice subtracted by m.
     */
    Matrix3D<T> &operator -= (const Matrix3D<T> &m);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     *
     * @return This matrice multiplied by s.
     */
    Matrix3D<T> &operator *= (const T &s);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 3x3 matrice.
     *
     * @return This matrice multiplied by m.
     */
    Matrix3D<T> &operator *= (const Matrix3D<T> &m);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return This matrice divided s.
     *
     */
    Matrix3D<T> &operator /= (const T &s);

    /** 
     * Set this matrix to the identity matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     */
    void Identity ();

    /** 
     * Calculate the determinant of this matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return This matrice determinant.
     */
    T Determinant () const;

  private:

  protected:

};


/**
 * A class representing a four-dimensional matrix.  This class is capable of
 * doing all standard matrix transforms and operations.
 *
 * @version 0.3
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 * @since   0.2
 */
template <typename T>
class Matrix4D
{

  public:
    /// The three columns, represented as vectors.
    Vector4D<T> mat4[4];

    /**
     * Constructs a null 4x4 matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    Matrix4D () {}

    /** 
     * Construct a 4x4 matrice from three vectors.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param [in] v1 First row of matrix
     * @param [in] v2 Second row of matrix.
     * @param [in] v3 Third row of matrix.
     * @param [in] v4 Fourth row of matrix.
     *
     */
    Matrix4D (const Vector4D<T> &v1, 
              const Vector4D<T> &v2,
              const Vector4D<T> &v3,
              const Vector4D<T> &v4)
    {
      mat4[0] = v1;
      mat4[1] = v2;
      mat4[2] = v3;
      mat4[3] = v4;
    }

    /** 
     * Construct a 4x4 matrice from coordinates.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param [in] x1 First row X coordinate.
     * @param [in] y1 First row Y coordinate.
     * @param [in] z1 First row Z coordinate.
     * @param [in] w1 First row W coordinate.
     * @param [in] x2 Second row X coordinate.
     * @param [in] y2 Second row Y coordinate.
     * @param [in] z2 Second row Z coordinate.
     * @param [in] w2 Second row W coordinate.
     * @param [in] x3 Third row X coordinate.
     * @param [in] y3 Third row Y coordinate.
     * @param [in] z3 Third row Z coordinate.
     * @param [in] w3 Third row W coordinate.
     * @param [in] x4 Fourth row X coordinate.
     * @param [in] y4 Fourth row Y coordinate.
     * @param [in] z4 Fourth row Z coordinate.
     * @param [in] w4 Fourth row W coordinate.
     *
     */
    Matrix4D (const T &x1, const T &y1, const T &z1, const T &w1, 
              const T &x2, const T &y2, const T &z2, const T &w2,
              const T &x3, const T &y3, const T &z3, const T &w3,
              const T &x4, const T &y4, const T &z4, const T &w4)
    {
      mat4[0].coord.x = x1;
      mat4[0].coord.y = y1;
      mat4[0].coord.z = z1;
      mat4[0].coord.w = w1;

      mat4[1].coord.x = x2;
      mat4[1].coord.y = y2;
      mat4[1].coord.z = z2;
      mat4[1].coord.w = w2;

      mat4[2].coord.x = x3;
      mat4[2].coord.y = y3;
      mat4[2].coord.z = z3;
      mat4[2].coord.w = w3;

      mat4[3].coord.x = x4;
      mat4[3].coord.y = y4;
      mat4[3].coord.z = z4;
      mat4[3].coord.w = w4;
    }

    /** 
     * Copy constructor. Constructs a 4x4 matrice from another 4x4
     * matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param [in] m A 4x4 matrice.
     *
     */ 
    Matrix4D (const Matrix4D<T>  &m)
    {
      mat4[0] = m[0];
      mat4[1] = m[1];
      mat4[2] = m[2];
      mat4[3] = m[3];
    }

    /** 
     * Destructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    ~Matrix4D () {}

    /** 
     * Assignment operator. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 4x4 matrice.
     *
     * @return This matrice.
     */ 
    Matrix4D<T> &operator = (const Matrix4D<T> &m);

    /** 
     * Equality operator. Check if two matrices are equal.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 4x4 matrice.
     * 
     * @return Whether the matrices are equal.
     */
    bool operator == (const Matrix4D<T> &m) const;

    /** 
     * Inequality operator. Check if two matrices are different.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 4x4 matrice.
     * 
     * @return Whether the matrices are different.
     */
    bool operator != (const Matrix4D<T> &m) const;

    /** 
     * Unary minus. Negate a 2x2 matrice. This is the same as
     * multiplying by -1.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return Negated matrice.
     */
    Matrix4D<T> operator - () const;

    /** 
     * Sum two 4x4 matrices.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 4x4 matrice.
     * 
     * @return A 4x4 matrice containing the sum of this with m.
     */
    Matrix4D<T> operator + (const Matrix4D<T> &m) const;

    /** 
     * Subtract two 4x4 matrices.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 4x4 matrice.
     * 
     * @return A 4x4 matrice containing the substraction of this with m.
     */
    Matrix4D<T> operator - (const Matrix4D<T> &m) const;

    /** 
     * Multiplication of a 4x4 matrice by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return A 4x4 matrice containing the multiplication of this with s.
     */
    Matrix4D<T> operator * (const T &s) const;

    /** 
     * Multiply this matrice with another 4x4 matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 4x4 matrice.
     *
     * @return The multiplication of this matrice with m.
     */
     Matrix4D<T> operator * (const Matrix4D<T> &m) const;

    /** 
     * Multiply this matrice with a vector.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] v A 4d vector.
     *
     * @return The multiplication of this matrice with v.
     */
     Vector4D<T> operator * (const Vector4D<T> &v) const;

    /** 
     * Division of a 4x4 matrice by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return A 4x4 matrice containing the division this with s..
     *
     */
    Matrix4D<T> operator / (const T &s) const;

    /** 
     * Return line from the matrix.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] r line to get.
     * 
     * @return matrice line.
     *
     */
    Vector4D<T> operator [] (const unsigned short r) const;

    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 4x4 matrice.
     * 
     * @return This matrice added with m.
     */
    Matrix4D<T> &operator += (const Matrix4D<T> &m);

    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 4x4 matrice.
     * 
     * @return This matrice subtracted with m.
     */
    Matrix4D<T> &operator -= (const Matrix4D<T> &m);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] m A 4x4 matrix.
     *
     * @return This matrix multiplied by m.
     */
    Matrix4D<T> &operator *= (const Matrix4D<T> &m);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     *
     * @return This matrice multiplied by s.
     */
    Matrix4D<T> &operator *= (const T &s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param [in] s scalar.
     * 
     * @return This matrice divided by s.
     *
     */
    Matrix4D<T> &operator /= (const T &s);

    /** 
     * Set this matrix to the identity matrix.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     */
    void Identity ();

    /** 
     * Calculate the determinant of this matrix.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return The determinant.
     */
    T Determinant () const;

  private:

  protected:

};



// implementation of member functions

template <typename T>
Matrix2D<T> &
Matrix2D<T>::operator = (const Matrix2D<T> &m)
{
  mat2[0] = m[0];
  mat2[1] = m[1];
  return *this;
}

template <typename T>
bool
Matrix2D<T>::operator == (const Matrix2D<T> &m) const
{
  return mat2[0] == m[0] && mat2[1] == m[1];
}

template <typename T>
bool
Matrix2D<T>::operator != (const Matrix2D<T> &m) const
{
  return mat2[0] != m[0] || mat2[1] != m[1];
}

template <typename T>
Matrix2D<T> 
Matrix2D<T>::operator - () const
{
  return Matrix2D<T> (-mat2[0],-mat2[1]);
}

template <typename T>
Matrix2D<T> 
Matrix2D<T>::operator + (const Matrix2D<T> &m) const
{
  return Matrix2D<T> (mat2[0] + m[0], mat2[1] + m[1]);
}

template <typename T>
Matrix2D<T>
Matrix2D<T>::operator - (const Matrix2D<T> &m) const
{
  return Matrix2D<T> (mat2[0] - m[0], mat2[1] - m[1]);
}

template <typename T>
Matrix2D<T>
Matrix2D<T>::operator * (const T &s) const
{
  return Matrix2D<T> (mat2[0]*s, mat2[1]*s);
}

template <typename T>
Matrix2D<T>
Matrix2D<T>::operator * (const Matrix2D<T> &m) const
{
  return Matrix2D<T> (mat2[0].coord.x*m[0].coord.x + mat2[0].coord.y*m[1].coord.x,
                      mat2[0].coord.x*m[0].coord.y + mat2[0].coord.y*m[1].coord.y,
                      mat2[1].coord.x*m[0].coord.x + mat2[1].coord.y*m[1].coord.x,
                      mat2[1].coord.x*m[0].coord.y + mat2[1].coord.y*m[1].coord.y);
}

template <typename T>
Vector2D<T>
Matrix2D<T>::operator * (const Vector2D<T> &v) const
{
  return Vector2D<T> (mat2[0].coord.x*v.coord.x + mat2[0].coord.y*v.coord.y,
                      mat2[1].coord.x*v.coord.x + mat2[1].coord.y*v.coord.y);
}

template <typename T>
Matrix2D<T> 
Matrix2D<T>::operator / (const T &s) const
{
  if (s == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Matrice division by zero.");
  T oneOverS = 1/s;
  return Matrix2D<T> (mat2[0]*oneOverS, mat2[1]*oneOverS);
}

template <typename T>
Vector2D<T> 
Matrix2D<T>::operator [] (const unsigned short r) const
{
  if ( r >= 2 )
    HUMMSTRUMM_THROW (OutOfRange,"Invalid matrice line.");

  return mat2[r];
}

template <typename T>
Matrix2D<T> &
Matrix2D<T>::operator -= (const Matrix2D<T> &m)
{
  mat2[0] -= m[0];
  mat2[1] -= m[1];
  return *this;
}

template <typename T>
Matrix2D<T> &
Matrix2D<T>::operator += (const Matrix2D<T> &m)
{
  mat2[0] += m[0];
  mat2[1] += m[1];
  return *this;
}

template <typename T>
Matrix2D<T> &
Matrix2D<T>::operator *= (const T &s)
{
  mat2[0] *= s;
  mat2[1] *= s;
  return *this;
}

template <typename T>
Matrix2D<T> &
Matrix2D<T>::operator *= (const Matrix2D<T> &m)
{
  Matrix2D tmp (*this);
  mat2[0].coord.x = tmp[0].coord.x*m[0].coord.x + tmp[0].coord.y*m[1].coord.x;
  mat2[0].coord.y = tmp[0].coord.x*m[0].coord.y + tmp[0].coord.y*m[1].coord.y;
  mat2[1].coord.x = tmp[1].coord.x*m[0].coord.x + tmp[1].coord.y*m[1].coord.x;
  mat2[1].coord.y = tmp[1].coord.x*m[0].coord.y + tmp[1].coord.y*m[1].coord.y;
  return *this;
}

template <typename T>
Matrix2D<T> &
Matrix2D<T>::operator /= (const T &s)
{
  if (s == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Matrice division by zero.");

  T oneOverS = 1/s; 
  mat2[0] *= oneOverS;
  mat2[1] *= oneOverS;
  return *this;
}

template <typename T>
void
Matrix2D<T>::Identity ()
{
  mat2[0].coord.x = mat2[1].coord.y = 1;
  mat2[0].coord.y = 0;
  mat2[1].coord.x = 0;
}

template <typename T>
T
Matrix2D<T>::Determinant () const
{
  return mat2[0].coord.x * mat2[1].coord.y - mat2[0].coord.y * mat2[1].coord.x;
}

// Matrix 3D
template <typename T>
Matrix3D<T> &
Matrix3D<T>::operator = (const Matrix3D<T> &m)
{
  mat3[0] = m[0];
  mat3[1] = m[1];
  mat3[2] = m[2];
  return *this;
}

template <typename T>
bool
Matrix3D<T>::operator == (const Matrix3D<T> &m) const
{
  return mat3[0] == m[0] && mat3[1] == m[1] && mat3[2] == m[2];
}

template <typename T>
bool
Matrix3D<T>::operator != (const Matrix3D<T> &m) const
{
  return mat3[0] != m[0] || mat3[1] != m[1] || mat3[2] != m[2];
}

template <typename T>
Matrix3D<T> 
Matrix3D<T>::operator - () const
{
  return Matrix3D<T> (-mat3[0],-mat3[1],-mat3[2]);
}

template <typename T>
Matrix3D<T> 
Matrix3D<T>::operator + (const Matrix3D<T> &m) const
{
  return Matrix3D<T> (mat3[0] + m[0], mat3[1] + m[1], mat3[2] + m[2]);
}

template <typename T>
Matrix3D<T>
Matrix3D<T>::operator - (const Matrix3D<T> &m) const
{
  return Matrix3D<T> (mat3[0] - m[0], mat3[1] - m[1], mat3[2] - m[2]);
}

template <typename T>
Matrix3D<T>
Matrix3D<T>::operator * (const T &s) const
{
  return Matrix3D<T> (mat3[0]*s, mat3[1]*s, mat3[2]*s);
}

template <typename T>
Matrix3D<T>
Matrix3D<T>::operator * (const Matrix3D<T> &m) const
{
  return Matrix3D<T> ( mat3[0].coord.x*m[0].coord.x 
                     + mat3[0].coord.y*m[1].coord.x 
                     + mat3[0].coord.z*m[2].coord.x,
                       mat3[0].coord.x*m[0].coord.y 
                     + mat3[0].coord.y*m[1].coord.y 
                     + mat3[0].coord.z*m[2].coord.y,
                       mat3[0].coord.x*m[0].coord.z 
                     + mat3[0].coord.y*m[1].coord.z 
                     + mat3[0].coord.z*m[2].coord.z,
                       mat3[1].coord.x*m[0].coord.x 
                     + mat3[1].coord.y*m[1].coord.x 
                     + mat3[1].coord.z*m[2].coord.x,
                       mat3[1].coord.x*m[0].coord.y 
                     + mat3[1].coord.y*m[1].coord.y 
                     + mat3[1].coord.z*m[2].coord.y,
                       mat3[1].coord.x*m[0].coord.z 
                     + mat3[1].coord.y*m[1].coord.z 
                     + mat3[1].coord.z*m[2].coord.z,
                       mat3[2].coord.x*m[0].coord.x 
                     + mat3[2].coord.y*m[1].coord.x 
                     + mat3[2].coord.z*m[2].coord.x,
                       mat3[2].coord.x*m[0].coord.y 
                     + mat3[2].coord.y*m[1].coord.y 
                     + mat3[2].coord.z*m[2].coord.y,
                       mat3[2].coord.x*m[0].coord.z 
                     + mat3[2].coord.y*m[1].coord.z 
                     + mat3[2].coord.z*m[2].coord.z);
}

template <typename T>
Vector3D<T>
Matrix3D<T>::operator * (const Vector3D<T> &v) const
{
  return Vector3D<T> (mat3[0].coord.x*v.coord.x 
                    + mat3[0].coord.y*v.coord.y 
                    + mat3[0].coord.z*v.coord.z,
                      mat3[1].coord.x*v.coord.x 
                    + mat3[1].coord.y*v.coord.y 
                    + mat3[1].coord.z*v.coord.z,
                      mat3[2].coord.x*v.coord.x 
                    + mat3[2].coord.y*v.coord.y 
                    + mat3[2].coord.z*v.coord.z);
}

template <typename T>
Matrix3D<T> 
Matrix3D<T>::operator / (const T &s) const
{
  if (s == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Matrice division by zero.");

  T oneOverS = 1/s;
  return Matrix3D<T> (mat3[0]*oneOverS, mat3[1]*oneOverS, mat3[2]*oneOverS);
}

template <typename T>
Vector3D<T> 
Matrix3D<T>::operator [] (const unsigned short r) const
{
  if ( r >= 3 )
    HUMMSTRUMM_THROW (OutOfRange,"Invalid matrix line.");

  return mat3[r];
}

template <typename T>
Matrix3D<T> &
Matrix3D<T>::operator -= (const Matrix3D<T> &m)
{
  mat3[0] -= m[0];
  mat3[1] -= m[1];
  mat3[2] -= m[2];
  return *this;
}

template <typename T>
Matrix3D<T> &
Matrix3D<T>::operator += (const Matrix3D<T> &m)
{
  mat3[0] += m[0];
  mat3[1] += m[1];
  mat3[2] += m[2];
  return *this;
}

template <typename T>
Matrix3D<T> &
Matrix3D<T>::operator *= (const T &s)
{
  mat3[0] *= s;
  mat3[1] *= s;
  mat3[2] *= s;
  return *this;
}

template <typename T>
Matrix3D<T> &
Matrix3D<T>::operator *= (const Matrix3D<T> &m)
{
  Matrix3D tmp(*this);
  mat3[0].coord.x = tmp[0].coord.x*m[0].coord.x 
                  + tmp[0].coord.y*m[1].coord.x 
                  + tmp[0].coord.z*m[2].coord.x;
  mat3[0].coord.y = tmp[0].coord.x*m[0].coord.y 
                  + tmp[0].coord.y*m[1].coord.y 
                  + tmp[0].coord.z*m[2].coord.y;
  mat3[0].coord.z = tmp[0].coord.x*m[0].coord.z 
                  + tmp[0].coord.y*m[1].coord.z 
                  + tmp[0].coord.z*m[2].coord.z;
  mat3[1].coord.x = tmp[1].coord.x*m[0].coord.x 
                  + tmp[1].coord.y*m[1].coord.x 
                  + tmp[1].coord.z*m[2].coord.x;
  mat3[1].coord.y = tmp[1].coord.x*m[0].coord.y 
                  + tmp[1].coord.y*m[1].coord.y 
                  + tmp[1].coord.z*m[2].coord.y;
  mat3[1].coord.z = tmp[1].coord.x*m[0].coord.z 
                  + tmp[1].coord.y*m[1].coord.z 
                  + tmp[1].coord.z*m[2].coord.z;
  mat3[2].coord.x = tmp[2].coord.x*m[0].coord.x 
                  + tmp[2].coord.y*m[1].coord.x 
                  + tmp[2].coord.z*m[2].coord.x;
  mat3[2].coord.y = tmp[2].coord.x*m[0].coord.y 
                  + tmp[2].coord.y*m[1].coord.y 
                  + tmp[2].coord.z*m[2].coord.y;
  mat3[2].coord.z = tmp[2].coord.x*m[0].coord.z 
                  + tmp[2].coord.y*m[1].coord.z 
                  + tmp[2].coord.z*m[2].coord.z;
  return *this;
}


template <typename T>
Matrix3D<T> &
Matrix3D<T>::operator /= (const T &s)
{
  if (s == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Matrice division by zero.");

  T oneOverS = 1/s; 
  mat3[0] *= oneOverS;
  mat3[1] *= oneOverS;
  mat3[2] *= oneOverS;
  return *this;
}

template <typename T>
void
Matrix3D<T>::Identity ()
{
  mat3[0].coord.x = mat3[1].coord.y = mat3[2].coord.z = 1;
  mat3[0].coord.y = mat3[0].coord.z = 0;
  mat3[1].coord.x = mat3[1].coord.z = 0;
  mat3[2].coord.x = mat3[2].coord.y = 0;
}

template <typename T>
T
Matrix3D<T>::Determinant () const
{
  return Vec3DDot(mat3[2],Vec3DCross(mat3[0],mat3[1]));
}

// Matrix 4D
template <typename T>
Matrix4D<T> &
Matrix4D<T>::operator = (const Matrix4D<T> &m)
{
  mat4[0] = m[0];
  mat4[1] = m[1];
  mat4[2] = m[2];
  mat4[3] = m[3];

  return *this;
}

template <typename T>
bool
Matrix4D<T>::operator == (const Matrix4D<T> &m) const
{
  return mat4[0] == m[0] && 
         mat4[1] == m[1] && 
         mat4[2] == m[2] &&
         mat4[3] == m[3];
}

template <typename T>
bool
Matrix4D<T>::operator != (const Matrix4D<T> &m) const
{
  return mat4[0] != m[0] || 
         mat4[1] != m[1] || 
         mat4[2] != m[2] ||
         mat4[3] != m[3];
}

template <typename T>
Matrix4D<T> 
Matrix4D<T>::operator - () const
{
  return Matrix4D<T> (-mat4[0],-mat4[1],-mat4[2],-mat4[3]);
}

template <typename T>
Matrix4D<T> 
Matrix4D<T>::operator + (const Matrix4D<T> &m) const
{
  return Matrix4D<T> (mat4[0] + m[0], mat4[1] + m[1], 
                      mat4[2] + m[2], mat4[3] + m[3]);
}

template <typename T>
Matrix4D<T>
Matrix4D<T>::operator - (const Matrix4D<T> &m) const
{
  return Matrix4D<T> (mat4[0] - m[0], mat4[1] - m[1], 
                      mat4[2] - m[2], mat4[3] - m[3]);
}

template <typename T>
Matrix4D<T>
Matrix4D<T>::operator * (const T &s) const
{
  return Matrix4D<T> (mat4[0]*s, mat4[1]*s, 
                      mat4[2]*s, mat4[3]*s);
}

template <typename T>
Matrix4D<T>
Matrix4D<T>::operator * (const Matrix4D<T> &m) const
{
  return Matrix4D<T> ( mat4[0].coord.x*m[0].coord.x 
                     + mat4[0].coord.y*m[1].coord.x 
                     + mat4[0].coord.z*m[2].coord.x 
                     + mat4[0].coord.w*m[3].coord.x,
                       mat4[0].coord.x*m[0].coord.y 
                     + mat4[0].coord.y*m[1].coord.y 
                     + mat4[0].coord.z*m[2].coord.y 
                     + mat4[0].coord.w*m[3].coord.y,
                       mat4[0].coord.x*m[0].coord.z 
                     + mat4[0].coord.y*m[1].coord.z 
                     + mat4[0].coord.z*m[2].coord.z 
                     + mat4[0].coord.w*m[3].coord.z,
                       mat4[0].coord.x*m[0].coord.w 
                     + mat4[0].coord.y*m[1].coord.w 
                     + mat4[0].coord.z*m[2].coord.w 
                     + mat4[0].coord.w*m[3].coord.w, 
                       mat4[1].coord.x*m[0].coord.x 
                     + mat4[1].coord.y*m[1].coord.x 
                     + mat4[1].coord.z*m[2].coord.x 
                     + mat4[1].coord.w*m[3].coord.x,
                       mat4[1].coord.x*m[0].coord.y 
                     + mat4[1].coord.y*m[1].coord.y 
                     + mat4[1].coord.z*m[2].coord.y 
                     + mat4[1].coord.w*m[3].coord.y,
                       mat4[1].coord.x*m[0].coord.z 
                     + mat4[1].coord.y*m[1].coord.z 
                     + mat4[1].coord.z*m[2].coord.z 
                     + mat4[1].coord.w*m[3].coord.z,
                       mat4[1].coord.x*m[0].coord.w 
                     + mat4[1].coord.y*m[1].coord.w 
                     + mat4[1].coord.z*m[2].coord.w 
                     + mat4[1].coord.w*m[3].coord.w,
                       mat4[2].coord.x*m[0].coord.x 
                     + mat4[2].coord.y*m[1].coord.x 
                     + mat4[2].coord.z*m[2].coord.x 
                     + mat4[2].coord.w*m[3].coord.x,
                       mat4[2].coord.x*m[0].coord.y 
                     + mat4[2].coord.y*m[1].coord.y 
                     + mat4[2].coord.z*m[2].coord.y 
                     + mat4[2].coord.w*m[3].coord.y,
                       mat4[2].coord.x*m[0].coord.z 
                     + mat4[2].coord.y*m[1].coord.z 
                     + mat4[2].coord.z*m[2].coord.z 
                     + mat4[2].coord.w*m[3].coord.z,
                       mat4[2].coord.x*m[0].coord.w 
                     + mat4[2].coord.y*m[1].coord.w 
                     + mat4[2].coord.z*m[2].coord.w 
                     + mat4[2].coord.w*m[3].coord.w,
                       mat4[3].coord.x*m[0].coord.x 
                     + mat4[3].coord.y*m[1].coord.x 
                     + mat4[3].coord.z*m[2].coord.x 
                     + mat4[3].coord.w*m[3].coord.x,
                       mat4[3].coord.x*m[0].coord.y 
                     + mat4[3].coord.y*m[1].coord.y 
                     + mat4[3].coord.z*m[2].coord.y 
                     + mat4[3].coord.w*m[3].coord.y,
                       mat4[3].coord.x*m[0].coord.z 
                     + mat4[3].coord.y*m[1].coord.z 
                     + mat4[3].coord.z*m[2].coord.z 
                     + mat4[3].coord.w*m[3].coord.z,
                       mat4[3].coord.x*m[0].coord.w 
                     + mat4[3].coord.y*m[1].coord.w 
                     + mat4[3].coord.z*m[2].coord.w 
                     + mat4[3].coord.w*m[3].coord.w);
}

template <typename T>
Vector4D<T>
Matrix4D<T>::operator * (const Vector4D<T> &v) const
{
  return Vector4D<T> (mat4[0].coord.x*v.coord.x 
                    + mat4[0].coord.y*v.coord.y 
                    + mat4[0].coord.z*v.coord.z 
                    + mat4[0].coord.w*v.coord.w,
                      mat4[1].coord.x*v.coord.x 
                    + mat4[1].coord.y*v.coord.y 
                    + mat4[1].coord.z*v.coord.z 
                    + mat4[1].coord.w*v.coord.w,
                      mat4[2].coord.x*v.coord.x 
                    + mat4[2].coord.y*v.coord.y 
                    + mat4[2].coord.z*v.coord.z 
                    + mat4[2].coord.w*v.coord.w,
                      mat4[3].coord.x*v.coord.x 
                    + mat4[3].coord.y*v.coord.y 
                    + mat4[3].coord.z*v.coord.z 
                    + mat4[3].coord.w*v.coord.w);
}

template <typename T>
Matrix4D<T> 
Matrix4D<T>::operator / (const T &s) const
{
  if (s == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Matrice division by zero.");

  T oneOverS = 1/s;
  return Matrix4D<T> (mat4[0]*oneOverS, mat4[1]*oneOverS,
                      mat4[2]*oneOverS, mat4[3]*oneOverS);
}

template <typename T>
Vector4D<T> 
Matrix4D<T>::operator [] (const unsigned short r) const
{
  if ( r >= 4 )
    HUMMSTRUMM_THROW (OutOfRange,"Invalid matrix line.");

  return mat4[r];
}

template <typename T>
Matrix4D<T> &
Matrix4D<T>::operator -= (const Matrix4D<T> &m)
{
  mat4[0] -= m[0];
  mat4[1] -= m[1];
  mat4[2] -= m[2];
  mat4[3] -= m[3];
  return *this;
}

template <typename T>
Matrix4D<T> &
Matrix4D<T>::operator += (const Matrix4D<T> &m)
{
  mat4[0] += m[0];
  mat4[1] += m[1];
  mat4[2] += m[2];
  mat4[3] += m[3];
  return *this;
}

template <typename T>
Matrix4D<T> &
Matrix4D<T>::operator *= (const Matrix4D<T> &m)
{
  Matrix4D tmp(*this);
  mat4[0].coord.x = tmp[0].coord.x*m[0].coord.x 
                  + tmp[0].coord.y*m[1].coord.x 
                  + tmp[0].coord.z*m[2].coord.x 
                  + tmp[0].coord.w*m[3].coord.x;
  mat4[0].coord.y = tmp[0].coord.x*m[0].coord.y 
                  + tmp[0].coord.y*m[1].coord.y 
                  + tmp[0].coord.z*m[2].coord.y 
                  + tmp[0].coord.w*m[3].coord.y;
  mat4[0].coord.z = tmp[0].coord.x*m[0].coord.z 
                  + tmp[0].coord.y*m[1].coord.z 
                  + tmp[0].coord.z*m[2].coord.z 
                  + tmp[0].coord.w*m[3].coord.z;
  mat4[0].coord.w = tmp[0].coord.x*m[0].coord.w 
                  + tmp[0].coord.y*m[1].coord.w 
                  + tmp[0].coord.z*m[2].coord.w 
                  + tmp[0].coord.w*m[3].coord.w; 
  mat4[1].coord.x = tmp[1].coord.x*m[0].coord.x 
                  + tmp[1].coord.y*m[1].coord.x 
                  + tmp[1].coord.z*m[2].coord.x 
                  + tmp[1].coord.w*m[3].coord.x;
  mat4[1].coord.y = tmp[1].coord.x*m[0].coord.y 
                  + tmp[1].coord.y*m[1].coord.y 
                  + tmp[1].coord.z*m[2].coord.y 
                  + tmp[1].coord.w*m[3].coord.y;
  mat4[1].coord.z = tmp[1].coord.x*m[0].coord.z 
                  + tmp[1].coord.y*m[1].coord.z 
                  + tmp[1].coord.z*m[2].coord.z 
                  + tmp[1].coord.w*m[3].coord.z;
  mat4[1].coord.w = tmp[1].coord.x*m[0].coord.w 
                  + tmp[1].coord.y*m[1].coord.w 
                  + tmp[1].coord.z*m[2].coord.w 
                  + tmp[1].coord.w*m[3].coord.w;
  mat4[2].coord.x = tmp[2].coord.x*m[0].coord.x 
                  + tmp[2].coord.y*m[1].coord.x 
                  + tmp[2].coord.z*m[2].coord.x 
                  + tmp[2].coord.w*m[3].coord.x;
  mat4[2].coord.y = tmp[2].coord.x*m[0].coord.y 
                  + tmp[2].coord.y*m[1].coord.y 
                  + tmp[2].coord.z*m[2].coord.y 
                  + tmp[2].coord.w*m[3].coord.y;
  mat4[2].coord.z = tmp[2].coord.x*m[0].coord.z 
                  + tmp[2].coord.y*m[1].coord.z 
                  + tmp[2].coord.z*m[2].coord.z 
                  + tmp[2].coord.w*m[3].coord.z;
  mat4[2].coord.w = tmp[2].coord.x*m[0].coord.w 
                  + tmp[2].coord.y*m[1].coord.w 
                  + tmp[2].coord.z*m[2].coord.w 
                  + tmp[2].coord.w*m[3].coord.w;
  mat4[3].coord.x = tmp[3].coord.x*m[0].coord.x 
                  + tmp[3].coord.y*m[1].coord.x 
                  + tmp[3].coord.z*m[2].coord.x 
                  + tmp[3].coord.w*m[3].coord.x;
  mat4[3].coord.y = tmp[3].coord.x*m[0].coord.y 
                  + tmp[3].coord.y*m[1].coord.y 
                  + tmp[3].coord.z*m[2].coord.y 
                  + tmp[3].coord.w*m[3].coord.y;
  mat4[3].coord.z = tmp[3].coord.x*m[0].coord.z 
                  + tmp[3].coord.y*m[1].coord.z 
                  + tmp[3].coord.z*m[2].coord.z 
                  + tmp[3].coord.w*m[3].coord.z;
  mat4[3].coord.w = tmp[3].coord.x*m[0].coord.w 
                  + tmp[3].coord.y*m[1].coord.w 
                  + tmp[3].coord.z*m[2].coord.w 
                  + tmp[3].coord.w*m[3].coord.w;
  return *this;
}


template <typename T>
Matrix4D<T> &
Matrix4D<T>::operator *= (const T &s)
{
  mat4[0] *= s;
  mat4[1] *= s;
  mat4[2] *= s;
  mat4[3] *= s;
  return *this;
}

template <typename T>
Matrix4D<T> &
Matrix4D<T>::operator /= (const T &s)
{
  if (s == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Matrice division by zero.");

  T oneOverS = 1/s; 
  mat4[0] *= oneOverS;
  mat4[1] *= oneOverS;
  mat4[2] *= oneOverS;
  mat4[3] *= oneOverS;
  return *this;
}

template <typename T>
void
Matrix4D<T>::Identity ()
{
  mat4[0].coord.x = mat4[1].coord.y = mat4[2].coord.z = mat4[3].coord.w = 1;
  mat4[0].coord.y = mat4[0].coord.z = mat4[0].coord.w = 0;
  mat4[1].coord.x = mat4[1].coord.z = mat4[1].coord.w = 0;
  mat4[2].coord.x = mat4[2].coord.y = mat4[2].coord.w = 0;
  mat4[3].coord.x = mat4[3].coord.y = mat4[3].coord.z = 0;
}

template <typename T>
T
Matrix4D<T>::Determinant () const
{
  return mat4[0].coord.x*(
             mat4[1].coord.y*(mat4[2].coord.z*mat4[3].coord.w - mat4[2].coord.w*mat4[3].coord.z)
           + mat4[1].coord.z*(mat4[2].coord.w*mat4[3].coord.y - mat4[2].coord.y*mat4[3].coord.w)
           + mat4[1].coord.w*(mat4[2].coord.y*mat4[3].coord.z - mat4[2].coord.z*mat4[3].coord.y)
       )
       - mat4[0].coord.y*(
             mat4[1].coord.x*(mat4[2].coord.z*mat4[3].coord.w - mat4[2].coord.w*mat4[3].coord.z)
           + mat4[1].coord.z*(mat4[2].coord.w*mat4[3].coord.x - mat4[2].coord.x*mat4[3].coord.w)
           + mat4[1].coord.w*(mat4[2].coord.x*mat4[3].coord.z - mat4[2].coord.z*mat4[3].coord.x)
       )
       + mat4[0].coord.z*(
             mat4[1].coord.x*(mat4[2].coord.y*mat4[3].coord.w - mat4[2].coord.w*mat4[3].coord.y)
           + mat4[1].coord.y*(mat4[2].coord.w*mat4[3].coord.x - mat4[2].coord.x*mat4[3].coord.w)
           + mat4[1].coord.w*(mat4[2].coord.x*mat4[3].coord.y - mat4[2].coord.y*mat4[3].coord.x)
       )
       - mat4[0].coord.w*(
             mat4[1].coord.x*(mat4[2].coord.y*mat4[3].coord.z - mat4[2].coord.z*mat4[3].coord.y)
           + mat4[1].coord.y*(mat4[2].coord.z*mat4[3].coord.x - mat4[2].coord.x*mat4[3].coord.z)
           + mat4[1].coord.z*(mat4[2].coord.x*mat4[3].coord.y - mat4[2].coord.y*mat4[3].coord.x)
       );
}

// non member functions declarations

/** 
 * Multiply a 2x2 matrice with a scalar on the left side.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] m A 2x2 matrice.
 * @param [in] s Scalar
 *
 * @return The multiplication of m with s.
 *
 * @see Matrix2D
 */
template <typename T>
Matrix2D<T> operator * (const T &s, const Matrix2D<T> &m);

/** 
 * Inverse of a 2x2 matrice.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] m A 2x2 matrice.
 * 
 * @return The inverse of m.
 *
 * @see Matrix2D
 */
template <typename T>
Matrix2D<T> Mat2DInverse (const Matrix2D<T> &m);

/** 
 * Transpose of a 2x2 matrice.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] m A 2x2 matrice.
 *
 * @return The transpose of m.
 *
 * @see Matrix2D
 */
template <typename T>
Matrix2D<T> Mat2DTranspose (const Matrix2D<T> &m);

/** 
 * Multiply a 3x3 matrice with a scalar on the left side.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] m A 3x3 matrice.
 * @param [in] s Scalar
 *
 * @return The multiplication of m with s.
 *
 * @see Matrix3D
 */
template <typename T>
Matrix3D<T> operator * (const T &s, const Matrix3D<T> &m);

/** 
 * Inverse of a 3x3 matrice.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] m A 3x3 matrice.
 * 
 * @return The inverse of m.
 *
 * @see Matrix3D
 */
template <typename T>
Matrix3D<T> Mat3DInverse (const Matrix3D<T> &m);

/** 
 * Transpose of a 3x3 matrice.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] m A 3x3 matrice.
 *
 * @return The transpose of m.
 *
 * @see Matrix3D
 */
template <typename T>
Matrix3D<T> Mat3DTranspose (const Matrix3D<T> &m);

/** 
 * Multiply a 4x4 matrice with a scalar on the left side.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] m A 4x4 matrice.
 * @param [in] s Scalar
 *
 * @return The multiplication of m with s.
 *
 * @see Matrix4D
 */
template <typename T>
Matrix4D<T> operator * (const T &s, const Matrix4D<T> &m);

/** 
 * Inverse of a 4x4 matrice.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] m A 4x4 matrice.
 * 
 * @return The inverse of m.
 *
 * @see Matrix4D
 */
template <typename T>
Matrix4D<T> Mat4DInverse (const Matrix4D<T> &m);

/** 
 * Transpose of a 4x4 matrice.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param [in] m A 4x4 matrice.
 *
 * @return The transpose of m.
 *
 * @see Matrix4D
 */
template <typename T>
Matrix4D<T> Mat4DTranspose (const Matrix4D<T> &m);

// non member functions implementation

template <typename T>
Matrix2D<T>
operator * (const T &s, const Matrix2D<T> &m)
{
  return Matrix2D<T> (m[0]*s, m[1]*s);
}

template <typename T>
Matrix2D<T>
Mat2DInverse (const Matrix2D<T> &m)
{
  T mDet = m.Determinant();
  if (mDet == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Matrice determinant is zero.");
 
  return Matrix2D<T> (m[1].coord.y, -m[0].coord.y, -m[1].coord.x, m[0].coord.x)/mDet;
}

template <typename T>
Matrix2D<T>
Mat2DTranspose (const Matrix2D<T> &m)
{
  return Matrix2D<T> (m[0].coord.x, m[1].coord.x, m[0].coord.y, m[1].coord.y);
}


template <typename T>
Matrix3D<T>
operator * (const T &s, const Matrix3D<T> &m)
{
  return Matrix3D<T> (m[0]*s, m[1]*s, m[2]*s);
}

template <typename T>
Matrix3D<T>
Mat3DInverse (const Matrix3D<T> &m)
{
  T mDet = m.Determinant();
  if (mDet == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Matrice determinant is zero.");

  return Matrix3D<T> (m[1].coord.y*m[2].coord.z - m[1].coord.z*m[2].coord.y, 
                      m[0].coord.z*m[2].coord.y - m[0].coord.y*m[2].coord.z,
                      m[0].coord.y*m[1].coord.z - m[0].coord.z*m[1].coord.y,
                      m[1].coord.z*m[2].coord.x - m[1].coord.x*m[2].coord.z,
                      m[0].coord.x*m[2].coord.z - m[0].coord.z*m[2].coord.x,
                      m[0].coord.z*m[1].coord.x - m[0].coord.x*m[1].coord.z,
                      m[1].coord.x*m[2].coord.y - m[1].coord.y*m[2].coord.x,
                      m[0].coord.y*m[2].coord.x - m[0].coord.x*m[2].coord.y,
                      m[0].coord.x*m[1].coord.y - m[0].coord.y*m[1].coord.x)/mDet;
}

template <typename T>
Matrix3D<T>
Mat3DTranspose (const Matrix3D<T> &m)
{
  return Matrix3D<T> (m[0].coord.x, m[1].coord.x, m[2].coord.x,
                      m[0].coord.y, m[1].coord.y, m[2].coord.y,
                      m[0].coord.z, m[1].coord.y, m[2].coord.z);
}

template <typename T>
Matrix4D<T>
operator * (const T &s, const Matrix4D<T> &m)
{
  return Matrix4D<T> (m[0]*s, m[1]*s, m[2]*s, m[3]*s);
}

template <typename T>
Matrix4D<T>
Mat4DInverse (const Matrix4D<T> &m)
{
  T mDet = m.Determinant();
  if (mDet == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Matrice determinant is zero.");

  return Matrix4D<T> ( m[1].coord.y*m[2].coord.z*m[3].coord.w 
                     + m[1].coord.z*m[2].coord.w*m[3].coord.y 
                     + m[1].coord.w*m[2].coord.y*m[3].coord.z
                     - m[1].coord.y*m[2].coord.w*m[3].coord.z 
                     - m[1].coord.z*m[2].coord.y*m[3].coord.w 
                     - m[1].coord.w*m[2].coord.z*m[3].coord.y, 
                       m[0].coord.y*m[2].coord.w*m[3].coord.z 
                     + m[0].coord.z*m[2].coord.y*m[3].coord.w 
                     + m[0].coord.w*m[2].coord.z*m[3].coord.y
                     - m[0].coord.y*m[2].coord.z*m[3].coord.w 
                     - m[0].coord.z*m[2].coord.w*m[3].coord.y 
                     - m[0].coord.w*m[2].coord.y*m[3].coord.z,
                       m[0].coord.y*m[1].coord.z*m[3].coord.w 
                     + m[0].coord.z*m[1].coord.w*m[3].coord.y 
                     + m[0].coord.w*m[1].coord.y*m[3].coord.z
                     - m[0].coord.y*m[1].coord.w*m[3].coord.z 
                     - m[0].coord.z*m[1].coord.y*m[3].coord.w 
                     - m[0].coord.w*m[1].coord.z*m[3].coord.y,
                       m[0].coord.y*m[1].coord.w*m[2].coord.z 
                     + m[0].coord.z*m[1].coord.y*m[2].coord.w 
                     + m[0].coord.w*m[1].coord.z*m[2].coord.y 
                     - m[0].coord.y*m[1].coord.z*m[2].coord.y 
                     - m[0].coord.z*m[1].coord.w*m[2].coord.y 
                     - m[0].coord.w*m[1].coord.y*m[2].coord.z,
                       m[1].coord.x*m[2].coord.w*m[3].coord.z 
                     + m[1].coord.z*m[2].coord.x*m[3].coord.w 
                     + m[1].coord.w*m[2].coord.z*m[3].coord.x
                     - m[1].coord.x*m[2].coord.z*m[3].coord.w 
                     - m[1].coord.z*m[2].coord.w*m[3].coord.x 
                     - m[1].coord.w*m[2].coord.x*m[3].coord.z,
                       m[0].coord.x*m[2].coord.z*m[3].coord.w 
                     + m[0].coord.z*m[2].coord.w*m[3].coord.x 
                     + m[0].coord.w*m[2].coord.x*m[3].coord.z
                     - m[0].coord.x*m[2].coord.w*m[3].coord.z 
                     - m[0].coord.z*m[2].coord.x*m[3].coord.w 
                     - m[0].coord.w*m[2].coord.z*m[3].coord.x,
                       m[0].coord.x*m[1].coord.w*m[3].coord.z 
                     + m[0].coord.z*m[1].coord.x*m[3].coord.w 
                     + m[0].coord.w*m[1].coord.z*m[3].coord.x
                     - m[0].coord.x*m[1].coord.z*m[3].coord.w 
                     - m[0].coord.z*m[1].coord.w*m[3].coord.x 
                     - m[0].coord.w*m[1].coord.x*m[3].coord.z,
                       m[0].coord.x*m[1].coord.z*m[2].coord.w 
                     + m[0].coord.z*m[1].coord.w*m[2].coord.x 
                     + m[0].coord.w*m[1].coord.x*m[2].coord.z
                     - m[0].coord.x*m[1].coord.w*m[2].coord.z 
                     - m[0].coord.z*m[1].coord.x*m[2].coord.w 
                     - m[0].coord.w*m[1].coord.z*m[2].coord.x,
                       m[1].coord.x*m[2].coord.y*m[3].coord.w 
                     + m[1].coord.y*m[2].coord.w*m[3].coord.x 
                     + m[1].coord.w*m[2].coord.x*m[3].coord.y
                     - m[1].coord.x*m[2].coord.w*m[3].coord.y 
                     - m[1].coord.y*m[2].coord.x*m[3].coord.w 
                     - m[1].coord.w*m[2].coord.y*m[3].coord.x,
                       m[0].coord.x*m[2].coord.w*m[3].coord.y 
                     + m[0].coord.y*m[2].coord.x*m[3].coord.w 
                     + m[0].coord.w*m[2].coord.y*m[3].coord.x
                     - m[0].coord.x*m[2].coord.y*m[3].coord.w 
                     - m[0].coord.y*m[2].coord.w*m[3].coord.x 
                     - m[0].coord.w*m[2].coord.x*m[3].coord.y,
                       m[0].coord.x*m[1].coord.y*m[3].coord.w 
                     + m[0].coord.y*m[1].coord.w*m[3].coord.x 
                     + m[0].coord.w*m[1].coord.x*m[3].coord.y
                     - m[0].coord.x*m[1].coord.w*m[3].coord.y 
                     - m[0].coord.y*m[1].coord.x*m[3].coord.w 
                     - m[0].coord.w*m[1].coord.y*m[3].coord.x,
                       m[0].coord.x*m[1].coord.w*m[2].coord.y 
                     + m[0].coord.y*m[1].coord.x*m[2].coord.w 
                     + m[0].coord.w*m[1].coord.y*m[2].coord.x
                     - m[0].coord.x*m[1].coord.y*m[2].coord.w 
                     - m[0].coord.y*m[1].coord.w*m[2].coord.x 
                     - m[0].coord.w*m[1].coord.x*m[2].coord.y,
                       m[1].coord.x*m[2].coord.z*m[3].coord.y 
                     + m[1].coord.y*m[2].coord.x*m[3].coord.z 
                     + m[1].coord.z*m[2].coord.y*m[3].coord.x
                     - m[1].coord.x*m[2].coord.y*m[3].coord.z 
                     - m[1].coord.y*m[2].coord.z*m[3].coord.x 
                     - m[1].coord.z*m[2].coord.x*m[3].coord.y,
                       m[0].coord.x*m[2].coord.y*m[3].coord.y 
                     + m[0].coord.y*m[2].coord.z*m[3].coord.x 
                     + m[0].coord.z*m[2].coord.x*m[3].coord.y
                     - m[0].coord.x*m[2].coord.z*m[3].coord.y 
                     - m[0].coord.y*m[2].coord.x*m[3].coord.z 
                     - m[0].coord.z*m[2].coord.y*m[3].coord.x,
                       m[0].coord.x*m[1].coord.z*m[3].coord.y 
                     + m[0].coord.y*m[1].coord.x*m[3].coord.z 
                     + m[0].coord.z*m[1].coord.y*m[3].coord.x
                     - m[0].coord.x*m[1].coord.y*m[3].coord.z 
                     - m[0].coord.y*m[1].coord.z*m[3].coord.x 
                     - m[0].coord.z*m[1].coord.x*m[3].coord.y,
                       m[0].coord.x*m[1].coord.y*m[2].coord.z 
                     + m[0].coord.y*m[1].coord.z*m[2].coord.x 
                     + m[0].coord.z*m[1].coord.x*m[2].coord.y
                     - m[0].coord.x*m[1].coord.z*m[2].coord.y 
                     - m[0].coord.y*m[1].coord.x*m[2].coord.z 
                     - m[0].coord.z*m[1].coord.y*m[2].coord.x)/mDet; 
}

template <typename T>
Matrix4D<T>
Mat4DTranspose (const Matrix4D<T> &m)
{
  return Matrix4D<T> (m[0].coord.x, m[1].coord.x, m[2].coord.x, m[3].coord.x,
                      m[0].coord.y, m[1].coord.y, m[2].coord.y, m[3].coord.y,
                      m[0].coord.z, m[1].coord.z, m[2].coord.z, m[3].coord.z,
                      m[0].coord.w, m[1].coord.w, m[2].coord.w, m[3].coord.w);
}

}
}
}

#endif

