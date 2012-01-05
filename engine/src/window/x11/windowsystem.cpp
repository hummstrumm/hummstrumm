// -*- c++ -*-
/* Humm and Strumm Video Game
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

#define HUMMSTRUMM_ENGINE_SOURCE

#include "hummstrummengine.hpp"
#include <sstream>

namespace hummstrumm
{
namespace engine
{
namespace window
{

enum netWMStates
{
  _NET_WM_STATE_REMOVE,
  _NET_WM_STATE_ADD,
  _NET_WM_STATE_TOGGLE
};

WindowSystem* WindowSystem::runningInstance = NULL;

WindowSystem::WindowSystem()
{
  int major;
  int minor;

  std::stringstream message;
  if ((dpy = XOpenDisplay(NULL)) == NULL)
    HUMMSTRUMM_THROW (WindowSystem, "Unable to open a connection to the X server.\n");

  XSetErrorHandler(HandleGeneralXErrors);
  XSetIOErrorHandler(HandleIOXErrors);

  screen = XDefaultScreen(dpy);
  root = XRootWindow(dpy,screen);
  depth = XDefaultDepth(dpy,screen);

  windowContext = 0;
  pbufferContext = 0;

  if (!glXQueryExtension(dpy, NULL, NULL)) 
    HUMMSTRUMM_THROW (WindowSystem, "GLX extension is not available on the X server.");
  
  major = minor = 0;
  if (!glXQueryVersion(dpy, &major, &minor))
    HUMMSTRUMM_THROW (WindowSystem, "Unable to get GLX version.");

  wndProtocols = XInternAtom(dpy, "WM_PROTOCOLS", False);
  wndDelete = XInternAtom(dpy, "WM_DELETE_WINDOW", False);

  message.str("");
  message << "Supported GLX version: ";
  message << major;
  message << ".";
  message << minor;
  HUMMSTRUMM_LOG(message.str().c_str(),MESSAGE);

  swapIntervalAddr = NULL;
  createContextAttribsAddr = NULL;
  chooseFBConfigAddr = NULL;
  makeContextCurrentAddr = NULL;
  createPbufferAddr = NULL;
  destroyPbufferAddr = NULL;

  supportedSizes = XRRSizes(dpy, screen, &numSupportedSizes);
  screenConfigInformation = XRRGetScreenInfo(dpy, root);
  originalRate = XRRConfigCurrentRate(screenConfigInformation);
  originalSizeID = XRRConfigCurrentConfiguration(screenConfigInformation, &originalRotation);

  InitializeGLXExtensions ();

  runningInstance = this;
}

WindowSystem::~WindowSystem()
{
  if (dpy != NULL)
    XCloseDisplay(dpy);
}

int
WindowSystem::HandleGeneralXErrors(Display *dpy, XErrorEvent *xerr)
{

  if (runningInstance != NULL)
  {
    XRRSetScreenConfigAndRate(dpy, 
                              runningInstance->screenConfigInformation, 
                              runningInstance->root,
                              runningInstance->originalSizeID, 
                              runningInstance->originalRotation, 
                              runningInstance->originalRate, 
                              CurrentTime);
  }

  char *errMsg = new char[1024];
  XGetErrorText(dpy, xerr->error_code, errMsg, 1024);
  HUMMSTRUMM_THROW (WindowSystem, errMsg);
}

int
WindowSystem::HandleIOXErrors(Display *dpy)
{
  if (runningInstance != NULL)
  {
    XRRSetScreenConfigAndRate(dpy, 
                              runningInstance->screenConfigInformation, 
                              runningInstance->root,
                              runningInstance->originalSizeID, 
                              runningInstance->originalRotation, 
                              runningInstance->originalRate, 
                              CurrentTime);
  }

  HUMMSTRUMM_THROW (WindowSystem,  "X connection fatal I/O");
}

void
WindowSystem::DestroyWindow()
{
  XRRSetScreenConfigAndRate(dpy, screenConfigInformation, root,originalSizeID, originalRotation, originalRate, CurrentTime);

  // Release the current context first
  glXMakeCurrent(dpy, None, NULL);

  DestroyPbuffer(); 

  if (windowContext != 0)
    glXDestroyContext(dpy, windowContext);

  if (dpy != 0 && window != 0)
    XDestroyWindow(dpy, window);
  else
  {
    std::stringstream message;
    message.str("");
    message << "Cannot destroy window ";
    message << "Display is " << dpy;
    message << " and is ";
    message << "Window " << window;
    HUMMSTRUMM_LOG(message.str().c_str(),WARNING);
  }
}

void
WindowSystem::DestroyPbuffer()
{
  if (pbufferContext != 0)
  {
    glXDestroyContext(dpy, pbufferContext);
    destroyPbufferAddr(dpy, pbuffer);
  }
}

void
WindowSystem::CreatePbuffer(WindowVisualInfo &param)
{
  XVisualInfo *vi = NULL;
  GLXFBConfig *fbconfig = NULL;
  const int* attribList = NULL;
  int nelements;

  // Create offscreen rendering and share it with the window context
  if (param.useOffScreenRendering)
  {
    std::cout << "Creating pixel buffer for offscreen rendering\n";
    if (createPbufferAddr == NULL || destroyPbufferAddr == NULL)
    {
      param.useOffScreenRendering = false;
      return;
    }

    attribList = param.GetPixelFormatAttributes(true);
    if (attribList == NULL)
    {
      param.useOffScreenRendering = false;
      return;
    }

    if (chooseFBConfigAddr != NULL)
    {
      fbconfig = chooseFBConfigAddr(dpy,screen,attribList,&nelements);

      if (fbconfig == NULL)
      {
        param.useOffScreenRendering = false;
        return;
      }
 
      vi = glXGetVisualFromFBConfig(dpy,*fbconfig);
    }
    else
    {
      param.useOffScreenRendering = false;
      return;
    }

    if (vi == NULL)
    {
      param.useOffScreenRendering = false;
      XFree(fbconfig);
      return;
    }

    int pbufferAttrib[] =
    {
      GLX_PBUFFER_WIDTH, param.offscreenBufferWidth,
      GLX_PBUFFER_HEIGHT, param.offscreenBufferHeight,
      GLX_LARGEST_PBUFFER, param.offscreenUseLargestBufferAvailable, 
      None
    };

    pbuffer = glXCreatePbuffer(dpy, *fbconfig, pbufferAttrib);

    if (createContextAttribsAddr != NULL && chooseFBConfigAddr != NULL)
    {
      const int *ctxAttributes = param.GetContextAttributes();
      pbufferContext = createContextAttribsAddr(dpy, *fbconfig, windowContext, true, ctxAttributes);
    }
    else
    {
      pbufferContext = glXCreateContext (dpy, vi, windowContext, true);
    }

    glXQueryDrawable(dpy, pbuffer, GLX_WIDTH, &param.offscreenBufferWidth);
    glXQueryDrawable(dpy, pbuffer, GLX_HEIGHT, &param.offscreenBufferHeight);
    unsigned int tmp;
    glXQueryDrawable(dpy, pbuffer, GLX_LARGEST_PBUFFER, &tmp);
    param.offscreenUseLargestBufferAvailable = (tmp != 0);
    XFree(fbconfig);
    XFree(vi);
  } 
}

void
WindowSystem::InitializeGLXExtensions()
{
  /* Note: http://dri.freedesktop.org/wiki/glXGetProcAddressNeverReturnsNULL */
  /* Doing this is acceptable for GLX functions. See the last paragraph of misconception #3. */

  const char* extensions =  glXQueryExtensionsString(dpy, screen);

  std::stringstream message;
  message.str("");
  message << "Available GLX extensions: ";
  message << extensions; 
  HUMMSTRUMM_LOG(message.str().c_str(),MESSAGE); 

  if (IsGLXExtensionSupported("GLX_SGI_swap_control",(const GLubyte *) extensions))
  {
    swapIntervalAddr = (PFNGLXSWAPINTERVALSGIPROC) 
                       glXGetProcAddressARB ((const GLubyte *) "glXSwapIntervalSGI");
  }

  if (IsGLXExtensionSupported("GLX_ARB_create_context",(const GLubyte *)extensions))
  {
    createContextAttribsAddr = (PFNGLXCREATECONTEXTATTRIBSARBPROC)
                                glXGetProcAddress ((const GLubyte *) "glXCreateContextAttribsARB");
  }

  chooseFBConfigAddr = (PFNGLXCHOOSEFBCONFIGPROC) 
                        glXGetProcAddressARB ((const GLubyte *) "glXChooseFBConfig");

  makeContextCurrentAddr = (PFNGLXMAKECONTEXTCURRENTPROC)
                            glXGetProcAddressARB ((const GLubyte *) "glXMakeContextCurrent");

  createPbufferAddr = (PFNGLXCREATEPBUFFERPROC)
                       glXGetProcAddressARB ((const GLubyte *) "glXCreatePbuffer");

  destroyPbufferAddr = (PFNGLXDESTROYPBUFFERPROC)
                        glXGetProcAddressARB ((const GLubyte *) "glXDestroyPbuffer");
}

bool
WindowSystem::IsGLXExtensionSupported(const char* extension, const GLubyte *extensions)
{
  const GLubyte *start;
  GLubyte *where, *terminator;

  start = extensions;
  while(1)
  {
      where = (GLubyte *) strstr ((const char *)start, extension);
      if( !where )
      {
          return false;
      }
      terminator = where + strlen(extension);
      if( where == start || *(where - 1) == ' ' )
      {
          if( *terminator == ' ' || *terminator == '\0' )
          {
              break;
          }
      }
      start = terminator;
  }
  return true;
}

void
WindowSystem::SetContextCurrent(Context &ctx)
{
  if (ctx == PBUFFER && pbufferContext != 0)
  {
    if (makeContextCurrentAddr != NULL)
    {
      makeContextCurrentAddr(dpy, pbuffer, pbuffer, pbufferContext);
    }
    else
      glXMakeCurrent(dpy,pbuffer,pbufferContext);
  }
  else
  {
    if (makeContextCurrentAddr != NULL && windowContext != 0)
    {
      makeContextCurrentAddr(dpy, window, window, windowContext);
    }
    else
      glXMakeCurrent(dpy,window,windowContext);
  }
}

void
WindowSystem::SwapBuffers()
{
  GLXDrawable currentDrawable = glXGetCurrentDrawable();
  if (currentDrawable == 0)
    return;
  glXSwapBuffers(dpy, currentDrawable);
}

void
WindowSystem::CreateWindow(WindowVisualInfo &windowParameters)
{
  XSetWindowAttributes winAttr; 
  XVisualInfo *vi = NULL;
  GLXFBConfig *fbconfig = NULL;
  int nelements;
  const int* attribList = NULL;

  attribList = windowParameters.GetPixelFormatAttributes(false);
  if (attribList == NULL)
    HUMMSTRUMM_THROW (WindowSystem, "Unable to get window parameters\n");

  if (chooseFBConfigAddr != NULL)
  {
    fbconfig = chooseFBConfigAddr(dpy,screen,attribList,&nelements);

    if (fbconfig == NULL)
      HUMMSTRUMM_THROW (WindowSystem, "No frame buffer configurations exist on the specified screen, or no frame buffer configurations match the specified attributes for window rendering");

    vi = glXGetVisualFromFBConfig(dpy,*fbconfig);
    int tmp;
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_RED_SIZE, &windowParameters.redSize);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_GREEN_SIZE, &windowParameters.greenSize);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_BLUE_SIZE, &windowParameters.blueSize);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_ALPHA_SIZE, &windowParameters.alphaSize);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_DOUBLEBUFFER, &tmp);
    windowParameters.useDoubleBuffer = (tmp != 0);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_STEREO, &tmp);
    windowParameters.useStereo = (tmp != 0);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_DEPTH_SIZE, &windowParameters.depthSize);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_STENCIL_SIZE, &windowParameters.stencilSize);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_ACCUM_RED_SIZE, &windowParameters.accumRedSize);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_ACCUM_GREEN_SIZE, &windowParameters.accumGreenSize);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_ACCUM_BLUE_SIZE, &windowParameters.accumBlueSize);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_ACCUM_ALPHA_SIZE, &windowParameters.accumAlphaSize);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_AUX_BUFFERS, &windowParameters.bufferSize);
    glXGetFBConfigAttrib(dpy, *fbconfig, GLX_SAMPLES, &windowParameters.samples);
  }
  else
  {
    // glXChooseFBConfig is not available so looks like we're running in a system with 
    // GLX 1.2 or below.
    // Fallback
    bool rgba = (windowParameters.renderType == GLX_RGBA_BIT) ? true : false;
    int hasStereo = 0;
    if (windowParameters.useStereo)
       hasStereo = GLX_STEREO;

    int altAttribList[] = 
    {
      GLX_USE_GL,           GL_TRUE,
      GLX_BUFFER_SIZE,      windowParameters.bufferSize,
      GLX_LEVEL,            0,
      GLX_RGBA,             rgba,
      GLX_DOUBLEBUFFER,     windowParameters.useDoubleBuffer,
      GLX_AUX_BUFFERS,      windowParameters.auxBuffers,
      GLX_RED_SIZE,         windowParameters.redSize,
      GLX_GREEN_SIZE,       windowParameters.greenSize,
      GLX_BLUE_SIZE,        windowParameters.blueSize,
      GLX_ALPHA_SIZE,       windowParameters.alphaSize,
      GLX_DEPTH_SIZE,       windowParameters.depthSize,
      GLX_STENCIL_SIZE,     windowParameters.stencilSize,
      GLX_ACCUM_RED_SIZE,   windowParameters.accumRedSize,
      GLX_ACCUM_BLUE_SIZE,  windowParameters.accumBlueSize,
      GLX_ACCUM_GREEN_SIZE, windowParameters.accumGreenSize,
      GLX_SAMPLE_BUFFERS,   (windowParameters.useAntiAliasing) ? 1 : 0,
      GLX_SAMPLES,          windowParameters.samples,
      hasStereo, 
      0
    };

    vi = glXChooseVisual(dpy, screen, altAttribList);
    int tmp;
    glXGetConfig(dpy, vi, GLX_RED_SIZE, &windowParameters.redSize);
    glXGetConfig(dpy, vi, GLX_GREEN_SIZE, &windowParameters.greenSize);
    glXGetConfig(dpy, vi, GLX_BLUE_SIZE, &windowParameters.blueSize);
    glXGetConfig(dpy, vi, GLX_ALPHA_SIZE, &windowParameters.alphaSize);
    glXGetConfig(dpy, vi, GLX_DOUBLEBUFFER, &tmp);
    windowParameters.useDoubleBuffer = (tmp != 0);
    glXGetConfig(dpy, vi, GLX_STEREO, &tmp);
    windowParameters.useStereo = (tmp != 0);
    glXGetConfig(dpy, vi, GLX_DEPTH_SIZE, &windowParameters.depthSize);
    glXGetConfig(dpy, vi, GLX_STENCIL_SIZE, &windowParameters.stencilSize);
    glXGetConfig(dpy, vi, GLX_ACCUM_RED_SIZE, &windowParameters.accumRedSize);
    glXGetConfig(dpy, vi, GLX_ACCUM_GREEN_SIZE, &windowParameters.accumGreenSize);
    glXGetConfig(dpy, vi, GLX_ACCUM_BLUE_SIZE, &windowParameters.accumBlueSize);
    glXGetConfig(dpy, vi, GLX_ACCUM_ALPHA_SIZE, &windowParameters.accumAlphaSize);
    glXGetConfig(dpy, vi, GLX_AUX_BUFFERS, &windowParameters.bufferSize);
    glXGetConfig(dpy, vi, GLX_SAMPLES, &windowParameters.samples);
  }

  if (vi == NULL)
    HUMMSTRUMM_THROW (WindowSystem, "Requested GLX visual is not supported by the graphics card.");

  if (createContextAttribsAddr != NULL && chooseFBConfigAddr != NULL)
  {
    const int *ctxAttributes = windowParameters.GetContextAttributes();
    windowContext = createContextAttribsAddr(dpy, *fbconfig, NULL, true, ctxAttributes);
  }
  else
  {
    windowContext = glXCreateContext(dpy,vi,0,GL_TRUE);
  }

  XFree(fbconfig);

  Screen* scr = DefaultScreenOfDisplay(dpy);

  winAttr.background_pixel = BlackPixel(dpy,screen);
  winAttr.border_pixel = 0;
  winAttr.colormap = XCreateColormap(dpy,root,vi->visual,AllocNone);
  winAttr.event_mask = KeyPressMask         |
                       ExposureMask         |
                       ButtonPressMask      |
                       StructureNotifyMask  |
                       PointerMotionMask    |
                       KeyReleaseMask       |
                       FocusChangeMask      |
                       ButtonReleaseMask;


  window = XCreateWindow(dpy, 
                        root, windowParameters.positionX, windowParameters.positionY, 
                        windowParameters.width, windowParameters.height, 
                        0, vi->depth, InputOutput, 
                        vi->visual,
                        CWBorderPixel | CWColormap | CWEventMask | CWBackPixel, 
                        &winAttr);


  XFree(vi);

  if (window == 0)
    HUMMSTRUMM_THROW (WindowSystem, "Unable to create an X11 window\n");

  XStoreName(dpy, window, windowParameters.name.c_str());

  Atom wndName = XInternAtom(dpy, "XA_WM_NAME", False);

  XSetWMProtocols(dpy,window, &wndDelete, 1);

  XMapWindow(dpy,window);
  XMapRaised(dpy,window);

  if (makeContextCurrentAddr != NULL)
  {
    makeContextCurrentAddr(dpy, window, window, windowContext);
  }
  else
    glXMakeCurrent(dpy,window,windowContext);

  if (glXIsDirect(dpy,windowContext))
    HUMMSTRUMM_LOG("DRI enabled",MESSAGE);
  else
    HUMMSTRUMM_LOG("DRI not enabled",MESSAGE);

  if ( swapIntervalAddr != NULL)
    swapIntervalAddr (windowParameters.useVerticalSync);

  CreatePbuffer(windowParameters);
 
  SetMode(windowParameters);
}

int
WindowSystem::IsResolutionSupported(unsigned int w, unsigned int h) const
{
  for (int j = 0; j < numSupportedSizes; j++)
  {
    if (supportedSizes[j].width == w && supportedSizes[j].height == h)
    {
      return j;
    }
  }
  return -1;
}

void
WindowSystem::SetMode(WindowVisualInfo &param)
{
  if (param.useFullscreen)
  {
    long atomsSize;
    Atom *atoms;
    XWindowAttributes xwa;
    bool netWMFullscreen = false;

    int resID = IsResolutionSupported(param.width, param.height);

    if (resID == -1)
    {
        param.useFullscreen = false;
        XMoveResizeWindow(dpy,window,param.positionX,param.positionY,param.width, param.height);
        return;
    }

    XRRSetScreenConfig(dpy, screenConfigInformation, root, resID, RR_Rotate_0, CurrentTime);

    // The EWMH spec says that "_NET_WM_STATE_FULLSCREEN indicates that the window 
    // should fill the entire screen and have no window decorations. Additionally 
    // the Window Manager is responsible for restoring the original geometry after 
    // a switch from fullscreen back to normal window. For example, a presentation 
    // program would use this hint." 

    // As some window managers still support the old MWN_HINTS we will try that to
    // disable any window decorations

    if (IsNetWMCompliant())
    {
      Atom netSupported = XInternAtom(dpy,"_NET_SUPPORTED", False);
      Atom wmState = XInternAtom(dpy, "_NET_WM_STATE", False);
      Atom fullScreen = XInternAtom(dpy,"_NET_WM_STATE_FULLSCREEN", False);
      if ((atoms = (Atom *) GetXProperty(root, netSupported, XA_ATOM, atomsSize)))
      {
       for (unsigned i = 0; i < atomsSize; i++)
        {
          if (atoms[i] == fullScreen) 
          {
            netWMFullscreen = true;
            break;
          }
        }
      }
      delete [] atoms;

      if (netWMFullscreen)
      {
        XEvent xev;
        xev.xclient.type = ClientMessage;
        xev.xclient.serial = 0;
        xev.xclient.send_event = True;
        xev.xclient.window = window;
        xev.xclient.message_type = wmState;
        xev.xclient.format = 32;
        xev.xclient.data.l[0] = _NET_WM_STATE_ADD;
        xev.xclient.data.l[1] = fullScreen;
        xev.xclient.data.l[2] = 0;
        xev.xclient.data.l[3] = 0;
        xev.xclient.data.l[4] = 0;

        XSendEvent(dpy, 
                   root, 
                   False, 
                   SubstructureRedirectMask | SubstructureNotifyMask, 
                   &xev);
   
        if (param.useOffScreenRendering)
        {
          unsigned int state;
          glXQueryDrawable(dpy, pbuffer, GLX_PRESERVED_CONTENTS, &state);
          if (state == 0)
          {
            std::cout << "Pbuffer contents have been lost!\n";
            DestroyPbuffer();
            CreatePbuffer(param);   
          }
        }
        return;
      }
      param.useFullscreen = false;
    }

    // Set fullscreen (fallback)
    HUMMSTRUMM_LOG("The Window Manager doesn't support NETWM. Using fullscreen fallback mode",WARNING);
    XGetWindowAttributes(dpy, root, &xwa);
    XMoveResizeWindow(dpy,window,0,0,xwa.width, xwa.height);
  }
  else
  {
    XRRSetScreenConfigAndRate(dpy, screenConfigInformation, root,originalSizeID, originalRotation, originalRate, CurrentTime);

    Atom wmState = XInternAtom(dpy, "_NET_WM_STATE", False);
    Atom fullScreen = XInternAtom(dpy,"_NET_WM_STATE_FULLSCREEN", False);

    XEvent xev;
    xev.xclient.type=ClientMessage;
    xev.xclient.serial = 0;
    xev.xclient.send_event=True;
    xev.xclient.window=window;
    xev.xclient.message_type=wmState;
    xev.xclient.format=32;
    xev.xclient.data.l[0] = 0;
    xev.xclient.data.l[1] = fullScreen;
    xev.xclient.data.l[2] = 0;
  
    XSendEvent(dpy, 
               root, 
               False, 
               SubstructureRedirectMask | SubstructureNotifyMask, 
               &xev);

    XMoveResizeWindow(dpy,window,param.positionX,param.positionY,param.width, param.height);

  }
}

hummstrumm::engine::events::WindowEvents*
WindowSystem::GetNextEvent()
{
  XEvent event;
  // Blocks until an event is received
  XNextEvent(dpy,&event);
 
  switch (event.type)
  {
    case DestroyNotify:
      return new hummstrumm::engine::events::StructureEvents(
        hummstrumm::engine::events::WindowEvents::WINDOW_CLOSE);

    case ClientMessage:
      if (event.xclient.message_type == wndProtocols &&
          event.xclient.data.l[0] == wndDelete)
      {
        return new hummstrumm::engine::events::StructureEvents(
          hummstrumm::engine::events::WindowEvents::WINDOW_CLOSE);
      }
      break;

    case FocusIn:
      return new hummstrumm::engine::events::StructureEvents(
        hummstrumm::engine::events::WindowEvents::WINDOW_ACTIVE);
 
    case FocusOut:
      return new hummstrumm::engine::events::StructureEvents(
        hummstrumm::engine::events::WindowEvents::WINDOW_INACTIVE);

    case Expose:
      break;

    case ConfigureNotify:
        return new hummstrumm::engine::events::StructureEvents(
          hummstrumm::engine::events::WindowEvents::WINDOW_RESIZE, 
          event.xconfigurerequest.width,
          event.xconfigurerequest.height);
    default:
      break;
  }
  return new hummstrumm::engine::events::WindowEvents();
}

int
WindowSystem::GetPendingEventsCount() const
{
  return XPending(dpy);
}

char *
WindowSystem::GetXProperty(const Window &win, Atom property, Atom property_type, long &size) const
{
  // adapted from wmctrl source code
  Atom xa_ret_type;
  int format;
  unsigned long nitems;
  unsigned long bytes_after_return;
  unsigned char *data;
  unsigned long nbytes;
  char *ret;
  unsigned long maxSize = 10000;

  if (XGetWindowProperty(dpy,win,property, 0, 1024, False, property_type,
                         &xa_ret_type, &format, &nitems, &bytes_after_return,
                         &data) != Success)
  {
    return NULL;
  }

  if (xa_ret_type != property_type)
  {
    return NULL;
    XFree(data);
  }
  
  if (format == 32)
    nbytes = sizeof(long);
  else if (format == 16)
    nbytes = sizeof(short);
  else if (format == 8)
    nbytes = 1;
  else
    return NULL;

  size= std::min(nitems * nbytes,maxSize);
  ret = new char[size + 1];
  memcpy(ret,data,size);
  ret[size] = '\0';
  size = size;
  XFree(data);
  return ret;
}

bool
WindowSystem::IsNetWMCompliant() const
{
  long winSize;
  bool retCode = false;
  Window *win = NULL;
  Atom netWMSupport = XInternAtom(dpy, "_NET_SUPPORTING_WM_CHECK",False);
  if ((win = (Window *) GetXProperty(root, netWMSupport, XA_WINDOW, winSize)))
    retCode = true;
  delete [] win;
  return retCode;
}

}
}
}

