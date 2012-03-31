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
     * Constructs a new Timezone object initialized to no offset from UTC.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-02-28
     * @since  0.5
     */
    Timezone (void);
    /**
     * Constructs a new Timezone object initialized to a specific offset from
     * UTC.  The Duration object is reduced with Reduce(Duration) and then only
     * the minute and hour fields are used.  If the Duration offset is more than
     * 12 hours (either before or after UTC), an InvalidParameter exception will
     * be thrown.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-02-28
     * @since  0.5
     *
     * @param [in] offset The offset from UTC.
     *
     * @throw OutOfRange If the timezone offset is impossible.
     */
    explicit Timezone (const Duration &offset)
      throw (hummstrumm::engine::error::OutOfRange);
    /**
     * Constructs a new Timezone object initialized to the value in another
     * Timezone object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-11
     * @since  0.5
     *
     * @param [in] timezone The offset from UTC.
     */
    Timezone (const Timezone &timezone);
    /**
     * Destructs an existing Timezone object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-11
     * @since  0.5
     */
    virtual ~Timezone (void);

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
     * @return A Duration representing the current timezone's offset from UTC.
     */
    Duration GetOffset (void)
      const throw ();
    
  private:
    Duration offset;
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

/**
 * Prints the Timezone to an output stream.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-24
 * @since  0.5
 *
 * @param [in] out The stream to write to.
 *
 * @return The output stream.
 */
std::ostream &operator>> (std::ostream &out, const Timezone &);
/**
 * Sets a Timezone from an input stream.  This stream must be two integers, a
 * valid hour amount and a minute amount.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-24
 * @since  0.5
 *
 * @param [in] in The stream to read from.
 *
 * @return The input stream.
 *
 * @throw OutOfRange If the stream gives a timezone offset that is impossible.
 */
std::istream &operator<< (std::istream &in, Timezone &)
  throw (hummstrumm::engine::error::OutOfRange);

/**
 * Creates a new Timezone initialized to the current timezone offset.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-02-28
 * @since  0.5
 *
 * @return A Timezone corresponding to the current offset.
 */
Timezone
GetCurrentTimezone (void)
  throw ();




}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_DATE_TIMEZONE
