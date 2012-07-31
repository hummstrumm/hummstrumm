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

/**
 * Window and OpenGL parameters.
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
     *
     * @param [in] param A reference to another WindowVisualInfo
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
     * Get the WGL/GLX context attributes.
     * The returned format is an array of (attrib, value) pairs.
     * (attrib1, value1, attrib2, value2, .., .., attribN, valueN)
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     *
     * @return An array of context attributes.
     */
    int* GetContextAttributes ();

    /**
     * Set the WGL/GLX context attributes. This gives the ability to the caller
     * to set the context attributes to its own liking. For example, 
     * the caller might want to disable or enable some specific feature 
     * that is not provided in the class data members.
     *
     * The given format must be an array of (attrib, value) pairs.
     * (attrib1, value1, attrib2, value2, .., .., attribN, valueN)
     * 
     * Only supported in Windows if wglCreateContextAttribsARB is available.
     * If that is not available then setting the context attributes manually 
     * has no influence because the system will use the old way
     * (a.k.a wglCreateContext).
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     *
     * @param [in] attrib An array of WGL/GLX context attributes.
     * @param [in] attribSize The attributes size. The attributes must be equal 
     * or less than ATTRIB_MAX to succeed.
     *
     * @return Whether the attributes were successfully set.
     */
    bool SetContextAttributes (const int* attrib, unsigned short attribSize);

    /**
     * Get the pixel format attributes in WGL/GLX format.
     * The returned format is an array of (attrib, value) pairs.
     * (attrib1, value1, attrib2, value2, .., .., attribN, valueN)
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     *
     * @param [in] offscreen Indicates whether we want the pixel attributes for 
     * the offscreen or window rendering.
     *
     * @return The pixel format attributes.
     */
    int* GetPixelFormatAttributes (bool offscreen);

    /**
     * Set the WGL/GLX pixel format attributes. This gives the ability to the 
     * caller to set the attributes to its own liking. For example, the
     * caller might want to disable or enable some specific feature that is 
     * not provided in the class data members. 
     *
     * The given format must be an array of (attrib, value) pairs.
     * (attrib1, value1, attrib2, value2, .., .., attribN, valueN)
     *
     * Only supported in Windows if wglChoosePixelFormatARB is available.
     * If that is not available then setting the attributes manually has
     * no influence because the system will use the old way
     * (a.k.a PIXELFORMATDESCRIPTOR).
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     *
     * @param [in] attrib An array of attributes.
     * @param [in] attribSize The attributes size. The attributes must be equal 
     * or less than ATTRIB_MAX.
     *
     * @return Whether the attributes were successfully set.
     */
    bool SetPixelFormatAttributes (const int* attrib, unsigned short attribSize);

    /**
     * Get the corresponding WGL/GLX parameters of the class data members.
     * The returned format is an array of attributes.
     * (attrib1, attrib2, .., attribN)
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     *
     * @param [in] sz The size of the returned array.
     *
     * @return The WGL/GLX parameters array.
     */
    int* GetQueryAttributes (int &sz) const;

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
    bool useFullscreen;
    
    bool useDoubleBuffer;

    bool useStereo;

    bool useAntiAliasing;

    bool useVerticalSync;

    bool useOffScreenRendering;

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
    
    int openGLMajorVer;

    int openGLMinorVer;

    unsigned int offscreenBufferWidth;
    
    unsigned int offscreenBufferHeight;

    bool offscreenUseLargestBufferAvailable;

  private:
    int* pixelAttributes;
    int* contextAttributes;
};

}
}
}
#endif
