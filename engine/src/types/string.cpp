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

#include <cstring>

namespace hummstrumm
{
namespace engine
{
namespace types
{

HUMMSTRUMM_IMPLEMENT_TYPE(hummstrumm::engine::types::String,
                          hummstrumm::engine::core::Object)


String::Iterator::Iterator (const char *iterator)
  : iterator (iterator)
{
}



bool
String::Iterator::HasNext (void)
  const throw ()
{
  // We just need to see whether this is the NUL character.
  return (*this->iterator != '\0');
}



Character &
String::Iterator::GetNext (void)
  throw ()
{
  // Increment using the overridden ++ method, and then return the Character
  // that I now point to.  Oh, and I may for some reason throw an error.  Just
  // pass it along to the caller of this function.
  return *(++(*this));
}



String::Iterator &
String::Iterator::operator++ (void)
  throw (hummstrumm::engine::error::Iterator)
{
  // Well, if I don't have anything after me, 
  if (HasNext ())
    {
      this->iterator += Character (this->iterator).GetSequenceLength ();
    }

  return *this;
}



String::Iterator &
String::Iterator::operator++ (int)
  throw ()
{
  if (HasNext ())
    {
      this->iterator += Character (this->iterator).GetSequenceLength ();
    }

  return *this;
}



Character &
String::Iterator::PeekNext (void)
  const throw ()
{
  static Character c;

  if (HasNext ())
    {
      c = Character (this->iterator + c.GetSequenceLength ());
    }
  
  return c;
}



bool
String::Iterator::operator== (const String::Iterator &object)
  const throw ()
{
  return (this->iterator == object.iterator);
}



bool
String::Iterator::operator!= (const String::Iterator &object)
  const throw ()
{
  return !(*this == object);
}



Character &
String::Iterator::operator* (void)
  const throw ()
{
  static Character c;
  c = Character (this->iterator);
  return c;
}



String::String (void)
  throw (hummstrumm::engine::error::OutOfMemory) try
  : characters (new char [1])
{
  this->characters[0] = 0;
}



String::String (const char *utf8)
  throw (hummstrumm::engine::error::OutOfMemory,
         hummstrumm::engine::error::Unicode,
         hummstrumm::engine::error::InvalidParam) try
{
  if (utf8 == 0)
    {
      HUMMSTRUMM_THROW (InvalidParam,
                        "A null Unicode buffer pointer was passed in.");
    }

  this->characters = new char [std::strlen (utf8) + 1];
  
  std::memcpy (this->characters, utf8, std::strlen (utf8) + 1);

  if (!IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode, "An invalid UTF-8 buffer was passed in");
    }
}



String::String (const uint16_t *utf16)
  throw (hummstrumm::engine::error::OutOfMemory,
         hummstrumm::engine::error::Unicode,
         hummstrumm::engine::error::InvalidParam) try
{
  if (utf16 == 0)
    {
      HUMMSTRUMM_THROW (InvalidParam,
                        "A null Unicode buffer pointer was passed in.");
    }
  
  int length = 0;
  Character c;

  const uint16_t *iteratorUtf16 = utf16;
  unsigned char *iteratorUtf8;
  
  while (true)
    {
      if (*iteratorUtf16 == 0)
        {
          // NUL character.
          break;
        }
      else
        {
          c.FromUtf16 (iteratorUtf16);

          length += c.GetSequenceLength ();
          
          if (*iteratorUtf16 > Character::MIN_LEAD_SURROGATE &&
              *iteratorUtf16 < Character::MAX_LEAD_SURROGATE)
            {
              // Surrogate pair; increment by two UTF-16 units.
              iteratorUtf16 += 2;
            }
          else
            {
              // Just one unit; increment once.
              ++iteratorUtf16;
            }
        }
    }

  this->characters = new char [length + 1];

  iteratorUtf8  = reinterpret_cast <unsigned char *> (this->characters);
  iteratorUtf16 = utf16;

  while (true)
    { 
      if (*iteratorUtf16 == 0)
        {
          // NUL character
          iteratorUtf8 = 0x00;
          break;
        }
      else
        {
          c.FromUtf16 (iteratorUtf16);
          c.ToUtf8 (iteratorUtf8);

          iteratorUtf8 += c.GetSequenceLength ();
          
          if (*iteratorUtf16 > Character::MIN_LEAD_SURROGATE &&
              *iteratorUtf16 < Character::MAX_LEAD_SURROGATE)
            {
              // Surrogate pair; increment by two UTF-16 units.
              iteratorUtf16 += 2;
            }
          else
            {
              // Just one unit; increment once.
              ++iteratorUtf16;
            }
        }
    }
}



String::String (const uint32_t *utf32)
  throw (hummstrumm::engine::error::OutOfMemory,
         hummstrumm::engine::error::Unicode,
         hummstrumm::engine::error::InvalidParam) try
{
  if (utf32 == 0)
    {
      throw hummstrumm::engine::InvalidParam;
    }
  
  int length = 0;
  Character c;

  const uint32_t *iteratorUtf32 = utf32;
  unsigned char *iteratorUtf8;
  
  while (true)
    {
      if (*iteratorUtf32 == 0)
        {
          // NUL character.
          break;
        }
      else
        {
          c.FromUtf32 (*iteratorUtf32);

          length += c.GetSequenceLength ();
          
          ++iteratorUtf32;
        }
    }

  this->characters = new char [length + 1];

  iteratorUtf8  = reinterpret_cast <unsigned char *> (this->characters);
  iteratorUtf32 = utf32;

  while (true)
    { 
      if (*iteratorUtf32 == 0)
        {
          // NUL character
          iteratorUtf8 = 0x00;
          break;
        }
      else
        {
          c.FromUtf32 (*iteratorUtf32);
          c.ToUtf8 (iteratorUtf8);

          iteratorUtf8 += c.GetSequenceLength ();
          
          ++iteratorUtf32;
        }
    }
}



String::String (const Character &character)
  throw (hummstrumm::engine::error::OutOfMemory,
         hummstrumm::engine::error::Unicode) try
  : characters (new char [character.GetSequenceLength () + 1])
{
  character.ToUtf8 (reinterpret_cast <unsigned char *> (this->characters));
  this->characters[character.GetSequenceLength ()] = 0x00;
}



String::~String (void)
{
  delete [] this->characters;
}


const char *
String::GetRaw (void)
  const throw () try
{
  return this->characters;
}



String
String::operator+ (const String &string)
  const throw (hummstrumm::engine::error::OutOfMemory) try
{
  const uint64_t thisLength = std::strlen (this->characters);
  const uint64_t thatLength = std::strlen (string.characters);
  
  char *temp = new char [thisLength + thatLength + 1];
  std::memcpy (temp, this->characters, thisLength);
  std::memcpy (temp + thisLength, string.characters, thatLength);
  temp[thisLength + thatLength] = '\0';

  return String (temp);
}



String &
String::operator= (const String &string)
  throw (hummstrumm::engine::error::OutOfMemory) try
{
  delete [] this->characters;
  this->characters = new char [std::strlen (string.characters) + 1];
  memcpy (this->characters, string.characters,
          std::strlen (string.characters) + 1);

  return *this;
}



String &
String::operator+= (const String &string)
  throw (hummstrumm::engine::error::OutOfMemory) try
{
  *this = *this + string;

  return *this;
}



bool
String::IsValid (void)
  const throw () try
{
  // Is the pointer even valid?
  if (!this->characters)
    {
      return false;
    }
  
  char *iterator = this->characters;
  while (true)
    {
      Character c (iterator);
      if (c.IsValid ())
        {
          if (!c.IsNul ())
            {
              iterator += c.GetSequenceLength ();
              continue;
            }
          else
            {
              break;
            }
        }
      else
        {
          return false;
        }
    }
  return true;
}



bool
String::IsEmpty (void)
  const throw (hummstrumm::engine::error::Unicode) try
{
  if (!IsValid ())
    {
      throw hummstrumm::engine::err
    }

  return (this->characters[0] == 0x00);
}



void
String::Clear (void)
  throw ()
{
  *this = "";
}



uint64_t
String::GetLength (void)
  const throw (int)
{
  if (!IsValid ())
    {
      throw 0;
    }

  uint64_t length = 0;
  Character c;

  char *iterator = this->characters;

  while (*iterator != 0)
    {
      c.FromUtf8 (reinterpret_cast <unsigned char *> (iterator));
      ++length;
      iterator += c.GetSequenceLength ();
    }

  return length;
} 



String::Iterator
String::GetStart (void)
  const throw ()
{
  return String::Iterator (this->characters);
}



String::Iterator
String::GetEnd (void)
  const throw ()
{
  return String::Iterator (this->characters + std::strlen (this->characters));
}



bool
String::IsMyIterator (const String::Iterator &iterator)
  const throw (int)
{
  if (!IsValid ())
    {
      throw 0;
    }
  
  return (iterator.iterator >= this->characters && iterator.iterator <=
          this->characters + std::strlen (this->characters) + 1);
}



String::Iterator
String::operator[] (uint64_t index)
  const throw (int)
{
  if (!IsValid ())
    {
      throw 0;
    }
  if (index > GetLength ())
    {
      throw 1;
    }

  String::Iterator iterator = GetStart ();

  for (uint64_t i = 0; i < index; ++i)
    {
      iterator++;
    }

  return iterator;
}



void
String::Insert (const String::Iterator &at, const String &stringToInsert)
  throw (int)
{
  if (!IsValid ())
    {
      throw 0;
    }
  if (!IsMyIterator (at))
    {
      throw 2;
    }
  
  const uint64_t thisLength = std::strlen (this->characters);
  const uint64_t thatLength = std::strlen (stringToInsert.characters);
  const std::ptrdiff_t firstPart  = at.iterator - this->characters;
  
  char *temp = new char [thisLength + thatLength + 1];
  std::memcpy (temp, this->characters, firstPart);
  std::memcpy (temp + firstPart, stringToInsert.characters, thatLength);
  std::memcpy (temp + firstPart + thatLength,
               this->characters + firstPart,
               thisLength - firstPart);
  temp[thisLength + thatLength] = '\0';


  *this = String (temp);
}



void
String::Remove (const String::Iterator &start, const String::Iterator &end)
  throw (int)
{
  if (!IsValid ())
    {
      throw 0;
    }
  if (!IsMyIterator (start) || !IsMyIterator (end) ||
      end.iterator < start.iterator)
    {
      throw 2;
    }

  const std::ptrdiff_t firstPart = start.iterator - this->characters;
  const std::ptrdiff_t deletion  = end.iterator - start.iterator;
  const std::ptrdiff_t lastPart  = std::strlen (this->characters) -
                                     firstPart - deletion;

  char *temp = new char [firstPart + lastPart + 1];
  std::memcpy (temp, this->characters, firstPart);
  std::memcpy (temp + firstPart, this->characters + deletion, lastPart);
  temp[firstPart + lastPart] = '\0';

  *this = String (temp);
}



String
String::GetSubstring (const String::Iterator &start,
                      const String::Iterator &end)
  const throw (int)
{
  if (!IsValid ())
    {
      throw 0;
    }
  if (!IsMyIterator (start) || !IsMyIterator (end) ||
      end.iterator < start.iterator)
    {
      throw 2;
    }
  
  char *temp = new char [end.iterator - start.iterator + 1];
  std::memcpy (temp, start.iterator, end.iterator - start.iterator);
  temp[end.iterator - start.iterator] = '\0';

  return String (temp);
}



bool
String::operator== (const String &string)
  const throw (int)
{
  if (!IsValid () || !string.IsValid ())
    {
      throw 0;
    }

  if (GetLength () != string.GetLength ())
    {
      return false;
    }
  
  return (std::strcmp (this->characters, string.characters) == 0);
}



bool
String::operator!= (const String &string)
  const throw (int)
{
  return !(*this == string);
}


}
}
}
