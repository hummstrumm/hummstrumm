// -*- mode: c++; c-file-style: hummstrumm -*-
/* Humm and Strumm Video Game
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

namespace hummstrumm
{
namespace engine
{
namespace window
{

#define ATTRIB_MAX 56
#define ATTRIB_ADD1(a, arr)                                                                \
{                                                                                          \
  if (idx >= ATTRIB_MAX) return NULL; arr[idx++] = a;                                      \
}                                                                     

#define ATTRIB_ADD2(a,b, arr)                                                              \
{                                                                                          \
  if (idx+1 >= ATTRIB_MAX) return NULL;                                                    \
  arr[idx++] = a; arr[idx++] = b;                                                          \
}

WindowVisualInfo::WindowVisualInfo ():
  name ("HUMMSTRUMM Window"),
  positionX (0),
  positionY (0),
  height (600),
  width (800),
  useFullscreen (false),
  useDoubleBuffer (true),
  useStereo (false),
  useVerticalSync (false),
  useAntiAliasing (false),
  useOffScreenRendering (false), 
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
  openGLMajorVer (-1),
  openGLMinorVer (-1),
  offscreenBufferWidth (256),
  offscreenBufferHeight (256),
  offscreenUseLargestBufferAvailable (true)
{
  pixelAttributes = NULL;
  contextAttributes = NULL;
}

WindowVisualInfo::WindowVisualInfo (const WindowVisualInfo &param):
  name (param.name),
  positionX (param.positionX),
  positionY (param.positionY),
  height (param.height),
  width (param.width),
  useFullscreen (param.useFullscreen),
  useDoubleBuffer (param.useDoubleBuffer),
  useStereo (param.useStereo),
  useVerticalSync (param.useVerticalSync),
  useAntiAliasing (param.useAntiAliasing),
  useOffScreenRendering (param.useOffScreenRendering),
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
  openGLMajorVer (param.openGLMajorVer),
  openGLMinorVer (param.openGLMinorVer),
  offscreenBufferWidth (param.offscreenBufferWidth),
  offscreenBufferHeight (param.offscreenBufferHeight),
  offscreenUseLargestBufferAvailable (param.offscreenUseLargestBufferAvailable)
{
  delete [] pixelAttributes;
  delete [] contextAttributes;
  pixelAttributes = new int[ATTRIB_MAX];
  contextAttributes = new int[ATTRIB_MAX];
  std::memcpy (pixelAttributes, param.pixelAttributes, ATTRIB_MAX); 
  std::memcpy (contextAttributes, param.contextAttributes, ATTRIB_MAX);
}

WindowVisualInfo::~WindowVisualInfo ()
{
  delete [] pixelAttributes;
  delete [] contextAttributes;
}

int *
WindowVisualInfo::GetContextAttributes ()
{
  if (contextAttributes != NULL)
    return contextAttributes;

  contextAttributes = new int[ATTRIB_MAX];
  int idx = 0;
  if (openGLMajorVer != -1 && openGLMinorVer != -1 )
  {
    #if defined (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
    ATTRIB_ADD2 (WGL_CONTEXT_MAJOR_VERSION_ARB, openGLMajorVer, contextAttributes); 
    ATTRIB_ADD2 (WGL_CONTEXT_MINOR_VERSION_ARB, openGLMinorVer, contextAttributes);
    #else
    ATTRIB_ADD2 (GLX_CONTEXT_MAJOR_VERSION_ARB, openGLMajorVer, contextAttributes); 
    ATTRIB_ADD2 (GLX_CONTEXT_MINOR_VERSION_ARB, openGLMinorVer, contextAttributes);
    #endif
  }
  ATTRIB_ADD1 (0, contextAttributes); 
  return contextAttributes;
}

int *
WindowVisualInfo::GetPixelFormatAttributes (bool offscreen)
{
  if (pixelAttributes != NULL)
    return pixelAttributes; 
  
  pixelAttributes = new int[ATTRIB_MAX];
  int idx = 0;
  #if defined (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
  ATTRIB_ADD2 (WGL_SUPPORT_OPENGL_ARB,   GL_TRUE, pixelAttributes);
  ATTRIB_ADD2 (WGL_ACCELERATION_ARB,     WGL_FULL_ACCELERATION_ARB, pixelAttributes);
  if (offscreen)
    ATTRIB_ADD2 (WGL_DRAW_TO_PBUFFER_ARB,  GL_TRUE, pixelAttributes);
  ATTRIB_ADD2 (WGL_COLOR_BITS_ARB,       bufferSize, pixelAttributes); // minimum
  ATTRIB_ADD2 (WGL_DOUBLE_BUFFER_ARB,    useDoubleBuffer, pixelAttributes); // exact
  ATTRIB_ADD2 (WGL_STEREO_ARB,           useStereo, pixelAttributes); // exact
  ATTRIB_ADD2 (WGL_AUX_BUFFERS_ARB,      auxBuffers, pixelAttributes);  // minimum
  ATTRIB_ADD2 (WGL_RED_BITS_ARB,         redSize, pixelAttributes); // minimum
  ATTRIB_ADD2 (WGL_GREEN_BITS_ARB,       greenSize, pixelAttributes); // minimum
  ATTRIB_ADD2 (WGL_BLUE_BITS_ARB,        blueSize, pixelAttributes); // minimum
  ATTRIB_ADD2 (WGL_ALPHA_BITS_ARB,       alphaSize, pixelAttributes); // minimum
  ATTRIB_ADD2 (WGL_DEPTH_BITS_ARB,       depthSize, pixelAttributes); // minimum
  ATTRIB_ADD2 (WGL_STENCIL_BITS_ARB,     stencilSize, pixelAttributes); // minimum
  ATTRIB_ADD2 (WGL_ACCUM_BITS_ARB,       accumRedSize + 
                                         accumGreenSize + 
                                         accumBlueSize + 
                                         accumAlphaSize, pixelAttributes);
  ATTRIB_ADD2 (WGL_ACCUM_RED_BITS_ARB,   accumRedSize, pixelAttributes);  // minimum
  ATTRIB_ADD2 (WGL_ACCUM_GREEN_BITS_ARB, accumGreenSize, pixelAttributes); // minimum
  ATTRIB_ADD2 (WGL_ACCUM_BLUE_BITS_ARB,  accumBlueSize, pixelAttributes); // minimum
  ATTRIB_ADD2 (WGL_ACCUM_ALPHA_BITS_ARB, accumAlphaSize, pixelAttributes); // minimum
  ATTRIB_ADD2 (WGL_PIXEL_TYPE_ARB,       renderType, pixelAttributes); // exact 
  if (useAntiAliasing)
  {
    ATTRIB_ADD2 (WGL_SAMPLE_BUFFERS_ARB, GL_TRUE, pixelAttributes);
    ATTRIB_ADD2 (WGL_SAMPLES_ARB,        samples, pixelAttributes); 
  }
  #else
//  ATTRIB_ADD2 (GLX_X_RENDERABLE,      GL_TRUE, pixelAttributes);
//  ATTRIB_ADD2 (GLX_X_VISUAL_TYPE,     GLX_TRUE_COLOR, pixelAttributes);
  if (!offscreen) // this needs more investigation
  {
    ATTRIB_ADD2 (GLX_DRAWABLE_TYPE,   GLX_WINDOW_BIT, pixelAttributes);
  }
  else
  {
    ATTRIB_ADD2 (GLX_DRAWABLE_TYPE,   GLX_WINDOW_BIT | GLX_PBUFFER_BIT, pixelAttributes);
  }
  ATTRIB_ADD2 (GLX_BUFFER_SIZE,       bufferSize, pixelAttributes);
  ATTRIB_ADD2 (GLX_DOUBLEBUFFER,      useDoubleBuffer, pixelAttributes);
  ATTRIB_ADD2 (GLX_STEREO,            useStereo, pixelAttributes);
  ATTRIB_ADD2 (GLX_AUX_BUFFERS,       auxBuffers, pixelAttributes); 
  ATTRIB_ADD2 (GLX_RED_SIZE,          redSize, pixelAttributes);
  ATTRIB_ADD2 (GLX_GREEN_SIZE,        greenSize, pixelAttributes);
  ATTRIB_ADD2 (GLX_BLUE_SIZE,         blueSize, pixelAttributes);
  ATTRIB_ADD2 (GLX_ALPHA_SIZE,        alphaSize, pixelAttributes);
  ATTRIB_ADD2 (GLX_DEPTH_SIZE,        depthSize, pixelAttributes);
  ATTRIB_ADD2 (GLX_STENCIL_SIZE,      stencilSize, pixelAttributes);
  ATTRIB_ADD2 (GLX_ACCUM_RED_SIZE,    accumRedSize, pixelAttributes); 
  ATTRIB_ADD2 (GLX_ACCUM_GREEN_SIZE,  accumGreenSize, pixelAttributes);
  ATTRIB_ADD2 (GLX_ACCUM_BLUE_SIZE,   accumBlueSize, pixelAttributes);
  ATTRIB_ADD2 (GLX_ACCUM_ALPHA_SIZE,  accumAlphaSize, pixelAttributes);
  ATTRIB_ADD2 (GLX_RENDER_TYPE,       renderType, pixelAttributes);

  if (useAntiAliasing)
  {
    ATTRIB_ADD2 (GLX_SAMPLE_BUFFERS,  1, pixelAttributes);
    ATTRIB_ADD2 (GLX_SAMPLES,         samples, pixelAttributes); 
  }
  #endif
  ATTRIB_ADD1 (0, pixelAttributes); 
  return pixelAttributes;
}

bool
WindowVisualInfo::SetPixelFormatAttributes (const int* attrib, unsigned short attribSize)
{
  if (attribSize > ATTRIB_MAX)
    return false;

  if (attrib == NULL) 
  {
    pixelAttributes = NULL;
    return true;
  }

  delete [] pixelAttributes;
  pixelAttributes = new int[ATTRIB_MAX];

  std::memcpy (pixelAttributes, attrib, attribSize);
  return true;
}

bool
WindowVisualInfo::SetContextAttributes (const int* ctx, unsigned short ctxSize)
{
  if (ctx == NULL) 
  {
    contextAttributes = NULL;
    return true;
  }

  if (ctxSize > ATTRIB_MAX)
    return false;

  delete [] contextAttributes;
  contextAttributes = new int[ATTRIB_MAX];

  std::memcpy (contextAttributes, ctx, ctxSize);
  
  return true;
}

int *
WindowVisualInfo::GetQueryAttributes (int& sz) const
{
  int idx = 0;
  int* queryAttrib = new int[ATTRIB_MAX];
  #if defined (HUMMSTRUMM_WINDOWSYSTEM_WINDOWS)
  ATTRIB_ADD1 (WGL_DOUBLE_BUFFER_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_STEREO_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_AUX_BUFFERS_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_RED_BITS_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_GREEN_BITS_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_BLUE_BITS_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_ALPHA_BITS_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_DEPTH_BITS_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_STENCIL_BITS_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_ACCUM_RED_BITS_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_ACCUM_GREEN_BITS_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_ACCUM_BLUE_BITS_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_ACCUM_ALPHA_BITS_ARB, queryAttrib);
  ATTRIB_ADD1 (WGL_PIXEL_TYPE_ARB, queryAttrib);
  if (useAntiAliasing)
    ATTRIB_ADD1 (WGL_SAMPLES_ARB, queryAttrib); 
  #endif 
  sz = idx;
  return queryAttrib;
}


}
}
}
