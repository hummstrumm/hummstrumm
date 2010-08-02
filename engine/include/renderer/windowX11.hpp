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
 * Defines a X11 window.
 *
 * @file    windowSystem.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-07-24
 */

#ifndef HUMMSTRUMM_ENGINE_WINDOW_X11
#define HUMMSTRUMM_ENGINE_WINDOW_X11

#include <climits>
#include <cstring>
#include <X11/Xlib.h>
#include <X11/Xatom.h>


namespace hummstrumm
{
namespace engine
{
namespace renderer
{

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
     * Create a X11 window.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     * @param name Window name.
     * @param height Height of the window.
     * @param width Width of the window.
     * @param fs Window in fullscreen.
     *
     */
    virtual void createWindow(std::string name, unsigned height, unsigned width, bool fs);

    /**
     * Set this window to fullscreen.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     */
    virtual void setToFullscreen();

    /**
     * Set this window back to window mode if its in fullscreen.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     */
    virtual void setToWindowMode();


     /**
     * Set this window width.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     */
    virtual void setWidth(unsigned width);

     /**
     * Set this window height.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     */
    virtual void setHeight(unsigned height);
 

  private:
    // Pointer to a X11 display structure.
    Display *dpy;
    // Root window.
    Window root;
    // To configure the window parameters.
    XWindowChanges winParam;
    // Is the window manager NetWM compliant
    bool NetWMSupport;
    // Default screen
    int screen;
    // The depth (number of planes) of the default root window for 'screen'
    int depth;
    // Main window
    Window winXMain;

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
     * @return True if successful, false otherwise.
     */  
    char * getXProperty(Window &win, Atom property, Atom property_type, long &size);

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
    bool IsNetWMCompliant();
};


}
}
}
#endif
