// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2010, the people listed in the AUTHORS file. 
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
 * Defines several cross-platform, fixed-size integer types.
 *
 * @file   number.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-04-27
 * @see    Number
 */

#ifndef HUMMSTRUMM_ENGINE_TYPES_NUMBER
#define HUMMSTRUMM_ENGINE_TYPES_NUMBER


#include <core/object.hpp>
#include <core/type.hpp>
#include <core/pointer.hpp>


namespace hummstrumm
{
namespace engine
{
namespace types
{

/**
 * Holds a buffer of device-dependent data.  This buffer allows for specific
 * representations of data, accessing each byte of the data, and converting data
 * from one endian to another for ease of data exchange.
 *
 * @version 0.2
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-03-26
 * @since   0.2
 *
 * @todo Add trig methods.
 * @todo Add constants.
 */
class Number : public hummstrumm::engine::core::Object
{
    HUMMSTRUMM_DECLARE_TYPE (Number)
  public:
    /**
     * Constructs a new Number object initialised to zero.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (void);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (double);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (float);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (int16);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (uint16);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (int32);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (uint32);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (int64);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (uint64);
    /**
     * Constructs a new Number object initialised to the value in a RawData
     * object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    explicit Number (hummstrumm::engine::types::RawData);
    
    /**
     * Destructs a Number object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     */
    virtual ~Number (void);

    /**
     * Adds two Number objects.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The sum of the Number objects.
     */
    const Number operator+ (const Number &) const throw ();
    /**
     * Subtracts two Number objects.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The difference of the Number objects.
     */
    const Number operator- (const Number &) const throw ();
    /**
     * Multiplies two Number objects.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The product of the Number objects.
     */
    const Number operator* (const Number &) const throw ();
    /**
     * Divides two Number objects.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The quotient of the Number objects.
     */
    const Number operator/ (const Number &) const throw (...);
    /**
     * Finds the modulus of two Number objects.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The remainder of the division of Number objects.
     */
    const Number operator% (const Number &) const throw (...);

    /**
     * Makes no change to the Number object.  Seriously, why do we need this?
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the Number.
     */
    const Number operator+ (void) const throw ();
    /**
     * Returns the negative of the value of the Number.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The negative of the Number.
     */
    const Number operator- (void) const throw ();

    /**
     * Prefix increment.  Increases the value of the Number by one.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the Number, after adding one.
     */
    const Number &operator++ (void) throw ();
    /**
     * Prefix decrement.  Decreases the value of the Number by one.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the Number, after subtracting one.
     */
    const Number &operator-- (void) throw ();
    /**
     * Postfix increment.  Increases the value of the Number by one.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the Number, before adding one.
     */
    const Number  operator++ (int)  throw ();
    /**
     * Postfix decrement.  Decreases the value of the Number by one.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the Number, before subtracting one.
     */
    const Number  operator-- (int)  throw ();

    /**
     * Assigns a value to this Number.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the Number, after assignment.
     */
    const Number &operator= (const Number &) throw ();

    /**
     * Adds a Number to this current value and then assigns the resulting value
     * to this Number.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the Number, after addition.
     */
    const Number &operator+= (const Number &) throw ();
    /**
     * Subtracts a Number from this current value and then assigns the resulting
     * value to this Number.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the Number, after subtraction.
     */
    const Number &operator-= (const Number &) throw ();
    /**
     * Multplies a Number by this current value and then assigns the resulting
     * value to this Number.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the Number, after multiplication.
     */
    const Number &operator*= (const Number &) throw ();
    /**
     * Divides this current value by a Number and then assigns the resulting
     * value to this Number.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the Number, after division.
     */
    const Number &operator/= (const Number &) throw (...);
    /**
     * Divides this current value by a Number, takes the remainder, and then
     * assigns the resulting value to this Number.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the Number, after modulus.
     */
    const Number &operator%= (const Number &) throw (...);

    /**
     * Checks if a Number is equal to this Number.  Number objects are
     * considered equal if they are close enough, by nature of the IEEE float
     * numbers.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return Whether the two Number objects are equal.
     */
    bool operator== (const Number &) const throw ();
    /**
     * Checks if a Number is greater than this Number.  Number objects are
     * considered non-equal if they are far enough apart, by nature of the IEEE
     * float numbers.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return Whether this value is less than that of another Number.
     */
    bool operator<  (const Number &) const throw ();

    /**
     * Converts this Number into native C++ double.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     */
    operator double  (void) const throw ();
    /**
     * Converts this Number into a RawData array.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     */
    operator RawData (void) const throw ();

    /**
     * Finds the absolute value of the Number; that is, the value returned will
     * always be a positive distance from zero.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     *
     * @return The absolute value of this Number.
     */
    const Number abs (void) const throw ();
    /**
     * Calculates the power of the Number with a certain exponent.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     *
     * @param exponent The exponent to which to raise this Number.
     *
     * @return The power with an exponent.
     */
    const Number power (const Number &exponent) const throw (...);
    /**
     * Calculates the logarithm of the Number with a certain base.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     *
     * @param exponent The base of the logarithm.
     *
     * @return The logarithm of a base.
     */
    const Number log   (const Number &base)     const throw ();
    /**
     * Calculates the root of the Number with a certain exponent.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     *
     * @param exponent The exponent to which to take the radical of this Number.
     *
     * @return The root of a specific exponent.
     */
    const Number root  (const Number &exponent) const throw (...);

    /**
     * Rounds the Number to the nearest integer value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     *
     * @return The rounded Number.
     */
    const Number round (void) const throw ();
    /**
     * Rounds the Number to the closest integer value less than the current
     * value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     *
     * @return The rounded Number.
     */
    const Number floor (void) const throw ();
    /**
     * Rounds the Number to the closest integer value greater than the current
     * value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     *
     * @return The rounded Number.
     */
    const Number ceil  (void) const throw ();

    /**
     * Returns whether the Number is an integer.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return Whether the Number is an integer value.
     *
     * @warning Numbers close to an integer will be counted as integers.
     */
    bool IsInteger (void) const throw ();
    
  private:
    double value; /**< Value of the Number. */
};


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_TYPES_RAWDATA
