// -*- mode: c++; c-file-style: hummstrumm -*-
/* Humm and Strumm Engine
 * Copyright (C) 2013, the people listed in the AUTHORS file. 
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
 * Defines the Profiler class template.
 *
 * @file   debug/profiler.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2013-07-16
 * @see    Profiler
 */

#ifndef HUMMSTRUMM_ENGINE_DEBUG_PROFILER
#define HUMMSTRUMM_ENGINE_DEBUG_PROFILER

#include <chrono>
#include <ratio>
#include <string>
#include <vector>
#include <iosfwd>
#include <atomic>

namespace hummstrumm {
namespace engine {
namespace debug {

namespace details {

/**
 * Makes a `std::string` from its template parameter that represents the unit
 * suffix of the duration.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2013-07-16
 * @since  0.7
 *
 * @tparam DurationT The duration type for which to build a unit suffix string.
 * This type must be an instantiation of the `std::chrono::duration` template.
 *
 * @return A string that contains the unit suffix for the given `DurationT`.
 */
template <typename DurationT>
std::string getDurationSuffix () /* nothrow */;
template <>
inline std::string getDurationSuffix<std::chrono::nanoseconds>() /* nothrow */;
template <>
inline std::string getDurationSuffix<std::chrono::microseconds>() /* nothrow */;
template <>
inline std::string getDurationSuffix<std::chrono::milliseconds>() /* nothrow */;
template <>
inline std::string getDurationSuffix<std::chrono::seconds>() /* nothrow */;
template <>
inline std::string getDurationSuffix<std::chrono::minutes>() /* nothrow */;
template <>
inline std::string getDurationSuffix<std::chrono::hours>() /* nothrow */;

}

/**
 * A timer that prints out elapsed times to a log.  A `Profiler<ClockT,
 * DurationT>` divides its lifetime into "runs" whose time durations are
 * recorded and outputted to the log.  The first "run" is defined as the period
 * of time from the constructor invocation until the first call to the`next()`
 * member function, a move operation from `*this`, or the destructor invocation
 * (whichever happens first).  Subsequent "runs" are defined as the period from
 * a call to the `next()` member function until the next call to the `next()`
 * member functor, a move operation from `*this` or the destructor invocation
 * (whichever happens first).  Statistics of the run durations are calculated
 * and printed.
 *
 * @version 0.7
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2013-07-16
 * @since   0.7
 *
 * @tparam ClockT The type from which to get the tick count.  This type must
 *         satisfy the requirements of the `Clock` concept, and the clock must
 *         be steady (`ClockT::is_steady == true`).
 * @tparam DurationT The type in which to print the times measured.  This type
 *         must be an instantiation of the `std::chrono::duration` template.
 *
 * @invariant The log stream stored within `*this` will not be a `nullptr`.
 * A valid `Profiler<ClockT, DurationT>` is always in a run.
 */
template <typename ClockT = std::chrono::high_resolution_clock,
          typename DurationT = typename ClockT::duration>
class Profiler
{
  public:
    /// The type that is used to get `time_point`s.
    using Clock = ClockT;
    /// The `std::chrono::duration` used to print the results.
    using Duration = DurationT;
    
    /**
     * Constructs a new `Profiler<ClockT, DurationT>` object using a given log.
     * This constructor starts the internal timer for the `Profiler<ClockT,
     * DurationT>`.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2013-07-16
     * @since 0.7
     *
     * @param [in] log A stream that will be used as a log.
     *
     * @pre `log` is a valid object guaranteed to outlive `*this`, either until
     * `~Profiler<ClockT, DurationT>` is called on `*this` or until `*this` is
     * moved from.
     *
     * @post `*this` is a valid object on which any operation can be performed.
     */
    explicit Profiler (std::ostream &outputLog);
    /**
     * Constructs a new `Profiler<ClockT, DurationT>` object by moving from
     * another existing `Profiler<ClockT, DurationT>` object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2013-07-16
     * @since  0.7
     *
     * @param [in,out] rhs An object from which to move construct `*this`.
     *
     * @pre `rhs` is a valid object.  The log that was used in the construction
     * of `rhs` is guaranteed to outlive `*this`, either until
     * `~Profiler<ClockT, DurationT>` is called on `*this` or until `*this` is
     * moved from.
     *
     * @post `*this` is a valid object on which any operation can be performed.
     * `rhs` is no longer a valid object; the only operations that can be
     * performed on it are to move assign something to it or to run the
     * destructor.  The effect of performing any other operations on `rhs` is
     * undefined.
     */
    Profiler (Profiler<Clock, Duration> &&rhs);
    /**
     * Destructs an existing `Profiler<ClockT, DurationT>` object.  If `*this`
     * is a valid object, this destructor finishes this run of the timer, prints
     * out the last run's data to the log, and then prints out statistics about
     * all runs.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2013-07-16
     * @since  0.7
     *
     * @post `*this` no longer exists, and the only operations that may be
     * performed on it if it is still in scope are reinitialization using a
     * constructor.
     */
    ~Profiler ();

    /**
     * Finishes this run of the timer, prints out the last run's data to the
     * log, and the starts a new run.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2013-07-16
     * @since  0.7
     *
     * @pre `*this` is a valid object.
     */
    void next ();

  private:
    /// The start of the current run.
    typename Clock::time_point start;
    /// The times of previous runs.
    std::vector<typename Clock::duration> times;
    /// The log to print to.
    std::iostream *out;
    /// The number of profilers that have been created so far.
    static std::atomic<unsigned> count;
};


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_PROFILER
