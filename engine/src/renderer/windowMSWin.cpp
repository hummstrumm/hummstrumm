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

#define HUMMSTRUMM_ENGINE_SOURCE

#include "hummstrummengine.hpp"

namespace hummstrumm
{
namespace engine
{
namespace renderer
{

using hummstrumm::engine::events::StructureEvents;

WindowMSWin::WindowMSWin()
{

}

WindowMSWin::~WindowMSWin()
{

}

void
WindowMSWin::DestroyWindow()
{

}

void
WindowMSWin::MakeWindow(const WindowParameters &winParam)
{

  HWND windowHandle;

  DWORD windowStyleEx = WS_EX_APPWINDOW;
  DWORD windowStyle = WS_POPUP;

  windowHandle = CreateWindowEx(windowStyleEx,
                                NULL,
                                winParam.GetWindowName().c_str(),
                                windowStyle,
                                winParam.GetPositionX(),
                                winParam.GetPositionY(),
                                winParam.GetWidth(),
                                winParam.GetHeight(),
                                NULL,
                                NULL,
                                hInstance,
                                NULL);
  if (windowHandle == NULL)
    HUMMSTRUMM_THROW (Generic,"Add a meaningful message with GetLastError");

}

void
WindowMSWin::SetFullscreen()
{

}

void
WindowMSWin::SetWindowMode()
{ 

}

int WindowMSWin::GetHeight()
{
  return 0;
}

int WindowMSWin::GetWidth()
{
  return 0;
}

WindowEvents*
WindowMSWin::GetNextEvent() const
{
  return NULL;
}

int
WindowMSWin::GetPendingEventsCount() const
{
  return 0;
}

void
WindowMSWin::SwapBuffers() const
{

}

}
}
}

