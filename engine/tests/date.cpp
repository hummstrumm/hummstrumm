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
      utc        = new Timezone (0);
      utcMinus10 = new Timezone (-10*60);
      utcPlus4   = new Timezone (4*60);
      utcPlus1   = new Timezone (1*60);
    }

    void testStorage (void)
    {
      CPPUNIT_ASSERT_EQUAL (utc->GetOffset (),        0);
      CPPUNIT_ASSERT_EQUAL (utcMinus10->GetOffset (), -10*60);
      CPPUNIT_ASSERT_EQUAL (utcPlus4->GetOffset (),   4*60);
      CPPUNIT_ASSERT_EQUAL (utcPlus1->GetOffset (),   1*60);
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

CPPUNIT_TEST_SUITE_REGISTRATION (TimezoneTest);

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
