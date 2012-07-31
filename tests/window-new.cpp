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
using namespace hummstrumm::engine;
 
#include <iomanip>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>


void initGL ();
void resizeGL (unsigned int, unsigned int);
void renderGL ();

int
main (int, char **)
{
  // Cut down on typing. ^_^
  using namespace debug::logging;
  using namespace std::tr1;

  // Start the engine.
  core::Engine::Configuration params;
  params.logBackends.push_back (
    shared_ptr<Backend> (new FileBackend (Level::info    |
                                          Level::success |
                                          Level::warning |
                                          Level::error, "test-window.log")));
  params.logBackends.push_back (
    shared_ptr<Backend> (new ConsoleBackend (Level::info    |
                                             Level::success |
                                             Level::warning |
                                             Level::error)));
  core::Engine engine (params);
  
  // We want the log to display true/false, not 1/0.
  std::ostream &log = engine.GetLog ();
  log << std::boolalpha;

  // Start the window system.  
  log << HUMMSTRUMM_SET_LOGGING (Level::info)
      << "HUMMSTRUMM window testing with OpenGL context" << std::flush;
  window::WindowSystem *windowSystem = new window::WindowSystem;

  window::WindowVisualInfo param;
  param.useFullscreen   = false;
  param.useDoubleBuffer = true;
  param.useVerticalSync = false;
  param.redSize         = 4;
  param.greenSize       = 4;
  param.blueSize        = 4;
  param.depthSize       = 16;
  param.useAntiAliasing = false;
  param.samples         = 0;
  param.stencilSize     = 0;
  param.width           = 640;
  param.height          = 480;
  (windowSystem->CreateWindow) (param);
  initGL ();
  resizeGL (640, 480);

  for (int i = 0; i < 400; ++i)
    {
      renderGL ();
      windowSystem->SwapBuffers ();
    }

  windowSystem->DestroyWindow ();
  delete windowSystem;
  return 0;
}


void
resizeGL (unsigned int width, unsigned int height)
{
  if (height == 0)
    height = 1;

  glViewport (0, 0, width, height);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (45.0f,
                  static_cast<GLfloat> (width) / static_cast<GLfloat> (height),
                  0.1f, 100.0f);
  glMatrixMode (GL_MODELVIEW);
}


void
initGL ()
{
//  glEnable(GL_MULTISAMPLE);
  glShadeModel (GL_SMOOTH);
  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth (1.0f);
  glEnable (GL_DEPTH_TEST);
  glDepthFunc (GL_LEQUAL);
  glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glFlush ();
}


void
renderGL ()
{
  static GLfloat rotQuad = 0.0f;

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity ();
  glTranslatef (0.0f, 0.0f, -7.0f);
  glRotatef (rotQuad, 1.0f, 0.5f, 0.25f);
  glBegin (GL_QUADS);
    /* top of cube */
    glColor3f  (0.0f, 1.0f, 0.0f);
    glVertex3f (1.0f, 1.0f, -1.0f);
    glVertex3f (-1.0f, 1.0f, -1.0f);
    glVertex3f (-1.0f, 1.0f, 1.0f);
    glVertex3f (1.0f, 1.0f, 1.0f);
    /* bottom of cube */
    glColor3f  (1.0f, 0.5f, 0.0f);
    glVertex3f (1.0f, -1.0f, 1.0f);
    glVertex3f (-1.0f, -1.0f, 1.0f);
    glVertex3f (-1.0f, -1.0f, -1.0f);
    glVertex3f (1.0f, -1.0f, -1.0f);
    /* front of cube */
    glColor3f  (1.0f, 0.0f, 0.0f);
    glVertex3f (1.0f, 1.0f, 1.0f);
    glVertex3f (-1.0f, 1.0f, 1.0f);
    glVertex3f (-1.0f, -1.0f, 1.0f);
    glVertex3f (1.0f, -1.0f, 1.0f);
    /* back of cube */
    glColor3f  (1.0f, 1.0f, 0.0f);
    glVertex3f (-1.0f, 1.0f, -1.0f);
    glVertex3f (1.0f, 1.0f, -1.0f);
    glVertex3f (1.0f, -1.0f, -1.0f);
    glVertex3f (-1.0f, -1.0f, -1.0f);
    /* right side of cube */
    glColor3f  (1.0f, 0.0f, 1.0f);
    glVertex3f (1.0f, 1.0f, -1.0f);
    glVertex3f (1.0f, 1.0f, 1.0f);
    glVertex3f (1.0f, -1.0f, 1.0f);
    glVertex3f (1.0f, -1.0f, -1.0f);
    /* left side of cube */
    glColor3f  (0.0f, 1.0f, 1.0f);
    glVertex3f (-1.0f, 1.0f, 1.0f);
    glVertex3f (-1.0f, 1.0f, -1.0f);
    glVertex3f (-1.0f, -1.0f, -1.0f);
    glVertex3f (-1.0f, -1.0f, 1.0f);
  glEnd ();
  rotQuad += 0.1f;
}
