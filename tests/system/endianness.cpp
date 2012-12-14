// -*- mode: c++; c-file-style: hummstrumm -*-
/* Humm and Strumm Engine
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

#ifdef __GNUC__
#  define CIPRA_CXX_ABI
#endif
#define CIPRA_USE_VARIADIC_TEMPLATES
#include <cipra/cipra.h>

#include "hummstrummengine.hpp"
using namespace hummstrumm::engine::system;

int
main ()
{
  class EndiannessTest : public cipra::fixture
  {
      virtual void
      test () override
      {
        plan (24);

        auto littleEndian     = new_ok<Endianness::Endian> (Endianness::Little),
          bigEndian           = new_ok<Endianness::Endian> (Endianness::Big),
          anotherLittleEndian = new_ok<Endianness::Endian> (Endianness::Little),
          anotherBigEndian    = new_ok<Endianness::Endian> (bigEndian);

        is (littleEndian, Endianness::Little, "endian storage");
        is (bigEndian, Endianness::Big, "endian storage");
        is (anotherLittleEndian, Endianness::Little, "endian storage");
        is (anotherBigEndian, Endianness::Big, "endian storage");

        is (littleEndian, littleEndian, "endian self-equality");
        is (bigEndian, bigEndian, "endian self-equality");
        is (anotherLittleEndian, anotherLittleEndian, "endian self-equality");
        is (anotherBigEndian, anotherBigEndian, "endian self-equality");

        is (anotherLittleEndian, littleEndian, "endian equality");
        is (littleEndian, anotherLittleEndian, "endian equality");
        is (anotherBigEndian, bigEndian, "endian equality");
        is (bigEndian, anotherBigEndian, "endian equality");

        isnt (littleEndian, bigEndian, "endian inequality");
        isnt (littleEndian, anotherBigEndian, "endian inequality");
        isnt (bigEndian, littleEndian, "endian inequality");
        isnt (bigEndian, anotherLittleEndian, "endian inequality");
        isnt (anotherLittleEndian, bigEndian, "endian inequality");
        isnt (anotherLittleEndian, anotherBigEndian, "endian inequality");
        isnt (anotherBigEndian, littleEndian, "endian inequality");
        isnt (anotherBigEndian, anotherLittleEndian, "endian inequality");
      }
  } test;

  return test.run ();
}
