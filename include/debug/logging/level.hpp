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

namespace hummstrumm
{
namespace engine
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
 *
 * @note You can't instantiate this class.  It only holds constants.
 */
class Level
{
  public:
    /// A simple message.
    static constexpr unsigned info    = (0x1u << 0);
    /// Alerting of some success.
    static constexpr unsigned success = (0x1u << 1);
    /// Alerting of some non-fatal error.
    static constexpr unsigned warning = (0x1u << 2);
    /// Alerting of some fatal error.
    static constexpr unsigned error   = (0x1u << 3);
    
  private:
    Level (); // So we can't create it.
};


}
}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_LEVEL
