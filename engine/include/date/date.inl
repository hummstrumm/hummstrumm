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

#ifndef HUMMSTRUMM_ENGINE_DATE_DATE_INL
#define HUMMSTRUMM_ENGINE_DATE_DATE_INL


namespace hummstrumm
{
namespace engine
{
namespace date
{


Date::~Date (void)
{}


hummstrumm::engine::types::uintNatural
Date::GetMillisecondsSinceEpoch (void)
  const throw ()
{
  return millisecondsSinceEpoch;
}


bool
operator== (const Date &a, const Date &b)
  throw ()
{
  return a.GetMillisecondsSinceEpoch () == b.GetMillisecondsSinceEpoch ();
}


bool
operator!= (const Date &a, const Date &b)
  throw ()
{
  // Implemented in terms of operator==.
  return !(a == b);
}


bool
operator> (const Date &a, const Date &b)
  throw ()
{
  return a.GetMillisecondsSinceEpoch () > b.GetMillisecondsSinceEpoch ();
}


bool
operator>= (const Date &a, const Date &b)
  throw ()
{
  return a.GetMillisecondsSinceEpoch () >= b.GetMillisecondsSinceEpoch ();
}


bool
operator< (const Date &a, const Date &b)
  throw ()
{
  // Implemented in terms of operator>=
  return !(a.GetMillisecondsSinceEpoch () >= b.GetMillisecondsSinceEpoch ());
}


bool
operator<= (const Date &a, const Date &b)
  throw ()
{
  // Implemented in terms of operator>
  return !(a.GetMillisecondsSinceEpoch () > b.GetMillisecondsSinceEpoch ());
}


Date &
operator+= (Date &a, const Duration &b)
  throw (hummstrumm::engine::error::OutOfRange)
{
  // Implemented in terms of operator+
  return (a = a + b);
}


Date &
operator-= (Date &a, const Duration &b)
  throw (hummstrumm::engine::error::OutOfRange)
{
  // Implemented in terms of operator-
  return (a = a - b);
}


hummstrumm::engine::types::uintNatural
DifferenceInMilliseconds (const Date &a, const Date &b)
  throw ()
{
  return a.GetMillisecondsSinceEpoch () - b.GetMillisecondsSinceEpoch ();
}


bool
IsLeapYear (const Date &d)
  throw ()
{
  return IsLeapYear (d.GetYear ());
}


bool
IsLeapYear (unsigned year)
  throw ()
{
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_DATE_DATE_INL
