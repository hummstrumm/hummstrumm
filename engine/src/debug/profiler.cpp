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

#include <config.h>
#include <debug/log.hpp>
#include <debug/profiler.hpp>
#include <types/inttypes.hpp>
#include <types/time.hpp>

#include <string>
#include <sstream>
#include <cmath>


namespace hummstrumm
{
namespace engine
{
namespace types
{
typedef std::wstring String;
}
namespace debug
{


Profiler::Profiler (hummstrumm::engine::types::String debugName)
  : startTime (hummstrumm::engine::types::Time::GetHighResolutionCount ()),
    debugName (debugName)
{
  // Construct log message.
  hummstrumm::engine::types::String message ("Profiler ``");
  message += this->debugName;
  message += "'' started.";

  // Log it.
  LOG (message, hummstrumm::engine::debug::Log::MESSAGE);
}

Profiler::~Profiler (void)
{
  // Get the time and calculate how long it has been since the start.
  hummstrumm::engine::types::int64 endTime (hummstrumm::engine::types::Time::
                                            GetHighResolutionCount ());
  
  hummstrumm::engine::types::int64 difference;
  
  if (endTime < this->startTime)
    {
      // An overflow or clock reset?  Whatever, we'll calculate it with the
      // constants from our <types/inttypes.hpp> header file.  Hopefully we
      // won't go through two of these, or something is really wrong.
      hummstrumm::engine::types::int64 endTimeOverflowAmount =
        endTime - hummstrumm::engine::types::INT64_MIN;
      
      hummstrumm::engine::types::int64 startTimeOverflowAmount =
        hummstrumm::engine::types::INT64_MIN - this->startTime;

      // The difference is their sum.
      difference = startTimeOverflowAmount + endTimeOverflowAmount;
    }
  else
    {
      difference = endTime - this->startTime;
    }

  // Get the timer frequency.
  hummstrumm::engine::types::int64 frequency (hummstrumm::engine::types::Time::
                   GetHighResolutionFrequency ());

  // Calculate the actual time, using tick counts and the frequency.
  double timeInSeconds (static_cast<double> (difference) / frequency);
  long   timeInMicroSeconds (std::ceil (timeInSeconds / 1000000));

  // Convert it to a string.
  std::stringstream intToStringStream;
  intToStringStream << timeInMicroSeconds;

  // Constuct a log message.
  hummstrumm::engine::types::String message ("Profiler ``");
  message += this->debugName;
  message += "'' ended in ";
  message += intToStringStream.str ();
  message += " µsec.";

  // Write it out.
  LOG (message, hummmstrumm::engine::debug::Log::MESSAGE);
}


}
}
}
