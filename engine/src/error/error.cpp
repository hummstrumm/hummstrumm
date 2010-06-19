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

#include <cstring>
#include <cstdlib>
#include <sstream>

#include "hummstrummengine.hpp"

namespace hummstrumm
{
namespace engine
{
namespace error
{


Error::Error (const char *fileName, unsigned int lineNumber, const char *text,
              const char *description)
  throw ()
  : fileName ((char *) fileName),
    lineNumber (lineNumber),
    text ((char *) std::calloc (std::strlen (text) + std::strlen (description) +
              3, 1))
{
  std::strncpy (this->text, description, std::strlen (text));
  std::strncat (this->text, "  ", std::strlen (text));
  std::strncat (this->text, text, std::strlen (text));
  this->text[std::strlen (text) + std::strlen (description) + 2] = '\0';
}

Error::~Error (void)
{
  std::free (this->text);
}

const char *
Error::GetHumanReadableMessage (void)
  const throw ()
{
  std::stringstream ss;
  ss << "An error has occured in " << this->GetFileName ()
     << " at line "                << this->GetLineNumber ()
     << ":\n\n"                    << this->GetText () << "\n";
  return ss.str ().c_str ();
}

const char *
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

const char *
Error::GetText (void)
  const throw ()
{
  return this->text;
}


}
}
}
