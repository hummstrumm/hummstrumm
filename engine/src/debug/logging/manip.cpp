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

#include <iostream>

namespace hummstrumm
{
namespace engine
{
namespace debug
{
namespace logging
{


const LockType Lock = {};

// We need dynamic casts here, because we don't know if the ostream will have a
// StreamBuffer as a streambuf.

std::ostream &
operator<< (std::ostream &out, const SetFile manip)
{
  StreamBuffer *buf = dynamic_cast<StreamBuffer *> (out.rdbuf ());
  if (buf)
    buf->SetFile (manip.file);
  return out;
}

std::ostream &
operator<< (std::ostream &out, const SetLine manip)
{
  StreamBuffer *buf = dynamic_cast<StreamBuffer *> (out.rdbuf ());
  if (buf)
    buf->SetLine (manip.line);
  return out;
}

std::ostream &
operator<< (std::ostream &out, const LockType manip)
{
  StreamBuffer *buf = dynamic_cast<StreamBuffer *> (out.rdbuf ());
  if (buf)
    {
      while (buf->IsLocked ()); // Loop infinitely until we can lock.
      buf->Lock ();
    }
  return out;
}


}
}
}
}
