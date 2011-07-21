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
 * of time logged to the game Log.  This profiler has up to nanosecond
 * precision, depending on the precision of the hardware high-resolution timer,
 * as made available through the Time::GetHighResolutionCount() method.
 *
 * One should create a new Profiler object via the PROFILE() macro.
 *
 * This class uses scoping for starting and stopping the profile.  A Profiler
 * object created with the PROFILE() macro will write its output at the end of
 * the block.  Furthermore, you can use the PROFILE_ITERATION() macro in
 * conjunction with a loop to find various amounts 
 *
 * @version 0.3
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
     * Where to output the results from profiler.
     *
     * @author Ricardo Tiago <Rtiago@gmail.com>
     * @date   2010-08-19
     * @since  0.3
     */  
    enum Output
    {
      LOGGER,             /// Write to hummstrumm log
      CONSOLE,            /// Show the results in the output stream
      LOGGER_AND_CONSOLE  /// Both
    };

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
     * @param [in] debugName A name for the profiler to identify it in the log.
     * Names are unique for up to 24 ASCII characters.
     * @param [in] reportIn The unit in which to report the final times.
     * @param [in] out Where to write the results.
     * @param out [in] Where to write the results.
     */
    Profiler (const char *debugName,
              Units reportIn = REPORT_IN_MILLISECONDS, Output out = LOGGER_AND_CONSOLE);
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

    /**
     * Starts a new run of the profiler.  This updates the various stats for
     * times of the profiler.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-06-14
     * @since  0.3
     */
    void Iterate (void) throw ();

  private:
    hummstrumm::engine::types::int64 startTime;    ///< The starting time for
                                                   ///  this run.
    char debugName[25];                            ///< A name for use in a log.
    hummstrumm::engine::types::uint64 lowestTime;   ///< The fastest run.
    hummstrumm::engine::types::uint64 averageTime;  ///< The average time of
                                                   ///  runs.
    hummstrumm::engine::types::uint64 numberOfRuns; ///< The running total of
                                                   ///  runs (no pun intended).
    Units                            reportInUnit; ///< The unit in which to
                                                   ///  report the times.
    Output                           writeTo;      /// Where to write the 
                                                   ///  results.

};

/**
 * Begins profiling until the end of the current block.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-15
 * @since  0.2
 *
 * @param [in] debugName A name for the Profiler, which will aid in picking it
 * out in the Log.
 * @param [in] reportIn The unit in which to report times.  A member of the
 * hummstrumm::engine::debug::Profiler::Units enumeration (without any
 * prefixes).
 * @param [in] out Where to write the results.
 *
 * @see Profiler
 */
#define HUMMSTRUMM_PROFILE(debugName, reportIn, out)                    \
  hummstrumm::engine::debug::Profiler profiler__HIDDEN__ ((debugName),  \
                                                          (reportIn),   \
                                                          (out))

/**
 * Starts a new run of the existing profiler.  A profiler must already exist in
 * the current scope for this method to work.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-06-14
 * @since  0.3
 *
 * @see HUMMSTRUMM_PROFILE()
 */
#define HUMMSTRUMM_PROFILE_ITERATION() \
  profiler__HIDDEN__.Iterate ()        \

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_PROFILER
