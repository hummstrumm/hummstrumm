// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2011, the people listed in the AUTHORS file. 
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

#include <windows.h>

namespace hummstrumm
{
namespace engine
{
namespace system
{


Clock::Clock (void)
  throw ()
  : //offset (0),
    //isDaylight (0),
    //timeZoneName (0),
    frequency (0)
{
  // Get clock frequency.
  LARGE_INTEGER freq;
  QueryPerformanceFrequency (&freq);
  if (freq.QuadPart == 0)
    {
      this->frequency = 0;  // wtf?  If this happens we have big problems.
    }
  else
    {
      this->frequency = 1000000000 /
        static_cast <hummstrumm::engine::types::uint64> (freq.QuadPart);
    }
}


Clock::~Clock (void)
{
}


hummstrumm::engine::types::uint64
Clock::GetHighResolutionCount (void)
  const throw ()
{
  LARGE_INTEGER time;

  // Get the timer's value.
  QueryPerformanceCounter (&time);

  return static_cast<hummstrumm::engine::types::uint64> (time.QuadPart);
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
