// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2010, the people listed in the AUTHORS file. 
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

#include "hummstrummengine.hpp"

#include <string>
#include <cstdio>
#include <iostream>

namespace hummstrumm
{
namespace engine
{
namespace debug
{


Log::Log (hummstrumm::engine::types::String fileName, bool isXmlMode,
          Level minimumLevel)
  : fileName (fileName),
    isXmlMode (isXmlMode),
    minimumLevel (minimumLevel),
    logFile (0)
{
  if (this->minimumLevel != Log::LEVEL_MESSAGE &&
      this->minimumLevel != Log::LEVEL_SUCCESS &&
      this->minimumLevel != Log::LEVEL_WARNING &&
      this->minimumLevel != Log::LEVEL_ERROR)
    {
      std::wcerr << L"An invalid log level was provided.\n";
      return;
    }
  
  this->logFile = std::fopen (fileName.ToAscii (), "w");
  if (!this->logFile)
    {
      std::cout << "Log file name" << fileName.ToAscii() << std::endl;
      std::wcerr << L"The log file could not be opened.\n";
      return;
    }

  if (!this->IsXmlMode ())
    {
      std::fprintf (this->logFile, "*** Logging Started ***\n");
    }
  else
    {
      std::fprintf (this->logFile, "<?xml version=\"1.1\" encoding=\"utf-8\"?>"
                    "\n\n<log>\n");
    }
}

Log::~Log (void)
{
  if (logFile)
    {
      if (!this->IsXmlMode ())
        {
          std::fprintf (this->logFile, "*** Logging Ended ***\n");
        }
      else
        {
          std::fprintf (this->logFile, "</log>\n");
        }
      std::fclose (this->logFile);
    }
}

Log &
Log::GetLog (void)
  throw ()
{
  static Log log (HUMMSTRUMM_LOG_FILENAME,
                  HUMMSTRUMM_LOG_XMLMODE,
                  Log::HUMMSTRUMM_LOG_LOGLEVEL);
  
  return log;
}

bool
Log::IsXmlMode (void)
  const throw ()
{
  return this->isXmlMode;
}

hummstrumm::engine::types::String
Log::GetFileName (void)
  const throw ()
{
  return this->fileName;
}

Log::Level
Log::GetMinimumLevel (void)
  const throw ()
{
  return this->minimumLevel;
}

void
Log::Write (hummstrumm::engine::types::String text,
            Log::Level level)
  throw ()
{
  if (!logFile)
    {
      std::wcerr << L"Trying to write to an invalid log file.\n"
                 << std::flush;
      return;
    }

  // Mask the messages by log level.
  switch (this->minimumLevel)
    {
    case Log::LEVEL_ERROR:
      if (level != Log::LEVEL_ERROR)
        {
          return;
        }
      break;
      
    case Log::LEVEL_WARNING:
      if (level != Log::LEVEL_ERROR || level != Log::LEVEL_WARNING)
        {
          return;
        }
      break;
      
    case Log::LEVEL_SUCCESS:
      if (level == Log::LEVEL_MESSAGE)
        {
          return;
        }
      break;
      
    default:
      break;
    }

  // Get the timestamp (TODO: Make this prettier.
  hummstrumm::engine::types::int64 time (hummstrumm::engine::types::Date::
                                         GetHighResolutionCount ());
      
  if (!this->IsXmlMode ())
    {
      hummstrumm::engine::types::String mode;
      switch (level)
        {
        case Log::LEVEL_MESSAGE:
          mode = "Message";
          break;

        case Log::LEVEL_ERROR:
          mode = " Error ";
          break;

        case Log::LEVEL_WARNING:
          mode = "Warning";
          break;

		case Log::LEVEL_SUCCESS:
          mode = "Success";
          break;

        default:
          std::wcerr << L"The log level was invalid.";
          return;
        }
      
      std::fprintf (this->logFile, "%lld [%s]\t%s\n", time, mode.ToAscii (), text.ToAscii ());
    }
  else
    {
      hummstrumm::engine::types::String mode;
      switch (level)
        {
        case Log::LEVEL_MESSAGE:
          mode = "message";
          break;

        case Log::LEVEL_ERROR:
          mode = "error";
          break;

        case Log::LEVEL_WARNING:
          mode = "warning";
          break;

        case Log::LEVEL_SUCCESS:
          mode = "success";
          break;

        default:
          std::wcerr << L"The log level wan invalid.";
          return;
        }

      std::fprintf (this->logFile,
                    "<item level=\"%s\" timestamp=\"%lld\">%s</item>\n",
                    mode.ToAscii (), time, text.ToAscii ());
    }
}

}
}
}
