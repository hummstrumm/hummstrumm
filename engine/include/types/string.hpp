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
 * Defines a class to hold strings of characters.
 *
 * @file   string.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-05-11
 * @see    String
 */

#ifndef HUMMSTRUMM_ENGINE_TYPES_STRING
#define HUMMSTRUMM_ENGINE_TYPES_STRING

namespace hummstrumm
{
namespace engine
{
namespace types
{

/**
 * Holds a string of 
 *
 * @version 0.2
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-05-11
 * @since   0.2
 *
 * @todo Maybe make a Character class, if the need arises.
 * @todo Add iterators in next release (0.3) after the containers are made.
 */
class String : public hummstrumm::engine::core::Object
{
    HUMMSTRUMM_DECLARE_TYPE (String)
  public:
    /**
     * Constructs a new String object initialised to no string.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     */
    String (void);
    /**
     * Constructs a new String object initialised to a Unicode character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     */
    String (const wchar_t);
    /**
     * Constructs a new String object initialised to a Unicode string.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     */
    String (const wchar_t *);
    /**
     * Constructs a new String object initialised to an ASCII character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     */
    String (const char);
    /**
     * Constructs a new String object initialised to an ASCII string.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     */
    String (const char *);
    /**
     * Constructs a new String object initialised to a Number.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     */
    explicit String (const Number &);
    /**
     * Constructs a new String object initialised to another String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     */
    String (const String &);
    
    /**
     * Destructs a String object and frees its memory.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     */
    virtual ~String (void);

    /**
     * Concatenates two String objects.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     * 
     * @return The concatenation of two String objects.
     */
    const String operator+ (const String &) const throw ();

    /**
     * Assigns a value to this String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-01
     * @since  0.2
     * 
     * @return The value of the String, after assignment.
     */
    String &operator= (const String &) throw ();

    /**
     * Concatenates a String with this current String and then assigns the
     * result to this String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     * 
     * @return The value of the String, after concatenation.
     */
    String &operator+= (const String &) throw ();

    /**
     * Checks if a String is equal to this String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     * 
     * @return Whether the two String objects are equal.
     *
     * @warning This method does not check for different normalisation forms,
     * so if two separate code point encodings represent the same character,
     * they will not be equal.
     */
    bool operator== (const String &) const throw ();
    /**
     * Checks if a String is not equal to this String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-15
     * @since  0.2
     * 
     * @return Whether the two String objects are not equal.
     *
     * @warning This method does not check for different normalisation forms,
     * so if two separate code point encodings represent the same character,
     * they will not be equal.
     */
    bool operator!= (const String &) const throw ();

    /**
     * Returns whether the String is composed of a single character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     * 
     * @return Whether the String is a single character.
     */
    bool IsCharacter (void) const throw ();
    
    /**
     * Returns the length of the String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     *
     * @return The length of the string.
     */
    Number GetLength (void) const throw ();
    
    /**
     * Get the character at a certain position.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     *
     * @return The character at a certain position.
     *
     * @todo Throw an exception on an invalid index.
     */
    wchar_t &operator[] (unsigned int index) throw ();
    /**
     * Get the character at a certain position.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     *
     * @return The character at a certain position.
     *
     * @todo Throw an exception on an invalid index.
     */
    wchar_t operator[] (unsigned int index) const throw ();
    
    /**
     * Return the Unicode string buffer.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     *
     * @return This string in C++ format.
     */
    const wchar_t *ToUnicode (void) const throw ();
    /**
     * Return the ASCII string buffer.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-05-14
     * @since  0.2
     *
     * @return This string in C++ format.
     */
    const char *ToAscii (void) const throw ();
    
  private:
    wchar_t *string; /**< The buffer containing the string. */
    uint32 length;   /**< Length of string.  4,294,967,296 is long enough. */
};


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_TYPES_STRING
