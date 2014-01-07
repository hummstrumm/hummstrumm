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

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>

#ifdef HAVE_TERMCOLORS_H
#include <term-colors/termcolors.h>
using namespace termcolors;
#endif

namespace hummstrummengine
{
namespace debug
{
namespace logging
{

////////////////////////////////////////////////////////////////////////////////
// hummstrummengine::debug::logging::Backend implementation

Backend::~Backend () {}

////////////////////////////////////////////////////////////////////////////////
// hummstrummengine::debug::logging::ConsoleBackend implementation

ConsoleBackend::~ConsoleBackend () {}

void ConsoleBackend::operator()(std::time_t t, std::string file, unsigned line,
                                Level level, std::string message)
{
  // Should we even print on this level?
  if ((level & acceptLevels) == Level::none)
    return;

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
#ifdef HAVE_TERMCOLORS_H
  if (printColor)
    {
      auto colorEnd = foreground_color (color::reset);
      auto colorStart = colorEnd; // by default, change below:
      switch (level)
        {
        case hummstrummengine::debug::logging::Level::success:
          colorStart = foreground_color (color::blue);
          break;

        case hummstrummengine::debug::logging::Level::warning:
          colorStart = foreground_color (color::yellow);
          break;

        case hummstrummengine::debug::logging::Level::error:
          colorStart = foreground_color (color::red);
          break;

        default:
          // keep default
          break;
        }

      out << colorStart << bright << "[ " << tbuffer << " ]" << normal << " "
          << file << "(" << line << ")\n\t" << colorEnd << message
          << std::endl;
    }
  else
    {
#endif
      out << "[ " << tbuffer << " ]"
          << " " << file << "(" << line << ")\n\t" << message << std::endl;
#ifdef HAVE_TERMCOLORS_H
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
// hummstrummengine::debug::logging::FileBackend implementation

FileBackend::FileBackend (Level levels, std::string file)
    : Backend (levels), fileStream (file)
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

FileBackend::~FileBackend () { fileStream << "</log>" << std::endl; }

void FileBackend::operator()(std::time_t t, std::string file, unsigned line,
                             Level level, std::string message)
{
  // Should we even print on this level?
  if ((level & acceptLevels) == Level::none)
    return;

  // Get timestamp.  It's guaranteed to be 22 chars, including the terminating
  // nul.  Use std::put_time (std::gmtime (&t), "%Y-%m-%dT%H:%M:%SZ")
  // eventually.
  char tbuffer[22];
  std::strftime (tbuffer, 22, "%Y-%m-%dT%H:%M:%SZ", std::gmtime (&t));

  // Give a name to the level.
  std::string lname;
  switch (level)
    {
    case Level::info:
      lname = "info";
      break;

    case Level::success:
      lname = "success";
      break;

    case Level::warning:
      lname = "warning";
      break;

    case Level::error:
      lname = "error";
      break;

    default:
      lname = "none";
      break;
    }

  // XML format.  See schema for details.  Outputs <message> element.
  fileStream << "<message timestamp=\"" << tbuffer << "\" file=\"" << file
             << "\" line=\"" << line << "\" level=\"" << lname << "\">\n"
             << message << "\n</message>" << std::endl;
}
}
}
}
