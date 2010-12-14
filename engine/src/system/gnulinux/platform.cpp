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
#include "hummstrummengine.hpp"

#include <cstring>
#include <sys/utsname.h>

namespace hummstrumm
{
namespace engine
{
namespace system
{


Platform::Platform (void)
  throw ()
  : name (0)
{
  utsname systemName;
  uname (&systemName);

  std::size_t length = std::strlen (systemName.sysname) + 1 +
    std::strlen (systemName.nodename) + 1 +
    std::strlen (systemName.release) + 1 +
    std::strlen (systemName.version) + 1 +
    std::strlen (systemName.machine) + 1;
  this->name = new char [length];
  
  std::strcpy (this->name, systemName.sysname);
  std::strcat (this->name, " ");
  std::strcat (this->name, systemName.nodename);
  std::strcat (this->name, " ");
  std::strcat (this->name, systemName.release);
  std::strcat (this->name, " ");
  std::strcat (this->name, systemName.version);
  std::strcat (this->name, " ");
  std::strcat (this->name, systemName.machine);
}


Platform::~Platform (void)
{
  delete this->name;
}


char *
Platform::GetName (void)
  const throw ()
{
  return this->name;
}


}
}
}
