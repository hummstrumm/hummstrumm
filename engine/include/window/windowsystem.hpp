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

#ifndef HUMMSTRUMM_ENGINE_WINDOW_SYSTEM
#define HUMMSTRUMM_ENGINE_WINDOW_SYSTEM

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#include <windows.h>
#include <queue>
#include <gl\gl.h>
#endif

#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
#include <climits>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>
#include <GL/glx.h>
#include "glxext.h"
#include "glext.h"
#endif


namespace hummstrumm
{
namespace engine
{
namespace window
{

enum Context
{
  WINDOW,
  PBUFFER,
};

class WindowSystem
{
  public:

    /**
     * Window System constructor.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     */
    WindowSystem();

    /**
     * Window System destructor.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     */
    ~WindowSystem();

    /**
     * Destroy the current window.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     */
    void DestroyWindow();

    /**
     * Create a window with the requested window parameters.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     * @param [in,out] windowParameters The requested and obtained window parameters. 
     */
    void (CreateWindow)(WindowVisualInfo &windowParameters);

    /**
     * Get the next window event.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     * @return A window event. 
     */
    hummstrumm::engine::events::WindowEvents* GetNextEvent();

    /**
     * The number of events waiting to be processed. 
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     */
    int GetPendingEventsCount() const;

    /**
     * Exchange the front and back buffers.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     */
    void SwapBuffers();

    /**
     * Change the current window to fullscreen or windowed mode.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     * @param [in,out] param The window parameters.
     */
    void SetMode(WindowVisualInfo &param);

    void SetContextCurrent(Context &ctx);

  private:    

    static WindowSystem* runningInstance;
    #ifdef HUMMSTRUMM_WINDOWSYSTEM_X11
    Display *dpy; // Pointer to a X11 display structure
    Window root; // Root window
    Window window; // Current window
    int screen;   // Default screen
    int depth;    // The depth of the default root window for default screen

    GLXContext windowContext;
    GLXContext pbufferContext;
    GLXPbuffer pbuffer;
    
    Atom wndProtocols;
    Atom wndDelete;

    // GLX Extensions
    PFNGLXSWAPINTERVALSGIPROC swapIntervalAddr;
    PFNGLXCHOOSEFBCONFIGPROC chooseFBConfigAddr;
    PFNGLXMAKECONTEXTCURRENTPROC makeContextCurrentAddr;
    PFNGLXCREATECONTEXTATTRIBSARBPROC createContextAttribsAddr;

    // Xrandr specific
    XRRScreenSize* supportedSizes;
    XRRScreenConfiguration* screenConfigInformation;
    Rotation originalRotation;
    SizeID originalSizeID;
    short originalRate;
    int numSupportedSizes;

    // PBuffer
    PFNGLXCREATEPBUFFERPROC createPbufferAddr;
    PFNGLXDESTROYPBUFFERPROC destroyPbufferAddr;

    /**
     * Initialize the GLX Extensions.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     */
    void InitializeGLXExtensions();

    /**
     * Check if a GLX Extension is supported
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     */
    bool IsGLXExtensionSupported(const char* extension, const GLubyte *extensions);

    /**
     * Get a X Window property.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     * @param [in] property The property we want.
     * @param [in] property_type The type of property.
     * @param [in] size Size of the returned data.
     *
     * @return A pointer to the property or null if property doesn't exist
     */
    char* GetXProperty(const Window &win, Atom property, Atom property_type, long &size) const;

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

    static int HandleGeneralXErrors(Display *dpy, XErrorEvent *xerr);

    static int HandleIOXErrors(Display *dpy);

    int IsResolutionSupported(unsigned int w, unsigned int h) const;

    #endif

    #ifdef HUMMSTRUMM_WINDOWSYSTEM_WINDOWS
    HINSTANCE moduleHandle;
    HWND windowHandle;
    HDC deviceContext;
    HGLRC renderingContext;

    // WGL Extensions
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
    PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT;
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
    PFNWGLMAKECONTEXTCURRENTARBPROC wglMakeContextCurrentARB;
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
    PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB;

    struct EventMsg
    {
      UINT   msg;
      WPARAM wparam;
      LPARAM lparam;
    };

    std::queue<EventMsg> msgQueue;

    /**
     * Initialize the WGL Extensions.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     */
    void InitializeWGLExtensions();

    /**
     * Get a description of the error code.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     * @param [in] pmsg A message to prepend to the error message
     * @param [in] code The error code.
     *
     * @return The description of the error code.
     */
    hummstrumm::engine::types::String GetErrorMessage(hummstrumm::engine::types::String premsg,
      DWORD code);
     
    /**
     * Process messages sent to the window.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     * @param [in] hWnd A handle to the window.
     * @param [in] uMsg The message.
     * @param [in] wParam Additional message information.
     * @param [in] lParam Additional message information.
     *
     * @return The result of the message processing and depends on the message sent.
     */
    static LRESULT CALLBACK ProcessWindowMessages(HWND hWnd, UINT uMsg,
      WPARAM wParam, LPARAM lParam);

    
    /**
     * Post an event message that will be retrieved by GetNextEvent()
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-16
     * @since 0.4
     *
     * @param [in] msg The message.
     * @param [in] wParam Additional message parameters.
     * @param [in] lParam Additional message information.
     *
     */
    void PostEventMessage(UINT msg, WPARAM wParam, LPARAM lParam);
    #endif
};

}
}
}
#endif
