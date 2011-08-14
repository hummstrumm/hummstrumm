// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2011, the people listed in the AUTHORS file.
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
 * Defines a X11 window.
 *
 * @file    renderer/windowX11.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-07-24
 */

#ifndef HUMMSTRUMM_ENGINE_WINDOW_X11
#define HUMMSTRUMM_ENGINE_WINDOW_X11

#include <climits>
#include <cstring>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>

#include <GL/glx.h>

namespace hummstrumm
{
namespace engine
{
namespace renderer
{

using namespace hummstrumm::engine::events;

/**
 * Implements the Window System for the X11 window system.
 *
 * @version 0.3
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-07-24
 * @since 0.3
 *
 */
class WindowX11: public WindowSystem
{
  public:
    /**
     * X11 window constructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     */
    WindowX11();
    /**
     * X11 window destructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     */
     ~WindowX11();
    
    /**
     * Destroy a X11 window.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2011-07-30
     * @since 0.3
     *
     */
    void DestroyWindow();
    /**
     * Create a X11 window.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     * @param winParam Window parameters.
     *
     */
    void CreateWindow(const WindowParameters &winParam);

    /**
     * Set this window to fullscreen.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     */
    void SetFullscreen();
    /**
     * Set this window back to window mode if its in fullscreen.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     */
    void SetWindowMode();

     /**
     * Get current window drawable width.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2011-01-03
     * @since 0.3
     *
     */
    int GetWidth();
     /**
     * Get current window drawable height.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2011-01-03
     * @since 0.3
     *
     */
    int GetHeight();

     /**
     * Get window event. If event queue is empty, the output buffer is 
     * flushed and getEvent is blocked until an event is received.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     * @note Needs to return the Event.
     */
    WindowEvents* GetNextEvent() const;
     /**
     * Get the number of pending events.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     * @return The number of events that have been received  but have 
     * not been removed from the event queue.
     */
    int GetPendingEventsCount() const;

     /**
     * Swap buffers if using double buffer.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-12-24
     * @since 0.3
     *
     */
    virtual void SwapBuffers() const;
 
  private:
    /// Pointer to a X11 display structure
    Display *dpy;
    /// Root window
    Window root;
    /// Default screen
    int screen;
    /// The depth (number of planes) of the default root window for 'screen'
    int depth;
    /// window
    Window winMn;
    /// Atom for deleting.
    Atom wndDelete;
    /// Atom for protocols.
    Atom wndProtocols;
    // Supported GLX version (major)
    int glXVerMajor;
    // Supported GLX version (minor)
    int glXVerMinor;
    // Pointer to the default screen
    Screen *scr;

    /**
     * Get a X Window property.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     * @param property The property we want.
     * @param property_type The type of property.
     * @param size Size of the returned data.
     *
     * @return A pointer to the property or null if property doesn't exist
     */  
    char * GetXProperty(const Window &win, Atom property, Atom property_type, long &size) const;

    /**
     * Checks if the Window manager supports 'extended window manager hints' 
     * (NetWM).
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     * @return True if yes, false otherwise.
     */  
    bool IsNetWMCompliant() const;
    /**
     * Verify if GLX extension is supported.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     * @return True if yes, false otherwise.
     */  
    bool IsGLXSupported() const;
    /**
     * Get the supported GLX version.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     * @param major Where to store the major value of version.
     * @param minor Where to store the minor value of version.
     *
     * @return True if success false otherwise. 
     */  
    bool GetGLXVersion(int *major, int *minor) const;
};


}
}
}
#endif
