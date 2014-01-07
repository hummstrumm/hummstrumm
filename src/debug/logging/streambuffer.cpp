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

#include "hummstrummengine.hpp"

#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

namespace hummstrummengine {
namespace debug {
namespace logging {


StreamBuffer::StreamBuffer (vector<shared_ptr<Backend>> backends)
  : backends (backends),
    file ("(no file)"),
    line (0),
    level (Level::none),
    lock (false)
{
}

void
StreamBuffer::SendToBackends ()
{
  time_t t = time (0);
  string message = str ();
  
  for (auto i = backends.begin (); i != backends.end (); ++i)
    {
      // Funny syntax here: first we dereference the iterator (that's the
      // inner star), and then we dereference the smart pointer that's in
      // the vector (leftmost star).  Then we call the @c operator() of that
      // dereferenced backend.
      (**i) (t, file, line, level, message);
    }
}

int
StreamBuffer::sync ()
{
  // Let the parent class do its thing.
  int result = stringbuf::sync ();
  if (result == -1) return result;
  
  // Now we flush to backends and clear our own string buffer.
  //   --> Is this efficient?  Will the string make lots of allocations?
  //       Can we set a default size, à la std::string's constructor that
  //       takes an integer value for size?
  try
    {
      SendToBackends ();
      str ("");
      file = "(no file)";
      line = 0;
      level = Level::none;
      lock = false;
    }
  catch (...)
    {
      // We have to return -1 on an error.  I would rather throw an error,
      // but whatever.
      return -1;
    }
  
  return 0;
}

}
}
}
