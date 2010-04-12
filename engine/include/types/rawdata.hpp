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
 * Defines several cross-platform, fixed-size integer types.
 *
 * @file   rawdata.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-24
 * @see    RawData
 */

#ifndef HUMMSTRUMM_ENGINE_TYPES_RAWDATA
#define HUMMSTRUMM_ENGINE_TYPES_RAWDATA


#include <core/object.hpp>
#include <core/type.hpp>
#include <core/pointer.hpp>
#include <system/endian.hpp>


namespace hummstrumm
{
namespace engine
{
namespace types
{

/**
 * Holds a buffer of device-dependent data.  This buffer allows for specific
 * representations of data, accessing each byte of the data, and converting data
 * from one endian to another for ease of data exchange.
 *
 * @version 0.2
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-03-26
 * @since   0.2
 */
class RawData : public hummstrumm::engine::core::Object
{
    HUMMSTRUMM_DECLARE_TYPE (RawData)
  public:
    /**
     * Constructs a new RawData object with no data.  The data is of certain
     * byte order.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-12
     * @since  0.2
     * 
     * @param endianness The byte order to use.
     */
    RawData (hummstrumm::engine::system::Endian endianness =
             hummstrumm::engine::system::Endian ());
    /**
     * Constructs a new RawData object with some buffer of data.  The data is
     * of certain byte order.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-12
     * @since  0.2
     *
     * @param buffer The data to copy into the RawData object, in the byte order
     * as defined by the endianness argument.
     * @param bufferSize The amount of data to copy from the buffer.
     * @param endianness The byte order of the data.
     */
    RawData (void *buffer, std::size_t bufferSize,
             hummstrumm::engine::system::Endian endianness =
             hummstrumm::engine::system::Endian ());
    /**
     * Destructs a RawData object.  Frees the data buffer.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-12
     * @since  0.2
     */
    virtual ~RawData (void);

    /**
     * Returns a specific byte of the RawData.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-12
     * @since  0.2
     *
     * @param byteNumber The number of the byte to access, from the least
     * significant byte.
     *
     * @returns The value stored in the accessed byte.
     */
    unsigned char
    operator[] (int byteNumber) const throw ();
    
    /**
     * Converts the data stored in the RawData into big endian data, if it is
     * not so already.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-12
     * @since  0.2
     * 
     * @warning If you are on a little endian system, like Intel x86
     * compatibles, and call GetBytes() after this call, the data will be
     * improperly calculated upon.
     */
    void ToBigEndian    (void) throw ();
    /**
     * Converts the data stored in the RawData into little endian data, if it is
     * not so already.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-12
     * @since  0.2
     * 
     * @warning If you are on a big endian system, like Intel Itanium, and call
     * GetBytes() after this call, the data will be improperly calculated upon.
     */
    void ToLittleEndian (void) throw ();
    /**
     * Converts the data stored in the RawData into the native system byte
     * order, if it is not so already.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-12
     * @since  0.2
     * 
     * @note After this call, your computer will be able to calculate upon the
     * data natively.
     */
    void ToSystemEndian (void) throw ();

    /**
     * Returns the actual data stored within the RawData.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-12
     * @since  0.2
     *
     * @returns A pointer to the buffer of the actual bytes of data.
     */
    const void  *GetBytes (void) const throw ();
    /**
     * Returns the size of the actual data stored within the RawData in bytes.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-12
     * @since  0.2
     *
     * @returns The size of the buffer of data currently in the RawData object.
     */
    std::size_t  GetSize  (void) const throw ();
    /**
     * Returns the endianness of the data stored in the RawData buffer.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-12
     * @since  0.2
     *
     * @returns The byte order of the RawData.
     */
    const hummstrumm::engine::system::Endian GetByteOrder (void) const throw ();

    /**
     * Sets the data stored in the RawData.  The old data is forgotten.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-12
     * @since  0.2
     *
     * @param buffer A pointer to the buffer containing the data.
     * @param bufferSize The amount of data to copy from the buffer.
     * @param endianness The byte order of the data.
     */
    void SetBytes (void *buffer, std::size_t bufferSize,
                   hummstrumm::engine::system::Endian endianness =
                   hummstrumm::engine::system::Endian ()) throw ();
                   
  private:
    /**
     * Swaps the byte order of the data in the RawData object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-04-12
     * @since  0.2
     */
    void SwapByteOrder (void) throw ();

    void       *buffer;     ///< The actual data buffer.
    std::size_t bufferSize; ///< The size of the data.
    hummstrumm::engine::system::Endian byteOrder; // The data's endianness.
};


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_TYPES_RAWDATA
