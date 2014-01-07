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
 * Defines several cross-platform, fixed-size integer types.
 *
 * @file   types/inttypes.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-13
 */

#ifndef HUMMSTRUMM_ENGINE_TYPES_INTTYPES
#define HUMMSTRUMM_ENGINE_TYPES_INTTYPES

#include <limits>

#if defined(HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX) || \
    defined (HUMMSTRUMM_ENGINE_PLATFORM_BSD)
#  include <inttypes.h>
#endif

namespace hummstrummengine
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

#ifdef HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS

typedef __int16          int16;
typedef unsigned __int16 uint16;
typedef __int32          int32;
typedef unsigned __int32 uint32;
typedef __int64          int64;
typedef unsigned __int64 uint64;

#else // #ifdef HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS

typedef int16_t  int16;
typedef uint16_t uint16;
typedef int32_t  int32;
typedef uint32_t uint32;
typedef int64_t  int64;
typedef uint64_t uint64;

#endif // #ifdef HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS

/**
 * A cross-platform type that represents the signed native type of the system
 * (since, unfortunately, @c int doesn't do that on all systems).
 *
 * @typedef intNatural
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2012-03-25
 * @since 0.5
 */
/**
 * A cross-platform type that represents the unsigned native type of the system
 * (since, unfortunately, @c int doesn't do that on all systems).
 *
 * @typedef uintNatural
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2012-03-25
 * @since 0.5
 */

#if defined (HUMMSTRUMM_ENGINE_ARCHITECTURE_64)

typedef int64  intNatural;
typedef uint64 uintNatural;

#elif defined (HUMMSTRUMM_ENGINE_ARCHITECTURE_32)

typedef int32  intNatural;
typedef uint32 uintNatural;

#else // Just guess

typedef signed   intNatural;
typedef unsigned uintNatural;

#endif // #if defined (HUMMSTRUMM_ENGINE_ARCHITECTURE_64)



}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_TYPES_TIME
