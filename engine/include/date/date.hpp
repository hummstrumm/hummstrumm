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
 * Defines a date/time class.
 *
 * @file   date/date.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @see    Date
 */

#ifndef HUMMSTRUMM_ENGINE_DATE_DATE
#define HUMMSTRUMM_ENGINE_DATE_DATE


namespace hummstrumm
{
namespace engine
{
namespace date
{


/**
 * Holds a specific instant of time.  All Date objects are measured from the
 * UNIX epoch, namely 1970-01-01T00:00:00.000.  Date objects store date and time
 * combinations without regard for timezones.  If you want to also manage
 * timezone information see the date::Timezone class.
 *
 * While an instant of time in the real world has absolutely no length and is
 * infinitely precise, time in the Humm and Strumm engine is represented with
 * millisecond precision.  For normal applications, this is more than enough.
 * If you want to use the system high-resolution timer with up to nanosecond
 * precision, look at the system::Clock class.
 *
 * For simplicity, Date objects are immutable.
 *
 * @version 0.5
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-03-25
 * @since   0.5
 */
class Date
{
  public:
    /**
     * Constructs a new Date object initialized to the UNIX epoch.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-25
     * @since  0.5
     */
    Date ();
    /**
     * Constructs a new Date object initialized to a specific number of
     * milliseconds since the UNIX epoch.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-25
     * @since  0.5
     *
     * @param [in] ms The number of milliseconds since the UNIX epoch that this
     *                Date object should hold.
     */
    explicit Date (hummstrumm::engine::types::uintNatural ms);
    /**
     * Constructs a new Date object initialized to a specific date/time
     * combination.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-25
     * @since  0.5
     *
     * @param [in] year        The specific year (\f$ 1970\leq x\f$).
     * @param [in] month       The specific month (\f$ 0<x<13\f$).
     * @param [in] day         The specific day (\f$ 0<x<\{28,29,30,31\}\f$).
     * @param [in] hour        The specific hour (\f$ 0\leq x<24\f$).
     * @param [in] minute      The specific minute (\f$ 0\leq x<60\f$).
     * @param [in] second      The specific second (\f$ 0\leq x<60\f$).
     * @param [in] millisecond The specific millisecond (\f$ 0\leq x<1000\f$).
     *
     * @throw OutOfRange When the given values are not in a range that makes
     *                   sense for dates, or are too large for the system.
     *
     * @warning The exact maximum date that can be held by this class is
     * dependent on the natural size of a @c time_t on the system on which the
     * engine was compiled.  On 32-bit systems, this is likely \f$ 2^{32}\f$
     * milliseconds after the UNIX epoch.  On 64-bit systems, it is likely
     * \f$ 2^{64}\f$ milliseconds after the UNIX epoch.
     */
    Date (unsigned year,
          unsigned month,
          unsigned day,
          unsigned hour,
          unsigned minute,
          unsigned second,
          unsigned millisecond);
    /**
     * Destructs an existing Date object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-25
     * @since  0.5
     */
    inline virtual ~Date ();

    /**
     * Retrieves the number of milliseconds that have elapsed between the UNIX
     * epoch and this Date.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-25
     * @since  0.5
     *
     * @return The milliseconds since the epoch.
     *
     * @note Because the engine currently stores times in this way, this is a
     * fast method.  Do not depend on this being the case in the future.
     */
    inline hummstrumm::engine::types::uintNatural
    GetMillisecondsSinceEpoch ()
      const /* noexcept */;

    /**
     * Retrieves the year stored by this Date.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-25
     * @since  0.5
     *
     * @return The year stored by this Date.
     *
     * @note Because the engine currently stores times in milliseconds, this is
     * not a simple accessor method; we have to compute the years each time this
     * method is called.  This may not be the case in the future.
     */
    unsigned GetYear ()
      const /* noexcept */;
    /**
     * Retrieves the month stored by this Date.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-25
     * @since  0.5
     *
     * @return The month stored by this Date.
     *
     * @note Because the engine currently stores times in milliseconds, this is
     * not a simple accessor method; we have to compute the years each time this
     * method is called.  This may not be the case in the future.
     */
    unsigned GetMonth ()
      const /* noexcept */;
    /**
     * Retrieves the day stored by this Date.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-25
     * @since  0.5
     *
     * @return The day stored by this Date.
     *
     * @note Because the engine currently stores times in milliseconds, this is
     * not a simple accessor method; we have to compute the years each time this
     * method is called.  This may not be the case in the future.
     */
    unsigned GetDay ()
      const /* noexcept */;
    /**
     * Retrieves the hour stored by this Date.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-25
     * @since  0.5
     *
     * @return The hour stored by this Date.
     *
     * @note Because the engine currently stores times in milliseconds, this is
     * not a simple accessor method; we have to compute the years each time this
     * method is called.  This may not be the case in the future.
     */
    unsigned GetHour ()
      const /* noexcept */;
    /**
     * Retrieves the minute stored by this Date.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-25
     * @since  0.5
     *
     * @return The minute stored by this Date.
     *
     * @note Because the engine currently stores times in milliseconds, this is
     * not a simple accessor method; we have to compute the years each time this
     * method is called.  This may not be the case in the future.
     */
    unsigned GetMinute ()
      const /* noexcept */;
    /**
     * Retrieves the second stored by this Date.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-25
     * @since  0.5
     *
     * @return The second stored by this Date.
     *
     * @note Because the engine currently stores times in milliseconds, this is
     * not a simple accessor method; we have to compute the years each time this
     * method is called.  This may not be the case in the future.
     */
    unsigned GetSecond ()
      const /* noexcept */;
    /**
     * Retrieves the millisecond stored by this Date.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-03-25
     * @since  0.5
     *
     * @return The millisecond stored by this Date.
     *
     * @note Because the engine currently stores times in milliseconds, this is
     * not a simple accessor method; we have to compute the years each time this
     * method is called.  This may not be the case in the future.
     */
    unsigned GetMillisecond ()
      const /* noexcept */;

  
  private:
    /** The number of elapsed milliseconds since the UNIX epoch. */
    hummstrumm::engine::types::uintNatural millisecondsSinceEpoch;
};


/**
 * Checks whether a Date is the same as another Date.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 * 
 * @return Whether the two Date objects are equal.
 */
inline bool operator== (const Date &, const Date &) /* noexcept */;
/**
 * Checks whether a Date does not hold the same date/time combination as another
 * Date.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 * 
 * @return Whether the two Date objects are not equal.
 */
inline bool operator!= (const Date &, const Date &) /* noexcept */;
/**
 * Checks whether a Date is greater than another Date.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 * 
 * @return Whether the first Date object is greater than the second Date object.
 */
inline bool operator> (const Date &, const Date &) /* noexcept */;
/**
 * Checks whether a Date is greater than or equal to another Date.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 * 
 * @return Whether the first Date object is greater than or equal to the second
 * Date object.
 */
inline bool operator>= (const Date &, const Date &) /* noexcept */;
/**
 * Checks whether a Date is less than another Date.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 * 
 * @return Whether the first Date object is less than the second Date object.
 */
inline bool operator< (const Date &, const Date &) /* noexcept */;
/**
 * Checks whether a Date is less than or equal to another Date.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 * 
 * @return Whether the first Date object is less than or equal to the second
 * Date object.
 */
inline bool operator<= (const Date &, const Date &) /* noexcept */;

/**
 * Adds a Duration to a Date object and places the result in a temporary object.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 * 
 * @return The new Date after the given Duration
 *
 * @throw OutOfRange If the resulting Date is too large or before the UNIX
 *                   epoch.
 */
Date operator+ (const Date &, Duration);
/**
 * @copydoc operator+ (const Date &, const Duration &)
 */
Date operator+ (const Duration &, const Date &);
/**
 * Subtracts a Duration from a Date object and places the result in a temporary
 * object.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 * 
 * @return The new Date before the given Duration.
 *
 * @throw OutOfRange If the resulting Date is too large or before the UNIX
 *                   epoch.
 */
Date operator- (const Date &, const Duration &);

/**
 * Subtracts a Date from another Date and places the result in a temporary
 * object.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 *
 * @return The Duration between the two Date objects.
 */
Duration operator- (const Date &, const Date &) /* noexcept */;

/**
 * Adds a Duration to a Date and sets the latter to the result.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 * 
 * @return The sum.
 *
 * @throw OutOfRange If the resulting Date is too large or before the UNIX
 *                   epoch.
 */
inline Date &operator+= (Date &, const Duration &);
/**
 * Subtracts a Duration from a Date and sets the latter to the result.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 * 
 * @return The difference.
 *
 * @throw OutOfRange If the resulting Date is too large or before the UNIX
 *                   epoch.
 */
inline Date &operator-= (Date &, const Duration &);

/**
 * Prints the Date to an output stream in ISO 8601 format.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 *
 * @param [in] out The stream to write to.
 *
 * @return The output stream.
 */
std::ostream &operator<< (std::ostream &out, const Date &);
/**
 * Sets a Date from an input stream.  This stream must be a string in ISO 8601
 * format (Exactly as yyyy-mm-ddThh:mm:ss.sss, where each element must have at
 * least one number and the dashes, colons, and "T" are literal).
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 *
 * @param [in] in The stream to read from.
 *
 * @return The input stream.
 *
 * @throw Generic    If the stream is malformed.
 * @throw OutOfRange If the resulting Date is too large or before the UNIX
 *                   epoch.
 */
std::istream &operator>> (std::istream &in, Date &);

/**
 * Gives a Date that is equivalent to a UTC Date with a given Timezone offset.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 *
 * @param [in] inUtc         The Date in UTC.
 * @param [in] offsetFromUtc The Timezone to convert to.
 *
 * @return The reduced Duration.
 *
 * @throw OutOfRange If the resulting Date is too large or before the UNIX
 *                   epoch.
 */
Date ConvertWithTimezone (const Date &inUtc, const Timezone &offsetFromUtc);
/**
 * Returns the difference between two dates in milliseconds.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 *
 * @return The number of milliseconds that elapsed from the second Date until
 * the first.
 */
inline hummstrumm::engine::types::uintNatural
DifferenceInMilliseconds (const Date &, const Date &)
  /* noexcept */;

/**
 * Returns whether the year held in the Date is a leap year.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 *
 * @return Whether the year of a Date is a leap year or not.
 */
inline bool IsLeapYear (const Date &) /* noexcept */;
/**
 * Returns whether a year is a leap year.
 *
 * @author Patrick M. Niedzielski <Patrick Niedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 *
 * @param [in] year The year to check.
 *
 * @return Whether the year is a leap year or not.
 *
 * @throw OutOfRange If the year is 0, which doesn't exist.
 */
inline bool IsLeapYear (unsigned year) /* noexcept */;

Date GetLocalDate () /* noexcept */;

/**
 * Holds a day of the seven day week.
 *
 * @version 0.5
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-03-25
 * @since   0.5
 */
enum DayOfWeek
{
  SUNDAY,    /**< Sunday.    **/
  MONDAY,    /**< Monday.    **/
  TUESDAY,   /**< Tuesday.   **/
  WEDNESDAY, /**< Wednesday. **/
  THURSDAY,  /**< Thursday.  **/
  FRIDAY,    /**< Friday.    **/
  SATURDAY,  /**< Saturday.  **/
};

/**
 * Returns the day of the week held by the Date.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-03-25
 * @since  0.5
 *
 * @return The day of the week (e.g., Sunday, Monday, ...)
 */
DayOfWeek FindDayOfWeek (const Date &) /* noexcept */;


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_DATE_DATE
