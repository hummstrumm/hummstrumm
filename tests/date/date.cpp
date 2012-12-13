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
#include <cipra/cipra.h>

#include "hummstrummengine.hpp"
using namespace hummstrumm::engine::date;

int
main ()
{
  class DateTest : public cipra::fixture
  {
    virtual void
    test () override
    {
      plan (170);

      // Test construction
      auto d1 = new_ok<Date> (),
        d2 = new_ok<Date> (0),
        d3 = new_ok<Date> (72463437),
        d4 = new_ok<Date> (2012, 3, 25, 0, 37, 10, 254),
        d5 = new_ok<Date> (1970, 1, 1, 0, 0, 0, 0),
        d6 = new_ok<Date> (4521, 12, 25, 18, 45, 7, 2);

      // Test storage
      is (d1.GetMillisecondsSinceEpoch (), 0, "d1 storage");
      is (d2.GetMillisecondsSinceEpoch (), 0, "d2 storage");
      is (d3.GetMillisecondsSinceEpoch (), 72463437, "d3 storage");
      is (d4.GetMillisecondsSinceEpoch (), 1332635830254, "d4 storage");
      is (d5.GetMillisecondsSinceEpoch (), 0, "d5 storage");
      is (d6.GetMillisecondsSinceEpoch (), 80532816307002, "d6 storage");

      // Test components
      is (d1.GetYear (), 1970, "d1 year");
      is (d1.GetMonth (), 1, "d1 month");
      is (d1.GetDay (), 1, "d1 day");
      is (d1.GetHour (), 0, "d1 hour");
      is (d1.GetMinute (), 0, "d1 minute");
      is (d1.GetSecond (), 0, "d1 second");
      is (d1.GetMillisecond (), 0, "d1 millisecond");

      is (d2.GetYear (), 1970, "d2 year");
      is (d2.GetMonth (), 1, "d2 month");
      is (d2.GetDay (), 1, "d2 day");
      is (d2.GetHour (), 0, "d2 hour");
      is (d2.GetMinute (), 0, "d2 minute");
      is (d2.GetSecond (), 0, "d2 second");
      is (d2.GetMillisecond (), 0, "d2 millisecond");

      is (d3.GetYear (), 1970, "d3 year");
      is (d3.GetMonth (), 1, "d3 month");
      is (d3.GetDay (), 1, "d3 day");
      is (d3.GetHour (), 20, "d3 hour");
      is (d3.GetMinute (), 7, "d3 minute");
      is (d3.GetSecond (), 43, "d3 second");
      is (d3.GetMillisecond (), 437, "d3 millisecond");

      is (d4.GetYear (), 2012, "d4 year");
      is (d4.GetMonth (), 3, "d4 month");
      is (d4.GetDay (), 25, "d4 day");
      is (d4.GetHour (), 0, "d4 hour");
      is (d4.GetMinute (), 37, "d4 minute");
      is (d4.GetSecond (), 10, "d4 second");
      is (d4.GetMillisecond (), 254, "d4 millisecond");

      is (d5.GetYear (), 1970, "d5 year");
      is (d5.GetMonth (), 1, "d5 month");
      is (d5.GetDay (), 1, "d5 day");
      is (d5.GetHour (), 0, "d5 hour");
      is (d5.GetMinute (), 0, "d5 minute");
      is (d5.GetSecond (), 0, "d5 second");
      is (d5.GetMillisecond (), 0, "d5 millisecond");

      is (d6.GetYear (), 4521, "d6 year");
      is (d6.GetMonth (), 12, "d6 month");
      is (d6.GetDay (), 25, "d6 day");
      is (d6.GetHour (), 18, "d6 hour");
      is (d6.GetMinute (), 45, "d6 minute");
      is (d6.GetSecond (), 7, "d6 second");
      is (d6.GetMillisecond (), 2, "d6 millisecond");

      // Test compare
      ok ([&]() { return d1 == d1; }, "d1 == d1");
      ok ([&]() { return d1 == d2; }, "d1 == d2");
      ok ([&]() { return d1 < d3; }, "d1 < d3");
      ok ([&]() { return d1 < d4; }, "d1 < d4");
      ok ([&]() { return d1 == d5; }, "d1 == d5");
      ok ([&]() { return d1 < d6; }, "d1 < d6");

      ok ([&]() { return d2 == d1; }, "d2 == d1");
      ok ([&]() { return d2 == d2; }, "d2 == d2");
      ok ([&]() { return d2 < d3; }, "d2 < d3");
      ok ([&]() { return d2 < d4; }, "d2 < d4");
      ok ([&]() { return d2 == d5; }, "d2 == d5");
      ok ([&]() { return d2 < d6; }, "d2 < d6");

      ok ([&]() { return d3 > d1; }, "d3 > d1");
      ok ([&]() { return d3 > d2; }, "d3 > d2");
      ok ([&]() { return d3 == d3; }, "d3 == d3");
      ok ([&]() { return d3 < d4; }, "d3 < d4");
      ok ([&]() { return d3 > d5; }, "d3 > d5");
      ok ([&]() { return d3 < d6; }, "d3 < d6");

      ok ([&]() { return d4 > d1; }, "d4 > d1");
      ok ([&]() { return d4 > d2; }, "d4 > d2");
      ok ([&]() { return d4 > d3; }, "d4 > d3");
      ok ([&]() { return d4 == d4; }, "d4 == d4");
      ok ([&]() { return d4 > d5; }, "d4 > d5");
      ok ([&]() { return d4 < d6; }, "d4 < d6");

      ok ([&]() { return d5 == d1; }, "d5 == d1");
      ok ([&]() { return d5 == d2; }, "d5 == d2");
      ok ([&]() { return d5 < d3; }, "d5 < d3");
      ok ([&]() { return d5 < d4; }, "d5 < d4");
      ok ([&]() { return d5 == d5; }, "d5 == d5");
      ok ([&]() { return d5 < d6; }, "d5 < d6");

      ok ([&]() { return d6 > d1; }, "d6 > d1");
      ok ([&]() { return d6 > d2; }, "d6 > d2");
      ok ([&]() { return d6 > d3; }, "d6 > d3");
      ok ([&]() { return d6 > d4; }, "d6 > d4");
      ok ([&]() { return d6 > d5; }, "d6 > d5");
      ok ([&]() { return d6 == d6; }, "d6 == d6");

      ok ([&]() { return !(d1 != d1); }, "not d1 != d1");
      ok ([&]() { return !(d1 != d2); }, "not d1 != d2");
      ok ([&]() { return !(d1 >= d3); }, "not d1 >= d3");
      ok ([&]() { return !(d1 >= d4); }, "not d1 >= d4");
      ok ([&]() { return !(d1 != d5); }, "not d1 != d5");
      ok ([&]() { return !(d1 >= d6); }, "not d1 >= d6");

      ok ([&]() { return !(d2 != d1); }, "not d2 != d1");
      ok ([&]() { return !(d2 != d2); }, "not d2 != d2");
      ok ([&]() { return !(d2 >= d3); }, "not d2 >= d3");
      ok ([&]() { return !(d2 >= d4); }, "not d2 >= d4");
      ok ([&]() { return !(d2 != d5); }, "not d2 != d5");
      ok ([&]() { return !(d2 >= d6); }, "not d2 >= d6");

      ok ([&]() { return !(d3 <= d1); }, "not d3 <= d1");
      ok ([&]() { return !(d3 <= d2); }, "not d3 <= d2");
      ok ([&]() { return !(d3 != d3); }, "not d3 != d3");
      ok ([&]() { return !(d3 >= d4); }, "not d3 >= d4");
      ok ([&]() { return !(d3 <= d5); }, "not d3 <= d5");
      ok ([&]() { return !(d3 >= d6); }, "not d3 >= d6");

      ok ([&]() { return !(d4 <= d1); }, "not d4 <= d1");
      ok ([&]() { return !(d4 <= d2); }, "not d4 <= d2");
      ok ([&]() { return !(d4 <= d3); }, "not d4 <= d3");
      ok ([&]() { return !(d4 != d4); }, "not d4 != d4");
      ok ([&]() { return !(d4 <= d5); }, "not d4 <= d5");
      ok ([&]() { return !(d4 >= d6); }, "not d4 >= d6");

      ok ([&]() { return !(d5 != d1); }, "not d5 != d1");
      ok ([&]() { return !(d5 != d2); }, "not d5 != d2");
      ok ([&]() { return !(d5 >= d3); }, "not d5 >= d3");
      ok ([&]() { return !(d5 >= d4); }, "not d5 >= d4");
      ok ([&]() { return !(d5 != d5); }, "not d5 != d5");
      ok ([&]() { return !(d5 >= d6); }, "not d5 >= d6");

      ok ([&]() { return !(d6 <= d1); }, "not d6 <= d1");
      ok ([&]() { return !(d6 <= d2); }, "not d6 <= d2");
      ok ([&]() { return !(d6 <= d3); }, "not d6 <= d3");
      ok ([&]() { return !(d6 <= d4); }, "not d6 <= d4");
      ok ([&]() { return !(d6 <= d5); }, "not d6 <= d5");
      ok ([&]() { return !(d6 != d6); }, "not d6 != d6");

      // Test set
      auto test = new_ok<Date> (d6);
      is (test, d6, "copy constructor gives exact clone");
      test = d4;
      is (test, d4, "assignment gives exact clone");

      // Test arithmetic
      auto dur1 = new_ok<Duration> (5, -1, 4, 2, 0, 0, 0, 5),
        dur2 = new_ok<Duration> (-1, 0, 0, 0, 0, 0, 0, 0),
        dur3 = new_ok<Duration> (0, 18, 0, 56, 12, 2, -1, 45);

      // use ok() to catch any exceptions that may happen (?)
      ok ([&]() { return d1 + dur1 == dur1 + d1; }, "dur1 commutativity");
      ok ([&]() { return d2 + dur1 == dur1 + d2; }, "dur1 commutativity");
      ok ([&]() { return d3 + dur1 == dur1 + d3; }, "dur1 commutativity");
      ok ([&]() { return d4 + dur1 == dur1 + d4; }, "dur1 commutativity");
      ok ([&]() { return d5 + dur1 == dur1 + d5; }, "dur1 commutativity");
      ok ([&]() { return d6 + dur1 == dur1 + d6; }, "dur1 commutativity");

      // Can't add dur2 to epoch, as it is negative.
      ok ([&]() { return d4 + dur2 == dur2 + d4; }, "dur2 commutativity");
      ok ([&]() { return d6 + dur2 == dur2 + d6; }, "dur2 commutativity");

      ok ([&]() { return d1 + dur3 == dur3 + d1; }, "dur3 commutativity");
      ok ([&]() { return d2 + dur3 == dur3 + d2; }, "dur3 commutativity");
      ok ([&]() { return d3 + dur3 == dur3 + d3; }, "dur3 commutativity");
      ok ([&]() { return d4 + dur3 == dur3 + d4; }, "dur3 commutativity");
      ok ([&]() { return d5 + dur3 == dur3 + d5; }, "dur3 commutativity");
      ok ([&]() { return d6 + dur3 == dur3 + d6; }, "dur3 commutativity");

      // exceptions thrown by these additions are now known.  we can use is().
      is (d1 + dur1, Date {1974, 12, 31, 0, 0, 0, 5}, "addition of duration");
      is (d1 + dur3, Date {1971, 8, 26, 12, 1, 59, 45}, "addition of duration");

      is (d2 + dur1, Date {1974, 12, 31, 0, 0, 0, 5}, "addition of duration");
      is (d2 + dur3, Date {1971, 8, 26, 12, 1, 59, 45}, "addition of duration");

      is (d3 + dur1, Date {1974, 12, 31, 20, 7, 43, 442},
          "addition of duration");
      is (d3 + dur3, Date {1971, 8, 27, 8, 9, 42, 482}, "addition of duration");

      is (d4 + dur1, Date {2017, 3, 27, 0, 37, 10, 259}, "addition of duration");
      is (d4 + dur2, Date {2011, 3, 25, 0, 37, 10, 254}, "addition of duration");
      is (d4 + dur3, Date {2013, 11, 20, 12, 39, 9, 299},
          "addition of duration");

      is (d5 + dur1, Date {1974, 12, 31, 0, 0, 0, 5}, "addition of duration");
      is (d5 + dur3, Date {1971, 8, 26, 12, 1, 59, 45}, "addition of duration");

      is (d6 + dur1, Date {4526, 12, 25, 18, 45, 7, 7}, "addition of duration");
      is (d6 + dur2, Date {4520, 12, 25, 18, 45, 7, 2}, "addition of duration");
      is (d6 + dur3, Date {4523, 8, 21, 6, 47, 6, 47}, "addition of duration");

      // Test serialization.
      std::ostringstream ss1 {};
      ss1 << d1;
      is (ss1.str (), "1970-01-01T00:00:00.000", "serialize d1 out");
      ss1.str (""); ss1 << d2;
      is (ss1.str (), "1970-01-01T00:00:00.000", "serialize d2 out");
      ss1.str (""); ss1 << d3;
      is (ss1.str (), "1970-01-01T20:07:43.437", "serialize d3 out");
      ss1.str (""); ss1 << d4;
      is (ss1.str (), "2012-03-25T00:37:10.254", "serialize d4 out");
      ss1.str (""); ss1 << d5;
      is (ss1.str (), "1970-01-01T00:00:00.000", "serialize d5 out");
      ss1.str (""); ss1 << d6;
      is (ss1.str (), "4521-12-25T18:45:07.002", "serialize d6 out");

      Date d {};
      std::istringstream ss2 {};
      ss2.str ("1984-05-14T12:00:00.0 20451-09-30T00:04:15.5 "
               "1970-01-01T00:00:00 2011-04-03T14:58:33.48");
      ss2 >> d;
      is (d, Date {1984, 5, 14, 12, 0, 0, 0}, "serialize Date in");
      ss2 >> d;
      is (d, Date {20451, 9, 30, 0, 4, 15, 500}, "serialize Date in");
      ss2 >> d;
      is (d, Date {}, "serialize Date in");
      ss2 >> d;
      is (d, Date {2011, 4, 3, 14, 58, 33, 480}, "serialize Date in");
    }
  } test;

  return test.run ();
}
