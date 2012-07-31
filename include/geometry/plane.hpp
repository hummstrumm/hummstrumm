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

/**
 * Class to represent a plane.
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

/**
 * A plane in three dimensions.  Planes are flat surfaces that extend infinitely
 * along two of their relative axis. In three dimensions, the implicit form of a
 * plane is given by all points \f$ p = (x,y,z)\f$ that satify the plane
 * equation: \f[ax + by + cz = d\f]
 *
 * \f$ p\cdot n = d\f$, where \f$ n = <a,b,c>\f$, called the plane normal.
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
    hummstrumm::engine::math::Vector3D<T> normal;
    /// The value d in the plane equation.
    T d;

    /**
     * Constructs a plane.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     */
    inline Plane3D ();

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
    inline Plane3D (const hummstrumm::engine::math::Vector3D<T> &norm,
                    const T &d);

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
    inline Plane3D (const T &a, const T &b, const T &c, const T &d);

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
    Plane3D (const hummstrumm::engine::math::Vector3D<T> &p1,
             const hummstrumm::engine::math::Vector3D<T> &p2,
             const hummstrumm::engine::math::Vector3D<T> &p3);

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
    Plane3D (const hummstrumm::engine::math::Vector3D<T> &p1,
             const hummstrumm::engine::math::Vector3D<T> &norm);

    /**
     * Copy constructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] p A plane.
     */
    inline Plane3D (const Plane3D<T> &p);

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
    inline bool operator== (const Plane3D<T> &p) const;

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
    inline bool operator!= (const Plane3D<T> &p) const;

    /**
     * Normalize the plane equation.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     */
    void Normalize ();

};


/**
 * Distance from point to plane.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date   2010-05-30
 * @since  0.3
 *
 * @param [in] plane A normalized plane.
 * @param [in] p     A point not necessarily lying on the plane.
 *
 * @see Plane3D
 */
template <typename T>
T 
DistanceTo (const Plane3D<T> &plane,
            const hummstrumm::engine::math::Vector3D<T> &p);

/**
 * Prints a plane to an output stream.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-04-28
 * @since  0.6
 */
template <typename T>
std::ostream &
operator<< (std::ostream &, Plane3D<T>);
/**
 * Retrieves a plane from an output stream.  The plane must be specified in the
 * form \f$ ax+by+cz=d\f$, where the + symbols can be replaced by - symbols if
 * the following coefficient is negative.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-04-28
 * @since  0.6
 */
template <typename T>
std::istream &
operator>> (std::istream &, Plane3D<T> &);


}
}
}

#endif
