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
 * Defines the Date class.
 *
 * @file   types/date.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-13
 * @see    Date
 */

#ifndef HUMMSTRUMM_ENGINE_TYPES_DATE
#define HUMMSTRUMM_ENGINE_TYPES_DATE

#include "inttypes.hpp"

namespace hummstrumm
{
namespace engine
{
namespace types
{

/**
 * Provides time storage.  At the moment, all this class does is allow
 * you to get the microsecond count from the system high-resolution timer.
 *
 * @version 0.2
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-03-13
 * @since 0.2
 *
 * @todo This class will eventually be a time class, storing information about
 * a moment in time.
 */
class Date : public hummstrumm::engine::core::Object
{
    HUMMSTRUMM_DECLARE_TYPE(Date);
    
  public:
    Date (void);
    virtual ~Date (void);

    const String ToString (void)
      const throw ();
    const String Format (void)
      const throw ();
    const String Format (const String &format)
      const throw ();

    const String &GetDayOfTheWeek (void)
      const throw ();
    // http://c-faq.com/misc/zeller.html
    
    /**
     * Returns the system high-resolution timer value.  The frequency of the
     * timer may be found with the GetHighResolutionFrequency() method.
     *
     * This method provides a cross-platform way of accessing the
     * high-resolution system timer.  Do not assume this value means anything
     * itself; instead, use it to compare with the return value of this method
     * from different times.  This timestamp is dependent on the system and the
     * hardware timer.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-13
     * @since  0.2
     *
     * @return The system timer value.
     *
     * @warning Do not assume this value means anything specific itself.  It is
     * merely a timestamp in a 64-bit integer.
     */
    static int64 GetHighResolutionCount (void)
      throw ();
    /**
     * Returns the update frequency of the system high-resolution timer.  This
     * value is in ticks per second.
     *
     * This method provides a cross-platform way of accessing the
     * high-resolution system timer.  If you take the value returned by the
     * GetHighResolutionCount() method and divide it by the value returned by
     * this method, you will get the system timer value in seconds.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-15
     * @since  0.2
     *
     * @return The system timer frequency in ticks per second.
     */
    static int64 GetHighResolutionFrequency (void)
      throw ();

  private:
    unsigned char  year;
    unsigned char  month;
    unsigned char  day;
    unsigned char  hour;
    unsigned char  minute;
    unsigned char  second;
    uint32         microsecond;
    signed   char  timeZoneOffset;
};

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_TYPES_TIME
