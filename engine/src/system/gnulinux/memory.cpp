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

#include <cstdio>
#include <cstring>
#include <unistd.h>

namespace hummstrumm
{
namespace engine
{
namespace system
{


Memory::Memory (void)
  throw ()
  : totalMemory (0),
    freeMemory (0)
{
  FILE *meminfo = 0;
  
  try
    {
      // We get our info from /proc/meminfo
      meminfo = fopen ("/proc/meminfo", "r");
      if (meminfo == 0)
        {
          throw 0; // Could not open the file.
        }

      // Our current line's text.
      char line[256];

      // What strings do we want to look for?
      const char *totalLabel   = "MemTotal:";
      const char *freeLabel    = "MemFree:";
      const char *buffersLabel = "Buffers:";
      const char *cachedLabel  = "Cached:";

      int tmpFree = 0;

      // We just need to loop through the file in search of what we want.
      while (true)
        {
          if (std::fgets (line, 256, meminfo) == 0 && std::ferror (meminfo))
            {
              throw 1; // Something went wrong in reading the file.
            }
          else if (std::feof (meminfo))
            {
              break;
            }
          else if (std::strncmp (totalLabel,
                                 line,
                                 std::strlen (totalLabel)) == 0)
            {
              // We've got a hit.  Give us the total memory.
              char *number = line + std::strlen (totalLabel);
              sscanf (number, "%d", &this->totalMemory);
              continue;
            }
          else if (std::strncmp (freeLabel,
                                 line,
                                 std::strlen (freeLabel)) == 0)
            {
              // We've got a hit.  Give us the total memory.
              char *number = line + std::strlen (freeLabel);
              sscanf (number, "%d", &tmpFree);
              this->freeMemory += tmpFree;
              continue;
            }
          else if (std::strncmp (buffersLabel,
                                 line,
                                 std::strlen (buffersLabel)) == 0)
            {
              // We've got a hit.  Give us the total memory.
              char *number = line + std::strlen (buffersLabel);
              sscanf (number, "%d", &tmpFree);
              this->freeMemory += tmpFree;
              continue;
            }
          else if (std::strncmp (cachedLabel,
                                 line,
                                 std::strlen (cachedLabel)) == 0)
            {
              // We've got a hit.  Give us the total memory.
              char *number = line + std::strlen (cachedLabel);
              sscanf (number, "%d", &tmpFree);
              this->freeMemory += tmpFree;
              continue;
            }
        }
      
      // We're done here.
      std::fclose (meminfo);
    }
  catch (int i)
    {
      switch (i)
        {
        case 1:
        case 2:
          // First we close the file, as we won't need it anymore.
          std::fclose (meminfo);
        case 0:
          // We couldn't open the file, or we couldn't read from it!  Doesn't
          // matter...nothing too critical should deal with this.
          break;
        }
    }
}


Memory::~Memory (void)
{
}


int
Memory::GetTotalMemory (void)
  const throw ()
{
  return this->totalMemory;
}


int
Memory::GetFreeMemory (void)
  const throw ()
{
  return this->freeMemory;
}


}
}
}
