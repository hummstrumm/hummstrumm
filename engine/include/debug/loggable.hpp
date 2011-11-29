// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2011, the people listed in the AUTHORS file. 
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
 * Defines the Loggable class.
 *
 * @file   debug/loggable.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2011-11-29
 * @see    Loggable
 */

#ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGABLE
#define HUMMSTRUMM_ENGINE_DEBUG_LOGGABLE


namespace hummstrumm
{
namespace engine
{
namespace debug
{

/**
 * Anything in the engine which can be printed to a Log.  Each class that is
 * Loggable will implement the code to print it to a String that can be logged.
 *
 * @version 0.5
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2011-11-29
 * @since   0.5
 */
class Loggable
{
    friend class Log; // Only the log can use the method here.
    
  protected:
    /**
     * Creates a String that contains debug information about the object in a
     * loggable form.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-11-29
     * @since  0.5
     *
     * @return A representation of the object that can be logged.
     */
    virtual hummstrumm::engine::types::String GetLoggableString (void)
      const throw () = 0;
};

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGABLE
