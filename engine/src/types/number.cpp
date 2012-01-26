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

#include "hummstrummengine.hpp"

#include <cmath>
#include <cfloat>
#include <limits>

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  pragma warning(disable:4244)
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS

namespace hummstrumm
{
namespace engine
{
namespace types
{

HUMMSTRUMM_IMPLEMENT_TYPE(hummstrumm::engine::types::Number,
                          hummstrumm::engine::core::Object)

Number::Number (void)
  : value (0.0)
{}


Number::Number (double value)
  : value (value)
{}


Number::Number (float value)
  : value (value)
{}


Number::Number (int16 value)
  : value (value)
{}


Number::Number (uint16 value)
  : value (value)
{}


Number::Number (int32 value)
  : value (value)
{}


Number::Number (uint32 value)
  : value (value)
{}


Number::Number (int64 value)
  : value (value)
{}


Number::Number (uint64 value)
  : value (value)
{}
    

Number::~Number (void)
{}




const Number
operator+ (const Number &value1, const Number &value2)
  throw ()
{
  return value1.value + value2.value;
}


const Number
operator- (const Number &value1, const Number &value2)
  throw ()
{
  return value1.value - value2.value;
}


const Number
operator* (const Number &value1, const Number &value2)
  throw ()
{
  return value1.value * value2.value;
}


const Number
operator/ (const Number &value1, const Number &value2)
  throw (hummstrumm::engine::error::DivisionByZero)
{
  // Throw exception
  if (value2 == 0.0)
    {
      HUMMSTRUMM_THROW (DivisionByZero, "Division.");
    }
  
  return value1.value / value2.value;
}


const Number
operator% (const Number &value1, const Number &value2)
  throw (hummstrumm::engine::error::DivisionByZero)
{
  // Throw exception
  if (value2 == 0.0)
    {
      HUMMSTRUMM_THROW (DivisionByZero, "Modulo");
    }

  return std::fmod (value1.value, value2.value);
}


const Number
Number::operator+ (void)
  const throw ()
{
  return this->value;
}


const Number
Number::operator- (void)
  const throw ()
{
  return -this->value;
}


const Number &
Number::operator++ (void)
  throw ()
{
  ++this->value;
  return *this;
}


const Number &
Number::operator-- (void)
  throw ()
{
  --this->value;
  return *this;
}


const Number
Number::operator++ (int)
  throw ()
{
  float temp = this->value;
  this->value++;
  return temp;
}


const Number
Number::operator-- (int)
  throw ()
{
  float temp = this->value;
  this->value--;
  return temp;
}


Number &
Number::operator= (const Number &value)
  throw ()
{
  this->value = value.value;
  return *this;
}


Number &
Number::operator+= (const Number &value)
  throw ()
{
  this->value += value.value;
  return *this;
}


Number &
Number::operator-= (const Number &value)
  throw ()
{
  this->value -= value.value;
  return *this;
}


Number &
Number::operator*= (const Number &value)
  throw ()
{
  this->value *= value.value;
  return *this;
}


Number &
Number::operator/= (const Number &value)
  throw (hummstrumm::engine::error::DivisionByZero)
{
  // Throw something
  if (value == 0.0)
    {
      HUMMSTRUMM_THROW (DivisionByZero, "");
    }

  this->value /= value.value;
  return *this;
}


Number &
Number::operator%= (const Number &value)
  throw (hummstrumm::engine::error::DivisionByZero)
{
  // Throw something
  if (value == 0.0)
    {
      HUMMSTRUMM_THROW (DivisionByZero, "");
    }

  *this = *this % value;
  return *this;
}
  

bool
operator== (const Number &value1, const Number &value2)
  throw ()
{
  if (value1.value == value2.value)
    {
      return true;
    }
  else
    {
      return (std::abs (value1.value - value2.value) <
              std::numeric_limits<float>::epsilon () * 10);
    }
}


bool
operator!= (const Number &value1, const Number &value2)
  throw ()
{
  return !(value1 == value2);
}


bool
operator< (const Number &value1, const Number &value2)
  throw ()
{
  return (value1.value < value2.value);
}


bool
operator<= (const Number &value1, const Number &value2)
  throw ()
{
  return (value1 < value2) || (value1 == value2);
}


bool
operator> (const Number &value1, const Number &value2)
  throw ()
{
  return !(value1 <= value2);
}


bool
operator>= (const Number &value1, const Number &value2)
  throw ()
{
  return !(value1 < value2);
}

            
const Number
Number::Abs (void)
  const throw ()
{
  return (this->value < 0) ? -this->value : this->value;
}

const Number
Number::Sign (void)
  const throw ()
{
#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
  return ::_copysign (1.0, this->value);
#else // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS
  return ::copysign (1.0, this->value);
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS
}


const Number
Number::Power (const Number &exponent)
  const throw (int)
{
  return std::pow (this->value, exponent.ToFloat ());
}


const Number
Number::Log (const Number &base) 
  const throw ()
{
  // There is no log-base x function, so we use some basic algebra identities
  // to do our own.
  return std::log (this->value) / std::log (base.ToFloat ());
}


const Number
Number::Sqrt (void)
  const throw (int)
{
  return std::sqrt (this->value);
}


const Number
Number::Round (void)
  const throw ()
{
  return std::floor (this->value + 0.5);
}


const Number
Number::Floor (void)
  const throw ()
{
  return std::floor (this->value);
}


const Number
Number::Ceil (void)
  const throw ()
{
  return std::ceil (this->value);
}


bool
Number::IsInteger (void)
  const throw ()
{
  return (*this % Number (1) == Number (0));
}


float
Number::ToFloat (void)
  const throw ()
{
  return this->value;
}


int
Number::ToInteger (void)
  const throw ()
{
  if (IsInteger ())
    {
      return this->value;
    }
  else
    {
      return this->Round ().value;
    }
}


}
}
}
