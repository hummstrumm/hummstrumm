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
 * Defines and implements a 2D and 3D Axially Aligned Bounding Box.
 *
 * @file    boundingBox.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 *
 */
#ifndef HUMMSTRUMM_ENGINE_AABB
#define HUMMSTRUMM_ENGINE_AABB

namespace hummstrumm
{
namespace engine
{
namespace geometry
{

using hummstrumm::engine::math::Vector3D;


/*
 *          _____________________ max
 *        /|                    /|
 *       / |    +Y             / |
 *      /  |     |            /  |
 *     /   |     |           /   |
 *    /    |     |          /    |
 *   /     |     |     +Z  /     |
 *  /______|___________/__/      |
 *  |      |     |    /   |      |
 *  |      |     |   /    |      |
 *  |      /-----|--/-----|------/
 *  |     /      | /      |     /
 *  |    /       |/       |    /
 *  |   /        * -------|--------- +X
 *  |  /                  |  /
 *  | /                   | /
 *  |/____________________|/
 * min       
 *         
 */
template <typename T>
class AABB3D
{
  public:
    Vector3D<T> min;
    Vector3D<T> max;

    /**
     * Constructs a default aabb.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     */
    AABB3D (): min (-1,-1,-1), max (1,1,1) {}
    
    /**
     * Constructs an aabb from corner points pmax and pmin.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param pmin Corner point min.
     * @param pmax Corner point max.
     */
    AABB3D (const Vector3D<T> &pmin, const Vector3D<T> &pmax)
      : min (pmin), max (pmax) {}

    /**
     * Constructs an aabb from min max coordinates.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param minx Min point coordinate x.
     * @param miny Min point coordinate y.
     * @param minz Min point coordinate z.
     * @param maxx Max point coordinate x.
     * @param maxy Max point coordinate y.
     * @param maxz Max point coordinate z.
     */
    AABB3D (const T &minx, const T &miny, const T &minz,
            const T &maxx, const T &maxy, const T &maxz)
      : min(minx, miny, minz), max(maxx, maxy, maxz) {}

    /**
     * Copy Constructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param b An 3d AABB.
     */
    AABB3D (const AABB3D<T> &b): min(b.min), max(b.max) {}

    /**
     * Destructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     */
    ~AABB3D () {}

    /**
     * Assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param b A bounding box.
     *
     * @return This bounding box.
     */
    AABB3D<T> &operator = (const AABB3D<T> &b);

     /**
     * Equality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param b A bounding box.
     *
     * @return Whether the two bounding boxes are equal.
     */
    bool operator == (const AABB3D<T> &b) const;

     /**
     * Inequality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param b A bounding box.
     *
     * @return Whether the two bounding boxes are different.
     */
    bool operator != (const AABB3D<T> &b) const;

    /**
     * Box dimension.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return The width, height and length of the box.
     */
    Vector3D<T> Size() const;
  
    /**
     * Box dimension in x axis.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return The width of the box.
     */
    T SizeX() const;

    /**
     * Box dimension in y axis.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return The height of the box.
     */  
    T SizeY() const;

    /**
     * Box dimension in z axis.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return The length of the box.
     */
    T SizeZ() const;

    /**
     * Box center point.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return The center point.
     */
    Vector3D<T> Center() const;

    /**
     * Empty the box.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     */
    void Empty();

    /**
     * Check if box is empty.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return Whether the box is empty.
     */
    bool IsEmpty() const;

    /**
     * Get the corner(s) of the box.
     * From 3D Math Primer book.
     *
     *
     *     6__________7
     *     /|        /|
     *    / |       / |
     * 2 /________3/  |
     *  |  4|_____|___|
     *  |  /      |  /5
     *  | /       | /
     *  |/________|/
     *  0         1 
     *
     * Bit 0 selects min.x vs max.x
     * Bit 1 selects min.y vs max.y
     * Bit 2 selects min.z vs max.z
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param i Corner number.
     */
    Vector3D<T> GetCorner(unsigned short i) const;

    /**
     * Volume of the box.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return Volume of this box.
     */
    T Volume() const;

    /**
     * Area of the box.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return Area of this box.
     */
    T Area() const;

};


template <typename T>
AABB3D<T> &
AABB3D<T>::operator = (const AABB3D<T> &b)
{
  min = b.min;
  max = b.max;
  return *this;
}

template <typename T>
bool
AABB3D<T>::operator == (const AABB3D<T> &b) const
{
  return min == b.min && max == b.max;
}

template <typename T>
bool
AABB3D<T>::operator != (const AABB3D<T> &b) const
{
  return min != b.min || max != b.max;
}

template <typename T>
Vector3D<T>
AABB3D<T>::Size() const
{
  return max - min;
}

template <typename T>
T
AABB3D<T>::SizeX() const
{
  return max.x - min.x;
}

template <typename T>
T
AABB3D<T>::SizeY() const
{
  return max.y - min.y;
}

template <typename T>
T
AABB3D<T>::SizeZ() const
{
  return max.z - min.z;
}

template <typename T>
Vector3D<T>
AABB3D<T>::Center() const
{
  return (min + max)*0.5;
}

template <typename T>
void
AABB3D<T>::Empty()
{
  max.x = max.y = max.z = 0;
  min.x = min.y = min.z = 0;
}

template <typename T>
bool
AABB3D<T>::IsEmpty() const
{
  return max == min;
}

template <typename T>
Vector3D<T>
AABB3D<T>::GetCorner(unsigned short i) const
{
  if (i < 0 || i > 7)
    THROW (OutOfRange,"Corner out of range\n");

  return Vector3D<T>(
    (i & 2) ? max.x : min.x,
    (i & 2) ? max.y : min.y,
    (i & 4) ? max.z : min.z
  );
}

template <typename T>
T
AABB3D<T>::Volume() const
{
  return ((max.x - min.x) * (max.y - min.y) * (max.z - min.z));
}

template <typename T>
T
AABB3D<T>::Area() const
{
  T x = max.x - min.x;
  T y = max.y - min.y;
  T z = max.z - min.z;
  return  2 * (x*y + x*z + y*z);
}


// Non member functions

/**
 * Check if the box contains a point.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param b A AABB.
 * @param p A point.
 *
 * @return Whether the point is inside the box.
 */
template <typename T>
bool AABB3ContainsPoint (const AABB3D<T> &b, const Vector3D<T> &p);

/**
 * Add a point to the box.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param b A AABB.
 * @param p A point.
 */
template <typename T>
void AABB3AddPoint (const AABB3D<T> &b, const Vector3D<T> &p);

/**
 * Add a aabb b2 to aabb b1. 
 * b1 expands to fit b2 if necessary.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param b1 A aabb.
 * @param b2 A aabb.
 */
template <typename T>
void AddBox (const AABB3D<T> &b1, const AABB3D<T> &b2);



template <typename T>
bool
AABB3ContainsPoint (const AABB3D<T> &b, const Vector3D<T> &p)
{
  return (p.x >= b.min.x) && (p.y <= b.max.x) &&
         (p.y >= b.min.y) && (p.y <= b.max.y) &&
         (p.z >= b.min.z) && (p.z <= b.max.z);
}

template <typename T>
void
AAB3AddPoint (const AABB3D<T> &b, const Vector3D<T> &p)
{
  if (p.x < b.min.x) b.min.x = p.x;
  if (p.x < b.max.x) b.max.x = p.x;
  if (p.y < b.min.y) b.min.y = p.y;
  if (p.y < b.max.y) b.max.y = p.y;
  if (p.z < b.min.z) b.min.z = p.z;
  if (p.z < b.max.z) b.max.z = p.z;
}

template <typename T>
void
AABB3AddBox (const AABB3D<T> &b1, const AABB3D<T> &b2)
{
  if (b2.min.x < b1.min.x) b1.min.x = b2.min.x;
  if (b2.min.x < b1.max.x) b1.max.x = b2.min.x;
  if (b2.min.y < b1.min.y) b1.min.y = b2.min.y;
  if (b2.min.y < b1.max.y) b1.max.y = b2.min.y;
  if (b2.min.z < b1.min.z) b1.min.z = b2.min.z;
  if (b2.min.z < b1.max.z) b1.max.z = b2.min.z;
}

}
}
}

#endif
