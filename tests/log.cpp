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

#include <iostream>
#include <fstream>
#include <memory>

#include "hummstrummengine.hpp"
using namespace hummstrumm::engine;

int
main ()
{
  typedef std::shared_ptr<debug::logging::Backend> ptr;
  ptr console = std::make_shared<debug::logging::ConsoleBackend> (
    debug::logging::Level::warning, true,
#ifdef HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS
      false);
#else
      true);
#endif
  ptr file = std::make_shared<debug::logging::FileBackend> (
    debug::logging::Level::info | debug::logging::Level::warning,
    "test-the-engine.log");
  core::Engine::Configuration params;
  params.logBackends.push_back (console);
  params.logBackends.push_back (file);
  core::Engine engine (params);
  
  engine.GetLog () << debug::logging::SetFile ("fake.filename")
                   << debug::logging::SetLine (123456)
                   << debug::logging::SetLevel (debug::logging::Level::warning)
                   << "Testing..." << std::flush;
  engine.GetLog () << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::info)
                   << "Have another message." << std::flush;

  return 0;
}
