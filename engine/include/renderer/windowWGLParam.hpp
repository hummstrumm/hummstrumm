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
 * Definition for Microsoft Windows OpenGL window parameters.
 *
 * @file    windowWGLParam.hpp
 * @author  Ricardo Tiago <Rtiago@gmail.com>
 * @date    2010-09-25
 */

#ifndef HUMMSTRUMM_ENGINE_WINDOW_WGL_PARAMETERS
#define HUMMSTRUMM_ENGINE_WINDOW_WGL_PARAMETERS

namespace hummstrumm
{
namespace engine
{
namespace renderer
{

/**
 * Contains the WGL parameters needed by the window system.
 *
 * @version 0.3
 * @author Ricardo Tiago <Rtiago@gmail.com>
 * @date 2010-09-25
 * @since 0.3
 *
 */
class WindowWGLParam: public WindowParameters
{
  public:
    /**
     * Initializes the WGL parameters to a set of sane default values.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-25
     * @since 0.3
     */
    WindowWGLParam()
      : doubleBuffer(true),
        stereo(false),
        depthBits(16),
        pixelType(PFD_TYPE_RGBA),
        colorBits(16),
        redBits(0),
        redShift(0),
        greenBits(0),
        greenShift(0),
        blueBits(0),
        blueShift(0),
        alphaBits(0),
        alphaShift(0),
        accumBits(0),
        accumRedBits(0),
        accumGreenBits(0),
        accumBlueBits(0),
        accumAlphaBits(0),
        stencilBits(0),
        auxBuffers(0),
        numberOfPlanes(0),
        visibleMask(0) 
    {}
    /**
     * Construct a WindowWGLParam object from another WindowWGLParam object.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-25
     * @since 0.3
     */
    WindowWGLParam(const WindowWGLParam &WGLParam)
      : WindowParameters(WGLParam),
        doubleBuffer(WGLParam.doubleBuffer),
        stereo(WGLParam.stereo),
        depthBits(WGLParam.depthBits),
        pixelType(WGLParam.pixelType),
        colorBits(WGLParam.colorBits),
        redBits(WGLParam.redBits),
        redShift(WGLParam.redShift),
        greenBits(WGLParam.greenBits),
        greenShift(WGLParam.greenShift),
        blueBits(WGLParam.blueBits),
        blueShift(WGLParam.blueShift),
        alphaBits(WGLParam.alphaBits),
        alphaShift(WGLParam.alphaShift),
        accumBits(WGLParam.accumBits),
        accumRedBits(WGLParam.accumRedBits),
        accumGreenBits(WGLParam.accumGreenBits),
        accumBlueBits(WGLParam.accumBlueBits),
        accumAlphaBits(WGLParam.accumAlphaBits),
        stencilBits(WGLParam.stencilBits),
        auxBuffers(WGLParam.auxBuffers),
        numberOfPlanes(WGLParam.numberOfPlanes),
        visibleMask(WGLParam.visibleMask) {}
    /**
     * Destruct an existing WindowWGLParam object.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-25
     * @since 0.3
     */
    virtual ~WindowWGLParam() {}

    /**
     * Gets a pointer to the WGL window parameters.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date 2010-09-25
     * @since 0.3
     * 
     * @return The pointer to parameters array.
     * @note The caller must free the pointer after using it.
     */
    inline virtual HUMMSTRUMM_WINDOW_LIST_POINTER WindowParamList() const
    {
      DWORD flags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
      if (doubleBuffer)
        flags = flags | PFD_DOUBLEBUFFER;
      if (stereo)
        flags = flags | PFD_STEREO;
      if (depthBits == 0)
        flags = flags | PFD_STEREO_DONTCARE;
     
      PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        flags, 
        pixelType,
        colorBits,
        redBits,
        redShift,
        greenBits,
        greenShift,
        blueBits,
        blueShift,
        alphaBits,
        alphaShift,
        accumBits,
        accumRedBits,
        accumGreenBits,
        accumBlueBits,
        accumAlphaBits,
        depthBits,
        stencilBits,
        auxBuffers,
        0,
        numberOfPlanes,
        0,
        visibleMask,
        0
      };

      return pfd;
    }

    /* @note See MSDN for a complete reference */

    /** 
     * If true, only double-buffered are considered. Otherwise, only single-buffered
     * visuals are considered.
     *
     * Defaults to true.
     */
    bool doubleBuffer; 

    /**
     * If true, only stereo visuals are considered. Otherwise, only monoscopic 
     * visuals are considered. 
     *
     * Defaults to false. 
     */
    bool stereo;

    /**
     * Specifies the depth of the depth (z-axis) buffer. Must be followed by a 
     * nonnegative minimum size specification. If this value is 0 it means 
     * PDF_DEPTH_DONTCARE, the request pixel format can be with or without a 
     * depth buffer. Otherwise, only pixel formats with a depth buffer of the 
     * specified size are considered.
     *
     * Defaults to PFD_DEPTH_DONTCARE.
     */
    BYTE depthBits;

    /*
     * Specified the type of pixel data. Valid types are PFD_TYPE_RGBA
     * and PFD_TYPE_COLORINDEX. PFD_TYPE_RGBA means RGBA pixels. Each pixel
     * has four components in this order: red, green, blue, and alpha.
     * PFD_TYPE_COLORINDEX means Color-index pixels. Each pixel uses a 
     * color-index value.
     *
     * Defaults to PFD_TYPE_RGBA.
     */ 
    BYTE pixelType;

    /**
     * Specifies the number of color bitplanes in each color buffer. For RGBA 
     * pixel types, it is the size of the color buffer, excluding the alpha
     * bitplanes. For color-index pixels, it is the size of the color-index buffer.
     */ 
    BYTE colorBits;

    /**
     * Specifies the number of red bitplanes in each RGBA color buffer.
     */ 
    BYTE redBits;

    /**
     * Specifies the shift count for red bitplanes in each RGBA color buffer.
     */ 
    BYTE redShift;

    /**
     * Specifies the number of green bitplanes in each RGBA color buffer.
     */ 
    BYTE greenBits;

    /**
     * Specifies the shift count for green bitplanes in each RGBA color buffer.
     */ 
    BYTE greenShift;

    /**
     * Specifies the number of blue bitplanes in each RGBA color buffer.
     */ 
    BYTE blueBits;

    /**
     * Specifies the shift count for blue bitplanes in each RGBA color buffer.
     */ 
    BYTE blueShift;

    /**
     * Specifies the number of alpha bitplanes in each RGBA color buffer. Alpha 
     * bitplanes are not supported.
     */ 
    BYTE alphaBits;

    /**
     * Specifies the shift count for alpha bitplanes in each RGBA color buffer. 
     * Alpha bitplanes are not supported.
     */ 
    BYTE alphaShift;

    /**
     * Specifies the total number of bitplanes in the accumulation buffer.
     */ 
    BYTE accumBits;

    /**
     * Specifies the number of red bitplanes in the accumulation buffer.
     */ 
    BYTE accumRedBits;

    /**
     * Specifies the number of green bitplanes in the accumulation buffer.
     */ 
    BYTE accumGreenBits;

    /**
     * Specifies the number of blue bitplanes in the accumulation buffer.
     */ 
    BYTE accumBlueBits;

    /**
     * Specifies the number of alpha bitplanes in the accumulation buffer.
     */ 
    BYTE accumAlphaBits;

    /**
     * Specifies the depth of the stencil buffer.
     */ 
    BYTE stencilBits;

    /**
     * Specifies the number of auxiliary buffers. Auxiliary buffers are 
     * not supported (MSDN). Leave it here for when they are supported (if ever).
     *
     * Defaults to 0.
     */ 
    BYTE auxBuffers;

    /**
     * Specifies the number of overlay and underlay planes. Bits 0 through 3
     * specify up to 15 overlay planes and bits 4 through 7 specify up to 15
     * underlay planes.
     */ 
    BYTE numberOfPlanes;

    /**
     * Specifies the transparent color or index of an underlay plane. When the pixel
     * type if RGBA, this variable is a transparent RGB color value. When the pixel 
     * type is color index, it is a transparent index value.
     */ 
    BYTE visibleMask;
};

}
}
}

#endif
