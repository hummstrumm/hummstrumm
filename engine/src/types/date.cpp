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
#define HUMMSTRUMM_ENGINE_SOURCE

#include "hummstrummengine.hpp"

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  include <windows.h>
#endif
#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
#  include <sys/time.h>
#endif

#include <ctime>

namespace hummstrumm
{
namespace engine
{
namespace types
{


#ifdef HUMMSTRUMM_PLATFORM_WINDOWS

int64
Date::GetHighResolutionCount (void)
  throw ()
{
  LARGE_INTEGER time;

  // Get the timer's value.
  QueryPerformanceCounter (&time);

  return static_cast<int64> (time);
}

int64
Date::GetHighResolutionFrequency (void)
  throw ()
{
  LARGE_INTEGER frequency;

  // Get the frequency.
  QueryPerformanceFrequency (&frequency);

  return static_cast<int64> (frequency);
}

#endif
#ifdef HUMMSTRUMM_PLATFORM_GNULINUX

int64
Date::GetHighResolutionCount (void)
  throw ()
{
  timespec ts;

  // Get the timer's value.
  clock_gettime (CLOCK_MONOTONIC, &ts);

  return static_cast <int64> (ts.tv_sec * 1000000000 +
                                     ts.tv_nsec);
}

int64
Date::GetHighResolutionFrequency (void)
  throw ()
{
  return static_cast<int64> (1000000000);
}

#endif


}
}
}
