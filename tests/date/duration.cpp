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

#ifdef __GNUC__
#  define CIPRA_CXX_ABI
#endif
#define CIPRA_USE_VARIADIC_TEMPLATES
#include <cipra/cipra.hpp>

#include "hummstrummengine.hpp"
using namespace hummstrumm::engine::date;

int
main ()
{
  class DurationTest : public cipra::fixture
  {
      virtual void
      test () override
      {
        plan (75);

        // Test construction
        auto d1 = new_ok<Duration> (),
          d2 = new_ok<Duration> (0, 0, 0, 0, 0, 0, 0, 0),
          d3 = new_ok<Duration> (1, 0, 0, 0, 0, 0, 0, 0),
          d4 = new_ok<Duration> (0, 12, 0, 0, 0, 0, 0, 0),
          d5 = new_ok<Duration> (0, 0, 0, 0, 52, 0, 0, 0),
          d6 = new_ok<Duration> (d5);

        // Test storage
        is (d1, Duration {}, "d1 duration storage");
        is (d2, Duration {0, 0, 0, 0, 0, 0, 0, 0}, "d2 duration storage");
        is (d3, Duration {1, 0, 0, 0, 0, 0, 0, 0}, "d3 duration storage");
        is (d4, Duration {0, 12, 0, 0, 0, 0, 0, 0}, "d4 duration storage");
        is (d5, Duration {0, 0, 0, 0, 52, 0, 0, 0}, "d5 duration storage");
        is (d5, Duration {d6}, "d6 duration storage");

        // Test equality
        is (d1, d1, "d1 == d1");
        is (d1, d2, "d1 == d2");
        isnt (d1, d3, "d1 != d3");
        isnt (d1, d4, "d1 != d4");
        isnt (d1, d5, "d1 != d5");
        isnt (d1, d6, "d1 != d6");

        is (d2, d1, "d2 == d1");
        is (d2, d2, "d2 == d2");
        isnt (d2, d3, "d2 != d3");
        isnt (d2, d4, "d2 != d4");
        isnt (d2, d5, "d2 != d5");
        isnt (d2, d5, "d2 != d6");

        isnt (d3, d1, "d3 != d1");
        isnt (d3, d2, "d3 != d2");
        is (d3, d3, "d3 == d3");
        isnt (d3, d4, "d3 != d4");
        isnt (d3, d5, "d3 != d5");
        isnt (d3, d6, "d3 != d6");

        isnt (d4, d1, "d4 != d1");
        isnt (d4, d2, "d4 != d2");
        isnt (d4, d3, "d4 != d3");
        is (d4, d4, "d4 == d4");
        isnt (d4, d5, "d4 != d5");
        isnt (d4, d6, "d4 != d6");

        isnt (d5, d1, "d5 != d1");
        isnt (d5, d1, "d5 != d2");
        isnt (d5, d3, "d5 != d3");
        isnt (d5, d4, "d5 != d4");
        is (d5, d5, "d5 == d5");
        is (d5, d6, "d5 == d6");

        isnt (d6, d1, "d6 != d1");
        isnt (d6, d2, "d6 != d2");
        isnt (d6, d3, "d6 != d3");
        isnt (d6, d4, "d6 != d4");
        is (d6, d5, "d6 == d5");
        is (d6, d6, "d6 == d6");

        // Test set
        auto test = new_ok<Duration> (d3);
        is (test, d3, "copy constructor gives exact copy");
        test = d5;
        is (test, d5, "assignment gives exact copy");

        // Test addition
        auto temp = new_ok<Duration> (d3);
        is (d3, temp += Duration {}, "addition/assignment of zero");
        is (d3, temp -= Duration {}, "subtraction/assignment of zero");
        is (d3, temp + Duration {}, "addition of zero");
        is (d3, temp - Duration {}, "subtraction of zero");

        temp += d5;
        is (temp, d5 + d3, "addition/assignment of two durations");
        temp -= d5;
        is (temp, d3, "subtraction of same duration gives original value");

        is (d5 + d3, Duration {1, 0, 0, 0, 52, 0, 0, 0}, "addition");
        is (d5 - d3, Duration {-1, 0, 0, 0, 52, 0, 0, 0}, "subtraction");

        // Test negation
        is (-Duration {}, Duration {}, "negation of zero");
        is (-d3, Duration {-1, 0, 0, 0, 0, 0, 0, 0}, "negation of d3");
        is (-d5, Duration {0, 0, 0, 0, -52, 0, 0, 0}, "negation of d5");
        is (-(-d4), d4, "double negation is original duration");

        is (d6 - d3, d6 + -d3, "Subtraction is addition of negative");

        // Test serialization
        std::ostringstream ss1 {};
        ss1 << d1;
        is (ss1.str (), "D0Y", "serialize d1 out");
        ss1.str (""); ss1 << d2;
        is (ss1.str (), "D0Y", "serialize d2 out");
        ss1.str (""); ss1 << d3;
        is (ss1.str (), "D1Y", "serialize d3 out");
        ss1.str (""); ss1 << d4;
        is (ss1.str (), "D12M", "serialize d4 out");
        ss1.str (""); ss1 << d5;
        is (ss1.str (), "DT52H", "serialize d5 out");
        ss1.str (""); ss1 << d6;
        is (ss1.str (), "DT52H", "serialize d6 out");

        Duration d {};
        std::istringstream ss2 {};
        ss2.str ("D0Y D1Y-51DT0.5S DT5H48M-56.456S DT-0.56S");
        ss2 >> d;
        is (d, Duration {}, "serialize duration in");
        ss2 >> d;
        is (d, Duration {1, 0, 0, -51, 0, 0, 0, 500}, "serialize duration in");
        ss2 >> d;
        is (d, Duration {0, 0, 0, 0, 5, 48, -56, -456}, "serialize duration in");
        ss2 >> d;
        is (d, Duration {0, 0, 0, 0, 0, 0, 0, -560}, "serialize duration in");
      }
  } test;

  return test.run ();
}
