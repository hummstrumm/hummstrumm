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

#ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_MANIP_INL
#define HUMMSTRUMM_ENGINE_DEBUG_LOGGING_MANIP_INL

#include <iostream>
#include <string>

namespace hummstrumm
{
namespace engine
{
namespace debug
{
namespace logging
{


SetFile::SetFile (std::string f)
  : file (f)
{
}

SetFile::~SetFile ()
{
}


SetLine::SetLine (unsigned l)
  : line (l)
{
}

SetLine::~SetLine ()
{
}


}
}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_MANIP_INL
