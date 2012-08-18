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
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <stdexcept>
using namespace hummstrumm::engine::types;


namespace hummstrumm
{
namespace engine
{
namespace date
{


// The number of milliseconds in a day is taken to be constant.
static const int MILLISECONDS_PER_DAY = 24 * 60 * 60 * 1000;

// Helper to find the first day number of a given year, with 1970-01-01 as day
// 0.
static uintNatural
FirstDayOfYear (unsigned year)
{
  // Algorithm from the ECMAScript standard (ECMA-262), version 5, section
  // 15.9.1.3.
  return 365 * (year-1970) + (year-1969)/4 - (year-1901)/100 + (year-1601)/400;
}


Date::Date ()
  : millisecondsSinceEpoch (0)
{}


Date::Date (uintNatural ms)
  : millisecondsSinceEpoch (ms)
{}

Date::Date (unsigned year,
            unsigned month,
            unsigned day,
            unsigned hour,
            unsigned minute,
            unsigned second,
            unsigned millisecond)
  : millisecondsSinceEpoch (0)
{
  // This'll be useful later.
  const unsigned DAYS_PER_MONTH [] =
    { 31u, (IsLeapYear (year)) ? 29u : 28u,
      31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u };

  // Check that everything is valid.
  if (year < 1970)
    {
      throw std::out_of_range ("The year is before the UNIX epoch.");
    }

  if (month == 0)
    {
      throw std::out_of_range ("There is no month 0.");
    }
  if (month > 12)
    {
      throw std::out_of_range ("There are only 12 months in a year.");
    }

  if (day == 0)
    {
      throw std::out_of_range ("There is no day 0.");
    }
  if (day > DAYS_PER_MONTH[month-1])
    {
      throw std::out_of_range
        ("There are fewer days in this month than that.");
    }

  if (hour > 23)
    {
      throw std::out_of_range ("There are only 24 hours in a day.");
    }
  if (minute > 59)
    {
      throw std::out_of_range ("There are only 60 minutes in an hour.");
    }
  if (second > 59)
    {
      throw std::out_of_range ("There are only 60 seconds in a minute.");
    }
  if (millisecond > 999)
    {
      throw std::out_of_range
        ("There are only 1000 milliseconds in a second.");
    }

  // Now convert everything to milliseconds.
  millisecondsSinceEpoch = ((hour    * 60 +   // Hours to minutes
                             minute) * 60 +   // Minutes to seconds
                             second) * 1000 + // Milliseconds to seconds
                             millisecond;
  
  // In both the day and month case, we start numbering from 1, so we have to
  // ignore the first day.
  uintNatural tempDay = day - 1;
  for (unsigned i = 1; i < month; ++i)
    {
      tempDay += DAYS_PER_MONTH[i-1];
    }
  tempDay += FirstDayOfYear (year);

  // Beware the overflow, my son!
  // The jaws that bite, the claws that catch!
  if ((std::numeric_limits<uintNatural>::max () - millisecond) /
      MILLISECONDS_PER_DAY < tempDay)
    {
      throw std::range_error ("The date is too large to fit on this system.");
    }
  
  millisecondsSinceEpoch += tempDay * MILLISECONDS_PER_DAY;
}


unsigned
Date::GetYear ()
  const /* noexcept */
{
  uintNatural days = millisecondsSinceEpoch / MILLISECONDS_PER_DAY;

  // Found this online at <http://stackoverflow.com/a/5079840/232217>
  days += 719162;
  unsigned n400 = days / 146097;
  days %= 146097;
  unsigned n100 = days / 36524;
  days %= 36524;
  unsigned n4 = days / 1461;
  days %= 1461;
  unsigned n1 = days / 365;

  unsigned year = 400 * n400 + 100 * n100 + 4 * n4 + n1;
  if (n100 != 4 && n1 != 4)
    {
      ++year;
    }

  return year;
}

unsigned
Date::GetMonth ()
  const /* noexcept */
{
  // Algorithm from the ECMAScript standard (ECMA-262), version 5, section
  // 15.9.1.4.
  unsigned year = GetYear ();
  unsigned dayInYear = millisecondsSinceEpoch / MILLISECONDS_PER_DAY -
                       FirstDayOfYear (year);
  
  unsigned leapYear = (IsLeapYear (year)) ? 1 : 0;

  if (dayInYear < 31)
    return 1;
  if (dayInYear < 59+leapYear)
    return 2;
  if (dayInYear < 90+leapYear)
    return 3;
  if (dayInYear < 120+leapYear)
    return 4;
  if (dayInYear < 151+leapYear)
    return 5;
  if (dayInYear < 181+leapYear)
    return 6;
  if (dayInYear < 212+leapYear)
    return 7;
  if (dayInYear < 243+leapYear)
    return 8;
  if (dayInYear < 273+leapYear)
    return 9;
  if (dayInYear < 304+leapYear)
    return 10;
  if (dayInYear < 334+leapYear)
    return 11;
  else
    return 12;
}


unsigned
Date::GetDay ()
  const /* noexcept */
{
  // Algorithm from the ECMAScript standard (ECMA-262), version 5, section
  // 15.9.1.5.
  unsigned year = GetYear ();
  unsigned dayInYear = millisecondsSinceEpoch / MILLISECONDS_PER_DAY -
                       FirstDayOfYear (year);
  unsigned month = GetMonth ();
  
  int leapYear = (IsLeapYear (year)) ? 1 : 0;

  switch (month)
    {
    case 1:
      return dayInYear+1;
    case 2:
      return dayInYear-30;
    case 3:
      return dayInYear-58-leapYear;
    case 4:
      return dayInYear-89-leapYear;
    case 5:
      return dayInYear-119-leapYear;
    case 6:
      return dayInYear-150-leapYear;
    case 7:
      return dayInYear-180-leapYear;
    case 8:
      return dayInYear-211-leapYear;
    case 9:
      return dayInYear-242-leapYear;
    case 10:
      return dayInYear-272-leapYear;
    case 11:
      return dayInYear-303-leapYear;
    default:
      return dayInYear-333-leapYear;
    }
}


unsigned
Date::GetHour ()
  const /* noexcept */
{
  return millisecondsSinceEpoch % MILLISECONDS_PER_DAY / 1000 / 60 / 60;
}


unsigned
Date::GetMinute ()
  const /* noexcept */
{
  return millisecondsSinceEpoch % MILLISECONDS_PER_DAY / 1000 / 60 -
         GetHour () * 60;
}


unsigned
Date::GetSecond ()
  const /* noexcept */
{
  return millisecondsSinceEpoch % MILLISECONDS_PER_DAY / 1000 -
         GetHour () * 60 * 60 -
         GetMinute () * 60;
}


unsigned
Date::GetMillisecond ()
  const /* noexcept */
{
  return millisecondsSinceEpoch % MILLISECONDS_PER_DAY -
         GetHour () * 60 * 60 * 1000 -
         GetMinute () * 60 * 1000 -
         GetSecond () * 1000;
}


Date
operator+ (const Date &a, Duration b)
{
  const unsigned DAYS_PER_MONTH [] =
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  b = Reduce (b);

  signed years        = a.GetYear () + b.years;
  signed months       = a.GetMonth () + b.months;
  signed days         = a.GetDay () + b.days;
  signed hours        = a.GetHour () + b.hours;
  signed minutes      = a.GetMinute () + b.minutes;
  signed seconds      = a.GetSecond () + b.seconds;
  signed milliseconds = a.GetMillisecond () + b.milliseconds;

  if (milliseconds < 0)
    {
      seconds += milliseconds / 1000;
      milliseconds %= 1000;
      milliseconds += 1000;
    }
  else if (milliseconds > 1000)
    {
      seconds += milliseconds / 1000;
      milliseconds %= 1000;
    }

  if (seconds < 0)
    {
      minutes += seconds / 60;
      seconds %= 60;
      seconds += 60;
    }
  else if (seconds > 60)
    {
      minutes += seconds / 60;
      seconds %= 60;
    }

  if (minutes < 0)
    {
      hours += minutes / 60;
      minutes %= 60;
      minutes += 60;
    }
  else if (minutes > 60)
    {
      hours += minutes / 60;
      minutes %= 60;
    }

  if (hours < 0)
    {
      days += hours / 24;
      hours %= 24;
      hours += 24;
    }
  else if (hours > 24)
    {
      days += hours / 24;
      hours %= 24;
    }

  if (months < 1)
    {
      years += months / 12 - 1;
      months %= 12;
      months += 12;
    }
  else if (months > 12)
    {
      years += months / 12;
      months %= 12;
    }

  int leapYear = (IsLeapYear (years)) ? 1 : 0;
  int daysInMonth = DAYS_PER_MONTH[months-1];
  if (months == 2)
    daysInMonth += leapYear;

  while (days > daysInMonth)
    {
      ++months;
      if (months > 12)
        {
          years += months / 12;
          months %= 12;
          leapYear = (IsLeapYear (years)) ? 1 : 0;
        }
      days -= daysInMonth;

      daysInMonth = DAYS_PER_MONTH[months-1];
      if (months == 2)
        daysInMonth += leapYear;
    }

  daysInMonth = DAYS_PER_MONTH[months-2];
  if (months == 3)
    daysInMonth += leapYear;

  while (days < 1)
    {
      --months;
      if (months < 1)
        {
          years += months / 12;
          months %= 12;
          months += 12;

          leapYear = (IsLeapYear (years)) ? 1 : 0;
        }
      days += daysInMonth;

      daysInMonth = DAYS_PER_MONTH[months-2];
      if (months == 3)
        daysInMonth += leapYear;
    }

  return Date (years, months, days, hours, minutes, seconds, milliseconds);
}


Date
operator+ (const Duration &a, const Date &b)
{
  // Implemented in terms of operator+ above.
  return b + a;
}


Date
operator- (const Date &a, const Duration &b)
{
  // Implemented in terms of unary operator- for Duration and operator+ above.
  return a + -b;
}


Duration
operator- (const Date &a, const Date &b)
  /* noexcept */
{
  return Duration (a.GetYear () - b.GetYear (),
                   a.GetMonth () - b.GetMonth (),
                   0,
                   a.GetDay () - b.GetDay (),
                   a.GetHour () - b.GetHour (),
                   a.GetMinute () - b.GetMinute (),
                   a.GetSecond () - b.GetSecond (),
                   a.GetMillisecond () - b.GetMillisecond ());
}


std::ostream &
operator<< (std::ostream &out, const Date &d)
{
  std::locale c ("C");
  std::locale old (out.imbue (c));

  // We change the fill character, but we don't want the change to leave this
  // method.
  char fillChar = out.fill ();
  out << std::setfill ('0');

  if (d.GetYear () >= 10000)
    out << std::setw (6);
  else
    out << std::setw (4);

  out << d.GetYear ()  << '-'
      << std::setw (2) << d.GetMonth () << '-'
      << std::setw (2) << d.GetDay () << 'T'
      << std::setw (2) << d.GetHour () << ':'
      << std::setw (2) << d.GetMinute () << ':'
      << std::setw (2) << d.GetSecond () << '.'
      << std::setw (3) << d.GetMillisecond ();
  out.fill (fillChar);

  out.imbue (old);
  return out;
}


std::istream &
operator>> (std::istream &in, Date &d)
{
  // See <http://books.xmlschemata.org/relaxng/ch19-77049.html>
  // Capture groups:
  //   1. Year  2. Month  3. Day
  //   4. Hour  5. Minute  6. Second and Millisecond
  HUMMSTRUMM_ENGINE_REGEX_NS_PREFIX::regex r ("(-?\\d{4,6})-"
    "(\\d{2})-"
    "(\\d{2})T"
    "(\\d{2}):"
    "(\\d{2}):"
    "(\\d{2}(?:\\.\\d{1,3})?)"
    "(.*)");
  HUMMSTRUMM_ENGINE_REGEX_NS_PREFIX::smatch m;
                        
  std::locale cLocale ("C");
  std::locale old (in.imbue (cLocale));

  std::string s;
  in >> s;

  if (regex_match (s, m, r))
    {
      unsigned year  = std::stoi (m[1].str ());
      unsigned month = std::stoi (m[2].str ());
      unsigned day   = std::stoi (m[3].str ());
      unsigned hour  = std::stoi (m[4].str ());
      unsigned min   = std::stoi (m[5].str ());
      auto secsAndMs = std::stod (m[6].str ());
      unsigned sec   = static_cast<unsigned> (secsAndMs);
      unsigned msec  = static_cast<unsigned> ((secsAndMs-sec + 0.0005) * 1000);

      d = Date (year, month, day, hour, min, sec, msec);

      if (m[m.size ()].str ().size () > 0)
	{
          Timezone offset;
          std::stringstream ss (m[m.size ()].str ());
          ss >> offset;
          ConvertWithTimezone (d, offset);
        }
    }
  else
    {
      throw std::runtime_error ("Date malformed.");
    }

  in.imbue (old);
  return in;
}


Date
ConvertWithTimezone (const Date &inUtc, const Timezone &offsetFromUtc)
{
  return inUtc + offsetFromUtc.GetOffset ();
}


DayOfWeek
FindDayOfWeek (const Date &d)
  /* noexcept */
{
  return static_cast <DayOfWeek>
    ((d.GetMillisecondsSinceEpoch () / MILLISECONDS_PER_DAY + 4) % 7);
}


Date
GetLocalDate ()
  /* noexcept */
{
  uint64 ms = (hummstrumm::engine::core::Engine::GetEngine ()) ?
    hummstrumm::engine::core::Engine::GetEngine ()->GetClock ()->
      GetMillisecondsSinceEpoch () : 0;

  return Date (static_cast<uintNatural> (ms));
}


}
}
}