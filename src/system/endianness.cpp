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

#include "hummstrummengine.hpp"

namespace hummstrummengine {
namespace system {

Endianness::Endianness ()
  /* noexcept */
{
  // These two have the same memory.
  union
  {
      hummstrummengine::types::uint32 value32;
      unsigned char                     values8[4];
  };

  // Set all but the last byte to 1.
  values8[0] = values8[1] = values8[2] = 0;
  values8[3] = 1;

  // Was it really the last byte that we set to 1?
  if (value32 == 1)
    {
      systemEndianness = Endianness::Big;
    }
  else
    {
      systemEndianness = Endianness::Little;
    }
}


template <>
hummstrummengine::types::uint16
Endianness::SwitchEndian (const hummstrummengine::types::uint16 memory)
  const /* noexcept */
{
  return (((memory >> 8)) | (memory << 8));
}


template <>
hummstrummengine::types::int16
Endianness::SwitchEndian (const hummstrummengine::types::int16 memory)
  const /* noexcept */
{
    return (((memory >> 8)) | (memory << 8));
}


template <>
hummstrummengine::types::uint32
Endianness::SwitchEndian (const hummstrummengine::types::uint32 memory)
  const /* noexcept */
{
  return (((memory & 0x000000FF) << 24) |
          ((memory & 0x0000FF00) << 8)  |
          ((memory & 0x00FF0000) >> 8)  |
          ((memory & 0xFF000000) >> 24));
}


template <>
hummstrummengine::types::int32
Endianness::SwitchEndian (const hummstrummengine::types::int32 memory)
  const /* noexcept */
{
  return (((memory & 0x000000FF) << 24) |
          ((memory & 0x0000FF00) << 8)  |
          ((memory & 0x00FF0000) >> 8)  |
          ((memory & 0xFF000000) >> 24));
}


template <>
hummstrummengine::types::uint64
Endianness::SwitchEndian (const hummstrummengine::types::uint64 memory)
  const /* noexcept */
{
  return (((memory & 0xFF00000000000000) << 56) |
          ((memory & 0x00FF000000000000) << 40) |
          ((memory & 0x0000FF0000000000) << 24) |
          ((memory & 0x000000FF00000000) << 8)  |
          ((memory & 0x00000000FF000000) >> 8)  |
          ((memory & 0x0000000000FF0000) >> 24) |
          ((memory & 0x000000000000FF00) >> 40) |
          ((memory & 0x00000000000000FF) >> 56));
}


template <>
hummstrummengine::types::int64
Endianness::SwitchEndian (const hummstrummengine::types::int64 memory)
  const /* noexcept */
{
  return (((memory & 0xFF00000000000000) << 56) |
          ((memory & 0x00FF000000000000) << 40) |
          ((memory & 0x0000FF0000000000) << 24) |
          ((memory & 0x000000FF00000000) << 8)  |
          ((memory & 0x00000000FF000000) >> 8)  |
          ((memory & 0x0000000000FF0000) >> 24) |
          ((memory & 0x000000000000FF00) >> 40) |
          ((memory & 0x00000000000000FF) >> 56));
}

}
}
