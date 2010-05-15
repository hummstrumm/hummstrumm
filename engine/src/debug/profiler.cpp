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

#include <string>
#include <sstream>
#include <cmath>


namespace hummstrumm
{
namespace engine
{
namespace debug
{

Profiler::Profiler (hummstrumm::engine::types::String debugName)
  : startTime (hummstrumm::engine::types::Date::GetHighResolutionCount ()),
    debugName (debugName)
{
  // Construct log message.
  hummstrumm::engine::types::String message (L"Profiler ``");
  message += this->debugName;
  message += L"'' started.";

  // Log it.
  LOG (message, MESSAGE);
}

Profiler::~Profiler (void)
{
  // Get the time and calculate how long it has been since the start.
  hummstrumm::engine::types::int64 endTime (hummstrumm::engine::types::Date::
                                            GetHighResolutionCount ());
  
  hummstrumm::engine::types::int64 difference;
  
  if (endTime < this->startTime)
    {
      // An overflow or clock reset?  Whatever, we'll calculate it with the
      // constants from our <types/inttypes.hpp> header file.  Hopefully we
      // won't go through two of these, or something is really wrong.
      hummstrumm::engine::types::int64 endTimeOverflowAmount =
        endTime - INT64_MIN;
      
      hummstrumm::engine::types::int64 startTimeOverflowAmount =
        INT64_MIN - this->startTime;

      // The difference is their sum.
      difference = startTimeOverflowAmount + endTimeOverflowAmount;
    }
  else
    {
      difference = endTime - this->startTime;
    }

  // Get the timer frequency.
  hummstrumm::engine::types::int64 frequency (hummstrumm::engine::types::Date::
                   GetHighResolutionFrequency ());

  // Calculate the actual time, using tick counts and the frequency.
  double timeInSeconds (static_cast<double> (difference) / frequency);
  long   timeInMicroSeconds (std::ceil (timeInSeconds / 1000000));

  // Convert it to a string.
  std::wstringstream intToStringStream;
  intToStringStream << timeInMicroSeconds;

  // Constuct a log message.
  hummstrumm::engine::types::String message (L"Profiler ``");
  message += this->debugName;
  message += L"'' ended in ";
  message += intToStringStream.str ().c_str ();
  message += L" µsec.";

  // Write it out.
  LOG (message, MESSAGE);
}


}
}
}
