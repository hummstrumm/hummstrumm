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

#include <sstream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  pragma warning(disable:4244)
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS

namespace hummstrumm
{
namespace engine
{
namespace debug
{

Profiler::Profiler (const char *debugName, Profiler::Units reportIn, Profiler::Output out)
  : startTime (hummstrumm::engine::types::Date::GetHighResolutionCount ()),
    reportInUnit (reportIn),
    writeTo (out),
    lowestTime (hummstrumm::engine::types::INT64_MAX), // So the first time will
                                                       // always be faster.
    averageTime (0),
    numberOfRuns (0)
{
  std::strncpy (this->debugName, debugName, 24);
  this->debugName[24] = '\0';
  
  // Construct log message.
  hummstrumm::engine::types::String message ("Profiler ``");
  message += this->debugName;
  message += "'' started.";


  // Log it.
  HUMMSTRUMM_LOG (message, MESSAGE);
}

void
Profiler::Iterate (void)
  throw ()
{
  // Get the time and calculate how long it has been since the start.
  hummstrumm::engine::types::int64 endTime (hummstrumm::engine::types::Date::
                                            GetHighResolutionCount ());
  std::cout << endTime << std::endl; 
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
  hummstrumm::engine::types::int64 frequency (hummstrumm::engine::types::Date::
                   GetHighResolutionFrequency ());

  // Calculate the actual time, using tick counts and the frequency.
  double timeInSeconds (static_cast<double> (difference) / frequency);
  long   time;
  if (this->reportInUnit == REPORT_IN_SECONDS)
    {
      time = std::ceil (timeInSeconds * 100) / 100;
    }
  else if (this->reportInUnit == REPORT_IN_MILLISECONDS)
    {
      time = std::ceil (timeInSeconds * 1000);
    }
  else if (this->reportInUnit == REPORT_IN_MICROSECONDS)
    {
      time = std::ceil (timeInSeconds * 1000000);
    }
  else
    {
      // throw something...
    }

  this->lowestTime = std::min<long> (this->lowestTime, time);
  this->averageTime = ((this->averageTime * this->numberOfRuns) + time) /
    (this->numberOfRuns + 1);
  this->numberOfRuns += 1;
  this->startTime = hummstrumm::engine::types::Date::GetHighResolutionCount ();
}

Profiler::~Profiler (void)
{
  // Add a run.
  Iterate ();

  // Construct a log message.
  std::stringstream message;
  message << "Profiler ``";
  message << this->debugName;
  message << "'' stats: ";
  message << this->numberOfRuns;
  message << " Runs, Lowest Time of ";
  message << this->lowestTime;
  message << ", Average Time of ";
  message << this->averageTime;

  if (this->writeTo == LOGGER_AND_CONSOLE)
    {
      // Write it out.
      HUMMSTRUMM_LOG (message.str ().c_str (), MESSAGE);      
      std::cout << message.str() << std::endl;
    }
  else if (this->writeTo == CONSOLE)
    {
      std::cout << message.str() << std::endl;
    }
  else if (this->writeTo == LOGGER)
    {
      HUMMSTRUMM_LOG (message.str ().c_str (), MESSAGE);
    }
  else
    {
      // throw something ...
    }
}


}
}
}
