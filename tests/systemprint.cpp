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

#include <memory>

using namespace hummstrummengine;

int
main ()
{
  core::Engine::Configuration params;
  params.logBackends.push_back (
    std::make_shared<debug::logging::ConsoleBackend> (
      debug::logging::Level::info));
  core::Engine engine (params);

  std::ostream &log = engine.GetLog ();


  log << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::info)
      << "Running on " << engine.GetPlatform ()->GetName () << std::flush;

  
  log << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::info)
      << engine.GetProcessors ()->GetNumberOfProcessors ()
      << " processors detected:\n";
  for (int i = 0; i < engine.GetProcessors ()->GetNumberOfProcessors (); ++i)
    {
      log << "  " << engine.GetProcessors ()->GetProcessorName (i);
    }
  log << " with SIMD: ";
  if (engine.GetProcessors ()->HaveSseSupport ())
    log << "SSE ";
  if (engine.GetProcessors ()->HaveSse2Support ())
    log << "SSE2 ";
  if (engine.GetProcessors ()->HaveSse3Support ())
    log << "SSE3 ";
  if (engine.GetProcessors ()->HaveSse41Support ())
    log << "SSE4.1 ";
  if (engine.GetProcessors ()->HaveSse42Support ())
    log << "SSE4.2 ";
  log << std::flush;


  log << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::info)
      << engine.GetMemory ()->GetFreeMemory ()  << " kb out of "
      << engine.GetMemory ()->GetTotalMemory () << " kb of memory free."
      << std::flush;
  
  return 0;
}
