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
#define HUMMSTRUMM_ENGINE_SOURCE

#include <iostream>
#include <cmath>
#include <vector>

#include "hummstrummengine.hpp"

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

using namespace hummstrumm::engine::math;
using namespace hummstrumm::engine::geometry;

class PlaneTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( PlaneTest );
  CPPUNIT_TEST ( testConstructor );
  CPPUNIT_TEST_SUITE_END ();

  public:
    void setUp () {}

    void tearDown () {}


    void testConstructor ()
    {
      Vector3D <float> p1 (0.0f,  1.0f, -7.0f);
      Vector3D <float> p2 (3.0f,  1.0f, -9.0f);
      Vector3D <float> p3 (0.0f, -5.0f, -8.0f);
      
      Plane3D <float> p (p1, p2, p3);

      CPPUNIT_ASSERT_EQUAL ( -12.0f, p.normal.coord.x  );
      CPPUNIT_ASSERT_EQUAL (   3.0f, p.normal.coord.y  );
      CPPUNIT_ASSERT_EQUAL ( -18.0f, p.normal.coord.z  );
      CPPUNIT_ASSERT_EQUAL ( 129.0f, p.d  );

      p.Normalize();

      Plane3D  <float> q (1.0f, 2.0f, 2.0f, 6.0f);
      CPPUNIT_ASSERT_EQUAL ( 1.0f, q.normal.coord.x  );
      CPPUNIT_ASSERT_EQUAL ( 2.0f, q.normal.coord.y  );
      CPPUNIT_ASSERT_EQUAL ( 2.0f, q.normal.coord.z  );
      CPPUNIT_ASSERT_EQUAL ( 6.0f, q.d  );

      Vector3D <float> point (3.0f, 1.0f, 0.5f);
      q.Normalize();

    }
};

class SegmentTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( SegmentTest );
  CPPUNIT_TEST ( testConstructor );
  CPPUNIT_TEST_SUITE_END ();

  public:
    void setUp () {}

    void tearDown () {}


    void testConstructor ()
    {
      Vector3D <float> v1 (1.0f,  2.0f, -2.0f);
      Vector3D <float> v2 (3.0f, -2.0f,  1.0f);
      
      Segment3D <float> s (v1, v2);

      CPPUNIT_ASSERT ( v1 == s.start );
      CPPUNIT_ASSERT ( v2 == s.end );    

    }
};

class BoundingSphereTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( BoundingSphereTest );
  CPPUNIT_TEST ( testConstructor );
  CPPUNIT_TEST_SUITE_END ();

  public:
    void setUp () {}

    void tearDown () {}


    void testConstructor ()
    {


    }
};


CPPUNIT_TEST_SUITE_REGISTRATION ( PlaneTest );
CPPUNIT_TEST_SUITE_REGISTRATION ( SegmentTest );
CPPUNIT_TEST_SUITE_REGISTRATION ( BoundingSphereTest );

int
main ()
{
  CppUnit::TestResult controller;
  CppUnit::TestResultCollector result;
  controller.addListener (&result);
  CppUnit::TextOutputter output (&result, std::cout);

  CppUnit::BriefTestProgressListener progress;
  controller.addListener (&progress);


  CppUnit::TestRunner runner;
  CppUnit::TestFactoryRegistry& registry = 
    CppUnit::TestFactoryRegistry::getRegistry ();
  
  runner.addTest ( registry.makeTest() );
  runner.run (controller);

  output.printFailures ();
  output.printStatistics ();
 
  return result.wasSuccessful() ? 0 : 1;  
}
