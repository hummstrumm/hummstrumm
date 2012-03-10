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
 * Defines a simple representation of a Date offset from the standard UTC time.
 *
 * @file   date/timezone.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-02-28
 * @see    Timezone
 */

#ifndef HUMMSTRUMM_ENGINE_DATE_TIMEZONE
#define HUMMSTRUMM_ENGINE_DATE_TIMEZONE


namespace hummstrumm
{
namespace engine
{
namespace date
{

/**
 * For now, we'll just implement the Timezone in terms of ints, which represent
 * minutes.  That's all we need at the moment.
 *
 * @deprecated
 */
typedef int DateDuration;


/**
 * Holds a timezone offset from UTC.  For simplicity, Timezone objects are
 * immutable.
 *
 * @version 0.5
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-02-28
 * @since   0.5
 */
class Timezone : public hummstrumm::engine::core::Object
{
    HUMMSTRUMM_DECLARE_TYPE (Timezone)
  public:
    /**
     * Constructs a new Timezone object initialized to the current default local
     * offset from UTC.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-02-28
     * @since  0.5
     */
    Timezone (void);
    /**
     * Constructs a new Timezone object initialized to a specific offset from
     * UTC.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-02-28
     * @since  0.5
     *
     * @param [in] offset The offset from UTC.
     */
    explicit Timezone (const DateDuration &offset);

    /**
     * Assigns a value to this Timezone.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-02-28
     * @since  0.5
     * 
     * @return The value of the Timezone, after assignment.
     */
    Timezone &operator= (const Timezone &)
      throw ();

    /**
     * Returns the offset of this timezone from UTC.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-02-28
     * @since  0.5
     *
     * @return A DateDuration representing the current timezone's offet from
     * UTC.
     */
    DateDuration GetOffset (void)
      const throw ();

    friend bool operator== (const Timezone &, const Timezone &) throw ();
    friend bool operator!= (const Timezone &, const Timezone &) throw ();
    friend bool operator<  (const Timezone &, const Timezone &) throw ();
    friend bool operator<= (const Timezone &, const Timezone &) throw ();
    friend bool operator>  (const Timezone &, const Timezone &) throw ();
    friend bool operator>= (const Timezone &, const Timezone &) throw ();
    
  private:
    DateDuration offset;
};


/**
 * Checks whether a Timezone holds the same offset as another Timezone.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-02-28
 * @since  0.5
 * 
 * @return Whether the two Timezone objects are equal.
 */
bool operator== (const Timezone &, const Timezone &) throw ();
/**
 * Checks whether a Timezone does not hold the same offset as another Timezone.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-02-28
 * @since  0.5
 * 
 * @return Whether the two Timezone objects are not equal.
 */
bool operator!= (const Timezone &, const Timezone &) throw ();
/**
 * Checks whether a Timezone represents an earlier offset than another Timezone.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-10
 * @since  0.5
 * 
 * @return Whether the first Timezone is less than the second Timezone.
 */
bool operator< (const Timezone &, const Timezone &) throw ();
/**
 * Checks whether a Timezone represents an earlier or equal offset compared with
 * another Timezone.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-10
 * @since  0.5
 * 
 * @return Whether the second Timezone is greater than the first Timezone.
 */
bool operator<= (const Timezone &, const Timezone &) throw ();
/**
 * Checks whether a Timezone represents a later offset than another Timezone.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-10
 * @since  0.5
 * 
 * @return Whether the first Timezone is greater than the second Timezone.
 */
bool operator> (const Timezone &, const Timezone &) throw ();
/**
 * Checks whether a Timezone represents a later or equal offset compared with
 * another Timezone.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-10
 * @since  0.5
 * 
 * @return Whether the the second Timezone is less than the Timezone
 */
bool operator>= (const Timezone &, const Timezone &) throw ();


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_DATE_TIMEZONE
