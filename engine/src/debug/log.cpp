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

namespace hummstrumm
{
namespace engine
{
namespace debug
{


Log *
Log::theLog = 0;


Log::Log (hummstrumm::engine::types::String fileName,
          Level minimumLevel)
throw (hummstrumm::engine::error::Generic)
  : fileName (fileName),
    minimumLevel (minimumLevel),
    logFile (0),
    currentId (0)
{
  // Make sure this is the only Log.  Throw an error otherwise.
  if (theLog != 0)
    {
      HUMMSTRUMM_THROW (Generic, "A second log is being created.");
    }

  // Print to console.
  std::printf ("Opening log...");

  // Make sure we've a valid log level.  That some idiot didn't try to pass the
  // value 32 to the Log via casting.
  if (this->minimumLevel != Log::LEVEL_MESSAGE &&
      this->minimumLevel != Log::LEVEL_SUCCESS &&
      this->minimumLevel != Log::LEVEL_WARNING &&
      this->minimumLevel != Log::LEVEL_ERROR)
    {
      std::fprintf (stderr, "failed\n\tAn invalid log level was provided.\n");
      return;
    }

  // Open the Log file.
  this->logFile = std::fopen (fileName.c_str (), "w");
  if (!this->logFile)
    {
      std::fprintf (stderr, "failed\n\tThe log file could not be opened.\n");
      return;
    }

  // Print the XML header.
  OutputHeader ();

  // Alert the user we've created the log.
  std::printf ("done\n");

  // Set the singleton pointer to this object.
  theLog = this;
}


Log::~Log (void)
{
  if (this->logFile)
    {
      // Print the last part of the XML and close the file.
      OutputFooter ();
      std::fclose (this->logFile);
    }
}


void
Log::OutputHeader (void)
  throw ()
{
  // Get the string for the minimum level for events in the log.
  const char *mode = 0;
  switch (this->minimumLevel)
    {
    case Log::LEVEL_ERROR:
      mode = "error";
      break;

    case Log::LEVEL_WARNING:
      mode = "warning";
      break;

    case Log::LEVEL_SUCCESS:
      mode = "success";
      break;

    case Log::LEVEL_MESSAGE:
      mode = "message";
      break;
    }

  // Get system attributes.
  hummstrumm::engine::core::Engine *engine =
    hummstrumm::engine::core::Engine::GetEngine ();

  hummstrumm::engine::types::String platform =
    engine->GetPlatform ()->GetName ();
  
  hummstrumm::engine::types::String processor;
  for (int i = 0; i < engine->GetProcessors ()->GetNumberOfProcessors (); ++i)
    {
      processor += "\n      <processor>";
      processor += engine->GetProcessors ()->GetProcessorName (i);
      processor += "</processor>";
    }

  int ram = engine->GetMemory ()->GetTotalMemory ();

  // Print it all out.
  std::fprintf (this->logFile,
                "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\n"
                "<log>\n\n"
                "<header>\n"
                "  <timestamp time=\"0\" date=\"0\" />\n"
                "  <level>%s</level>\n"
                "  <system>\n"
                "    <platform>%s</platform>\n"
                "    <processors>%s\n    </processors>\n"
                "    <memory>%d KiB</memory>\n"
                "  </system>\n"
                "</header>",
                mode,
                platform.c_str (),
                processor.c_str (),
                ram);
  std::fflush (this->logFile);
}


void
Log::OutputFooter (void)
  throw ()
{
  std::fprintf (this->logFile,
                "\n\n</log>");
  std::fflush (this->logFile);
}
  

Log &
Log::GetLog (void)
  throw (hummstrumm::engine::error::Generic)
{
  if (theLog == 0)
    {
      HUMMSTRUMM_THROW (Generic, "A log hasn't yet been created.");
    }
  
  return *theLog;
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
            hummstrumm::engine::types::String fileName,
            int lineNumber,
            hummstrumm::engine::types::String function,
            Log::Level level)
  throw ()
{
  if (!logFile)
    {
      std::cerr << "Trying to write to an invalid log file.\n";
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

  // Get the timestamp (TODO: Make this prettier).
  /*hummstrumm::engine::types::int64 time (hummstrumm::engine::types::Date::
                                         GetHighResolutionCount ());*/
      
  const char *mode = 0;
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
    }

  std::fprintf (this->logFile,
                "\n\n<event>\n"
                "  <id>%d</id>\n"
                "  <level>%s</level>\n"
                "  <timestamp time=\"0\" date=\"0\" />\n"
                "  <file>%s</file>\n"
                "  <function>%s</function>\n"
                "  <line>%d</line>\n"
                "  <message>%s</message>\n"
                "</event>",
                ReturnAndIncrementId (),
                mode,
                fileName.c_str (),
                function.c_str (),
                lineNumber,
                text.c_str ());
}


int
Log::ReturnAndIncrementId (void)
  throw ()
{
  return ++currentId;
}


}
}
}
