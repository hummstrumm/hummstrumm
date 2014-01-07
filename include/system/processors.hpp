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
 * Defines the Processors class, which provides information about the
 *processors
 * on the system.
 *
 * @file   system/processors.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-11-26
 * @see    Processors
 */

#ifndef HUMMSTRUMM_ENGINE_SYSTEM_PROCESSORS
#define HUMMSTRUMM_ENGINE_SYSTEM_PROCESSORS

#include <vector>
#include <string>

namespace hummstrummengine
{
namespace system
{

/**
 * Provides information about the system's processors.  Currently, it provides
 * the number of cores on the system (including hyperthreaded cores), the
 * processor string for each of these, and information about SSE support in the
 * processors.
 *
 * @version 0.3
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-11-26
 * @since   0.3
 */
class Processors
{
public:
  /**
   * Constructs a new Processors object.  This will detect the attributes of
   * the system's processors that can later be retrieved by the game engine.
   *
   * The following attributes are detected: the number of processor cores, the
   * processor strings of each processor, and what versions of SSE the
   * processor cores support.
   *
   * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
   * @date   2012-06-21
   * @since  0.3
   */
  Processors ()
      /* noexcept */;

  /**
   * Returns the number of processors on the system.  This count includes
   * normal cores and hyperthreaded cores.
   *
   * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
   * @date   2012-06-21
   * @since  0.3
   *
   * @return The number of processors on the system.
   */
  inline int GetNumberOfProcessors () const /* noexcept */;
  /**
   * Returns the processor string associated with the processor index passed
   * in.
   *
   * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
   * @date   2012-06-21
   * @since  0.3
   *
   * @param index [in] The processor index of which the string will be
   * returned.
   *
   * @return The processor name.
   */
  inline std::string GetProcessorName (int index) const /* noexcept */;

  /**
   * Returns whether the system supports Streaming SIMD Extensions (SSE).
   *
   * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
   * @date   2012-06-21
   * @since  0.3
   *
   * @return If the system has SSE support.
   */
  inline bool HaveSseSupport () const /* noexcept */;
  /**
   * Returns whether the system supports Streaming SIMD Extensions 2 (SSE2).
   *
   * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
   * @date   2012-06-21
   * @since  0.3
   *
   * @return If the system has SSE 2 support.
   */
  inline bool HaveSse2Support () const /* noexcept */;

  /**
   * Returns whether the system supports Streaming SIMD Extensions 3 (SSE3).
   *
   * @author Ricardo Tiago <rtiago.mendes@gmail.com>
   * @date   2012-06-21
   * @since  0.3
   *
   * @return If the system has SSE 3 support.
   */
  inline bool HaveSse3Support () const /* noexcept */;

  /**
   * Returns whether the system supports Streaming SIMD Extensions 4.1 (SSE4).
   *
   * @author Ricardo Tiago <rtiago.mendes@gmail.com>
   * @date   2012-06-21
   * @since  0.3
   *
   * @return If the system has SSE 4.1 support.
   */
  inline bool HaveSse41Support () const /* noexcept */;

  /**
   * Returns whether the system supports Streaming SIMD Extensions 4.2 (SSE4).
   *
   * @author Ricardo Tiago <rtiago.mendes@gmail.com>
   * @date   2012-06-21
   * @since  0.3
   *
   * @return If the system has SSE 4.2 support.
   */
  inline bool HaveSse42Support () const /* noexcept */;

private:
  /// The number of processors on the system.
  int numberOfProcessors;
  /// An array of the names of each processor.
  std::vector<std::string> processorStrings;

  bool sseSupport;   ///< Whether we have SSE.
  bool sse2Support;  ///< Whether we have SSE 2.
  bool sse3Support;  ///< Whether we have SSE 3.
  bool sse41Support; ///< Whether we have SSE 4.1.
  bool sse42Support; ///< Whether we have SSE 4.2.
};
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_SYSTEM_PROCESSORS
