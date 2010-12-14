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
 * Defines a class to hold any UTF-8 character encoding.
 *
 * @file   types/character.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-06-08
 * @see    Character
 */

#ifndef HUMMSTRUMM_ENGINE_TYPES_CHARACTER
#define HUMMSTRUMM_ENGINE_TYPES_CHARACTER


namespace hummstrumm
{
namespace engine
{
namespace types
{

/**
 * Holds a single UTF-8 character, with four bytes.  This class can store any
 * Unicode character thrown at it.  Please note that this doesn't allow for the
 * full UTF-8 48 bytes, but that is currently not needed for Unicode characters.
 *
 * All characters are stored as sequences of four bytes.  This allows any
 * Unicode code point to be stored in a Character. Holding an array of
 * Character objects is not the most efficient way to store text.  Instead, use
 * the String class.  Furthermore, these are sequences of UTF-8 data, not one
 * character stored as a UTF-32 block.  This means we can effectively ignore
 * endianness.
 *
 * @version 0.3
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-09-03
 * @since   0.3
 */
class Character : public hummstrumm::engine::core::Object
{
    HUMMSTRUMM_DECLARE_TYPE (Character);

    /// So String can use some of the UTF-8 methods from Character.
    friend class String;
  public:
    /**
     * Constructs a new Character object.  The character will have the value
     * U+0000, the Unicode NUL character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-03
     * @since  0.3 
     */
    Character (void)
      throw ();
    /**
     * Constructs a new Character object from an ASCII character.  The Character
     * will be initialized to asciiChar, which must be a valid ASCII character
     * with a value from U+0000 to U+007F.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielsk@gmail.com>
     * @date   2010-09-03
     * @since  0.3
     *
     * @param asciiChar [in] A character in the ASCII range.
     *
     * @throw hummstrumm::engine::error::OutOfRange If the character is not a
     * valid ASCII character in the Unicode range U+0000 to U+007F.
     */
    Character (char asciiChar)
      throw (hummstrumm::engine::error::OutOfRange);
    /**
     * Constructs a new Character object from a sequence of UTF-8 octets.  The
     * Character will have the value of the four octets, as long as they are a
     * valid UTF-8 sequence.
     *
     * In UTF-8, the first octet in a sequence tells how many octets are in
     * the sequence.  UTF-8 sequences holding Unicode characters (as opposed to
     * ISO UTF-8 characters, which can hold more characters than Unicode
     * currently supports) are up to 4 octets in length.  Shorter sequences will
     * ignore the octets given to this function which are more than their
     * length; that is, in a two octet sequence, parameters octet3 and octet4
     * will be disregarded.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-03
     * @since  0.3
     *
     * @param octet1 [in] The first octet in the UTF-8 sequence.
     * @param octet2 [in] The secend octet in the UTF-8 sequence.
     * @param octet3 [in] The third octet in the UTF-8 sequence.
     * @param octet4 [in] The fourth octet in the UTF-8 sequence.
     *
     * @throw hummstrumm::engine::error::Unicode If the UTF-8 octets form an
     * an invalid sequence or code point.
     */
    Character (unsigned char octet1,
               unsigned char octet2,
               unsigned char octet3,
               unsigned char octet4)
      throw (hummstrumm::engine::error::Unicode);
    /**
     * Constructs a new Character from a UTF-16 sequence.  The Character will be
     * set to the equivalent UTF-8 sequence, as long as the inputted UTF-16
     * sequence is valid.
     *
     * UTF-16 sequences are composed of at most two 16-bit integers.  Most
     * allocated characters in the current Unicode standard can fit in only one
     * of these integers, but many of the higher valued characters need both
     * integers.  To accomidate this, UTF-16 has "surrogate pairs", which are
     * pairs of two 16 bit integers of special values, which together encode the
     * Unicode code point.  If this method detects that the first integer is
     * part of a surrogate pair, it will look at the second parameter.
     * Otherwise, the second parameter is ignored.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-04
     * @since  0.3
     *
     * @param surrogate1 [in] The first value of the UTF-16 sequence.  This does
     * not need to be a surrogate.
     * @param surrogate2 [in] The second value of a UTF-16 surrogate pair.  This
     * is only regarded if surrogate1 actually denotes the beginning of a
     * surrogate pair.
     *
     * @throw hummstrumm::engine::error::Unicode If the UTF-16 pair forms an
     * invalid surrogate pair or code point.
     */
    Character (uint16 surrogate1,
               uint16 surrogate2)
      throw (hummstrumm::engine::error::Unicode);
    /**
     * Constructs a new Character from a UTF-32 code point.  The Character will
     * be set to the equivalent UTF-8 sequence, as long as the inputted code
     * point is valid.  If the code point is not valid, then the Character will
     * be set to the Unicode NUL character, U+0000.
     *
     * Valid Unicode code points include all values up to U+10FFFF, except the
     * Surrogate blocks, which are reserved for encoding UTF-16 values in
     * surrogate pairs.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-04
     * @since  0.3
     *
     * @param codePoint [in] The Unicode code point which to encode into UTF-8.
     *
     * @throw hummstrumm::engine::error::Unicode If the UTF-16 pair forms an
     * invalid surrogate pair or code point.
     */
    explicit Character (uint32 codePoint)
      throw (hummstrumm::engine::error::Unicode);
    /**
     * Constructs a new Character from an existing Character.  The new Character
     * will be set to the value contained within the existing Character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-04
     * @since  0.3
     *
     * @param character [in] A Character to clone.
     *
     * @throw hummstrumm::engine::error::Unicode If the other Character is
     * invalid.
     */
    Character (const Character &character)
      throw (hummstrumm::engine::error::Unicode);
    /**
     * Destructs a Character.  The buffer for the Character is freed, because
     * memory leaks really do suck.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-04
     * @since  0.3
     */
    virtual ~Character (void);

    /**
     * Returns whether the Character contains a valid UTF-8 sequence of octets.
     * This includes looking for invalid internal buffers, malformed bytes,
     * invalid sequences, overlong sequences, and invalid code points.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-04
     * @since  0.3
     *
     * @return If the character is a valid UTF-8 sequence, encoding a valid
     * Unicode code point.
     */
    bool IsValid (void)
      const throw ();
    /**
     * Returns whether the Character is the Unicode Byte-order Mark (BOM)
     * character, U+FEFF.  Do note that the Character may not function as a BOM
     * in the context of the string, even if this method returns true; the only
     * time this code point could be a true BOM is if it were to appear at the
     * beginning of the String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-04
     * @since  0.3
     *
     * @return If the character is the BOM character.
     *
     * @throw hummstrumm::engine::error::Unicode If the Character is not valid.
     */
    bool IsBom (void)
      const throw (hummstrumm::engine::error::Unicode);
    /**
     * Returns whether the Character is the Unicode NUL character, U+0000.  This
     * Character is used to end a string.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-04
     * @since  0.3
     *
     * @return If the character is the NUL character.
     *
     * @throw hummstrumm::engine::error::Unicode If the Character is not valid.
     */
    bool IsNul (void)
      const throw (hummstrumm::engine::error::Unicode);
    /**
     * Returns whether the Character is in the ASCII code point range, from
     * U+0000 to U+007F.  These Characters are the only ones which can fit in
     * one octet in the UTF+8 encoding.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-04
     * @since  0.3
     *
     * @return If the character is of the ASCII set.
     *
     * @throw hummstrumm::engine::error::Unicode If the Character is not valid.
     */
    bool IsAscii (void)
      const throw (hummstrumm::engine::error::Unicode);

    /**
     * Convert the Character to a UTF-32 code point.  You must specify a valid
     * buffer into which to place the code point.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-06
     * @since  0.3
     *
     * @param buffer [out] The address of the buffer in which to store the code
     * point.  This pointer must be valid, and point to a one element buffer of
     * type uint32. 
     *
     * @throw hummstrumm::engine::error::InvalidParam If the buffer pointer is
     * invalid.
     * @throw hummstrumm::engine::error::Unicode If the Character is not valid.
     */
    void ToUtf32 (uint32 *buffer)
      const throw (hummstrumm::engine::error::InvalidParam,
                   hummstrumm::engine::error::Unicode);
    /**
     * Convert the Character to a UTF-16 sequence.  You must specify a valid
     * buffer into which to place the sequence.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-06
     * @since  0.3
     *
     * @param buffer [out] The address of the buffer in which to store the
     * sequence.  This pointer must be valid, and point to a big enough to hold
     * the UTF-16 sequence.  To be safe, you should use a buffer that is at
     * least two uint16 elements long; this can hold any UTF-16 sequence.
     *
     * @throw hummstrumm::engine::error::InvalidParam If the buffer pointer is
     * invalid.
     * @throw hummstrumm::engine::error::Unicode If the Character is not valid.
     */
    void ToUtf16 (uint16 *buffer)
      const throw (hummstrumm::engine::error::InvalidParam,
                   hummstrumm::engine::error::Unicode);
    /**
     * Convert the Character to a UTF-8 sequence.  You must specify a valid
     * buffer into which to place the sequence.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-06
     * @since  0.3
     *
     * @param buffer [out] The address of the buffer in which to store the
     * sequence.  This pointer must be valid, and point to a big enough to hold
     * the UTF-8 sequence.  To be safe, you should use a buffer that is at least
     * four unsigned char elements long; this can hold any UTF-8 sequence which
     * encodes a Unicode character.
     *
     * @throw hummstrumm::engine::error::InvalidParam If the buffer pointer is
     * invalid.
     * @throw hummstrumm::engine::error::Unicode If the Character is not valid.
     */
    void ToUtf8 (unsigned char *buffer)
      const throw (hummstrumm::engine::error::InvalidParam,
                   hummstrumm::engine::error::Unicode);

    /**
     * Set this Character to the equivalent UTF-8 sequence for the specified
     * UTF-32 code point.  This will succeed given a valid, non-surrogate UTF-32
     * code point.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-06
     * @since  0.3
     *
     * @param utf32Value [in] The address of the buffer containing the code
     * point.
     *
     * @throw hummstrumm::engine::error::Unicode If utf32Value encodes an
     * invalid code point.
     * @throw hummstrumm::engine::error::InvalidParam If utf32Value points to a
     * null buffer.
     */
    void FromUtf32 (const uint32 *const utf32Value)
      throw (hummstrumm::engine::error::Unicode,
             hummstrumm::engine::error::InvalidParam);
    /**
     * Set this Character to the equivalent UTF-8 sequence for the specified
     * UTF-16 sequence.  This will succeed given a valid UTF-16 sequence.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-06
     * @since  0.3
     *
     * @param utf16Value [in] The address of the buffer containing the
     * sequence.
     *
     * @throw hummstrumm::engine::error::Unicode If utf16Value encodes an
     * invalid code point or invalid surrogate pair.
     * @throw hummstrumm::engine::error::InvalidParam If utf16Value points to a
     * null buffer.
     */
    void FromUtf16 (const uint16 *const utf16Value)
      throw (hummstrumm::engine::error::Unicode,
             hummstrumm::engine::error::InvalidParam);
    /**
     * Set this Character to the given UTF-8 sequence.  This will succeed given
     * a valid UTF-8 sequence.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-06
     * @since  0.3
     *
     * @param utf8Value [in] The address of the buffer containing the
     * sequence.
     *
     * @throw hummstrumm::engine::error::Unicode If utf8Value encodes an
     * invalid code point or invalid sequence.
     * @throw hummstrumm::engine::error::InvalidParam If utf8Value points to a
     * null buffer.
     */
    void FromUtf8 (const unsigned char *const utf8Value)
      throw (hummstrumm::engine::error::Unicode,
             hummstrumm::engine::error::InvalidParam);

    /**
     * Set this Character to be completely equivalent to another Character.  As
     * long as the Character on the right side is valid.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-06
     * @since  0.3
     *
     * @param character [in] A Character to clone.
     *
     * @return This object, to facilitate chaining of assignments.
     *
     * @throw hummstrumm::engine::error::Unicode If character is not a valid
     * Character.
     */
    Character &operator= (const Character &character)
      throw (hummstrumm::engine::error::Unicode);

    /**
     * Return whether two Characters are equivalent.  Equivalent code points, by
     * the definition of UTF-8, will be equal in raw memory value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-08
     * @since  0.3
     *
     * @param character [in] A Character to which to compare for equality.
     *
     * @return If the two Characters being compared are equal.
     *
     * @throw hummstrumm::engine::error::Unicode If one of the Character objects
     * is invalid.
     */
    bool operator== (const Character &character)
      const throw (hummstrumm::engine::error::Unicode);
    /**
     * Return whether two Characters are not equivalent.  Inequivalent code
     * points, by the definition of UTF-8, will be unequal in raw memory value.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-08
     * @since  0.3
     *
     * @param character [in] A Character to which to compare for inequality.
     *
     * @return If the two Characters being compared are unequal.
     *
     * @throw hummstrumm::engine::error::Unicode If one of the Character objects
     * is invalid.
     */
    bool operator!= (const Character &character)
      const throw (hummstrumm::engine::error::Unicode);
    /**
     * Return whether this Character's code point is less than another
     * Character's.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-08
     * @since  0.3
     *
     * @param character [in] A Character to which to compare for difference.
     *
     * @return If this code point is less than another Character's code point.
     *
     * @throw hummstrumm::engine::error::Unicode If one of the Character objects
     * is invalid.
     */
    bool operator< (const Character &character)
      const throw (hummstrumm::engine::error::Unicode);
    /**
     * Return whether this Character's code point is not greater than another
     * Character's.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-08
     * @since  0.3
     *
     * @param character [in] A Character to which to compare for difference.
     *
     * @return If this code point is not greater than another Character's code
     * point.
     */
    bool operator<= (const Character &character)
      const throw ();
    /**
     * Return whether this Character's code point is greater than another
     * Character's.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-08
     * @since  0.3
     *
     * @param character [in] A Character to which to compare for difference.
     *
     * @return If this code point is greater than another Character's code
     * point.
     */
    bool operator> (const Character &character)
      const throw ();
    /**
     * Return whether this Character's code point is not less than another
     * Character's.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-08
     * @since  0.3
     *
     * @param character [in] A Character to which to compare for difference.
     *
     * @return If this code point is not less than another Character's code
     * point.
     */
    bool operator>= (const Character &character)
      const throw ();

  private:
    /**
     * Constructs a new Character from octets in a String.  The new Character
     * will copy the octets of a String from a pointer to the beginning of the
     * sequence.  This constructor will safely copy the correct number of
     * octets, so for valid UTF-8, there will be no access violations.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-08
     * @since  0.3
     *
     * @param octetsFromString [in] A pointer to the beginning of the UTF-8
     * sequence.
     *
     * @throw hummstrumm::engine::error::InvalidParam If octetsFromString is a
     * null pointer.
     * @throw hummstrumm::engine::error::Unicode If the UTF-8 sequence is
     * malformed.
     */
    Character (const char *octetsFromString)
      throw (hummstrumm::engine::error::InvalidParam,
             hummstrumm::engine::error::Unicode);

    /**
     * Return the Unicode code point associated with this Character.  This is an
     * internal method, called after all error checks, so if something gets to
     * us that is invalid, we just return U+110000, one past the last Unicode
     * code point.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-08
     * @since  0.3
     *
     * @return The code point of this Character.
     */
    uint32 GetCodePoint (void)
      const throw ();
    /**
     * Return the sequence length associated with the UTF-8 in this Character.
     * If passed an invalid value, this will return 0, but all sequence lengths
     * defined by UTF-8, including overlong sequences and sequences encoding
     * non-Unicode code points, will be recognised and returned.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-08
     * @since  0.3
     *
     * @return The sequence length of this Character.
     */
    uint16 GetSequenceLength (void)
      const throw ();
    /**
     * Return the sequence length associated with the first octet of a UTF-8
     * sequence, including that octet.  If passed an invalid value, this will
     * return 0, but all sequence lengths defined by UTF-8, including overlong
     * sequences and sequences encoding non-Unicode code points, will be
     * recognised and returned.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-08
     * @since  0.3
     *
     * @param firstByte [in] The first octet in a UTF-8 sequence.
     *
     * @return The sequence length of this Character.
     */
    uint16 GetSequenceLength (unsigned char firstByte)
      const throw ();

    unsigned char octets[4]; /// The UTF-8 octets.

    // And now constants for UTF-16.  Had to look them up, but this shouldn't
    // change.  Ever.
    /// The smallest code point for a leading surrogate.
    static const uint16_t MIN_LEAD_SURROGATE     = 0xD800u;
    /// The largest code point for a leading surrogate.
    static const uint16_t MAX_LEAD_SURROGATE     = 0xDBFFu;
    /// The smallest code point for a trailing surrogate.
    static const uint16_t MIN_TRAILING_SURROGATE = 0xDC00u;
    /// The largest code point for a trailing surrogate.
    static const uint16_t MAX_TRAILING_SURROGATE = 0xDFFFu;
};


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_TYPES_CHARACTER
