// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2010, the people listed in the AUTHORS file.
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

/**
 * Definition of GLX window parameters.
 * The available configuration options are based on the available GLX version.
 * GLX 1.2 or older only uses the following subset of options. See the
 * description of each option for more information.
 * 
 * @file    renderer/windowGLXParam.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-09-25
 */

#ifndef HUMMSTRUMM_ENGINE_WINDOW_GLX_PARAMETERS
#define HUMMSTRUMM_ENGINE_WINDOW_GLX_PARAMETERS

namespace hummstrumm
{
namespace engine
{
namespace renderer
{

/**
 * Contains the parameters concerning GLX.
 *
 * @version 0.3
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-09-28
 * @since 0.3
 */
struct WindowGLXParam: public WindowParameters
{
    /**
     * Initializes the GLX parameters to a set of sane default values.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     */
    WindowGLXParam(): bufferSize(0),
                      level(0),
                      auxBuffers(0),
                      redSize(0),
                      greenSize(0),
                      blueSize(0),
                      alphaSize(0),
                      depthSize(16),
                      stencilSize(0),
                      doubleBuffer(true),
                      stereo(false),
                      renderType(GLX_RGBA_BIT),
                      drawableType(GLX_WINDOW_BIT),
                      xRenderable(GLX_DONT_CARE),
                      visualType(GLX_DONT_CARE),
                      configCaveat(GLX_DONT_CARE),
                      transparentType(GLX_NONE),
                      transparentIndexValue(GLX_DONT_CARE),
                      transparentRedValue(GLX_DONT_CARE),
                      transparentGreenValue(GLX_DONT_CARE),
                      transparentBlueValue(GLX_DONT_CARE),
                      transparentAlphaValue(GLX_DONT_CARE),
                      accumRedSize(0),
                      accumGreenSize(0),
                      accumBlueSize(0),
                      accumAlphaSize(0),
                      sampleBuffers(0),
                      samples(0) {}

    /**
     * Construct a WindowGLXParam object from another WindowGLXParam object.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     */
    WindowGLXParam(const WindowGLXParam &GLXParam) :
      WindowParameters(GLXParam),
      bufferSize(GLXParam.bufferSize),
      level(GLXParam.level),
      auxBuffers(GLXParam.auxBuffers),
      redSize(GLXParam.redSize),
      greenSize(GLXParam.greenSize),
      blueSize(GLXParam.blueSize),
      alphaSize(GLXParam.alphaSize),
      depthSize(GLXParam.depthSize),
      stencilSize(GLXParam.stencilSize),
      doubleBuffer(GLXParam.doubleBuffer),
      stereo(GLXParam.stereo),
      renderType(GLXParam.renderType),
      drawableType(GLXParam.drawableType),
      xRenderable(GLXParam.xRenderable),
      visualType(GLXParam.visualType),
      configCaveat(GLXParam.configCaveat),
      transparentType(GLXParam.transparentType),
      transparentIndexValue(GLXParam.transparentIndexValue),
      transparentRedValue(GLXParam.transparentRedValue),
      transparentGreenValue(GLXParam.transparentGreenValue),
      transparentBlueValue(GLXParam.transparentBlueValue),
      transparentAlphaValue(GLXParam.transparentAlphaValue),
      accumRedSize(GLXParam.accumRedSize),
      accumGreenSize(GLXParam.accumGreenSize),
      accumBlueSize(GLXParam.accumBlueSize),
      accumAlphaSize(GLXParam.accumAlphaSize),
      sampleBuffers(GLXParam.sampleBuffers),
      samples(GLXParam.samples) {}
 

    /**
     * Destruct an existing WindowGLXParam object.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     */
    virtual ~WindowGLXParam() {}


    /**
     * Gets a pointer to the GLX window parameters to be used with
     * glXChooseVisual.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-28
     * @since 0.3
     * 
     * @return The pointer to parameters array.
     * @note The caller must free the pointer after using it.
     */
    inline virtual HUMMSTRUMM_WINDOW_LIST_POINTER WindowParamList() const 
    {
      int idx = 0;
      const unsigned max_attributes = 56;
      HUMMSTRUMM_WINDOW_LIST_POINTER attrib = new int[max_attributes];
      if (attrib == NULL)
        return NULL;
      if (bufferSize)
        {
          attrib[idx++] = GLX_BUFFER_SIZE;
          attrib[idx++] = bufferSize;
        }
      if (level)
        {
          attrib[idx++] = GLX_LEVEL;
          attrib[idx++] = level;
        }
      if (doubleBuffer)
        {
          attrib[idx++] = GLX_DOUBLEBUFFER;
          attrib[idx++] = doubleBuffer;
        }
      if (stereo)
        {
          attrib[idx++] = GLX_STEREO;
          attrib[idx++] = stereo;
        }
      if (auxBuffers)
        {
          attrib[idx++] = GLX_AUX_BUFFERS;
          attrib[idx++] = auxBuffers;
        }
      if (redSize)
        {
          attrib[idx++] = GLX_RED_SIZE;
          attrib[idx++] = redSize;
        }
      if (greenSize)
        {
          attrib[idx++] = GLX_GREEN_SIZE;
          attrib[idx++] = greenSize;
        }
      if (blueSize)
        {
          attrib[idx++] = GLX_BLUE_SIZE;
          attrib[idx++] = blueSize;
        }
      if (alphaSize)
        {
          attrib[idx++] = GLX_ALPHA_SIZE;
          attrib[idx++] = alphaSize;
        }
      if (depthSize)
        {
          attrib[idx++] = GLX_DEPTH_SIZE;
          attrib[idx++] = depthSize;
        }
      if (stencilSize)
        {
          attrib[idx++] = GLX_STENCIL_SIZE;
          attrib[idx++] = stencilSize;
        }
      if (accumRedSize)
        {
          attrib[idx++] = GLX_ACCUM_RED_SIZE;
          attrib[idx++] = accumRedSize;
        }
      if (accumGreenSize)
        {
          attrib[idx++] = GLX_ACCUM_GREEN_SIZE;
          attrib[idx++] = accumGreenSize;
        }
      if (accumBlueSize)
        {
          attrib[idx++] = GLX_ACCUM_BLUE_SIZE;
          attrib[idx++] = accumBlueSize;
        }
      if (accumAlphaSize)
        {
          attrib[idx++] = GLX_ACCUM_ALPHA_SIZE;
          attrib[idx++] = accumAlphaSize;
        }
      if (sampleBuffers)
        {
          attrib[idx++] = GLX_SAMPLE_BUFFERS;
          attrib[idx++] = sampleBuffers;
        }
      if (samples)
        {
          attrib[idx++] = GLX_SAMPLES;
          attrib[idx++] = samples;
        }
      
      if (renderType != GLX_RGBA_BIT) 
        {
          attrib[idx++] = GLX_RENDER_TYPE;
          attrib[idx++] = renderType;
        }
      if (drawableType != GLX_WINDOW_BIT)
        {
          attrib[idx++] = GLX_DRAWABLE_TYPE;
          attrib[idx++] = drawableType;
        }
      if (xRenderable != GLX_DONT_CARE)
        {
          attrib[idx++] = GLX_X_RENDERABLE;
          attrib[idx++] = xRenderable;
        }
      if (visualType != GLX_DONT_CARE)
        {
          attrib[idx++] = GLX_X_VISUAL_TYPE;
          attrib[idx++] = visualType;
        }
      if (configCaveat != GLX_DONT_CARE)
        {
          attrib[idx++] = GLX_CONFIG_CAVEAT;
          attrib[idx++] = configCaveat;
        }
      if (transparentType != GLX_NONE)
        {
          attrib[idx++] = GLX_TRANSPARENT_TYPE;
          attrib[idx++] = transparentType;
        }
      if (transparentIndexValue != GLX_DONT_CARE)
        {
          attrib[idx++] = GLX_TRANSPARENT_INDEX_VALUE;
          attrib[idx++] = transparentIndexValue;
        }
      if (transparentRedValue != GLX_DONT_CARE)
        {
          attrib[idx++] = GLX_TRANSPARENT_RED_VALUE;
          attrib[idx++] = transparentRedValue;
        }
      if (transparentGreenValue != GLX_DONT_CARE)
        {
          attrib[idx++] = GLX_TRANSPARENT_GREEN_VALUE;
          attrib[idx++] = transparentGreenValue;
        }
      if (transparentBlueValue != GLX_DONT_CARE)
        {
          attrib[idx++] = GLX_TRANSPARENT_BLUE_VALUE;
          attrib[idx++] = transparentBlueValue;
        }
      if (transparentAlphaValue != GLX_DONT_CARE)
        {
          attrib[idx++] = GLX_TRANSPARENT_ALPHA_VALUE;
          attrib[idx++] = transparentAlphaValue;
        }
      attrib[idx++] = None;
    
      return attrib;
    }

    // GLXFBConfig attributes

    /**
     * The render type.  Must be followed by a mask indicating which OpenGL
     * rendering modes the frame buffer configuration must support. Valid bits
     * are GLX_RGBA_BIT and GLX_COLOR_INDEX_BIT. If the mask is set to
     * GLX_RGBA_BIT | GLX_COLOR_INDEX_BIT, then only frame buffer configurations
     * that can be bound to both RGBA contexts and color index contexts will be
     * considered.
     */                
    int renderType;
    /**
     * The drawable type.  Must be followed by a mask indicating which GLX
     * drawable types the frame buffer configuration must support. Valid bits
     * are GLX_WINDOW_BIT, GLX_PIXMAP_BIT, and GLX_PBUFFER_BIT.  For example, if
     * mask is set to GLX_WINDOW_BIT | GLX_PIXMAP_BIT,  only frame buffer
     * configurations that support both windows and GLX pixmaps will be
     * considered.
     */
    int drawableType;
    /**
     * The Renderable object for X11.  Must be followed by True or False. If
     * True is specified, then only frame buffer configurations that have
     * associated X visuals (and can be used to render to Windows and/or GLX
     * pixmaps) will be considered.
     */
    int xRenderable;
    /**
     * The visual type.  Must be followed by one of GLX_TRUE_COLOR,
     * GLX_DIRECT_COLOR, GLX_PSEUDO_COLOR, GLX_STATIC_COLOR, GLX_GRAY_SCALE, or
     * GLX_STATIC_GRAY, indicating the desired X visual type.  Not all frame
     * buffer configurations have an associated X visual. If GLX_DRAWABLE_TYPE
     * is specified in attrib_list and the mask that follows does not have
     * GLX_WINDOW_BIT set, then this value is ignored. It is also ignored if
     * GLX_X_RENDERABLE is specified as False. RGBA rendering may be supported
     * for visuals of type GLX_TRUE_COLOR, GLX_DIRECT_COLOR, GLX_PSEUDO_COLOR,
     * or GLX_STATIC_COLOR, but color index rendering is only supported for
     * visuals of type GLX_PSEUDO_COLOR or GLX_STATIC_COLOR (i.e.,
     * single-channel visuals). The tokens GLX_GRAY_SCALE and GLX_STATIC_GRAY
     * will not match current OpenGL enabled visuals, but are included for
     * future use.
     */
    int visualType;
    /**
     * A param regarding the configuration process.  Must be followed by one of
     * GLX_NONE, GLX_SLOW_CONFIG, GLX_NON_CONFORMANT_CONFIG. If GLX_NONE is
     * specified, then only frame buffer configurations with no caveats will be
     * considered; if GLX_SLOW_CONFIG is specified, then only slow frame buffer
     * configurations will be considered; if GLX_NON_CONFORMANT_CONFIG is
     * specified, then only nonconformant frame buffer configurations will be
     * considered.
     */
    int configCaveat;
    /**
     * This attribute indicates whether or not the configuration supports
     * transparency, and if it it does support transparency, what type of
     * transparency is available.
     */
    int transparentType;
    /**
     * Must be followed by an integer value indicating the transparent index
     * value; the value must be between 0 and the maximum frame buffer value for
     * indices. Only frame buffer configurations that use the specified
     * transparent index value  will be considered.  This attribute is ignored
     * unless GLX_TRANSPARENT_TYPE  is included in attribibute list and
     * specified as GLX_TRANSPARENT_INDEX.
     */                    
    int transparentIndexValue;
    /**
     * Must be followed by an integer value indicating the transparent red
     * value; the value must be between 0 and the maximum frame buffer value for
     * red. Only frame buffer configurations that use the specified transparent
     * red value will be considered.  This attribute is ignored unless
     * GLX_TRANSPARENT_TYPE is included in attribute list and specified as
     * GLX_TRANSPARENT_RGB.
     */                    
    int transparentRedValue;
    /**
     * Must be followed by an integer value indicating the transparent green
     * value; the value must be between 0 and the maximum frame buffer value for
     * green.  Only frame buffer configurations that use the specified
     * transparent green value will be considered.  This attribute is ignored
     * unless GLX_TRANSPARENT_TYPE is included in attribute list and specified
     * as GLX_TRANSPARENT_RGB.
     */
    int transparentGreenValue;
    /**
     * Must be followed by an integer value indicating the transparent blue
     * value; the value must be between 0 and the maximum frame buffer value for
     * blue. Only frame buffer configurations that use the specified transparent
     * blue value will be considered.  This attribute is ignored unless
     * GLX_TRANSPARENT_TYPE is included in attribute list  and specified as
     * GLX_TRANSPARENT_RGB.
     */
    int transparentBlueValue;
    /**
     * Must be followed by an integer value indicating the transparent alpha
     * value; the value must be between 0 and the maximum frame buffer value for
     * alpha.  Only frame buffer configurations that use the specified
     * transparent alpha value will be considered.
     */                    
    int transparentAlphaValue;
    /**
     * If true, only double-buffered visuals are considered. Otherwise, only
     * single-buffered visuals are considered.
     *
     * Used in GLX version 1.2 and above. Defaults to true.
     */
    bool doubleBuffer;
    /**
     * If true, only stereo visuals are considered. Otherwise, only monoscopic 
     * visuals are considered. 
     *
     * Used in GLX version 1.2 and above. Defaults to false. 
     */
    bool stereo;
    /**
     * Must be followed by a nonnegative integer that indicates the desired 
     * color index buffer size. The smallest index buffer of at least the 
     * specified size is preferred. Ignored if GLX_RGBA is asserted. 
     *
     * Used in GLX version 1.2 and above. Defaults 0.
     */
    int bufferSize;
    /**
     * Must be followed by an integer buffer-level specification. This 
     * specification is honored exactly. Buffer level zero corresponds to 
     * the main frame buffer of the display. Buffer level one is the first 
     * overlay frame buffer, level two the second overlay frame buffer, 
     * and so on. Negative buffer levels correspond to underlay frame buffers.
     * 
     * Used in GLX version 1.2 and above. Defaults to 0.
     */
    int level;
    /**
     * Must be followed by a nonnegative integer that indicates the desired
     * number of auxiliary buffers. Visuals with the smallest number of
     * auxiliary buffers that meets or exceeds the specified number are
     * preferred.
     *
     * Used in GLX version 1.2 and above. Defaults to 0.
     */
    int auxBuffers;
    /**
     * Must be followed by a nonnegative minimum size specification. If this
     * value is zero, the smallest available red buffer is preferred. Otherwise,
     * the largest available red buffer of at least the minimum size is
     * preferred.
     *
     * Used in GLX version 1.2 and above. Defaults to 0.
     */
    int redSize;
    /**
     * Must be followed by a nonnegative minimum size specification. If this
     * value is zero, the smallest available green buffer is
     * preferred. Otherwise, the largest available green buffer of at least the
     * minimum size is preferred.
     *
     * Used in GLX version 1.2 and above. Defaults to 0.
     */
    int greenSize;
    /**
     * Must be followed by a nonnegative minimum size specification. If this
     * value is zero, the smallest available blue buffer is
     * preferred. Otherwise, the largest available blue buffer of at least the
     * minimum size is preferred.
     *
     * Used in GLX version 1.2 and above. Defaults to 0.
     */
    int blueSize;
    /**
     * Must be followed by a nonnegative minimum size specification. If this
     * value is zero, the smallest available alpha buffer is
     * preferred. Otherwise, the largest available alpha buffer of at least the
     * minimum size is preferred.
     *
     * Used in GLX version 1.2 and above. Defaults to 0.
     */
    int alphaSize;
    /**
     * Must be followed by a nonnegative minimum size specification. If this
     * value is zero, visuals with no depth buffer are preferred. Otherwise, the
     * largest available depth buffer of at least the minimum size is preferred.
     *
     * Used in GLX version 1.2 and above. Defaults to 0.
     */
    int depthSize;
    /**
     * Must be followed by a nonnegative integer that indicates the desired
     * number of stencil bitplanes. The smallest stencil buffer of at least the
     * specified size is preferred. If the desired value is zero, visuals with
     * no stencil buffer are preferred.
     *
     * Used in GLX version 1.2 and above. Defaults to 0.
     */
    int stencilSize;
    /**
     * Must be followed by a nonnegative minimum size specification. If this
     * value is zero, visuals with no red accumulation buffer are preferred.
     * Otherwise, the largest possible red accumulation buffer of at least the
     * minimum size is preferred.
     * 
     * Used in GLX version 1.2 and above. Defaults to 0. 
     */
    int accumRedSize;
    /**
     * Must be followed by a nonnegative minimum size specification. If this
     * value is zero, visuals with no green accumulation buffer are preferred.
     * Otherwise, the largest possible green accumulation buffer of at least the
     * minimum size is preferred.
     *
     * Used in GLX version 1.2 and above. Defaults to 0. 
     */
    int accumGreenSize;
    /**
     * Must be followed by a nonnegative minimum size specification. If this
     * value is zero, visuals with no blue accumulation buffer are
     * preferred. Otherwise, the largest possible blue accumulation buffer of at
     * least the minimum size is preferred.
     *
     * Used in GLX version 1.2 and above. Defaults to 0. 
     */
    int accumBlueSize;
    /**
     * Must be followed by a nonnegative minimum size specification. If this
     * value is zero, visuals with no alpha accumulation buffer are preferred.
     * Otherwise, the largest possible alpha accumulation buffer of at least the
     * minimum size is preferred.
     *
     * Used in GLX version 1.2 and above. Defaults to 0. 
     */
    int accumAlphaSize;
    /**
     * This attribute indicates the number of multisample buffers, which must be
     * zero or one. If this attribute is zero, then samples will also be zero.
     * If this is one, then the number of color, depth, and stencil bits for
     * each sample in the multisample buffer are as specified by the size
     * attributes.
     *
     * Used in GLX version 1.2 and above. Defaults to 0.
     */
    int sampleBuffers;
    /**
     * The attribute samples gives the number of samples per pixel. 
     *
     * Used in GLX version 1.2 and above. Defaults to 0.
     */
    int samples;
    // http://publib.boulder.ibm.com/infocenter/pseries/v5r3/topic/com.ibm.aix.opengl/doc/openglrf/glXChooseFBConfig.htm
    /**
     * This attribute indicates the maximum width that can be passed into
     * glXCreatePbuffer.  This attribute is ignored by glXChooseFBConfig.
     */
    int maxPbufferWidth; 
    /**
     * This attribute indicates the maximum height that can be passed into
     * glXCreatePbuffer. This attribute is ignored by glXChooseFBConfig.
     */ 
    int maxPbufferHeight;
    /**
     * This attribute indicates the maximum number of pixels (width*height) ofr
     * a GLXPbuffer. This attribute is ignored by glXChooseFBConfig.
     */ 
    int maxPbufferPixels;
};

}
}
}
#endif
