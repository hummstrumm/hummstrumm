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


#include <system/endian.hpp>

#include <config.h>

namespace hummstrumm
{
namespace engine
{
namespace system
{


Endian Endian::Big    (Endian::BIG);
Endian Endian::Little (Endian::LITTLE);


Endian::Endian (const Endian &byteOrder)
  : byteOrder (byteOrder.byteOrder)
{}


Endian::~Endian (void)
{}


bool
Endian::operator== (const Endian &endian) const throw ()
{
  return (endian.byteOrder == this->byteOrder);
} 


#if defined (HUMMSTRUMM_ENDIAN_BIG)

Endian &
Endian::GetSystemByteOrder (void) throw ()
{
  return Endian::Big;
}

#else // #if defined (HUMMSTRUMM_ENDIAN_BIG)

Endian &
Endian::GetSystemByteOrder (void) throw ()
{
  return Endian::Little;
}

#endif // #if defined (HUMMSTRUMM_ENDIAN_BIG)


Endian::Endian (Endian::Order byteOrder)
  : byteOrder ((byteOrder == Endian::BIG) ? 0 : 1)
{}


}
}
}
