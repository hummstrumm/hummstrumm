#include "stdlib.h"
#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
#include "GL/glx.h"
#include "X11/Xlib.h"
#elif HUMMSTRUMM_PLATFORM_WIN

#endif

int
main()
{
  #ifdef HUMMSTRUMM_PLATFORM_GNULINUX
  Display *dpy;
  int major = 0;
  int minor = 0;
  if ((dpy = XOpenDisplay(NULL)) == NULL)
    return -1;
  if (glXQueryVersion(dpy, &major, &minor))
    return major*10 + minor;
  else
    return -1;
  #elif HUMMSTRUMM_PLATFORM_WIN
  return 0;
  #endif
}

