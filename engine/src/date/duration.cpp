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

#include <hummstrummengine.hpp>

using namespace hummstrumm::engine::core;

namespace hummstrumm
{
namespace engine
{
namespace date
{

HUMMSTRUMM_IMPLEMENT_TYPE (Duration, Object)


Duration::Duration (void)
{
  // Just set everything to zero.
  years = months = days = hours = minutes = seconds = milliseconds = 0;
}


Duration::Duration (int years,
                    int months,
                    int weeks,
                    int days,
                    int hours,
                    int minutes,
                    int seconds,
                    int milliseconds)
{
  this->years        = years;
  this->months       = months;
  this->days         = days + weeks*7;
  this->hours        = hours;
  this->minutes      = minutes;
  this->seconds      = seconds;
  this->milliseconds = milliseconds;
}


std::ostream &
operator<< (std::ostream &out, const Duration &d)
{
   out << d.years        << " year(s), "
       << d.months       << " month(s), "
       << d.days         << " day(s), "
       << d.hours        << " hour(s), "
       << d.minutes      << " minute(s), "
       << d.seconds      << " second(s), "
       << d.milliseconds << " millisecond(s)";
   return out;
}


std::istream &
operator>> (std::istream &in, Duration &d)
{  
  in >> d.years;
  in >> d.months;
  in >> d.days;
  in >> d.hours;
  in >> d.minutes;
  in >> d.seconds;
  in >> d.milliseconds;
  return in;
}


Duration
Reduce (Duration d)
{
  // We reduce each unit into a greater unit first, and then check whether any
  // of the units are negative.  We don't like having smaller negative units and
  // greater positive units (we don't think in 1 second and -356 milliseconds,
  // but rather 644 milliseconds), so we reduce in that case.

  // There are 1000 ms per s.
  d.seconds += d.milliseconds / 1000;
  d.milliseconds %= 1000;
  // There are 60 s per min.
  d.minutes += d.seconds / 60;
  d.seconds %= 60;
  // There are 60 min per hr.
  d.hours += d.minutes / 60;
  d.minutes %= 60;
  // There are 24 hr per day.
  d.days += d.hours / 24;
  d.hours %= 24;

  // I'm not sure why, but I can't think of a nicer way to do this.

  // Find the first non-zero unit from the left.
  int placeValue = 0;
  if (d.hours == 0)
    {
      ++placeValue;
      if (d.minutes == 0)
        {
          ++placeValue;
          if (d.seconds == 0)
            {
              ++placeValue;
            }
        }
    }

  // Go through and non-negate until that last unit.
  if (d.milliseconds < 0 && placeValue < 3)
    {
      --d.seconds;
      d.milliseconds += 1000;
    }
  if (d.seconds < 0 && placeValue < 2)
    {
      --d.minutes;
      d.seconds += 60;
    }
  if (d.seconds < 0 && placeValue < 1)
    {
      --d.hours;
      d.minutes += 60;
    }

  return d;
}


bool
ReduceEquals (const Duration &a, const Duration &b)
{
  return Reduce (a) == Reduce (b);
}


}
}
}
