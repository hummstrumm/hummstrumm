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
 * Defines the Profiler class.
 *
 * @file   debug/profiler.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-15
 * @see    Profiler
 */

#ifndef HUMMSTRUMM_ENGINE_DEBUG_PROFILER
#define HUMMSTRUMM_ENGINE_DEBUG_PROFILER

namespace hummstrumm
{
namespace engine
{
namespace debug
{

/**
 * Provides a method by which a segment of code can be timed, and that length
 * of time logged to the engine log.  This profiler has up to nanosecond
 * precision, depending on the precision of the hardware high-resolution timer.
 *
 * This class uses scoping for starting and stopping the profile.  A Profiler
 * object will write its output at the end of the block.  Furthermore, you can
 * use the Iterate() method to restart the profiler, averaging the last time
 * with any previous iterations and saving the lowest time (this can be useful
 * in measuring performance of a loop, for instance, by calling Iterate() at the
 * end of the loop).
 *
 * @version 0.7
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-06-23
 * @since   0.2
 */
class Profiler
{ 
  public:
    /**
     * The unit of measure in which to report times from the profiler.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-14
     * @since  0.3
     */
    enum Units
    {
      REPORT_IN_SECONDS,      ///< Report in seconds      (decimal)
      REPORT_IN_MILLISECONDS, ///< Report in milliseconds (integer)
      REPORT_IN_MICROSECONDS  ///< Report in microseconds (integer)
    };

    /**
     * Starts a profiler.  This profiler will output a log message with the
     * debug name to help in identifying the profiling information.  It will
     * also take the current timestamp with the high-resolution timer, which
     * will be used in finding the length of time spent in the block.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-23
     * @since  0.2
     *
     * @param [in] debugName A name for the profiler to identify it in the log.
     * @param [in] reportIn The unit in which to report the final times.
     */
    Profiler (std::string debugName, Units reportIn = REPORT_IN_MILLISECONDS);
    /**
     * Stops the profiler.  The profiler will compare the current time with the
     * time taken when it was created and output a log message with the
     * difference.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-23
     * @since  0.2
     */
    ~Profiler ();

    /**
     * Starts a new run of the profiler.  This updates the various stats for
     * times of the profiler.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-14
     * @since  0.3
     */
    void Iterate () /* noexcept */;

  private:
    /// The starting time for this run.
    hummstrumm::engine::types::int64 startTime;
    /// A name for use in a log.
    std::string debugName;
    /// The fastest run.
    hummstrumm::engine::types::uint64 lowestTime;
    /// The average time of runs.
    hummstrumm::engine::types::uint64 averageTime;
    /// The running total of runs (pun completely intended).
    hummstrumm::engine::types::uint64 numberOfRuns;
    /// The unit in which to report the times.
    Units reportInUnit;

};


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_PROFILER
