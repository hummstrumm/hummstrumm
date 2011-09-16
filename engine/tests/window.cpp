
#define HUMMSTRUMM_ENGINE_SOURCE
#include <iostream>
#include <sstream>
#include "hummstrummengine.hpp"
#include <GL/gl.h>
#include <GL/glu.h>

using namespace hummstrumm::engine::window;
using namespace hummstrumm::engine::system;
using namespace hummstrumm::engine::types;
using namespace hummstrumm::engine::events;
using std::boolalpha;

static GLfloat rotQuad = 0.0f;

int64 start;
int64 freq;

WindowSystem* windowsystem = NULL;
WindowVisualInfo param;
int64 TIME_FOR_EACH_TEST;
bool isTesting = true;
bool shouldRender = false;

unsigned short currentTest = 0;

void 
resizeGL(unsigned int width, unsigned int height)
{                                                     
    if (height == 0)                                  
        height = 1;
 
    glViewport(0, 0, width, height);                  
    glMatrixMode(GL_PROJECTION);                      
    glLoadIdentity();                                 
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}                                                                         
 
void 
initGL()
{
//    glEnable(GL_MULTISAMPLE); 
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);                  
    glEnable(GL_DEPTH_TEST);             
    glDepthFunc(GL_LEQUAL);              
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    rotQuad = 0;                                               
    glFlush();                                                  

}                                                               
 
void 
renderGL()
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
showParameters(WindowVisualInfo &param, const char *title)
{
    std::cout << title << std::endl;
    std::cout << " Fullscreen : " << param.useFullscreen << std::endl;
    std::cout << " Double buffer : " << param.useDoubleBuffer << std::endl;
    std::cout << " Red buffer size: " << param.redSize << std::endl;
    std::cout << " Green buffer size: " << param.greenSize << std::endl;
    std::cout << " Blue buffer size: " << param.blueSize << std::endl;
    std::cout << " Depth buffer size: " << param.depthSize << std::endl;
    std::cout << " Vertical sync: " << param.useVerticalSync << std::endl;
    std::cout << " Width : " << param.width << std::endl;
    std::cout << " Height : " << param.height << std::endl;
    std::cout << " Position : " << param.positionX << "," << param.positionY << std::endl;
    std::cout << " Alpha size: " << param.alphaSize << std::endl;
    std::cout << " Anti-Aliasing : " << param.useAntiAliasing << std::endl;
    if (param.useAntiAliasing)
      std::cout << " Samples : " << param.samples << std::endl;
    if (param.openGLMajorVer != -1)
      std::cout << " Context version: " << param.openGLMajorVer
                << "."
                << param.openGLMinorVer
                << std::endl;
    std::cout << " Offscreen rendering : " << param.useOffScreenRendering << std::endl;
    if (param.useOffScreenRendering)
    {
      std::cout << " Offscreen buffer width : " << param.offscreenBufferWidth << std::endl;
      std::cout << " Offscreen buffer height : " << param.offscreenBufferHeight << std::endl;
      std::cout << " Using largest buffer available: " << param.offscreenUseLargestBufferAvailable << std::endl;
    }
}
  
void
runTest(int n)
{

  std::cout << boolalpha;

  switch(n)
  {
    case 0:
    {     
      param.useFullscreen = false;      
      param.useDoubleBuffer = true;
      param.useVerticalSync = false;
      param.redSize = 8;
      param.greenSize = 8;
      param.blueSize = 8;
      param.alphaSize = 8;
      param.depthSize = 24;
      param.stencilSize = 8;
      param.useAntiAliasing = true;
      param.useOffScreenRendering = true;
      param.offscreenBufferWidth = 256;
      param.offscreenBufferHeight = 256;
      param.offscreenUseLargestBufferAvailable = true;
      param.samples = 8;
    }
    break;

    case 1:
    {
      param.useFullscreen = true;
      param.useDoubleBuffer = true;
      param.useVerticalSync = true;
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;
      param.stencilSize = 0;
      param.width = 1024;
      param.height = 768;
      param.useAntiAliasing = false;
      param.samples = 0;
    }
    break;

    case 2:
    {
      param.useFullscreen = false;
      param.useDoubleBuffer = true;
      param.useVerticalSync = true;
      param.redSize = 8;
      param.greenSize = 8;
      param.blueSize = 8;
      param.depthSize = 24;
      param.stencilSize = 8;
      param.width = 800;
      param.height = 600;
      param.useAntiAliasing = true;
      param.samples = 4;
    }
    break;

    case 3:
    {
      param.useFullscreen = false;
      param.useDoubleBuffer = true;
      param.useVerticalSync = false;
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;
      param.useAntiAliasing = false;
      param.samples = 0;
      param.stencilSize = 0;

      param.width = 200;
      param.height = 200;
    } 
    break;

    case 4:
    {
      param.useFullscreen = true;
      param.useDoubleBuffer = true;
      param.useVerticalSync = false;
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;
      param.width = 500;
      param.height = 200;
      param.useAntiAliasing = false;
      param.samples = 0;
      param.stencilSize = 0;
      param.openGLMajorVer = 1;
      param.openGLMinorVer = 0;
    } 
    break;

    case 5:
    {
      param.useFullscreen = true;
      param.useDoubleBuffer = true;
      param.useVerticalSync = false;
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;
      param.width = 1024;
      param.height = 768;
      param.openGLMajorVer = 3;
      param.openGLMinorVer = 1;
      param.stencilSize = 8;
      param.useAntiAliasing = true;
      param.samples = 8;
    } 
    break;

    case 6:
    {
      param.useFullscreen = false;
      param.width = 800;
      param.height = 600;
    }
    break;

    case 7:
    {
      param.useFullscreen = true;
      param.width = 640;
      param.height = 480;
    }
    break;

    case 8:
    {
      param.useFullscreen = false;
      param.width = 640;
      param.height = 480;
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
    showParameters(param, "Requested parameters");
    if ( n < 6)
    {
      std::cout << "Created new window\n";
      (windowsystem->CreateWindow)(param);
    }
    else
    {
      std::cout << "Reusing same window\n";
      windowsystem->SetMode(param);
    }
    showParameters(param, "Obtained parameters");
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
    if (++currentTest < 6)
    {
      std::cout << "Destroyed window\n";
      windowsystem->DestroyWindow();
    }
    runTest(currentTest);
  }
}

int
main()
{
  hummstrumm::engine::core::Engine engine;

  freq = engine.GetClock ()->GetHighResolutionFrequency();

  TIME_FOR_EACH_TEST = 10 * engine.GetClock()->NANOSECONDS_PER_SECOND;
  try
  {
    std::stringstream logMessage;
    std::cout << "HUMMSTRUMM window testing with OpenGL context" << std::endl;
    windowsystem = new WindowSystem;    
    runTest(0);

    while (isTesting)
    {
      while (windowsystem->GetPendingEventsCount() > 0) 
      {

        WindowEvents *wev = windowsystem->GetNextEvent();
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

          case WindowEvents::WINDOW_ACTIVE:
              std::cout << "Window is active " << std::endl;
              shouldRender = true;
              break;
          case WindowEvents::WINDOW_INACTIVE:
              std::cout << "Window inactive " << std::endl;
              shouldRender = false;
              break;

          default: 
              break;
        }
      }
      if (shouldRender)
      {
        renderGL();
        windowsystem->SwapBuffers();
      }
      checkTestIsOver();
    }
  } catch (HUMMSTRUMM_ERRORNAME(WindowSystem) &e)
  {
    std::cout << "Test #" << currentTest << " failed\n";
    
    std::cout << e.GetHumanReadableMessage() << std::endl;
    return -1;
  }  
  return 0;
}
