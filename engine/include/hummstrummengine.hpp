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

/**
 * Includes the files needed by the engine and documents the namespaces of the
 * engine.  This is the header file included PUBLICLY, and by the source code
 * of the engine.
 * 
 * @file   hummstrummengine.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-03
 */

#ifndef HUMMSTRUMM_ENGINE
#define HUMMSTRUMM_ENGINE

/**
 * @mainpage
 * @image  html logo-large.png
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @author Ricardo Tiago <rtiago.mendes@gmail.com>
 * @date   2011-08-03
 *
 * @section overview Overview
 *
 * The Humm and Strumm Game Engine is the game engine for the Humm and Strumm
 * Video Game.
 *
 * The Humm and Strumm Video Game is a free/open source software project.  Our
 * goal is to create a 3D adventure game.  Please see our website, which you
 * can find <a href="http://code.google.com/p/hummstrumm/">here</a>, for more
 * information.
 *
 * This is the complete API reference for the Humm and Strumm Game Engine.
 * The API reference contains the entire specification for the classes and the
 * methods of those classes for use in development.  If you want a higher level
 * description of the game engine, please see the
 * <a href="http://sites.google.com/site/hummstrummdoc/home/humm-and-strumm-engine">
 * game engine design document</a>.
 *
 * We do not recommend you try to start learning how to use the engine by
 * reading this API documentation.  A better way to learn would be to look at
 * the engine design document at the above link, which contains many code
 * samples and tutorials.
 *
 * We have tried to make this documentation as complete as possible, but in the
 * case that it is not, please submit a request to our issue tracker on Google
 * Code with the label "Component-Docs."  If you wish, you can also add a
 * request on the <a href="mailto:hummstrumm-user@googlegroups.com">
 * hummstrumm-user</a> mailing list.
 *
 * @section using Using this API Reference
 *
 * This API reference was generated automatically from the source code of the
 * Humm and Strumm Game Engine using the <a href="www.doxygen.org/">doxygen</a>
 * utility.  If you've used API documentation generated by the tool before, this
 * documentation is not much different.
 *
 * At the top of the documentation is the navigation header and the title.  If
 * you click on the Humm and Strumm logo, you will be taken back to the
 * project's homepage.  Below the logo are the various sections of the
 * documentation.  The first section, the Main Page is where you are right now.
 *
 * The second section contains links to pages that aren't class documentation,
 * but are important in the API reference.  Pages that are here might include a
 * todo list and tutorials for engine usage.
 *
 * The third section contains links to the namespaces defined by the Humm and
 * Strumm Game Engine.  The subsystems of the engine are organized logically
 * into various namespaces, so here is good place to start to learn about a
 * specific subsystem.
 *
 * The fourth section contains links to all the classes defined by the Humm and
 * Strumm Game Engine.  This is useful if you want to look up the documentation
 * of a specific class.
 *
 * The fifth section contains links to all the files included in the Humm and
 * Strumm Game Engine.  Not all functionality of the engine is defined in the
 * classes, and some symbols are present here that are important.  Furthermore,
 * the code of the files is included, sans Doxygen comments, so you can see the
 * structure.
 *
 * The final section contains links to all the directories included in the Humm
 * and Strumm Game Engine.  This is a good way to access various files'
 * documentation if you know where it is located in the source tree.
 */

#include <string>

// The extensive namespace hierarchy in the game engine.

/**
 * The namespace for all of the Humm and Strumm project.  This namespace
 * contains both the engine and the game code.
 */
namespace hummstrumm
{

/**
 * The namespace for the game engine.  This namespace contains the subsystems
 * that the engine needs.
 */
namespace engine
{

/**
 * The namespace for the classes which aid in the debugging of the
 * game.  This namespace contains the logging class.
 */
namespace debug
{
class Log;
class Profiler;
}

/**
 * The namespace for the math classes of the game engine. 
 */
namespace math
{
template <typename T>
class Vector2D;
template <typename T>
class Vector3D;
template <typename T>
class Vector4D;
template <typename T>
class Matrix2D;
template <typename T>
class Matrix3D;
template <typename T>
class Matrix4D;
template <typename T>
class Quaternion;
}

/**
 * The namespace for the geometry classes of the game engine.
 */
namespace geometry
{
template <typename T>
class Plane3D;
template <typename T>
class Segment3D;
template <typename T>
class Segment2D;
template <typename T>
class AABBox3D;
template <typename T>
class AABBox2D;
template <typename T>
class BSphere3D;
}

/**
 * The namespace for the core of the game engine.  This namespace contains
 * the memory manager, the Object/Type system, and the smart pointer.
 */
namespace core
{
class Object;
class Type;
//template <typename T, unsigned int SIZE>
//class Pool;
template <typename T>
class Pointer;
class Engine;
class AllocationTable;
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
class Clock;
}

/**
 * The namespace for the basic type classes of the game engine.  This
 * namespace contains type wrapper classes to integrate basic C++ types
 * with the Object/Type system, extended types based on the basic types,
 * and measure types, that support units.
 */
namespace types
{
typedef std::string String;
}

/**
 * The namespace for date and time related classes.  The main requirement for
 * these classes are that they be programmer-friendly, not that they be
 * comprehensive.
 */
namespace date
{
class Timezone;
class Duration;
class Date;
}

/**
 * The namespace for throwable exceptions.  These classes work together with
 * those of the debug namespace to help produce robust code,
 */
namespace error
{
class Error;
class OutOfMemory;
class OutOfRange;
class DivisionByZero;
class Unicode;
class MemoryCorruption;
class InvalidParam;
class Iterator;
class WindowSystem;
}

/**
 * The namespace for input/output streams.  This namespace contains memory,
 * terminal, file, string, and null streams buffers and stream classes.
 */
namespace streams {}

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

}

#include "config.h"

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  define NOMINMAX
// Microsoft has deprecated CRT functions as "insecure".  Hah, good one guys.
#  pragma warning(disable:4996)
#  pragma warning(push)
#  pragma warning(disable:4290)
// To avoid the do-while(false) trick warnings from the MSVC compiler 
// Credit to Charles Nicholson from cnicholson.net
#  define MULTI_LINE_MACRO_BEGIN do { 
#  define MULTI_LINE_MACRO_END \
    __pragma(warning(push)) \
   	__pragma(warning(disable:4127)) \
    } while(0) \
    __pragma(warning(pop))
#  endif
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS

#include "types/inttypes.hpp"
#include "debug/utils.hpp"
#include "core/object.hpp"
#include "core/type.hpp"
#include "error/error.hpp"
#include "error/generic.hpp"
#include "error/outofmemory.hpp"
#include "error/outofrange.hpp"
#include "error/divisionbyzero.hpp"
#include "error/windowsystem.hpp"
#include "error/unicode.hpp"
#include "error/memorycorruption.hpp"
#include "error/invalidparam.hpp"
#include "error/iterator.hpp"
#include "core/allocationtable.hpp"
#include "core/pointer.hpp"
#include "system/platform.hpp"
#include "system/endianness.hpp"
#include "system/processors.hpp"
#include "system/memory.hpp"
#include "system/clock.hpp"
#include "date/duration.hpp"
#include "date/timezone.hpp"
#include "date/date.hpp"
#include "debug/log.hpp"
#include "debug/profiler.hpp"
#include "math/simd.hpp"
#include "math/mathutils.hpp"
#include "math/vector.hpp"
#include "math/matrice.hpp"
#include "math/quaternion.hpp"
#include "geometry/geomutils.hpp"
#include "geometry/plane.hpp"
#include "geometry/segment.hpp"
#include "geometry/boundingbox.hpp"
#include "geometry/boundingsphere.hpp"
#include "events/windowevents.hpp"
#include "window/windowvisualinfo.hpp"
#include "window/windowsystem.hpp"
// This has to go last.
#include "core/engine.hpp"
// Template and Inline implementations now...
#include "core/pointer.inl"
#include "system/endianness.inl"
#include "date/duration.inl"
#include "date/date.inl"

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  pragma warning(pop)
#  pragma warning(disable:4290)
#endif // #ifndef HUMMSTRUMM_ENGINE
