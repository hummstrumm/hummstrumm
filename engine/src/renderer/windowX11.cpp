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
namespace renderer
{

using hummstrumm::engine::events::StructureEvents;

enum netWMStates
{
  _NET_WM_STATE_REMOVE,
  _NET_WM_STATE_ADD,
  _NET_WM_STATE_TOGGLE
};

WindowX11::WindowX11()
{
  std::stringstream message;
  if ((dpy = XOpenDisplay(NULL)) == NULL)
    HUMMSTRUMM_THROW (Generic, "Unable to open a connection to the X server.\n");
  screen = XDefaultScreen(dpy);
  root = XRootWindow(dpy,screen);
  depth = XDefaultDepth(dpy,screen);
  if (!IsGLXSupported()) 
    HUMMSTRUMM_THROW (Generic, "GLX extension is not available on the X server.");
  
  glXVerMajor = glXVerMinor = 0;
  if (!GetGLXVersion(&glXVerMajor, &glXVerMinor))
    HUMMSTRUMM_THROW (Generic, "Unable to get GLX version.");

  message.str("");
  message << "Supported GLX version: ";
  message << glXVerMajor;
  message << ".";
  message << glXVerMinor;
  HUMMSTRUMM_LOG(message.str().c_str(),MESSAGE);
}

WindowX11::~WindowX11()
{
  if (dpy != NULL)
    XCloseDisplay(dpy);
}


void
WindowX11::DestroyWindow()
{
  if (dpy != NULL && winMn != NULL)
    XDestroyWindow(dpy, winMn);
  else
  {
    std::stringstream message;
    message.str("");
    message << "Cannot destroy window ";
    message << "Display is " << dpy;
    message << " and is ";
    message << "Window " << winMn;
    HUMMSTRUMM_LOG(message.str().c_str(),WARNING);
  }
}

void
WindowX11::CreateWindow(const WindowParameters &winParam)
{
  XSetWindowAttributes winAttr; 
  XVisualInfo *vi;
  GLXFBConfig *fbconfig;
  GLXContext glxCtx;
  int nelements;
  HUMMSTRUMM_WINDOW_LIST_POINTER attribList = winParam.WindowParamList();

  if (attribList == NULL)
    HUMMSTRUMM_THROW(Generic, "Unable to get window parameters\n");

  fbconfig = glXChooseFBConfig(dpy,screen,attribList,&nelements);

  if (fbconfig == NULL)
    HUMMSTRUMM_THROW(Generic, "No frame buffer configurations exist on the specified screen, or no frame buffer configurations match the specified attributes.");

  vi = glXGetVisualFromFBConfig(dpy,*fbconfig);
  if (vi == NULL)
    HUMMSTRUMM_THROW(Generic, "Requested GLX visual is not supported by the graphics card.");

  glxCtx = glXCreateContext(dpy,vi,0,GL_TRUE);

  XFree(fbconfig);

  delete [] attribList;

  scr = DefaultScreenOfDisplay(dpy);

  winAttr.background_pixel = BlackPixel(dpy,screen);
  winAttr.border_pixel = 0;
  winAttr.colormap = XCreateColormap(dpy,root,vi->visual,AllocNone);
  winAttr.event_mask = KeyPressMask         |
                       ExposureMask         |
                       ButtonPressMask      |
                       StructureNotifyMask  |
                       PointerMotionMask    |
                       KeyReleaseMask       |
                       ButtonReleaseMask;


  winMn = XCreateWindow(dpy, 
                        root, winParam.positionX, winParam.positionY, 
                        winParam.width, winParam.height, 
                        0, vi->depth, InputOutput, 
                        vi->visual,
                        CWBorderPixel | CWColormap | CWEventMask | CWBackPixel, 
                        &winAttr);


  XFree(vi);

  if (winMn == 0)
    HUMMSTRUMM_THROW(Generic, "Unable to create an X11 window\n");

  XStoreName(dpy, winMn, winParam.name.c_str());

  wndProtocols = XInternAtom(dpy, "WM_PROTOCOLS", False);
  wndDelete = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
  Atom wndName = XInternAtom(dpy, "XA_WM_NAME", False);

  XSetWMProtocols(dpy,winMn, &wndDelete, 1);

  XMapWindow(dpy,winMn);
  XMapRaised(dpy,winMn);
  if (winParam.fullscreen)
    SetFullscreen();

  glXMakeCurrent(dpy,winMn,glxCtx);
  if (glXIsDirect(dpy,glxCtx))
  {
    HUMMSTRUMM_LOG("DRI enabled",MESSAGE);
  }
  else
  {
    HUMMSTRUMM_LOG("DRI not enabled",MESSAGE);
  }


}

void
WindowX11::SetFullscreen()
{

  long atomsSize;
  Atom *atoms;
  XWindowAttributes xwa;
  bool netWMFullscreen = false;

  //The EWMH spec says that "_NET_WM_STATE_FULLSCREEN indicates that the window 
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
    if ( atoms = (Atom *) GetXProperty(root, netSupported, XA_ATOM, atomsSize))
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
      xev.xclient.window = winMn;
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
  
      return;
    }
  }

  // Set fullscreen (fallback)
  HUMMSTRUMM_LOG("The Window Manager doesn't support NETWM",WARNING);
  XGetWindowAttributes(dpy, root, &xwa);
  XMoveResizeWindow(dpy,winMn,0,0,xwa.width, xwa.height);
}

void
WindowX11::SetWindowMode()
{ 
  Atom wmState = XInternAtom(dpy, "_NET_WM_STATE", False);
  Atom fullScreen = XInternAtom(dpy,"_NET_WM_STATE_FULLSCREEN", False);

  XEvent xev;
  xev.xclient.type=ClientMessage;
  xev.xclient.serial = 0;
  xev.xclient.send_event=True;
  xev.xclient.window=winMn;
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
}

int WindowX11::GetHeight()
{
  XWindowAttributes xwa;
  XGetWindowAttributes(dpy,winMn,&xwa);
  return xwa.height;
}

int WindowX11::GetWidth()
{
  XWindowAttributes xwa;
  XGetWindowAttributes(dpy,winMn,&xwa);
  return xwa.width;
}

WindowEvents*
WindowX11::GetNextEvent() const
{
  XEvent event;
  XNextEvent(dpy,&event);

  switch (event.type)
  {
    case DestroyNotify:
      return new StructureEvents(WindowEvents::WINDOW_CLOSE);

    case ClientMessage:
      if (event.xclient.message_type == wndProtocols &&
        event.xclient.data.l[0] == wndDelete)
      {
        return new StructureEvents(WindowEvents::WINDOW_CLOSE);
      }
      break;

    case Expose:
      break;

    case ConfigureNotify:
        return new StructureEvents(WindowEvents::WINDOW_RESIZE, event.xconfigurerequest.width,
                                   event.xconfigurerequest.height);

    default:
      break;
  }
  return new WindowEvents();
}

int
WindowX11::GetPendingEventsCount() const
{
  return XPending(dpy);
}

void
WindowX11::SwapBuffers() const
{
  // No-op if winMn was created with a non-double-buffered GLXFBConfig.
  glXSwapBuffers(dpy, winMn);
}

// Private methods

char *
WindowX11::GetXProperty(const Window &win, Atom property, Atom property_type, long &size) const
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
WindowX11::IsNetWMCompliant() const
{
  long winSize;
  bool retCode = false;
  Window *win = NULL;
  Atom netWMSupport = XInternAtom(dpy, "_NET_SUPPORTING_WM_CHECK",False);
  if (win = (Window *) GetXProperty(root, netWMSupport, XA_WINDOW, winSize))
    retCode = true;
  delete [] win;
  return retCode;
}

bool 
WindowX11::IsGLXSupported() const
{
  return glXQueryExtension(dpy, NULL, NULL);
}

bool
WindowX11::GetGLXVersion(int *major, int *minor) const
{
  return glXQueryVersion(dpy, major, minor);
}

}
}
}

