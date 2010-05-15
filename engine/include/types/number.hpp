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

// For the various relational operator shortcuts.
#include <utility>
using namespace std::rel_ops;

#include <core/object.hpp>
#include <core/type.hpp>
#include <core/pointer.hpp>

#include <types/inttypes.hpp>

namespace hummstrumm
{
namespace engine
{
namespace types
{

/**
 * Holds real number data.  Number allows all the operations of a normal IEEE
 * floating point number or a standard integer, as per the standard C++ types.
 * This allows more or less transparent integration with both C++ and the
 * ECMAScript-compatible scripting language.
 *
 * @version 0.2
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-05-08
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
    Number (short);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (unsigned short);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (int);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (unsigned int);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (long int);
    /**
     * Constructs a new Number object initialised to a value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-27
     * @since  0.2
     */
    Number (unsigned long int);
    
    /**
     * Destructs a Number object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     */
    virtual ~Number (void);

    friend const Number operator+ (const Number &, const Number &)
      throw ();
    friend const Number operator- (const Number &, const Number &)
      throw ();
    friend const Number operator* (const Number &, const Number &)
      throw ();
    friend const Number operator/ (const Number &, const Number &)
      throw (hummstrumm::engine::error::DivisionByZero);
    friend const Number operator% (const Number &, const Number &)
      throw (hummstrumm::engine::error::DivisionByZero);

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
    Number &operator= (const Number &) throw ();

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
    Number &operator+= (const Number &) throw ();
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
    Number &operator-= (const Number &) throw ();
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
    Number &operator*= (const Number &) throw ();
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
    Number &operator/= (const Number &)
      throw (hummstrumm::engine::error::DivisionByZero);
    /**
     * Divides this current value by a Number and then assigns the resulting
     * remainder value to this Number.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the Number, after modulo.
     */
    Number &operator%= (const Number &)
      throw (hummstrumm::engine::error::DivisionByZero);
    

    friend bool operator== (const Number &, const Number &) throw ();
    friend bool operator!= (const Number &, const Number &) throw ();
    friend bool operator<  (const Number &, const Number &) throw ();
    friend bool operator<= (const Number &, const Number &) throw ();
    friend bool operator>  (const Number &, const Number &) throw ();
    friend bool operator>= (const Number &, const Number &) throw ();


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
    const Number Abs (void) const throw ();
    /**
     * Returns the sign of the Number.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     *
     * @return A value corresponding to the sign of the Number.
     * @retval -1 The Number is of negative sign.
     * @retval 1  The Number is of positive sign.
     *
     * @warning Unlike std::sign(), this method does not return 0 for a value.
     * Zeros are stored as both positive and negative internally.  To check for
     * zero, regardless of sign, just use the operator==() method, as normal.
     * Whether -0 is recognised as separate from +0 is up to your compiler.
     */
   const Number Sign (void) const throw ();
    
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
    const Number Power (const Number &exponent) const throw (int);
    /**
     * Calculates the logarithm of the Number with a certain base.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     *
     * @param base The base of the logarithm.
     *
     * @return The logarithm of a base.
     */
    const Number Log   (const Number &base)     const throw ();
    /**
     * Calculates the square root of the Number.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     *
     * @return The square root.
     */
    const Number Sqrt (void) const throw (int);

    /**
     * Rounds the Number to the nearest integer value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     *
     * @return The rounded Number.
     */
    const Number Round (void) const throw ();
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
    const Number Floor (void) const throw ();
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
    const Number Ceil  (void) const throw ();

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

    /**
     * Casts the Number to a float.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     *
     * @return The value of the Number as a float.
     */
    float ToFloat (void) const throw ();
    /**
     * Casts the Number to an int.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-15
     * @since  0.2
     *
     * @return The value of the Number as a int.
     */
    int ToInteger (void) const throw ();
    
  private:
    float value; /**< Value of the Number. */
};


/**
 * Adds two Number objects.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-05-01
 * @since  0.2
 * 
 * @return The sum of the Number objects.
 */
const Number operator+ (const Number &, const Number &) throw ();

/**
 * Subtracts two Number objects.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-05-01
 * @since  0.2
 * 
 * @return The difference of the Number objects.
 */
const Number operator- (const Number &, const Number &) throw ();
/**
 * Multiplies two Number objects.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-05-01
 * @since  0.2
 * 
 * @return The product of the Number objects.
 */
const Number operator* (const Number &, const Number &) throw ();
/**
 * Divides two Number objects.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-05-01
 * @since  0.2
 * 
 * @return The quotient of the Number objects.
 *
 * @throws DivisionByZero Is the second value is 0.
 */
const Number operator/ (const Number &, const Number &)
  throw (hummstrumm::engine::error::DivisionByZero);
/**
 * Finds the modulus of two Number objects.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-05-01
 * @since  0.2
 * 
 * @return The remainder of the division of Number objects.
 *
 * @throws DivisionByZero If the second value is 0.
 */
const Number operator% (const Number &, const Number &)
  throw (hummstrumm::engine::error::DivisionByZero);


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
bool operator== (const Number &, const Number &) throw ();
/**
 * Checks if a Number is not equal to this Number.  Number objects are
 * considered equal if they are close enough, by nature of the IEEE float
 * numbers.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-05-01
 * @since  0.2
 * 
 * @return Whether the two Number objects are not equal.
 */
bool operator!= (const Number &, const Number &) throw ();
/**
 * Checks if a Number is less than this Number.  Number objects are
 * considered equal if they are close enough, by nature of the IEEE float
 * numbers.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-05-01
 * @since  0.2
 * 
 * @return Whether the first Number is less than the second.
 */
bool operator< (const Number &, const Number &) throw ();
/**
 * Checks if a Number is less than or equal to this Number.  Number objects are
 * considered equal if they are close enough, by nature of the IEEE float
 * numbers.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-05-01
 * @since  0.2
 * 
 * @return Whether the second Number is greater than the first.
 */
bool operator<= (const Number &, const Number &) throw ();
/**
 * Checks if a Number is more than this Number.  Number objects are
 * considered equal if they are close enough, by nature of the IEEE float
 * numbers.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-05-01
 * @since  0.2
 * 
 * @return Whether the first Number is greater than the second.
 */
bool operator> (const Number &, const Number &) throw ();
/**
 * Checks if a Number is more than or equal to this Number.  Number objects are
 * considered equal if they are close enough, by nature of the IEEE float
 * numbers.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-05-01
 * @since  0.2
 * 
 * @return Whether the the second Number is less than the first.
 */
bool operator>= (const Number &, const Number &) throw ();


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_TYPES_NUMBER
