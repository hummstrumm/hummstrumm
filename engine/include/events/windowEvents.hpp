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

/**
 * Defines events used by the window system.
 * 
 * @file    events/windowEvents.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-09-25
 */

#ifndef HUMMSTRUMM_ENGINE_EVENTS
#define HUMMSTRUMM_ENGINE_EVENTS

namespace hummstrumm
{
namespace engine
{
namespace events
{

/**
 * The class for representing events from the window system.  This is the
 * superclass of all separate window events.
 *
 * @version 0.3
 * @author  Ricardo Tiago <RTiago@gmail.com>
 * @date    2011-01-07
 * @since   0.3
 *
 * @note We're probably going to have to change this class when the event system
 * is completed.
 */
class WindowEvents
{
  public:
    /**
     * Represents the various individual types of window system events that the
     * codebase currently handles.
     *
     * @version 0.3
     * @author  Ricardo Tiago <RTiago@gmail.com>
     * @date    2011-01-07
     * @since   0.3
     */
    enum WindowEventType
    {
      WINDOW_RESIZE,     ///< Resizing the window.
      WINDOW_CLOSE,      ///< Closing the window.
      KEY_PRESS,         ///< Key down.
      KEY_RELEASE,       ///< Key up.
      MOUSE_PRESS,       ///< Mouse button down.
      MOUSE_RELEASE,     ///< Mouse button up.
      MOUSE_MOTION,      ///< Mouse movement.
      NONE               ///< No event.
    };

    /**
     * Constructs a new WindowEvents object.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-01-07
     * @since  0.3
     */
    WindowEvents();

    /**
     * Destructs an existing WindowEvents object.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-01-07
     * @since  0.3
     */
    virtual ~WindowEvents();

    /**
     * Retrieves the type of the WindowEvent emitted.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-01-07
     * @since  0.3
     *
     * @return The type of the event.
     */
    WindowEventType getType();

  protected:
    /// The type of this event.
    WindowEventType type;

};

/**
 * Represents window events related to the structure of the window, as opposed
 * to direct user input.
 *
 * @version 0.3
 * @author  Ricardo Tiago <RTiago@gmail.com>
 * @date    2011-01-07
 * @since   0.3
 */
class StructureEvents: public WindowEvents
{
  public:
    /**
     * Constructs a new StructureEvents object.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-01-07
     * @since  0.3
     *
     * @param [in] evType The specific type of structure event emitted.
     */
    StructureEvents(WindowEventType evType);
    /**
     * Constructs a new StructureEvents object.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-01-07
     * @since  0.3
     *
     * @param [in] evType The specific type of structure event emitted.
     * @param [in] w      The new width of the window, if applicable.
     * @param [in] h      The new height of the window, if applicable.
     */
    StructureEvents(WindowEventType evType, int w, int h);
    /**
     * Destructs an existing StructureEvents object.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-01-07
     * @since  0.3
     */
    virtual ~StructureEvents();

    /**
     * Returns the new width of the window, if applicable.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-01-07
     * @since  0.3
     *
     * @return The width of the window.
     */
    int GetWidth();
    /**
     * Returns the new height. of the window, if applicable.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-01-07
     * @since  0.3
     *
     * @return The height of the window.
     */
    int GetHeight();

  private:
    /// The new width of the window, when applicable.
    int width;
    /// The new height of the window, when applicable.
    int height;
};

/**
 * Represents window events due to user input via the keyboard.
 *
 * @version 0.3
 * @author  Ricardo Tiago <RTiago@gmail.com>
 * @date    2011-01-07
 * @since   0.3
 */
class KeyboardEvents: public WindowEvents
{
  public:
    /**
     * Constructs a new KeyboardEvents object.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-01-07
     * @since  0.3
     *
     * @param [in] evType The specific type of keyboard event emitted.
     */
    KeyboardEvents(WindowEventType evType);
    /**
     * Destructs an existing KeyboardEvents object.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-01-07
     * @since  0.3
     */
    virtual ~KeyboardEvents();
};

/**
 * Represents window events due to user input via the mouse.
 *
 * @version 0.3
 * @author  Ricardo Tiago <RTiago@gmail.com>
 * @date    2011-01-07
 * @since   0.3
 */
class MouseEvents: public WindowEvents
{
  public:
    /**
     * Constructs a new MouseEvents object.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-01-07
     * @since  0.3
     *
     * @param [in] evType The specific type of keyboard event emitted.
     */
    MouseEvents(WindowEventType evType);
    /**
     * Destructs an existing MouseEvents object.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-01-07
     * @since  0.3
     */
    virtual ~MouseEvents();
};

}
}
}


#endif
