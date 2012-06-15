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

/**
 * Defines several manipulators for <tt>ostream</tt>s that have a
 * debug::logging::StreamBuffer as a streambuf.
 *
 * @file   debug/logging/manip.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-06-15
 */

#ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_MANIP
#define HUMMSTRUMM_ENGINE_DEBUG_LOGGING_MANIP

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


/**
 * An @c iostream manipulator for setting the file of a message for a log.  This
 * manipulator only works for @c ostream objects that have a
 * debug::logging::StreamBuffer as a streambuf.
 *
 * The basic usage is as follows:
 *
 * @code
 * log << SetFile (__FILE__) << "Testing file..." << std::flush;
 * @endcode
 *
 * Note that you can use the HummstrummSetLogging() macro to automatically use
 * this manipulator, the SetLine manipulator, and the SetLevel manipulator,
 * using the default values of @c __FILE__ and @c __LINE__ and the provided log
 * level.
 * 
 * @version 0.6
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-06-15
 * @since   0.6
 */
struct SetFile
{
    /**
     * Constructs and initializes the manipulator to some file.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-15
     * @since  0.6
     */
    inline SetFile (std::string);
    /**
     * Destructs the manipulator.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-15
     * @since  0.6
     */
    inline ~SetFile ();

    std::string file;
};

/**
 * An @c iostream manipulator for setting the line of a message for a log.  This
 * manipulator only works for @c ostream objects that have a
 * debug::logging::StreamBuffer as a streambuf.
 *
 * The basic usage is as follows:
 *
 * @code
 * log << SetLine (__LINE__) << "Testing file..." << std::flush;
 * @endcode
 *
 * Note that you can use the HummstrummSetLogging() macro to automatically use
 * this manipulator, the SetFile manipulator, and the SetLevel manipulator,
 * using the default values of @c __FILE__ and @c __LINE__ and the provided log
 * level.
 * 
 * @version 0.6
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-06-15
 * @since   0.6
 */
struct SetLine
{
    /**
     * Constructs and initializes the manipulator to some line.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-15
     * @since  0.6
     */
    inline SetLine (unsigned);
    /**
     * Destructs the manipulator.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-15
     * @since  0.6
     */
    inline ~SetLine ();

    unsigned line;
};

/**
 * Applies the manipulator to an @c ostream .  This only succeeds if the @c
 * ostream object has a streambuf of type debug::logging::StreamBuffer.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-06-15
 * @since  0.6
 * 
 * @return The @c ostream object passed in.
 */
std::ostream &operator<< (std::ostream &, const SetFile);
/**
 * @copydoc hummstrumm::engine::debug::logging::operator<<(std::ostream &, const SetFile)
 */
std::ostream &operator<< (std::ostream &, const SetLine);

/**
 * @def HummstrummSetLogging
 *
 * Applies the SetFile, SetLine, and SetLevel manipulators to an @c ostream .
 * This macro functions just like another manipulator.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-06-15
 * @since  0.6
 *
 * @param [in] level The logging level to apply.
 *
 * @todo Implement logging levels.
 * @todo Might need to modify this to make the logging thread safe.
 *
 * @remarks We unfortunately have to have this as a macro, because it uses the
 * default macros @c __FILE__ and @c __LEVEL__ .  If you don't feel comfortable
 * with this macro, you can call the manipulators individually (it is
 * recommended that you not do this).
 */
#define HummstrummSetLogging(level)                                     \
  hummstrumm::engine::debug::logging::SetFile (__FILE__) <<             \
  hummstrumm::engine::debug::logging::SetLine (__LINE__)


}
}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_MANIP
