
#define HUMMSTRUMM_ENGINE_SOURCE
#include <iostream>
#include "hummstrummengine.hpp"
#ifndef HUMMSTRUMM_PLATFORM_WINDOWS
#include <unistd.h>
#include <signal.h>
#endif // #ifndef HUMMSTRUMM_PLATFORM_WINDOWS

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

using namespace hummstrumm::engine::renderer;


static GLfloat rotQuad = 0.0f;
static WindowX11* xwindow;
static bool window;


void resizeGL(unsigned int width, unsigned int height)
{                                                     
    /* prevent divide-by-zero */                      
    if (height == 0)                                  
        height = 1;                                   
    glViewport(0, 0, width, height);                  
    glMatrixMode(GL_PROJECTION);                      
    glLoadIdentity();                                 
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}                                                                         
 
void initGL()
{            
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);                  
    glEnable(GL_DEPTH_TEST);             
    glDepthFunc(GL_LEQUAL);              
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    /* Reset the rotation angle of our object */
    rotQuad = 0;                                               
    glFlush();                                                  

}                                                               
 
void renderGL()
{              
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();                                  
    glTranslatef(0.0f, 0.0f, -7.0f);                   
    glRotatef(rotQuad, 1.0f, 0.5f, 0.25f);             
    glBegin(GL_QUADS);                                 
        /* top of cube */                              
        glColor3f(0.0f, 1.0f, 0.0f);                   
        glVertex3f(1.0f, 1.0f, -1.0f);                 
        glVertex3f(-1.0f, 1.0f, -1.0f);                
        glVertex3f(-1.0f, 1.0f, 1.0f);                 
        glVertex3f(1.0f, 1.0f, 1.0f);                  
        /* bottom of cube */                           
        glColor3f(1.0f, 0.5f, 0.0f);                   
        glVertex3f(1.0f, -1.0f, 1.0f);                 
        glVertex3f(-1.0f, -1.0f, 1.0f);                
        glVertex3f(-1.0f, -1.0f, -1.0f);               
        glVertex3f(1.0f, -1.0f, -1.0f);                
        /* front of cube */                            
        glColor3f(1.0f, 0.0f, 0.0f);                   
        glVertex3f(1.0f, 1.0f, 1.0f);                  
        glVertex3f(-1.0f, 1.0f, 1.0f);                 
        glVertex3f(-1.0f, -1.0f, 1.0f);                
        glVertex3f(1.0f, -1.0f, 1.0f);                 
        /* back of cube */                             
        glColor3f(1.0f, 1.0f, 0.0f);                   
        glVertex3f(-1.0f, 1.0f, -1.0f);                
        glVertex3f(1.0f, 1.0f, -1.0f);                 
        glVertex3f(1.0f, -1.0f, -1.0f);                
        glVertex3f(-1.0f, -1.0f, -1.0f);               
        /* right side of cube */                       
        glColor3f(1.0f, 0.0f, 1.0f);                   
        glVertex3f(1.0f, 1.0f, -1.0f);                 
        glVertex3f(1.0f, 1.0f, 1.0f);                  
        glVertex3f(1.0f, -1.0f, 1.0f);                 
        glVertex3f(1.0f, -1.0f, -1.0f);                
        /* left side of cube */                        
        glColor3f(0.0f, 1.0f, 1.0f);                   
        glVertex3f(-1.0f, 1.0f, 1.0f);                 
        glVertex3f(-1.0f, 1.0f, -1.0f);                
        glVertex3f(-1.0f, -1.0f, -1.0f);               
        glVertex3f(-1.0f, -1.0f, 1.0f);                
    glEnd();                                           
    rotQuad += 0.1f;     
}  


void
setfs(int sig)
{
    std::cout << "Alarm" << std::endl;

    window = false;

    if (window)
    {
      std::cout << "Fullscreen window mode\n";
      xwindow->SetFullscreen();
//      resizeGL(xwindow->GetWidth(), xwindow->GetHeight());
    }
    else
    {
      std::cout << "Windowed mode\n";
      xwindow->SetWindowMode();
//      resizeGL(400,812);
    }
    alarm(10); 
}


int
main()
{
  hummstrumm::engine::core::Engine engine;

#ifdef HUMMSTRUMM_WINDOWSYSTEM_X11

  try
  {
    std::cout << "X11 windows testing with OpenGL/GLX context" << std::endl;
    xwindow = new WindowX11;
    WindowGLXParam param;
    param.fullscreen = false;
    param.doubleBuffer = true;
    param.redSize = 4;
    param.greenSize = 4;
    param.blueSize = 4;
    param.depthSize = 16;

    window = !param.fullscreen;
    xwindow->CreateWindow(param);
    initGL();
//    std::cout << xwindow->GetWidth() << "," <<  xwindow->GetHeight() << std::endl;
//    std::cout << param.width << "," << param.height << std::endl;
//    resizeGL(xwindow->GetWidth(), xwindow->GetHeight());


//    resizeGL(512,512);
   
//    signal(SIGALRM, setfs);    
//    alarm(10);
//    xwindow->SetFullscreen();

    while (1)
    {
      while (xwindow->GetPendingEventsCount() > 0) 
      {
        WindowEvents *wev = xwindow->GetNextEvent();
        StructureEvents *wsv = NULL;
        switch(wev->getType())
        {
          case WindowEvents::WINDOW_RESIZE: 
              std::cout << "window resize event\n";
              wsv = (StructureEvents *) wev;
              std::cout << wsv->GetWidth() << "," << wsv->GetHeight() << std::endl;
              resizeGL(wsv->GetWidth(), wsv->GetHeight());
              break;

          case WindowEvents::WINDOW_CLOSE: 
              std::cout << "window close event\n";
              return 0;
              break;

          case WindowEvents::KEY_PRESS: 
              std::cout << "key press event\n";
              break;

          case WindowEvents::KEY_RELEASE: 
              std::cout << "key release event\n";
              break;

          case WindowEvents::MOUSE_PRESS: 
              std::cout << "mouse press event\n";
              break;

          case WindowEvents::MOUSE_RELEASE: 
              std::cout << "mouse release event\n";
              break;

          case WindowEvents::MOUSE_MOTION: 
              std::cout << "mouse motion event\n";
              break;

          default: 
              break;
        }
      }
      renderGL();
      xwindow->SwapBuffers();
    }

  } catch (hummstrumm::engine::error::Generic &e)
  {
    std::cout << e.GetHumanReadableMessage() << std::endl;
    return 0;
  }

  #endif
  
  #ifdef HUMMSTRUMM_WINDOWSYSTEM_WINDOWS
  std::cout << "Win32 window with OpenGL/WGL context" << std::endl;
  #endif

  return 0;
}
