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
  if (this->minimumLevel != Log::MESSAGE &&
      this->minimumLevel != Log::SUCCESS &&
      this->minimumLevel != Log::WARNING &&
      this->minimumLevel != Log::ERROR)
    {
      std::wcerr << L"An invalid log level was provided.\n";
      return;
    }
  
  this->logFile = std::fopen (fileName.ToAscii (), "w");
  if (!this->logFile)
    {
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
            Log::Level level = Log::MESSAGE)
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
    case Log::ERROR:
      if (level != Log::ERROR)
        {
          return;
        }
      break;
      
    case Log::WARNING:
      if (level != Log::ERROR || level != Log::WARNING)
        {
          return;
        }
      break;
      
    case Log::SUCCESS:
      if (level == Log::MESSAGE)
        {
          return;
        }
      break;
      
    default:
      break;
    }

      
  if (!this->IsXmlMode ())
    {
      hummstrumm::engine::types::String mode;
      switch (level)
        {
        case Log::MESSAGE:
          mode = "Message";
          break;

        case Log::ERROR:
          mode = " Error ";
          break;

        case Log::WARNING:
          mode = "Warning";
          break;

        case Log::SUCCESS:
          mode = "Success";
          break;

        default:
          std::wcerr << L"The log level was invalid.";
          return;
        }
      
      std::fprintf (this->logFile, "[%s]\t%s\n", mode.ToAscii (), text.ToAscii ());
    }
  else
    {
      hummstrumm::engine::types::String mode;
      switch (level)
        {
        case Log::MESSAGE:
          mode = "message";
          break;

        case Log::ERROR:
          mode = "error";
          break;

        case Log::WARNING:
          mode = "warning";
          break;

        case Log::SUCCESS:
          mode = "success";
          break;

        default:
          std::wcerr << L"The log level wan invalid.";
          return;
        }

      std::fprintf (this->logFile, "<item level=\"%s\">%s</item>\n",
                    mode.ToAscii (), text.ToAscii ());
    }
}

}
}
}
