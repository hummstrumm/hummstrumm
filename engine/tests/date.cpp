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
    CPPUNIT_TEST (testSet);
    CPPUNIT_TEST (testCompare);
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


CPPUNIT_TEST_SUITE_REGISTRATION (TimezoneTest);
CPPUNIT_TEST_SUITE_REGISTRATION (DurationTest);

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
