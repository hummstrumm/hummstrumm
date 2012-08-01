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


namespace hummstrumm
{
namespace engine
{
namespace system
{


Processors::Processors ()
  /* noexcept */
  : numberOfProcessors (1),
    processorStrings (),
    sseSupport (false),
    sse2Support (false),
    sse3Support (false),
    sse41Support (false),
    sse42Support (false)
{
  // I don't know of a way to do this with just POSIX functions, so only assume
  // one processor with unknown name.
  processorStrings.push_back (std::string ("Unknown"));
}


}
}
}
