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
WindowMSWin::DisposeWindow()
{
  DWORD error;

  if (renderingContext)
  {
    BOOL noLongerCurrent = wglMakeCurrent(deviceContext,NULL);
    if (!noLongerCurrent)
    {
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("wglMakeCurrent: ",error);
      HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
    }
    BOOL ctxDeleted = wglDeleteContext(renderingContext);
    if (!ctxDeleted)
    {
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("wglDeleteContext: ",error);
      HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
    }  
    renderingContext = NULL; 
  }

  int wasReleased = ReleaseDC(windowHandle,deviceContext);
  if (wasReleased == 0)
  {
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("ReleaseDC: ",error);
      HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
      deviceContext = NULL;
  } 

  BOOL windowDestroyed = DestroyWindow(windowHandle);
  if (!windowDestroyed)
  {
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("DestroyWindow: ",error);
      HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
      windowHandle = NULL; 
  }

  BOOL classUnregistered = UnregisterClass("HummstrummWindow",moduleHandle);
  if (!classUnregistered)
  {
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("UnregisteredClass: ",error);
      HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
      moduleHandle = NULL; 
  }

}

void
WindowMSWin::MakeWindow(const WindowParameters &winParam)
{
  WNDCLASS wndAttributes;

  ATOM classAtom;
  DWORD windowStyleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
  DWORD windowStyle = WS_OVERLAPPEDWINDOW;
  DWORD error;
  RECT windowRect;

  wndAttributes.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wndAttributes.lpfnWndProc = (WNDPROC) ProcessWindowMessages;
  wndAttributes.cbClsExtra = 0;
  wndAttributes.cbWndExtra = 0;
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
                                this);

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
WindowMSWin::GetNextEvent()
{
  MSG msg = { };

  if (msgQueue.size() > 0)
  {
    EventMsg eMsg = EventMsg();
    eMsg = msgQueue.front();
    switch (eMsg.msg)
    {
      case WM_SIZE:
      {
        msgQueue.pop();
        return new StructureEvents(WindowEvents::WINDOW_RESIZE,LOWORD(eMsg.lparam),
          HIWORD(eMsg.lparam));
      }
      break;

      default:
        msgQueue.pop();
        break;
    }
  }

  PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
  switch (msg.message)
  {
    case WM_QUIT:
    {
      return new StructureEvents(WindowEvents::WINDOW_CLOSE);
    }

    default:
    {       
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    break;
  }    

  return new WindowEvents();
}

int
WindowMSWin::GetPendingEventsCount() const
{
  DWORD queueStatus = GetQueueStatus(QS_ALLINPUT);
  // The high-order word of the return value indicates the types of 
  // messages currently in the queue.
  return HIWORD(queueStatus) + msgQueue.size();
}

void
WindowMSWin::ExchangeBuffers() const
{
  SwapBuffers(deviceContext);
}

void 
WindowMSWin::PostEventMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
  EventMsg *pMsg = new EventMsg;
  pMsg->msg = msg;
  pMsg->wparam = wParam;
  pMsg->lparam = lParam;
  msgQueue.push(*pMsg);
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
WindowMSWin::ProcessWindowMessages(HWND hWnd, UINT uMsg, 
  WPARAM wParam, LPARAM lParam)
{

 WindowMSWin *pWin;

  switch (uMsg)
  {

    case WM_CREATE:
    {
        CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pWin = reinterpret_cast<WindowMSWin*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWin);
    }

    case WM_ACTIVATE:
    {
      return 0;
    }

    case WM_SYSCOMMAND:
    {
      switch (wParam)
      {
        case SC_SCREENSAVE:
        case SC_MONITORPOWER:
        return 0;
      }
      break;
    }

    case WM_CLOSE:
    {
      PostQuitMessage(0);
      return 0;
    }

    case WM_KEYUP:
    {
      return 0;
    }

    case WM_SIZE:
    {
      LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
      pWin = reinterpret_cast<WindowMSWin*>(ptr);
      // I could probably avoid having to do this only if I was able
      // to post a message to the thread message queue. Well, I'm 
      // capable of posting a message but this message is only received
      // once when the window starts! WHY??! I don't know. 
      // PostQuitMessage does exactly what I want but without the source 
      // code of it I can't figure it out and Google didn't help much.
      // 
      // Until I can find an alternative we have to stick to the internal queue 
      // to pass messages around. The alternative would be to redesign the event
      // system to be more Microsoft Windows friendly.
      //
      // References:
      // http://msdn.microsoft.com/en-us/library/ff381400%28v=VS.85%29.aspx
      pWin->PostEventMessage(WM_SIZE, wParam, lParam);
      return 0;
    }

  }

  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

}
}
}

