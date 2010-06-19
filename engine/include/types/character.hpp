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
 * @file   character.hpp
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
 * Character also provides a routine for determining the Unicode character
 * category.  All Unicode character categories are supported.
 *
 * @version 0.3
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-06-08
 * @since   0.3
 */
class Character : public hummstrumm::engine::core::Object
{
    HUMMSTRUMM_DECLARE_TYPE (Character)
  public:
    /**
     * The Unicode character category of a Unicode code point.  All characters
     * have a character category.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     */
    enum Category
      {
        None, ///< Well, no category...shouldn't happen...but who knows?
        Mn, ///< Mark, Nonspacing
        Mc, ///< Mark, Spacing Combining
        Me, ///< Mark, Enclosing
        Nd, ///< Number, Decimal Digit
        Nl, ///< Number, Letter
        No, ///< Number, Other
        Zs, ///< Separator, Space
        Zl, ///< Separator, Line
        Zp, ///< Separator, Paragraph
        Cc, ///< Other, Control
        Cf, ///< Other, Format
        Cs, ///< Other, Surrogate
        Co, ///< Other, Private Use
        Cn, ///< Other, Not Assigned
        Lu, ///< Letter, Uppercase
        Ll, ///< Letter, Lowercase
        Lt, ///< Letter, Titlecase
        Lm, ///< Letter, Modifier
        Lo, ///< Letter, Other
        Pc, ///< Punctuation, Connector
        Pd, ///< Punctuation, Dash
        Ps, ///< Punctuation, Open
        Pe, ///< Punctuation, Close
        Pi, ///< Punctuation, Initial Quote
        Pf, ///< Punctuation, Final Quote
        Po, ///< Punctuation, Other
        Sm, ///< Symbol, Math
        Sc, ///< Symbol, Currency
        Sk, ///< Symbol, Modifier
        So, ///< Symbol, Other
      };

    void
    DebugOutput (void)
      {
        std::cout << (int)(unsigned char)utf8Data[0] << ' '
                  << (int)(unsigned char)utf8Data[1] << ' '
                  << (int)(unsigned char)utf8Data[2] << ' '
                  << (int)(unsigned char)utf8Data[3] << '\n';
      }
    
    /**
     * Constructs a new Character object initialised to the Unicode NUL
     * character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     */
    Character (void)
      throw ();
    /**
     * Constructs a new Character object initialised to a Unicode character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     */
    Character (const wchar_t)
      throw ();
    /**
     * Constructs a new Character object initialised to an ASCII character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     */
    Character (const char)
      throw ();
    /**
     * Constructs a new Character object initialised to the bytes of a UTF-8
     * Unicode character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     */
    Character (const char [4])
      throw ();
    /**
     * Constructs a new Character object initialised to another Character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     */
    Character (const Character &)
      throw ();
    
    /**
     * Destructs a Character object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     */
    virtual ~Character (void);
    
    /**
     * Assigns a value to this Character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     * 
     * @return The value of the Character, after assignment.
     */
    Character &operator= (const Character &)
      throw ();

    /**
     * Checks if a Character is equal to this Character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     * 
     * @return Whether the two Character objects are equal.
     */
    bool operator== (const Character &)
      const throw ();
    /**
     * Checks if a Character is not equal to this Character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     * 
     * @return Whether the two Character objects are not equal.
     */
    bool operator!= (const Character &)
      const throw ();

    /**
     * Returns whether a Character is in the ASCII range.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     *
     * @return Whether the Character is an ASCII character.
     */
    bool IsAscii (void)
      const throw ();

    /**
     * Returns a char, if possible.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     *
     * @return The standard char value of the UTF-8 character, if one such
     * exists.
     */
    char ToChar (void)
      const throw (hummstrumm::engine::error::Unicode);
    /**
     * Returns a wchar_t, if possible.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     *
     * @return The standard wchar_t value of the UTF-8 character, if one such
     * exists.
     */
    wchar_t ToWchar_t(void)
      const throw (hummstrumm::engine::error::Unicode);

    /**
     * Returns the Unicode character category of this specific character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     *
     * @return The Category of this Character.
     */
    Category GetCategory (void) const throw ();
    
  private:
    /**
     * Returns the number value corresponding to the Character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     */
    uint32 GetCodePoint (void)
      const throw (hummstrumm::engine::error::Unicode);
    /**
     * Returns the length of the UTF-8 sequence in bytes.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-08
     * @since  0.3
     *
     * @return The number of bytes in the stored UTF-8 sequence.
     */
    int GetSequenceLength (void)
      const throw (hummstrumm::engine::error::Unicode);
    
    char utf8Data[4];
};


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_TYPES_CHARACTER
