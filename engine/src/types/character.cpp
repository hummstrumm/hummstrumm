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
#define HUMMSTRUMM_ENGINE_SOURCE
#include "hummstrummengine.hpp"

#include <cstdlib>
#include <cstring>

namespace hummstrumm
{
namespace engine
{
namespace types
{

HUMMSTRUMM_IMPLEMENT_TYPE(hummstrumm::engine::types::Character,
                          hummstrumm::engine::core::Object)


Character::Character (void)
  throw ()
{
  
  // Set all bytes to 0, effectively making this a NUL character.
  std::memset (this->octets, 0, 4);
}


Character::Character (char asciiChar)
  throw (hummstrumm::engine::error::OutOfRange)
{
  // ASCII is always one byte, but this could be a non ASCII character.
  if (asciiChar < 0 || asciiChar > 127)
    {
      HUMMSTRUMM_THROW (OutOfRange,
                        "The character was not in the ASCII range.");
    }
  else
    {
      // This char is perfectly fine.
      this->octets[0] = asciiChar;
      this->octets[1] = 0x00;
    }
}


Character::Character (unsigned char octet1,
                      unsigned char octet2,
                      unsigned char octet3,
                      unsigned char octet4)
  throw (hummstrumm::engine::error::Unicode)
{
  // Create a temporary, contiguous array for passing to the method FromUtf8().
  unsigned char temp[4];
  temp[0] = octet1;
  temp[1] = octet2;
  temp[2] = octet3;
  temp[3] = octet4;

  // Convert from UTF-8.
  FromUtf8 (temp);
}


Character::Character (uint16 surrogate1,
                      uint16 surrogate2)
  throw (hummstrumm::engine::error::Unicode,
         hummstrumm::engine::error::OutOfMemory)
{
  // Create a temporary, contiguous array to pass to the method FromUtf16().
  uint16_t temp[2];
  temp[0] = surrogate1;
  temp[1] = surrogate2;

  // Convert from UTF-16.
  FromUtf16 (temp);
}

  
Character::Character (uint32 codePoint)
  throw (hummstrumm::engine::error::Unicode)
{
   // Convert from UTF-32.
   FromUtf32 (&codePoint);
}


Character::Character (const Character &character)
  throw (hummstrumm::engine::error::Unicode)
{
  
  if (!character.IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode, "Invalid Character.");
    }
  
  // Copy straight through the octets from the other Character.
  std::memcpy (this->octets, character.octets, 4);
}


Character::Character (const char *octetsFromString)
  throw (hummstrumm::engine::error::InvalidParam,
         hummstrumm::engine::error::Unicode)
{
  if (octetsFromString == 0)
    {
      HUMMSTRUMM_THROW (InvalidParam);
    }
  
  // We use this in the String class.  Copy the octets from part of a String.
  // Create a temporary, contiguous array for passing to the method FromUtf8().
  unsigned char temp[4];

  int length = GetSequenceLength (octetsFromString[0]);
  if (length > 4 || length < 1)
    {
      HUMMSTRUMM_THROW (Unicode, "Invalid sequence length.");
    }

  std::memcpy (temp,
               octetsFromString,
               length);

  // Convert from UTF-8.
  FromUtf8 (temp);
}


Character::~Character (void)
{
}


bool
Character::IsValid ()
  const throw ()
{
  // ***NOTE***
  //   Characters above U+10FFFF are allowed by ISO/IEC 10646 description of
  //   UTF-8, but they do not map to any Unicode characters.  We follow the RFC
  //   3629 description, which forbids these.  This is what "Non-Unicode
  //   character" means below.
  
  // Check for invalid octets.
  if (this->octets[0] == 0xC0u || // Overlong sequence
      this->octets[0] == 0xC1u || // Overlong sequence
      this->octets[0] >= 0xF5u)   // Non-Unicode character
    {
      return false;
    }
  for (unsigned char i = 1; i < GetSequenceLength (); ++i)
    {
      if (this->octets[i] < 0x80u || // Malformed sequence
          this->octets[i] > 0xC0u)   // Malformed sequence
        {
          return false;
        }
    }

  // Check for surrogate pairs.
  if (this->octets[0] == 0xEDu &&
      this->octets[1] >= 0xA0u && this->octets[1] <= 0xBFu &&
      this->octets[2] >= 0x80u && this->octets[2] <= 0xBFu)
    {
      return false;
    }

  // Check for invalid characters.  These would be U+FFFE and U+FFFF.
  if (this->octets[0] == 0xEFu &&
      this->octets[1] == 0xBFu &&
      (this->octets[2] == 0xBEu || this->octets[2] == 0xBF))
    {
      return false;
    }
  
  // Yep-yep.
  return true;
}


bool
Character::IsBom (void)
  const throw (hummstrumm::engine::error::Unicode)
{
  if (!IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode, "The Character is not valid.");
    }
  
  // Check if this character has the BOM sequence (always the same in UTF-8).
  return (octets[0] == 0xEF && octets[1] == 0xBB && octets[2] == 0xBF);
}


bool
Character::IsNul (void)
  const throw (hummstrumm::engine::error::Unicode)
{
  if (!IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode, "The Character is not valid.");
    }
  
  // Check if this character is NUL (only check the first byte).
  return (octets[0] == 0x00);
}


bool
Character::IsAscii (void)
  const throw (hummstrumm::engine::error::Unicode)
{
  if (!IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode, "The Character is not valid.");
    }

  // ASCII chars are the only ones that can fit in one octet.
  return (GetSequenceLength () == 1);
}


void
Character::ToUtf32 (uint32 *buffer)
  const throw (hummstrumm::engine::error::InvalidParam,
               hummstrumm::engine::error::Unicode)
{
  if (buffer == 0)
    {
      HUMMSTRUMM_THROW (InvalidParam,
                        "The destination buffer pointer was null.");
    }

  if (!IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode, "The Character is not valid.");
    }
  
  *buffer = GetCodePoint ();
}


void
Character::ToUtf16 (uint16 *buffer)
  const throw (hummstrumm::engine::error::InvalidParam,
               hummstrumm::engine::error::Unicode)
{
  if (buffer == 0)
    {
      HUMMSTRUMM_THROW (InvalidParam,
                        "The destination buffer pointer was null.");
    }

  if (!IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode,
                        "The Character is not valid.");
    }

  std::memset (buffer, 0, 4);
  uint32 codePoint = GetCodePoint ();

  // If can't fit in one UTF-16 unit.
  if (codePoint > 0xFFFFu)
    {
      buffer[0] = (codePoint >> 10) + (MIN_LEAD_SURROGATE - 0x0040u);
      buffer[1] = (codePoint & 0x3FFu) + MIN_TRAILING_SURROGATE;
    }
  else
    {
      buffer[0] = codePoint;
    }
}


void
Character::ToUtf8 (unsigned char *buffer)
  const throw (hummstrumm::engine::error::InvalidParam,
               hummstrumm::engine::error::Unicode)
{
  if (buffer == 0)
    {
      HUMMSTRUMM_THROW (InvalidParam,
                        "The destination buffer pointer was null.");
    }

  if (!IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode,
                        "The Character is not valid.");
    }

  int length = GetSequenceLength ();
  std::memcpy (buffer, this->octets, length);
  std::memset (buffer + length, 0, 4 - length);
}


void
Character::FromUtf32 (const uint32 *const utf32Value)
  throw (hummstrumm::engine::error::Unicode
         hummstrumm::engine::error::InvalidParam) try
{
  if (utf32Value == 0)
    {
      HUMMSTRUMM_THROW (InvalidParam,
                        "The destination buffer pointer was null.");
    }
  
  // Temp save so we can reset.
  unsigned char temp [4];
  std::memcpy (temp, this->octets, 4);

  // Convert to UTF-32
  if (utf32Value < 0x80u)
    {
      // One octet.
      this->octets[0] = utf32Value;
    }
  else if (utf32Value < 0x800u)
    {
      // Two octets.
      this->octets[0] = (utf32Value >> 6)    | 0xC0u;
      this->octets[1] = (utf32Value & 0x3Fu) | 0x80u;
    }
  else if (utf32Value < 0x10000u)
    {
      // Three octets.
      this->octets[0] = (utf32Value >> 12)          | 0xE0;
      this->octets[1] = ((utf32Value >> 6) & 0x3Fu) | 0x80;
      this->octets[2] = (utf32Value & 0x3Fu)        | 0x80;
    }
  else if (utf32Value <= 0x10FFFF)
    {
      this->octets[0] = (utf32Value >> 18)           | 0xF0;
      this->octets[1] = ((utf32Value >> 12) & 0x3Fu) | 0x80;
      this->octets[2] = ((utf32Value >> 6)  & 0x3Fu) | 0x80;
      this->octets[3] = (utf32Value & 0x3Fu)         | 0x80;
    }
  else
    {
      HUMMSTRUMM_THROW (Unicode,
        "The passed-in value encoded a non Unicode code point.");
    }

  if (!IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode, "The specified code point is invalid.");
    }
}
catch (hummstrumm::engine::error::Unicode &e)
{
  // Reset the character.
  std::memset (this->octets, temp, 4);
  throw;
}


void
Character::FromUtf16 (const uint16 *const utf16)
  throw (hummstrumm::engine::error::Unicode,
         hummstrumm::engine::error::InvalidParam)
{
  if (utf16 == 0)
    {
      HUMMSTRUMM_THROW (InvalidParam,
                        "The destination buffer pointer was null.");
    }
  
  uint32 codePoint;
  if (utf16[0] >= MIN_LEAD_SURROGATE && utf16[0] <= MAX_LEAD_SURROGATE)
    {
      // Check surrogates.
      if (utf16[1] >= MIN_TRAILING_SURROGATE &&
          utf16[1] <= MAX_TRAILING_SURROGATE)
        {
          codePoint = (utf16[0] << 10) + utf16[1] +
            0x10000u - (MIN_LEAD_SURROGATE << 10) - MIN_TRAILING_SURROGATE;
        }
      else
        {
          HUMMSTRUMM_THROW (Unicode, "No trailing surrogate.");
        }
    }
  else if (utf16[0] >= MIN_TRAILING_SURROGATE &&
           utf16[0] <= MAX_TRAILING_SURROGATE)
    {
      HUMMSTRUMM_THROW (Unicode, "Only trailing surrogate.");
    }
  else
    {
      codePoint = utf16[0];
    }

  FromUtf32 (codePoint);
}


void
Character::FromUtf8 (const unsigned char *const utf8)
  throw (hummstrumm::engine::error::Unicode,
         hummstrumm::engine::error::InvalidParam) try
{
  if (utf8 == 0)
    {
      HUMMSTRUMM_THROW (InvalidParam,
                        "The destination buffer pointer was null.");
    }
  
  // Save value so we can reset on error.
  unsigned char temp [4];
  std::memset (temp, this->octets, 4);

  // Copy the data.
  int length = GetSequenceLength (utf8[0]);
  if (length > 4 || length < 1)
    {
      HUMMSTRUMM_THROW (Unicode, "Invalid sequence length.");
    }
  std::memcpy (this->octets,
               utf8,
               length);

  if (!IsValid ())
    {      
      HUMMSTRUMM_THROW (Unicode, "The specified UTF-8 is invalid.");
    }
}
catch (hummstrumm::engine::error::Unicode &e)
{
  // Reset the character.
  std::memset (this->octets, temp, 4);
  throw;
}


Character &
Character::operator= (const Character &character)
  throw (hummstrumm::engine::error::Unicode)
{
  if (!character.IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode, "Invalid Character to copy.");
    }

  std::memcpy (this->octets, character.octets, 4);

  return *this;
}


bool
Character::operator== (const Character &character)
  const throw (hummstrumm::engine::error::Unicode)
{
  if (!IsValid () || !character.IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode,
                        "One of the Character objects to compare was invalid.");
    }
  
  if (GetSequenceLength () == character.GetSequenceLength ())
    {
      return (memcmp (this->octets,
                      character.octets,
                      GetSequenceLength ()) == 0);
    }
  else
    {
      return false;
    }
}


bool
Character::operator!= (const Character &character)
  const throw (hummstrumm::engine::error::Unicode)
{
  return !(*this == character);
}


bool
Character::operator< (const Character &character)
  const throw (hummstrumm::engine::error::Unicode)
{
  if (!IsValid () || !character.IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode,
                        "One of the Character objects to compare was invalid.");
    }
  
  if (GetSequenceLength () < character.GetSequenceLength ())
    {
      // Has to be less.
      return true;
    }
  else if (GetSequenceLength () > character.GetSequenceLength ())
    {
      // Has to be more.
      return false;
    }
  else
    {
      // Same sequence size.
      return (GetCodePoint () < character.GetCodePoint ());
    }
}


bool
Character::operator<= (const Character &character)
  const throw (hummstrumm::engine::error::Unicode)
{
  if (!IsValid () || !character.IsValid ())
    {
      HUMMSTRUMM_THROW (Unicode,
                        "One of the Character objects to compare was invalid.");
    }
  
  if (GetSequenceLength () < character.GetSequenceLength ())
    {
      // Has to be less.
      return true;
    }
  else if (GetSequenceLength () > character.GetSequenceLength ())
    {
      // Has to be more.
      return false;
    }
  else
    {
      // Same sequence size.
      return (GetCodePoint () <= character.GetCodePoint ());
    }
}


bool
Character::operator> (const Character &character)
  const throw (hummstrumm::engine::error::Unicode)
{
  return !(*this <= character);
}


bool
Character::operator>= (const Character &character)
  const throw (hummstrumm::engine::error::Unicode)
{
  return !(*this < character);
}

    
uint16
Character::GetSequenceLength (void)
  const throw ()
{
  if (this->octets[0] == 0)
    {
      return 0;
    }
  
  return GetSequenceLength (this->octets[0]);
}


uint16
Character::GetSequenceLength (unsigned char firstByte)
  const throw ()
{
  // Based on the value of the octet.  This is some magic numbers here.  At
  // least they are all nice powers of 2.
  // This does not provide error checking.
  if (firstByte < 0xC0u)
    {
      return 1;
    }
  else if (firstByte < 0xE0u)
    {
      return 2;
    }
  else if (firstByte < 0xF0u)
    {
      return 3;
    }
  else if (firstByte < 0xF8u)
    {
      return 4;
    }
  else if (firstByte < 0xFCu)
    {
      return 5; // Cannot appear.
    }
  else if (firstByte < 0xFEu)
    {
      return 6; // Cannot appear.
    }
  else
    {
      return 0; // Not defined.
    }
}
               

uint32
Character::GetCodePoint (void)
  const throw ()
{ 
  unsigned char sequenceLength = GetSequenceLength ();
  uint32_t      codePoint = 0x110000; // An invalid Unicode code point.
  uint32_t      temp      = 0;

  switch (sequenceLength)
    {
    case 1:
      codePoint = this->octets[0];
      break;

    case 2:
      codePoint = (this->octets[0] - 0xC0u);  // Switch off high bits.
      codePoint <<= 6; // Make room.
      temp = (this->octets[1] - 0x80u); // Switch off high bit.
      codePoint += temp; // Combine the octets.
      break;

    case 3:
      codePoint = (this->octets[0] - 0xE0u); // Switch off high bits.
      codePoint <<= 12; // Make room.
      temp = (this->octets[1] - 0x80u); // Switch off high bit.
      temp <<= 6; // Make room.
      codePoint |= temp; // Combine the octets.
      temp = (this->octets[2] - 0x80u); // Switch off high bit.
      codePoint |= temp;
      break;

    case 4:
      codePoint = (this->octets[0] - 0xF0u); // Switch off high bits.
      codePoint <<= 18; // Make room.
      temp = (this->octets[1] - 0x80u); // Switch off high bit.
      temp <<= 12; // Make room.
      codePoint |= temp; // Combine the octets.
      temp = (this->octets[2] - 0x80u); // Switch off high bit.
      temp <<= 6; // Make room.
      codePoint |= temp; // Combine the octets.
      temp = (this->octets[3] - 0x80u); // Switch off high bit.
      codePoint |= temp;
      break;

    default:
      // Cannot happen.  This is a valid codePoint.
      break;
    }
  
  return codePoint;
}


}
}
}
