// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2010, the people listed in the AUTHORS file. 
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

#include <iostream>
#include <cmath>
#include <vector>

#include "math/vector.hpp"

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

// @todo Finish the rest of the test cases for Vec2D, 3D and 4D.
// @todo Finish the testOrthonormalize

using namespace hummstrumm::engine::math;

class VectorTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( VectorTest );
  CPPUNIT_TEST ( testConstructor );
  CPPUNIT_TEST ( testCopyConstructor );
  CPPUNIT_TEST ( testAssignment );
  CPPUNIT_TEST ( testEquality );
  CPPUNIT_TEST ( testInequality );
  CPPUNIT_TEST ( testMinus );
  CPPUNIT_TEST ( testSum );
  CPPUNIT_TEST ( testNegation );
  CPPUNIT_TEST ( testDivision );
  CPPUNIT_TEST ( testMultiplication );
  CPPUNIT_TEST ( testNormalize );
  CPPUNIT_TEST ( testPerpendicular );
  CPPUNIT_TEST ( testUnitPerpendicular );
  CPPUNIT_TEST ( testOrthonormalize );
  CPPUNIT_TEST ( testDotProduct );
  CPPUNIT_TEST_SUITE_END ();

  public:

    void setUp () {}

    void tearDown () {}

    void testConstructor ()
    {
      Vector2D <float> v2_0;
      Vector2D <float> v2_1 ( 3.0f, 4.0f );

      CPPUNIT_ASSERT_EQUAL ( v2_0.x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_0.y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_1.x, 3.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_1.y, 4.0f );
    }

    void testCopyConstructor ()
    {
      Vector2D <float> v2_0;
      Vector2D <float> v2_1 ( 3.0f, 4.0f );
      Vector2D <float> v2_2 ( v2_1 );

      CPPUNIT_ASSERT_EQUAL ( v2_2.x, 3.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.y, 4.0f );
    }

    void testAssignment ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_1 = v2_0;

      CPPUNIT_ASSERT_EQUAL ( v2_1.x, -4.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_1.y,  5.0f );
    }

    void testEquality ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_1 = v2_0;

      CPPUNIT_ASSERT ( v2_0 == v2_1 );

    }

    void testInequality ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_1;

      CPPUNIT_ASSERT ( v2_0 != v2_1 );
    }

    void testMinus ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_1 (3.0f, 10.0f);
      Vector2D <float> v2_2;
  
      v2_2 = v2_0 - v2_1;
      CPPUNIT_ASSERT_EQUAL ( v2_2.x, -7.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.y, -5.0f );
    }

    void testNegation ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_2;
  
      v2_2 = - v2_0;
      CPPUNIT_ASSERT_EQUAL ( v2_2.x, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.y, -5.0f );
    }


    void testSum ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_1 (3.0f, 10.0f);
      Vector2D <float> v2_2;
  
      v2_2 = v2_0 + v2_1;
      CPPUNIT_ASSERT_EQUAL ( v2_2.x, -1.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.y, 15.0f );
    }

    void testDivision ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_2;
      float scalar = 2.0f;
  
      v2_2 = v2_0 / scalar;
      CPPUNIT_ASSERT_EQUAL ( v2_2.x, -2.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.y, 5.0f/scalar );
    }

    void testMultiplication ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_2;
      float scalar = 2.0f;
  
      v2_2 = v2_0 * scalar;
      CPPUNIT_ASSERT_EQUAL ( v2_2.x, -8.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.y, 10.0f );
    }

    void testNormalize ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      v2_0.normalize ();
      
      float expectedX = (1/sqrt(41.0f))*-4.0f;
      float expectedY = (1/sqrt(41.0f))*5.0f;
      CPPUNIT_ASSERT_EQUAL ( v2_0.x, expectedX );
      CPPUNIT_ASSERT_EQUAL ( v2_0.y, expectedY );
    }

    void testPerpendicular ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_2;

      v2_2 = v2_0.Perpendicular ();
      CPPUNIT_ASSERT_EQUAL ( v2_2.x, 5.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.y, 4.0f );
    }

    void testUnitPerpendicular ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_2;
      float mag = sqrt ( v2_0.x*v2_0.x + v2_0.y*v2_0.y ); 
      v2_2 = v2_0.UnitPerpendicular ();

      float expectedX = 5.0f/mag;
      float expectedY = 4.0f/mag;

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( expectedX, v2_2.x , 0.0001 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( expectedY, v2_2.y , 0.0001 );
    }

    void testOrthonormalize ()
    {
      std::vector <Vector4D<float> > v4;
      std::vector <Vector3D<float> > v3;
      std::vector <Vector2D<float> > v2;

      Vector2D <float> v2_0 ( 1.0f, 3.0f );
      Vector2D <float> v2_1 ( 0.0f, 2.0f );

      Vector3D <float> v3_0 ( 2.0f, -1.0f, 0.0f );
      Vector3D <float> v3_1 ( 1.0f, 0.0f, -1.0f );
      Vector3D <float> v3_2 ( 3.0f, 7.0f, -1.0f );

      Vector4D <float> v4_0 ( 2.0f, -1.0f, 0.0f, 1.0f );
      Vector4D <float> v4_1 ( 1.0f, 0.0f, -1.0f, 5.0f );
      Vector4D <float> v4_2 ( 3.0f, 7.0f, -1.0f, 9.0f );
      Vector4D <float> v4_3 ( 3.0f, 7.0f, -1.0f, 2.0f );

      v2.push_back(v2_0);
      v2.push_back(v2_1);

      Orthonormalize2D ( v2 );

      v2_1 = v2.back();
      v2.pop_back();
      v2_0 = v2.back();
      v2.pop_back();
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, v2_0.dot(v2_1), 0.01);

      v3.push_back(v3_0);
      v3.push_back(v3_1);
      v3.push_back(v3_2);

      Orthonormalize3D ( v3 );

      v3_2 = v3.back();
      v3.pop_back();
      v3_1 = v3.back();
      v3.pop_back();
      v3_0 = v3.back();
      v3.pop_back();

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, v3_0.dot(v3_1), 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, v3_0.dot(v3_2), 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, v3_1.dot(v3_2), 0.01);

      v4.push_back(v4_0);
      v4.push_back(v4_1);
      v4.push_back(v4_2);
      v4.push_back(v4_3);

      Orthonormalize4D ( v4 );

      v4_3 = v4.back();
      v4.pop_back();
      v4_2 = v4.back();
      v4.pop_back();
      v4_1 = v4.back();
      v4.pop_back();
      v4_0 = v4.back();
      v4.pop_back();

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, v4_0.dot(v4_1), 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, v4_0.dot(v4_2), 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, v4_0.dot(v4_2), 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, v4_1.dot(v4_2), 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, v4_2.dot(v4_3), 0.01);

    }


    void testDotProduct ()
    {
      hummstrumm::engine::math::Vector2D <float> v2_0;
      hummstrumm::engine::math::Vector2D <float> v2_1 (3.0f, 4.0f);

      CPPUNIT_ASSERT_EQUAL ( v2_0.dot(v2_1), 0.0f ); 
    }

  private:

};

CPPUNIT_TEST_SUITE_REGISTRATION ( VectorTest );

int
main (int argc, char **argv)
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
