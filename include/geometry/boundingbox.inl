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

#ifndef HUMMSTRUMM_ENGINE_AABBOX_INL
#define HUMMSTRUMM_ENGINE_AABBOX_INL

#include <stdexcept>

namespace hummstrumm
{
namespace engine
{
namespace geometry
{
template <typename T>
AABBox3D<T> &
AABBox3D<T>::operator = (const AABBox3D<T> &box)
{
  bmin = box.bmin;
  bmax = box.bmax;
  return *this;
}

template <typename T>
bool
AABBox3D<T>::operator == (const AABBox3D<T> &box) const
{
  return bmin == box.bmin && bmax == box.bmax;
}

template <typename T>
bool
AABBox3D<T>::operator != (const AABBox3D<T> &box) const
{
  return bmin != box.bmin || bmax != box.bmax;
}

template <typename T>
Vector3D<T>
AABBox3D<T>::Size() const
{
  return bmax - bmin;
}

template <typename T>
T
AABBox3D<T>::SizeX() const
{
  return bmax.x - bmin.x;
}

template <typename T>
T
AABBox3D<T>::SizeY() const
{
  return bmax.y - bmin.y;
}

template <typename T>
T
AABBox3D<T>::SizeZ() const
{
  return bmax.z - bmin.z;
}

template <typename T>
Vector3D<T>
AABBox3D<T>::Center() const
{
  return (bmin + bmax)*0.5;
}

template <typename T>
void
AABBox3D<T>::Empty()
{
  bmax.x = bmax.y = bmax.z = 0;
  bmin.x = bmin.y = bmin.z = 0;
}

template <typename T>
bool
AABBox3D<T>::IsEmpty() const
{
  return bmax == bmin;
}

template <typename T>
Vector3D<T>
AABBox3D<T>::GetCorner(unsigned short i) const
{
  if (i < 0 || i > 7)
    throw std::out_of_range ("Corner out of range.");

  return Vector3D<T>(
    (i & 1) ? bmax.x : bmin.x,
    (i & 2) ? bmax.y : bmin.y,
    (i & 4) ? bmax.z : bmin.z
  );
}

template <typename T>
T
AABBox3D<T>::Volume() const
{
  return ((bmax.x - bmin.x) * (bmax.y - bmin.y) * (bmax.z - bmin.z));
}

template <typename T>
T
AABBox3D<T>::Area() const
{
  T x = bmax.x - bmin.x;
  T y = bmax.y - bmin.y;
  T z = bmax.z - bmin.z;
  return  2 * (x*y + x*z + y*z);
}

// Bounding box in 2D space

template <typename T>
AABBox2D<T> &
AABBox2D<T>::operator = (const AABBox2D<T> &box)
{
  bmin = box.bmin;
  bmax = box.bmax;
  return *this;
}

template <typename T>
bool
AABBox2D<T>::operator == (const AABBox2D<T> &box) const
{
  return bmin == box.bmin && bmax == box.bmax;
}

template <typename T>
bool
AABBox2D<T>::operator != (const AABBox2D<T> &box) const
{
  return bmin != box.bmin || bmax != box.bmax;
}

template <typename T>
Vector2D<T>
AABBox2D<T>::Size() const
{
  return bmax - bmin;
}

template <typename T>
T
AABBox2D<T>::SizeX() const
{
  return bmax.x - bmin.x;
}

template <typename T>
T
AABBox2D<T>::SizeY() const
{
  return bmax.y - bmin.y;
}

template <typename T>
Vector2D<T>
AABBox2D<T>::Center() const
{
  return (bmin + bmax)*0.5;
}

template <typename T>
void
AABBox2D<T>::Empty()
{
  bmax.x = bmax.y = 0;
  bmin.x = bmin.y = 0;
}

template <typename T>
bool
AABBox2D<T>::IsEmpty() const
{
  return bmax == bmin;
}

template <typename T>
Vector2D<T>
AABBox2D<T>::GetCorner(unsigned short i) const
{
  if (i < 0 || i > 3)
    throw std::out_of_range ("Corner out of range.");

  return Vector2D<T>(
    (i & 1) ? bmax.x : bmin.x,
    (i & 2) ? bmax.y : bmin.y
  );
}

template <typename T>
T
AABBox2D<T>::Area() const
{
  T x = bmax.x - bmin.x;
  T y = bmax.y - bmin.y;
  return x*y;
}


// non member AABBox3D implementations 

template <typename T>
bool
AABBox3ContainsPoint (const AABBox3D<T> &box, const Vector3D<T> &plane)
{
  return contains (box,plane);
}

template <typename T>
void
AABBox3AddPoint (AABBox3D<T> &box, const Vector3D<T> &plane)
{
  if (plane.x < box.bmin.x) box.bmin.x = plane.x;
  if (plane.x > box.bmax.x) box.bmax.x = plane.x;
  if (plane.y < box.bmin.y) box.bmin.y = plane.y;
  if (plane.y > box.bmax.y) box.bmax.y = plane.y;
  if (plane.z < box.bmin.z) box.bmin.z = plane.z;
  if (plane.z > box.bmax.z) box.bmax.z = plane.z;
}

template <typename T>
void
AABBox3AddBox (AABBox3D<T> &box, const AABBox3D<T> &other)
{
  if (other.bmin.x < box.bmin.x) box.bmin.x = other.bmin.x;
  if (other.bmin.x > box.bmax.x) box.bmax.x = other.bmin.x;
  if (other.bmin.y < box.bmin.y) box.bmin.y = other.bmin.y;
  if (other.bmin.y > box.bmax.y) box.bmax.y = other.bmin.y;
  if (other.bmin.z < box.bmin.z) box.bmin.z = other.bmin.z;
  if (other.bmin.z > box.bmax.z) box.bmax.z = other.bmin.z;
}

template <typename T>
void 
AABBox3AddSphere (AABBox3D<T> &box, const BSphere3D<T> &sphere)
{
  T sxn = sphere.center.x - sphere.radius;
  T syn = sphere.center.y - sphere.radius;
  T szn = sphere.center.z - sphere.radius;
  T sxp = sphere.center.x + sphere.radius;
  T syp = sphere.center.y + sphere.radius;
  T szp = sphere.center.z + sphere.radius;
  if (sxn < box.bmin.x) box.bmin.x = sxn;
  if (syn < box.bmin.y) box.bmin.y = syn;
  if (szn < box.bmin.z) box.bmin.z = szn;
  if (sxp > box.bmax.x) box.bmax.x = sxp;
  if (syp > box.bmax.y) box.bmax.y = syp;
  if (szp > box.bmax.z) box.bmax.z = szp;
}


template <typename T>
short 
AABBox3IntersectBox (const AABBox3D<T> &box, const AABBox3D<T> &other)
{
  if (contains(box,other))
    return 1;

  if (intersect(box,other))
    return 0;

  return -1; // no intersection
}

template <typename T>
short 
AABBox3IntersectSphere (const AABBox3D<T> &box, const BSphere3D<T> &sphere)
{
  if (contains (box,sphere))
    return 1;
 
  Vector3D<T> closestPoint_ = AABBox3ClosestPoint (box, sphere.center);
  // intersect
  if (intersect(box,sphere,closestPoint_))
    return 0;
  
  return -1; // no intersection
}

template <typename T>
short AABBox3IntersectPlane (const AABBox3D<T> &box, const Plane3D<T> &plane)
{
  return intersect(box,plane);
}

template <typename T>
Vector3D<T> 
AABBox3ClosestPoint (const AABBox3D<T> &box, const Vector3D<T> &point)
{
  Vector3D<T> closestPoint;

  if (point.x < box.bmin.x)
    closestPoint.x = box.bmin.x;
  else if (point.x > box.bmax.x)
    closestPoint.x = box.bmax.x;
  else
    closestPoint.x = point.x;

  if (point.y < box.bmin.y)
    closestPoint.y = box.bmin.y;
  else if (point.y > box.bmax.y)
    closestPoint.y = box.bmax.y;
  else
    closestPoint.y = point.y;

  if (point.z < box.bmin.z)
    closestPoint.z = box.bmin.z;
  else if (point.z > box.bmax.z)
    closestPoint.z = box.bmax.z;
  else
    closestPoint.z = point.z;

  return closestPoint;
}


// non member AABBox2D implementations 

template <typename T>
bool
AABBox2ContainsPoint (const AABBox2D<T> &box, const Vector2D<T> &plane)
{
  return contains (box,plane);
}

template <typename T>
void
AABBox2AddPoint (AABBox2D<T> &box, const Vector2D<T> &plane)
{
  if (plane.x < box.bmin.x) box.bmin.x = plane.x;
  if (plane.x > box.bmax.x) box.bmax.x = plane.x;
  if (plane.y < box.bmin.y) box.bmin.y = plane.y;
  if (plane.y > box.bmax.y) box.bmax.y = plane.y;
}

template <typename T>
void
AABBox2AddBox (AABBox2D<T> &box, const AABBox2D<T> &other)
{
  if (other.bmin.x < box.bmin.x) box.bmin.x = other.bmin.x;
  if (other.bmin.x > box.bmax.x) box.bmax.x = other.bmin.x;
  if (other.bmin.y < box.bmin.y) box.bmin.y = other.bmin.y;
  if (other.bmin.y > box.bmax.y) box.bmax.y = other.bmin.y;
}

template <typename T>
short 
AABBox2IntersectBox (const AABBox2D<T> &box, const AABBox2D<T> &other)
{
  if (contains(box,other))
    return 1;

  if (intersect(box,other))
    return 0;
  
  return -1;
}

template <typename T>
Vector2D<T> 
AABBox2ClosestPoint (const AABBox2D<T> &box, const Vector2D<T> &point)
{
  Vector2D<T> closestPoint;

  if (point.x < box.bmin.x)
    closestPoint.x = box.bmin.x;
  else if (point.x > box.bmax.x)
    closestPoint.x = box.bmax.x;
  else
    closestPoint.x = point.x;

  if (point.y < box.bmin.y)
    closestPoint.y = box.bmin.y;
  else if (point.y > box.bmax.y)
    closestPoint.y = box.bmax.y;
  else
    closestPoint.y = point.y;

  return closestPoint;
}

};
};
};

#endif //HUMMSTRUMM_ENGINE_AABBOX_INL
