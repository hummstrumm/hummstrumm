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

#ifndef HUMMSTRUMM_ENGINE_BOUNDINGSPHERE_INL
#define HUMMSTRUMM_ENGINE_BOUNDINGSPHERE_INL

namespace hummstrumm
{
namespace engine
{
namespace geometry
{

template <typename T>
BSphere3D<T> &
BSphere3D<T>::operator = (const BSphere3D<T> &bsphere)
{
  center = bsphere.center;
  radius = bsphere.radius;
  return *this;
}

template <typename T>
bool
BSphere3D<T>::operator == (const BSphere3D<T> &bsphere) const
{
  return center == bsphere.center && radius == bsphere.radius;
}

template <typename T>
bool
BSphere3D<T>::operator != (const BSphere3D<T> &bsphere) const
{
  return center != bsphere.center || radius != bsphere.radius;
}

template <typename T>
void
BSphere3D<T>::Empty()
{
  radius = 0;
}

template <typename T>
bool
BSphere3D<T>::IsEmpty() const
{
  return radius <= 0;
}

template <typename T>
T
BSphere3D<T>::Volume() const
{
  return (4/3)*hummstrumm::engine::math::PI*radius*radius*radius; 
}

template <typename T>
T
BSphere3D<T>::SurfaceArea() const
{
  return 4*hummstrumm::engine::math::PI*radius*radius;
}

// non-member implementation

template <typename T>
bool
BSphere3ContainsPoint (const BSphere3D<T> &bsphere, const Vector3D<T> &point)
{
  return contains(bsphere, point);
}

template <typename T>
short
BSphere3IntersectSphere (const BSphere3D<T> &bsphere, const BSphere3D<T> &other)
{
  if (contains(bsphere,other))
    return 1;

  if (intersect(bsphere,other))
    return 0;

  return -1;
}

template <typename T>
void
BSphere3AddPoint (BSphere3D<T> &bsphere, const Vector3D<T> &point)
{
  if (bsphere.IsEmpty())
  {
    bsphere.center = point;
    bsphere.radius = Vec3DMagnitude(point);
  }
  else
  {
    if (!BSphere3ContainsPoint (bsphere,point))
    {
      Vector3D<T> _v = point - bsphere.center;
      T _r = Vec3DMagntiude(_v);
      Vector3D<T> common_point = bsphere.center - bsphere.radius*(_v/_r);
      bsphere.center = (common_point + point)*0.5;
      bsphere.radius = _r;
    }
  }
}

template <typename T>
void
BSphere3AddSphere (BSphere3D<T> &bsphere, const BSphere3D<T> &other)
{
  if (bsphere.IsEmpty())
  {
    bsphere.center = other.center;
    bsphere.radius = other.radius;
  }
  else
  {
    T centerDistSpheres = Vec3DMagnitude(bsphere.center - other.center);

    // Sphere other is inside sphere bsphere.
    if (centerDistSpheres + other.radius <= bsphere.radius)
      return;
    // Sphere other contains sphere bsphere.
    else if (centerDistSpheres + bsphere.radius <= other.radius)
    {
      bsphere.center = other.center;
      bsphere.radius = other.radius;
    }
    // Sphere bsphere must expand to contain sphere other.
    else
    {
      T _r = (bsphere.radius + centerDistSpheres + other.radius)*0.5;
      T _ratio = (_r - bsphere.radius) / centerDistSpheres;
      bsphere.center = (other.center - bsphere.center)*_ratio;
      bsphere.radius = _r;
    }
  }
}

template <typename T>
void
BSphere3AddBox (BSphere3D<T> &bsphere, const AABBox3D<T> &box)
{
  if (!box.IsEmpty())
  {
    if (!bsphere.IsEmpty())
    {
      for (unsigned short i = 0; i < 8; i++)
      {
        BSpere3AddPoint(bsphere,box.GetCorner(i));
      } 
    }
    else
    {
      bsphere.center = box.Center();
      bsphere.radius = Vec3DMagnitude(box.max - box.min)*0.25; // wrong
    }
  }
}

};
};
};

#endif //HUMMSTRUMM_ENGINE_BSPHERE_INL
