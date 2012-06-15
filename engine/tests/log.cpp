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
#include <fstream>
#include <tr1/memory>

#include "hummstrummengine.hpp"
using namespace hummstrumm::engine;

int
main ()
{
  // Use make_shared<> here soon.
  std::ofstream logFile ("test-the-engine.log");
  core::Engine::Configuration params;
  params.logBackends.push_back (std::tr1::shared_ptr<debug::logging::Backend>
                                (new debug::logging::ConsoleBackend (true)));
  params.logBackends.push_back (std::tr1::shared_ptr<debug::logging::Backend>
                                (new debug::logging::FileBackend
                                 (logFile)));

  core::Engine engine (params);
  
  engine.GetLog () << debug::logging::SetFile ("fake.filename")
                   << debug::logging::SetLine (123456)
                   << "Testing..." << std::flush;
  engine.GetLog () << HummstrummSetLogging (placeholder)
                   << "Have another message." << std::flush;

  return 0;
}
