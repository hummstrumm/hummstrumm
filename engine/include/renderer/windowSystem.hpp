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
 * Defines the window system abstract class.
 * This class cannot be instantiated and will be implemented by specific
 * windows systems.
 *
 * @file    renderer/windowSystem.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-07-24
 */

#ifndef HUMMSTRUMM_ENGINE_WINDOW_SYSTEM
#define HUMMSTRUMM_ENGINE_WINDOW_SYSTEM

namespace hummstrumm
{
namespace engine
{
namespace renderer
{

class WindowSystem
{
  public:
    /**
     * Window system constructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     */
    WindowSystem() {}

    /**
     * Window system destructor.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     */
    virtual ~WindowSystem() {}

    /**
     * Destroy a window.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     */
    virtual void DestroyWindow() = 0;

    /**
     * Create a window.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     *@param winParam Window parameters.
     *
     */
    virtual void CreateWindow(const WindowParameters &winParam) = 0;
    /**
     * Set the window to fullscreen.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     */
    virtual void SetFullscreen() = 0;

    /**
     * Set the window back to window mode if its in fullscreen.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     */
    virtual void SetWindowMode() = 0;

     /**
     * Get the window drawable width.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     */
    virtual int GetWidth() = 0;

     /**
     * Get the window drawable height.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-07-24
     * @since 0.3
     *
     */
    virtual int GetHeight() = 0;

};


}
}
}
#endif
