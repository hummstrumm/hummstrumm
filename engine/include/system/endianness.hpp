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

/**
 * Defines the Endianness class, which provides information about the byte order
 * of the system and conversion methods.
 *
 * @file   system/endianness.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-11-27
 * @see    Endianness
 */

#ifndef HUMMSTRUMM_ENGINE_SYSTEM_ENDIANNESS
#define HUMMSTRUMM_ENGINE_SYSTEM_ENDIANNESS


namespace hummstrumm
{
namespace engine
{
namespace system
{

/**
 * Provides information about the system's byte order as well as conversion
 * methods between endian sizes.
 *
 * @version 0.3
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-11-27
 * @since   0.3
 */
class Endianness
{
  public:
    /**
     * Represents the two byte orders possible.
     *
     * @version 0.3
     * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date    2010-11-27
     * @since   0.3
     */
    enum Endian
    {
      Little, ///< Little endian, like x86 and x64.
      Big,    ///< Big endian, like PowerPC and network byte order.
    };

    /**
     * Constructs a new Endianness object.  The system endianness is detected.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     */
    Endianness ()
      /* noexcept */;
    /**
     * Destructs an Endianness object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     */
    virtual ~Endianness ();

    /**
     * Returns the system's Endianness.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @return The system's byte order.
     */
    Endian GetSystemEndianness ()
      const /* noexcept */;


    // Conversions

    /**
     * Switches the endian of an atomic type.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param [in] memory A value.
     * 
     * @return An equivalent swapped-endian value
     */
    template <typename T>
    T SwitchEndian (const T memory)
      const /* noexcept */;

    /**
     * Converts an atomic type of big endianness to its equivalent system endian
     * value.  The output of this depends on the endianess of the system.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param [in] bigEndian The big endian value.
     * 
     * @return An equivalent system endian value.
     */
    template <typename T>
    T ConvertBigToSystem (const T bigEndian)
      const /* noexcept */;

    /**
     * Converts an atomic type of /little endianness to its equivalent system
     * endian value.  The output of this depends on the endianess of the system.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param [in] littleEndian The little endian value.
     * 
     * @return An equivalent system endian value.
     */
    template <typename T>
    T ConvertLittleToSystem (const T littleEndian)
      const /* noexcept */;

    /**
     * Converts an atomic type of system endianness to its equivalent big endian
     * value.  The output of this will always be big endian.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param [in] systemEndian The system endian value.
     * 
     * @return An equivalent big endian value.
     */
    template <typename T>
    T ConvertSystemToBig (const T systemEndian)
      const /* noexcept */;

    /**
     * Converts an atomic type of system endianness to its equivalent little
     * endian value.  The output of this will always be little endian.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param [in] systemEndian The system endian value.
     * 
     * @return An equivalent little endian value.
     */
    template <typename T>
    T ConvertSystemToLittle (const T systemEndian)
      const /* noexcept */;
    

  private:
    Endian systemEndianness; ///< The byte order of the system.
};


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_SYSTEM_ENDIANNESS
