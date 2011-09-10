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

class HsWindowSystem
{
  public:
    HsWindowSystem();

    ~HsWindowSystem();

    void HsDestroyWindow();

    void HsCreateWindow(WindowVisualInfo &windowParameters);

    hummstrumm::engine::events::WindowEvents* HsGetNextEvent();

    int HsGetPendingEventsCount() const;

    void HsSwapBuffers();

  private:    
    void HsSetMode(WindowVisualInfo &param);

    #ifdef HUMMSTRUMM_WINDOWSYSTEM_X11
    Display *dpy; // Pointer to a X11 display structure
    Window  root; // Root window
    int screen;   // Default screen
    int depth;    // The depth of the default root window for default screen
    Window winMn; // Current window
    GLXContext glxCtx;
    
    Atom wndProtocols;
    Atom wndDelete;

    // GLX Extensions
    PFNGLXSWAPINTERVALSGIPROC swapIntervalAddr;
    PFNGLXCHOOSEFBCONFIGPROC chooseFBConfigAddr;
    PFNGLXMAKECONTEXTCURRENTPROC makeContextCurrentAddr;
    PFNGLXCREATECONTEXTATTRIBSARBPROC createContextAttribsAddr;

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
