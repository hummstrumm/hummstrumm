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
#define ATTRIB_PIXEL_ADD1(a)                                                               \
{                                                                                          \
  if (pidx >= ATTRIB_MAX) return NULL; pixelDescriptor[pidx++] = a;                        \
}                                                                     

#define ATTRIB_PIXEL_ADD2(a,b)                                                             \
{                                                                                          \
  if (pidx+1 >= ATTRIB_MAX) return NULL;                                                   \
  pixelDescriptor[pidx++] = a; pixelDescriptor[pidx++] = b;                                \
}

#define ATTRIB_CONTEXT_ADD1(a)                                                             \
{                                                                                          \
  if (cidx >= ATTRIB_MAX) return NULL; contextDescriptor[cidx++] = a;                      \
}

#define ATTRIB_CONTEXT_ADD2(a,b)                                                           \
{                                                                                          \
  if (cidx+1 >= ATTRIB_MAX) return NULL;                                                   \
  contextDescriptor[cidx++] = a; contextDescriptor[cidx++] = b;                            \
}

#define ATTRIB_QUERY_ADD(a)                                                             \
{                                                                                       \
  if (qidx+1 >= ATTRIB_MAX) return NULL;                                                \
  queryAttrib[qidx++] = a;                                                              \
}

WindowVisualInfo::WindowVisualInfo ():
  name ("HUMMSTRUMM Window"),
  positionX (0),
  positionY (0),
  height (600),
  width (800),
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
  forceVerticalSync (false),
  useAntiAliasing (false),  
  openGLMajorVer (-1),
  openGLMinorVer (-1)
{
  pixelDescriptor = NULL;
  contextDescriptor = NULL;
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
  forceVerticalSync (param.forceVerticalSync),
  useAntiAliasing (param.useAntiAliasing),
  openGLMajorVer (param.openGLMajorVer),
  openGLMinorVer (param.openGLMinorVer)
{
  delete [] pixelDescriptor;
  delete [] contextDescriptor;
  pixelDescriptor = new int[ATTRIB_MAX];
  contextDescriptor = new int[ATTRIB_MAX];
  std::memcpy (pixelDescriptor, param.pixelDescriptor, ATTRIB_MAX); 
  std::memcpy (contextDescriptor, param.contextDescriptor, ATTRIB_MAX);
}

WindowVisualInfo::~WindowVisualInfo ()
{
  if (pixelDescriptor != NULL)
    delete [] pixelDescriptor;

  if (contextDescriptor != NULL)
    delete [] contextDescriptor;
}

int *
WindowVisualInfo::GetContextDescriptor ()
{
  if (contextDescriptor != NULL)
    return contextDescriptor;

  contextDescriptor = new int[ATTRIB_MAX];
  int cidx = 0;
  #if defined (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
  if (openGLMajorVer != -1 && openGLMinorVer != -1 )
  {
    ATTRIB_CONTEXT_ADD2 (WGL_CONTEXT_MAJOR_VERSION_ARB, openGLMajorVer); 
    ATTRIB_CONTEXT_ADD2 (WGL_CONTEXT_MINOR_VERSION_ARB, openGLMinorVer);
  }
  #else
  ATTRIB_CONTEXT_ADD2 (GLX_CONTEXT_MAJOR_VERSION_ARB, openGLMajorVer); 
  ATTRIB_CONTEXT_ADD2 (GLX_CONTEXT_MINOR_VERSION_ARB, openGLMinorVer);
  #endif
  ATTRIB_CONTEXT_ADD1 (0); 
  return contextDescriptor;
}

int *
WindowVisualInfo::GetPixelFormatDescriptor ()
{
  if (pixelDescriptor != NULL)
    return pixelDescriptor; 
  
  pixelDescriptor = new int[ATTRIB_MAX];
  int pidx = 0;
  #if defined (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
  ATTRIB_PIXEL_ADD2 (WGL_SUPPORT_OPENGL_ARB,   GL_TRUE);
  ATTRIB_PIXEL_ADD2 (WGL_ACCELERATION_ARB,     WGL_FULL_ACCELERATION_ARB);
  ATTRIB_PIXEL_ADD2 (WGL_COLOR_BITS_ARB,       bufferSize); // minimum
  ATTRIB_PIXEL_ADD2 (WGL_DOUBLE_BUFFER_ARB,    isDoubleBuffer); // exact
  ATTRIB_PIXEL_ADD2 (WGL_STEREO_ARB,           isStereo); // exact
  ATTRIB_PIXEL_ADD2 (WGL_AUX_BUFFERS_ARB,      auxBuffers);  // minimum
  ATTRIB_PIXEL_ADD2 (WGL_RED_BITS_ARB,         redSize); // minimum
  ATTRIB_PIXEL_ADD2 (WGL_GREEN_BITS_ARB,       greenSize); // minimum
  ATTRIB_PIXEL_ADD2 (WGL_BLUE_BITS_ARB,        blueSize); // minimum
  ATTRIB_PIXEL_ADD2 (WGL_ALPHA_BITS_ARB,       alphaSize); // minimum
  ATTRIB_PIXEL_ADD2 (WGL_DEPTH_BITS_ARB,       depthSize); // minimum
  ATTRIB_PIXEL_ADD2 (WGL_STENCIL_BITS_ARB,     stencilSize); // minimum
  ATTRIB_PIXEL_ADD2 (WGL_ACCUM_BITS_ARB,       accumRedSize + 
                                               accumGreenSize + 
                                               accumBlueSize + 
                                               accumAlphaSize);
  ATTRIB_PIXEL_ADD2 (WGL_ACCUM_RED_BITS_ARB,   accumRedSize);  // minimum
  ATTRIB_PIXEL_ADD2 (WGL_ACCUM_GREEN_BITS_ARB, accumGreenSize); // minimum
  ATTRIB_PIXEL_ADD2 (WGL_ACCUM_BLUE_BITS_ARB,  accumBlueSize); // minimum
  ATTRIB_PIXEL_ADD2 (WGL_ACCUM_ALPHA_BITS_ARB, accumAlphaSize); // minimum
  ATTRIB_PIXEL_ADD2 (WGL_PIXEL_TYPE_ARB,       renderType); // exact 
  if (useAntiAliasing)
  {
    ATTRIB_PIXEL_ADD2 (WGL_SAMPLE_BUFFERS_ARB, GL_TRUE);
    ATTRIB_PIXEL_ADD2 (WGL_SAMPLES_ARB,        samples); 
  }
  #else
  ATTRIB_PIXEL_ADD2 (GLX_BUFFER_SIZE,      bufferSize);
  ATTRIB_PIXEL_ADD2 (GLX_DOUBLEBUFFER,     isDoubleBuffer);
  ATTRIB_PIXEL_ADD2 (GLX_STEREO,           isStereo);
  ATTRIB_PIXEL_ADD2 (GLX_AUX_BUFFERS,      auxBuffers); 
  ATTRIB_PIXEL_ADD2 (GLX_RED_SIZE,         redSize);
  ATTRIB_PIXEL_ADD2 (GLX_GREEN_SIZE,       greenSize);
  ATTRIB_PIXEL_ADD2 (GLX_BLUE_SIZE,        blueSize);
  ATTRIB_PIXEL_ADD2 (GLX_ALPHA_SIZE,       alphaSize);
  ATTRIB_PIXEL_ADD2 (GLX_DEPTH_SIZE,       depthSize);
  ATTRIB_PIXEL_ADD2 (GLX_STENCIL_SIZE,     stencilSize);
  ATTRIB_PIXEL_ADD2 (GLX_ACCUM_RED_SIZE,   accumRedSize); 
  ATTRIB_PIXEL_ADD2 (GLX_ACCUM_GREEN_SIZE, accumGreenSize);
  ATTRIB_PIXEL_ADD2 (GLX_ACCUM_BLUE_SIZE,  accumBlueSize);
  ATTRIB_PIXEL_ADD2 (GLX_ACCUM_ALPHA_SIZE, accumAlphaSize);
  ATTRIB_PIXEL_ADD2 (GLX_RENDER_TYPE,      renderType);
  ATTRIB_PIXEL_ADD2 (GLX_SAMPLES,          samples);
  #endif
  ATTRIB_PIXEL_ADD1 (0); 
  return pixelDescriptor;
}

bool
WindowVisualInfo::SetPixelFormatDescriptor (const int* desc, unsigned short descSize)
{
  if (desc == NULL) 
  {
    pixelDescriptor = NULL;
    return true;
  }

  if (descSize > ATTRIB_MAX)
    return false;

  delete [] pixelDescriptor;
  pixelDescriptor = new int[ATTRIB_MAX];

  std::memcpy (pixelDescriptor, desc, descSize);
  
  return true;
}

bool
WindowVisualInfo::SetContextDescriptor (const int* ctx, unsigned short ctxSize)
{
  if (ctx == NULL) 
  {
    contextDescriptor = NULL;
    return true;
  }

  if (ctxSize > ATTRIB_MAX)
    return false;

  delete [] contextDescriptor;
  contextDescriptor = new int[ATTRIB_MAX];

  std::memcpy (contextDescriptor, ctx, ctxSize);
  
  return true;
}

int *
WindowVisualInfo::GetQueryAttributes (int& sz) const
{
  int qidx = 0;
  int* queryAttrib = new int[ATTRIB_MAX];
  ATTRIB_QUERY_ADD (WGL_DOUBLE_BUFFER_ARB);
  ATTRIB_QUERY_ADD (WGL_STEREO_ARB);
  ATTRIB_QUERY_ADD (WGL_AUX_BUFFERS_ARB);
  ATTRIB_QUERY_ADD (WGL_RED_BITS_ARB);
  ATTRIB_QUERY_ADD (WGL_GREEN_BITS_ARB);
  ATTRIB_QUERY_ADD (WGL_BLUE_BITS_ARB);
  ATTRIB_QUERY_ADD (WGL_ALPHA_BITS_ARB);
  ATTRIB_QUERY_ADD (WGL_DEPTH_BITS_ARB);
  ATTRIB_QUERY_ADD (WGL_STENCIL_BITS_ARB);
  ATTRIB_QUERY_ADD (WGL_ACCUM_RED_BITS_ARB);
  ATTRIB_QUERY_ADD (WGL_ACCUM_GREEN_BITS_ARB);
  ATTRIB_QUERY_ADD (WGL_ACCUM_BLUE_BITS_ARB);
  ATTRIB_QUERY_ADD (WGL_ACCUM_ALPHA_BITS_ARB);
  ATTRIB_QUERY_ADD (WGL_PIXEL_TYPE_ARB);
  if (useAntiAliasing)
    ATTRIB_QUERY_ADD (WGL_SAMPLES_ARB); 
  sz = qidx;
  return queryAttrib;
}


}
}
}
