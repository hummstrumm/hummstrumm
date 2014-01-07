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

/**
 * Defines several levels for log messages.
 *
 * @file   debug/logging/level.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-06-15
 * @see    Level
 */

#ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_LEVEL
#define HUMMSTRUMM_ENGINE_DEBUG_LOGGING_LEVEL

namespace hummstrummengine
{
namespace debug
{
namespace logging
{

/**
 * Holds constants representing message levels.
 * 
 * @version 0.6
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-06-15
 * @since   0.6
 */
enum class Level : unsigned
{
    info    = 0x1u << 0,        /// A simple message.
    success = 0x1u << 1,        /// Alerting of some success.
    warning = 0x1u << 2,        /// Alerting of some non-fatal error.
    error   = 0x1u << 3,        /// Elerting of some fatal error.
    all = info | success | warning | error, /// All levels
    none = 0u
};

/**
 * Applies a bitwise mask to two Level objects.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2013-07-19
 * @since  0.7
 *
 * @return A Level that represents the bitwise mask of the two arguments.
 */
inline Level operator&(const Level &, const Level &);
/**
 * Applies a bitwise or to two Level objects.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2013-07-19
 * @since  0.7
 *
 * @return A Level that represents the bitwise or of the two arguments.
 */
inline Level operator|(const Level &, const Level &);


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_LEVEL
