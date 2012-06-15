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

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>

namespace hummstrumm
{
namespace engine
{
namespace debug
{
namespace logging
{


////////////////////////////////////////////////////////////////////////////////
// hummstrumm::engine::debug::logging::ConsoleBackend implementation

void
ConsoleBackend::operator() (std::time_t t, std::string file, unsigned line,
                            std::string message)
{
  // To which stream should we print?
  std::ostream &out = useStderr ? std::cerr : std::cout;

  // Get timestamp.  It's guaranteed to be 22 chars, including the terminating
  // nul.  Use std::put_time (std::gmtime (&t), "%Y-%m-%dT%H:%M:%SZ")
  // eventually.
  char tbuffer[22];
  std::strftime (tbuffer, 22, "%Y-%m-%dT%H:%M:%SZ", std::gmtime (&t));

  // Print out.
  // Format: [ 2012-06-14T02:09:18Z ] /whatever/file.cpp(52)
  //         Message here.
  out << "[ " << tbuffer << " ]"
      << " " << file << "(" << line << ")\n\t"
      << message << std::endl;

  // Eventually allow for different colors, if terminal allows it.
}


////////////////////////////////////////////////////////////////////////////////
// hummstrumm::engine::debug::logging::FileBackend implementation

FileBackend::FileBackend (std::ofstream &file)
  : fileStream (file)
{
  // Get timestamp.  It's guaranteed to be 22 chars, including the terminating
  // nul.  Use std::put_time (std::gmtime (&t), "%Y-%m-%dT%H:%M:%SZ")
  // eventually.
  std::time_t t = std::time (0);
  char tbuffer[22];
  std::strftime (tbuffer, 22, "%Y-%m-%dT%H:%M:%SZ", std::gmtime (&t));
  
  fileStream << "<?xml version=\"1.1\" encoding=\"utf-8\"?>\n\n"
             << "<log timestamp=\"" << tbuffer << "\">" << std::endl;
}

FileBackend::~FileBackend ()
{
  fileStream << "</log>" << std::flush;
}

void
FileBackend::operator() (std::time_t t, std::string file, unsigned line,
                         std::string message)
{
  // Get timestamp.  It's guaranteed to be 22 chars, including the terminating
  // nul.  Use std::put_time (std::gmtime (&t), "%Y-%m-%dT%H:%M:%SZ")
  // eventually.
  char tbuffer[22];
  std::strftime (tbuffer, 22, "%Y-%m-%dT%H:%M:%SZ", std::gmtime (&t));
  
  // XML format.  See schema for details.  Outputs <message> element.
  fileStream << "<message timestamp=\"" << tbuffer
             << "\" file=\"" << file
             << "\" line=\"" << line << "\">\n"
             << message << "\n</message>"
             << std::endl;
}


}
}
}
}

