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

#ifndef HUMMSTRUMM_ENGINE_MATH_MATRIX_INL
#define HUMMSTRUMM_ENGINE_MATH_MATRIX_INL

#include <stdexcept>


namespace hummstrumm
{
namespace engine
{
namespace math
{

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
    throw std::domain_error ("Matrix division by zero.");
  T oneOverS = 1/s;
  return Matrix2D<T> (mat2[0]*oneOverS, mat2[1]*oneOverS);
}

template <typename T>
Vector2D<T> 
Matrix2D<T>::operator [] (const unsigned short r) const
{
  if ( r >= 2 )
    throw std::out_of_range ("Invalid matrix line.");

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
    throw std::domain_error ("Matrix division by zero.");

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
    throw std::domain_error ("Matrix division by zero.");

  T oneOverS = 1/s;
  return Matrix3D<T> (mat3[0]*oneOverS, mat3[1]*oneOverS, mat3[2]*oneOverS);
}

template <typename T>
Vector3D<T> 
Matrix3D<T>::operator [] (const unsigned short r) const
{
  if ( r >= 3 )
    throw std::out_of_range ("Invalid matrix line.");

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
    throw std::domain_error ("Matrix division by zero.");

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
    throw std::domain_error ("Matrix division by zero.");

  T oneOverS = 1/s;
  return Matrix4D<T> (mat4[0]*oneOverS, mat4[1]*oneOverS,
                      mat4[2]*oneOverS, mat4[3]*oneOverS);
}

template <typename T>
Vector4D<T> 
Matrix4D<T>::operator [] (const unsigned short r) const
{
  if ( r >= 4 )
    throw std::out_of_range ("Invalid matrix line.");

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
    throw std::domain_error ("Matrix division by zero.");

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
    throw std::logic_error ("Matrix determinant is zero.");
 
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
    throw std::logic_error ("Matrix determinant is zero.");

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
    throw std::domain_error ("Matrix determinant zero.");

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

};
};
};

#endif //HUMMSTRUMM_ENGINE_MATH_MATRIX_INL
