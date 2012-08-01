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

#ifndef HUMMSTRUMM_ENGINE_SYSTEM_PROCESSORS_INL
#define HUMMSTRUMM_ENGINE_SYSTEM_PROCESSORS_INL


namespace hummstrumm
{
namespace engine
{
namespace system
{


unsigned
Processors::GetNumberOfProcessors ()
  const /* noexcept */
{
  return numberOfProcessors;
}


std::string
Processors::GetProcessorName (int index)
  const /* noexcept */
{
  return processorStrings[index];
}


bool
Processors::HaveSseSupport ()
  const /* noexcept */
{
  return sseSupport;
}


bool
Processors::HaveSse2Support ()
  const /* noexcept */
{
  return sse2Support;
}


bool
Processors::HaveSse3Support ()
  const /* noexcept */
{
  return sse3Support;
}


bool
Processors::HaveSse41Support ()
  const /* noexcept */
{
  return sse41Support;
}


bool
Processors::HaveSse42Support ()
  const /* noexcept */
{
  return sse42Support;
}


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_SYSTEM_PROCESSORS_INL
