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

/**
 * Defines the Engine class.
 *
 * @file   core/engine.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-01-03
 * @see    Engine
 */

#ifndef HUMMSTRUMM_ENGINE_CORE_ENGINE
#define HUMMSTRUMM_ENGINE_CORE_ENGINE


namespace hummstrumm
{
namespace engine
{
namespace core
{

/**
 * The class that manages the basic structure of the engine.
 *
 * The engine-wide, automatically created log is contained here.
 *
 * @version 0.3
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-11-22
 * @since 0.3
 */
class Engine
{
  public:
    /**
     * Initializes the entire Humm and Strumm Engine.  A log file is created.
     * The Heap is initialized.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-22
     * @since  0.3
     */
    Engine (void)
      throw (HUMMSTRUMM_ERRORNAME(Generic));
    virtual ~Engine (void);

    /**
     * Returns the Engine.  This is useful to get the Engine in places where the
     * original variable is non-existent.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-24
     * @since  0.3
     *
     * @return The Engine object of the game.
     */
    static Engine *GetEngine (void)
      throw ();

    /**
     * Returns the Log.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @return The Log object.
     */
    hummstrumm::engine::debug::Log *GetLog (void)
      throw ();
    /**
     * Returns the Platform.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-28
     * @since  0.3
     *
     * @return The Platform object.
     */
    hummstrumm::engine::system::Platform *GetPlatform (void)
      throw ();
    /**
     * Returns the Processors.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @return The Processors object.
     */
    hummstrumm::engine::system::Processors *GetProcessors (void)
      throw ();
    /**
     * Returns the Memory.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @return The Memory object.
     */
    hummstrumm::engine::system::Memory *GetMemory (void)
      throw ();
    /**
     * Returns the Endianness.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @return The Endianness object.
     */
    hummstrumm::engine::system::Endianness *GetEndianness (void)
      throw ();
    /**
     * Returns the Clock.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-08-01
     * @since  0.3
     *
     * @return The Clock object.
     */
    hummstrumm::engine::system::Clock *GetClock (void)
      throw ();

  private:
    /// The engine-wide log.
    hummstrumm::engine::debug::Log *log;
    /// Platform information.
    hummstrumm::engine::system::Platform *platform;
    /// Processor information.
    hummstrumm::engine::system::Processors *processors;
    /// Memory information.
    hummstrumm::engine::system::Memory *memory;
    /// Endianness information.
    hummstrumm::engine::system::Endianness *endianness;
    /// High resolution clock information.
    hummstrumm::engine::system::Clock *clock;

    /// The global engine pointer.
    static Engine *theEngine;
};

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_ENGINE
