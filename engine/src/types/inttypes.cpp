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
#define HUMMSTRUMM_ENGINE_SOURCE
#include "hummstrummengine.hpp"


#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  pragma warning(disable: 4146)
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS

namespace hummstrumm
{
namespace engine
{
namespace types
{

const int16 INT16_MIN  (-32768);
const int16 INT16_MAX  (+32767);
const uint16 UINT16_MAX (+65535u);
const int32 INT32_MIN  (-2147483648l);
const int32 INT32_MAX  (+2147483647l);
const uint32 UINT32_MAX (+4294967295ul);
const int64 INT64_MIN  (-9223372036854775807ll-1); // GCC warnings without this.
const int64 INT64_MAX  (+9223372036854775807ll);
const uint64 UINT64_MAX (+18446744073709551615ull);

}
}
}
