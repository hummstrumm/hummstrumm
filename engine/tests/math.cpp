// -*- c++ -*-
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
#define HUMMSTRUMM_ENGINE_SOURCE

#include <iostream>
#include <cmath>
#include <vector>
#include <climits>

#include "hummstrummengine.hpp"

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

using namespace hummstrumm::engine::math;
using namespace hummstrumm::engine::debug;
using namespace hummstrumm::engine::core;

class QuaternionsTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( QuaternionsTest );
  CPPUNIT_TEST ( testLogExpPow );
  CPPUNIT_TEST ( testMultiplication );
  CPPUNIT_TEST_SUITE_END ();

  public:
    void setUp () {}

    void tearDown () {}

    void testMultiplication ()
    {
      Quaternion <float> q0 ( 1, 2, 3, 4);
      Quaternion <float> q5 ( 1, 1, 1, 1);

      Quaternion <float> q1 ( 3, 2, 5, 4);
      Quaternion <float> q2 ( 4, 5, 3, 1);

      Quaternion <float> q0Expected;
      q0.Normalize();
      q5.Normalize();
      q0Expected = q0*q5;
      // expect a unit quaternion
      CPPUNIT_ASSERT (QuatMagnitude(q0Expected) == 1);
      q0Expected = q1*q2;
      CPPUNIT_ASSERT_DOUBLES_EQUAL (-17, q0Expected.w,   0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 16, q0Expected.v.coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 47, q0Expected.v.coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL (  0, q0Expected.v.coord.z, 0.01);

    }

    void testLogExpPow ()
    { 
      float exponent = 2;
      Quaternion <float> q0 ( 4, 1, 2, 3);
      Quaternion <float> q1 ( 1, 0, 0, 0);
      Quaternion <float> q2 ( 2, 0, 0, 0);
      Quaternion <float> q3 ( 0, 1, 0, 0);
      Quaternion <float> q4 ( 0, 2, 0, 0);
      Quaternion <float> q5 ( 1, 1, 1, 1);
      Quaternion <float> q6 ( 3, 3, 3, 3);
      Quaternion <float> q7 (-4,-4,-4,-4);
      Quaternion <float> q0Expected,
                         q1Expected,
                         q2Expected,
                         q3Expected,
                         q4Expected,
                         q5Expected,
                         q6Expected,
                         q7Expected;

      q0Expected = QuatLog (q0);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 1.7006,   q0Expected.w,   0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.200991, q0Expected.v.coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.401982, q0Expected.v.coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.602974, q0Expected.v.coord.z, 0.01);

      q1Expected = QuatLog (q1);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, q1Expected.w,   0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, q1Expected.v.coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, q1Expected.v.coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, q1Expected.v.coord.z, 0.01);

      q2Expected = QuatLog (q2);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.693147, q2Expected.w,   0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0,        q2Expected.v.coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0,        q2Expected.v.coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0,        q2Expected.v.coord.z, 0.01);

      q3Expected = QuatLog (q3);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0,        q3Expected.w,   0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 1.5708,   q3Expected.v.coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0,        q3Expected.v.coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0,        q3Expected.v.coord.z, 0.01);

      q4Expected = QuatLog (q4);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.693147, q4Expected.w,   0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 1.5708,   q4Expected.v.coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0,        q4Expected.v.coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0,        q4Expected.v.coord.z, 0.01);

      q5Expected = QuatLog (q5);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.693147, q5Expected.w,   0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.6046,   q5Expected.v.coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.6046,   q5Expected.v.coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.6046,   q5Expected.v.coord.z, 0.01);

      q6Expected = QuatLog (q6);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 1.79176, q6Expected.w,   0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.6046,  q6Expected.v.coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.6046,  q6Expected.v.coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.6046,  q6Expected.v.coord.z, 0.01);

      q7Expected = QuatLog (q7);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 2.07944, q7Expected.w,   0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( -1.2092, q7Expected.v.coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( -1.2092, q7Expected.v.coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( -1.2092, q7Expected.v.coord.z, 0.01);

      q0Expected = QuatExp (QuatLog (q0));
      CPPUNIT_ASSERT_DOUBLES_EQUAL (q0.w,   q0Expected.w,   0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL (q0.v.coord.x, q0Expected.v.coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL (q0.v.coord.y, q0Expected.v.coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL (q0.v.coord.z, q0Expected.v.coord.z, 0.01);

      q0Expected = QuatLog (QuatExp (q0));
      CPPUNIT_ASSERT_DOUBLES_EQUAL (4,         q0Expected.w,   0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL (-0.679252, q0Expected.v.coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.3585,   q0Expected.v.coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL (-2.03776,  q0Expected.v.coord.z, 0.01);


      q0Expected = QuatPow (q0,q0);
      CPPUNIT_ASSERT_DOUBLES_EQUAL (-53.8975, q0Expected.w,   0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL (0.772254, q0Expected.v.coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL (1.54451,  q0Expected.v.coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL (2.31676,  q0Expected.v.coord.z, 0.01);

      q0Expected = QuatPow (q0,exponent);      
    }
};


class MatricesTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( MatricesTest );  
  CPPUNIT_TEST ( testConstructor );
  CPPUNIT_TEST ( testAssignment );
  CPPUNIT_TEST ( testEquality );
  CPPUNIT_TEST ( testInequality );
  CPPUNIT_TEST ( testNegate );
  CPPUNIT_TEST ( testSubtraction );
  CPPUNIT_TEST ( testAdd );
  CPPUNIT_TEST ( testMultiplication );
  CPPUNIT_TEST ( testDivision );
  CPPUNIT_TEST ( testDeterminant );
  CPPUNIT_TEST ( testInverse );
  CPPUNIT_TEST_SUITE_END ();
  public:

    void setUp () {}

    void tearDown () {}

    void testConstructor ()
    {
      Matrix2D <float> m2_1;
      Matrix3D <float> m3_1;
      Matrix4D <float> m4_1;

      CPPUNIT_ASSERT_EQUAL ( m2_1[0].coord.x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_1[0].coord.y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_1[1].coord.x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_1[1].coord.y, 0.0f );

      CPPUNIT_ASSERT_EQUAL ( m3_1[0].coord.x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[0].coord.y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[0].coord.z, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[1].coord.x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[1].coord.y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[1].coord.z, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[2].coord.x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[2].coord.y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[2].coord.z, 0.0f );

      CPPUNIT_ASSERT_EQUAL ( m4_1[0].coord.x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[0].coord.y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[0].coord.z, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[0].coord.w, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[1].coord.x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[1].coord.y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[1].coord.z, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[1].coord.w, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[2].coord.x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[2].coord.y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[2].coord.z, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[2].coord.w, 0.0f );


      Matrix2D <float> m2_2 (2, 3,
                             4, 5);

      Matrix3D <float> m3_2 ( 2,  3,  4,
                              5,  6,  7,
                             -1, -2, -3);

      Matrix4D <float> m4_2 (   2,      3,     4,      5,
                             -0.01f,   0.5f,  3.24f,     -3,
                              -1.4f, -20.1f,  -300, -41.23f,
                                 0,  -678, -1.02f,    -10  );

      CPPUNIT_ASSERT_EQUAL ( m2_2[0].coord.x,  2.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_2[0].coord.y,  3.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_2[1].coord.x,  4.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_2[1].coord.y,  5.0f );

      CPPUNIT_ASSERT_EQUAL ( m3_2[0].coord.x,  2.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[0].coord.y,  3.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[0].coord.z,  4.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[1].coord.x,  5.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[1].coord.y,  6.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[1].coord.z,  7.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[2].coord.x, -1.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[2].coord.y, -2.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[2].coord.z, -3.0f );

      CPPUNIT_ASSERT_EQUAL ( m4_2[0].coord.x,    2.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[0].coord.y,    3.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[0].coord.z,    4.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[0].coord.w,    5.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[1].coord.x,  -0.01f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[1].coord.y,    0.5f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[1].coord.z,   3.24f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[1].coord.w,   -3.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[2].coord.x,   -1.4f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[2].coord.y,  -20.1f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[2].coord.z, -300.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[2].coord.w, -41.23f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[3].coord.x,    0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[3].coord.y, -678.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[3].coord.z,  -1.02f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[3].coord.w,  -10.0f );

      Vector2D <float> v1 ( 6, 7);
      Vector2D <float> v2 ( 9, 0);
      Matrix2D <float> m2_3 ( v1, v2);

      Vector3D <float> v3_1 ( 6, 7, 8);
      Vector3D <float> v3_2 ( 9, 0, -1);

      Vector3D <float> v3_3 ( -10, -0.01f, -0.1f);

      Matrix3D <float> m3_3 ( v3_1, v3_2, v3_3);

      Vector4D <float> v4_1 ( 6, 7, 8, -1.3f);
      Vector4D <float> v4_2 ( 9, 0,-1, -3.1f);

      Vector4D <float> v4_3 ( -10, -0.01f, -0.1f, -4.2f);
      Vector4D <float> v4_4 (-0.1f,  -134, -1.9f, -5.5f);

      Matrix4D <float> m4_3 ( v4_1, v4_2, v4_3, v4_4);

      CPPUNIT_ASSERT_EQUAL ( m2_3[0].coord.x,  6.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[0].coord.y,  7.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].coord.x,  9.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].coord.y,  0.0f );

      CPPUNIT_ASSERT_EQUAL ( m3_3[0].coord.x,  6.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[0].coord.y,  7.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[0].coord.z,  8.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[1].coord.x,  9.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[1].coord.y,  0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[1].coord.z, -1.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[2].coord.x,-10.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[2].coord.y,-0.01f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[2].coord.z, -0.1f );

      CPPUNIT_ASSERT_EQUAL ( m4_3[0].coord.x,   6.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[0].coord.y,   7.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[0].coord.z,   8.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[0].coord.w,  -1.3f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[1].coord.x,   9.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[1].coord.y,   0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[1].coord.z,  -1.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[1].coord.w,  -3.1f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[2].coord.x, -10.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[2].coord.y, -0.01f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[2].coord.z,  -0.1f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[2].coord.w,  -4.2f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[3].coord.x,  -0.1f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[3].coord.y,-134.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[3].coord.z,  -1.9f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[3].coord.w,  -5.5f );

      // copy constructor
      Matrix2D <float> m2_4 (m2_3);

      CPPUNIT_ASSERT_EQUAL ( m2_4[0].coord.x, m2_3[0].coord.x );
      CPPUNIT_ASSERT_EQUAL ( m2_4[0].coord.y, m2_3[0].coord.y );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].coord.x, m2_3[1].coord.x );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].coord.y, m2_3[1].coord.y );

       // copy constructor
      Matrix3D <float> m3_4 (m3_3);

      CPPUNIT_ASSERT_EQUAL ( m3_4[0].coord.x, m3_3[0].coord.x );
      CPPUNIT_ASSERT_EQUAL ( m3_4[0].coord.y, m3_3[0].coord.y );
      CPPUNIT_ASSERT_EQUAL ( m3_4[0].coord.z, m3_3[0].coord.z );
      CPPUNIT_ASSERT_EQUAL ( m3_4[1].coord.x, m3_3[1].coord.x );
      CPPUNIT_ASSERT_EQUAL ( m3_4[1].coord.y, m3_3[1].coord.y );
      CPPUNIT_ASSERT_EQUAL ( m3_4[1].coord.z, m3_3[1].coord.z );
      CPPUNIT_ASSERT_EQUAL ( m3_4[2].coord.x, m3_3[2].coord.x );
      CPPUNIT_ASSERT_EQUAL ( m3_4[2].coord.y, m3_3[2].coord.y );
      CPPUNIT_ASSERT_EQUAL ( m3_4[2].coord.z, m3_3[2].coord.z );

      // copy constructor
      Matrix4D <float> m4_4 (m4_3);

      CPPUNIT_ASSERT_EQUAL ( m4_4[0].coord.x, m4_3[0].coord.x );
      CPPUNIT_ASSERT_EQUAL ( m4_4[0].coord.y, m4_3[0].coord.y );
      CPPUNIT_ASSERT_EQUAL ( m4_4[0].coord.z, m4_3[0].coord.z );
      CPPUNIT_ASSERT_EQUAL ( m4_4[0].coord.w, m4_3[0].coord.w );
      CPPUNIT_ASSERT_EQUAL ( m4_4[1].coord.x, m4_3[1].coord.x );
      CPPUNIT_ASSERT_EQUAL ( m4_4[1].coord.y, m4_3[1].coord.y );
      CPPUNIT_ASSERT_EQUAL ( m4_4[1].coord.z, m4_3[1].coord.z );
      CPPUNIT_ASSERT_EQUAL ( m4_4[1].coord.w, m4_3[1].coord.w );
      CPPUNIT_ASSERT_EQUAL ( m4_4[2].coord.x, m4_3[2].coord.x );
      CPPUNIT_ASSERT_EQUAL ( m4_4[2].coord.y, m4_3[2].coord.y );
      CPPUNIT_ASSERT_EQUAL ( m4_4[2].coord.z, m4_3[2].coord.z );
      CPPUNIT_ASSERT_EQUAL ( m4_4[2].coord.w, m4_3[2].coord.w );
      CPPUNIT_ASSERT_EQUAL ( m4_4[3].coord.x, m4_3[3].coord.x );
      CPPUNIT_ASSERT_EQUAL ( m4_4[3].coord.y, m4_3[3].coord.y );
      CPPUNIT_ASSERT_EQUAL ( m4_4[3].coord.z, m4_3[3].coord.z );
      CPPUNIT_ASSERT_EQUAL ( m4_4[3].coord.w, m4_3[3].coord.w );
     
    }

    void testAssignment ()
    {
      Matrix2D <float> m2_3 ( 3, 4, -2, -5);
      Matrix2D <float> m2_4;
      m2_4 = m2_3;

      CPPUNIT_ASSERT_EQUAL ( m2_4[0].coord.x, m2_3[0].coord.x );
      CPPUNIT_ASSERT_EQUAL ( m2_4[0].coord.y, m2_3[0].coord.y );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].coord.x, m2_3[1].coord.x );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].coord.y, m2_3[1].coord.y );

    }

    void testEquality ()
    {
      Matrix2D <float> m2_3 ( 3, 4, -2, -5);

      Matrix2D <float> m2_4 ( 3.0, 4.0, -2, -5.0);

      CPPUNIT_ASSERT ( m2_3 == m2_4 );

    }

    void testInequality ()
    {

      Matrix2D <float> m2_3 ( 3, 4, -1, -5);

      Matrix2D <float> m2_4 ( 3.0, 4.0, -2, -5.0);

      CPPUNIT_ASSERT ( m2_3 != m2_4 );
    }

    void testNegate ()
    {

      Matrix2D <float> m2_3 ( 3, 4, -1, -5);
      Matrix2D <float> m2_4;

      m2_4 = -m2_3;  

      CPPUNIT_ASSERT_EQUAL ( m2_4[0].coord.x, -3.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[0].coord.y, -4.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].coord.x,  1.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].coord.y,  5.0f );
     
    }

    void testSubtraction ()
    {

      Matrix2D <float> m2_3 ( 3,  4, -1, -5);
      Matrix2D <float> m2_4 ( 2,  1,  3,  6);
      m2_4 = m2_4 - m2_3;

      CPPUNIT_ASSERT_EQUAL ( m2_4[0].coord.x, -1.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[0].coord.y, -3.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].coord.x,  4.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].coord.y, 11.0f );

      Matrix2D <float> m2_5 ( -1, -1, -1, 0);
      m2_5 -= m2_4;

      CPPUNIT_ASSERT_EQUAL ( m2_5[0].coord.x,  0.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_5[0].coord.y,  2.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_5[1].coord.x, -5.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_5[1].coord.y, -11.0f );

    }

    void testAdd ()
    {

      Matrix2D <float> m2_3 ( 3,  4,  -1,  -5);
      Matrix2D <float> m2_4 ( 2,  1,  3,  6);
      m2_4 = m2_4 + m2_3;

      CPPUNIT_ASSERT_EQUAL ( m2_4[0].coord.x, 5.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[0].coord.y, 5.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].coord.x, 2.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].coord.y, 1.0f );

      Matrix2D <float> m2_5 ( -1, -1, -1, 0);
      m2_5 += m2_4;

      CPPUNIT_ASSERT_EQUAL ( m2_5[0].coord.x, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_5[0].coord.y, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_5[1].coord.x, 1.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_5[1].coord.y, 1.0f );

      m2_5 = m2_4 + m2_3;

    }

    void testMultiplication ()
    {

      Matrix2D <float> m2_3 ( 3,  4,  -1,  -5);
      float scalar = 3;
      m2_3 = m2_3 * scalar;

      CPPUNIT_ASSERT_EQUAL ( m2_3[0].coord.x,   9.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[0].coord.y,  12.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].coord.x,  -3.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].coord.y, -15.0f );

      m2_3 *= scalar;

      CPPUNIT_ASSERT_EQUAL ( m2_3[0].coord.x,  27.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[0].coord.y,  36.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].coord.x,  -9.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].coord.y, -45.0f );

      m2_3 = scalar * m2_3;

      CPPUNIT_ASSERT_EQUAL ( m2_3[0].coord.x,   81.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[0].coord.y,  108.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].coord.x,  -27.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].coord.y, -135.0f );

      // Matrix multiplcation
      Matrix2D<float> m2_4 (4, 5, 6, -0.5);
      Matrix2D<float> m2_5;

      m2_5 = m2_3*m2_4;
      CPPUNIT_ASSERT_EQUAL (  972.0f, m2_5[0].coord.x );
      CPPUNIT_ASSERT_EQUAL (  351.0f, m2_5[0].coord.y );
      CPPUNIT_ASSERT_EQUAL ( -918.0f, m2_5[1].coord.x );
      CPPUNIT_ASSERT_EQUAL (  -67.5f, m2_5[1].coord.y );
      m2_5 *= m2_4;
      CPPUNIT_ASSERT_EQUAL (   5994.0f,  m2_5[0].coord.x );
      CPPUNIT_ASSERT_EQUAL (   4684.5f,  m2_5[0].coord.y );
      CPPUNIT_ASSERT_EQUAL (  -4077.0f,  m2_5[1].coord.x );
      CPPUNIT_ASSERT_EQUAL ( -4556.250f, m2_5[1].coord.y );


      Matrix3D<float> m3_1 ( 3,  6,  1,
                             4,  3, -5,
                            -1, -3,  9);

      Matrix3D<float> m3_2 ( 5,  7,  1,
                             4,  2, -5,
                            -1, -1,  9);
      Matrix3D<float> m3_0;
      m3_0 = m3_1*m3_2;
      CPPUNIT_ASSERT_EQUAL (  38.0f, m3_0[0].coord.x );
      CPPUNIT_ASSERT_EQUAL (  32.0f, m3_0[0].coord.y );
      CPPUNIT_ASSERT_EQUAL ( -18.0f, m3_0[0].coord.z );
      CPPUNIT_ASSERT_EQUAL (  37.0f, m3_0[1].coord.x );
      CPPUNIT_ASSERT_EQUAL (  39.0f, m3_0[1].coord.y );
      CPPUNIT_ASSERT_EQUAL ( -56.0f, m3_0[1].coord.z );
      CPPUNIT_ASSERT_EQUAL ( -26.0f, m3_0[2].coord.x );
      CPPUNIT_ASSERT_EQUAL ( -22.0f, m3_0[2].coord.y );
      CPPUNIT_ASSERT_EQUAL (  95.0f, m3_0[2].coord.z );

      m3_0 *= m3_2;
      CPPUNIT_ASSERT_EQUAL (  336.0f, m3_0[0].coord.x );
      CPPUNIT_ASSERT_EQUAL (  348.0f, m3_0[0].coord.y );
      CPPUNIT_ASSERT_EQUAL ( -284.0f, m3_0[0].coord.z );
      CPPUNIT_ASSERT_EQUAL (  397.0f, m3_0[1].coord.x );
      CPPUNIT_ASSERT_EQUAL (  393.0f, m3_0[1].coord.y );
      CPPUNIT_ASSERT_EQUAL ( -662.0f, m3_0[1].coord.z );
      CPPUNIT_ASSERT_EQUAL ( -313.0f, m3_0[2].coord.x );
      CPPUNIT_ASSERT_EQUAL ( -321.0f, m3_0[2].coord.y );
      CPPUNIT_ASSERT_EQUAL (  939.0f, m3_0[2].coord.z );

      Matrix4D <float> m4_4 (3, 4, -1, -0.5f,
                            -5, 3,  2,    2,
                             3, 6,  7,    4,
                             7, 0,  0,    8);

      Matrix4D <float> m4_5 ( 0.035f,  -0.133f,   0.043f,  0.014f, 
                              0.181f,   0.092f,   0.000f, -0.012f,
                             -0.153f,  -0.089f,   0.146f, -0.061f,
                             -0.031f,   0.117f,  -0.038f,  0.113f);

      Matrix4D <float> m4_6;
      m4_6 = m4_4*m4_5;

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[0].coord.x, 1, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[0].coord.y, 0, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[0].coord.z, 0, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[0].coord.w, 0, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[1].coord.x, 0, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[1].coord.y, 1, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[1].coord.z, 0, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[1].coord.w, 0, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[2].coord.x, 0, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[2].coord.y, 0, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[2].coord.z, 1, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[2].coord.w, 0, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[3].coord.x, 0, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[3].coord.y, 0, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[3].coord.z, 0, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_6[3].coord.w, 1, 0.01);

      m4_6 *= m4_4; // precision loss

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[0].coord.x, m4_6[0].coord.x, 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[0].coord.y, m4_6[0].coord.y, 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[0].coord.z, m4_6[0].coord.z, 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[0].coord.w, m4_6[0].coord.w, 0.05);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[1].coord.x, m4_6[1].coord.x, 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[1].coord.y, m4_6[1].coord.y, 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[1].coord.z, m4_6[1].coord.z, 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[1].coord.w, m4_6[1].coord.w, 0.05);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[2].coord.x, m4_6[2].coord.x, 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[2].coord.y, m4_6[2].coord.y, 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[2].coord.z, m4_6[2].coord.z, 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[2].coord.w, m4_6[2].coord.w, 0.05);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[3].coord.x, m4_6[3].coord.x, 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[3].coord.y, m4_6[3].coord.y, 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[3].coord.z, m4_6[3].coord.z, 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[3].coord.w, m4_6[3].coord.w, 0.05);


    }

    void testDivision ()
    {

      Matrix2D <float> m2_3 ( 3, 4, -1, -5);
      float divisor = 2;
      m2_3 = m2_3 / divisor;

      CPPUNIT_ASSERT_DOUBLES_EQUAL (  3/divisor, m2_3[0].coord.x, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL (  4/divisor, m2_3[0].coord.y, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( -1/divisor, m2_3[1].coord.x, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( -5/divisor, m2_3[1].coord.y, 0.01 );

      Matrix2D <float> m2_4 (-0.5, 67, -7, 2);
      m2_4 /= divisor;

      CPPUNIT_ASSERT_DOUBLES_EQUAL (-0.5/divisor, m2_4[0].coord.x, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL (  67/divisor, m2_4[0].coord.y, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL (  -7/divisor, m2_4[1].coord.x, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL (   2/divisor, m2_4[1].coord.y, 0.01 );
   
    }

    void testDeterminant ()
    {

      Matrix2D <float> m2_3 (3, 4, -1, -5);

      Matrix3D <float> m3_1 ( 3.0f, -2.0f,  0.0f, 
                              1.0f,  4.0f, -3.0f, 
                             -1.0f,  0.0f,  2.0f);

      Matrix3D <float> m3_2 ( 3.0f, -1.0f, -0.5f, 
                             -5.0f,  2.0f,  2.0f, 
                              3.0f,  7.0f,  4.0f);

      Matrix4D <float> m4_1 (-2.0f, 2.0f,  2.0f, 7.0f,
                              5.0f, 8.0f, -5.0f, 2.0f,
                              5.0f, 8.0f,  9.0f, 2.0f,
                              2.0f, 5.0f,  6.0f, 4.0f);

      CPPUNIT_ASSERT_EQUAL ( m2_3.Determinant(),  -11.0f);
      CPPUNIT_ASSERT_EQUAL ( m3_1.Determinant(),   22.0f);
      CPPUNIT_ASSERT_EQUAL ( m3_2.Determinant(),  -23.5f);
      CPPUNIT_ASSERT_EQUAL ( m4_1.Determinant(), -182.0f);

    }

    void testInverse()
    {
      Matrix2D <float> m2_3 (0.455f, 0.364f, -0.091f, -0.273f);
      Matrix2D <float> m2_4 (3, 4, -1, -5);
      Matrix2D <float> m2_4Inv;

      Matrix3D <float> m3_4 (3, 4, -1, 
                            -5, 3,  2,
                             3, 6,  7);

      Matrix3D <float> m3_5 ( 0.039f,  -0.148f,   0.048f, 
                              0.178f,   0.104f,  -0.004f,
                             -0.170f,  -0.026f,   0.126f);
      Matrix3D <float> m3_4Inv;

      Matrix4D <float> m4_4 (3, 4, -1,   -5,
                            -5, 3,  2,    2,
                             3, 6,  7,    4,
                             7, 0,  0,    8);
/*
      Matrix4D <float> m4_5 ( 0.035f,  -0.133f,   0.043f,  0.014f, 
                              0.181f,   0.092f,   0.000f, -0.012f,
                             -0.153f,  -0.089f,   0.146f, -0.061f,
                             -0.031f,   0.117f,  -0.038f,  0.113f);
*/
      Matrix4D <float> m4_5 ( 0.031f, -0.117f,  0.038f,  0.030f,
                              0.159f,  0.176f, -0.028f,  0.069f,
                             -0.134f, -0.159f,  0.169f, -0.129f,
                             -0.027f,  0.102f, -0.033f,  0.099f);

      Matrix4D <float> m4_4Inv;


      m2_4Inv = Mat2DInverse(m2_4);
      m3_4Inv = Mat3DInverse(m3_4);
      m4_4Inv = Mat4DInverse(m4_4);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m2_3[0].coord.x, m2_4Inv[0].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m2_3[0].coord.y, m2_4Inv[0].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m2_3[1].coord.x, m2_4Inv[1].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m2_3[1].coord.y, m2_4Inv[1].coord.y, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_5[0].coord.x, m3_4Inv[0].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_5[0].coord.y, m3_4Inv[0].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_5[0].coord.z, m3_4Inv[0].coord.z, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_5[1].coord.x, m3_4Inv[1].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_5[1].coord.y, m3_4Inv[1].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_5[1].coord.z, m3_4Inv[1].coord.z, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_5[2].coord.x, m3_4Inv[2].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_5[2].coord.y, m3_4Inv[2].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_5[2].coord.z, m3_4Inv[2].coord.z, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[0].coord.x, m4_4Inv[0].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[0].coord.y, m4_4Inv[0].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[0].coord.z, m4_4Inv[0].coord.z, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[0].coord.w, m4_4Inv[0].coord.w, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[1].coord.x, m4_4Inv[1].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[1].coord.y, m4_4Inv[1].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[1].coord.z, m4_4Inv[1].coord.z, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[1].coord.w, m4_4Inv[1].coord.w, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[2].coord.x, m4_4Inv[2].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[2].coord.y, m4_4Inv[2].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[2].coord.z, m4_4Inv[2].coord.z, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[2].coord.w, m4_4Inv[2].coord.w, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[3].coord.x, m4_4Inv[3].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[3].coord.y, m4_4Inv[3].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[3].coord.z, m4_4Inv[3].coord.z, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_5[3].coord.w, m4_4Inv[3].coord.w, 0.01);

    }
    void testTranspose ()
    {

      Matrix2D <float> m2_4 (3,  4, 
                            -1, -5);

      Matrix2D <float> m2_4t (3, -1, 
                              4, -5);

      Matrix3D <float> m3_4 (3, 4, -1, 
                            -5, 3,  2,
                             3, 6,  7);

      Matrix3D <float> m3_4t ( 3, -5, 3,
                               4,  3, 6,
                              -1,  2, 7);

      Matrix4D <float> m4_4 (3,  4, -1, -0.5,
                            -5,  3,  2,    2,
                             3,  6,  7,    4,
                             7,  0,  0,    8);

      Matrix4D <float> m4_4t (   3,  -5,  3,  7,
                                 4,   3,  6,  0,
                                -1,   2,  7,  0,
                              -0.5,   2,  4,  8);

      m2_4t = Mat2DTranspose(m2_4);
      m3_4t = Mat3DTranspose(m3_4);
      m4_4t = Mat4DTranspose(m4_4);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m2_4[0].coord.x, m2_4t[0].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m2_4[0].coord.y, m2_4t[1].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m2_4[1].coord.x, m2_4t[0].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m2_4[1].coord.y, m2_4t[1].coord.y, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_4[0].coord.x, m3_4t[0].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_4[0].coord.y, m3_4t[1].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_4[0].coord.z, m3_4t[2].coord.x, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_4[1].coord.x, m3_4t[0].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_4[1].coord.y, m3_4t[1].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_4[1].coord.z, m3_4t[2].coord.y, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_4[2].coord.x, m3_4t[0].coord.z, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_4[2].coord.y, m3_4t[1].coord.z, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m3_4[2].coord.z, m3_4t[2].coord.z, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[0].coord.x, m4_4t[0].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[0].coord.y, m4_4t[1].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[0].coord.z, m4_4t[2].coord.x, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[0].coord.w, m4_4t[3].coord.x, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[1].coord.x, m4_4t[0].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[1].coord.y, m4_4t[1].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[1].coord.z, m4_4t[2].coord.y, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[1].coord.w, m4_4t[3].coord.y, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[2].coord.x, m4_4t[0].coord.z, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[2].coord.y, m4_4t[1].coord.z, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[2].coord.z, m4_4t[2].coord.z, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[2].coord.w, m4_4t[3].coord.z, 0.01);

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[3].coord.x, m4_4t[0].coord.w, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[3].coord.y, m4_4t[1].coord.w, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[3].coord.z, m4_4t[2].coord.w, 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( m4_4[3].coord.w, m4_4t[3].coord.w, 0.01);

    }
};

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
  //CPPUNIT_TEST ( testOrthonormalize );
  CPPUNIT_TEST ( testDotProduct );
  CPPUNIT_TEST_SUITE_END ();
  public:

    void setUp () {}

    void tearDown () {}

    void testConstructor ()
    {
      Vector2D <float> v2_0;
      Vector2D <float> v2_1 ( 3.0f, 4.0f );

      Vector4D <float> v4_0;
      Vector4D <float> v4_1 ( 3.0f, 4.0f, 1.0f, -0.5f );


      CPPUNIT_ASSERT_EQUAL ( v2_0.coord.x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_0.coord.y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_1.coord.x, 3.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_1.coord.y, 4.0f );

      CPPUNIT_ASSERT_EQUAL ( v4_0.coord.x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_0.coord.y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_0.coord.z, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_0.coord.w, 0.0f );

      CPPUNIT_ASSERT_EQUAL ( v4_1.coord.x, 3.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_1.coord.y, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_1.coord.z, 1.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_1.coord.w, -0.5f );


    }

    void testCopyConstructor ()
    {
      Vector2D <float> v2_0;
      Vector2D <float> v2_1 ( 3.0f, 4.0f );
      Vector2D <float> v2_2 ( v2_1 );

      Vector4D <float> v4_0;
      Vector4D <float> v4_1 ( 3.0f, 4.0f, 1.0f, -0.5f );
      Vector4D <float> v4_2 ( v4_1 );

      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.x, 3.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.y, 4.0f );

      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.x, 3.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.y, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.z, 1.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.w, -.5f );

    }

    void testAssignment ()
    {
      Vector2D <float> v2_0 ( -4.0f, 5.0f);
      Vector2D <float> v2_1 = v2_0;
 
      Vector4D <float> v4_0 ( -4.0f, 5.0f, 1.0f, -0.5f);
      Vector4D <float> v4_1 = v4_0;

      CPPUNIT_ASSERT_EQUAL ( v2_1.coord.x, -4.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_1.coord.y,  5.0f );

      CPPUNIT_ASSERT_EQUAL ( v4_1.coord.x, -4.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_1.coord.y,  5.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_1.coord.z,  1.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_1.coord.w,  -.5f );
    }

    void testEquality ()
    {
      Vector2D <float> v2_0 ( -4.0f, 5.0f);
      Vector2D <float> v2_1 = v2_0;

      Vector4D <float> v4_0 ( -4.0f, 5.0f, 1.0f, -.5f);
      Vector4D <float> v4_1 = v4_0;

      CPPUNIT_ASSERT ( v2_0 == v2_1 );
      CPPUNIT_ASSERT ( v4_0 == v4_1 );
    }

    void testInequality ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_1;

      Vector4D <float> v4_0 ( -4.0f, 5.0f, 1.0f, -.5f);
      Vector4D <float> v4_1;

      CPPUNIT_ASSERT ( v2_0 != v2_1 );
      CPPUNIT_ASSERT ( v4_0 != v4_1 );
    }

    void testMinus ()
    {
      Vector2D <float> v2_0 ( -4.0f, 5.0f);
      Vector2D <float> v2_1 ( 3.0f, 10.0f);
      Vector2D <float> v2_2;

      Vector4D <float> v4_0 ( -4.0f, 5.0f, 1.0f, -1.0f);
      Vector4D <float> v4_1 ( 3.0f, 10.0f, 1.0f, -.5f);
      Vector4D <float> v4_2;
 
      v2_2 = v2_0 - v2_1;
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.x, -7.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.y, -5.0f );

      v4_2 = v4_0 - v4_1;
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.x, -7.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.y, -5.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.z,  0.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.w, -0.5f );

    }

    void testNegation ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_2;

      Vector4D <float> v4_0 ( -4.0f, 5.0f, 1.0f, -1.0f);
      Vector4D <float> v4_2;
  
      v2_2 = -v2_0;
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.x,  4.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.y, -5.0f );

      v4_2 = -v4_0;
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.x, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.y, -5.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.z, -1.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.w,  1.0f );

    }


    void testSum ()
    {
      Vector2D <float> v2_0 (-4.0f, 5.0f);
      Vector2D <float> v2_1 ( 3.0f, 10.0f);
      Vector2D <float> v2_2;
  
      v2_2 = v2_0 + v2_1;
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.x, -1.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.y, 15.0f );
    }

    void testDivision ()
    {
      Vector2D <float> v2_0 ( -4.0f,5.0f);
      Vector2D <float> v2_2;

      Vector4D <float> v4_0 ( -4.0f, 5.0f, 2.0f, -1.0f);
      Vector4D <float> v4_2;

      float scalar = 2.0f;
  
      v2_2 = v2_0 / scalar;
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.x, -2.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.y,  5.0f/scalar );

      v4_2 = v4_0 / scalar;
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.x, -2.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.y,  5.0f/scalar );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.z,  1.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.w,  -0.5f );

    }

    void testMultiplication ()
    {
      Vector2D <float> v2_0 ( -4.0f, 5.0f);
      Vector2D <float> v2_2;

      Vector4D <float> v4_0 ( -4.0f, 5.0f, 2.0f, -1.0f);
      Vector4D <float> v4_2;
 
      float scalar = 2.0f;
  
      v2_2 = scalar * v2_0;
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.x, -8.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.y, 10.0f );

      v4_2 = scalar * v4_0;
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.x, -8.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.y, 10.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.z, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( v4_2.coord.w, -2.0f );

    }

    void testNormalize ()
    {
      Vector2D <float> v2_0 ( -4.0f, 5.0f);
      v2_0.Normalize ();

      float expectedX = (1/sqrt(41.0f))*-4.0f;
      float expectedY = (1/sqrt(41.0f))*5.0f;

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( v2_0.coord.x, expectedX, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( v2_0.coord.y, expectedY, 0.01 );

      Vector4D <float> v4_0 ( -4.0f, 5.0f, 1.0f, 0.5f);
      v4_0.Normalize ();

      expectedX = (1/sqrt(41.0f))*-4.0f;
      expectedY = (1/sqrt(41.0f))*5.0f;

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( v2_0.coord.x, expectedX, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( v2_0.coord.y, expectedY, 0.01 );

    }

    void testPerpendicular ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_2;

      v2_2 = Vec2DPerpendicular (v2_0);
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.x, 5.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.coord.y, 4.0f );
    }

    void testUnitPerpendicular ()
    {
      Vector2D <float> v2_0 (-4.0f,5.0f);
      Vector2D <float> v2_2;
      float mag = sqrt ( v2_0.coord.x*v2_0.coord.x + v2_0.coord.y*v2_0.coord.y ); 
      v2_2 = Vec2DUnitPerpendicular (v2_0);

      float expectedX = 5.0f/mag;
      float expectedY = 4.0f/mag;

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( expectedX, v2_2.coord.x , 0.0001 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( expectedY, v2_2.coord.y , 0.0001 );
    }
/*
    void testOrthonormalize ()
    {
      std::vector <Vector4D<float> > v4;
      std::vector <Vector3D<float> > v3;
      std::vector <Vector2D<float> > v2;

      Vector2D <float> v2_0 ( 1.0f, 3.0f );
      Vector2D <float> v2_1 ( 0.0f, 2.0f );

      Vector3D <float> v3_0 ( 2.0f, -1.0f,  0.0f );
      Vector3D <float> v3_1 ( 1.0f,  0.0f, -1.0f );
      Vector3D <float> v3_2 ( 3.0f,  7.0f, -1.0f );

      Vector4D <float> v4_0 ( 2.0f, -1.0f,  0.0f, 1.0f );
      Vector4D <float> v4_1 ( 1.0f,  0.0f, -1.0f, 5.0f );
      Vector4D <float> v4_2 ( 3.0f,  7.0f, -1.0f, 9.0f );
      Vector4D <float> v4_3 ( 3.0f,  7.0f, -1.0f, 2.0f );

      v2.push_back(v2_0);
      v2.push_back(v2_1);

      Orthonormalize2D ( v2 );

      v2_1 = v2.back();
      v2.pop_back();
      v2_0 = v2.back();
      v2.pop_back();
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, Vec2DDot(v2_0,v2_1), 0.01);

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

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, Vec3DDot(v3_0,v3_1), 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, Vec3DDot(v3_0,v3_2), 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, Vec3DDot(v3_1,v3_2), 0.01);

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

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, Vec4DDot(v4_0,v4_1), 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, Vec4DDot(v4_0,v4_2), 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, Vec4DDot(v4_0,v4_2), 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, Vec4DDot(v4_1,v4_2), 0.01);
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0, Vec4DDot(v4_2,v4_3), 0.01);

    }
*/

    void testDotProduct ()
    {
      hummstrumm::engine::math::Vector2D <float> v2_0;
      hummstrumm::engine::math::Vector2D <float> v2_1 (3.0f, 4.0f);

      hummstrumm::engine::math::Vector4D <float> v4_0;
      hummstrumm::engine::math::Vector4D <float> v4_1 (3.0f, 4.0f, 1.0f, 4.0f);

      CPPUNIT_ASSERT_EQUAL ( 0.0f, Vec2DDot(v2_0, v2_1) );

      CPPUNIT_ASSERT_EQUAL ( 0.0f, Vec4DDot(v4_0, v4_1) ); 

      CPPUNIT_ASSERT_EQUAL ( 42.0f, Vec4DDot(v4_1, v4_1) ); 
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION ( VectorTest );
CPPUNIT_TEST_SUITE_REGISTRATION ( MatricesTest );
CPPUNIT_TEST_SUITE_REGISTRATION ( QuaternionsTest );

int
main ()
{
  CppUnit::TestResult controller;
  CppUnit::TestResultCollector result;
  controller.addListener (&result);
  CppUnit::TextOutputter output (&result, std::cout);

  CppUnit::BriefTestProgressListener progress;
  controller.addListener (&progress);

  Engine engine; 

  CppUnit::TestRunner runner;
  CppUnit::TestFactoryRegistry& registry = 
    CppUnit::TestFactoryRegistry::getRegistry ();
  
  runner.addTest ( registry.makeTest() );
  runner.run (controller);

  output.printFailures ();
  output.printStatistics ();
 
  return result.wasSuccessful() ? 0 : 1;  
}
