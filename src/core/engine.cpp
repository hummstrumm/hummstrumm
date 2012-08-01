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

#if defined(HAVE_TR1_MEMORY)
#  include <tr1/memory> // This will change when we switch to C++11.
#elif defined(HAVE_MEMORY)
#  include <memory>
#endif
#include <iostream>

using namespace hummstrumm::engine;

namespace hummstrumm
{
namespace engine
{
namespace core
{


Engine *
Engine::theEngine = 0;

Engine::Engine (const Engine::Configuration params)
  try
  : logStreamBuffer (params.logBackends),
    log (&logStreamBuffer)
{
  log << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::info)
      << "Humm and Strumm Game Engine is initializing..." << std::flush;
  // Set the engine pointer.
  theEngine = this;

  // Get system attributes.
  platform   = new system::Platform;
  processors = new system::Processors;
  memory     = new system::Memory;
  endianness = new system::Endianness;
  clock      = new system::Clock;

  log << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::info)
      << "Humm and Strumm Game Engine is up and running." << std::flush;
}
catch (...)
  {
    theEngine = 0;
    throw;
  }


Engine::~Engine ()
{
  log << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::info)
      << "Humm and Strumm Game Engine is going down." << std::flush;
  
  delete this->clock;
  delete this->endianness;
  delete this->memory;
  delete this->processors;
  delete this->platform;
}


Engine *
Engine::GetEngine ()
  /* noexcept */
{
  return theEngine;
}


std::ostream &
Engine::GetLog ()
  /* noexcept */
{
  return this->log;
}


hummstrumm::engine::system::Platform *
Engine::GetPlatform ()
  /* noexcept */
{
  return this->platform;
}


hummstrumm::engine::system::Processors *
Engine::GetProcessors ()
  /* noexcept */
{
  return this->processors;
}


hummstrumm::engine::system::Memory *
Engine::GetMemory ()
  /* noexcept */
{
  return this->memory;
}


hummstrumm::engine::system::Endianness *
Engine::GetEndianness ()
  /* noexcept */
{
  return this->endianness;
}

hummstrumm::engine::system::Clock *
Engine::GetClock ()
  /* noexcept */
{
  return this->clock;
}


}
}
}
