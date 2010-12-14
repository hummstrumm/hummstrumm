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
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @author Ricardo Tiago <RTiago@gmail.com>
 * @date 2010-02-06
 *
 * @section Overview
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
 **/

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
class Date;
//class Character;
//class String;
typedef std::string String;
class Number;
}

/**
 * The namespace for container types.  This namespace contains STL-style
 * data structure classes, iterator types, concept maps for the data
 * structures, and generic algorithms that work on data structures.
 */
namespace containers
{
template <typename T>
class List;
//template <typename T>
//class Iterator;
}

/**
 * The namespace for input/output streams.  This namespace contains memory,
 * terminal, file, string, and null streams buffers and stream classes.
 */
namespace streams {}

/**
 * The namespace for the renderer system.
 */
namespace renderer
{
class WindowSystem;
class WindowX11;
}
}

}


#ifndef HUMMSTRUMM_ENGINE_SOURCE
#  include <hummstrummengine/config.h>
#else  // #ifndef HUMMSTRUMM_ENGINE_SOURCE
#  include "config.h"
#endif // #ifndef HUMMSTRUMM_ENGINE_SOURCE

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  define _CRT_SECURE_NO_WARNINGS
#  define NOMINMAX
#  pragma warning(push)
#  pragma warning(disable:4290)
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS

#ifndef HUMMSTRUMM_ENGINE_SOURCE
#  include <hummstrummengine/types/inttypes.hpp>
#  include <hummstrummengine/debug/utils.hpp>
#  include <hummstrummengine/error/error.hpp>
#  include <hummstrummengine/error/generic.hpp>
#  include <hummstrummengine/error/outofmemory.hpp>
#  include <hummstrummengine/error/outofrange.hpp>
#  include <hummstrummengine/error/divisionbyzero.hpp>
#  include <hummstrummengine/error/unicode.hpp>
#  include <hummstrummengine/error/memorycorruption.hpp>
#  include <hummstrummengine/error/invalidparam.hpp>
//#  include <hummstrummengine/error/iterator.hpp>
#  include <hummstrummengine/core/allocationtable.hpp>
//#  include <hummstrummengine/core/pool.hpp>
#  include <hummstrummengine/core/object.hpp>
#  include <hummstrummengine/core/type.hpp>
#  include <hummstrummengine/core/pointer.hpp>
#  include <hummstrummengine/system/platform.hpp>
#  include <hummstrummengine/system/endianness.hpp>
#  include <hummstrummengine/system/processors.hpp>
#  include <hummstrummengine/system/memory.hpp>
#  include <hummstrummengine/system/clock.hpp>
#  include <hummstrummengine/containers/iterator.hpp>
#  include <hummstrummengine/types/date.hpp>
//#  include <hummstrummengine/types/character.hpp>
#  include <hummstrummengine/types/number.hpp>
//#  include <hummstrummengine/types/string.hpp>
#  include <hummstrummengine/debug/log.hpp>
#  include <hummstrummengine/debug/profiler.hpp>
#  include <hummstrummengine/geometry/plane.hpp>
#  include <hummstrummengine/geometry/geomutils.hpp>
#  include <hummstrummengine/geometry/segment.hpp>
#  include <hummstrummengine/geometry/boundingbox.hpp>
#  include <hummstrummengine/geometry/boundingsphere.hpp>
#  include <hummstrummengine/math/vector.hpp>
#  include <hummstrummengine/math/matrice.hpp>
#  include <hummstrummengine/math/quaternion.hpp>
#  include <hummstrummengine/renderer/windowSystem.hpp>
#  ifdef HUMMSTRUMM_WINDOWSYSTEM_X11
#    include <hummstrummengine/renderer/windowX11.hpp>
#  endif // #ifdef HUMMSTRUMM_WINDOWSYSTEM_X11
#  include <hummstrummengine/containers/list.hpp>
// This has to go last.
#  include <hummstrummengine/core/engine.hpp>
// Template and Inline implementations now...
#  include <hummstrummengine/core/pointer.inl>
//#  include <hummstrummengine/core/pool.inl>
#  include <hummstrummengine/containers/list.inl>
#  include <hummstrummengine/system/endianness.inl>
#else  // #ifndef HUMMSTRUMM_ENGINE_SOURCE
#  include "types/inttypes.hpp"
#  include "debug/utils.hpp"
#  include "error/error.hpp"
#  include "error/generic.hpp"
#  include "error/outofmemory.hpp"
#  include "error/outofrange.hpp"
#  include "error/divisionbyzero.hpp"
#  include "error/unicode.hpp"
#  include "error/memorycorruption.hpp"
#  include "error/invalidparam.hpp"
#  include "error/iterator.hpp"
#  include "core/allocationtable.hpp"
//#  include "core/pool.hpp"
#  include "core/object.hpp"
#  include "core/type.hpp"
#  include "core/pointer.hpp"
#  include "system/platform.hpp"
#  include "system/endianness.hpp"
#  include "system/processors.hpp"
#  include "system/memory.hpp"
#  include "system/clock.hpp"
//#  include "containers/iterator.hpp"
#  include "types/date.hpp"
//#  include "types/character.hpp"
#  include "types/number.hpp"
//#  include "types/string.hpp"
#  include "debug/log.hpp"
#  include "debug/profiler.hpp"
#  include "math/mathutils.hpp"
#  include "math/vector.hpp"
#  include "math/matrice.hpp"
#  include "math/quaternion.hpp"
#  include "geometry/geomutils.hpp"
#  include "geometry/plane.hpp"
#  include "geometry/segment.hpp"
#  include "geometry/boundingbox.hpp"
#  include "geometry/boundingsphere.hpp"
#  include "renderer/windowSystem.hpp"
#  ifdef HUMMSTRUMM_WINDOWSYSTEM_X11
#    include "renderer/windowX11.hpp"
#  endif // #ifdef HUMMSTRUMM_WINDOWSYSTEM_X11
#  include "containers/list.hpp"
// This has to go last.
#  include "core/engine.hpp"
// Template and Inline implementations now...
#  include "core/pointer.inl"
//#  include "core/pool.inl"
#  include "containers/list.inl"
#  include "system/endianness.inl"
#endif // #ifndef HUMMSTRUMM_ENGINE_SOURCE

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  pragma warning(pop)
#  ifdef HUMMSTRUMM_ENGINE_SOURCE
#    pragma warning(disable:4290)
#  endif // #ifdef HUMMSTRUMM_ENGINE_SOURCE
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS

#endif // #ifndef HUMMSTRUMM_ENGINE
