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

#include "hummstrummengine.hpp"

namespace hummstrumm
{
namespace engine
{
namespace date
{


HUMMSTRUMM_IMPLEMENT_TYPE(hummstrumm::engine::date::Timezone,
                          hummstrumm::engine::core::Object)


Timezone::Timezone (const DateDuration &duration)
  : offset (duration)
{}


Timezone::Timezone (const Timezone &timezone)
  : offset (timezone.offset)
{}


Timezone::~Timezone (void)
{}


Timezone &
Timezone::operator= (const Timezone &timezone)
  throw ()
{
  offset = timezone.offset;
}


DateDuration
Timezone::GetOffset (void)
  const throw ()
{
  return offset;
}


bool
operator== (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.offset == b.offset;
}


bool
operator!= (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.offset != b.offset;
}


bool
operator< (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.offset < b.offset;
}


bool
operator<= (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.offset <= b.offset;
}


bool
operator> (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.offset > b.offset;
}


bool
operator>= (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.offset >= b.offset;
}


}
}
}
