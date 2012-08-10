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

#include <hummstrummengine.hpp>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <stdexcept>

namespace hummstrumm
{
namespace engine
{
namespace date
{


Duration::Duration ()
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
  std::locale c ("C");
  std::locale old (out.imbue (c));

  // Check that we have some duration in the years or nothing else, which means
  // we want to explicitly say "0Y".
  out << 'D';
  if (d.years ||
      (!d.months && !d.days && !d.hours &&
       !d.minutes && !d.seconds && !d.milliseconds))
    {
      out << d.years << 'Y';
    }
  if (d.months)
    {
      out << d.months << 'M';
    }
  if (d.days)
    {
      out << d.days << 'D';
    }

  // If we have a time duration as well, say that.
  if (d.hours || d.minutes || d.seconds || d.milliseconds)
    {
      out << 'T';
    }
  if (d.hours)
    {
      out << d.hours << 'H';
    }
  if (d.minutes)
    {
      out << d.minutes << 'M';
    }
  if (d.seconds || d.milliseconds)
    {
      int sec, ms;
      if (d.seconds < 0 && d.milliseconds > 0)
        {
          sec = d.seconds + 1;
          ms  = 1000 - d.milliseconds;
        }
      else if (d.seconds > 0 && d.milliseconds < 0)
        {
          sec = d.seconds - 1;
          ms  = 1000 + d.milliseconds;
        }
      else
        {
          sec = d.seconds;
          ms  = d.milliseconds;
        }

      if (sec == 0 && ms < 0)
        {
          out << '-';
        }
      out << sec;
      if (ms)
        {
          char fillChar = out.fill ();
          out << '.' << std::setfill ('0') << std::setw (3) << std::abs (ms);
          out.fill (fillChar);
        }
      out << 'S';
    }

  out.imbue (old);
  return out;
}


std::istream &
operator>> (std::istream &in, Duration &d)
{
  // Each field or element of the duration string has the form 'nC', where 'n'
  // is a number of variable length and 'C' is a capital ASCII letter denoting
  // which field of the duration the preceding number represents.
  //
  // So, ISO 8601 isn't clear about this.  If parts of the duration are negative
  // (we know that sometimes they can't be normalized to be a completely
  // positive or negative duration, due to the relative nature of temporal
  // durations), what we do is place the negative signs inside each element of
  // the duration:
  //
  //     D1Y-5DT5S -- one year, negative five days, five seconds
  HUMMSTRUMM_ENGINE_REGEX_NS_PREFIX::regex r ("D(?:(-?\\d+)(Y))?"
    "(?:(-?\\d+)(M))?"
    "(?:(-?\\d+)(D))?"
    "(?:(T)(?:(-?\\d+)(H))?"
    "(?:(-?\\d+)(M))?"
    "(?:(-?\\d+(?:\\.\\d{1,3})?)(S))?)?");
  HUMMSTRUMM_ENGINE_REGEX_NS_PREFIX::smatch m;

  // ISO 8601 durations allow parts of the duration that we store to be left out
  // if they are zero.
  d = Duration ();
                        
  std::locale cLocale ("C");
  std::locale old (in.imbue (cLocale));

  std::string s;
  in >> s;

  if (regex_match (s, m, r))
    {
      // Check the labels after each value.
      int i = 1;
      while (i+1 <= m.size () && m[i].str () != "T")
        {
          std::string type = m[i+1].str ();
          if (type == "Y")
            d.years = std::stoi (m[i].str ());
          else if (type == "M")
            d.months = std::stoi (m[i].str ());
          else if (type == "D")
            d.days = std::stoi (m[i].str ());
          i += 2;
        }
      if (i <= m.size () && m[i].str () == "T")
        ++i;
      while (i+1 <= m.size ())
        {
          std::string type = m[i+1].str ();
          if (type == "H")
            d.hours = std::stoi (m[i].str ());
          else if (type == "M")
            d.minutes = std::stoi (m[i].str ());
          else if (type == "S")
            {
              auto secsAndMs = std::stod (m[i].str ());
              d.seconds      = static_cast<signed> (secsAndMs);
              d.milliseconds =
                hummstrumm::engine::math::round ((secsAndMs-d.seconds) * 1000);
            }
	  i += 2;
        }
    }
  else
    {
      throw std::runtime_error ("Input stream did not contain a valid duration."
                                "  We don't support differences between two "
                                "dates.");
    }

  in.imbue (old);
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
