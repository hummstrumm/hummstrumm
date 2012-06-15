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
 * The class that manages the basic structure of the engine.  This class manages
 * the game loop, holds the engine wide log, and provides system information.
 *
 * @version 0.3
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-11-22
 * @since   0.3
 */
class Engine
{
  public:
    /**
     * The parameters with which to initialize the Engine.  This is passed to
     * the Engine during its initialization phase.
     *
     * @version 0.5
     * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date    2012-02-13
     * @since   0.5
     */
    struct Configuration
    {
        /// A file to which, by default, to log engine messages.
        hummstrumm::engine::debug::Log::Ptr log;
    };

    /**
     * Initializes the entire Humm and Strumm Engine with specified parameters.
     * The Heap is initialized.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-02-13
     * @since  0.5
     */
    Engine (const Configuration &params);
    /**
     * Shuts down the Humm and Strumm Engine.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-02-13
     * @since  0.5
     */
    virtual ~Engine ();

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
    static Engine *GetEngine ()
      /* noexcept */;

    /**
     * Returns the Log.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @return The Log object.
     */
    hummstrumm::engine::debug::Log::Ptr GetLog ()
      /* noexcept */;
    /**
     * Returns the Platform.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-28
     * @since  0.3
     *
     * @return The Platform object.
     */
    hummstrumm::engine::system::Platform *GetPlatform ()
      /* noexcept */;
    /**
     * Returns the Processors.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @return The Processors object.
     */
    hummstrumm::engine::system::Processors *GetProcessors ()
      /* noexcept */;
    /**
     * Returns the Memory.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @return The Memory object.
     */
    hummstrumm::engine::system::Memory *GetMemory ()
      /* noexcept */;
    /**
     * Returns the Endianness.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @return The Endianness object.
     */
    hummstrumm::engine::system::Endianness *GetEndianness ()
      /* noexcept */;
    /**
     * Returns the Clock.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-08-01
     * @since  0.3
     *
     * @return The Clock object.
     */
    hummstrumm::engine::system::Clock *GetClock ()
      /* noexcept */;

  private:
    /// The engine-wide log.
    hummstrumm::engine::debug::Log::Ptr log;
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
