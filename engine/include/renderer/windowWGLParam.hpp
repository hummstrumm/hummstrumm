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
 * Definition for Microsoft Windows OpenGL window parameters.
 *
 * @file    windowWGLParam.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-09-25
 */

#ifndef HUMMSTRUMM_ENGINE_WINDOW_WGL_PARAMETERS
#define HUMMSTRUMM_ENGINE_WINDOW_WGL_PARAMETERS

namespace hummstrumm
{
namespace engine
{
namespace renderer
{

struct WindowWGLParam: public WindowParameters
{
  WindowWGLParam() {}

  WindowWGLParam(const WindowWGLParam &param): WindowParameters(param) {}

  virtual ~WindowWGLParam() {}

  inline virtual HUMMSTRUMM_WINDOW_LIST_POINTER WindowParamList() const
  {
    return NULL;
  }
};

}
}
}

#endif
