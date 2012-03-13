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

namespace hummstrumm
{
namespace engine
{
namespace core
{


Engine *
Engine::theEngine = 0;


Engine::Engine (void)
  throw (hummstrumm::engine::error::Generic) try
{
  std::cout << "Humm and Strumm Game Engine initializing...\n\n";

  // Set the engine pointer.
  theEngine = this;

  // Get system attributes.
  this->platform   = new hummstrumm::engine::system::Platform;
  this->processors = new hummstrumm::engine::system::Processors;
  this->memory     = new hummstrumm::engine::system::Memory;
  this->endianness = new hummstrumm::engine::system::Endianness;
  this->clock      = new hummstrumm::engine::system::Clock;
  
  try
    {
      // Create a new log.
      this->log = new hummstrumm::engine::debug::Log (HUMMSTRUMM_LOG_FILENAME,
                    hummstrumm::engine::debug::Log::HUMMSTRUMM_LOG_LOGLEVEL);
    }
  catch (hummstrumm::engine::error::Generic e)
    {
      // We couldn't open the log.  Kind of evil, but we should still be able
      // to run the game.  Just warn the user of this, and continue on.  Our
      // logging functionality is smart enough to realize that the log file
      // doesn't exist and to instead use only stdout.
      HUMMSTRUMM_LOG ("Log support has been disabled due to REASON.",
                      hummstrumm::engine::debug::Log::LEVEL_WARNING);
      this->log = 0;
    }

  HUMMSTRUMM_LOG ("Humm and Strumm Game Engine up and running.",
                   hummstrumm::engine::debug::Log::LEVEL_SUCCESS);
  std::cout << "-------------------------------------------\n\n";
}
catch (...)
  {
    theEngine = 0;
  }


Engine::Engine (const Engine::Configuration &params)
  throw (hummstrumm::engine::error::Generic) try
{
  std::cout << "Humm and Strumm Game Engine initializing...\n\n";

  // Set the engine pointer.
  theEngine = this;

  // Get system attributes.
  this->platform   = new hummstrumm::engine::system::Platform;
  this->processors = new hummstrumm::engine::system::Processors;
  this->memory     = new hummstrumm::engine::system::Memory;
  this->endianness = new hummstrumm::engine::system::Endianness;
  this->clock      = new hummstrumm::engine::system::Clock;
  
  // Use the given log.
  this->log = params.log;
  // Print the XML header.
  log->OutputSystemInfo ();

  HUMMSTRUMM_LOG ("Humm and Strumm Game Engine up and running.",
                  hummstrumm::engine::debug::Log::LEVEL_SUCCESS);
  std::cout << "-------------------------------------------\n\n";
}
catch (...)
  {
    theEngine = 0;
    throw;
  }


Engine::~Engine (void)
{
  std::cout << "\n\n-------------------------------\n"
            << "Engine going down!\n\n";
  HUMMSTRUMM_LOG ("Engine going down!",
                  hummstrumm::engine::debug::Log::LEVEL_MESSAGE);
  delete this->clock;
  delete this->endianness;
  delete this->memory;
  delete this->processors;
  delete this->platform;
}


Engine *
Engine::GetEngine (void)
  throw ()
{
  return theEngine;
}


hummstrumm::engine::debug::Log::Ptr
Engine::GetLog (void)
  throw ()
{
  return this->log;
}


hummstrumm::engine::system::Platform *
Engine::GetPlatform (void)
  throw ()
{
  return this->platform;
}


hummstrumm::engine::system::Processors *
Engine::GetProcessors (void)
  throw ()
{
  return this->processors;
}


hummstrumm::engine::system::Memory *
Engine::GetMemory (void)
  throw ()
{
  return this->memory;
}


hummstrumm::engine::system::Endianness *
Engine::GetEndianness (void)
  throw ()
{
  return this->endianness;
}

hummstrumm::engine::system::Clock *
Engine::GetClock (void)
  throw ()
{
  return this->clock;
}


}
}
}
