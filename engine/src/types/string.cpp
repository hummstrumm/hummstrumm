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
#define HUMMSTRUMM_ENGINE_SOURCE
#include "hummstrummengine.hpp"

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  pragma warning(disable:4267)
#endif // #ifdef HUMMSTRMM_PLATFORM_WINDOWS

#include <cstring>
#include <wchar.h>
#include <string>
#include <sstream>

namespace hummstrumm
{
namespace engine
{
namespace types
{

HUMMSTRUMM_IMPLEMENT_TYPE(hummstrumm::engine::types::String,
                          hummstrumm::engine::core::Object)

String::String (void)
  : string (new wchar_t [1]),
    length (0)
{
  this->string[0] = L'\0';
}


String::String (const wchar_t character)
  : string (new wchar_t [2]),
    length (1)
{
  this->string[0] = character;
  this->string[1] = L'\0';
}


String::String (const wchar_t *string)
  : string (new wchar_t [wcslen (string) + 1]),
    length (wcslen (string))
{
  wcsncpy (this->string, string, this->length + 1);
}


String::String (const char character)
  : string (new wchar_t [2]),
    length (1)
{
  // This should work on bot big and little endian machines, if I remember
  // correctly.
  this->string[0] = static_cast <wchar_t> (character);
}


String::String (const char *string)
  : string (new wchar_t [std::strlen (string) + 1]),
    length (std::strlen (string))
{
  std::string tempString (string);
  std::wostringstream stream;
  
  const std::ctype<wchar_t> &facet =
    std::use_facet<std::ctype<wchar_t> > (stream.getloc ());

  for (std::size_t i = 0; i < tempString.size (); ++i)
    {
      stream << facet.widen (tempString[i]);
    }

  wcsncpy (this->string, stream.str ().c_str (), this->length + 1);
}


String::String (const Number &value)
  : string (0), // We set these later
    length (0)
{
  std::wostringstream stream;
  stream << value.ToFloat ();
  
  this->length = stream.str ().length ();
  this->string = new wchar_t [this->length + 1];
  wcsncpy (this->string, stream.str ().c_str (), this->length + 1);
}


String::String (const String &string)
  : string (new wchar_t [string.length + 1]),
    length (string.length)
{
  wcsncpy (this->string, string.string, this->length + 1);
}


String::~String (void)
{
  if (this->string)
    {
      delete [] string;
    }
}


const String
String::operator+ (const String &string)
  const throw ()
{
  if (string.length == 0)
    {
      return *this;
    }
  else
    {
      String tempString (*this);
      tempString += string;
      return tempString;
    }
}


String &
String::operator= (const String &string)
  throw ()
{
  if (this->string)
    {
      delete [] this->string;
    }
  
  this->length = string.length;
  this->string = new wchar_t[this->length + 1];
  wcsncpy (this->string, string.string, this->length + 1);

  return *this;
}


String &
String::operator+= (const String &string)
  throw ()
{
  wchar_t *tempBuffer = new wchar_t [this->length + string.length + 1];
  wcsncpy (tempBuffer, this->string, this->length + 1);
  wcsncat (tempBuffer, string.string, string.length + 1);
  
  this->length += string.length;
  
  delete [] this->string;
  this->string = new wchar_t[this->length + 1];
  wcsncpy (this->string, tempBuffer, this->length + 1);

  return *this;
}


bool
String::operator== (const String &string)
  const throw ()
{
  return (wcscmp (this->string, string.string) == 0);
}


bool
String::operator!= (const String &string)
  const throw ()
{
  return (wcscmp (this->string, string.string) != 0);
}


bool
String::IsCharacter (void)
  const throw ()
{
  return (this->length == 1);
}
    

Number
String::GetLength (void)
  const throw ()
{
  return Number (this->length);
}
    

wchar_t &
String::operator[] (unsigned int index)
  throw ()
{
  if (index < 0 || index > this->length)
    {
      // THROW ERROR...
      return this->string[this->length];
    }
  else
    {
      return this->string[index];
    }
}


wchar_t
String::operator[] (unsigned int index)
  const throw ()
{
  if (index < 0 || index > this->length)
    {
      // THROW ERROR...
      return '\0';
    }
  else
    {
      return this->string[index];
    }
}
    

const wchar_t *
String::ToUnicode (void)
  const throw ()
{
  return this->string;
}


const char *
String::ToAscii (void)
  const throw ()
{
  std::ostringstream stream;
  const std::ctype<char> &facet = 
    std::use_facet<std::ctype<char> > (stream.getloc ());
  for (std::size_t i = 0; i < this->length; ++i)
    {
      stream << facet.narrow (this->string[i], 0);
    }
  return stream.str ().c_str ();
}

}
}
}
