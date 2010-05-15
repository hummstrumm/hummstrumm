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

#include <string>
#include <sstream>

#include "hummstrummengine.hpp"

namespace hummstrumm
{
namespace engine
{
namespace error
{


Error::Error (std::string fileName, unsigned int lineNumber, std::string text)
  : fileName (fileName),
    lineNumber (lineNumber),
    text (text)
{}

Error::~Error (void)
{}

std::string
Error::GetHumanReadableMessage (void)
  const throw ()
{
  std::stringstream ss;
  ss << "An error has occured in " << this->GetFileName ()
     << " at line " + this->GetLineNumber ()
     << ":\n\n" + this->GetText () << "\n";
  return ss.str ();
}

std::string
Error::GetFileName (void)
  const throw ()
{
  return this->fileName;
}

unsigned int
Error::GetLineNumber (void)
  const throw ()
{
  return this->lineNumber;
}

std::string
Error::GetText (void)
  const throw ()
{
  return this->text;
}


}
}
}
