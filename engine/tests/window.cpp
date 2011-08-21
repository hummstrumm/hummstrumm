
#define HUMMSTRUMM_ENGINE_SOURCE
#include <iostream>
#include <sstream>
#include "hummstrummengine.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#ifndef HUMMSTRUMM_PLATFORM_WINDOWS
#include <unistd.h>
#include <signal.h>
#include <GL/glx.h>
#endif // #ifndef HUMMSTRUMM_PLATFORM_WINDOWS



using namespace hummstrumm::engine::renderer;
using namespace hummstrumm::engine::system;
using namespace hummstrumm::engine::types;
using std::boolalpha;

static GLfloat rotQuad = 0.0f;
#if defined (HUMMSTRUMM_WINDOWSYSTEM_X11)
static WindowX11* xwindow;
#elif defined (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
static WindowMSWin* mswindow;
#endif

int64 start;
int64 freq;

int64 TIME_FOR_EACH_TEST;
bool isTesting = true;

unsigned short currentTest = 0;

void resizeGL(unsigned int width, unsigned int height)
{                                                     
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
initializeTest(int n)
{

  std::cout << boolalpha;

  #if defined (HUMMSTRUMM_WINDOWSYSTEM_X11)
  WindowGLXParam param = WindowGLXParam();
  #elif defined (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
  WindowWGLParam param = WindowWGLParam();
  #endif

  switch(n)
  {
    case 0:
    {
      param.SetFullscreen(false);      
      param.doubleBuffer = true;
      param.depthBits = 16;
      #ifdef HUMMSTRUMM_WINDOWSYSTEM_X11
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;
      #endif
    }
    break;

    case 1:
    {
      param.SetFullscreen(true);
      param.doubleBuffer = true;
      #ifdef HUMMSTRUMM_WINDOWSYSTEM_X11
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;
      #endif
    }
    break;

    case 2:
    {
      param.SetFullscreen(false);
      param.doubleBuffer = true;
      #ifdef HUMMSTRUMM_WINDOWSYSTEM_X11
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;
      #endif

      param.SetWidth(200);
      param.SetHeight(200);
    } 
    break;

    default:   
      isTesting = false;
      break;
  }

  if (isTesting)
  {

    start = hummstrumm::engine::core::Engine::
      GetEngine ()->GetClock ()->GetHighResolutionCount();

    std::cout << "Test #" << n << std::endl;
    std::cout << " FullScreen : " << param.IsFullscreen() << std::endl;
    std::cout << " Double Buffer : " << param.doubleBuffer << std::endl;
    #if defined (HUMMSTRUMM_WINDOWSYSTEM_X11)
    std::cout << " Red Buffer Size: " << param.redSize << std::endl;
    std::cout << " Green Buffer Size: " << param.greenSize << std::endl;
    std::cout << " Blue Buffer Size: " << param.blueSize << std::endl;
    std::cout << " Depth Buffer Size: " << param.depthSize << std::endl;
    xwindow->MakeWindow(param);
    #elif defined (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
    mswindow->MakeWindow(param);
    resizeGL(512,512);
    #endif
    initGL();
  }

}

void
checkTestIsOver()
{
  int64 end = hummstrumm::engine::core::Engine::
    GetEngine ()->GetClock ()->GetHighResolutionCount();

  if ( (end - start) > TIME_FOR_EACH_TEST )
  {
    std::cout << "Test ended\n";
    #if defined (HUMMSTRUMM_WINDOWSYSTEM_X11)
    xwindow->DisposeWindow();
    #elif defined (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
    mswindow->DisposeWindow();
    #endif
    initializeTest(++currentTest);

  }
}


int
main()
{
  hummstrumm::engine::core::Engine engine;

  freq = engine.GetClock ()->GetHighResolutionFrequency();

  TIME_FOR_EACH_TEST = 5 * engine.GetClock()->NANOSECONDS_PER_SECOND;
  #ifdef HUMMSTRUMM_WINDOWSYSTEM_X11
  try
  {
    std::stringstream logMessage;
    std::cout << "HUMMSTRUMM X11 window testing with OpenGL/GLX context" << std::endl;
    xwindow = new WindowX11();

    initializeTest(0);

    while (1)
    {
      while (xwindow->GetPendingEventsCount() > 0) 
      {
        WindowEvents *wev = xwindow->GetNextEvent();
        StructureEvents *wsv = NULL;
        switch(wev->getType())
        {
          case WindowEvents::WINDOW_RESIZE: 
              wsv = (StructureEvents *) wev;
              logMessage.str("");
              logMessage << "Window Event : RESIZE ( w ";
              logMessage << wsv->GetWidth();
              logMessage << ", h ";
              logMessage << wsv->GetHeight();
              logMessage << " )";
              HUMMSTRUMM_LOG(logMessage.str().c_str(), MESSAGE);
              resizeGL(wsv->GetWidth(), wsv->GetHeight());
              break;

          case WindowEvents::WINDOW_CLOSE: 
              logMessage.str("");
              logMessage << "Window Event : CLOSE";
              HUMMSTRUMM_LOG(logMessage.str().c_str(), MESSAGE);
              break;

          case WindowEvents::KEY_PRESS:
              logMessage.str("");
              logMessage << "Window Event : KEY PRESS";
              break;

          case WindowEvents::KEY_RELEASE:
              logMessage.str("");
              logMessage << "Window Event : KEY RELEASE";
              break;

          case WindowEvents::MOUSE_PRESS:
              logMessage.str("");
              logMessage << "Window Event : MOUSE PRESS";
              break;

          case WindowEvents::MOUSE_RELEASE:
              logMessage.str("");
              logMessage << "Window Event : MOUSE RELEASE";
              break;

          case WindowEvents::MOUSE_MOTION:
              logMessage.str("");
              logMessage << "Window Event : MOUSE MOTION";
              break;

          default: 
              break;
        }
      }
      if (!isTesting)
        break;

      renderGL();
      xwindow->ExchangeBuffers();
      checkTestIsOver();
    }
  } catch (HUMMSTRUMM_ERRORNAME(Generic) &e)
  {
    std::cout << "Test #" << currentTest << " failed";

    std::cout << e.GetHumanReadableMessage() << std::endl;

    return 0;
  }
  #endif
  
  #ifdef HUMMSTRUMM_WINDOWSYSTEM_WINDOWS
  try
  {
    std::stringstream logMessage;
    std::cout << "HUMMSTRUMM Microsoft Windows window with OpenGL/WGL context" << std::endl;
    mswindow = new WindowMSWin();

    initializeTest(0);

    while (isTesting)
    {
      while (mswindow->GetPendingEventsCount() > 0) 
      {
        WindowEvents *wev = mswindow->GetNextEvent();
        StructureEvents *wsv = NULL;
        switch(wev->getType())
        {
          case WindowEvents::WINDOW_RESIZE:
          { 
              wsv = (StructureEvents *) wev;
              logMessage.str("");
              logMessage << "Window Event : RESIZE ( w ";
              logMessage << wsv->GetWidth();
              logMessage << ", h ";
              logMessage << wsv->GetHeight();
              logMessage << " )";
              HUMMSTRUMM_LOG(logMessage.str().c_str(), MESSAGE);
              std::cout << "Resize event\n";
              resizeGL(wsv->GetWidth(), wsv->GetHeight());
          }
          break;

          case WindowEvents::WINDOW_CLOSE:
          {
              logMessage.str("");
              logMessage << "Window Event : CLOSE";
              HUMMSTRUMM_LOG(logMessage.str().c_str(), MESSAGE);
          }
          break;

          case WindowEvents::KEY_PRESS:
          {
              logMessage.str("");
              logMessage << "Window Event : KEY PRESS";
          }
          break;

          case WindowEvents::KEY_RELEASE:
          {
              logMessage.str("");
              logMessage << "Window Event : KEY RELEASE";
          }
          break;

          case WindowEvents::MOUSE_PRESS:
          {
              logMessage.str("");
              logMessage << "Window Event : MOUSE PRESS";
          }
          break;

          case WindowEvents::MOUSE_RELEASE:
          {
              logMessage.str("");
              logMessage << "Window Event : MOUSE RELEASE";
          }
          break;

          case WindowEvents::MOUSE_MOTION:
          {
              logMessage.str("");
              logMessage << "Window Event : MOUSE MOTION";
          }
          break;

          default: 
              break;
        }
      }
      renderGL();
      mswindow->ExchangeBuffers();
      checkTestIsOver();
    }
  } catch (HUMMSTRUMM_ERRORNAME(WindowSystem) &e)
  {
    std::cout << "Test #" << currentTest << " failed" << std::endl;

    std::cout << e.GetHumanReadableMessage() << std::endl;

    return 0;
  } 
  #endif

  return 0;
}
