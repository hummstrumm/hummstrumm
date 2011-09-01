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

namespace hummstrumm
{
namespace engine
{
namespace window
{

#define ATTRIB_MAX 56
#define ATTRIB_ADD1(a) { if (idx >= ATTRIB_MAX) return NULL; descriptor[idx++] = a; }
#define ATTRIB_ADD2(a,b)                                                                \
{                                                                                       \
  if (idx+1 >= ATTRIB_MAX) return NULL; descriptor[idx++] = a; descriptor[idx++] = b;   \
}

WindowVisualInfo::WindowVisualInfo ():
  name ("HUMMSTRUMM Window"),
  positionX (0),
  positionY (0),
  height (512),
  width (512),
  isFullscreen (false),
  isDoubleBuffer (true),
  isStereo (false),
  #if defined (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
  renderType (WGL_TYPE_RGBA_ARB),
  #elif defined (HUMMSTRUMM_WINDOWSYSTEM_X11)
  renderType (GLX_RGBA_BIT),
  #endif 
  depthSize (16),
  bufferSize (0),
  redSize (0),
  greenSize (0),
  blueSize (0),
  alphaSize (0),
  accumRedSize (0),
  accumGreenSize (0),
  accumBlueSize (0),
  accumAlphaSize (0),
  stencilSize (0),
  auxBuffers (0),
  samples (0),
  verticalSync (false) 
{
  descriptor = NULL;
}

WindowVisualInfo::WindowVisualInfo (const WindowVisualInfo &param):
  name (param.name),
  positionX (param.positionX),
  positionY (param.positionY),
  height (param.height),
  width (param.width),
  isFullscreen (param.isFullscreen),
  isDoubleBuffer (param.isDoubleBuffer),
  isStereo (param.isStereo),
  renderType (param.renderType),
  depthSize (param.depthSize),
  bufferSize (param.bufferSize),
  redSize (param.redSize),
  greenSize (param.greenSize),
  blueSize (param.blueSize),
  alphaSize (param.alphaSize),
  accumRedSize (param.accumRedSize),
  accumGreenSize (param.accumGreenSize),
  accumBlueSize (param.accumBlueSize),
  accumAlphaSize (param.accumAlphaSize),
  stencilSize (param.stencilSize),
  auxBuffers (param.auxBuffers),
  samples (param.samples),
  verticalSync (param.verticalSync)
{
  delete [] descriptor;
  descriptor = new int[ATTRIB_MAX];
  std::memcpy (descriptor, param.descriptor, sizeof(param.descriptor));    
}

WindowVisualInfo::~WindowVisualInfo ()
{
  if (descriptor != NULL)
    delete [] descriptor;
}

int *
WindowVisualInfo::GetWindowDescriptor ()
{
  if (descriptor != NULL)
    return descriptor; 
  
  descriptor = new int[ATTRIB_MAX];
  int idx = 0;
  #if defined (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
  ATTRIB_ADD2 (WGL_SUPPORT_OPENGL_ARB,   GL_TRUE);
  ATTRIB_ADD2 (WGL_ACCELERATION_ARB,     WGL_FULL_ACCELERATION_ARB);
  ATTRIB_ADD2 (WGL_COLOR_BITS_ARB,       bufferSize); // minimum
  ATTRIB_ADD2 (WGL_DOUBLE_BUFFER_ARB,    isDoubleBuffer); // exact
  ATTRIB_ADD2 (WGL_STEREO_ARB,           isStereo); // exact
  ATTRIB_ADD2 (WGL_AUX_BUFFERS_ARB,      auxBuffers);  // minimum
  ATTRIB_ADD2 (WGL_RED_BITS_ARB,         redSize); // minimum
  ATTRIB_ADD2 (WGL_GREEN_BITS_ARB,       greenSize); // minimum
  ATTRIB_ADD2 (WGL_BLUE_BITS_ARB,        blueSize); // minimum
  ATTRIB_ADD2 (WGL_ALPHA_BITS_ARB,       alphaSize); // minimum
  ATTRIB_ADD2 (WGL_DEPTH_BITS_ARB,       depthSize); // minimum
  ATTRIB_ADD2 (WGL_STENCIL_BITS_ARB,     stencilSize); // minimum
  ATTRIB_ADD2 (WGL_ACCUM_BITS_ARB,       accumRedSize +  // minimum
                                         accumGreenSize + 
                                         accumBlueSize + 
                                         accumAlphaSize)
  ATTRIB_ADD2 (WGL_ACCUM_RED_BITS_ARB,   accumRedSize);  // minimum
  ATTRIB_ADD2 (WGL_ACCUM_GREEN_BITS_ARB, accumGreenSize); // minimum
  ATTRIB_ADD2 (WGL_ACCUM_BLUE_BITS_ARB,  accumBlueSize); // minimum
  ATTRIB_ADD2 (WGL_ACCUM_ALPHA_BITS_ARB, accumAlphaSize); // minimum
  ATTRIB_ADD2 (WGL_PIXEL_TYPE_ARB,       renderType); // exact 
  ATTRIB_ADD2 (WGL_SAMPLES_ARB,          samples); 
  ATTRIB_ADD1 (0); 
  #else
  ATTRIB_ADD2 (GLX_BUFFER_SIZE,      bufferSize);
  ATTRIB_ADD2 (GLX_DOUBLEBUFFER,     isDoubleBuffer);
  ATTRIB_ADD2 (GLX_STEREO,           isStereo);
  ATTRIB_ADD2 (GLX_AUX_BUFFERS,      auxBuffers); 
  ATTRIB_ADD2 (GLX_RED_SIZE,         redSize);
  ATTRIB_ADD2 (GLX_GREEN_SIZE,       greenSize);
  ATTRIB_ADD2 (GLX_BLUE_SIZE,        blueSize);
  ATTRIB_ADD2 (GLX_ALPHA_SIZE,       alphaSize);
  ATTRIB_ADD2 (GLX_DEPTH_SIZE,       depthSize);
  ATTRIB_ADD2 (GLX_STENCIL_SIZE,     stencilSize);
  ATTRIB_ADD2 (GLX_ACCUM_RED_SIZE,   accumRedSize); 
  ATTRIB_ADD2 (GLX_ACCUM_GREEN_SIZE, accumGreenSize);
  ATTRIB_ADD2 (GLX_ACCUM_BLUE_SIZE,  accumBlueSize);
  ATTRIB_ADD2 (GLX_ACCUM_ALPHA_SIZE, accumAlphaSize);
  ATTRIB_ADD2 (GLX_RENDER_TYPE,      renderType);
  ATTRIB_ADD2 (GLX_SAMPLES,          samples);
  ATTRIB_ADD1 (None);
  #endif
  return descriptor;
}

bool
WindowVisualInfo::SetWindowDescriptor (const int* desc, unsigned short descSize)
{
  if (desc == NULL) 
  {
    descriptor = NULL;
    return true;
  }

  if (descSize > ATTRIB_MAX)
    return false;

  delete [] descriptor;
  descriptor = new int[ATTRIB_MAX];

  std::memcpy (descriptor, desc, sizeof(desc));
  
  return true;
}

}
}
}
