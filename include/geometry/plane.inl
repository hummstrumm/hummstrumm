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


#ifndef HUMMSTRUMM_ENGINE_GEOMETRY_PLANE_INL
#define HUMMSTRUMM_ENGINE_GEOMETRY_PLANE_INL

#include <stdexcept>

namespace hummstrumm
{
namespace engine
{
namespace geometry
{


template <typename T>
Plane3D<T>::Plane3D ()
  : normal (0, 1, 0),
    d (0)
{}


template <typename T>
Plane3D<T>::Plane3D (const hummstrumm::engine::math::Vector3D<T> &norm,
                     const T &d)
  : normal (norm),
    d (d)
{}


template <typename T>
Plane3D<T>::Plane3D (const T &a, const T &b, const T &c, const T &d)
  : normal (a, b, c),
    d (d)
{}


template <typename T>
Plane3D<T>::Plane3D (const Plane3D<T> &p)
  : normal (p.normal), d (p.d)
{}


template <typename T>
bool
Plane3D<T>::operator== (const Plane3D<T> &p)
  const
{
  return d == p.v && normal == p.normal;
}


template <typename T>
bool
Plane3D<T>::operator!= (const Plane3D<T> &p)
  const
{
  return d != p.v || normal != p.normal;
}


template <typename T>
Plane3D<T>::Plane3D (const hummstrumm::engine::math::Vector3D<T> &p1,
                     const hummstrumm::engine::math::Vector3D<T> &p2,
                     const hummstrumm::engine::math::Vector3D<T> &p3)
{
  hummstrumm::engine::math::Vector3D<T> e3 = p2 - p1;
  hummstrumm::engine::math::Vector3D<T> e1 = p3 - p1;

  normal = Vec3DCross (e3, e1);
  d      = Vec3DDot (p1, normal);
}


template <typename T>
Plane3D<T>::Plane3D (const hummstrumm::engine::math::Vector3D<T> &p1,
                     const hummstrumm::engine::math::Vector3D<T> &norm)
  : normal (norm)
{
  d = Vec3DDot (p1, norm);
}


template <typename T>
void
Plane3D<T>::Normalize ()
{
  T normalMag = Vec3DMagnitude(normal);
  if (normalMag == 0)
    throw std::domain_error ("Plane division by zero.");

  normal /= normalMag;
  d      /= normalMag;
}


template <typename T>
T
DistanceTo (const Plane3D<T>  &plane,
            const hummstrumm::engine::math::Vector3D<T> &p)
{
  return Vec3DDot (p, plane.normal) - plane.d;
}


template <typename T>
std::ostream &
operator<< (std::ostream &out, Plane3D<T> plane)
{
  if (plane.normal.coord.x || (!plane.normal.coord.y && !plane.normal.coord.z))
    out << plane.normal.coord.x << "x";

  if (plane.normal.coord.y < 0)
    out << plane.normal.coord.y << "y";
  else if (plane.normal.coord.y > 0)
    out << "+" << plane.normal.coord.y << "y";

  if (plane.normal.coord.z < 0)
    out << plane.normal.coord.z << "z";
  else if (plane.normal.coord.z > 0)
    out << "+" << plane.normal.coord.z << "z";

  out << "=" << plane.d;

  return out;
}


template <typename T>
std::istream &
operator>> (std::istream &in, Plane3D<T> &plane)
{
  plane = Plane3D<T> (0, 0, 0, 0);

  while (in.peek () != '=')
    {
      T temp;
      in >> temp;
      switch (in.get ())
        {
        case 'x':
          plane.normal.coord.x += temp;
          break;
        case 'y':
          plane.normal.coord.y += temp;
          break;
        case 'z':
          plane.normal.coord.z += temp;
          break;
        }
    }

  in.get ();
  in >> plane.d;

  return in;
}


}
}
}

#endif // HUMMSTRUMM_ENGINE_GEOMETRY_PLANE_INL
