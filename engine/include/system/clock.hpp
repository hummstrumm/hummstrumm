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
 * Defines the Clock class, which provides system specific date-time features.
 *
 * @file   system/clock.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-12-13
 * @see    Clock
 */

#ifndef HUMMSTRUMM_ENGINE_SYSTEM_CLOCK
#define HUMMSTRUMM_ENGINE_SYSTEM_CLOCK


namespace hummstrumm
{
namespace engine
{
namespace system
{

/**
 * Provides information from the system's clock.  You can find the current
 * system clock value (in nanoseconds), find the the system clock's frequency,
 * and get the current Date both from the system time zone and from UTC.
 * Whenever possible, the high resolution clock on the system is used.
 *
 * @version 0.3
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-12-13
 * @since   0.3
 */
class Clock
{
  public:
    /**
     * Constructs a new Clock object.  Calculates the frequency of the system
     * high resolution clock.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-12-13
     * @since  0.3
     */
    Clock (void)
      throw ();
    /**
     * Destructs a Clock object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-12-13
     * @since  0.3
     */
    virtual ~Clock (void);


    /**
     * Returns the value of the high resolution clock on the system, in
     * nanoseconds.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-12-13
     * @since  0.3
     *
     * @return The current high resolution clock's value, in nanoseconds.
     *
     * @warning The high resolution clock may not have nanosecond resolution,
     * depending on the system.  You can check the clock's frequency with the
     * GetHighResolutionFrequency() method.
     */
    hummstrumm::engine::types::uint64 GetHighResolutionCount (void)
      const throw ();
    /**
     * Returns the number of nanoseconds that pass between clicks of the high
     * resolution clock.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-12-13
     * @since  0.3
     *
     * @return The high resolution clock's frequency, in nanoseconds.
     */
    hummstrumm::engine::types::uint64 GetHighResolutionFrequency (void)
      const throw ();

    /// The number of nanoseconds in a second.
    static hummstrumm::engine::types::uint64 NANOSECONDS_PER_SECOND;

  private:
    hummstrumm::engine::types::uint64 frequency; ///< The high resolution
                                                 ///< clock's frequency.
};


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_SYSTEM_CLOCK
