// -*- c++ -*-
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

#define HUMMSTRUMM_ENGINE_SOURCE

#include "hummstrummengine.hpp"

namespace hummstrumm
{
namespace engine
{
namespace events
{

WindowEvents::WindowEvents() { type = WindowEvents::NONE; }

WindowEvents::~WindowEvents() { }

WindowEvents::WindowEventType
WindowEvents::getType()
{
  return type;
}

StructureEvents::StructureEvents(WindowEventType evType) 
{ 
  type = evType;
  width = 0; 
  height = 0;
}

StructureEvents::StructureEvents(WindowEventType evType, int w, int h) 
{ 
  type = evType;
  width = w;
  height = h;
}

StructureEvents::~StructureEvents() { }

int
StructureEvents::GetWidth() { return width; }

int
StructureEvents::GetHeight() { return height; }

KeyboardEvents::KeyboardEvents(WindowEventType evType) 
{ 
  type = evType;
}

KeyboardEvents::~KeyboardEvents() { }


MouseEvents::MouseEvents(WindowEventType evType) 
{ 
  type = evType;
}

MouseEvents::~MouseEvents() { }

}
}
}

