// -*- mode: c++; c-file-style: hummstrumm -*-
/* Humm and Strumm Engine
 * Copyright (C) 2008-2012, the people listed in the AUTHORS file.
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

#include "hummstrummengine.hpp"

#include <strsafe.h>

using namespace hummstrumm::engine;

namespace hummstrumm
{
namespace engine
{
namespace window
{

WindowSystem::WindowSystem()
{
  DWORD error;

  // Passing NULL retrieves a handle to the file used to create the calling process.
  moduleHandle = GetModuleHandle(NULL);
  if (moduleHandle == NULL)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("GetModuleHandle: ",error);
    throw std::runtime_error (errMsg.c_str ());
  }
  InitializeWGLExtensions();
}

WindowSystem::~WindowSystem()
{
  DestroyWindow();
}

void
WindowSystem::DestroyWindow()
{
  DWORD error;

  ChangeDisplaySettings(NULL,0);

  if (renderingContext)
  {
    BOOL noLongerCurrent = wglMakeCurrent(deviceContext,NULL);
    if (!noLongerCurrent)
    {
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("wglMakeCurrent: ",error);
      core::Engine::GetEngine ()->GetLog ()
        << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::warning)
        << errMsg << std::flush;
    }
    BOOL ctxDeleted = wglDeleteContext(renderingContext);
    if (!ctxDeleted)
    {
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("wglDeleteContext: ",error);
      core::Engine::GetEngine ()->GetLog ()
        << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::warning)
        << errMsg << std::flush;
    }  
    renderingContext = NULL; 
  }

  int wasReleased = ReleaseDC(windowHandle,deviceContext);
  if (wasReleased == 0)
  {
      deviceContext = NULL;
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("ReleaseDC: ",error);
      core::Engine::GetEngine ()->GetLog ()
        << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::warning)
        << errMsg << std::flush;
  } 

  BOOL windowDestroyed = ::DestroyWindow(windowHandle);
  if (!windowDestroyed)
  {
      windowHandle = NULL;
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("DestroyWindow: ",error);
      core::Engine::GetEngine ()->GetLog ()
        << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::warning)
        << errMsg << std::flush;
  }

  BOOL classUnregistered = UnregisterClass("HummstrummWindow",moduleHandle);
  if (!classUnregistered)
  {
      moduleHandle = NULL; 
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("UnregisteredClass: ",error);
      core::Engine::GetEngine ()->GetLog ()
        << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::warning)
        << errMsg << std::flush;
  }

}

void
(WindowSystem::CreateWindow)(WindowVisualInfo &windowParameters)
{
  WNDCLASS wndAttributes;

  ATOM classAtom;
  DWORD windowStyleEx;
  DWORD windowStyle;
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
    throw std::runtime_error (errMsg.c_str ());
  }
  SetMode(windowParameters);
  if (windowParameters.useFullscreen)
  {
    windowStyleEx = WS_EX_APPWINDOW;
    windowStyle = WS_POPUP;
  }
  else
  {
    windowStyleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    windowStyle = WS_OVERLAPPEDWINDOW;
  }
 
  windowRect.left = (long) windowParameters.positionX;
  windowRect.right = (long) windowParameters.width;
  windowRect.top = (long) windowParameters.positionY; 
  windowRect.bottom = (long) windowParameters.height;

  AdjustWindowRectEx(&windowRect, windowStyle, FALSE, windowStyleEx);

  windowHandle = CreateWindowEx(windowStyleEx,
                                "HummstrummWindow",
                                windowParameters.name.c_str(),
                                WS_CLIPSIBLINGS | WS_CLIPCHILDREN | windowStyle,
                                windowParameters.positionX,
                                windowParameters.positionY,
                                windowParameters.width,
                                windowParameters.height,
                                NULL,
                                NULL,
                                moduleHandle,
                                this);

  if (windowHandle == NULL)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("CreateWindowEx: ",error);
    throw std::runtime_error (errMsg.c_str ());
  }

  deviceContext = GetDC(windowHandle);

  if (deviceContext == NULL)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("GetDC: ", error);
    throw std::runtime_error (errMsg.c_str ());
  }

  int pixelFormat;
  PIXELFORMATDESCRIPTOR pfd;
  if (wglChoosePixelFormatARB != NULL && wglGetPixelFormatAttribivARB != NULL) 
  { 
    UINT matchedFormats;
    const int* descriptor = windowParameters.GetPixelFormatAttributes(false);
    BOOL ret = wglChoosePixelFormatARB(deviceContext, descriptor, NULL, 1 , &pixelFormat, &matchedFormats);
    if (!ret)
    {
      throw std::runtime_error ("Couldn't find a suitable pixel format that "
                                "matched the requested parameters.");
    }

    if (matchedFormats == 0)
    {
      throw std::runtime_error ("No suitable pixel formats have been found.");
    }

    const int* attrib;
    int attribSize = 0;
    attrib = windowParameters.GetQueryAttributes (attribSize);
    int* values = new int[attribSize];
    wglGetPixelFormatAttribivARB(deviceContext, pixelFormat, 0, attribSize, attrib, values);
   
    windowParameters.useDoubleBuffer = values[0] != 0;
    windowParameters.useStereo = values[1] != 0;
    windowParameters.auxBuffers = values[2];
    windowParameters.redSize = values[3];
    windowParameters.greenSize = values[4];
    windowParameters.blueSize = values[5];
    windowParameters.alphaSize = values[6];
    windowParameters.accumRedSize = values[9];
    windowParameters.accumGreenSize = values[10];
    windowParameters.accumBlueSize = values[11];
    windowParameters.accumAlphaSize = values[12];
    windowParameters.depthSize = values[7];
    windowParameters.stencilSize = values[8];
    if (windowParameters.useAntiAliasing)
      windowParameters.samples = values[14]; 

  }
  else
  {
    DWORD flags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED;
    if (windowParameters.useDoubleBuffer) flags = flags | PFD_DOUBLEBUFFER;
    if (windowParameters.useStereo) flags = flags | PFD_STEREO;
    if (windowParameters.depthSize == 0) flags = flags | PFD_DEPTH_DONTCARE;
    pfd.nSize           =  sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion        =  1;
    pfd.dwFlags         =  flags;
    pfd.iPixelType      =  (BYTE) windowParameters.renderType;
    pfd.cColorBits      =  (BYTE) windowParameters.bufferSize;
    pfd.cRedBits        =  (BYTE) windowParameters.redSize;
    pfd.cRedShift       =  0;
    pfd.cGreenBits      =  (BYTE) windowParameters.greenSize;
    pfd.cGreenShift     =  0;
    pfd.cBlueBits       =  (BYTE) windowParameters.blueSize;
    pfd.cBlueShift      =  0;
    pfd.cAlphaBits      =  (BYTE) windowParameters.alphaSize;
    pfd.cAlphaShift     =  0;
    pfd.cAccumBits      =  (BYTE) (windowParameters.accumRedSize + 
                                   windowParameters.accumGreenSize + 
                                   windowParameters.accumBlueSize + 
                                   windowParameters.accumAlphaSize);
    pfd.cAccumRedBits   =  (BYTE) windowParameters.accumRedSize;
    pfd.cAccumGreenBits =  (BYTE) windowParameters.accumGreenSize;
    pfd.cAccumBlueBits  =  (BYTE) windowParameters.accumBlueSize;
    pfd.cDepthBits      =  (BYTE) windowParameters.depthSize;
    pfd.cStencilBits    =  (BYTE) windowParameters.stencilSize;
    pfd.cAuxBuffers     =  (BYTE) windowParameters.auxBuffers;
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
      throw std::runtime_error (errMsg.c_str());
    }

    int ret = DescribePixelFormat(deviceContext, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    if (ret == 0)
    {
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("DescribePixelFormat: ",error);
      throw std::runtime_error (errMsg.c_str ());
    }
    
    windowParameters.renderType = pfd.iPixelType;
    windowParameters.bufferSize = pfd.cColorBits;
    windowParameters.redSize = pfd.cRedBits;
    windowParameters.greenSize = pfd.cGreenBits;
    windowParameters.blueSize = pfd.cBlueBits;
    windowParameters.alphaSize = pfd.cAlphaBits;
    windowParameters.accumRedSize = pfd.cAccumRedBits;
    windowParameters.accumGreenSize = pfd.cAccumGreenBits;
    windowParameters.accumBlueSize = pfd.cAccumBlueBits;
    windowParameters.depthSize = pfd.cDepthBits;
    windowParameters.stencilSize = pfd.cStencilBits;
    windowParameters.auxBuffers = pfd.cAuxBuffers;
    windowParameters.samples = 0; 
  }

  BOOL isPixelFormatSet = SetPixelFormat(deviceContext, pixelFormat, &pfd);
  if (!isPixelFormatSet)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("SetPixelFormat: ",error);
    throw std::runtime_error (errMsg.c_str ());
  }

  if (wglCreateContextAttribsARB != NULL)
  {
    const int* ctxAttribs = windowParameters.GetContextAttributes();
    renderingContext = wglCreateContextAttribsARB(deviceContext, 0, ctxAttribs); 
    if (renderingContext == NULL)
    {
      DWORD error = GetLastError();
      hummstrumm::engine::types::String errMsg;
      switch (error)
      {
        case ERROR_INVALID_VERSION_ARB:
          errMsg = "Requested OpenGL context version is not supported";
          break;
        case ERROR_INVALID_PROFILE_ARB:
          errMsg = "Requested OpenGL context profile is not support or invalid";
          break;
        default:
          errMsg = GetErrorMessage("wglCreateContextAttribsARB: ",error);
          break;         
      }
      throw std::runtime_error (errMsg.c_str ());
    }  
  }
  else
  {
    renderingContext = wglCreateContext(deviceContext);
    if (renderingContext == NULL)
    {
      error = GetLastError();
      hummstrumm::engine::types::String errMsg = GetErrorMessage("wglCreateContext: ",error);
      throw std::runtime_error (errMsg.c_str ());
    }
  }

  BOOL isCurrent = wglMakeCurrent(deviceContext, renderingContext);
  if (!isCurrent)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("wglMakeCurrent: ",error);
    throw std::runtime_error (errMsg.c_str ());
  }

  if (wglSwapIntervalEXT != NULL)
  {
    BOOL ret = wglSwapIntervalEXT (windowParameters.useVerticalSync);
    if (!ret)
    {
      DWORD error = GetLastError();
      hummstrumm::engine::types::String errMsg;
      switch (error)
      {
        case ERROR_INVALID_DATA:
          errMsg = "The requested interval parameter is negative";
          break;
        case ERROR_DC_NOT_FOUND:
          errMsg = "No device context could be obtained";
          break;
        default:
          errMsg = GetErrorMessage("wglSwapIntervalEXT: ",error);
          break;         
      }
      throw std::runtime_error (errMsg.c_str ());
    }
  }

  ShowWindow(windowHandle,SW_SHOW);
  SetForegroundWindow(windowHandle);
  SetFocus(windowHandle); 
}

void
WindowSystem::SwapBuffers()
{
  DWORD error;
  BOOL ret = ::SwapBuffers(deviceContext);
  if (!ret)
  {
    error = GetLastError();
    hummstrumm::engine::types::String errMsg = GetErrorMessage("SwapBuffers: ",error);
    throw std::runtime_error (errMsg.c_str ());
  }
}

void
WindowSystem::SetMode(WindowVisualInfo &param)
{
  DWORD dwStyle;
  dwStyle = GetWindowLong(windowHandle, GWL_STYLE);
  if (param.useFullscreen)
  {
    DEVMODE dmScreenSettings;
    memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
    dmScreenSettings.dmSize=sizeof(dmScreenSettings); 
    dmScreenSettings.dmPelsWidth  = param.width;
    dmScreenSettings.dmPelsHeight = param.height;
    dmScreenSettings.dmBitsPerPel = param.depthSize;
    dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
    LONG ret = ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN);
    if (ret != DISP_CHANGE_SUCCESSFUL)
    {
      core::Engine::GetEngine ()->GetLog ()
        << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::warning)
        << "Window doesn't support fullscreen." << std::flush;
      param.useFullscreen = false;
      return;
    }
    if (dwStyle & WS_OVERLAPPEDWINDOW) {
        SetWindowLong(windowHandle, GWL_STYLE,
                      dwStyle & ~WS_OVERLAPPEDWINDOW);
        SetWindowPos(windowHandle, HWND_TOP,
                     0, 0, param.width, param.height,
                     SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    } 

  }
  else
  {
    ChangeDisplaySettings(NULL,0);
    if (!(dwStyle & WS_OVERLAPPEDWINDOW))
    {
      SetWindowLong(windowHandle, GWL_STYLE,
                    dwStyle | WS_OVERLAPPEDWINDOW);
      SetWindowPos(windowHandle, HWND_TOP, param.positionX, param.positionY, 
                   param.width, param.height,
                   SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    }
  }
}

void
WindowSystem::InitializeWGLExtensions()
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
  int pixelFormat;

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
  wglGetPixelFormatAttribivARB  = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)
                                  wglGetProcAddress("wglGetPixelFormatAttribivARB");
  wglChoosePixelFormatARB       = (PFNWGLCHOOSEPIXELFORMATARBPROC) 
                                  wglGetProcAddress("wglChoosePixelFormatARB");
  wglCreateContextAttribsARB    = (PFNWGLCREATECONTEXTATTRIBSARBPROC) 
                                  wglGetProcAddress("wglCreateContextAttribsARB");

  PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
  PFNWGLGETEXTENSIONSSTRINGEXTPROC wglGetExtensionsStringEXT;

  wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)
      wglGetProcAddress("wglGetExtensionsStringARB");

  if (wglGetExtensionsStringARB != NULL)
  {
    const char * extensionsARB = wglGetExtensionsStringARB(deviceContext);
    core::Engine::GetEngine ()->GetLog ()
      << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::warning)
      << "Supported WGL ARB Extensions : " << extensionsARB << std::flush;
  }

  wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)
      wglGetProcAddress("wglGetExtensionsStringEXT");

  if (wglGetExtensionsStringEXT != NULL)
  {
    const char * extensionsEXT = wglGetExtensionsStringEXT();
    core::Engine::GetEngine ()->GetLog ()
      << HUMMSTRUMM_ENGINE_SET_LOGGING (Level::warning)
      << "Supported WGL EXT Extensions : " << extensionsEXT << std::flush;
  }

  wglMakeCurrent (NULL,NULL);
  wglDeleteContext (renderingContext);
  ReleaseDC (windowHandle, deviceContext);
  ::DestroyWindow (windowHandle); 
}

hummstrumm::engine::events::WindowEvents*
WindowSystem::GetNextEvent()
{
  MSG msg = { };

  if (msgQueue.size() > 0)
  {
    EventMsg eMsg;
    eMsg = msgQueue.front();
    switch (eMsg.msg)
    {
      case WM_SIZE:
      {
        msgQueue.pop();
        return new hummstrumm::engine::events::StructureEvents (
          hummstrumm::engine::events::WindowEvents::WINDOW_RESIZE, 
          LOWORD(eMsg.lparam),HIWORD(eMsg.lparam));
      }
      break;

      case WM_ACTIVATE:
      {
        msgQueue.pop();
        DWORD state = LOWORD(eMsg.wparam);
        if (state == 0)
        {
          return new hummstrumm::engine::events::StructureEvents (
            hummstrumm::engine::events::WindowEvents::WINDOW_INACTIVE);
        }
        else
        {
          return new hummstrumm::engine::events::StructureEvents (
            hummstrumm::engine::events::WindowEvents::WINDOW_ACTIVE);
        }
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
      return new hummstrumm::engine::events::StructureEvents(
        hummstrumm::engine::events::WindowEvents::WINDOW_CLOSE);
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
WindowSystem::PostEventMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
  EventMsg *pMsg = new EventMsg;
  pMsg->msg = msg;
  pMsg->wparam = wParam;
  pMsg->lparam = lParam;
  msgQueue.push(*pMsg);
}

int
WindowSystem::GetPendingEventsCount() const
{
  DWORD queueStatus = GetQueueStatus(QS_ALLINPUT);
  // The high-order word of the return value indicates the types of 
  // messages currently in the queue.
  return HIWORD(queueStatus) + msgQueue.size();
}

hummstrumm::engine::types::String
WindowSystem::GetErrorMessage(hummstrumm::engine::types::String premsg, DWORD code)
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
WindowSystem::ProcessWindowMessages(HWND hWnd, UINT uMsg, 
  WPARAM wParam, LPARAM lParam)
{

 WindowSystem *pWin;

  switch (uMsg)
  {

    case WM_CREATE:
    {
        CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pWin = reinterpret_cast<WindowSystem*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWin);
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

    case WM_ACTIVATE:
    {
      LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
      pWin = reinterpret_cast<WindowSystem*>(ptr);

      pWin->PostEventMessage(WM_ACTIVATE, wParam, lParam);
      break;
    }

    case WM_DISPLAYCHANGE:
    {
/*
      LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
      pWin = reinterpret_cast<WindowSystem*>(ptr);
      wParam = 0x1;
      lParam = 0x0;
      pWin->PostEventMessage(WM_ACTIVATE, wParam, lParam);
*/
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
      pWin = reinterpret_cast<WindowSystem*>(ptr);
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

