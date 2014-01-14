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

#ifndef HUMMSTRUMM_ENGINE_DEBUG_PROFILER_INL
#define HUMMSTRUMM_ENGINE_DEBUG_PROFILER_INL

#include <chrono>
#include <ratio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <atomic>
#include <sstream>
#include <utility>

namespace hummstrummengine {
namespace debug {
namespace detail {

/**
 * Returns the count of `Profiler` objects of any type, and increments that
 * count.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2013-07-16
 * @since  0.7
 *
 * @return The number of `Profiler` objects that have been created, before
 * incrementing.
 */
inline unsigned long
profilerCount ()
{
  static std::atomic<unsigned long> count;
  return count++;
}

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
std::string
getDurationSuffix () /* nothrow */
{
  return std::to_string (DurationT::period::num) +
    (DurationT::period::den != 1 ?
     std::to_string (DurationT::period::den) : "") +
    " s";
}

template <>
inline std::string
getDurationSuffix<std::chrono::nanoseconds>() /* nothrow */
{
  return "ns";
}

template <>
inline std::string
getDurationSuffix<std::chrono::microseconds>() /* nothrow */
{
#ifdef MSVC
  return "\x00B5s";             // non standard, but MSVC doesn't have u8""
#else
  return u8"\x00B5s";
#endif
}

template <>
inline std::string
getDurationSuffix<std::chrono::milliseconds>() /* nothrow */
{
  return "ms";
}

template <>
inline std::string
getDurationSuffix<std::chrono::seconds>() /* nothrow */
{
  return "s";
}

template <>
inline std::string
getDurationSuffix<std::chrono::minutes>() /* nothrow */
{
  return "min";
}

template <>
inline std::string
getDurationSuffix<std::chrono::hours>() /* nothrow */
{
  return "h";
}

}


template <typename ClockT, typename DurationT>
Profiler<ClockT, DurationT>::Profiler (std::ostream &outputLog)
  : start (ClockT::now ()), out (&outputLog), num (detail::profilerCount ())
{
  *out << "Profiler " << num << ": run " << times.size () << " starting"
       << std::endl;
}

template <typename ClockT, typename DurationT>
Profiler<ClockT, DurationT>::Profiler (Profiler<ClockT, DurationT> &&rhs)
  : start (std::move (rhs.start)), times (std::move (rhs.times)),
    out (std::move (rhs.out)), num (std::move (rhs.num))
{
  rhs.out = nullptr;
}

template <typename ClockT, typename DurationT>
Profiler<ClockT, DurationT>::~Profiler ()
{
  // If the invariant is broken, we moved from this class.  Don't do anything.
  if (out == nullptr)
    return;

  auto newStart = ClockT::now ();

  if (newStart < start)
    {
      times.emplace_back (ClockT::duration::zero ());
    }
  else
    {
      times.emplace_back (newStart - start);
    }

  start = std::move (newStart);

  *out << "Profiler " << num << ": run " << times.size () - 1
       << " ending after "
       << printDuration (times.back ()) << std::endl;

  auto min_max = std::minmax_element (times.begin (), times.end ());
  // elements of times should never be negative (by construction), so we don't
  // need to worry about any signed/unsigned mismatches here.
  auto ave =
    std::accumulate (times.begin (), times.end (), ClockT::duration::zero ()) /
    times.size ();

  *out << "Profiler " << num << ": in " << times.size ()
       << " run(s), min time = " << printDuration (*min_max.first)
       << ", max time = " << printDuration (*min_max.second)
       << ", ave time = " << printDuration (ave) << std::endl;
}

template <typename ClockT, typename DurationT>
void Profiler<ClockT, DurationT>::next ()
{
  auto newStart = ClockT::now ();

  if (newStart < start)
    {
      times.emplace_back (ClockT::duration::zero ());
    }
  else
    {
      times.emplace_back (newStart - start);
    }

  start = std::move (newStart);

  *out << "Profiler " << num << ": run " << times.size () - 1
       << " ending after "
       << printDuration (times.back ()) << std::endl;
  *out << "Profiler " << num << ": run " << times.size () << " starting"
       << std::endl;
}


template <typename ClockT, typename DurationT>
template <typename InDurationT>
std::string
Profiler<ClockT, DurationT>::printDuration (const InDurationT &d)
{
  std::ostringstream ss;
  ss << std::chrono::duration_cast<DurationT> (d).count () << ' '
     << detail::getDurationSuffix<DurationT> ();
  return ss.str ();
}

}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_PROFILER_INL
