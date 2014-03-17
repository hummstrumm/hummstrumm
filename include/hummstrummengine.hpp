// -*- mode: c++; c-file-style: hummstrumm -*-
/* Humm and Strumm Engine
 * Copyright (C) 2008-2012, 2014, the people listed in the AUTHORS file.
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
 * Includes the files needed by the engine and documents the namespaces of the
 * engine.  This is the header file included PUBLICALLY, and by the source code
 * of the engine.
 *
 * @file   hummstrummengine.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-03
 */

#ifndef HUMMSTRUMM_ENGINE
#define HUMMSTRUMM_ENGINE

#include <string>

/**
 * The namespace for the Humm and Strumm game engine.
 */
namespace hummstrummengine {

/**
 * The namespace for the classes which aid in the debugging of the
 * game.  This namespace contains the logging class.
 */
namespace debug
{
template <typename ClockT, typename DurationT> class Profiler;
/**
 * The namespace for classes that help logging.
 */
namespace logging
{
enum class Level : unsigned;
class StreamBuffer;
class Backend;
class ConsoleBackend;
class FileBackend;
struct SetFile;
struct SetLine;
}
}

/**
 * The namespace for general utility classes that aren't very tightly coupled to
 * the engine.
 */
namespace util
{
/**
 * The namespace for outputting text to the terminal in color.  This currently
 * only works on ANSI terminals.
 */
namespace termcolors
{
enum class Color;
}
}

/**
 * The namespace for the geometry classes of the game engine.
 */
namespace geometry
{
template <typename T> class Plane3D;
template <typename T> class Segment3D;
template <typename T> class Segment2D;
template <typename T> class AABBox3D;
template <typename T> class AABBox2D;
template <typename T> class BSphere3D;
}

/**
 * The namespace for the core of the game engine.
 */
namespace core
{
class Engine;
}

/**
 * The namespace for any direct wrapper of a system concept that does not fit
 * elsewhere in the engine.
 */
namespace system
{
class Platform;
class Endianness;
class Processors;
class Memory;
}

/**
 * The namespace for input/output streams.  This namespace contains memory,
 * terminal, file, string, and null streams buffers and stream classes.
 */
namespace streams
{
}

/**
 * The namespace for the events used by the render system.  Later, this will
 * include the code for the event system.
 */
namespace events
{
class WindowEvents;
class StructureEvents;
class KeyboardEvents;
class MouseEvents;
}

/**
 * The namespace for the window system.
 */
namespace window
{
class WindowVisualInfo;
class WindowSystem;
}
}

#include "config.h"

#ifdef HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS
#define NOMINMAX
// Microsoft has deprecated CRT functions as "insecure".  Hah, good one guys.
#pragma warning(disable : 4996)
#pragma warning(push)
#pragma warning(disable : 4290)
// To avoid the do-while(false) trick warnings from the MSVC compiler
// Credit to Charles Nicholson from cnicholson.net
#define MULTI_LINE_MACRO_BEGIN                                                \
  do                                                                          \
    {
#define MULTI_LINE_MACRO_END                                                  \
  __pragma (warning (push)) __pragma (warning (disable : 4127))               \
  }                                                                           \
  while (0)                                                                   \
  __pragma (warning (pop))
#else
#define MULTI_LINE_MACRO_BEGIN                                                \
  do                                                                          \
    {
#define MULTI_LINE_MACRO_END                                                  \
  }                                                                           \
  while (0)
#endif // #ifdef HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS

#include "debug/utils.hpp"
#include "util/optimizations.hpp"
#include "util/termcolors.hpp"
#include "system/platform.hpp"
#include "system/endianness.hpp"
#include "system/processors.hpp"
#include "system/memory.hpp"
#include "debug/logging/level.hpp"
#include "debug/logging/streambuffer.hpp"
#include "debug/logging/backend.hpp"
#include "debug/logging/manip.hpp"
#include "debug/profiler.hpp"
#include "math/mathutils.hpp"
//#include "geometry/geomutils.hpp"
//#include "geometry/plane.hpp"
//#include "geometry/segment.hpp"
//#include "geometry/boundingbox.hpp"
//#include "geometry/boundingsphere.hpp"
#include "events/windowevents.hpp"
#include "window/windowvisualinfo.hpp"
#include "window/windowsystem.hpp"
// This has to go last.
#include "core/engine.hpp"
// Template and Inline implementations now...
#include "util/termcolors.inl"
#include "system/endianness.inl"
#include "system/memory.inl"
#include "system/platform.inl"
#include "system/processors.inl"
#include "debug/logging/level.inl"
#include "debug/logging/streambuffer.inl"
#include "debug/logging/backend.inl"
#include "debug/logging/manip.inl"
//#include "geometry/boundingbox.inl"
//#include "geometry/boundingsphere.inl"
//#include "geometry/plane.inl"
//#include "geometry/segment.inl"
#include "math/mathutils.inl"

#ifdef HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS
#pragma warning(pop)
#pragma warning(disable : 4290)
#endif /// #ifdef HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS

#endif // #ifndef HUMMSTRUMM_ENGINE
