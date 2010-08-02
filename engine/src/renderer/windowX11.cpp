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

#define HUMMSTRUMM_ENGINE_SOURCE

#include "hummstrummengine.hpp"

namespace hummstrumm
{
namespace engine
{
namespace renderer
{

WindowX11::WindowX11()
{
  if ((dpy = XOpenDisplay(NULL)) == NULL)
    HUMMSTRUMM_THROW (Generic, "Unable to open a connection to the X server.");
  screen = XDefaultScreen(dpy);
  root = XRootWindow(dpy,screen);
  depth = XDefaultDepth(dpy,screen);
  NetWMSupport = IsNetWMCompliant(); 
}

WindowX11::~WindowX11()
{
  if (dpy != NULL)
    XCloseDisplay(dpy);
}

void
WindowX11::createWindow(std::string name, unsigned height, unsigned width, bool fs)
{
  winXMain = XCreateSimpleWindow(dpy, root, 100, 100, width, height, 0, 0, BlackPixel(dpy,screen));
  if (fs)
    setToFullscreen();
  XMapWindow(dpy,winXMain);
  XMapRaised(dpy,winXMain);
}

void
WindowX11::setToFullscreen()
{

  long atomsSize;
  Atom *atoms;
  XWindowAttributes xwa;
  bool netWMFullscreen = false;
  // Lets see if the WM supports _NET_WM_STATE and _NET_WM_STATE_FULLSCREEN.
  if (NetWMSupport)
  {
    Atom netSupported = XInternAtom(dpy,"_NET_SUPPORTED", False);
    Atom wmState = XInternAtom(dpy, "_NET_WM_STATE", False);
    Atom fullScreen = XInternAtom(dpy,"_NET_WM_STATE_FULLSCREEN", False);
    if ( atoms = (Atom *) getXProperty(root, netSupported, XA_ATOM, atomsSize))
    {
      for (unsigned i = 0; i < atomsSize; i++)
        if (atoms[i] == fullScreen) 
        {
          // NetWM Fullscreen supported
          netWMFullscreen = true;
          break;
        } 
    }
    delete [] atoms;
    
    if (netWMFullscreen)
    {
      XEvent xev;
      xev.xclient.type=ClientMessage;
      xev.xclient.serial = 0;
      xev.xclient.send_event=True;
      xev.xclient.window=winXMain;
      xev.xclient.message_type=wmState;
      xev.xclient.format=32;
      xev.xclient.data.l[0] = 1;
      xev.xclient.data.l[1] = fullScreen;
      xev.xclient.data.l[2] = 0;

      XSendEvent(dpy, root, False,
             SubstructureRedirectMask | SubstructureNotifyMask,&xev);
  
      return;
    }

  }
  // Set fullscreen (fallback)
  // This may keep WM decorations..
  XGetWindowAttributes(dpy, root, &xwa);
  std::cout << xwa.width << " " << xwa.height << std::endl;
  XMoveResizeWindow(dpy,winXMain,0,0,xwa.width, xwa.height);
}

void
WindowX11::setToWindowMode()
{

}

void
WindowX11::setWidth(unsigned width)
{
  XWindowAttributes xwa;
  XGetWindowAttributes(dpy, root, &xwa);
  XResizeWindow(dpy,winXMain,width,xwa.height);
}

void
WindowX11::setHeight(unsigned height)
{
  XWindowAttributes xwa;
  XGetWindowAttributes(dpy, root, &xwa);
  XResizeWindow(dpy,winXMain,xwa.width,height);
}

// Private methods

char *
WindowX11::getXProperty(Window &win, Atom property, Atom property_type, long &size)
{
  // adapted from wmctrl source code
  Atom xa_ret_type;
  int format;
  unsigned long nitems;
  unsigned long bytes_after_return;
  unsigned long tmpsize;
  unsigned char *data;
  char *ret;

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
  tmpsize = (format / 8) * nitems;
  ret = new char[tmpsize + 1];
  memcpy(ret,data,tmpsize);
  // makes life easier to handling string
  ret[tmpsize] = '\0';

  size = tmpsize;
  XFree(data);
  return ret;
}

bool
WindowX11::IsNetWMCompliant()
{
  long winSize;
  bool retCode = false;
  Window *win = NULL;
  Atom netWMSupport = XInternAtom(dpy, "_NET_SUPPORTING_WM_CHECK",False);
  if (win = (Window *) getXProperty(root, netWMSupport, XA_WINDOW, winSize))
  {
    retCode = true;
  }
  delete [] win;
  return retCode;
}

}
}
}

