// -*- c++ -*-
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
 * Class(es) to represent a line segment.
 *
 * @file    geometry/segment.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 *
 */

#ifndef HUMMSTRUMM_ENGINE_GEOMETRY_SEGMENT
#define HUMMSTRUMM_ENGINE_GEOMETRY_SEGMENT

namespace hummstrumm
{
namespace engine
{
namespace geometry
{

using hummstrumm::engine::math::Vector2D;
using hummstrumm::engine::math::Vector3D;

/**
 * Represents a segment of a line on a plane.  This segment is defined by a
 * starting point and an an ending point.
 *
 * @version 0.3
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-05-10
 * @since   0.3
 */
template <typename T>
class Segment2D
{
  public:
    /// The starting point of the segment.
    Vector2D<T> start;
    /// The ending point of the segment.
    Vector2D<T> end;

    /**
     * Constructs a line segment.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     */
    Segment2D (): start(0,0), end(1,0) {}

    /**
     * Constructs a line segment from point coordinates.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     *
     * @param [in] x1 x coordinate of start point.
     * @param [in] y1 y coordinate of start point.
     * @param [in] x2 x coordinate of end point.
     * @param [in] y2 y coordinate of end point.
     */
    Segment2D (const T &x1, const T &y1, const T &x2, const T &y2)
      : start(x1,y1), end(x2,y2) {}

    /**
     * Constructs a line segment from two points given as vectors.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     * 
     * @param [in] s Start point as a vector.
     * @param [in] e End point as a vector.
     */
    Segment2D (const Vector2D<T> &s, const Vector2D<T> &e): start(s), end(e) {}

    /**
     * Copy constructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     *
     * @param [in] s A line segment.
     */
    Segment2D (const Segment2D<T> &s): start(s.start), end(s.end) {}

    /**
     * Destructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     */
    ~Segment2D () {}

    /**
     * Assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     *
     * @param [in] s A line segment.
     * 
     * @return This segment.
     */
    Segment2D<T> &operator = (const Segment2D<T> &s);

    /**
     * Equality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     *
     * @param [in] s A line segment.
     * 
     * @return Whether the segments are equal.
     */
    bool operator == (const Segment2D<T> &s);

    /**
     * Inequality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     *
     * @param [in] s A line segment.
     * 
     * @return Whether the segments are different.
     */
    bool operator != (const Segment2D<T> &s);

};

/**
 * Represents a segment of a line in space.  This segment is defined by a
 * starting point and an an ending point.
 *
 * @version 0.3
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-05-10
 * @since   0.3
 */
template <typename T>
class Segment3D
{
  public:
    /// The starting point of the segment.
    Vector3D<T> start;
    /// The ending point of the segment.
    Vector3D<T> end;

    /**
     * Constructs a line segment.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     */
    Segment3D (): start(0,0,0), end(1,1,1) {}

    /**
     * Constructs a line segment from point coordinates.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     *
     * @param [in] x1 x coordinate of start point.
     * @param [in] y1 y coordinate of start point.
     * @param [in] z1 z coordinate of start point.
     * @param [in] x2 x coordinate of end point.
     * @param [in] y2 y coordinate of end point.
     * @param [in] z2 z coordinate of end point.
     */
    Segment3D (const T &x1, const T &y1, const  T &z1, const T &x2, 
               const T &y2, const T &z2)
      : start(x1,y1,z1), end(x2,y2,z2) {}

    /**
     * Constructs a line segment from two points given as vectors.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     * 
     * @param [in] s Start point as a vector.
     * @param [in] e End point as a vector.
     */
    Segment3D (const Vector3D<T> &s, const Vector3D<T> &e): start(s), end(e) {}

    /**
     * Copy constructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     *
     * @param [in] s A line segment.
     */
    Segment3D (const Segment3D<T> &s): start(s.start), end(s.end) {}

    /**
     * Destructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     */
    ~Segment3D () {}

    /**
     * Assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     *
     * @param [in] s A line segment.
     * 
     * @return This segment.
     */
    Segment3D<T> &operator = (const Segment3D<T> &s);

    /**
     * Equality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     *
     * @param [in] s A line segment.
     * 
     * @return Whether the segments are equal.
     */
    bool operator == (const Segment3D<T> &s);

    /**
     * Inequality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-10
     * @since 0.3
     *
     * @param [in] s A line segment.
     * 
     * @return Whether the segments are different.
     */
    bool operator != (const Segment3D<T> &s);

};

template <typename T>
Segment2D<T> &
Segment2D<T>::operator = (const Segment2D<T> &s)
{
  start = s.start;
  end = s.end;
  return *this;
}

template <typename T>
bool
Segment2D<T>::operator == (const Segment2D<T> &s)
{
  return start == s.start && end == s.end;
}

template <typename T>
bool
Segment2D<T>::operator != (const Segment2D<T> &s)
{
  return start != s.start || end != s.end;
}

template <typename T>
Segment3D<T> &
Segment3D<T>::operator = (const Segment3D<T> &s)
{
  start = s.start;
  end = s.end;
  return *this;
}

template <typename T>
bool
Segment3D<T>::operator == (const Segment3D<T> &s)
{
  return start == s.start && end == s.end;
}

template <typename T>
bool
Segment3D<T>::operator != (const Segment3D<T> &s)
{
  return start != s.start || end != s.end;
}

}
}
}

#endif
