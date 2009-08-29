// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2009, the people listed in the AUTHORS file. 
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

#ifndef HUMMSTRUMM_ENGINE
#define HUMMSTRUMM_ENGINE

// The extensive namespace hierarchy in the game engine.

namespace hummstrumm
{
  namespace engine
  {
    namespace core
    {
      class Object;
      class Type;
      class Heap;
      class Pointer;
    }
    namespace types
    {
      class String;
      namespace measure;
    }
    namespace containers;
    namespace streams;
  }
}

#include <compileconfig.hpp>