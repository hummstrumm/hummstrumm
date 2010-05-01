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

#include <iostream>

#include "config.h"
#include "debug/log.hpp"

int
main (int argc, char **argv)
{
  hummstrumm::engine::debug::Log &log =
    hummstrumm::engine::debug::Log::GetLog ();


  // Have we got the filename right?
  if (log.GetFileName () != HUMMSTRUMM_LOG_FILENAME)
    {
      std::wcerr << L"The filename is incorrect.\n";
      return 1;
    }


  // The mode of the log?
  if (log.IsXmlMode () != HUMMSTRUMM_LOG_XMLMODE)
    {
      std::wcerr << L"The mode is incorrect.\n";
      return 1;
    }
  
  
  // And what about the minimum level of the log?
  if (log.GetMinimumLevel () !=
      hummstrumm::engine::debug::Log::HUMMSTRUMM_LOG_LOGLEVEL)
    {
      std::wcerr << L"The log level is incorrect.\n";
      return 1;
    }


  log.Write (L"Testing...", hummstrumm::engine::debug::Log::MESSAGE);
  log.Write (L"Testing...", hummstrumm::engine::debug::Log::ERROR);
  log.Write (L"Testing...", hummstrumm::engine::debug::Log::WARNING);

  return 0;
}
