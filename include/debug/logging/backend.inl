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

#ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_BACKEND_INL
#define HUMMSTRUMM_ENGINE_DEBUG_LOGGING_BACKEND_INL

namespace hummstrummengine
{
namespace debug
{
namespace logging
{


////////////////////////////////////////////////////////////////////////////////
// hummstrummengine::debug::logging::Backend implementation

Backend::Backend (Level levels)
  : acceptLevels (levels)
{
}


////////////////////////////////////////////////////////////////////////////////
// hummstrummengine::debug::logging::ConsoleBackend implementation

ConsoleBackend::ConsoleBackend (Level levels, bool useStderr,
                                bool printColor)
  : Backend (levels),
    useStderr (useStderr),
    printColor (printColor)
{
}


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_BACKEND_INL
