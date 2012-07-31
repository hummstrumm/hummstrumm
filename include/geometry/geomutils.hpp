// -*- mode: c++; c-file-style: hummstrumm -*-
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
 * Geometry utility functions.
 *
 * @file    geometry/geomutils.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 */

#ifndef HUMMSTRUMM_ENGINE_GEOMETRY_UTILS
#define HUMMSTRUMM_ENGINE_GEOMETRY_UTILS

namespace hummstrumm
{
namespace engine
{
namespace geometry
{

using hummstrumm::engine::math::Vector3D;
using hummstrumm::engine::math::Vector2D;


/* @TODO Inline all functions? Performance gain? */

//// intersection ////

/**
 * Static intersection between two bounding boxes.
 * Return true if they intersect false otherwise.
 */
template <typename T>
bool
intersect (const AABBox3D<T> &box, const AABBox3D<T> &other)
{
  // don't intersect
  if (box.min.x > other.max.x) return false;
  if (box.max.x < other.min.x) return false;
  if (box.min.y > other.max.y) return false;
  if (box.max.y < other.min.y) return false;
  if (box.min.z > other.max.z) return false;
  if (box.max.z < other.min.z) return false;

  return true;
}

/**
 * Static intersection between two bounding spheres.
 * Return true if they intersect false otherwise.
 */
template <typename T>
bool
intersect (const BSphere3D<T> &sphere, const BSphere3D<T> &other)
{
  T _r = sphere.radius + other.radius;
  T _dr = _r * _r;
  T center_ =  other.center - sphere.center;
  if (center_ > _dr)
    return  false;
  
  return true;
}

/**
 * Static intersection between two planes.
 * Return true if they intersect false otherwise.
 */
template <typename T>
bool
intersect (const Plane3D<T> &plane, const Plane3D<T> &other)
{
  // Implement 
  return true;
}

/**
 * Static intersection between a bounding box and a plane.
 * Return 0 if they intersect, 1 if in front of plane and -1 
 * if in the back of plane.
 */
template <typename T>
short
intersect (const AABBox3D<T> &box, const Plane3D<T> &plane)
{
  T minD, maxD;
  if (plane.normal.x > 0)
  {
    minD = plane.normal.x*box.min.x; maxD = plane.normal.x*box.max.x;
  } else {
    minD = plane.normal.x*box.max.x; maxD = plane.normal.x*box.min.x;
  }

  if (plane.normal.y > 0) {
    minD += plane.normal.y*box.min.y; maxD += plane.normal.y*box.max.y;
  } else {
    minD += plane.normal.y*box.max.y; maxD += plane.normal.y*box.min.y;
  }

  if (plane.normal.z > 0) {
    minD += plane.normal.z*box.min.z; maxD += plane.normal.z*box.max.z;
  } else {
    minD += plane.normal.z*box.max.z; maxD += plane.normal.z*box.min.z;
  }

  if (minD > plane.d)
    return 1; //front of plane

  if (maxD < plane.d)
    return -1; //back of plane

  return 0; // intersect
}

/**
 * Static intersection between a bounding box and a sphere.
 * Return true if they intersect false otherwise.
 */
template <typename T>
bool
intersect (const AABBox3D<T> &box, const BSphere3D<T> &sphere, 
           const Vector3D<T> &point)
{
  if (Vec3DSqDistance(sphere.center, point) < sphere.radius * sphere.radius)
    return true;

  return false;
}

/**
 * Static intersection between a bounding sphere and a plane.
 * Return true if they intersect false otherwise.
 */
template <typename T>
bool
intersect (const BSphere3D<T> &sphere, const Plane3D<T> &plane)
{
  // Implement
  return false;
}

///// contain /////

/**
 * Check if a bounding box totally contains another 
 * bounding box.
 * Return true if totally contains false otherwise.
 */
template <typename T>
bool
contains (const AABBox3D<T> &box, const AABBox3D<T> &other)
{
  if (box.min.x <= other.min.x && box.min.y <= other.min.y &&
      box.min.z <= other.min.z && box.max.x >= other.max.x &&
      box.max.y >= other.max.y && box.max.z >= other.max.z)
      return true; // box contains other

  return false;
}

/**
 * Check if a bounding sphere totally contains another 
 * bounding sphere.
 * Return true if the totally contains false otherwise.
 */
template <typename T>
bool
contains (const BSphere3D<T> &sphere, const BSphere3D<T> &other)
{
  T center_ =  other.center - sphere.center;
  if (center_ <= sphere.radius)
    return true;
  return false;
}

/**
 * Check if a bounding box totally contains a sphere.
 * Return true totally contains false otherwise.
 */
template <typename T>
bool
contains (const AABBox3D<T> &box, const BSphere3D<T> &sphere)
{
  if (box.min.x <= (sphere.center.x - sphere.radius) &&
      box.max.x >= (sphere.center.x + sphere.radius) &&
      box.min.y <= (sphere.center.y - sphere.radius) &&
      box.max.y >= (sphere.center.y + sphere.radius) &&
      box.min.z <= (sphere.center.z - sphere.radius) &&
      box.max.z >= (sphere.center.z + sphere.radius)) return true;

  return false;
}

/**
 * Check if a sphere totally contains a bounding box.
 * Return true if totally contains false otherwise.
 */
template <typename T>
bool
contains (const BSphere3D<T> &sphere,const AABBox3D<T> &box)
{
  // Implement
  return false;
}

/**
 * Check if a sphere contains a point in 3D space.
 * Return true if contains false otherwise.
 */
template <typename T>
bool
contains (const BSphere3D<T> &sphere,const Vector3D<T> &point)
{
  return Vec3DSqMagnitude(point - sphere.center) <= sphere.radius*sphere.radius;
}

/**
 * Check if a bounding box contains a point in 3D space.
 * Return true if contains false otherwise.
 */
template <typename T>
bool
contains (const AABBox3D<T> &box, const Vector3D<T> &point)
{
  return (point.x >= box.min.x) && (point.y <= box.max.x) &&
         (point.y >= box.min.y) && (point.y <= box.max.y) &&
         (point.z >= box.min.z) && (point.z <= box.max.z);
}

/**
 * Check if a bounding box totally contains another 
 * bounding box.
 * Return true if totally contains false otherwise.
 */
template <typename T>
bool
contains (const AABBox2D<T> &box, const AABBox2D<T> &other)
{
  if (box.min.x <= other.min.x && box.min.y <= other.min.y &&
      box.max.x >= other.max.x && box.max.y >= other.max.y)
      return true; // box contains other

  return false;
}

/**
 * Check if a bounding box contains a point in 2D space.
 * Return true if contains false otherwise.
 */
template <typename T>
bool
contains (const AABBox2D<T> &box, const Vector2D<T> &point)
{
  return (point.x >= box.min.x) && (point.y <= box.max.x) &&
         (point.y >= box.min.y) && (point.y <= box.max.y);
}


}
}
}


#endif
