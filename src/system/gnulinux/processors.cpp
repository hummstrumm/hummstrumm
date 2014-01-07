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
#include <limits>
#include <string>
#include <vector>
#include <unistd.h>

namespace hummstrummengine {
namespace system {

Processors::Processors ()
    /* noexcept */
    : numberOfProcessors (0),
      processorStrings (),
      sseSupport (false),
      sse2Support (false),
      sse3Support (false),
      sse41Support (false),
      sse42Support (false)
{
  // We get our info from /proc/cpuinfo
  std::ifstream cpuinfo ("/proc/cpuinfo");

  // Our current line's text.
  std::string line;

  // What strings do we want to look for?
  const std::string processorLabel ("processor");
  const std::string nameLabel1 ("model");
  const std::string nameLabel2 ("name");
  const std::string flagsLabel ("flags");

  // We just need to loop through the file in search of what we want.
  while (cpuinfo >> line)
    {
      if (line == processorLabel)
        {
          ++numberOfProcessors;
          std::getline (cpuinfo, line);
          continue;
        }
      else if (line == nameLabel1 &&                  // First word
               cpuinfo >> line && line == nameLabel2) // Second word
        {
          cpuinfo >> line;   // ignore the colon
          cpuinfo.ignore (); // ignore the space after it, too
          std::getline (cpuinfo, line);

          // Add the name.
          processorStrings.push_back (line);
          continue;
        }
      else if (line == flagsLabel)
        {
          // We've got a hit.  Get ourselves to the beginning of the actual
          // flags.
          cpuinfo >> line;   // ignore the colon
          cpuinfo.ignore (); // ignore the space after it, too
          std::getline (cpuinfo, line);

          // Now search the string for the proper flags.
          // The flags we are interested in.
          const std::string sseFlag ("sse");
          const std::string sse2Flag ("sse2");
          const std::string sse3Flag ("pni");
          const std::string sse41Flag ("sse4_1");
          const std::string sse42Flag ("sse4_2");

          if (std::string::npos != line.find (sseFlag))
            sseSupport = true;
          if (std::string::npos != line.find (sse2Flag))
            sse2Support = true;
          if (std::string::npos != line.find (sse3Flag))
            sse3Support = true;
          if (std::string::npos != line.find (sse41Flag))
            sse41Support = true;
          if (std::string::npos != line.find (sse42Flag))
            sse42Support = true;

          continue;
        }

      std::getline (cpuinfo, line); // Next line
    }

  // Make sure we got a processor.
  if (numberOfProcessors == 0)
    {
      // We couldn't open the file, we couldn't read from it, or we got a
      // result of no processors!  Fall back to POSIX interface.
      numberOfProcessors = sysconf (_SC_NPROCESSORS_ONLN);
      // Set all strings to Unknown.
      processorStrings.clear ();
      for (int i = 0; i < numberOfProcessors; ++i)
        {
          processorStrings.push_back (std::string ("Unknown"));
        }
      return;
    }

  // Make sure that we have as many names as processors.
  if (numberOfProcessors > static_cast<int>(processorStrings.size ()))
    {
      // We have more processors than names?  Just set the rest to unknown.
      for (auto i = processorStrings.size ();
           static_cast<int>(i) < numberOfProcessors; ++i)
        {
          processorStrings.push_back (std::string ("Unknown"));
        }
    }
  else if (numberOfProcessors < static_cast<int>(processorStrings.size ()))
    {
      // We have more names than processors?  Just pop off the last ones.
      for (auto i = processorStrings.size ();
           static_cast<int>(i) > numberOfProcessors; --i)
        {
          processorStrings.pop_back ();
        }
    }
}

}
}
