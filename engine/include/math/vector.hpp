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
 * Defines and implements classes for vector in 2,3,and 4 dimensions.
 *
 * @file    vector.hpp
 * @author  Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
 * @date    2010-03-28
 * @see     Vector2D
 * @see     Vector3D
 * @see     Vector4D
 *
 * @todo Finish the Gram-Schmidt Orthonormalization and associated 
 * Projection methods.
 */

#ifndef HUMMSTRUMM_ENGINE_MATH_VECTORS
#define HUMMSTRUMM_ENGINE_MATH_VECTORS

#include <cmath>

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
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    Vector2D ();

    /** 
     * Construct a Vector2D object. It will assign coordinates vx, 
     * and vy to x and y respectively.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param vx X coordinate.
     * @param vy Y coordinate.
     *
     */
    Vector2D (T vx, T vy);

    /** 
     * Copy constructor for Vector2D class.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param v Constant reference to a Vector2D object.
     *
     */ 
    Vector2D (const Vector2D<T>  &v); 

    /** 
     * Destructs a Vector2D object.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    ~Vector2D ();

    /** 
     * Assignment operator for Vector2D class. 
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    Vector2D<T> &operator = (const Vector2D<T> &v);

    /** 
     * Equality operator. Check if two Vector2D are equal.
     * 
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector2D object.
     * 
     * @return Whether the vectors are equal.
     */
    bool operator == (const Vector2D<T> &v) const;

    /** 
     * Inequality operator. Check if two Vector2D are not equal.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector2D object.
     * 
     * @return Whether the vectors are different.
     */
    bool operator != (const Vector2D<T> &v) const;
    
    /** 
     * Unary minus. Negate coordinates of Vector2D.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return The negation of a Vector2D.
     */
    Vector2D<T> operator - () const;
   
    /** 
     * Sum two Vector2D objects. 
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector2D object.
     * 
     * @return The result of the sum.
     */
    Vector2D<T> operator + (const Vector2D<T> &v) const;

    /** 
     * Subtract two Vector2D objects.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector2D object.
     * 
     * @return The result of the subtraction.
     */
    Vector2D<T> operator - (const Vector2D<T> &v) const;

    /** 
     * Multiplication of a Vector2D object by a scalar.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return The result of the multiplication.
     */
    Vector2D<T> operator * (T s) const;

    /** 
     * Division of a Vector2D object by a scalar.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return The result of the division.
     *
     * @note Does not check for division by zero.
     */
    Vector2D<T> operator / (T s) const;

    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector2D object.
     * 
     * @return The result of the addition.
     */
    Vector2D<T> &operator += (const Vector2D<T> &v);

    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector2D object.
     * 
     * @return The result of the subtraction.
     */
    Vector2D<T> &operator -= (const Vector2D<T> &v);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return The result of the multiplication.
     */
    Vector2D<T> &operator *= (T s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return The result of the division.
     */
    Vector2D<T> &operator /= (T s);

    /** 
     * Normalize the vector.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */
    void normalize ();

    /** 
     * Compute the dot product.
     * 
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constante reference to a Vector2D object.
     * 
     * @return The result of the dot product.
     */
    T dot (const Vector2D<T> &v) const;

    /** 
     * Computes a perpendicular vector.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return A perpendicular vector.
     */
    Vector2D<T> Perpendicular () const;

    /** 
     * Computes a perpendicular vector of unit length.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @return A perpendicular vector of unit length.
     */
    Vector2D<T> UnitPerpendicular () const;

    /** 
     * Gram-Schmidt Orthogonalization.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v A reference to a Vector2D object.
     * @param w Another reference to a Vector2D object.
     
    void Orthonormalize (Vector2D<T> &v, Vector2D<T> &w);
    */

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
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    Vector3D ();

    /** 
     * Construct a Vector3D object. It will assign coordinates vx, 
     * vy, and vz to x, y, and z respectively.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param vx X coordinate.
     * @param vy Y coordinate.
     * @param vz Z coordinate.
     *
     */
    Vector3D (T vx, T vy, T vz);

    /** 
     * Copy constructor for Vector3D class.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param v Constant reference to a Vector3D object.
     *
     */ 
    Vector3D (const Vector3D<T>  &v); 

    /** 
     * Destructs a Vector3D object.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    ~Vector3D ();

    /** 
     * Assignment operator for Vector3D class. 
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    Vector3D<T> &operator = (const Vector3D<T> &v);

    /** 
     * Equality operator. Check if two Vector3D are equal.
     * 
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector3D object.
     * 
     * @return Whether the vectors are equal.
     */
    bool operator == (const Vector3D<T> &v) const;

    /** 
     * Inequality operator. Check if two Vector3D are not equal.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector3D object.
     * 
     * @return Whether the vectors are different.
     */
    bool operator != (const Vector3D<T> &v) const;
    
    /** 
     * Unary minus. Negate coordinates of Vector3D.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return The negation of a Vector3D.
     */
    Vector3D<T> operator - () const;
   
    /** 
     * Sum two Vector3D objects. 
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector3D object.
     * 
     * @return The result of the sum.
     */
    Vector3D<T> operator + (const Vector3D<T> &v) const;

    /** 
     * Subtract two Vector3D objects.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector3D object.
     * 
     * @return The result of the subtraction.
     */
    Vector3D<T> operator - (const Vector3D<T> &v) const;

    /** 
     * Multiplication of a Vector3D object by a scalar.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return The result of the multiplication.
     */
    Vector3D<T> operator * (T s) const;

    /** 
     * Division of a Vector3D object by a scalar.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return The result of the division.
     *
     * @note Does not check for division by zero.
     */
    Vector3D<T> operator / (T s) const;

    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector3D object.
     * 
     * @return The result of the addition.
     */
    Vector3D<T> &operator += (const Vector3D<T> &v);

    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector3D object.
     * 
     * @return The result of the subtraction.
     */
    Vector3D<T> &operator -= (const Vector3D<T> &v);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return The result of the multiplication.
     */
    Vector3D<T> &operator *= (T s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return The result of the division.
     */
    Vector3D<T> &operator /= (T s);

    /** 
     * Normalize the vector.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */
    void normalize ();

    /** 
     * Compute the dot product.
     * 
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constante reference to a Vector3D object.
     * 
     * @return The result of the dot product.
     */
    T dot (const Vector3D<T> &v) const;

    /** 
     * Computes a perpendicular vector.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return A perpendicular vector.
     */
    Vector3D<T> Perpendicular () const;

    /** 
     * Computes perpendicular vector of unit length.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return A perpendicular vector of unit length.
     */
    Vector3D<T> UnitPerpendicular () const;

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
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    Vector4D ();

    /** 
     * Construct a Vector4D object. It will assign coordinates vx, 
     * vy,vz, and vw to x,y,z, and w respectively.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param vx X coordinate.
     * @param vy Y coordinate.
     * @param vz Z coordinate.
     * @param vz W coordinate.
     *
     */
    Vector4D (T vx, T vy, T vz, T vw);

    /** 
     * Copy constructor for Vector4D class.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     * 
     * @param v Constant reference to a Vector4D object.
     *
     */ 
    Vector4D (const Vector4D<T>  &v); 

    /** 
     * Destructs a Vector4D object.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    ~Vector4D ();

    /** 
     * Assignment operator for Vector4D class. 
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */ 
    Vector4D<T> &operator = (const Vector4D<T> &v);

    /** 
     * Equality operator. Check if two Vector4D are equal.
     * 
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector4D object.
     * 
     * @return Whether the vectors are equal.
     */
    bool operator == (const Vector4D<T> &v) const;

    /** 
     * Inequality operator. Check if two Vector4D are not equal.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector4D object.
     * 
     * @return Whether the vectors are different.
     */
    bool operator != (const Vector4D<T> &v) const;
    
    /** 
     * Unary minus. Negate coordinates of Vector4D.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return The negation of a Vector4D.
     */
    Vector4D<T> operator - () const;
   
    /** 
     * Sum two Vector4D objects. 
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector4D object.
     * 
     * @return The result of the sum.
     */
    Vector4D<T> operator + (const Vector4D<T> &v) const;

    /** 
     * Subtract two Vector4D objects.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector4D object.
     * 
     * @return The result of the subtraction.
     */
    Vector4D<T> operator - (const Vector4D<T> &v) const;

    /** 
     * Multiplication of a Vector4D object by a scalar.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return The result of the multiplication.
     */
    Vector4D<T> operator * (T s) const;

    /** 
     * Division of a Vector4D object by a scalar.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return The result of the division.
     *
     * @note Does not check for division by zero.
     */
    Vector4D<T> operator / (T s) const;

    /** 
     * Combined add assigment operator.
     * 
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector4D object.
     * 
     * @return The result of the addition.
     */
    Vector4D<T> &operator += (const Vector4D<T> &v);

    /** 
     * Combined subtract assignment operator.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constant reference to a Vector4D object.
     * 
     * @return The result of the subtraction.
     */
    Vector4D<T> &operator -= (const Vector4D<T> &v);

    /** 
     * Combined multiplication assignment operator.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return The result of the multiplication.
     */
    Vector4D<T> &operator *= (T s);

    /** 
     * Combined division assignment operator.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param s scalar.
     * 
     * @return The result of the division.
     */
    Vector4D<T> &operator /= (T s);

    /** 
     * Normalize the vector.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     */
    void normalize ();

    /** 
     * Compute the dot product.
     * 
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @param v Constante reference to a Vector4D object.
     * 
     * @return The result of the dot product.
     */
    T dot (const Vector4D<T> &v) const;

    /** 
     * Computes a perpendicular vector.
     *
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2
     *
     * @return A perpendicular vector.
     */
    Vector4D<T> Perpendicular () const;

    /** 
     * Computes perpendicular vector of unit length.
     * 
     * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
     * @date 2010-03-28
     * @since 0.2

     * @return A perpendicular vector of unit length.
     */
    Vector4D<T> UnitPerpendicular () const;

  private:

  protected:

};

// Non-member functions

/** 
 * Magnitude of a Vector2D.
 *
 * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v Constant reference to a Vector2D.
 * 
 * @return The magnitude of vector.
 */
template <typename T> 
T 
Vec2DMagnitude (const Vector2D<T> &v);

/** 
 * @brief Distance between two vectors of type Vector2D. 
 *
 * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v Constant reference to a Vector2D object.
 * @param w Another Constant reference to a Vector2D object.
 * 
 * @return The distance between the vectors.
*/
template <typename T>
T 
Vec2DDistance (const Vector2D<T> &v, const Vector2D<T> &w);

template <typename T>
void 
Orthonormalize2D (Vector2D<T> &u, Vector2D<T> &v, Vector2D<T> &w);

/** 
 * @brief Magnitude of a Vector3D.
 *
 * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v Constant reference to a Vector3D.
 * 
 * @return The magnitude of vector.
 */
template <typename T> 
T 
Vec3DMagnitude (const Vector3D<T> &v);

/** 
 * @brief Vector3D cross product.
 *
 * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v Constant reference to a Vector3D.
 * @param w	Another constant reference to a Vector3D.
 * 
 * @return Cross product result.
 */
template <typename T>
Vector3D<T> 
Vec3DCross (const Vector3D<T> &v, const Vector3D<T> &w);

/** 
 * @brief Distance between two vectors of type Vector3D. 
 * 
 * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v Constant reference to a Vector3D object.
 * @param w Another constant reference to a Vector3D object.
 * 
 * @return The distance between the vectors.
*/
template <typename T>
T 
Vec3DDistance (const Vector3D<T> &v, const Vector3D<T> &w);

template <typename T>
void 
Orthonormalize3D (Vector3D<T> &u, Vector3D<T> &v, Vector3D<T> &w);

/** 
 * @brief Vector4D magnitude.
 *
 * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v Constant reference to a Vector4D.
 * 
 * @return The magnitude of vector.
 */
template <typename T> 
T 
Vec4DMagnitude (const Vector4D<T> &v);

/** 
 * @brief Distance between two vectors of type Vector4D. 
 *
 * @author Ricardo Tiago <Ricardo.Tiago.Mendes@gmail.com>
 * @date 2010-03-28
 * @since 0.2
 *
 * @param v Constant reference to a Vector4D object.
 * @param w Another constant reference to a Vector4D object.
 * 
 * @return The distance between the vectors.
*/
template <typename T>
T 
Vec4DDistance (const Vector4D<T> &v, const Vector4D<T> &k);


// Implementation of Vector2D,3D,4D

template <typename T>
Vector2D<T>::Vector2D ()
{
  x = 0;
  y = 0;
}

template <typename T>
Vector2D<T>::Vector2D (const T vx,const T vy)
{
  x = vx;
  y = vy;
}

template <typename T>
Vector2D<T>::Vector2D (const Vector2D<T>  &v)
{
  x = v.x;
  y = v.y;
}

template <typename T>
Vector2D<T>::~Vector2D ()
{
}

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
  return Vector2D<T>::Vector2D<T> (x + v.x, y + v.y);
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator - (const Vector2D<T> &v) const
{
  return Vector2D<T>::Vector2D<T> (x - v.x, y - v.y);
}

template <typename T>
Vector2D<T> 
Vector2D<T>::operator - () const 
{
  return Vector2D<T> (-x,-y); 
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
  T oneOverS = 1/s;
	x *= oneOverS; y *= oneOverS;
	return *this;
}

template <typename T>
void 
Vector2D<T>::normalize ()
{
  T magSq = x*x + y*y;
	if (magSq > 0)
	{
	  T oneOverMag = 1/sqrt (magSq);
		x *= oneOverMag;
		y *= oneOverMag;
	}
}

template <typename T>
T 
Vector2D<T>::dot (const Vector2D<T> &v) const
{
  return x*v.x + y*v.y;
}

template <typename T>
Vector2D<T> 
Vector2D<T>::Perpendicular () const
{
  return Vector2D (y,-x);
}

template <typename T>
Vector2D<T> 
Vector2D<T>::UnitPerpendicular () const
{
  return Vector2D<T>::Perpendicular ()/Vec2DMagnitude (*this);
}

template <typename T>
Vector3D<T>::Vector3D ()
{
  x = 0;
  y = 0;
  z = 0;
}

template <typename T>
Vector3D<T>::Vector3D (const T vx, const T vy, const T vz)
{
  x = vx;
  y = vy;
  z = vz;
}

template <typename T>
Vector3D<T>::Vector3D (const Vector3D<T>  &v)
{
  x = v.x;
  y = v.y;
  z = v.z;
}

template <typename T>
Vector3D<T>::~Vector3D ()
{
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
  return Vector3D<T>::Vector3D<T> (x + v.x, y + v.y, z + v.z);
}

template <typename T>
Vector3D<T> 
Vector3D<T>::operator - (const Vector3D<T> &v) const
{
  return Vector3D<T>::Vector3D<T> (x - v.x, y - v.y, z - v.z);
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
  T oneOverS = 1/s;
	x *= oneOverS; y *= oneOverS; z *= oneOverS;
	return *this;
}

template <typename T>
void 
Vector3D<T>::normalize ()
{
  T magSq = x*x + y*y + z*z;
	if (magSq > 0)
	{
	  T oneOverMag = 1/sqrt (magSq);
		x *= oneOverMag;
		y *= oneOverMag;
    z *= oneOverMag;
	}
}

template <typename T>
T 
Vector3D<T>::dot (const Vector3D<T> &v) const
{
  return x*v.x + y*v.y + z*v.z;
}


template <typename T>
Vector4D<T>::Vector4D ()
{
  x = 0;
  y = 0;
  z = 0;
  w = 0;
}

template <typename T>
Vector4D<T>::Vector4D (const T vx, const T vy, const T vz, const T vw)
{
  x = vx;
  y = vy;
  z = vz;
  w = vw;
}

template <typename T>
Vector4D<T>::Vector4D (const Vector4D<T>  &v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
}

template <typename T>
Vector4D<T>::~Vector4D ()
{
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
  return Vector4D<T>::Vector4D<T> (x + v.x, y + v.y, z + v.z, w + v.w);
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator - (const Vector4D<T> &v) const
{
  return Vector4D<T>::Vector4D<T> (x - v.x, y - v.y, z - v.z, w - v.w);
}

template <typename T>
Vector4D<T> 
Vector4D<T>::operator - () const 
{
 return Vector4D<T> (-x,-y, -z, -w); 
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
  T oneOverS = 1/s;
	x *= oneOverS; y *= oneOverS; z *= oneOverS; w *= oneOverS;
	return *this;
}

template <typename T>
void 
Vector4D<T>::normalize ()
{
  T magSq = x*x + y*y + z*z + w*w;
	if (magSq > 0)
	{
	  T oneOverMag = 1/sqrt (magSq);
		x *= oneOverMag;
		y *= oneOverMag;
    z *= oneOverMag;
    w *= oneOverMag;
	}
}

template <typename T>
T 
Vector4D<T>::dot (const Vector4D<T> &v) const
{
  return x*v.x + y*v.y + z*v.z + w*v.w;
}

// Non-member implementation

template<typename T> 
T 
Vec2DMagnitude (const Vector2D<T> &v)
{
  return sqrt (v.x*v.x + v.y*v.y);
}

template<typename T>
T 
Vec2DDistance (const Vector2D<T> &v, const Vector2D<T> &w)
{
  T dx = v.x - w.x;
  T dy = v.y - w.y;
  return sqrt (dx*dx + dy*dy);
}

template <typename T>
void 
Orthonormalize2D (Vector2D<T> &u, Vector2D<T> &v, Vector2D<T> &w)
{
/*
  Vector2D<T> tmp_u, tmp_v, tmp_w;
  tmp_u = u;
  tmp_v = v - ((tmp_u.dot(v)/pow(Vec2DMagnitude(tmp_u),2))*tmp_u);
  tmp_w = w - ((tmp_u.dot(w)/pow(Vec2DMagnitude(tmp_u),2))*tmp_u)
          -  ((tmp_v.dot(w)/pow(Vec2DMagnitude(tmp_v),2))*tmp_v);

  u = tmp_u/Vec2DMagnitude(u);
  v = tmp_v/Vec2DMagnitude(v);
  w = tmp_w/Vec2DMagnitude(w);
*/
}


template<typename T> 
T 
Vec3DMagnitude (const Vector3D<T> &v)
{
  return sqrt (v.x*v.x  + v.y*v.y + v.z*v.z);
}

template<typename T>
Vector3D<T> 
Vec3DCross (const Vector3D<T> &v, const Vector3D<T> &w)
{
  return Vector3D<T>::Vector3D (v.y*w.z - v.z*w.y,
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
  return sqrt (dx*dx + dy*dy + dz*dz);
}

template <typename T>
void 
Orthonormalize3D (Vector3D<T> &u, Vector3D<T> &v, Vector3D<T> &w)
{
  Vector3D<T> tmp_u, tmp_v, tmp_w;
  tmp_u = u;

  tmp_v = v - (tmp_u*(tmp_u.dot(v)/tmp_u.dot(tmp_u)));

  tmp_w = w - (tmp_u*(tmp_u.dot(w)/tmp_u.dot(tmp_u)))
          -  (tmp_v*(tmp_v.dot(w)/tmp_v.dot(tmp_v)));

  //u = tmp_u/Vec3DMagnitude(tmp_u);
  //v = tmp_v/Vec3DMagnitude(tmp_v);
  //w = tmp_w/Vec3DMagnitude(tmp_w);
  u = tmp_u;
  v = tmp_v;
  w = tmp_w;
}


template<typename T> 
T 
Vec4DMagnitude (const Vector4D<T> &v)
{
  return sqrt (v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

template<typename T>
T 
Vec4DDistance (const Vector4D<T> &v, const Vector4D<T> &k)
{
  T dx = v.x - k.x;
  T dy = v.y - k.y;
  T dz = v.z - k.z;
  T dw = v.w - k.w;
  return sqrt (dx*dx + dy*dy + dw*dw);
}

}
}
}

#endif
