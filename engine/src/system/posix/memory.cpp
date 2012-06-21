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

#include "hummstrummengine.hpp"

#include <cstdlib>

namespace hummstrumm
{
namespace engine
{
namespace system
{


Memory::Memory ()
  /* noexcept */
  : totalMemory (0),
    freeMemory (0)
{
  // There no way of telling on POSIX how much memory there is.  If you want
  // this, implement it on a platform-by-platform basis.
}

Memory::~Memory ()
{
}

std::size_t
Memory::GetTotalMemory ()
  const /* noexcept */
{
  return totalMemory;
}

std::size_t
Memory::GetFreeMemory ()
  const /* noexcept */
{
  return freeMemory;
}

void
Memory::Update ()
  /* noexcept */
{
}


}
}
}
