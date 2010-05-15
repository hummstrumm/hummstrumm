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
#define HUMMSTRUMM_ENGINE_SOURCE

#include <iostream>

#include "hummstrummengine.hpp"

int
main (int argc, char **argv)
{
  // How are the definitions of the CMake variables doing?
#if defined (HUMMSTRUMM_ENDIAN_BIG) && defined (HUMMSTRUMM_ENDIAN_LITTLE)
  std::wcerr << L"Both endians are defined.\n";
  return 1;
#elif !defined (HUMMSTRUMM_ENDIAN_BIG) && !defined (HUMMSTRUMM_ENDIAN_LITTLE)
  std::wcerr << L"Neither endian is defined.\n";
  return 1;
#else
  

  hummstrumm::engine::system::Endian endianBig
    (hummstrumm::engine::system::Endian::Big);
  hummstrumm::engine::system::Endian endianLittle
    (hummstrumm::engine::system::Endian::Little);
  

  // Did the construction work/do the (in)equality operators work?
  if (endianBig != hummstrumm::engine::system::Endian::Big)
    {
      std::wcerr << L"The endianBig variable does not appear equal to the big "
                 << L"endian constant./n";
      return 1;
    }
  if (endianLittle != hummstrumm::engine::system::Endian::Little)
    {
      std::wcerr << L"The endianLittle variable does not appear equal to the "
                 << L"little endian constant./n";
      return 1;
    }
  

  // Are the endian constants the same?
  if (hummstrumm::engine::system::Endian::Big ==
      hummstrumm::engine::system::Endian::Little)
    {
      std::wcerr << L"The endian constants are the same.\n";
      return 1;
    }

  
  // Let us confuse the hell out of you and set the endianBig variable to the
  // little endian constant.  Does assignment work?
  endianBig = hummstrumm::engine::system::Endian::Little;
  if (endianBig != hummstrumm::engine::system::Endian::Little)
    {
      std::wcerr << L"Assignment does not change the value of the endian "
                 << L"variable correctly.\n";
      return 1;
    }
  

  // Is the system byte order correct?
#ifdef HUMMSTRUMM_ENDIAN_BIG
  if (hummstrumm::engine::system::Endian::GetSystemByteOrder () !=
      hummstrumm::engine::system::Endian::Big)
    {
      std::wcerr << L"The system endian is supposed to be Big.\n";
      return 1;
    }
#endif
#ifdef HUMMSTRUMM_ENDIAN_LITTLE
  if (hummstrumm::engine::system::Endian::GetSystemByteOrder () !=
      hummstrumm::engine::system::Endian::Little)
    {
      std::wcerr << L"The system endian is supposed to be Little.\n";
      return 1;
    }
#endif

  
  return 0;
#endif
}
