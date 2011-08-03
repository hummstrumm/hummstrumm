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

/** 
 * Mathematical constants.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-07-30
 * @since 0.3
 *
 */

const float PI = 3.1415927410125732421875f;
const float HALF_PI = 1.57079637050628662109375f;
const float DEG_TO_RAD = PI / 180.0f;
const float RAD_TO_DEG = 180.0f / PI;


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
inline 
float 
RadToDeg (float radians)
{
  return RAD_TO_DEG * radians;  
}

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
inline 
float 
DegToRad (float degrees)
{
  return DEG_TO_RAD * degrees;
}

/* As explained in http://randydillon.org/Papers/2007/everfast.htm */
#define SIGNMASK (i) (-(int) ((unsigned int) (i)) >> 31)

}
}
}

#endif
