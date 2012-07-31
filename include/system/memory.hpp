// -*- mode: c++; c-file-style: hummstrumm -*-
/* Humm and Strumm Engine
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
 * Defines the Memory class, which provides information about the RAM on the
 * system.
 *
 * @file   system/memory.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-11-27
 * @see    Memory
 */

#ifndef HUMMSTRUMM_ENGINE_SYSTEM_MEMORY
#define HUMMSTRUMM_ENGINE_SYSTEM_MEMORY

#include <cstdlib>

namespace hummstrumm
{
namespace engine
{
namespace system
{

/**
 * Provides information about the system's memory.  Currently, we only give the
 * total memory and free memory at initialization.
 *
 * @version 0.3
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-06-21
 * @since   0.3
 *
 * @warning These counts are only updated when the Update() method is called.
 */
class Memory
{
  public:
    /**
     * Constructs a new Memory object.  The total RAM count and the total
     * available free RAM is calculated.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-21
     * @since  0.3
     */
    inline Memory ()
      /* noexcept */;

    /**
     * Returns the total RAM on the system, in binary kilobytes (KiB).
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-21
     * @since  0.3
     *
     * @return The total amount of memory on the system in KiB.
     */
    inline std::size_t GetTotalMemory ()
      const /* noexcept */;
    /**
     * Returns the amount of free RAM on the system at the last update, in
     * binary kilobytes (KiB).
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-21
     * @since  0.3
     *
     * @return The total amount of free memory on the system in KiB.
     */
    inline std::size_t GetFreeMemory ()
      const /* noexcept */;

    /**
     * Update the engine's measure of the amount of free RAM on the system.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-20
     * @since  0.7
     */
    void Update ()
      /* noexcept */;

  private:
    /// The total amount of RAM in KiB at engine startup.
    std::size_t totalMemory;
    /// The total amount of free RAM in KiB at engine startup.
    std::size_t freeMemory;
};


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_SYSTEM_MEMORY
