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
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

namespace hummstrumm
{
namespace engine
{
namespace date
{


HUMMSTRUMM_IMPLEMENT_TYPE(hummstrumm::engine::date::Timezone,
                          hummstrumm::engine::core::Object)

Timezone::Timezone ()
  : offset ()
{}


Timezone::Timezone (const Duration &duration)
  throw (hummstrumm::engine::error::OutOfRange)
  : offset (Reduce (duration))
{
  if (offset.years != 0 || offset.months  != 0 || offset.days  != 0 ||
      offset.hours*60 + offset.minutes > 12*60 ||
      offset.hours*60 + offset.minutes < -12*60)
    {
      HUMMSTRUMM_THROW (OutOfRange,
                        "The timezone offset is too large.");
    }

  // Normalize such that both carry the same sign.
  if (offset.hours < 0 && offset.minutes > 0)
    {
      ++offset.hours;
      offset.minutes = 60 - offset.minutes;
    }
  else if (offset.hours > 0 && offset.minutes < 0)
    {
      --offset.hours;
      offset.minutes += 60;
    }

  offset.seconds = 0;
  offset.milliseconds = 0;
}


Timezone::Timezone (const Timezone &timezone)
  : offset (timezone.offset)
{}


Timezone::~Timezone ()
{}


Timezone &
Timezone::operator= (const Timezone &timezone)
  throw ()
{
  offset = timezone.offset;
  return *this;
}


Duration
Timezone::GetOffset ()
  const throw ()
{
  return offset;
}


bool
operator== (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.GetOffset () == b.GetOffset ();
}


bool
operator!= (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.GetOffset () != b.GetOffset ();
}


bool
operator< (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.GetOffset ().hours*60 + a.GetOffset ().minutes <
         b.GetOffset ().hours*60 + b.GetOffset ().minutes;
}


bool
operator<= (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.GetOffset ().hours*60 + a.GetOffset ().minutes <=
         b.GetOffset ().hours*60 + b.GetOffset ().minutes;
}


bool
operator> (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.GetOffset ().hours*60 + a.GetOffset ().minutes >
         b.GetOffset ().hours*60 + b.GetOffset ().minutes;
}


bool
operator>= (const Timezone &a, const Timezone &b)
  throw ()
{
  return a.GetOffset ().hours*60 + a.GetOffset ().minutes >=
         b.GetOffset ().hours*60 + b.GetOffset ().minutes;
}


std::ostream &
operator<< (std::ostream &out, const Timezone &t)
{
  std::locale c ("C");
  std::locale old (out.imbue (c));

  if (t.GetOffset ().hours == 0 && t.GetOffset ().minutes == 0)
    {
      out << "Z";
    }
  else
    {
      // Since both carry the same sign, check one.
      char sign = (t.GetOffset ().hours < 0) ? '-' : '+';

      char fillChar = out.fill ();
      out << std::setfill ('0') << sign
          << std::setw (2) << std::abs (t.GetOffset ().hours) << ':'
          << std::setw (2) << std::abs (t.GetOffset ().minutes);
      out.fill (fillChar);
    }

  out.imbue (old);
  return out;
}


std::istream &
operator>> (std::istream &in, Timezone &t)
  throw (hummstrumm::engine::error::OutOfRange)
{
  std::locale c ("C");
  std::locale old (in.imbue (c));

  Duration temp;

  std::string input;
  in >> input;
  std::replace (input.begin (), input.end (), ':', ' ');
  std::stringstream inputStream (input);

  inputStream >> temp.hours;
  inputStream >> temp.minutes;

  t = Timezone (temp);

  in.imbue (old);
  return in;
}


Timezone
GetCurrentTimezone ()
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
