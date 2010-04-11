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
 * Holds a buffer of device-dependent data.
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
    RawData (hummstrumm::engine::system::Endian endianness =
             hummstrumm::engine::system::Endian ());
    RawData (void *buffer, std::size_t bufferSize,
             hummstrumm::engine::system::Endian endianness =
             hummstrumm::engine::system::Endian ());
    virtual ~RawData (void);
    
    void ToBigEndian    (void) throw ();
    void ToLittleEndian (void) throw ();
    void ToSystemEndian (void) throw ();

    const void  *GetBytes (void) const throw ();
    std::size_t  GetSize  (void) const throw ();
    const hummstrumm::engine::system::Endian GetByteOrder (void) const throw ();

    void SetBytes (void *buffer, std::size_t bufferSize,
                   hummstrumm::engine::system::Endian endianness =
                   hummstrumm::engine::system::Endian ()) throw ();
                   
  private:
    void SwapByteOrder (void) throw ();

    void       *buffer;
    std::size_t bufferSize;
    hummstrumm::engine::system::Endian byteOrder;
};


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_TYPES_RAWDATA
