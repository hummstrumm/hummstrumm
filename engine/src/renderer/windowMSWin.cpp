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
#include <AtlBase.h>

namespace hummstrumm
{
namespace engine
{
namespace renderer
{

using hummstrumm::engine::events::StructureEvents;

WindowMSWin::WindowMSWin()
{
  DWORD error;

  // Passing NULL retrieves a handle to the file used to create 
  // the calling process.
  moduleHandle = GetModuleHandle(NULL);
  if (moduleHandle == NULL)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("GetModuleHandle: ",error);
    HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }
 
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
  WNDCLASS wndAttributes;
  HWND windowHandle;
  HDC deviceContext;
  HGLRC renderingContext;

  ATOM classAtom;
  DWORD windowStyleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
  DWORD windowStyle = WS_OVERLAPPEDWINDOW;
  DWORD error;
  RECT windowRect;

  wndAttributes.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wndAttributes.lpfnWndProc = (WNDPROC) ProcessWindowMessages;
  wndAttributes.cbClsExtra = 0;
  wndAttributes.hInstance = moduleHandle;
  wndAttributes.hIcon = LoadIcon(NULL,IDI_WINLOGO);
  wndAttributes.hCursor = LoadCursor(NULL,IDC_ARROW);
  wndAttributes.hbrBackground = NULL;
  wndAttributes.lpszMenuName = NULL;
  wndAttributes.lpszClassName = "HummstrummWindow";

  // TODO: Superseded by RegisterClassEx
  classAtom = RegisterClass(&wndAttributes);
  if (classAtom == NULL)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("RegisterClass: ",error);
    HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }

  windowRect.left = (long) winParam.GetPositionX();
  windowRect.right = (long) winParam.GetWidth();
  windowRect.top = (long) winParam.GetPositionY(); 
  windowRect.bottom = (long) winParam.GetHeight();

  AdjustWindowRectEx(&windowRect, windowStyle, FALSE, windowStyleEx);

  windowHandle = CreateWindowEx(windowStyleEx,
                                "HummstrummWindow",
                                winParam.GetWindowName().c_str(),
                                WS_CLIPSIBLINGS | WS_CLIPCHILDREN | windowStyle,
                                winParam.GetPositionX(),
                                winParam.GetPositionY(),
                                winParam.GetWidth(),
                                winParam.GetHeight(),
                                NULL,
                                NULL,
                                moduleHandle,
                                NULL);

  if (windowHandle == NULL)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("CreateWindowEx: ",error);
    HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }


  PIXELFORMATDESCRIPTOR pfd = winParam.WindowParamList();

  deviceContext = GetDC(windowHandle);

  if (deviceContext == NULL)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("GetDC: ", error);
    HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }

  int pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
  if (pixelFormat == 0)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("ChoosePixelFormat: ",error);
    HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }

  BOOL isPixelFormatSet = SetPixelFormat(deviceContext, pixelFormat, &pfd);
  if (!isPixelFormatSet)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("SetPixelFormat: ",error);
    HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }

  renderingContext = wglCreateContext(deviceContext);
  if (renderingContext == NULL)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("wglCreateContext: ",error);
    HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }

  BOOL isCurrent = wglMakeCurrent(deviceContext, renderingContext);
  if (!isCurrent)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("wglMakeCurrent: ",error);
    HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }
 
  ShowWindow(windowHandle,SW_SHOW);
  SetForegroundWindow(windowHandle);
  SetFocus(windowHandle); 
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

hummstrumm::engine::types::String
WindowMSWin::GetErrorMessage(hummstrumm::engine::types::String premsg, DWORD code)
{
  LPVOID lpMsgBuf;

  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM  |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                code,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR) &lpMsgBuf,
                0,
                NULL);

  MessageBox(NULL, (LPCTSTR)lpMsgBuf, TEXT("HUMMSTRUMM"), MB_OK);

  std::string msg(premsg + (LPTSTR) lpMsgBuf); 
  LocalFree(lpMsgBuf);
  return msg;
}

LRESULT CALLBACK
ProcessWindowMessages(HWND windowHandle, UINT uMsg, 
  WPARAM wParam, LPARAM lParam)
{
  return DefWindowProc(windowHandle, uMsg, wParam, lParam);
}

}
}
}

