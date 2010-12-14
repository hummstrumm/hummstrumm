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
 * @file   types/string.hpp
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
 * Holds a string of UTF-8 formatted characters.  All Strings visible to the
 * game developers are stored in this class.  It manages the memory of the
 * Character data, checks for invalid requests on the String, provides many
 * utilities for dealing with strings, and isolates all String code in one
 * place.  Whenever possible, use this class instead of plain ``char *'' or
 * ``Character *''.
 *
 * This class provides convenience methods and constructors to allow for
 * conversions between various Unicode Transformation Formats (from UTF-16
 * or UTF-32 to UTF-8, and vice versa).  This class does not support any other
 * Character sets, like the Latin-x ISO family of standards, Shift_JIS, or
 * Windows-125x.  Do note, though, that since ASCII is a strict subset of UTF-8,
 * this class supports it without any conversion.
 *
 * String acts like a container:: class, specifically a specialized array of
 * Character objects.  To access individual Character elements, you need to use
 * the specialized Iterator of the String, which provides the same API as other
 * Iterator classes in the engine.
 *
 * You can also retrieve the raw UTF-8 data of this String, for use in APIs that
 * don't interface with our String class.  Ideally, this should be used at the
 * minimum frequency possible.  Whenever possible, use the built-in APIs and
 * support that make use of String.
 *
 * @version 0.3
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-05-11
 * @since   0.2
 *
 * @warning In Unicode Transformation Format conversion, byte order is not
 * considered.  If you expect UTF-16 or UTF-32 character data that isn't in the
 * system byte order, use the Endian class to convert.  (HINT: Use UTF-8.  It's
 * just simpler.)
 */
class String
{
  public:
    /**
     * An interface for accessing individual Character elements in a String.
     * This Iterator allows for iterating through array elements, accessing
     * their Character data, and checking for equality/inequality between
     * Iterator objects.
     * 
     * @version 0.3
     * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date    2010-11-16
     * @since   0.2
     */
    class Iterator : public hummstrumm::engine::containers::Iterator<Character>
    {
        /// Allows String to check whether, in fact, this is one of its Iterator
        /// objects, and to create new Iterator objects.
        friend class String;
      public:
        /**
         * Constructs a new Iterator from an existing, valid Iterator.  The new
         * Iterator will be valid.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2010-11-16
         * @since  0.3
         *
         * @throw hummstrumm::engine::error::InvalidParam If the Iterator that
         * was passed in was somehow invalid.  Not sure how that could happen
         * (or if it does, we've bigger problems to deal with...), but let's
         * prepare for it, just in case.  Unless if someone is messing around
         * with pointers.
         */
        Iterator (const Iterator &iterator)
          throw (hummstrumm::engine::error::InvalidParam);
        /**
         * Returns whether the Iterator can be incremented to the next
         * Character.  Generally, for a valid iterator, this is true as long as
         * the iterator is not equal to the iterator returned by GetEnd () of
         * the String.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2010-09-18
         * @since  0.3
         *
         * @return If there is another element to which this iterator can be
         * iterated.
         *
         * @throw hummstrumm::engine::error::Iterator If the Iterator is invalid
         * (i.e., it doesn't point to an actual element).
         */
        virtual bool HasNext (void)
          const throw (hummstrumm::engine::error::Iterator);
        /**
         * 
         * 
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2010-11-16
         * @since  0.3
         *
         * @return The next Character in the 
         */
        virtual Character &GetNext (void)
          throw (hummstrumm::engine::error::Iterator);
        virtual String::Iterator &operator++ (void)
          throw ();
        virtual String::Iterator &operator++ (int)
          throw ();
        virtual Character &PeekNext (void)
          const throw ();
        virtual bool operator== (const String::Iterator &object)
          const throw ();
        virtual bool operator!= (const String::Iterator &object)
          const throw ();
        virtual Character &operator* (void)
          const throw ();

      private:
        /**
         * Constructs a new Iterator from a pointer to a specific element in a
         * String.  All Iterators that are not copied from others should be made
         * by means of this method, and by no other means should they be made.
         * For this is the sole means of creation, the sole means of creation
         * being this.
         * 
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2010-11-16
         * @since  0.3
         */
        Iterator (const char *iterator);

        /**
         * DOES NOTHING.  This method is private, such that no Iterator will be
         * created without pointing to anything.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2010-11-16
         * @since  0.3
         *
         * @warning YOU ARE NOT TO EVER EVEN THINK ABOUT USING THIS METHOD.  IT
         * WILL NOT BE TOLERATED.  (You should always use the String object to
         * get a valid Iterator or else just copy construct another valid
         * Iterator.)
         */
        Iterator (void);

        /// The pointer that all this Iterator nonsense all boils down to in the
        /// end.
        const char *iterator;
    };

    /**
     * Constructs a new String, initialized to an empty array of Characters.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-26
     * @since  0.3
     *
     * @throw hummstrumm::engine::error::OutOfMemory If not enough memory can be
     * allocated to store the String.
     */
    String (void)
      throw (hummstrumm::engine::error::OutOfMemory);
    /**
     * Constructs a new String, initialized to an array of UTF-8 encoded
     * characters.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-26
     * @since  0.3
     *
     * @param utf8 [in] A null terminated buffer of UTF-8 octets.
     * 
     * @throw hummstrumm::engine::error::OutOfMemory If not enough memory can be
     * allocated to store the String.
     * @throw hummstrumm::engine::error::Unicode If the given UTF-8 is invalid.
     * @throw hummstrumm::engine::error::InvalidParam If the given buffer
     * pointer is null.
     */
    String (const char *utf8)
      throw (hummstrumm::engine::error::OutOfMemory,
             hummstrumm::engine::error::Unicode,
             hummstrumm::engine::error::InvalidParam);
    /**
     * Constructs a new String, initialized to an array of UTF-16 encoded
     * characters.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-26
     * @since  0.3
     *
     * @param utf16 [in] A null terminated buffer of UTF-16 code points.
     * 
     * @throw hummstrumm::engine::error::OutOfMemory If not enough memory can be
     * allocated to store the String.
     * @throw hummstrumm::engine::error::Unicode If the given UTF-16 is invalid.
     * @throw hummstrumm::engine::error::InvalidParam If the given buffer
     * pointer is null.
     */
    String (const uint16_t *utf16)
      throw (hummstrumm::engine::error::OutOfMemory,
             hummstrumm::engine::error::Unicode,
             hummstrumm::engine::error::InvalidParam);
    /**
     * Constructs a new String, initialized to an array of UTF-32 encoded
     * characters.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-26
     * @since  0.3
     *
     * @param utf32 [in] A null terminated buffer of UTF-32 codepoints.
     * 
     * @throw hummstrumm::engine::error::OutOfMemory If not enough memory can be
     * allocated to store the String.
     * @throw hummstrumm::engine::error::Unicode If the given UTF-32 is invalid.
     * @throw hummstrumm::engine::error::InvalidParam If the given buffer
     * pointer is null.
     */
    String (const uint32_t *utf32)
      throw (hummstrumm::engine::error::OutOfMemory,
             hummstrumm::engine::error::Unicode,
             hummstrumm::engine::error::InvalidParam);
    /**
     * Constructs a new String, initialized to a Character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-26
     * @since  0.3
     *
     * @param character [in] A Character holding a single Unicode code point.
     *
     * @throw hummstrumm::engine::error::OutOfMemory If not enough memory can be
     * allocated to store the String.
     * @throw hummstrumm::engine::error::Unicode If the given Character is
     * invalid.
     */
    String (const Character &character)
      throw (hummstrumm::engine::error::OutOfMemory,
             hummstrumm::engine::error::Unicode);
    /**
     * Destructs a String, freeing any memory used by it.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-27
     * @since  0.3
     */
    virtual ~String (void);

    /**
     * Returns the concatenation of this String with another String.  This
     * String is not modified in the process.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-27
     * @since  0.3
     *
     * @param string [in] A String to add to this one.
     *
     * @return A new String containing the concatenation of both this String and
     * argument String.
     *
     * @throw hummstrumm::engine::error::OutOfMemory If not enough memory can be
     * allocated to store the new String.
     */
    String operator+ (const String &string)
      const throw (hummstrumm::engine::error::OutOfMemory);

    /**
     * Sets this String equal in value to another String, and then returns a
     * reference to this String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-27
     * @since  0.3
     *
     * @param string [in] A String to which to set this one.
     *
     * @return A reference to this String, after having undergone the operation.
     *
     * @throw hummstrumm::engine::error::OutOfMemory If not enough memory can be
     * allocated to store the new String.
     */
    String &operator= (const String &string)
      throw (hummstrumm::engine::error::OutOfMemory);
    /**
     * Sets this String to the concatenation of itself and another String, and
     * then returns a reference to this String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-27
     * @since  0.3
     *
     * @param string [in] A String to which to add to this one.
     *
     * @return A reference to this String, after having undergone the operation.
     *
     * @throw hummstrumm::engine::error::OutOfMemory If not enough memory can be
     * allocated to store the new String.
     */
    String &operator+= (const String &string)
      throw (hummstrumm::engine::error::OutOfMemory);

    /**
     * Returns the raw data held in the String.  This data should not be
     * changed.  This data will be in UTF-8 format, and is useful when
     * interfacing with libraries that don't use this lovely String class we've
     * made.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-27
     * @since  0.3
     *
     * @return A pointer to the raw buffer that stores the String.  This will be
     * a NUL-terminated, UTF-8 encoded buffer.
     */
    const char *GetRaw (void)
      const throw ();

    
//    String::Iterator operator[] (uint64_t index)
//      const throw (int);

    /**
     * Clears the String of any Character data.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-27
     * @since  0.3
     *
     * @throw hummstrumm::engine::error::OutOfMemory If not enough memory can be
     * allocated to store the new String.
     */
    void Clear (void)
      throw (hummstrumm::engine::error::OutOfMemory);

    /**
     * Returns the length of the String (excluding the NUL byte) in Characters.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-27
     * @since  0.3
     *
     * @return The number of Characters in the String.
     *
     * @throw hummstrumm::engine::error::Unicode If the String is invalid.
     */
    uint64_t GetLength (void)
      const throw (hummstrumm::engine::error::Unicode);

    /**
     * Returns whether this String is a valid, NUL-terminated, UTF-8 character
     * string.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-27
     * @since  0.3
     *
     * @return If the String is valid.
     */
    bool IsValid (void)
      const throw ();
    /**
     * Returns whether this String is empty, having only a NUL-terminator.  A
     * String constructed with no arguments and a String which has just been
     * cleared are guaranteed to be empty.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-27
     * @since  0.3
     *
     * @return If the String is empty.
     *
     * @throw hummstrumm::engine::error::Unicode If the String tested is
     * invalid.
     */
    bool IsEmpty (void)
      const throw (hummstrumm::engine::error::Unicode);

    /**
     * Returns whether this String is equal to another.  It will not take into
     * account different Normalization Forms of the text.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-27
     * @since  0.3
     *
     * @return If the String is equal to another String.
     *
     * @throw hummstrumm::engine::error::Unicode If either of the String objects
     * are invalid.
     */
    bool operator== (const String &string)
      const throw (hummstrumm::engine::error::Unicode);
    /**
     * Returns whether this String is not equal to another.  It will not take
     * into account different Normalization Forms of the text.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-10-09
     * @since  0.3
     *
     * @return If the String is not equal to another String.
     *
     * @throw hummstrumm::engine::error::Unicode If either of the String objects
     * are invalid.
     */
    bool operator!= (const String &string)
      const throw (hummstrumm::engine::error::Unicode);

    /**
     * Returns an iterator to the first Character in this String.  This iterator
     * can be used to access the Character.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-10-09
     * @since  0.3
     *
     * @return An iterator that references the first Character in the String.
     */
    String::Iterator GetStart (void)
      const throw ();
    /**
     * Returns an iterator to the Unicode NUL Character in this String.  This
     * iterator is guaranteed to exist, and is the last valid iterator in this
     * String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-10-09
     * @since  0.3
     *
     * @return An iterator that references the NUL Character in the String.
     */
    String::Iterator GetEnd (void)
      const throw ();

    bool IsMyIterator (const String::Iterator &iterator)
      const throw (int);

    void Insert (const String::Iterator &at, const String &stringToInsert)
      throw (int);
    void Remove (const String::Iterator &start, const String::Iterator &end)
      throw (int);

    /**
     * Returns a new String containing the substring starting with a starting
     * iterator and ending with the Character one before the ending iterator.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-10-16
     * @since  0.3
     *
     * @return A String equal to the substring of requested in this String.
     *
     * @param start [in] The Iterator from which to start counting Characters.
     * @param end   [in] The Iterator one after the final counted Character.
     */
    String GetSubstring (const String::Iterator &start,
                         const String::Iterator &end)
      const throw (int);

  private:
    /// A pointer to the memory buffer that contains the Unicode characters.
    char *characters;
};


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_TYPES_STRING
