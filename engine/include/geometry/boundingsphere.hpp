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
 * Defines and implements a bounding sphere.
 *
 * @file    geometry/boundingsphere.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 *
 */
#ifndef HUMMSTRUMM_ENGINE_BSPHERE
#define HUMMSTRUMM_ENGINE_BSPHERE

namespace hummstrumm
{
namespace engine
{
namespace geometry
{

using hummstrumm::engine::math::Vector3D;

template <typename T>
class BSphere3D
{
  public:
    Vector3D<T> center;
    T radius;

    /**
     * Constructs an empty bounding sphere.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     */
    BSphere3D (): center (0,0,0), radius (0) {}
    
    /**
     * Constructs a bounding sphere a given center and radius.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param c Center of the bounding sphere
     * @param r Radius of the bounding sphere.
     */
    BSphere3D (const Vector3D<T> &c, const T &r)
      : center(c), radius(r) {}

    /**
     * Constructs a boungin sphere from given coordinates.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param centerx Sphere center coordinate x.
     * @param centery Sphere center coordinate y.
     * @param centerz Sphere center coordinate z.
     * @param r Sphere radius.
     */
    BSphere3D (const T &centerx, const T &centery, const T &centerz,
               const T &r)
      : center(centerx, centery, centerz), radius(r) {}

    /**
     * Copy Constructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param bsphere A bounding sphere.
     */
    BSphere3D (const BSphere3D<T> &bsphere): center(bsphere.center), radius(bsphere.radius) {}

    /**
     * Destructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     */
    ~BSphere3D () {}

    /**
     * Assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param bsphere A bounding sphere.
     *
     * @return This bounding sphere.
     */
    BSphere3D<T> &operator = (const BSphere3D<T> &bsphere);

     /**
     * Equality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param bsphere A bounding spheres.
     *
     * @return Whether the two bounding spheres are equal.
     */
    bool operator == (const BSphere3D<T> &bsphere) const;

     /**
     * Inequality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param bsphere A bounding spheres.
     *
     * @return Whether the two bounding spheres are different.
     */
    bool operator != (const BSphere3D<T> &bsphere) const;

    /**
     * Empty the bounding sphere.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     */
    void Empty();

    /**
     * Check if bounding sphere is empty.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return Whether the sphere is empty.
     */
    bool IsEmpty() const;

    /**
     * Volume of the bounding sphere.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return Volume of this sphere.
     */
    T Volume() const;

    /**
     * Surface area of this bounding sphere.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return Surface area of the bounding sphere.
     */
    T SurfaceArea() const;

};


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


// Non member functions

/**
 * Check if the bounding sphere contains a point.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param bsphere A bounding sphere.
 * @param point A point.
 *
 * @return Whether the point is inside the sphere.
 */
template <typename T>
bool BSphere3ContainsPoint (const BSphere3D<T> &bsphere, const Vector3D<T> &point);

/**
 * Check if two bounding spheres intersect. 
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param bsphere A bounding sphere.
 * @param other Another bounding sphere.
 *
 * @return -1 if they don't intersect, 1 if bsphere
 * contains other and 0 if they intersect.
 */
template <typename T>
short BSphere3IntersectSphere (const BSphere3D<T> &bsphere, const BSphere3D<T> &other);

/**
 * Add a point to the bounding sphere. 
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param bsphere A bounding sphere.
 * @param point A point.
 *
 * @note Moves bounding sphere center.
 */
template <typename T>
void BSphere3AddPoint (BSphere3D<T> &bsphere, const Vector3D<T> &point);

/**
 * Add bounding sphere o to bounding sphere bsphere.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param bsphere A bounding sphere.
 * @param other Another bounding sphere.
 *
 */
template <typename T>
void BSphere3AddSphere (BSphere3D<T> &bsphere, const BSphere3D<T> &other);

/**
 * Add bounding box other to bounding sphere.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param bsphere A bounding sphere.
 * @param box A bounding box.
 *
 */
template <typename T>
void BSphere3AddBox (BSphere3D<T> &bsphere, const AABBox3D<T> &box);

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



}
}
}

#endif
