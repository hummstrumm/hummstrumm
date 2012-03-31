// -*- mode: c++; c-file-style: hummstrumm -*-
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

#include "hummstrummengine.hpp"

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

using namespace hummstrumm::engine::date;

class TimezoneTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE (TimezoneTest);
    CPPUNIT_TEST (testStorage);
    CPPUNIT_TEST (testCompare);
    CPPUNIT_TEST (testSet);
    CPPUNIT_TEST (testSerialization);
    CPPUNIT_TEST_SUITE_END ();

    Timezone::Ptr utc;
    Timezone::Ptr utcMinus10;
    Timezone::Ptr utcPlus4;
    Timezone::Ptr utcPlus1;

  public:
    void setUp (void)
    {
      utc        = new Timezone (Duration ());
      utcMinus10 = new Timezone (Duration (0, 0, 0, 0, -10, 0, 0, 0));
      utcPlus4   = new Timezone (Duration (0, 0, 0, 0, 4, 0, 0, 0));
      utcPlus1   = new Timezone (Duration (0, 0, 0, 0, 1, 0, 0, 0));
    }

    void testStorage (void)
    {
      CPPUNIT_ASSERT_EQUAL (utc->GetOffset (),
                            Duration ());
      CPPUNIT_ASSERT_EQUAL (utcMinus10->GetOffset (),
                            Duration (0, 0, 0, 0, -10, 0, 0, 0));
      CPPUNIT_ASSERT_EQUAL (utcPlus4->GetOffset (),
                            Duration (0, 0, 0, 0, 4, 0, 0, 0));
      CPPUNIT_ASSERT_EQUAL (utcPlus1->GetOffset (),
                            Duration (0, 0, 0, 0, 1, 0, 0, 0));
    }

    void testCompare (void)
    {
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utc == *utc));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utc <= *utc));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utc >= *utc));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utc > *utcMinus10));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utc < *utcPlus4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utc < *utcPlus1));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utcMinus10 < *utc));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utcMinus10 ==
                                                     *utcMinus10));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utcMinus10 < *utcPlus4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utcMinus10 < *utcPlus1));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utcPlus4 > *utc));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utcPlus4 > *utcMinus10));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utcPlus4 == *utcPlus4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utcPlus4 > *utcPlus1));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utcPlus1 > *utc));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utcPlus1 > *utcMinus10));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utcPlus1 == *utcPlus1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*utcPlus1 < *utcPlus4));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utc != *utc));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utc > *utc));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utc < *utc));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utc <= *utcMinus10));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utc >= *utcPlus4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utc >= *utcPlus1));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utcMinus10 >= *utc));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utcMinus10 !=
                                                     *utcMinus10));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utcMinus10 >= *utcPlus4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utcMinus10 >= *utcPlus1));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utcPlus4 <= *utc));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utcPlus4 <= *utcMinus10));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utcPlus4 != *utcPlus4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utcPlus4 <= *utcPlus1));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utcPlus1 <= *utc));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utcPlus1 <= *utcMinus10));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utcPlus1 != *utcPlus1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*utcPlus1 >= *utcPlus4));
    }

    void testSet (void)
    {
      Timezone test (*utc);
      CPPUNIT_ASSERT (test == *utc);
      test = *utcMinus10;
      CPPUNIT_ASSERT (test == *utcMinus10);
    }

    void testSerialization (void)
    {
      std::ostringstream ss1;
      ss1 << *utc;
      CPPUNIT_ASSERT (ss1.str () == "Z");
      ss1.str (""); ss1 << *utcMinus10;
      CPPUNIT_ASSERT (ss1.str () == "-10:00");
      ss1.str (""); ss1 << *utcPlus4;
      CPPUNIT_ASSERT (ss1.str () == "+04:00");
      ss1.str (""); ss1 << *utcPlus1;
      CPPUNIT_ASSERT (ss1.str () == "+01:00");

      Timezone t;
      std::istringstream ss2;
      ss2.str ("Z -10:00 +04:00 +01:00");
      ss2 >> t;
      CPPUNIT_ASSERT (t == *utc);
      ss2 >> t;
      CPPUNIT_ASSERT (t == *utcMinus10);
      ss2 >> t;
      CPPUNIT_ASSERT (t == *utcPlus4);
      ss2 >> t;
      CPPUNIT_ASSERT (t == *utcPlus1);
    }
};


class DurationTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE (DurationTest);
    CPPUNIT_TEST (testEquality);
    CPPUNIT_TEST (testSet);
    CPPUNIT_TEST (testAddition);
    CPPUNIT_TEST (testNegation);
    CPPUNIT_TEST_SUITE_END ();

    Duration::Ptr d1, d2, d3, d4, d5, d6;

  public:
    void setUp (void)
    {
      d1 = new Duration ();
      d2 = new Duration (0, 0, 0, 0, 0, 0, 0, 0);
      d3 = new Duration (1, 0, 0, 0, 0, 0, 0, 0);
      d4 = new Duration (0, 12, 0, 0, 0, 0, 0, 0);
      d5 = new Duration (0, 0, 0, 0, 52, 0, 0, 0);
      d6 = new Duration (*d5);
    }

    void testEquality (void)
    {
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d1 == *d1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d1 == *d2));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d1 != *d3));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d1 != *d4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d1 != *d5));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d1 != *d6));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d2 == *d1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d2 == *d2));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d2 != *d3));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d2 != *d4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d2 != *d5));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d2 != *d6));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d3 != *d1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d3 != *d2));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d3 == *d3));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d3 != *d4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d3 != *d5));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d3 != *d6));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d4 != *d1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d4 != *d2));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d4 != *d3));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d4 == *d4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d4 != *d5));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d4 != *d6));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d5 != *d1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d5 != *d2));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d5 != *d3));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d5 != *d4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d5 == *d5));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d5 == *d6));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d6 != *d1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d6 != *d2));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d6 != *d3));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d6 != *d4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d6 == *d5));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d6 == *d6));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d1 != *d1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d1 != *d2));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d1 == *d3));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d1 == *d4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d1 == *d5));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d1 == *d6));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d2 != *d1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d2 != *d2));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d2 == *d3));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d2 == *d4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d2 == *d5));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d2 == *d6));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d3 == *d1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d3 == *d2));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d3 != *d3));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d3 == *d4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d3 == *d5));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d3 == *d6));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d4 == *d1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d4 == *d2));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d4 == *d3));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d4 != *d4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d4 == *d5));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d4 == *d6));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d5 == *d1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d5 == *d2));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d5 == *d3));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d5 == *d4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d5 != *d5));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d5 != *d6));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d6 == *d1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d6 == *d2));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d6 == *d3));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d6 == *d4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d6 != *d5));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d6 != *d6));
    }

    void testSet (void)
    {
      Duration test (*d3);
      CPPUNIT_ASSERT (test == *d3);
      test = *d5;
      CPPUNIT_ASSERT (test == *d5);
    }

    void testAddition (void)
    {
      Duration temp (*d3);
      CPPUNIT_ASSERT (*d3 == (temp += Duration ()));
      CPPUNIT_ASSERT (*d3 == (temp -= Duration ()));
      CPPUNIT_ASSERT (*d3 == (temp + Duration ()));
      CPPUNIT_ASSERT (*d3 == (temp - Duration ()));

      temp += *d5;
      CPPUNIT_ASSERT (temp == *d5 + *d3);
      temp -= *d5;
      CPPUNIT_ASSERT (temp == *d3);

      CPPUNIT_ASSERT (*d5 + *d3 == Duration (1, 0, 0, 0, 52, 0, 0, 0));
      CPPUNIT_ASSERT (*d5 - *d3 == Duration (-1, 0, 0, 0, 52, 0, 0, 0));
    }

    void testNegation (void)
    {
      CPPUNIT_ASSERT (-Duration () == Duration ());
      CPPUNIT_ASSERT (-*d3 == Duration (-1, 0, 0, 0, 0, 0, 0, 0));
      CPPUNIT_ASSERT (-*d5 == Duration (0, 0, 0, 0, -52, 0, 0, 0));
      CPPUNIT_ASSERT (-(-*d4) == *d4);

      CPPUNIT_ASSERT (*d6 - *d3 == *d6 + -*d3);
    }

};


class DateTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE (DateTest);
    CPPUNIT_TEST (testStorage);
    CPPUNIT_TEST (testComponents);
    CPPUNIT_TEST (testCompare);
    CPPUNIT_TEST (testSet);
    CPPUNIT_TEST (testArithmetic);
    CPPUNIT_TEST_SUITE_END ();

    Date::Ptr d1, d2, d3, d4, d5, d6;

  public:
    void setUp (void)
    {
      d1 = new Date ();
      d2 = new Date (0);
      d3 = new Date (72463437);
      d4 = new Date (2012, 3, 25, 0, 37, 10, 254);
      d5 = new Date (1970, 1, 1, 0, 0, 0, 0);
      d6 = new Date (4521, 12, 25, 18, 45, 7, 2);
    }

    void testStorage (void)
    {
      CPPUNIT_ASSERT (d1->GetMillisecondsSinceEpoch () == 0);
      CPPUNIT_ASSERT (d2->GetMillisecondsSinceEpoch () == 0);
      CPPUNIT_ASSERT (d3->GetMillisecondsSinceEpoch () == 72463437);
      CPPUNIT_ASSERT (d4->GetMillisecondsSinceEpoch () == 1332635830254);
      CPPUNIT_ASSERT (d5->GetMillisecondsSinceEpoch () == 0);
      CPPUNIT_ASSERT (d6->GetMillisecondsSinceEpoch () == 80532816307002);
    }

    void testComponents (void)
    {
      CPPUNIT_ASSERT (d1->GetYear () == 1970);
      CPPUNIT_ASSERT (d1->GetMonth () == 1);
      CPPUNIT_ASSERT (d1->GetDay () == 1);
      CPPUNIT_ASSERT (d1->GetHour () == 0);
      CPPUNIT_ASSERT (d1->GetMinute () == 0);
      CPPUNIT_ASSERT (d1->GetSecond () == 0);
      CPPUNIT_ASSERT (d1->GetMillisecond () == 0);

      CPPUNIT_ASSERT (d2->GetYear () == 1970);
      CPPUNIT_ASSERT (d2->GetMonth () == 1);
      CPPUNIT_ASSERT (d2->GetDay () == 1);
      CPPUNIT_ASSERT (d2->GetHour () == 0);
      CPPUNIT_ASSERT (d2->GetMinute () == 0);
      CPPUNIT_ASSERT (d2->GetSecond () == 0);
      CPPUNIT_ASSERT (d2->GetMillisecond () == 0);

      CPPUNIT_ASSERT (d3->GetYear () == 1970);
      CPPUNIT_ASSERT (d3->GetMonth () == 1);
      CPPUNIT_ASSERT (d3->GetDay () == 1);
      CPPUNIT_ASSERT (d3->GetHour () == 20);
      CPPUNIT_ASSERT (d3->GetMinute () == 07);
      CPPUNIT_ASSERT (d3->GetSecond () == 43);
      CPPUNIT_ASSERT (d3->GetMillisecond () == 437);

      CPPUNIT_ASSERT (d4->GetYear () == 2012);
      CPPUNIT_ASSERT (d4->GetMonth () == 3);
      CPPUNIT_ASSERT (d4->GetDay () == 25);
      CPPUNIT_ASSERT (d4->GetHour () == 0);
      CPPUNIT_ASSERT (d4->GetMinute () == 37);
      CPPUNIT_ASSERT (d4->GetSecond () == 10);
      CPPUNIT_ASSERT (d4->GetMillisecond () == 254);

      CPPUNIT_ASSERT (d5->GetYear () == 1970);
      CPPUNIT_ASSERT (d5->GetMonth () == 1);
      CPPUNIT_ASSERT (d5->GetDay () == 1);
      CPPUNIT_ASSERT (d5->GetHour () == 0);
      CPPUNIT_ASSERT (d5->GetMinute () == 0);
      CPPUNIT_ASSERT (d5->GetSecond () == 0);
      CPPUNIT_ASSERT (d5->GetMillisecond () == 0);

      CPPUNIT_ASSERT (d6->GetYear () == 4521);
      CPPUNIT_ASSERT (d6->GetMonth () == 12);
      CPPUNIT_ASSERT (d6->GetDay () == 25);
      CPPUNIT_ASSERT (d6->GetHour () == 18);
      CPPUNIT_ASSERT (d6->GetMinute () == 45);
      CPPUNIT_ASSERT (d6->GetSecond () == 7);
      CPPUNIT_ASSERT (d6->GetMillisecond () == 2);
    }

    void testCompare (void)
    {
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d1 == *d1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d1 == *d2));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d1 < *d3));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d1 < *d4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d1 == *d5));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d1 < *d6));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d2 == *d1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d2 == *d2));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d2 < *d3));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d2 < *d4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d2 == *d5));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d2 < *d6));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d3 > *d1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d3 > *d2));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d3 == *d3));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d3 < *d4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d3 > *d5));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d3 < *d6));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d4 > *d1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d4 > *d2));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d4 > *d3));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d4 == *d4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d4 > *d5));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d4 < *d6));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d5 == *d1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d5 == *d2));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d5 < *d3));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d5 < *d4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d5 == *d5));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d5 < *d6));

      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d6 > *d1));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d6 > *d2));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d6 > *d3));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d6 > *d4));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d6 > *d5));
      CPPUNIT_ASSERT_ASSERTION_PASS (CPPUNIT_ASSERT (*d6 == *d6));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d1 != *d1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d1 != *d2));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d1 >= *d3));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d1 >= *d4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d1 != *d5));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d1 >= *d6));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d2 != *d1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d2 != *d2));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d2 >= *d3));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d2 >= *d4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d2 != *d5));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d2 >= *d6));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d3 <= *d1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d3 <= *d2));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d3 != *d3));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d3 >= *d4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d3 <= *d5));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d3 >= *d6));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d4 <= *d1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d4 <= *d2));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d4 <= *d3));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d4 != *d4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d4 <= *d5));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d4 >= *d6));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d5 != *d1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d5 != *d2));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d5 >= *d3));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d5 >= *d4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d5 != *d5));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d5 >= *d6));

      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d6 <= *d1));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d6 <= *d2));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d6 <= *d3));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d6 <= *d4));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d6 <= *d5));
      CPPUNIT_ASSERT_ASSERTION_FAIL (CPPUNIT_ASSERT (*d6 != *d6));
    }

    void testSet (void)
    {
      Date test (*d6);
      CPPUNIT_ASSERT (test == *d6);
      test = *d4;
      CPPUNIT_ASSERT (test == *d4);
    }

    void testArithmetic (void)
    {
      Duration dur1 (5, -1, 4, 2, 0, 0, 0, 5);
      Duration dur2 (-1, 0, 0, 0, 0, 0, 0, 0);
      Duration dur3 (0, 18, 0, 56, 12, 2, -1, 45);

      CPPUNIT_ASSERT (*d1 + dur1 == dur1 + *d1);
      CPPUNIT_ASSERT (*d2 + dur1 == dur1 + *d2);
      CPPUNIT_ASSERT (*d3 + dur1 == dur1 + *d3);
      CPPUNIT_ASSERT (*d4 + dur1 == dur1 + *d4);
      CPPUNIT_ASSERT (*d5 + dur1 == dur1 + *d5);
      CPPUNIT_ASSERT (*d6 + dur1 == dur1 + *d6);

      // Can't add dur2 to epoch, as it is negative.
      CPPUNIT_ASSERT (*d4 + dur2 == dur2 + *d4);
      CPPUNIT_ASSERT (*d6 + dur2 == dur2 + *d6);

      CPPUNIT_ASSERT (*d1 + dur3 == dur3 + *d1);
      CPPUNIT_ASSERT (*d2 + dur3 == dur3 + *d2);
      CPPUNIT_ASSERT (*d3 + dur3 == dur3 + *d3);
      CPPUNIT_ASSERT (*d4 + dur3 == dur3 + *d4);
      CPPUNIT_ASSERT (*d5 + dur3 == dur3 + *d5);
      CPPUNIT_ASSERT (*d6 + dur3 == dur3 + *d6);

      CPPUNIT_ASSERT (*d1 + dur1 == Date (1974, 12, 31, 0, 0, 0, 5));
      CPPUNIT_ASSERT (*d1 + dur3 == Date (1971, 8, 26, 12, 1, 59, 45));

      CPPUNIT_ASSERT (*d2 + dur1 == Date (1974, 12, 31, 0, 0, 0, 5));
      CPPUNIT_ASSERT (*d2 + dur3 == Date (1971, 8, 26, 12, 1, 59, 45));

      CPPUNIT_ASSERT (*d3 + dur1 == Date (1974, 12, 31, 20, 7, 43, 442));
      CPPUNIT_ASSERT (*d3 + dur3 == Date (1971, 8, 27, 8, 9, 42, 482));

      CPPUNIT_ASSERT (*d4 + dur1 == Date (2017, 3, 27, 0, 37, 10, 259));
      CPPUNIT_ASSERT (*d4 + dur2 == Date (2011, 3, 25, 0, 37, 10, 254));
      CPPUNIT_ASSERT (*d4 + dur3 == Date (2013, 11, 20, 12, 39, 9, 299));

      CPPUNIT_ASSERT (*d5 + dur1 == Date (1974, 12, 31, 0, 0, 0, 5));
      CPPUNIT_ASSERT (*d5 + dur3 == Date (1971, 8, 26, 12, 1, 59, 45));

      CPPUNIT_ASSERT (*d6 + dur1 == Date (4526, 12, 25, 18, 45, 7, 7));
      CPPUNIT_ASSERT (*d6 + dur2 == Date (4520, 12, 25, 18, 45, 7, 2));
      CPPUNIT_ASSERT (*d6 + dur3 == Date (4523, 8, 21, 6, 47, 6, 47));
    }

};


CPPUNIT_TEST_SUITE_REGISTRATION (TimezoneTest);
CPPUNIT_TEST_SUITE_REGISTRATION (DurationTest);
CPPUNIT_TEST_SUITE_REGISTRATION (DateTest);

int
main (void)
{
  CppUnit::TestResult controller;
  CppUnit::TestResultCollector result;
  controller.addListener (&result);
  CppUnit::TextOutputter output (&result, std::cout);

  CppUnit::BriefTestProgressListener progress;
  controller.addListener (&progress);


  CppUnit::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry = 
    CppUnit::TestFactoryRegistry::getRegistry ();
  
  runner.addTest (registry.makeTest ());
  runner.run (controller);

  output.printFailures ();
  output.printStatistics ();
 
  return result.wasSuccessful () ? 0 : 1;  
}
