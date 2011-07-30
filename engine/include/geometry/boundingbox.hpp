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
 * Defines and implements an Axially Aligned Bounding Box in 2D and 
 * 3D space.
 *
 * @file    geometry/boundingbox.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-03-28
 *
 */
#ifndef HUMMSTRUMM_ENGINE_AABBOX
#define HUMMSTRUMM_ENGINE_AABBOX

namespace hummstrumm
{
namespace engine
{
namespace geometry
{

using hummstrumm::engine::math::Vector3D;

/*
 *          _____________________ bmax
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
 * bmin       
 *         
 */
/**
 * @image html aabb3d.png
 */
template <typename T>
class AABBox3D
{
  public:
    Vector3D<T> bmin;
    Vector3D<T> bmax;

    /**
     * Constructs an empty AABB.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     */
    AABBox3D (): bmin (0,0,0), bmax (0,0,0) {}
    
    /**
     * Constructs an AABB from corner points pmax and pmin.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] pmin Corner point bmin.
     * @param [in] pmax Corner point bmax.
     */
    AABBox3D (const Vector3D<T> &pmin, const Vector3D<T> &pmax)
      : bmin (pmin), bmax (pmax) {}

    /**
     * Constructs an AABB from bmin bmax coordinates.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] minx Min point coordinate x.
     * @param [in] miny Min point coordinate y.
     * @param [in] minz Min point coordinate z.
     * @param [in] maxx Max point coordinate x.
     * @param [in] maxy Max point coordinate y.
     * @param [in] maxz Max point coordinate z.
     */
    AABBox3D (const T &minx, const T &miny, const T &minz,
            const T &maxx, const T &maxy, const T &maxz)
      : bmin(minx, miny, minz), bmax(maxx, maxy, maxz) {}

    /**
     * Copy Constructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] box An 3d AABB.
     */
    AABBox3D (const AABBox3D<T> &box): bmin(box.bmin), bmax(box.bmax) {}

    /**
     * Destructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     */
    ~AABBox3D () {}

    /**
     * Assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] box A bounding box.
     *
     * @return This bounding box.
     */
    AABBox3D<T> &operator = (const AABBox3D<T> &box);

     /**
     * Equality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] box A bounding box.
     *
     * @return Whether the two bounding boxes are equal.
     */
    bool operator == (const AABBox3D<T> &box) const;

     /**
     * Inequality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] box A bounding box.
     *
     * @return Whether the two bounding boxes are different.
     */
    bool operator != (const AABBox3D<T> &box) const;

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
     * @image html aabb3d-corners.png
     *
     * Bit 0 selects bmin.x vs bmax.x
     * Bit 1 selects bmin.y vs bmax.y
     * Bit 2 selects bmin.z vs bmax.z
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] i Corner number.
     */
    /*     6__________7
     *     /|        /|
     *    / |       / |
     * 2 /________3/  |
     *  |  4|_____|___|
     *  |  /      |  /5
     *  | /       | /
     *  |/________|/
     *  0         1
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

/*
 *
 *
 *          +Y
 *           |
 *           |     
 *   ________|________ bmax
 *  |        |        |
 *  |        |        |
 *  |        |        |
 *  |        |        |
 *  |        * -------|------ +X
 *  |                 |
 *  |                 |
 *  |_________________|
 * bmin       
 *         
 */
/**
 * @image html aabb2d.png
 */
template <typename T>
class AABBox2D
{
  public:
    Vector2D<T> bmin;
    Vector2D<T> bmax;

    /**
     * Constructs an empty AABB.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     */
    AABBox2D (): bmin (0,0), bmax (0,0) {}
    
    /**
     * Constructs an AABB from corner points pmax and pmin.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] pmin Corner point bmin.
     * @param [in] pmax Corner point bmax.
     */
    AABBox2D (const Vector2D<T> &pmin, const Vector2D<T> &pmax)
      : bmin (pmin), bmax (pmax) {}

    /**
     * Constructs an AABB from bmin bmax coordinates.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] minx Min point coordinate x.
     * @param [in] miny Min point coordinate y.
     * @param [in] maxx Max point coordinate x.
     * @param [in] maxy Max point coordinate y.
     */
    AABBox2D (const T &minx, const T &miny, const T &maxx, 
              const T &maxy)
      : bmin(minx, miny), bmax(maxx, maxy) {}

    /**
     * Copy Constructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] box An 3d AABB.
     */
    AABBox2D (const AABBox2D<T> &box): bmin(box.bmin), bmax(box.bmax) {}

    /**
     * Destructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     */
    ~AABBox2D () {}

    /**
     * Assignment operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] box A bounding box.
     *
     * @return This bounding box.
     */
    AABBox2D<T> &operator = (const AABBox2D<T> &box);

     /**
     * Equality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] box A bounding box.
     *
     * @return Whether the two bounding boxes are equal.
     */
    bool operator == (const AABBox2D<T> &box) const;

     /**
     * Inequality operator.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] box A bounding box.
     *
     * @return Whether the two bounding boxes are different.
     */
    bool operator != (const AABBox2D<T> &box) const;

    /**
     * Box dimension.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return The width, height and length of the box.
     */
    Vector2D<T> Size() const;
  
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
     * Box center point.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @return The center point.
     */
    Vector2D<T> Center() const;

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
     *
     * @image html aabb2d-corners.png
     *
     * Bit 0 selects bmin.x vs bmax.x
     * Bit 1 selects bmin.y vs bmax.y
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-05-30
     * @since 0.3
     *
     * @param [in] i Corner number.
     */
    /*  2_________3
     *  |         |
     *  |         |
     *  |         |
     *  |_________|
     *  0         1
     */
    Vector2D<T> GetCorner(unsigned short i) const;

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
    HUMMSTRUMM_THROW (OutOfRange,"Corner out of range\n");

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
    HUMMSTRUMM_THROW (OutOfRange,"Corner out of range\n");

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

// Non member functions

/**
 * Check if the box contains a point.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in] box A AABB.
 * @param [in] plane A point.
 *
 * @return Whether the point is inside the box.
 *
 * @see AABBox3D
 */
template <typename T>
bool AABBox3ContainsPoint (const AABBox3D<T> &box, const Vector3D<T> &plane);

/**
 * Add a point to the box.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in,out] box A AABB.
 * @param [in] plane A point.
 *
 * @see AABBox3D
 */
template <typename T>
void AABBox3AddPoint (AABBox3D<T> &box, const Vector3D<T> &plane);

/**
 * Add a AABB other to AABB box. 
 * Box expands to fit if necessary.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in,out] box A AABB.
 * @param [in] other Another AABB.
 *
 * @see AABBox3D
 */
template <typename T>
void AABBox3AddBox (AABBox3D<T> &box, const AABBox3D<T> &other);

/**
 * Add a bounding sphere to bounding box.
 * Box expands to fit.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in,out] box A AABB.
 * @param [in] sphere A bounding sphere.
 *
 * @see AABBox3D
 */
template <typename T>
void AABBox3AddSphere (AABBox3D<T> &box, const BSphere3D<T> &sphere);

/**
 * Check if bounding box intersects or contains another bounding box.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in] box A AABB.
 * @param [in] other Another AABB.
 *
 * @return -1 if they don't intersect, 1 if box contains the other box
 * and 0 if they intersect.
 *
 * @note Static.
 * @see AABBox3D
 */
template <typename T>
short AABBox3IntersectBox (const AABBox3D<T> &box, const AABBox3D<T> &other);

/**
 * Check if bounding box intersects or contains a bounding sphere.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in] box A AABB.
 * @param [in] sphere A bounding sphere.
 *
 * @return -1 if they don't intersect, 1 if box contains the sphere
 * and 0 if they intersect.
 *
 * @note Static.
 * @see AABBox3D
 */
template <typename T>
short AABBox3IntersectSphere (const AABBox3D<T> &box, const BSphere3D<T> &sphere);

/**
 * Check if bounding box intersects or contains a plane.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in] box A AABB.
 * @param [in] plane A plane
 *
 * @return 0 if they intersect, -1 if box is completely on the back side
 * of the plane and 1 if the box is completely on the front side of the place.
 *
 * @note Static.
 * @see AABBox3D
 */
template <typename T>
short AABBox3IntersectPlane (const AABBox3D<T> &box, const Plane3D<T> &plane);

/**
 * Closest point on bounding box to another point.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in] box A AABB.
 * @param [in] point A point
 *
 * @return The closest point.
 * @see AABBox3D
 */
template <typename T>
Vector3D<T> AABBox3ClosestPoint (const AABBox3D<T> &box, const Vector3D<T> &point);

////// AABBox2D definitions //////

/**
 * Check if the box contains a point.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in] box A AABB.
 * @param [in] plane A point.
 *
 * @return Whether the point is inside the box.
 * @see AABBox2D
 */
template <typename T>
bool AABBox2ContainsPoint (const AABBox2D<T> &box, const Vector2D<T> &plane);

/**
 * Add a point to the box.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in,out] box A AABB.
 * @param [in] plane A point.
 *
 * @see AABBox2D
 */
template <typename T>
void AABBox2AddPoint (AABBox2D<T> &box, const Vector2D<T> &plane);

/**
 * Add a AABB other to AABB box. 
 * Box expands to fit if necessary.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in,out] box A AABB.
 * @param [in] other Another AABB.
 *
 * @see AABBox2D
 */
template <typename T>
void AABBox2AddBox (AABBox2D<T> &box, const AABBox2D<T> &other);

/**
 * Add a bounding sphere to bounding box.
 * Box expands to fit.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in,out] box A AABB.
 * @param [in] sphere A bounding sphere.
 *
 * @see AABBox2D
 */
template <typename T>
void AABBox2AddSphere (AABBox2D<T> &box, const BSphere3D<T> &sphere);

/**
 * Check if bounding box intersects or contains another bounding box.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in] box A AABB.
 * @param [in] other Another AABB.
 *
 * @return -1 if they don't intersect, 1 if box contains the other box
 * and 0 if they intersect.
 *
 * @note Static.
 * @see AABBox2D
 */
template <typename T>
short AABBox2IntersectBox (const AABBox2D<T> &box, const AABBox2D<T> &other);

/**
 * Closest point on bounding box to another point.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-05-30
 * @since 0.3
 *
 * @param [in] box A AABB.
 * @param [in] point A point
 *
 * @return The closest point.
 * @see AABBox2D
 */
template <typename T>
Vector2D<T> AABBox2ClosestPoint (const AABBox2D<T> &box, const Vector2D<T> &point);


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
  contains (box,plane);
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

}
}
}

#endif
