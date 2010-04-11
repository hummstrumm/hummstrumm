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

#include <config.h>

#include <types/rawdata.hpp>
#include <system/endian.hpp>
#include <core/type.hpp>
#include <debug/log.hpp>

#include <new>
#include <algorithm>
#include <cstring>


namespace hummstrumm
{
namespace engine
{
namespace types
{


HUMMSTRUMM_IMPLEMENT_TYPE(hummstrumm::engine::types::RawData,
                          hummstrumm::engine::core::Object)


RawData::RawData (hummstrumm::engine::system::Endian endianness)
  : buffer (0),
    bufferSize (0),
    byteOrder (endianness)
{}


RawData::RawData (void *buffer, std::size_t bufferSize,
                  hummstrumm::engine::system::Endian endianness)
  : buffer (new (std::nothrow) char [bufferSize]),
    bufferSize (bufferSize),
    byteOrder (endianness)
{
  if (this->buffer)
    {
      std::memcpy (this->buffer, buffer, bufferSize);
    }
  else
    {
      // TODO: Move allocation into block so we can catch errors for info.
      LOG (L"Could not create RawData object.", ERROR);
      this->bufferSize = 0;
    }
}


RawData::~RawData (void)
{
  if (this->buffer)
    {
      delete [] reinterpret_cast<char *> (this->buffer);
    }
}


void
RawData::SwapByteOrder (void) throw ()
{
  for (std::size_t i = 0; i < this->bufferSize / 2; i++)
    {
      std::swap (reinterpret_cast<char *> (this->buffer)[i],
                 reinterpret_cast<char *> (this->buffer)[this->bufferSize-1-i]);
    }
}

void
RawData::ToBigEndian (void) throw ()
{
  if (this->GetByteOrder () == hummstrumm::engine::system::Endian::Big)
    {
      return;
    }
  else
    {
      this->SwapByteOrder ();
    }
}

void
RawData::ToLittleEndian (void) throw ()
{
  if (this->GetByteOrder () == hummstrumm::engine::system::Endian::Little)
    {
      return;
    }
  else
    {
      this->SwapByteOrder ();
    }
}


void
RawData::ToSystemEndian (void) throw ()
{
  if (this->GetByteOrder () ==
      hummstrumm::engine::system::Endian::GetSystemByteOrder ())
    {
      return;
    }
  else
    {
      this->SwapByteOrder ();
    }
}


const void *
RawData::GetBytes (void) const throw ()
{
  return this->buffer;
}


std::size_t
RawData::GetSize (void) const throw ()
{
  return this->bufferSize;
}


const hummstrumm::engine::system::Endian
RawData::GetByteOrder (void) const throw ()
{
  return this->byteOrder;
}


void
RawData::SetBytes (void *buffer, std::size_t bufferSize,
               hummstrumm::engine::system::Endian endianness)
  throw ()
{
  if (this->buffer)
    {
      delete [] reinterpret_cast<char *> (this->buffer);
    }

  this->buffer = new (std::nothrow) char [bufferSize];
  if (this->buffer)
    {
      std::memcpy (this->buffer, buffer, bufferSize);
      this->bufferSize = bufferSize;
      this->byteOrder  = endianness;
    }
  else
    {
      // TODO: Catch errors for info.
      LOG (L"Could not set RawData object.", ERROR);
      this->bufferSize = 0;
    }
}


}
}
}
