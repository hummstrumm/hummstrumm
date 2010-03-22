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
 * Defines several cross-platform, fixed-size integer types.
 *
 * @file   inttypes.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-13
 */

#ifndef HUMMSTRUMM_ENGINE_TYPES_INTTYPES
#define HUMMSTRUMM_ENGINE_TYPES_INTTYPES

#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
#  include <inttypes.h>
#endif

namespace hummstrumm
{
namespace engine
{
namespace types
{

/**
 * A cross-platform, 16-bit, signed integer.
 *
 * @typedef int16
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
/**
 * A cross-platform, 16-bit, unsigned integer.
 *
 * @typedef uint16
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
/**
 * A cross-platform, 32-bit, signed integer.
 *
 * @typedef int32
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
/**
 * A cross-platform, 32-bit, unsigned integer.
 *
 * @typedef uint32
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
/**
 * A cross-platform, 64-bit, signed integer.
 *
 * @typedef int64
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
/**
 * A cross-platform, 64-bit, unsigned integer.
 *
 * @typedef uint64
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */

#ifdef HUMMSTRUMM_PLATFORM_GNULINUX

typedef int16_t  int16;
typedef uint16_t uint16;
typedef int32_t  int32;
typedef uint32_t uint32;
typedef int64_t  int64;
typedef uint64_t uint64;

#endif // #ifdef HUMMSTRUMM_PLATFORM_GNULINUX
#ifdef HUMMSTRUMM_PLATFORM_WINDOWS

typedef __int16          int16;
typedef unsigned __int16 uint16;
typedef __int32          int32;
typedef unsigned __int32 uint32;
typedef __int64          int64;
typedef unsigned __int64 uint64;

#endif // #ifdef HUMMSTRUMM_PLATFORM_GNULINUX

/**
 * The minimum value of an int16.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
#define INT16_MIN  (-32768);
/**
 * The maximum value of an int16.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
#define INT16_MAX  (+32767);
/**
 * The maximum value of an uint16.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
#define UINT16_MAX (+65535u);
/**
 * The minimum value of an int32.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
#define INT32_MIN  (-2147483648);
/**
 * The maximum value of an int32.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
#define INT32_MAX  (+2147483647);
/**
 * The maximum value of an uint32.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
#define UINT32_MAX (+4294967295u);
/**
 * The minimum value of an int64.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
#define INT64_MIN  (-9223372036854775808);
/**
 * The maximum value of an int64.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
#define INT64_MAX  (+9223372036854775807);
/**
 * The maximum value of an uint64.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-15
 * @since 0.2
 */
#define UINT64_MAX (+18446744073709551615u);


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_TYPES_TIME
