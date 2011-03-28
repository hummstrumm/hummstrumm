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


#ifndef HUMMSTRUMM_ENGINE_EVENTS
#define HUMMSTRUMM_ENGINE_EVENTS

namespace hummstrumm
{
namespace engine
{
namespace events
{

using hummstrumm::engine::renderer::WindowParameters;

class WindowEvents
{
  public:
    enum WindowEventType
    {
      WINDOW_RESIZE,
      WINDOW_CLOSE,
      KEY_PRESS,
      KEY_RELEASE,
      MOUSE_PRESS,
      MOUSE_RELEASE,
      MOUSE_MOTION,
      NONE
    };

    WindowEvents();

    virtual ~WindowEvents();

    WindowEventType getType();

  protected:
    WindowEventType type;

};

class StructureEvents: public WindowEvents
{

  public:
    StructureEvents(WindowEventType evType);

    StructureEvents(WindowEventType evType, int w, int h);
    
    virtual ~StructureEvents();

    int GetWidth();
    
    int GetHeight();

  private:
    int width;
    int height;
};

class KeyboardEvents: public WindowEvents
{
  public:
    KeyboardEvents(WindowEventType evType);

    virtual ~KeyboardEvents();
};

class MouseEvents: public WindowEvents
{
  public:
    MouseEvents(WindowEventType evType);

    virtual ~MouseEvents();
};

}
}
}


#endif
