// -*- c++ -*-
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
 * Defines the Processors class, which provides information about the processors
 * on the system.
 *
 * @file   system/processors.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-11-26
 * @see    Processors
 */

#ifndef HUMMSTRUMM_ENGINE_SYSTEM_PROCESSORS
#define HUMMSTRUMM_ENGINE_SYSTEM_PROCESSORS


namespace hummstrumm
{
namespace engine
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
     * processor strings of each processor, whether the system supports SSE, and
     * whether the system supports SSE2.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     */
    Processors (void)
      throw ();
    /**
     * Destructs a Processors object.  This will free the memory used by the
     * processor names.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     */
    virtual ~Processors (void);

    /**
     * Returns the number of processors on the system.  This count includes
     * normal cores and hyperthreaded cores.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @return The number of processors on the system.
     */
    int GetNumberOfProcessors (void)
      const throw ();
    /**
     * Returns the processor string associated with the processor index passed
     * in.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param index [in] The processor index of which the string will be
     * returned.
     *
     * @return The processor name.
     */
    const char *GetProcessorName (int index)
      const throw ();

    /**
     * Returns whether the system supports Streaming SIMD Extensions (SSE).
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @return If the system has SSE support.
     */
    bool HaveSseSupport (void)
      const throw ();
    /**
     * Returns whether the system supports Streaming SIMD Extensions 2 (SSE2).
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @return If the system has SSE 2 support.
     */
    bool HaveSse2Support (void)
      const throw ();

    /**
     * Returns whether the system supports Streaming SIMD Extensions 3 (SSE3).
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-03-27
     * @since  0.3
     *
     * @return If the system has SSE 3 support.
     */
    bool HaveSse3Support (void)
      const throw ();

    /**
     * Returns whether the system supports Streaming SIMD Extensions 4.1 (SSE4).
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-03-27
     * @since  0.3
     *
     * @return If the system has SSE 4.1 support.
     */
    bool HaveSse41Support (void)
      const throw ();

    /**
     * Returns whether the system supports Streaming SIMD Extensions 4.2 (SSE4).
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date   2011-03-27
     * @since  0.3
     *
     * @return If the system has SSE 4.2 support.
     */
    bool HaveSse42Support (void)
      const throw ();

  private:
    /**
     * Allocates a processor name and sets it to the string "Unknown".  This is
     * what the processor string will be when we can't figure out what the
     * actual name is.  Nothing critical should be based on this, anyways.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param [in] index The processor index for which to set the name. 
     */
    void SetProcessorNameToUnknown (int index)
      throw ();
    
    int numberOfProcessors;  ///< The number of processors on the system.
    char **processorStrings; ///< An array of the names of each processor.
    bool sseSupport;         ///< Whether we have SSE.
    bool sse2Support;        ///< Whether we have SSE 2.
    bool sse3Support;        ///< Whether we have SSE 3.
    bool sse41Support;       ///< Whether we have SSE 4.1.
    bool sse42Support;       ///< Whether we have SSE 4.2.

};


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_SYSTEM_PROCESSORS
