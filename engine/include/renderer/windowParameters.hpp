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
 * Common window parameters interface for the GLX and WGL windows.
 *
 * @file    renderer/windowParameters.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-07-24
 */

#ifndef HUMMSTRUMM_ENGINE_WINDOW_PARAMETERS
#define HUMMSTRUMM_ENGINE_WINDOW_PARAMETERS

//#include <GL/glx.h>

namespace hummstrumm
{
namespace engine
{
namespace renderer
{

/**
 * Common window parameters to be used with hummstrumm window system when 
 * creating a GLX or WGL window.
 *
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-09-28
 * @since 0.3
 */

#ifdef HUMMSTRUMM_PLATFORM_WINDOW
#define HUMMSTRUMM_WINDOW_LIST_POINTER PIXELFORMATDESCRIPTOR
#else
#define HUMMSTRUMM_WINDOW_LIST_POINTER int*
#endif

struct WindowParameters
{

  /**
   * Initializes the parameters to a default configuration values.
   *
   * @author Ricardo Tiago <Rtiago@gmail.com>
   * @date 2010-09-28
   * @since 0.3
   */
  WindowParameters(): name("HUMMSTRUMM Engine Window"),
                      positionX(0),
                      positionY(0),
                      height(512), 
                      width(512),
                      fullscreen(false) {}

  /**
   * Construct a WindowParameters object from another WindowParameters object.
   *
   * @author Ricardo Tiago <Rtiago@gmail.com>
   * @date 2010-09-28
   * @since 0.3
   */
  WindowParameters(const WindowParameters &param): name(param.name),
                                                   positionX(param.positionX),
                                                   positionY(param.positionY),
                                                   height(param.height),
                                                   width(param.width),
                                                   fullscreen(param.fullscreen) {}

  /**
   * Destructs a WindowParameters object.
   *
   * @author Ricardo Tiago <Rtiago@gmail.com>
   * @date 2010-09-28
   * @since 0.3
   */
  virtual ~WindowParameters() {}

  /**
   * Gets a pointer of type HUMMSTRUMM_WINDOW_LIST_POINTER to the window parameters.
   *
   * @author Ricardo Tiago <Rtiago@gmail.com>
   * @date 2010-09-28
   * @since 0.3
   *
   * @return A pointer to an array of window parameters else NULL in case of an error.
   * @note The caller is responsible for freeing the pointer.
   */
  virtual HUMMSTRUMM_WINDOW_LIST_POINTER WindowParamList() const = 0;

  // Set the window caption name.
  std::string name;
  // Set the window position in X.
  unsigned int positionX;
  // Set the window position in Y.
  unsigned int positionY;
  // Set the window height.
  unsigned int height;
  // Set the window width.
  unsigned int width;
  // Specificies if the window should cover the whole screen or not.
  bool fullscreen;
};

}
}
}
#endif
