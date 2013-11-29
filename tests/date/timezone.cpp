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
#define CIPRA_CXX_ABI
#endif
#define CIPRA_USE_VARIADIC_TEMPLATES
#include <cipra/cipra.hpp>

#include "hummstrummengine.hpp"
using namespace hummstrumm::engine::date;

int
main ()
{
  class TimezoneTest : public cipra::fixture
  {
      virtual void
      test () override
      {
        plan (55);

        // Test construction.
        auto utc     = new_ok<Timezone> (),
          utcMinus10 = new_ok<Timezone> (Duration {0, 0, 0, 0, -10, 0, 0, 0}),
          utcPlus4   = new_ok<Timezone> (Duration {0, 0, 0, 0, 4, 0, 0, 0}),
          utcPlus1   = new_ok<Timezone> (Duration {0, 0, 0, 0, 1, 0, 0, 0});
        
        // Test storage
        is (utc.GetOffset (), Duration {},
            "Timezone utc has proper offset");
        is (utcMinus10.GetOffset (), Duration {0, 0, 0, 0, -10, 0, 0, 0},
            "Timezone utcMinus10 has proper offset");
        is (utcPlus4.GetOffset (), Duration {0, 0, 0, 0, 4, 0, 0, 0},
            "Timezone utcPlus4 has proper offset");
        is (utcPlus1.GetOffset (), Duration {0, 0, 0, 0, 1, 0, 0, 0},
            "Timezone utcPlus1 has proper offset");
        
        // Test compare
        ok ([&]() { return utc == utc; }, "utc == utc");
        ok ([&]() { return utc <= utc; }, "utc <= utc");
        ok ([&]() { return utc >= utc; }, "utc >= utc");
        ok ([&]() { return utc > utcMinus10; }, "utc > utcMinus10");
        ok ([&]() { return utc < utcPlus4; }, "utc < utcPlus4");
        ok ([&]() { return utc < utcPlus1; }, "utc < utcPlus1");

        ok ([&]() { return utcMinus10 < utc; }, "utcMinus10 < utc");
        ok ([&]() { return utcMinus10 == utcMinus10; },
            "utcMinus10 == utcMinus10");
        ok ([&]() { return utcMinus10 < utcPlus4; }, "utcMinus10 < utcPlus4");
        ok ([&]() { return utcMinus10 < utcPlus1; }, "utcMinus10 < utcPlus1");
        
        ok ([&]() { return utcPlus4 > utc; }, "utcPlus4 > utc");
        ok ([&]() { return utcPlus4 > utcMinus10; }, "utcPlus4 > utcMinus10");
        ok ([&]() { return utcPlus4 == utcPlus4; }, "utcPlus4 == utcPlus4");
        ok ([&]() { return utcPlus4 > utcPlus1; }, "utcPlus4 > utcPlus1");
        
        ok ([&]() { return utcPlus1 > utc; }, "utcPlus1 > utc");
        ok ([&]() { return utcPlus1 > utcMinus10; }, "utcPlus1 > utcMinus10");
        ok ([&]() { return utcPlus1 == utcPlus1; }, "utcPlus1 == utcPlus1");
        ok ([&]() { return utcPlus1 < utcPlus4; }, "utcPlus1 < utcPlus4");
        
        ok ([&]() { return !(utc != utc); }, "utc != utc");
        ok ([&]() { return !(utc > utc); }, "utc > utc");
        ok ([&]() { return !(utc < utc); }, "utc < utc");
        ok ([&]() { return !(utc <= utcMinus10); }, "utc <= utcMinus10");
        ok ([&]() { return !(utc >= utcPlus4); }, "utc >= utcPlus4");
        ok ([&]() { return !(utc >= utcPlus1); }, "utc >= utcPlus1");
        
        ok ([&]() { return !(utcMinus10 >= utc); }, "not utcMinus10 >= utc");
        ok ([&]() { return !(utcMinus10 != utcMinus10); },
            "not utcMinus10 != utcMinus10");
        ok ([&]() { return !(utcMinus10 >= utcPlus4); },
            "not utcMinus10 >= utcPlus4");
        ok ([&]() { return !(utcMinus10 >= utcPlus1); },
            "not utcMinus10 >= utcPlus1");
        
        ok ([&]() { return !(utcPlus4 <= utc); },
            "not utcPlus4 <= utc");
        ok ([&]() { return !(utcPlus4 <= utcMinus10); },
            "not utcPlus4 <= utcMinus10");
        ok ([&]() { return !(utcPlus4 != utcPlus4); },
            "not utcPlus4 != utcPlus4");
        ok ([&]() { return !(utcPlus4 <= utcPlus1); },
            "not utcPlus4 <= utcPlus1");
        
        ok ([&]() { return !(utcPlus1 <= utc); },
            "not utcPlus1 <= utc");
        ok ([&]() { return !(utcPlus1 <= utcMinus10); },
            "not utcPlus1 <= utcMinus10");
        ok ([&]() { return !(utcPlus1 != utcPlus1); },
            "not utcPlus1 != utcPlus1");
        ok ([&]() { return !(utcPlus1 >= utcPlus4); },
            "not utcPlus1 >= utcPlus4");

        // Test copy
        auto test = new_ok<Timezone> (utc);
        ok ([&]() { return test == utc; }, "Equality after copy construction");
        test = utcMinus10;
        ok ([&]() { return test == utcMinus10; }, "Equality after assignment");

        // Test serialization
        std::ostringstream ss1;
        ss1 << utc;
        ok ([&]() { return ss1.str () == "Z"; }, "UTC output");
        ss1.str ("");
        ss1 << utcMinus10;
        ok ([&]() { return ss1.str () == "-10:00"; }, "UTC-10 output");
        ss1.str ("");
        ss1 << utcPlus4;
        ok ([&]() { return ss1.str () == "+04:00"; }, "UTC+4 output");
        ss1.str ("");
        ss1 << utcPlus1;
        ok ([&]() { return ss1.str () == "+01:00"; }, "UTC+1 output");
        
        Timezone t;
        std::istringstream ss2;
        ss2.str ("Z -10:00 +04:00 +01:00");
        ss2 >> t;
        ok ([&]() { return t == utc; }, "UTC input");
        ss2 >> t;
        ok ([&]() { return t == utcMinus10; }, "UTC-10 input");
        ss2 >> t;
        ok ([&]() { return t == utcPlus4; }, "UTC+4 input");
        ss2 >> t;
        ok ([&]() { return t == utcPlus1; }, "UTC+1 input");
      }
  } test;

  return test.run ();
}
