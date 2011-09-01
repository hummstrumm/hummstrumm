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
#include <sstream>

namespace hummstrumm
{
namespace engine
{
namespace window
{

using hummstrumm::engine::events::StructureEvents;

HsWindowSystem::HsWindowSystem()
{
  DWORD error;
  // Passing NULL retrieves a handle to the file used to create the calling process.
  moduleHandle = GetModuleHandle(NULL);
  if (moduleHandle == NULL)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("GetModuleHandle: ",error);
    HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }

  InitializeWGLExtensions();
}

HsWindowSystem::~HsWindowSystem()
{
  HsDestroyWindow();
}

void
HsWindowSystem::HsDestroyWindow()
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
      deviceContext = NULL;
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("ReleaseDC: ",error);
      HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  } 

  BOOL windowDestroyed = DestroyWindow(windowHandle);
  if (!windowDestroyed)
  {
      windowHandle = NULL;
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("DestroyWindow: ",error);
      HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }

  BOOL classUnregistered = UnregisterClass("HummstrummWindow",moduleHandle);
  if (!classUnregistered)
  {
      moduleHandle = NULL; 
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("UnregisteredClass: ",error);
      HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }

}

void
HsWindowSystem::HsCreateWindow(WindowVisualInfo &winVisual)
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
  wndAttributes.hIcon = LoadIcon (NULL,IDI_WINLOGO);
  wndAttributes.hCursor = LoadCursor (NULL,IDC_ARROW);
  wndAttributes.hbrBackground = NULL;
  wndAttributes.lpszMenuName = NULL;
  wndAttributes.lpszClassName = "HummstrummWindow";

  classAtom = RegisterClass (&wndAttributes);
  if (classAtom == NULL)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage ("RegisterClass: ",error);
    HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }

  windowRect.left = (long) winVisual.positionX;
  windowRect.right = (long) winVisual.width;
  windowRect.top = (long) winVisual.positionY; 
  windowRect.bottom = (long) winVisual.height;

  AdjustWindowRectEx(&windowRect, windowStyle, FALSE, windowStyleEx);

  windowHandle = CreateWindowEx(windowStyleEx,
                                "HummstrummWindow",
                                winVisual.name.c_str(),
                                WS_CLIPSIBLINGS | WS_CLIPCHILDREN | windowStyle,
                                winVisual.positionX,
                                winVisual.positionY,
                                winVisual.width,
                                winVisual.height,
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

  deviceContext = GetDC(windowHandle);

  if (deviceContext == NULL)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("GetDC: ", error);
    HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }

  const int* descriptor = winVisual.GetWindowDescriptor();
  int pixelFormat;
  PIXELFORMATDESCRIPTOR pfd;
  if (wglChoosePixelFormatARB != NULL) 
  { 
    UINT matchedFormats;
    BOOL ret = wglChoosePixelFormatARB(deviceContext, descriptor, NULL, 1 , &pixelFormat, &matchedFormats);
    if (!ret)
    {
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("wglChoosePixelFormat: ",error);
      HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
    }

    if (matchedFormats == 0)
    {
      HUMMSTRUMM_THROW (WindowSystem, "No suitable pixel formats have been found");
    }
  }
  else
  {
    DWORD flags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED;
    if (winVisual.isDoubleBuffer) flags = flags | PFD_DOUBLEBUFFER;
    if (winVisual.isStereo) flags = flags | PFD_STEREO;
    if (winVisual.depthSize == 0) flags = flags | PFD_DEPTH_DONTCARE;
    pfd.nSize           =  sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion        =  1;
    pfd.dwFlags         =  flags;
    pfd.iPixelType      =  (BYTE) winVisual.renderType;
    pfd.cColorBits      =  (BYTE) winVisual.bufferSize;
    pfd.cRedBits        =  (BYTE) winVisual.redSize;
    pfd.cRedShift       =  0;
    pfd.cGreenBits      =  (BYTE) winVisual.greenSize;
    pfd.cGreenShift     =  0;
    pfd.cBlueBits       =  (BYTE) winVisual.blueSize;
    pfd.cBlueShift      =  0;
    pfd.cAlphaBits      =  (BYTE) winVisual.alphaSize;
    pfd.cAlphaShift     =  0;
    pfd.cAccumBits      =  (BYTE) (winVisual.accumRedSize + 
                                  winVisual.accumGreenSize + 
                                  winVisual.accumBlueSize + 
                                  winVisual.accumAlphaSize);
    pfd.cAccumRedBits   =  (BYTE) winVisual.accumRedSize;
    pfd.cAccumGreenBits =  (BYTE) winVisual.accumGreenSize;
    pfd.cAccumBlueBits  =  (BYTE) winVisual.accumBlueSize;
    pfd.cDepthBits      =  (BYTE) winVisual.depthSize;
    pfd.cStencilBits    =  (BYTE) winVisual.stencilSize;
    pfd.cAuxBuffers     =  (BYTE) winVisual.auxBuffers;
    pfd.iLayerType      =  PFD_MAIN_PLANE;
    pfd.bReserved       =  0;
    pfd.dwLayerMask     =  0;
    pfd.dwVisibleMask   =  0;
    pfd.dwDamageMask    =  0;

    pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
    if (pixelFormat == 0)
    {
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("ChoosePixelFormat: ",error);
      HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
    }
  }

  BOOL isPixelFormatSet = SetPixelFormat(deviceContext, pixelFormat, &pfd);
  if (!isPixelFormatSet)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("SetPixelFormat: ",error);
    HUMMSTRUMM_THROW (WindowSystem, errMsg.c_str());
  }

  if (wglSwapIntervalEXT != NULL)
  {
    wglSwapIntervalEXT (winVisual.verticalSync);
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
HsWindowSystem::InitializeWGLExtensions()
{
  /* This method deserves a quick explanation. The objective is to get
   * the address of WGL functions and to do that we need to create a 
   * false context. 
   *
   * See the quote below from OpenGL.org, its quite elucidating.
   *
   * " The key problem is this: the function you use to get WGL extensions is, 
   * itself, an OpenGL extension. Thus like any OpenGL function, it requires an 
   * OpenGL context to call it. So in order to get the functions we need to create 
   * a context, we have to... create a context. "
   *
   */
  PIXELFORMATDESCRIPTOR pfd;
  int pixelFormat = 0;
  std::stringstream message;

  DWORD flags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED;
  pfd.nSize           =  sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion        =  1;
  pfd.dwFlags         =  flags;
  pfd.iPixelType      =  PFD_TYPE_RGBA;
  pfd.cColorBits      =  0;
  pfd.cRedBits        =  0;
  pfd.cRedShift       =  0;
  pfd.cGreenBits      =  0;
  pfd.cGreenShift     =  0;
  pfd.cBlueBits       =  0;
  pfd.cBlueShift      =  0;
  pfd.cAlphaBits      =  0;
  pfd.cAlphaShift     =  0;
  pfd.cAccumBits      =  0;
  pfd.cAccumRedBits   =  0;
  pfd.cAccumGreenBits =  0;
  pfd.cAccumBlueBits  =  0;
  pfd.cDepthBits      =  0;
  pfd.cStencilBits    =  0;
  pfd.cAuxBuffers     =  0;
  pfd.iLayerType      =  0;
  pfd.bReserved       =  0;
  pfd.dwLayerMask     =  0;
  pfd.dwVisibleMask   =  0;
  pfd.dwDamageMask    =  0;

  deviceContext = GetDC (NULL);
  pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
  windowHandle = CreateWindowEx(WS_EX_APPWINDOW,
                                "Static",
                                "Temporary Window",
                                WS_POPUP,
                                0, 0, 64, 64,
                                NULL,
                                NULL,
                                NULL,
                                NULL);
  deviceContext = GetDC (windowHandle);
  SetPixelFormat(deviceContext, pixelFormat, &pfd);
  renderingContext = wglCreateContext(deviceContext);
  wglMakeCurrent (deviceContext, renderingContext);

  wglSwapIntervalEXT            = (PFNWGLSWAPINTERVALEXTPROC) 
                                  wglGetProcAddress("wglSwapIntervalEXT");
  wglGetSwapIntervalEXT         = (PFNWGLGETSWAPINTERVALEXTPROC) 
                                  wglGetProcAddress("wglGetSwapIntervalEXT");
  wglChoosePixelFormatARB       = (PFNWGLCHOOSEPIXELFORMATARBPROC) 
                                  wglGetProcAddress("wglChoosePixelFormatARB");
  wglMakeContextCurrentARB      = (PFNWGLMAKECONTEXTCURRENTARBPROC) 
                                  wglGetProcAddress("wglMakeContextCurrentARB");
  wglCreateContextAttribsARB    = (PFNWGLCREATECONTEXTATTRIBSARBPROC) 
                                  wglGetProcAddress("wglCreateContextAttribsARB");

  PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
  PFNWGLGETEXTENSIONSSTRINGEXTPROC wglGetExtensionsStringEXT;

  wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)
      wglGetProcAddress("wglGetExtensionsStringARB");

  if (wglGetExtensionsStringARB != NULL)
  {
    const char * extensionsARB = wglGetExtensionsStringARB(deviceContext);
    message.str("");
    message << "Supported WGL ARB Extensions : ";
    message << extensionsARB;
    HUMMSTRUMM_LOG(message.str().c_str(), MESSAGE);
  }

  wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)
      wglGetProcAddress("wglGetExtensionsStringEXT");

  if (wglGetExtensionsStringEXT != NULL)
  {
    const char * extensionsEXT = wglGetExtensionsStringEXT();
    message.str("");
    message << "Supported WGL EXT Extensions : ";
    message << extensionsEXT;
    HUMMSTRUMM_LOG(message.str().c_str(), MESSAGE);
  }

  wglMakeCurrent (NULL,NULL);
  wglDeleteContext (renderingContext);
  ReleaseDC (windowHandle, deviceContext);
  DestroyWindow (windowHandle); 
}

hummstrumm::engine::events::WindowEvents*
HsWindowSystem::GetNextEvent()
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
        return new StructureEvents(hummstrumm::engine::events::WindowEvents::WINDOW_RESIZE, LOWORD(eMsg.lparam),HIWORD(eMsg.lparam));
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
      return new StructureEvents(hummstrumm::engine::events::WindowEvents::WINDOW_CLOSE);
    }

    default:
    {       
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    break;
  }    
  
  return new hummstrumm::engine::events::WindowEvents();
}

void
HsWindowSystem::PostEventMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
  EventMsg *pMsg = new EventMsg;
  pMsg->msg = msg;
  pMsg->wparam = wParam;
  pMsg->lparam = lParam;
  msgQueue.push(*pMsg);
}

int
HsWindowSystem::GetPendingEventsCount() const
{
  DWORD queueStatus = GetQueueStatus(QS_ALLINPUT);
  // The high-order word of the return value indicates the types of 
  // messages currently in the queue.
  return HIWORD(queueStatus) + msgQueue.size();
}

hummstrumm::engine::types::String
HsWindowSystem::GetErrorMessage(hummstrumm::engine::types::String premsg, DWORD code)
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
HsWindowSystem::ProcessWindowMessages(HWND hWnd, UINT uMsg, 
  WPARAM wParam, LPARAM lParam)
{

 HsWindowSystem *pWin;

  switch (uMsg)
  {

    case WM_CREATE:
    {
        CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pWin = reinterpret_cast<HsWindowSystem*>(pCreate->lpCreateParams);
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
      pWin = reinterpret_cast<HsWindowSystem*>(ptr);
      // I could probably avoid having to do this only if I was able
      // to post a message to the thread message queue. Well, I'm 
      // capable of posting a message but this message is only received
      // once when the window starts! WHY??! I don't know. 
      // PostQuitMessage does exactly what I want but without the source 
      // code of it I can't figure it out and Google didn't help much.
      // 
      // Until I can find an alternative we have to stick to the internal queue 
      // to pass messages around. The alternative would be to redesign the event
      // system to be more Microsoft Windows friendly. Something to think about it.
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

