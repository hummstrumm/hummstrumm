// -*- c++ -*-
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

#include <sys/time.h>

namespace hummstrumm
{
namespace engine
{
namespace system
{

hummstrumm::engine::types::uint64
Clock::NANOSECONDS_PER_SECOND = 1000000000;


Clock::Clock (void)
  throw ()
  : frequency (0)
{
  try
    {
      // Get clock frequency.
      timespec monotonicResolution;
      if (-1 == clock_getres (CLOCK_MONOTONIC, &monotonicResolution))
        {
          // I guess we don't have a monotonic clock.
          clock_getres (CLOCK_REALTIME, &monotonicResolution);
        }
      this->frequency = monotonicResolution.tv_sec * NANOSECONDS_PER_SECOND +
                        monotonicResolution.tv_nsec;
    }
  catch (int i)
    {
    }
}


Clock::~Clock (void)
{
}


hummstrumm::engine::types::uint64
Clock::GetHighResolutionCount (void)
  const throw ()
{
  // Get clock count.  Try monotonic first, because it is guaranteed to keep on
  // ticking and always increase, never decrease.
  timespec monotonicCount;
  if (-1 == clock_gettime (CLOCK_MONOTONIC, &monotonicCount))
    {
      // I guess we don't have a monotonic clock.
      clock_gettime (CLOCK_REALTIME, &monotonicCount);
    }
  return monotonicCount.tv_sec * NANOSECONDS_PER_SECOND +
         monotonicCount.tv_nsec;
}


hummstrumm::engine::types::uint64
Clock::GetHighResolutionFrequency (void)
  const throw ()
{
  return this->frequency;
}


}
}
}
