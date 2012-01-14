// -*- c++ -*-
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

using namespace hummstrumm::engine::system;

int
main ()
{
  hummstrumm::engine::core::Engine engine;


  std::cout << "Running on " << engine.GetPlatform ()->GetName () << "\n\n";

  
  std::cout << engine.GetProcessors ()->GetNumberOfProcessors ()
            << " processors detected:\n";
  for (int i = 0; i < engine.GetProcessors ()->GetNumberOfProcessors (); ++i)
    {
      std::cout << "  " << engine.GetProcessors ()->GetProcessorName (i)
                << "\n";
    }
  std::cout << "SIMD: ";
  if (engine.GetProcessors ()->HaveSseSupport ())
    {
      std::cout << "SSE ";
    }
  if (engine.GetProcessors ()->HaveSse2Support ())
    {
      std::cout << "SSE2 ";
    }
  if (engine.GetProcessors ()->HaveSse3Support ())
    {
      std::cout << "SSE3 ";
    }
  if (engine.GetProcessors ()->HaveSse41Support ())
    {
      std::cout << "SSE4.1 ";
    }
  if (engine.GetProcessors ()->HaveSse42Support ())
    {
      std::cout << "SSE4.2 ";
    }
  std::cout << "\n\n";


  std::cout << engine.GetMemory ()->GetFreeMemory ()  << " kb out of "
            << engine.GetMemory ()->GetTotalMemory () << " kb of memory free."
            << "\n";
  
  return 0;
}
