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

#include "hummstrummengine.hpp"

#include <windows.h>

using hummstrumm::engine::types::uint64;

namespace hummstrumm
{
namespace engine
{
namespace system
{

uint64 Clock::NANOSECONDS_PER_SECOND = 1000000000;


Clock::Clock ()
  /* noexcept */
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
      this->frequency = NANOSECONDS_PER_SECOND /
        static_cast <uint64> (freq.QuadPart);
    }
}

uint64
Clock::GetHighResolutionCount ()
  const /* noexcept */
{
  LARGE_INTEGER time;

  // Get the timer's value.
  QueryPerformanceCounter (&time);

  return static_cast<uint64> (time.QuadPart) * this->frequency;
}

// http://msdn.microsoft.com/en-us/library/windows/desktop/ms724284.aspx
//
// The Microsoft Windows epoch is 1601-01-01.  Because why not.
//
// This date was in the Julian calendar.  Which makes it even worse, because of
// semantics not defined in the Windows documentation.
//
// Subtract this from milliseconds to get right answer.
static const uint64 WIN_EPOCH_TO_UNIX_EPOCH = 11643609600000;


uint64
Clock::GetMillisecondsSinceEpoch ()
  const /* noexcept */
{
  // Windows is silly.
  FILETIME time;
  ULARGE_INTEGER asLargeInteger;
 
  GetSystemTimeAsFileTime (&time);
  asLargeInteger.LowPart  = time.dwLowDateTime;
  asLargeInteger.HighPart = time.dwHighDateTime;

  return static_cast<uint64> (asLargeInteger.QuadPart) / 10000 +
    WIN_EPOCH_TO_UNIX_EPOCH;
}


int
Clock::GetTimezoneBias ()
  const /* noexcept */
{
  TIME_ZONE_INFORMATION tz;
  DWORD dwRange = GetTimeZoneInformation (&tz);

  return tz.Bias + (dwRange == TIME_ZONE_ID_STANDARD) ? tz.StandardBias : 0 +
                   (dwRange == TIME_ZONE_ID_DAYLIGHT) ? tz.DaylightBias : 0;
}


}
}
}
