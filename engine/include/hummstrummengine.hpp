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
 * engine.  This is the header file included PUBLICLY, no by the source code of
 * the engine.
  * 
 * @file   hummstrummengine.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-01-03
 */

#ifndef HUMMSTRUMM_ENGINE
#define HUMMSTRUMM_ENGINE

/**
 * @mainpage
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
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
 */

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
     * The namespace for the core of the game engine.  This namespace contains
     * the memory manager, the Object/Type system, and the smart pointer.
     */
    namespace core
    {
      class Object;
      class Type;
      class Heap;
    }
    /**
     * The namespace for the basic type classes of the game engine.  This
     * namespace contains type wrapper classes to integrate basic C++ types
     * with the Object/Type system, extended types based on the basic types,
     * and measure types, that support units.
     */
    namespace types
    {
//      class String;
      typedef std::wstring String;
      /**
       * The namespace for the measure types.  This namespace contains classes
       * that represent items that can be measured in units and the Unit class.
       */
      namespace measure;
    }
    /**
     * The namespace for container types.  This namespace contains STL-style
     * data structure classes, iterator types, concept maps for the data
     * structures, and generic algorithms that work on data structures.
     */
    namespace containers;
    /**
     * The namespace for input/output streams.  This namespace contains memory,
     * terminal, file, string, and null streams buffers and stream classes.
     */
    namespace streams;
  }
}

#include "hummstrummengine/config.h"
#include "hummstrummengine/error/error.hpp"
#include "hummstrummengine/error/outofmemory.hpp"
#include "hummstrummengine/core/heap.hpp"
#include "hummstrummengine/core/type.hpp"
#include "hummstrummengine/core/pointer.hpp"
#include "hummstrummengine/core/object.hpp"

#endif // #ifndef HUMMSTRUMM_ENGINE
