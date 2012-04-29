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
 * Mathematical constants and some fast math functions.
 *
 * @file    math/mathutils.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-06-10
 */

#ifndef HUMMSTRUMM_ENGINE_MATH_UTILS
#define HUMMSTRUMM_ENGINE_MATH_UTILS

namespace hummstrumm
{
namespace engine
{
namespace math
{


/// The mathematical constant \f$\pi\f$.
extern const double PI;
/// The mathematical constant \f$\frac{\pi}{2}\f$.
extern const double HALF_PI;
/// Conversion multiplier from degree to radian measure.
extern const double DEG_TO_RAD;
/// Conversion multiplier from radian to degree measure.
extern const double RAD_TO_DEG;


/**
 * Convert from Radians to Degrees.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-07-30
 * @since 0.3
 * 
 * @param [in] radians angle in radians
 *
 * @return The angle in degrees
 */
template <typename T>
inline T
RadToDeg (T radians);
/** 
 * Convert from Degrees to Radians
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-07-30
 * @since 0.3
 * 
 * @param [in] degrees angle in degrees
 *
 * @return The angle in radians
 */
template <typename T>
inline T
DegToRad (T degrees);

/* As explained in http://randydillon.org/Papers/2007/everfast.htm */
#define SIGNMASK (i) (-(int) ((unsigned int) (i)) >> 31)


}
}
}

#endif
