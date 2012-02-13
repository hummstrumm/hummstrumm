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
  core::Engine::Configuration params;
  params.log = new debug::Log ("test-the-engine.log",
                               debug::Log::LEVEL_MESSAGE);

  core::Engine engine (params);

  debug::Log log ("another-log.log", debug::Log::LEVEL_ERROR);
  HUMMSTRUMM_LOG_USING (log, "Testing...hi...", MESSAGE);
  HUMMSTRUMM_LOG_USING (log, "Testing...hi...", ERROR);
  
  HUMMSTRUMM_LOG ("Testing...", MESSAGE);
  HUMMSTRUMM_LOG ("Testing...", ERROR);
  HUMMSTRUMM_LOG ("Testing...", WARNING);

  return 0;
}
