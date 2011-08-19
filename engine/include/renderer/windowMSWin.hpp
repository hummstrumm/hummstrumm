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
 * Defines a Microsoft Windows window.
 *
 * @file    renderer/windowMSWin.hpp
 * @author  Ricardo Tiago <rtiago.mendes@gmail.com>
 * @date    2011-07-12
 */

#ifndef HUMMSTRUMM_ENGINE_WINDOW_MSWIN
#define HUMMSTRUMM_ENGINE_WINDOW_MSWIN

#include <windows.h>
#include <gl\gl.h>

namespace hummstrumm
{
namespace engine
{
namespace renderer
{

using namespace hummstrumm::engine::events;

/**
 * Implements the Window System for Microsoft Windows.
 *
 * @version 0.4
 * @author Ricardo Tiago <rtiago.mendes@gmail.com>
 * @date 2011-07-12
 * @since 0.4
 */

class WindowMSWin : public WindowSystem
{
  public:
    /**
     * Microsoft Windows window constructor.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-07-12
     * @since 0.4
     */
    WindowMSWin();

    /**
     * Microsoft Windows window destructor.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-07-12
     * @since 0.4
     */
    ~WindowMSWin();

    /**
     * Destroy a Microsoft Windows window.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-07-12
     * @since 0.4
     *
     */
    void DestroyWindow();
    /**
     * Create a Microsoft Windows window.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-07-12
     * @since 0.4
     *
     * @param winParam Window parameters.
     *
     */
    void MakeWindow(const WindowParameters &winParam);

    /**
     * Set this window to fullscreen.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-07-12
     * @since 0.4
     *
     */
    void SetFullscreen();
    /**
     * Set this window back to window mode if its in fullscreen.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-07-12
     * @since 0.4
     *
     */
    void SetWindowMode();

     /**
     * Get current window drawable width.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-01-03
     * @since 0.4
     *
     */
    int GetWidth();
     /**
     * Get current window drawable height.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-01-03
     * @since 0.4
     *
     */
    int GetHeight();

     /**
     * Get window event. If event queue is empty, the output buffer is 
     * flushed and getEvent is blocked until an event is received.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-07-12
     * @since 0.4
     *
     * @note Needs to return the Event.
     */
    WindowEvents* GetNextEvent() const;
     /**
     * Get the number of pending events.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-07-12
     * @since 0.4
     *
     * @return The number of events that have been received  but have 
     * not been removed from the event queue.
     */
    int GetPendingEventsCount() const;

     /**
     * Swap buffers if using double buffer.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-07-12
     * @since 0.4
     *
     */
    virtual void SwapBuffers() const;

  private:    
    HINSTANCE moduleHandle;

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

    friend LRESULT CALLBACK ProcessWindowMessages(HWND windowHandle, UINT uMsg, 
      WPARAM wParam, LPARAM lParam);
};

/**
 * Process messages sent to the window.
 *
 * @author Ricardo Tiago <rtiago.mendes@gmail.com>
 * @date 2011-08-16
 * @since 0.4
 *
 * @param [in] windowHandle A handle to the window.
 * @param [in] uMsg The message.
 * @param [in] wParam Additional message information.
 * @param [in] lParam Additional message information.
 *
 * @return The result of the message processing and depends on the message sent.
 */
LRESULT CALLBACK ProcessWindowMessages(HWND windowHandle, UINT uMsg, 
  WPARAM wParam, LPARAM lParam);

}
}
}
#endif
