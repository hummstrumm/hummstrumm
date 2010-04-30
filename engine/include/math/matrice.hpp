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
 * Defines and implements classes for square matrices.
 *
 * @file    matrice.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 * @see     Matrix2D
 * @see     Matrix3D
 * @see     Matrix4D
 *
 */

#ifndef HUMMSTRUMM_ENGINE_MATH_MATRICES
#define HUMMSTRUMM_ENGINE_MATH_MATRICES

#include <math/vector.hpp>

namespace hummstrumm
{
namespace engine
{
namespace math
{

template <typename T>
class Matrix2D
{

  public:
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
     * @param v1 First row of matrix
     * @param v1 Second row of matrix.
     *
     */
    Matrix2D (const Vector2D<T> &v1, const Vector2D<T> &v2)
    {
      mat2[0] = v1;
      mat2[1] = v2;
    };

    /** 
     * Construct a 2x2 matrice from coordinates.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param x1 First row X coordinate.
     * @param y1 First row Y coordinate.
     * @param x2 Second row X coordinate
     * @param y2 Second row Y coordinate
     *
     */
    Matrix2D (const T &x1, const T &y1, const T &x2, const T &y2)
    {
      mat2[0].x = x1;
      mat2[0].y = y1;
      mat2[1].x = x2;
      mat2[1].y = y2;
    }

    /** 
     * Copy constructor. Constructs a 2x2 matrice from another 2x2
     * matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param v A 2x2 matrice.
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
     * Assignment operator. Assings a 2x2 matrice to another 2x2
     * matrice. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 2x2 matrice.
     *
     * @return A matrice equal to m.
     */ 
    Matrix2D<T> &operator = (const Matrix2D<T> &m);

    /** 
     * Equality operator. Check if two matrices are equal.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 2x2 matrice.
     * 
     * @return Whether the matrices are equal.
     */
    bool operator == (const Matrix2D<T> &m) const;

    /** 
     * Inequality operator. Check if two matrices are not equal.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 2x2 matrice.
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
     * @param m A 2x2 matrice.
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
     * @param m A 2x2 matrice.
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
     * @param s scalar.
     * 
     * @return A 2x2 matrice containing the multiplication of the
     * scalar with the matrice.
     */
    Matrix2D<T> operator * (const T s) const;

    /** 
     * Division of a 2x2 matrice by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 2x2 matrice containing the division of the scalar
     * with the matrice.
     *
     * @note Does not check for division by zero.
     */
    Matrix2D<T> operator / (const T s) const;

    /** 
     * Return line from the matrix.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param r line to get.
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
     * @param m A 2x2 matrice.
     * 
     * @return A 2x2 matrice containing the sum of the two matrices.
     */
    Matrix2D<T> &operator += (const Matrix2D<T> &m);

    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 2x2 matrice.
     * 
     * @return A 2x2 matrice containing the substraction of the two
     * matrices.
     */
    Matrix2D<T> &operator -= (const Matrix2D<T> &m);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     *
     * @return A 2x2 matrice containing the multiplication of the
     * scalar with the matrice.
     */
    Matrix2D<T> &operator *= (const T s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 2x2 matrice containing the division of the scalar
     * with the matrice.
     *
     * @note Does not check for division by zero.
     */
    Matrix2D<T> &operator /= (const T s);

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
     */
    T Determinant () const;

    /** 
     * Inverse of this matrix.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     */
    void Inverse ();

  private:

  protected:

};

template <typename T>
class Matrix3D
{

  public:
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
     * @param v1 First row of matrix
     * @param v1 Second row of matrix.
     * @param v3 Third row of matrix.
     *
     */
    Matrix3D (const Vector3D<T> &v1, 
              const Vector3D<T> &v2,
              const Vector3D<T> &v3)
    {
      mat3[0] = v1;
      mat3[1] = v2;
      mat3[2] = v3;
    };

    /** 
     * Construct a 3x3 matrice from coordinates.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param x1 First row X coordinate.
     * @param y1 First row Y coordinate.
     * @param x2 Second row X coordinate
     * @param y2 Second row Y coordinate
     * @param x3 Third row X coordinate
     * @param y3 Third row Y coordinate
     *
     */
    Matrix3D (const T &x1, const T &y1, const T &z1,
              const T &x2, const T &y2, const T &z2,
              const T &x3, const T &y3, const T &z3)
    {
      mat3[0].x = x1;
      mat3[0].y = y1;
      mat3[0].z = z1;

      mat3[1].x = x2;
      mat3[1].y = y2;
      mat3[1].z = z2;

      mat3[2].x = x3;
      mat3[2].y = y3;
      mat3[2].z = z3;
    }

    /** 
     * Copy constructor. Constructs a 3x3 matrice from another 3x3
     * matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param v A 3x3 matrice.
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
     * Assignment operator. Assings a 3x3 matrice to another 3x3
     * matrice. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 3x3 matrice.
     *
     * @return A matrice equal to m.
     */ 
    Matrix3D<T> &operator = (const Matrix3D<T> &m);

    /** 
     * Equality operator. Check if two matrices are equal.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 3x3 matrice.
     * 
     * @return Whether the matrices are equal.
     */
    bool operator == (const Matrix3D<T> &m) const;

    /** 
     * Inequality operator. Check if two matrices are not equal.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 3x3 matrice.
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
     * @param m A 3x3 matrice.
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
     * @param m A 3x3 matrice.
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
     * @param s scalar.
     * 
     * @return A 3x3 matrice containing the multiplication of the
     * scalar with the matrice.
     */
    Matrix3D<T> operator * (const T s) const;

    /** 
     * Division of a 3x3 matrice by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 3x3 matrice containing the division of the scalar
     * with the matrice.
     *
     * @note Does not check for division by zero.
     */
    Matrix3D<T> operator / (const T s) const;

    /** 
     * Return line from the matrix.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param r line to get.
     * 
     * @return Line of the matrice.
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
     * @param m A 3x3 matrice.
     * 
     * @return A 3x3 matrice containing the sum of the two matrices.
     */
    Matrix3D<T> &operator += (const Matrix3D<T> &m);

    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 3x3 matrice.
     * 
     * @return A 3x3 matrice containing the substraction of the two
     * matrices.
     */
    Matrix3D<T> &operator -= (const Matrix3D<T> &m);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     *
     * @return A 3x3 matrice containing the multiplication of the
     * scalar with the matrice.
     */
    Matrix3D<T> &operator *= (const T s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 3x3 matrice containing the division of the scalar
     * with the matrice.
     *
     * @note Does not check for division by zero.
     */
    Matrix3D<T> &operator /= (const T s);

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
     */
    T Determinant () const;

    /** 
     * Inverse of this matrix.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     */
    void Inverse ();

  private:

  protected:

};

template <typename T>
class Matrix4D
{

  public:
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
     * @param v1 First row of matrix
     * @param v1 Second row of matrix.
     * @param v3 Third row of matrix.
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
    };

    /** 
     * Construct a 4x4 matrice from coordinates.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param x1 First row X coordinate.
     * @param y1 First row Y coordinate.
     * @param x2 Second row X coordinate.
     * @param y2 Second row Y coordinate.
     * @param x3 Third row X coordinate.
     * @param y3 Third row Y coordinate.
     * @param x4 Fourth row X coordinate.
     * @param y4 Fourth row Y coordinate.
     *
     */
    Matrix4D (const T &x1, const T &y1, const T &z1, const T &w1, 
              const T &x2, const T &y2, const T &z2, const T &w2,
              const T &x3, const T &y3, const T &z3, const T &w3,
              const T &x4, const T &y4, const T &z4, const T &w4)
    {
      mat4[0].x = x1;
      mat4[0].y = y1;
      mat4[0].z = z1;
      mat4[0].w = w1;

      mat4[1].x = x2;
      mat4[1].y = y2;
      mat4[1].z = z2;
      mat4[1].w = w2;

      mat4[2].x = x3;
      mat4[2].y = y3;
      mat4[2].z = z3;
      mat4[2].w = w3;

      mat4[3].x = x4;
      mat4[3].y = y4;
      mat4[3].z = z4;
      mat4[3].w = w4;
    }

    /** 
     * Copy constructor. Constructs a 4x4 matrice from another 4x4
     * matrice.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param v A 4x4 matrice.
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
     * Assignment operator. Assings a 4x4 matrice to another 4x4
     * matrice. 
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 4x4 matrice.
     *
     * @return A matrice equal to m.
     */ 
    Matrix4D<T> &operator = (const Matrix4D<T> &m);

    /** 
     * Equality operator. Check if two matrices are equal.
     * 
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 4x4 matrice.
     * 
     * @return Whether the matrices are equal.
     */
    bool operator == (const Matrix4D<T> &m) const;

    /** 
     * Inequality operator. Check if two matrices are not equal.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 4x4 matrice.
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
     * @param m A 4x4 matrice.
     * 
     * @return A 4x4 matrice containing the sum of the two matrices.
     */
    Matrix4D<T> operator + (const Matrix4D<T> &m) const;

    /** 
     * Subtract two 4x4 matrices.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 4x4 matrice.
     * 
     * @return A 4x4 matrice containing the substraction of the two
     * matrices.
     */
    Matrix4D<T> operator - (const Matrix4D<T> &m) const;

    /** 
     * Multiplication of a 4x4 matrice by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 4x4 matrice containing the multiplication of the
     * scalar with the matrice.
     */
    Matrix4D<T> operator * (const T s) const;

    /** 
     * Division of a 4x4 matrice by a scalar.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 4x4 matrice containing the division of the scalar
     * with the matrice.
     *
     * @note Does not check for division by zero.
     */
    Matrix4D<T> operator / (const T s) const;

    /** 
     * Return line from the matrix.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param r line to get.
     * 
     * @return Line of the matrice.
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
     * @param m A 4x4 matrice.
     * 
     * @return A 4x4 matrice containing the sum of the two matrices.
     */
    Matrix4D<T> &operator += (const Matrix4D<T> &m);

    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param m A 4x4 matrice.
     * 
     * @return A 4x4 matrice containing the substraction of the two
     * matrices.
     */
    Matrix4D<T> &operator -= (const Matrix4D<T> &m);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     *
     * @return A 4x4 matrice containing the multiplication of the
     * scalar with the matrice.
     */
    Matrix4D<T> &operator *= (const T s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return A 4x4 matrice containing the division of the scalar
     * with the matrice.
     *
     * @note Does not check for division by zero.
     */
    Matrix4D<T> &operator /= (const T s);

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
     */
    T Determinant () const;

    /** 
     * Inverse of this matrix.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     */
    void Inverse ();

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
Matrix2D<T>::operator * (const T s) const
{
  return Matrix2D<T> (mat2[0]*s, mat2[1]*s);
}

template <typename T>
Matrix2D<T> 
Matrix2D<T>::operator / (const T s) const
{
  T oneOverS = 1/s;
  return Matrix2D<T> (mat2[0]*oneOverS, mat2[1]*oneOverS);
}

template <typename T>
Vector2D<T> 
Matrix2D<T>::operator [] (const unsigned short r) const
{
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
Matrix2D<T>::operator *= (const T s)
{
  mat2[0] *= s;
  mat2[1] *= s;
  return *this;
}

template <typename T>
Matrix2D<T> &
Matrix2D<T>::operator /= (const T s)
{
  T oneOverS = 1/s; 
  mat2[0] *= oneOverS;
  mat2[1] *= oneOverS;
  return *this;
}

template <typename T>
void
Matrix2D<T>::Identity ()
{
  mat2[0].x = mat2[1].y = 1;
  mat2[0].y = 0;
  mat2[1].x = 0;
}

template <typename T>
T
Matrix2D<T>::Determinant () const
{
  return mat2[0].x * mat2[1].y - mat2[0].y * mat2[1].x;
}

template <typename T>
void
Matrix2D<T>::Inverse ()
{
  *this = Matrix2D(mat2[1].y, -mat2[0].y, -mat2[1].x, mat2[0].x)
          /Determinant();
}

// Matrix 3D
template <typename T>
Matrix3D<T> &
Matrix3D<T>::operator = (const Matrix3D<T> &m)
{
  mat3[0] = m[0];
  mat3[1] = m[1];
  mat3[2] = m[2];
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
Matrix3D<T>::operator * (const T s) const
{
  return Matrix3D<T> (mat3[0]*s, mat3[1]*s, mat3[2]*s);
}

template <typename T>
Matrix3D<T> 
Matrix3D<T>::operator / (const T s) const
{
  T oneOverS = 1/s;
  return Matrix3D<T> (mat3[0]*oneOverS, mat3[1]*oneOverS, mat3[2]*oneOverS);
}

template <typename T>
Vector3D<T> 
Matrix3D<T>::operator [] (const unsigned short r) const
{
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
Matrix3D<T>::operator *= (const T s)
{
  mat3[0] *= s;
  mat3[1] *= s;
  mat3[2] *= s;
  return *this;
}

template <typename T>
Matrix3D<T> &
Matrix3D<T>::operator /= (const T s)
{
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
  mat3[0].x = mat3[1].y = mat3[2].z = 1;
  mat3[0].y = mat3[0].z = 0;
  mat3[1].x = mat3[1].z = 0;
  mat3[2].x = mat3[2].y = 0;
}

template <typename T>
T
Matrix3D<T>::Determinant () const
{
  return mat3[2].dot(Vec3DCross(mat3[0],mat3[1]));
}

template <typename T>
void
Matrix3D<T>::Inverse ()
{
  *this = Matrix3D(mat3[1].y*mat3[2].z - mat3[1].z*mat3[2].y, 
                   mat3[0].z*mat3[2].y - mat3[0].y*mat3[2].z,
                   mat3[0].y*mat3[1].z - mat3[0].z*mat3[1].y,
                   mat3[1].z*mat3[2].x - mat3[1].x*mat3[2].z,
                   mat3[0].x*mat3[2].z - mat3[0].z*mat3[2].x,
                   mat3[0].z*mat3[1].x - mat3[0].x*mat3[1].z,
                   mat3[1].x*mat3[2].y - mat3[1].y*mat3[2].x,
                   mat3[0].y*mat3[2].x - mat3[0].x*mat3[2].y,
                   mat3[0].x*mat3[1].y - mat3[0].y*mat3[1].x)
                   /Determinant();
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
Matrix4D<T>::operator * (const T s) const
{
  return Matrix4D<T> (mat4[0]*s, mat4[1]*s, 
                      mat4[2]*s, mat4[3]*s);
}

template <typename T>
Matrix4D<T> 
Matrix4D<T>::operator / (const T s) const
{
  T oneOverS = 1/s;
  return Matrix4D<T> (mat4[0]*oneOverS, mat4[1]*oneOverS,
                      mat4[2]*oneOverS, mat4[3]*oneOverS);
}

template <typename T>
Vector4D<T> 
Matrix4D<T>::operator [] (const unsigned short r) const
{
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
Matrix4D<T>::operator *= (const T s)
{
  mat4[0] *= s;
  mat4[1] *= s;
  mat4[2] *= s;
  mat4[3] *= s;
  return *this;
}

template <typename T>
Matrix4D<T> &
Matrix4D<T>::operator /= (const T s)
{
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
  mat4[0].x = mat4[1].y = mat4[2].z = mat4[3].w = 1;
  mat4[0].y = mat4[0].z = mat4[0].w = 0;
  mat4[1].x = mat4[1].z = mat4[1].w = 0;
  mat4[2].x = mat4[2].y = mat4[2].w = 0;
  mat4[3].x = mat4[3].y = mat4[3].z = 0;
}

template <typename T>
T
Matrix4D<T>::Determinant () const
{
  return mat4[0].x*(mat4[1].y*(mat4[2].z*mat4[3].w - mat4[2].w*mat4[3].z)
         + mat4[1].z*(mat4[2].w*mat4[3].y - mat4[2].y*mat4[3].w)
         + mat4[1].w*(mat4[2].y*mat4[3].z - mat4[2].z*mat4[3].y))

         - mat4[0].y*(mat4[1].x*(mat4[2].z*mat4[3].w - mat4[2].w*mat4[3].z)
         + mat4[1].z*(mat4[2].w*mat4[3].x - mat4[2].x*mat4[3].w)
         + mat4[1].w*(mat4[2].x*mat4[3].z - mat4[2].z*mat4[3].x))

         + mat4[0].z*(mat4[1].x*(mat4[2].y*mat4[3].w - mat4[2].w*mat4[3].y)
         + mat4[1].y*(mat4[2].w*mat4[3].x - mat4[2].x*mat4[3].w)
         + mat4[1].w*(mat4[2].x*mat4[3].y - mat4[2].y*mat4[3].x))

         - mat4[0].w*(mat4[1].x*(mat4[2].y*mat4[3].z - mat4[2].z*mat4[3].y)
         + mat4[1].y*(mat4[2].z*mat4[3].x - mat4[2].x*mat4[3].z)
         + mat4[1].z*(mat4[2].x*mat4[3].y - mat4[2].y*mat4[3].x));
}


template <typename T>
void
Matrix4D<T>::Inverse ()
{ 
  *this = Matrix4D(mat4[1].y*mat4[2].z*mat4[3].w + mat4[1].z*mat4[2].w*mat4[3].y 
                   + mat4[1].w*mat4[2].y*mat4[3].z
                   - mat4[1].y*mat4[2].w*mat4[3].z - mat4[1].z*mat4[2].y*mat4[3].w 
                   - mat4[1].w*mat4[2].z*mat4[3].y, 
                   mat4[0].y*mat4[2].w*mat4[3].z + mat4[0].z*mat4[2].y*mat4[3].w 
                   + mat4[0].w*mat4[2].z*mat4[3].y
                   - mat4[0].y*mat4[2].z*mat4[3].w - mat4[0].z*mat4[2].w*mat4[3].y 
                   - mat4[0].w*mat4[2].y*mat4[3].z,
                   mat4[0].y*mat4[1].z*mat4[3].w + mat4[0].z*mat4[1].w*mat4[3].y 
                   +  mat4[0].w*mat4[1].y*mat4[3].z
                   - mat4[0].y*mat4[1].w*mat4[3].z - mat4[0].z*mat4[1].y*mat4[3].w 
                   - mat4[0].w*mat4[1].z*mat4[3].y,
                   mat4[0].y*mat4[1].w*mat4[2].z + mat4[0].z*mat4[1].y*mat4[2].w 
                   + mat4[0].w*mat4[1].z*mat4[2].y 
                   - mat4[0].y*mat4[1].z*mat4[2].y - mat4[0].z*mat4[1].w*mat4[2].y 
                   - mat4[0].w*mat4[1].y*mat4[2].z,

                   mat4[1].x*mat4[2].w*mat4[3].z + mat4[1].z*mat4[2].x*mat4[3].w 
                   + mat4[1].w*mat4[2].z*mat4[3].x
                   - mat4[1].x*mat4[2].z*mat4[3].w - mat4[1].z*mat4[2].w*mat4[3].x 
                   - mat4[1].w*mat4[2].x*mat4[3].z,
                   mat4[0].x*mat4[2].z*mat4[3].w + mat4[0].z*mat4[2].w*mat4[3].x 
                   + mat4[0].w*mat4[2].x*mat4[3].z
                   - mat4[0].x*mat4[2].w*mat4[3].z - mat4[0].z*mat4[2].x*mat4[3].w 
                   - mat4[0].w*mat4[2].z*mat4[3].x,
                   mat4[0].x*mat4[1].w*mat4[3].z + mat4[0].z*mat4[1].x*mat4[3].w 
                   + mat4[0].w*mat4[1].z*mat4[3].x
                   - mat4[0].x*mat4[1].z*mat4[3].w - mat4[0].z*mat4[1].w*mat4[3].x 
                   - mat4[0].w*mat4[1].x*mat4[3].z,
                   mat4[0].x*mat4[1].z*mat4[2].w + mat4[0].z*mat4[1].w*mat4[2].x 
                   + mat4[0].w*mat4[1].x*mat4[2].z
                   - mat4[0].x*mat4[1].w*mat4[2].z - mat4[0].z*mat4[1].x*mat4[2].w 
                   - mat4[0].w*mat4[1].z*mat4[2].x,

                   mat4[1].x*mat4[2].y*mat4[3].w + mat4[1].y*mat4[2].w*mat4[3].x 
                   + mat4[1].w*mat4[2].x*mat4[3].y
                   - mat4[1].x*mat4[2].w*mat4[3].y - mat4[1].y*mat4[2].x*mat4[3].w 
                   - mat4[1].w*mat4[2].y*mat4[3].x,
                   mat4[0].x*mat4[2].w*mat4[3].y + mat4[0].y*mat4[2].x*mat4[3].w 
                   + mat4[0].w*mat4[2].y*mat4[3].x
                   - mat4[0].x*mat4[2].y*mat4[3].w - mat4[0].y*mat4[2].w*mat4[3].x 
                   - mat4[0].w*mat4[2].x*mat4[3].y,
                   mat4[0].x*mat4[1].y*mat4[3].w + mat4[0].y*mat4[1].w*mat4[3].x 
                   + mat4[0].w*mat4[1].x*mat4[3].y
                   - mat4[0].x*mat4[1].w*mat4[3].y - mat4[0].y*mat4[1].x*mat4[3].w 
                   - mat4[0].w*mat4[1].y*mat4[3].x,
                   mat4[0].x*mat4[1].w*mat4[2].y + mat4[0].y*mat4[1].x*mat4[2].w 
                   + mat4[0].w*mat4[1].y*mat4[2].x
                   - mat4[0].x*mat4[1].y*mat4[2].w - mat4[0].y*mat4[1].w*mat4[2].x 
                   - mat4[0].w*mat4[1].x*mat4[2].y,

                   mat4[1].x*mat4[2].z*mat4[3].y + mat4[1].y*mat4[2].x*mat4[3].z 
                   + mat4[1].z*mat4[2].y*mat4[3].x
                   - mat4[1].x*mat4[2].y*mat4[3].z - mat4[1].y*mat4[2].z*mat4[3].x 
                   - mat4[1].z*mat4[2].x*mat4[3].y,
                   mat4[0].x*mat4[2].y*mat4[3].y + mat4[0].y*mat4[2].z*mat4[3].x 
                   + mat4[0].z*mat4[2].x*mat4[3].y
                   - mat4[0].x*mat4[2].z*mat4[3].y - mat4[0].y*mat4[2].x*mat4[3].z 
                   - mat4[0].z*mat4[2].y*mat4[3].x,
                   mat4[0].x*mat4[1].z*mat4[3].y + mat4[0].y*mat4[1].x*mat4[3].z 
                   + mat4[0].z*mat4[1].y*mat4[3].x
                   - mat4[0].x*mat4[1].y*mat4[3].z - mat4[0].y*mat4[1].z*mat4[3].x 
                   - mat4[0].z*mat4[1].x*mat4[3].y,
                   mat4[0].x*mat4[1].y*mat4[2].z + mat4[0].y*mat4[1].z*mat4[2].x 
                   + mat4[0].z*mat4[1].x*mat4[2].y
                   - mat4[0].x*mat4[1].z*mat4[2].y - mat4[0].y*mat4[1].x*mat4[2].z 
                   - mat4[0].z*mat4[1].y*mat4[2].x)/Determinant(); 
}

// non member functions

template <typename T>
Matrix2D<T>
operator * (const T s, const Matrix2D<T> &m)
{
  return typename Matrix2D<T>::Matrix2D (m[0]*s, m[1]*s);
}

template <typename T>
Matrix3D<T>
operator * (const T s, const Matrix3D<T> &m)
{
  return typename Matrix3D<T>::Matrix3D (m[0]*s, m[1]*s, m[2]*s);
}

template <typename T>
Matrix4D<T>
operator * (const T s, const Matrix4D<T> &m)
{
  return typename Matrix4D<T>::Matrix4D (m[0]*s, m[1]*s, m[2]*s, m[3]*s);
}



}
}
}

#endif

