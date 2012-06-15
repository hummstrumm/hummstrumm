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

#include "hummstrummengine.hpp"

#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace hummstrumm::engine;

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  pragma warning(disable:4244)
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS

namespace hummstrumm
{
namespace engine
{
namespace debug
{

Profiler::Profiler (const char *debugName, Profiler::Units reportIn)
  : startTime (0),
    reportInUnit (reportIn),
    // So the first time will always be faster.
    lowestTime (std::numeric_limits<types::int64>::max ()),
    averageTime (0),
    numberOfRuns (0)
{
  std::strncpy (this->debugName, debugName, 24);
  this->debugName[24] = '\0';

  // Construct log message and log it.
  core::Engine::GetEngine ()->GetLog () << HummstrummSetLogging (placeholder)
    << "Profiler ``" << debugName << "'' started." << std::flush;
}

void
Profiler::Iterate ()
  /* noexcept */
{
  core::Engine *engine = core::Engine::GetEngine ();
  // Get the time and calculate how long it has been since the start.
  types::int64 endTime = engine->GetClock ()->GetHighResolutionCount ();
  std::cout << endTime << std::endl;
  types::int64 difference;

  difference = endTime - this->startTime;

  // Get the timer frequency.
  types::int64 frequency = engine->GetClock ()->GetHighResolutionFrequency ();

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

  lowestTime = std::min<long> (lowestTime, time);
  averageTime = ((averageTime * numberOfRuns) + time) / (numberOfRuns + 1);
  numberOfRuns += 1;
  startTime = engine->GetClock ()->GetHighResolutionCount ();
}

Profiler::~Profiler ()
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

      // Write it out.
      HUMMSTRUMM_LOG (message.str ().c_str (), Log::LEVEL_MESSAGE);      
      std::cout << message.str() << std::endl;
}


}
}
}
