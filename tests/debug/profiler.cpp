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

#include <utility>
#include <sstream>

#ifdef __GNUC__
#define CIPRA_CXX_ABI
#endif
#define CIPRA_USE_VARIADIC_TEMPLATES
#include <cipra/cipra.hpp>

#include "debug/profiler.hpp"
using namespace hummstrummengine::debug;

// Mock returns 0 on first call to now(), 1 on all later calls.
struct SteadyClockMock
{
  public:
    using duration   = std::chrono::seconds;
    using rep        = duration::rep;
    using period     = duration::period;
    using time_point = std::chrono::time_point<SteadyClockMock>;
    
    static const bool is_steady = true;

    static bool is_first_call;
    
    static time_point now () /* noexcept */
    {
      if (is_first_call)
        {
          is_first_call = false;
          return time_point::min ();
        }
      else
        {
          return time_point::min () + duration (1);
        }
    }
};

bool SteadyClockMock::is_first_call = true;

// Mock returns 1 on first call to now(), 0 on all later calls.
struct NonsteadyClockMock
{
  public:
    using duration   = std::chrono::seconds;
    using rep        = duration::rep;
    using period     = duration::period;
    using time_point = std::chrono::time_point<NonsteadyClockMock>;
    
    static const bool is_steady = false;

    static bool is_first_call;
    
    static time_point now () /* noexcept */
    {
      if (is_first_call)
        {
          is_first_call = false;
          return time_point::min () + duration (1);
        }
      else
        {
          return time_point::min ();
        }
    }
};

bool NonsteadyClockMock::is_first_call = true;

int
main ()
{
  struct ProfilerTest : cipra::fixture
  {
    virtual void
    test() override
    {
      plan(13);
      std::ostringstream out;
        
      // block to limit the lifetime of the profiler
      {
        auto p = new_ok<Profiler<SteadyClockMock>> (out);
        is (out.str (), "Profiler 0: run 0 starting\n",
            "Constructor prints out proper string to log.");
        out.str ("");
      }
      is (out.str (), "Profiler 0: run 0 ending after 1 s\n"
          "Profiler 0: in 1 run(s), min time = 1 s, max time = 1 s, "
          "ave time = 1 s\n",
          "Destructor prints out proper string to log.");
        
      SteadyClockMock::is_first_call = true;
      out.str ("");
        
      // block to limit the lifetime of the profiler
      {
        auto p = new_ok<Profiler<NonsteadyClockMock>> (out);
        is (out.str (), "Profiler 1: run 0 starting\n",
            "Constructor prints out proper string to log.");
        out.str ("");
      }
      is (out.str (), "Profiler 1: run 0 ending after 0 s\n"
          "Profiler 1: in 1 run(s), min time = 0 s, max time = 0 s, "
          "ave time = 0 s\n",
          "Destructor prints out proper string to log.");
        
      NonsteadyClockMock::is_first_call = true;
      out.str ("");
        
      // block to limit the lifetime of the profiler
      {
        auto p = new_ok<Profiler<SteadyClockMock>> (out);
        is (out.str (), "Profiler 2: run 0 starting\n",
            "Constructor prints out proper string to log.");
        out.str ("");
        p.next ();
        is (out.str (), "Profiler 2: run 0 ending after 1 s\n"
            "Profiler 2: run 1 starting\n",
            "next() prints proper string to log.");
        out.str ("");
      }
      is (out.str (), "Profiler 2: run 1 ending after 0 s\n"
          "Profiler 2: in 2 run(s), min time = 0 s, max time = 1 s, "
          "ave time = 0 s\n",
          "Destructor prints out proper string to log.");
        
      SteadyClockMock::is_first_call = true;
      out.str ("");
        
      // block to limit the lifetime of the profiler
      {
        auto p = new_ok<Profiler<SteadyClockMock>> (
          std::move (
            [&]() {
              Profiler<SteadyClockMock> p (out);
              p.next ();
              return p; } ()));
        is (out.str (), "Profiler 3: run 0 starting\n"
            "Profiler 3: run 0 ending after 1 s\n"
            "Profiler 3: run 1 starting\n",
            "Move constructor prints out proper string to log.");
        out.str ("");
      }
      is (out.str (), "Profiler 3: run 1 ending after 0 s\n"
          "Profiler 3: in 2 run(s), min time = 0 s, max time = 1 s, "
          "ave time = 0 s\n",
          "Destructor prints out proper string to log.");
        
      SteadyClockMock::is_first_call = true;
      out.str ("");
    }
  } test;

  return test.run ();
}
