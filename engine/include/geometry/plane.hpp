// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2011, the people listed in the AUTHORS file.
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
 * Class(es) to represent a plane. 
 *
 * @file    geometry/plane.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 *
 */

#ifndef HUMMSTRUMM_ENGINE_GEOMETRY_PLANE
#define HUMMSTRUMM_ENGINE_GEOMETRY_PLANE

namespace hummstrumm
{
namespace engine
{
namespace geometry
{

using hummstrumm::engine::math::Vector3D;

/**
 * A plane in three dimensions.  Planes are flat surfaces that extend infinitely
 * along two of their relative axis. In three dimensions, the implicit form of a
 * plane is given* by all points \f$ p = (x,y,z)\f$ that satify the plane
 * equation:
 *
 * \f$ ax + by + cz = d\f$
 *
 * \f$ p\cdot n = d\f$ where \f$ n = <a,b,c>\f$, and it's called the plane
 * normal.
 *
 * @version 0.3
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 * @since   0.2
 */
template <typename T>
class Plane3D
{
  public:
    /// The normal vector of the plane.
    Vector3D<T> normal;
    /// The value d in the plane equation.
    T d;

    /**
     * Constructs a plane.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     */
    Plane3D () : normal(0,1,0), d(0) {}
  
    /**
     * Constructs a plane from a normal and d.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     * 
     * @param [in] norm Plane normal
     * @param [in] d    From the above equation.
     */
    Plane3D (const Vector3D<T> &norm, const T &d) 
      : normal(norm), d(d) {}
  
    /**
     * Constructs a plane from given components.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     * 
     * @param [in] a Component a of normal.
     * @param [in] b Component b of normal.
     * @param [in] c Component c of normal.
     * @param [in] d Component d.
     */
    Plane3D (const T &a, const T &b, const T &c, const T &d) 
      : normal(a,b,c), d(d) {}
  
    /**
     * Constructs a plane from three noncollinear points.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     * 
     * @param [in] p1 A point given as vector.
     * @param [in] p2 Another point given as vector.
     * @param [in] p3 Another point given as vector.
     */
    Plane3D (const Vector3D<T> &p1, 
             const Vector3D<T> &p2, 
             const Vector3D<T> &p3);

    /**
     * Constructs a plane from a point and a normal.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     * 
     * @param [in] p1 A point given as vector.
     * @param [in] norm Plane normal.
     */
    Plane3D (const Vector3D<T> &p1, 
             const Vector3D<T> &norm);

    /**
     * Copy constructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] p A plane.
     */
    Plane3D (const Plane3D<T> &p): normal(p.normal), d(p.d) {}

    /**
     * Destructs a plane.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     */
    ~Plane3D () {}

     /**
     * Assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] p A plane.
     *
     * @return This plane.
     */
    Plane3D<T> &operator = (const Plane3D<T> &p);

     /**
     * Compare if two plane3D object are equal.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] p A plane.
     *
     * @return Whether the planes are equal.
     */
    bool operator == (const Plane3D<T> &p) const;

     /**
     * Inequality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] p A plane.
     *
     * @return Whether the planes are different.
     */
    bool operator != (const Plane3D<T> &p) const;

    /**
     * Normalize the plane equation.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     */
    void Normalize();
   
};


// implementation
template <typename T>
Plane3D<T>::Plane3D (const Vector3D<T> &p1,
                     const Vector3D<T> &p2,
                     const Vector3D<T> &p3)
{
  Vector3D<T> e3 = p2 - p1;
  Vector3D<T> e1 = p3 - p1;

  normal = Vec3DCross(e3,e1);

  d = Vec3DDot(p1,normal);
}

template <typename T>
Plane3D<T>::Plane3D (const Vector3D<T> &p1, 
                     const Vector3D<T> &norm): normal(norm)
{
  d = Vec3DDot(p1,norm); 
}

template <typename T>
Plane3D<T> &
Plane3D<T>::operator = (const Plane3D<T> &p)
{
  d = p.d;
  normal = p.normal;
  return *this;
}

template <typename T>
bool
Plane3D<T>::operator == (const Plane3D<T> &p) const
{
  return d == p.v && normal == p.normal;
}

template <typename T>
bool
Plane3D<T>::operator != (const Plane3D<T> &p) const
{
  return d != p.v || normal != p.normal;
}

template <typename T>
void
Plane3D<T>::Normalize ()
{
  T normalMag = Vec3DMagnitude(normal);
  if (normalMag == 0)
    HUMMSTRUMM_THROW (DivisionByZero,"Plane division by zero.");

  normal /= normalMag;
  d /= normalMag;
}

// non member functions

/**
  * Distance from point to plane.
  *
  * @author Ricardo Tiago <Rtiago@gmail.com>
  * @date 2010-05-30
  * @since 0.3
  *
  * @param [in] plane A normalized plane.
  * @param [in] p     A point not necessarily lying on the plane.
  *
  * @see Plane3D
  */
template <typename T>
T
PlaneDistanceTo(const Plane3D<T> &plane, const Vector3D<T> &p);

// implementation of non member functions 

template <typename T>
T
PlaneDistanceTo(const Plane3D<T> &plane, const Vector3D<T> &p)
{
  return Vec3DDot(p,plane.normal) - plane.d;
}




  
}
}
}

#endif