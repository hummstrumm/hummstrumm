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

#include <sstream>

namespace hummstrumm
{
namespace engine
{
namespace error
{


Error::Error (const char *fileName, unsigned int lineNumber,
              const char *function, const char *description,
              const char *text)
  throw ()
  : fileName (fileName),
    lineNumber (lineNumber),
    function (function),
    text (text),
    description (description)
{
}

Error::~Error ()
{
}

const char *
Error::GetFileName ()
  const throw ()
{
  return this->fileName;
}

unsigned int
Error::GetLineNumber ()
  const throw ()
{
  return this->lineNumber;
}

const char *
Error::GetText ()
  const throw ()
{
  return this->text;
}

const char *
Error::GetDescription ()
  const throw ()
{
  return this->description;
}

const char *
Error::GetFunction ()
  const throw ()
{
  return this->function;
}


std::ostream &
operator<< (std::ostream &out, const Error &e)
{
  out << e.GetFileName () << ':' << e.GetLineNumber () << " in " <<
    e.GetFunction () << ": " << e.GetDescription () << " " << e.GetText ();

  return out;
}


}
}
}
