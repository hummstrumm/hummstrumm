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

#include <fstream>
#include <string>

namespace hummstrummengine {
namespace system {

void
Memory::Update ()
  /* noexcept */
{
  // We get our info from /proc/meminfo
  std::ifstream meminfo ("/proc/meminfo");
  
  // Our current line's text.
  std::string label;

  // What strings do we want to look for?
  const std::string totalLabel   ("MemTotal:");
  const std::string freeLabel    ("MemFree:");
  const std::string buffersLabel ("Buffers:");
  const std::string cachedLabel  ("Cached:");

  // Free memory is spread out over several labels, so we need to add them
  // together using this temp variable.
  std::size_t tmpFree;
  
  // We just need to loop through the file in search of what we want.
  while (meminfo >> label)
    {
      if (label == totalLabel)
        {
          meminfo >> totalMemory;
        }
      else if (label == freeLabel    ||
               label == buffersLabel ||
               label == cachedLabel)
        {
          meminfo >> tmpFree;
          freeMemory += tmpFree;
        }
      std::getline (meminfo, label); // Next line.
    }
}

}
}
