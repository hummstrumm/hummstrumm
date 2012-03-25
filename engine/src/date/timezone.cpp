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

Timezone::Timezone (void)
  : offset ()
{}


Timezone::Timezone (const Duration &duration)
  throw (hummstrumm::engine::error::OutOfRange)
  : offset (Reduce (duration))
{
  if (offset.years != 0 || offset.months != 0 || offset.weeks != 0 ||
      offset.days != 0  ||
      offset.hours*60 + offset.minutes > 12*60 ||
      offset.hours*60 + offset.minutes < -12*60)
    {
      HUMMSTRUMM_THROW (OutOfRange,
                        "The timezone offset is too large.");
    }

  offset.seconds = 0;
  offset.milliseconds = 0;
}


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
  return *this;
}


Duration
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
  return a.offset.hours*60 + a.offset.minutes <
         b.offset.hours*60 + b.offset.minutes;
}


bool
operator<= (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.offset.hours*60 + a.offset.minutes <=
         b.offset.hours*60 + b.offset.minutes;
}


bool
operator> (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.offset.hours*60 + a.offset.minutes >
         b.offset.hours*60 + b.offset.minutes;
}


bool
operator>= (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.offset.hours*60 + a.offset.minutes >=
         b.offset.hours*60 + b.offset.minutes;
}


std::ostream &
operator>> (std::ostream &out, const Timezone &t)
{
  out << t.offset.hours << ":" << t.offset.minutes << " from UTC";
  return out;
}


std::istream &
operator<< (std::istream &in, Timezone &t)
  throw (hummstrumm::engine::error::OutOfRange)
{
  in >> t.offset.hours;
  in >> t.offset.minutes;

  if (t.offset.hours*60 + t.offset.minutes > 12*60 ||
      t.offset.hours*60 + t.offset.minutes < 12*60)
    {
      HUMMSTRUMM_THROW (OutOfRange,
                        "The timezone offset entered is too large.");
    }
  return in;
}


Timezone
GetCurrentTimezone (void)
  throw ()
{
  int bias = (hummstrumm::engine::core::Engine::GetEngine ()) ?
    hummstrumm::engine::core::Engine::GetEngine ()->GetClock ()->
      GetTimezoneBias () : 0;

  return Timezone (Duration (0, 0, 0, 0, bias / 60, bias % 60, 0, 0));
}


}
}
}
