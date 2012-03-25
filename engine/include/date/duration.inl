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

#ifndef HUMMSTRUMM_ENGINE_DATE_DURATION_INL
#define HUMMSTRUMM_ENGINE_DATE_DURATION_INL


namespace hummstrumm
{
namespace engine
{
namespace date
{


Duration::~Duration (void)
{ }


bool
operator== (const Duration &a, const Duration &b)
  throw ()
{
  return a.years        == b.years        &&
         a.months       == b.months       &&
         a.weeks        == b.weeks        &&
         a.days         == b.days         &&
         a.hours        == b.hours        &&
         a.minutes      == b.minutes      &&
         a.seconds      == b.seconds      &&
         a.milliseconds == b.milliseconds;
}


bool
operator!= (const Duration &a, const Duration &b)
  throw ()
{
  // Implemented in terms of == operator.
  return !(a == b);
}


Duration
operator+ (const Duration &a, const Duration &b)
  throw ()
{
  Duration temp (a);
  // Implemented in terms of += operator.
  temp += b;
  return temp;
}


Duration
operator- (const Duration &a, const Duration &b)
  throw ()
{
  Duration temp (a);
  // Implemented in terms of -= operator.
  temp -= b;
  return temp;
}


Duration &
operator+= (Duration &a, const Duration &b)
  throw ()
{
  a.years        += b.years;
  a.months       += b.months;
  a.weeks        += b.weeks;
  a.days         += b.days;
  a.hours        += b.hours;
  a.minutes      += b.minutes;
  a.seconds      += b.seconds;
  a.milliseconds += b.milliseconds;

  return a;
}


Duration &
operator-= (Duration &a, const Duration &b)
  throw ()
{
  // Implemented in terms of += and unary - operators.
  return (a += -b);
}


Duration
operator- (const Duration &a)
  throw ()
{
  Duration temp (a);
  temp.years        = -temp.years;
  temp.months       = -temp.months;
  temp.weeks        = -temp.weeks;
  temp.days         = -temp.days;
  temp.hours        = -temp.hours;
  temp.minutes      = -temp.minutes;
  temp.seconds      = -temp.seconds;
  temp.milliseconds = -temp.milliseconds;
  return temp;
}


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_DATE_DURATION_INL
