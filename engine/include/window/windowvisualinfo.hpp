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
 * Window visual parameters.
 *
 * @file    window/windowvisualinfo.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-07-24
 */

#ifndef HUMMSTRUMM_ENGINE_WINDOW_VISUAL_INFO
#define HUMMSTRUMM_ENGINE_WINDOW_VISUAL_INFO

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#include <gl\gl.h>
#include "wglext.h"
#endif

namespace hummstrumm
{
namespace engine
{
namespace window
{

/**
 * Window parameters to be used in the hummstrumm window system.
 *
 * @version 0.3
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-09-28
 * @since 0.3
 */
class WindowVisualInfo
{
  public:  
    /**
     * Initializes the parameters to a default configuration values.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     */
    WindowVisualInfo ();

    /**
     * Construct a WindowVisualInfo object from another WindowVisualInfo object.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     */
    WindowVisualInfo (const WindowVisualInfo &param);

    /**
     * Destructs a WindowVisualInfo object.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     */
    ~WindowVisualInfo ();

    /**
     * Get the visual descriptor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     *
     * @return A pointer to a window descriptor.
     * @note The caller is responsible for freeing the pointer.
     */
    int* GetWindowDescriptor ();

    /**
     * Set the visual descriptor. This gives the power to the caller
     * to set the descriptor to its own liking. For example, the caller
     * might want to disable or enable some specific feature that is 
     * not provided in the class data members. 
     * 
     * Only supported in Windows if wglChoosePixelFormatARB is available.
     * If that is not available then setting the descriptor manually has
     * no influence because the system will use the old way
     * (a.k.a PIXELFORMATDESCRIPTOR).
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     *
     * @param [in] desc A pointer to a window descriptor.
     * @param [in] descSize The descriptor size. The descriptor must be equal 
     * or less than ATTRIB_MAX.
     *
     * @return Whether the descriptor was successfully set.
     */
    bool SetWindowDescriptor (const int* desc, unsigned short descSize);

    // Parameters common to every window for all systems 

    /// Defines the window caption name.
    std::string name;
    /// Defines the window position in X.
    unsigned short positionX;
    /// Defines the window position in Y.
    unsigned short positionY;
    /// Defines the window height.
    unsigned short height;
    /// Defines the window width.
    unsigned short width;
    /// Whether the window should be created in fullscreen.
    bool isFullscreen;
    
    bool isDoubleBuffer;

    bool isStereo;

    bool verticalSync;

    int renderType;

    int depthSize;

    int bufferSize;

    int redSize;

    int greenSize;

    int blueSize;
  
    int alphaSize;

    int accumRedSize;
  
    int accumGreenSize;

    int accumBlueSize;
  
    int accumAlphaSize;

    int stencilSize;

    int auxBuffers;

    int samples;

  private:
    int* descriptor;
 
};

}
}
}
#endif
