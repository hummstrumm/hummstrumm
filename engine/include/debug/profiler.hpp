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
 * Defines the Profiler class.
 *
 * @file   profiler.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-15
 * @see    Profiler
 */

#ifndef HUMMSTRUMM_ENGINE_DEBUG_PROFILER
#define HUMMSTRUMM_ENGINE_DEBUG_PROFILER

#include <types/inttypes.hpp>

namespace hummstrumm
{
namespace engine
{
namespace types
{
typedef std::wstring String;
}
namespace debug
{

/**
 * Provides a method by which a segment of code can be timed, and that length
 * of time logged to the game Log.  This profiler has up to nanosecond
 * precision, depending on the precision of the hardware high-resolution timer,
 * as made available through the Time::GetHighResolutionCount() method.
 *
 * One should create a new Profiler object via the PROFILE() macro.
 *
 * This class uses scoping for starting and stopping the profile.  A Profiler
 * object created with the PROFILE() macro will write its output at the end of
 * the block.
 *
 * @version 0.2
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-03-15
 * @since   0.2
 *
 * @see PROFILE()
 */
class Profiler
{ 
  public:
    /**
     * Starts a profiler.  This profiler will output a log message with the
     * debug name to help in identifying the profiling information.  It will
     * also take the current timestamp with the high-resolution timer, which
     * will be used in finding the length of time spent in the block.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-15
     * @since  0.2
     *
     * @param debugName A name for the profiler to identify it in the log.
     */
    Profiler (hummstrumm::engine::types::String debugName);
    /**
     * Stops the profiler.  The profiler will compare the current time with the
     * time taken when it was created and output a log message with the
     * difference.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-15
     * @since  0.2
     */
    virtual ~Profiler (void);

  private:
    hummstrumm::engine::types::int64 startTime;  ///< The starting time.
    hummstrumm::engine::types::String debugName; ///< A name for use in a log.
};

/**
 * Begins profiling until the end of the current block.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-15
 * @since  0.2
 *
 * @param debugName A name for the Profiler, which will aid in picking it out in
 * the Log.
 *
 * @see Profiler
 */
#define PROFILE(debugName)                     \
  Profiler profiler__HIDDEN__ ((debugName))

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_PROFILER
