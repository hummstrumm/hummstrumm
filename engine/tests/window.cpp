
#define HUMMSTRUMM_ENGINE_SOURCE
#include <iostream>
#include <unistd.h>
#include "hummstrummengine.hpp"

using namespace hummstrumm::engine::renderer;

int
main()
{
  #ifdef HUMMSTRUMM_PLATFORM_GNULINUX
  std::cout << "Creating a X11 window\n";
  WindowX11 xwindow;
  
  xwindow.createWindow("Test window",512,512,0);
  std::cout << "Will set the window to fullscreen in 4 seconds...\n";
  sleep(4);
  xwindow.setToFullscreen();
  sleep(3);
  #endif

  #ifdef HUMMSTRUMM_PLATFORM_WINDOW
  std::cout << "Creating a Window in Microsoft Windows\n";
  #endif
  return 0;
}
