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

/**
 * Defines the Platform class, which provides information about the platform.
 *
 * @file   system/platform.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-11-28
 * @see    Platform
 */

#ifndef HUMMSTRUMM_ENGINE_SYSTEM_PLATFORM
#define HUMMSTRUMM_ENGINE_SYSTEM_PLATFORM


namespace hummstrumm
{
namespace engine
{
namespace system
{

/**
 * Provides information about the system's operating system.  Currently, we only
 * give the system's name string.
 *
 * @version 0.3
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-11-28
 * @since   0.3
 */
class Platform
{
  public:
    /**
     * Constructs a new Platform object.  The system string is copied.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-28
     * @since  0.3
     *
     * @note On Windows, we need make the string ourselves.  We need to remember
     * to update 
     */
    Platform (void)
      throw ();
    /**
     * Destructs a Platform object.  Heap memory used to store the string is
     * freed.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-28
     * @since  0.3
     */
    virtual ~Platform (void);

    /**
     * Returns the name of the system's platform.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-28
     * @since  0.3
     *
     * @return A string containing the name of the platform.
     */
    char *GetName (void)
      const throw ();

  private:
    char *name; ///< The name of the platform.
};


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_SYSTEM_PLATFORM
