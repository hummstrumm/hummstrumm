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
 * Defines a difference between two Date objects.
 *
 * @file   date/duration.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-17
 * @see    Duration
 */

#ifndef HUMMSTRUMM_ENGINE_DATE_DURATION
#define HUMMSTRUMM_ENGINE_DATE_DURATION


namespace hummstrumm
{
namespace engine
{
namespace date
{

/**
 * Holds a duration of time.  A Duration object is defined to be the difference
 * between two Date objects.  The Duration object allows easy addition and
 * subtraction with Date objects in an intuitive way.
 *
 * Duration objects are relative, not absolute.  Each Duration is composed of
 * smaller durations in various time units -- years, months, weeks, days, hours,
 * minutes, seconds, and milliseconds.  We cannot assume that a year will always
 * be 365 days, however.  Certain years are leap years with an extra day.  Which
 * years are leap years depend on which absolute year one is talking about.
 * Because durations of time are created by the subtraction of two Date objects,
 * the absolute aspect of the date is conceptually lost, giving only a relative
 * aspect, the difference.  This means that Duration objects cannot easily be
 * compared.  If one wants have comparable differences, subtract the Date
 * objects using the MillisecondsBetween(const Date &, const Date &) function.
 *
 * @version 0.5
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-03-17
 * @since   0.5
 *
 * @see operator== (const Duration &, const Duration &)
 * @see operator!= (const Duration &, const Duration &)
 * @note We do not provide relational operators other than the
 * equality and inequality operators, because a Duration's exact length is
 * relative to the Date it is summed with.
 * @see operator+ (const Duration &, const Duration &)
 * @see operator- (const Duration &, const Duration &)
 * @see operator+= (Duration &, const Duration &)
 * @see operator-= (Duration &, const Duration &)
 * @see operator- (const Duration &)
 * @see operator<< (const ostream &, const Duration &)
 * @see operator>> (const istream &, const Duration &)
 * @see Reduce (const Duration &)
 * @see ReduceEquals (const Duration &, const Duration &)
 *
 * @note There are no invariants in a duration (durations of time have no
 * restrictions outside the standard ones of a @c int ), so all the members are
 * public.
 */
struct Duration : public hummstrumm::engine::core::Object
{
    HUMMSTRUMM_DECLARE_TYPE (Duration)
  public:
    /**
     * Constructs a new Duration object initialized a null duration.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-17
     * @since  0.5
     */
    Duration (void);
    /**
     * Constructs a new Duration object initialized to a specific
     * duration of time, measured in its components.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-17
     * @since  0.5
     *
     * @param [in] years        The number of years elapsed in this duration.
     * @param [in] months       The number of months elasped in this duration.
     * @param [in] weeks        The number of weeks elapsed in this duration.
     * @param [in] days         The number of days elapsed in this duration.
     * @param [in] hours        The number of hours elapsed in this duration.
     * @param [in] minutes      The number of minutes elapsed in this duration.
     * @param [in] seconds      The number of seconds elapsed in this duration.
     * @param [in] milliseconds The number of milliseconds elapsed in this
     *                          duration.
     */
    Duration (int years,
              int months,
              int weeks,
              int days,
              int hours,
              int minutes,
              int seconds,
              int milliseconds);
    /**
     * Destructs an existing Duration object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-17
     * @since  0.5
     */
    inline virtual ~Duration (void);
    
    int years;        /**< The year interval         **/
    int months;       /**< The months interval       **/
    int days;         /**< The days interval         **/
    int hours;        /**< The hours interval        **/
    int minutes;      /**< The minutes interval      **/
    int seconds;      /**< The seconds interval      **/
    int milliseconds; /**< The milliseconds interval **/
};


/**
 * Checks whether a Duration is the same as another Duration.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-23
 * @since  0.5
 * 
 * @return Whether the two Duration objects are equal.
 */
inline bool operator== (const Duration &, const Duration &) throw ();
/**
 * Checks whether a Duration does not hold the same offset as another Duration.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-23
 * @since  0.5
 * 
 * @return Whether the two Duration objects are not equal.
 */
inline bool operator!= (const Duration &, const Duration &) throw ();

/**
 * Adds a Duration to another Duration and places the result in a temporary
 * object.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-23
 * @since  0.5
 * 
 * @return The sum.
 */
inline Duration operator+ (const Duration &, const Duration &) throw ();
/**
 * Subtracts a Duration from another Duration and places the result in a
 * temporary object.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-23
 * @since  0.5
 * 
 * @return The difference.
 */
inline Duration operator- (const Duration &, const Duration &) throw ();

/**
 * Adds a Duration to another Duration and sets the latter to the result.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-23
 * @since  0.5
 * 
 * @return The sum.
 */
inline Duration &operator+= (Duration &, const Duration &) throw ();
/**
 * Subtracts a Duration from another Duration and sets the latter to the
 * result.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-23
 * @since  0.5
 * 
 * @return The difference.
 */
inline Duration &operator-= (Duration &, const Duration &) throw ();

/**
 * Negates the Duration, such that it represents a Duration of the same
 * magnitude in the opposite direction.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-23
 * @since  0.5
 * 
 * @return The negated Duration.
 */
inline Duration operator- (const Duration &) throw ();

/**
 * Prints the Duration to an output stream.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-24
 * @since  0.5
 *
 * @param [in] out The stream to write to.
 *
 * @return The output stream.
 */
std::ostream &operator<< (std::ostream &out, const Duration &);
/**
 * Sets a Duration from an input stream.  This stream must be a series of eight
 * integers.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-24
 * @since  0.5
 *
 * @param [in] in The stream to read from.
 *
 * @return The input stream.
 */
std::istream &operator>> (std::istream &in, Duration &);

/**
 * Reduces a Duration using certain duration amounts that are not relative
 * (there are always 1000 milliseconds in a second, 60 minutes in an hour,
 * etc).
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-24
 * @since  0.5
 *
 * @return The reduced Duration.
 */
Duration Reduce (Duration);
/**
 * Checks for the equality of two Duration objects, if they were to be reduced.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-24
 * @since  0.5
 *
 * @return Whether the two Duration objects, when reduced, represent the same
 * duration.
 *
 * @warning This method does not check whether two Duration objects are
 * necessarily equal, due to the still relative nature of Duration.  This method
 * uses known facts about Duration objects that are not relative to check more
 * properly for overlap.
 */
bool ReduceEquals (const Duration &a, const Duration &b);

}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_DATE_DURATION
