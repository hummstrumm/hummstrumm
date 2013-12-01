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

#ifndef HUMMSTRUMM_ENGINE_SYSTEM_ENDIANNESS_INL
#define HUMMSTRUMM_ENGINE_SYSTEM_ENDIANNESS_INL


namespace hummstrumm
{
namespace engine
{
namespace system
{


Endianness::Endian
Endianness::GetSystemEndianness ()
  const /* noexcept */
{
  return systemEndianness;
}


template <typename T>
T
Endianness::SwitchEndian (const T memory)
  const /* noexcept */
{
  union
  {
      T data;
      unsigned char bytes[sizeof (T)];
  };

  data = memory;

  // TODO: use <algorithm> for this
  int i = 0;
  int j = sizeof (T) - 1;
  while (i < j)
    {
      unsigned char temp = bytes[i];
      bytes[i] = bytes[j];
      bytes[j] = temp;
      ++i;
      --j;
    }

  return data;
}


template <typename T>
T
Endianness::ConvertBigToSystem (const T bigEndian)
  const /* noexcept */
{
  if (GetSystemEndianness () == Big)
    {
      return bigEndian;
    }
  else
    {
      return SwitchEndian (bigEndian);
    }
}


template <typename T>
T
Endianness::ConvertLittleToSystem (const T littleEndian)
  const /* noexcept */
{
  if (GetSystemEndianness () == Little)
    {
      return littleEndian;
    }
  else
    {
      return SwitchEndian (littleEndian);
    }
}


template <typename T>
T
Endianness::ConvertSystemToBig (const T systemEndian)
  const /* noexcept */
{
  if (GetSystemEndianness () == Big)
    {
      return systemEndian;
    }
  else
    {
      return SwitchEndian (systemEndian);
    }
}


template <typename T>
T
Endianness::ConvertSystemToLittle (const T systemEndian)
  const /* noexcept */
{
  if (GetSystemEndianness () == Little)
    {
      return systemEndian;
    }
  else
    {
      return SwitchEndian (systemEndian);
    }
}


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_SYSTEM_ENDIANNESS
