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
 * Defines the Endian class, which stores information about byte order.
 *
 * @file   endian.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-26
 * @see    Endian
 */

#ifndef HUMMSTRUMM_ENGINE_SYSTEM_ENDIAN
#define HUMMSTRUMM_ENGINE_SYSTEM_ENDIAN


// For the various relational operator shortcuts.
#include <utility>
using namespace std::rel_ops;


namespace hummstrumm
{
namespace engine
{
namespace system
{

/**
 * Holds byte-order information.  This class also allows you to get the system
 * byte order in an Endian object.  (There are \#defines in the config.h file
 * that are created during CMake configuration.  You can use these, too, but
 * only in <tt>\#ifdef ... \#endif</tt> constructions.)
 *
 * Two static constants are created to represent each type of Endian.  If you
 * need to create an Endian of a specific value, use these.  You can also
 * compare existing Endian objects to these, to check their value.
 *
 * @version 0.2
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-03-26
 * @since   0.2
 *
 * @todo Add serialisation method, such as output as a Unicode byte order mark
 * (BOM).
 */
class Endian
{
  public:
    /**
     * Constructs an Endian from one of the constants or another Endian object.
     * If no Endian is passed, an Endian of the system byte order is
     * constructed.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-26
     * @since  0.2
     *
     * @param byteOrder [in] The byte order of the new Endian.
     */
    Endian (const Endian &byteOrder = GetSystemByteOrder ());
    /**
     * Destructs an Endian.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-26
     * @since  0.2
     */
    virtual ~Endian (void);

    /**
     * Checks if two endians are the same.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-26
     * @since  0.2
     *
     * @return Whether two Endians are the same.
     *
     * @note We don't have to implement a != operator, because a template is for
     * it using the == operator is provided by the \<utility\> header.
     */
    bool operator== (const Endian &endian) const throw ();

    /**
     * Returns the system byte order.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-26
     * @since  0.2
     *
     * @return The endianness of the system.
     */
    static Endian &GetSystemByteOrder (void) throw ();

    static Endian Big;    ///< The constant for big endianness.
    static Endian Little; ///< The constant for little endianness.

  private:
    /**
      * An internal structure for creating the static constants in the game
      * engine.  The user does not need these.
      *
      * @version 0.2
      * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
      * @date    2010-03-26
      * @since   0.2
      */
    enum Order
    {
      BIG  = 0,   ///< Big Endian.
      LITTLE = 1, ///< Little Endian.
    };

    /**
     * Constructs an Endina from the internal Order enumeration.  This
     * constructor is only used in the creation of the static constants.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-26
     * @since  0.2
     *
     * @param byteOrder [in] The byte order to construct. 
     */
    Endian (Endian::Order byteOrder);
    
    bool byteOrder; ///< The byte order.  A bool for size optimisation;
                    ///  enumerations are not necessarily as small as possible.
};


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_SYSTEM_ENDIAN
