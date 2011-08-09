/* Humm and Strumm Video Game
 * Copyright (C) 2008-2011, the people listed in the AUTHORS file. 
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
#include <iostream>
#include "hummstrummengine.hpp"

using namespace hummstrumm::engine::system;
using namespace hummstrumm::engine::types;

int
main (int argc, char **argv)
{
  int64 start = 0, end = 0;
  int64 freq = 0;
  hummstrumm::engine::core::Engine engine;

  const int64 TIME_FOR_EACH_TEST = 2 *
    engine.GetClock ()->NANOSECONDS_PER_SECOND;

  start = engine.GetClock ()->GetHighResolutionCount ();
  freq  = engine.GetClock ()->GetHighResolutionFrequency();

  std::cout << "This test should run for exactly 2 seconds!\n";
  std::cout << "There are " << freq << " ns between ticks.\n";

  do
    {
      end = engine.GetClock ()->GetHighResolutionCount();
    }
  while ((end - start) < TIME_FOR_EACH_TEST);
  return 0;
}