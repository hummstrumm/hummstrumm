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

#include <iostream>
#include "hummstrummengine.hpp"

using namespace hummstrumm::engine;

int
main ()
{
  types::int64 start = 0, end = 0;
  types::int64 freq = 0;
  
  core::Engine::Configuration params;
  params.logBackends.push_back (std::tr1::shared_ptr<debug::logging::Backend>
                                (new debug::logging::ConsoleBackend (
                                  debug::logging::Level::INFO)));
  core::Engine engine (params);
  std::ostream &log = engine.GetLog ();

  const types::int64 TIME_FOR_EACH_TEST = 2 *
    engine.GetClock ()->NANOSECONDS_PER_SECOND;

  start = engine.GetClock ()->GetHighResolutionCount ();
  freq  = engine.GetClock ()->GetHighResolutionFrequency();

  log << HummstrummSetLogging (Level::INFO)
      << "This test should run for exactly 2 seconds." << std::flush;
  log << HummstrummSetLogging (Level::INFO)
      << "There are " << freq << " ns between ticks." << std::flush;

  do
    {
      end = engine.GetClock ()->GetHighResolutionCount();
    }
  while ((end - start) < TIME_FOR_EACH_TEST);
  return 0;
}
