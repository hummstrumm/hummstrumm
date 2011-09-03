
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

HsWindowSystem* window;
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
showParameters(WindowVisualInfo &param, const char *title)
{
    std::cout << title << std::endl;
    std::cout << " FullScreen : " << param.isFullscreen << std::endl;
    std::cout << " Double Buffer : " << param.isDoubleBuffer << std::endl;
    std::cout << " Red Buffer Size: " << param.redSize << std::endl;
    std::cout << " Green Buffer Size: " << param.greenSize << std::endl;
    std::cout << " Blue Buffer Size: " << param.blueSize << std::endl;
    std::cout << " Depth Buffer Size: " << param.depthSize << std::endl;
    std::cout << " Vertical Sync: " << param.forceVerticalSync << std::endl;
    std::cout << " Width : " << param.width << std::endl;
    std::cout << " Height : " << param.height << std::endl;
    std::cout << " Position : " << param.positionX << "," << param.positionY << std::endl;
    std::cout << " Alpha Size: " << param.alphaSize << std::endl;
    std::cout << " AntiAliasing : " << param.useAntiAliasing << std::endl;
    if (param.useAntiAliasing)
      std::cout << " Samples : " << param.samples << std::endl;
    if (param.openGLMajorVer != -1)
      std::cout << " Context Version: " << param.openGLMajorVer
                << "."
                << param.openGLMinorVer
                << std::endl;
}
  
void
runTest(int n)
{

  std::cout << boolalpha;
  WindowVisualInfo param;

  switch(n)
  {
    case 0:
    {
      param.isFullscreen = false;      
      param.isDoubleBuffer = true;
      param.forceVerticalSync = false;
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;
    }
    break;

    case 1:
    {
      param.isFullscreen = true;
      param.isDoubleBuffer = true;
      param.forceVerticalSync = true;
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;
    }
    break;

    case 2:
    {
      param.isFullscreen = true;
      param.isDoubleBuffer = true;
      param.forceVerticalSync = true;
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;
      param.useAntiAliasing = true;
      param.samples = 2;
    }
    break;

    case 3:
    {
      param.isFullscreen = false;
      param.isDoubleBuffer = true;
      param.forceVerticalSync = false;
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;

      param.width = 200;
      param.height = 200;
    } 
    break;

    case 4:
    {
      param.isFullscreen = true;
      param.isDoubleBuffer = true;
      param.forceVerticalSync = false;
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;
      param.width = 500;
      param.height = 200;
      param.openGLMajorVer = 1;
      param.openGLMinorVer = 0;
    } 
    break;

    case 5:
    {
      param.isFullscreen = true;
      param.isDoubleBuffer = true;
      param.forceVerticalSync = false;
      param.redSize = 4;
      param.greenSize = 4;
      param.blueSize = 4;
      param.depthSize = 16;
      param.width = 1024;
      param.height = 768;
      param.openGLMajorVer = 3;
      param.openGLMinorVer = 1;
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
    window->HsCreateWindow(param);
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
    window->HsDestroyWindow();
    runTest(++currentTest);
  }
}

int
main()
{
  hummstrumm::engine::core::Engine engine;

  freq = engine.GetClock ()->GetHighResolutionFrequency();

  TIME_FOR_EACH_TEST = 15 * engine.GetClock()->NANOSECONDS_PER_SECOND;
  try
  {
    std::stringstream logMessage;
    std::cout << "HUMMSTRUMM window testing with OpenGL context" << std::endl;
    window = new HsWindowSystem;

    runTest(0);

    while (isTesting)
    {
      while (window->HsGetPendingEventsCount() > 0) 
      {
        WindowEvents *wev = window->HsGetNextEvent();
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
      renderGL();
      window->HsSwapBuffers();
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
