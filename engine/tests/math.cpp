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
#include "math/matrice.hpp"

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

//@TODO Finishing Testing Matrix3D and Matrix4D.
using namespace hummstrumm::engine::math;

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

  CPPUNIT_TEST_SUITE_END ();

  public:

    void setUp () {}

    void tearDown () {}

    void testConstructor ()
    {
      Matrix2D <float> m2_1;
      Matrix3D <float> m3_1;
      Matrix4D <float> m4_1;

      CPPUNIT_ASSERT_EQUAL ( m2_1[0].x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_1[0].y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_1[1].x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_1[1].y, 0.0f );

      CPPUNIT_ASSERT_EQUAL ( m3_1[0].x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[0].y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[0].z, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[1].x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[1].y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[1].z, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[2].x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[2].y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_1[2].z, 0.0f );

      CPPUNIT_ASSERT_EQUAL ( m4_1[0].x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[0].y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[0].z, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[0].w, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[1].x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[1].y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[1].z, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[1].w, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[2].x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[2].y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[2].z, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_1[2].w, 0.0f );


      Matrix2D <float> m2_2 (2, 3,
                             4, 5);
      Matrix3D <float> m3_2 (2, 3, 4,
                             5, 6, 7,
                            -1,-2,-3);
      Matrix4D <float> m4_2 (2    , 3    , 4   , 5    ,
                             -0.01, 0.5  , 3.24,-3    ,
                             -1.4 ,-20.1 ,-300 ,-41.23,
                             0    , -678 ,-1.02,-10  );

      CPPUNIT_ASSERT_EQUAL ( m2_2[0].x, 2.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_2[0].y, 3.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_2[1].x, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_2[1].y, 5.0f );

      CPPUNIT_ASSERT_EQUAL ( m3_2[0].x, 2.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[0].y, 3.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[0].z, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[1].x, 5.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[1].y, 6.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[1].z, 7.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[2].x, -1.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[2].y, -2.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_2[2].z, -3.0f );

      CPPUNIT_ASSERT_EQUAL ( m4_2[0].x, 2.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[0].y, 3.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[0].z, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[0].w, 5.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[1].x, -0.01f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[1].y, 0.5f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[1].z, 3.24f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[1].w, -3.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[2].x, -1.4f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[2].y, -20.1f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[2].z, -300.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[2].w, -41.23f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[3].x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[3].y, -678.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[3].z, -1.02f );
      CPPUNIT_ASSERT_EQUAL ( m4_2[3].w, -10.0f );

      Vector2D <float> v1 (6,7);
      Vector2D <float> v2 (9,0);
      Matrix2D <float> m2_3 (v1,v2);

      Vector3D <float> v3_1 (6,7,8);
      Vector3D <float> v3_2 (9,0,-1);
      Vector3D <float> v3_3 (-10,-0.01,-0.1);

      Matrix3D <float> m3_3 (v3_1,v3_2,v3_3);

      Vector4D <float> v4_1 (6,7,8,-1.3);
      Vector4D <float> v4_2 (9,0,-1,-3.1);
      Vector4D <float> v4_3 (-10,-0.01,-0.1,-4.2);
      Vector4D <float> v4_4 (-0.1,-134,-1.9,-5.5);

      Matrix4D <float> m4_3 (v4_1,v4_2,v4_3,v4_4);

      CPPUNIT_ASSERT_EQUAL ( m2_3[0].x, 6.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[0].y, 7.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].x, 9.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].y, 0.0f );

      CPPUNIT_ASSERT_EQUAL ( m3_3[0].x, 6.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[0].y, 7.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[0].z, 8.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[1].x, 9.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[1].y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[1].z, -1.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[2].x, -10.0f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[2].y, -0.01f );
      CPPUNIT_ASSERT_EQUAL ( m3_3[2].z, -0.1f );

      CPPUNIT_ASSERT_EQUAL ( m4_3[0].x, 6.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[0].y, 7.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[0].z, 8.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[0].w, -1.3f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[1].x, 9.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[1].y, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[1].z, -1.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[1].w, -3.1f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[2].x, -10.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[2].y, -0.01f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[2].z, -0.1f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[2].w, -4.2f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[3].x, -0.1f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[3].y, -134.0f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[3].z, -1.9f );
      CPPUNIT_ASSERT_EQUAL ( m4_3[3].w, -5.5f );

      // copy constructor
      Matrix2D <float> m2_4 (m2_3);

      CPPUNIT_ASSERT_EQUAL ( m2_4[0].x, m2_3[0].x );
      CPPUNIT_ASSERT_EQUAL ( m2_4[0].y, m2_3[0].y );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].x, m2_3[1].x );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].y, m2_3[1].y );

       // copy constructor
      Matrix3D <float> m3_4 (m3_3);

      CPPUNIT_ASSERT_EQUAL ( m3_4[0].x, m3_3[0].x );
      CPPUNIT_ASSERT_EQUAL ( m3_4[0].y, m3_3[0].y );
      CPPUNIT_ASSERT_EQUAL ( m3_4[0].z, m3_3[0].z );
      CPPUNIT_ASSERT_EQUAL ( m3_4[1].x, m3_3[1].x );
      CPPUNIT_ASSERT_EQUAL ( m3_4[1].y, m3_3[1].y );
      CPPUNIT_ASSERT_EQUAL ( m3_4[1].z, m3_3[1].z );
      CPPUNIT_ASSERT_EQUAL ( m3_4[2].x, m3_3[2].x );
      CPPUNIT_ASSERT_EQUAL ( m3_4[2].y, m3_3[2].y );
      CPPUNIT_ASSERT_EQUAL ( m3_4[2].z, m3_3[2].z );

      // copy constructor
      Matrix4D <float> m4_4 (m4_3);

      CPPUNIT_ASSERT_EQUAL ( m4_4[0].x, m4_3[0].x );
      CPPUNIT_ASSERT_EQUAL ( m4_4[0].y, m4_3[0].y );
      CPPUNIT_ASSERT_EQUAL ( m4_4[0].z, m4_3[0].z );
      CPPUNIT_ASSERT_EQUAL ( m4_4[0].w, m4_3[0].w );
      CPPUNIT_ASSERT_EQUAL ( m4_4[1].x, m4_3[1].x );
      CPPUNIT_ASSERT_EQUAL ( m4_4[1].y, m4_3[1].y );
      CPPUNIT_ASSERT_EQUAL ( m4_4[1].z, m4_3[1].z );
      CPPUNIT_ASSERT_EQUAL ( m4_4[1].w, m4_3[1].w );
      CPPUNIT_ASSERT_EQUAL ( m4_4[2].x, m4_3[2].x );
      CPPUNIT_ASSERT_EQUAL ( m4_4[2].y, m4_3[2].y );
      CPPUNIT_ASSERT_EQUAL ( m4_4[2].z, m4_3[2].z );
      CPPUNIT_ASSERT_EQUAL ( m4_4[2].w, m4_3[2].w );
      CPPUNIT_ASSERT_EQUAL ( m4_4[3].x, m4_3[3].x );
      CPPUNIT_ASSERT_EQUAL ( m4_4[3].y, m4_3[3].y );
      CPPUNIT_ASSERT_EQUAL ( m4_4[3].z, m4_3[3].z );
      CPPUNIT_ASSERT_EQUAL ( m4_4[3].w, m4_3[3].w );
     
    }

    void testAssignment ()
    {

      Matrix2D <float> m2_3 (3,4,-2,-5);
      Matrix2D <float> m2_4;
      m2_4 = m2_3;

      CPPUNIT_ASSERT_EQUAL ( m2_4[0].x, m2_3[0].x );
      CPPUNIT_ASSERT_EQUAL ( m2_4[0].y, m2_3[0].y );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].x, m2_3[1].x );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].y, m2_3[1].y );

    }

    void testEquality ()
    {
      Matrix2D <float> m2_3 (3,4,-2,-5);
      Matrix2D <float> m2_4 (3.0,4.0,-2,-5.0);

      CPPUNIT_ASSERT ( m2_3 == m2_4 );

    }

    void testInequality ()
    {
      Matrix2D <float> m2_3 (3,4,-1,-5);
      Matrix2D <float> m2_4 (3.0,4.0,-2,-5.0);

      CPPUNIT_ASSERT ( m2_3 != m2_4 );
    }

    void testNegate ()
    {
      Matrix2D <float> m2_3 (3,4,-1,-5);
      Matrix2D <float> m2_4;

      m2_4 = -m2_3;  

      CPPUNIT_ASSERT_EQUAL ( m2_4[0].x, -3.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[0].y, -4.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].x, 1.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].y, 5.0f );
     
    }

    void testSubtraction ()
    {
      Matrix2D <float> m2_3 (3, 4, -1, -5);
      Matrix2D <float> m2_4 (2, 1, 3, 6);
      m2_4 = m2_4 - m2_3;

      CPPUNIT_ASSERT_EQUAL ( m2_4[0].x, -1.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[0].y, -3.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].x, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].y, 11.0f );

      Matrix2D <float> m2_5 (-1, -1, -1, 0);
      m2_5 -= m2_4;

      CPPUNIT_ASSERT_EQUAL ( m2_5[0].x, 0.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_5[0].y, 2.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_5[1].x, -5.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_5[1].y, -11.0f );

    }

    void testAdd ()
    {
      Matrix2D <float> m2_3 (3, 4, -1, -5);
      Matrix2D <float> m2_4 (2, 1, 3, 6);
      m2_4 = m2_4 + m2_3;

      CPPUNIT_ASSERT_EQUAL ( m2_4[0].x, 5.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[0].y, 5.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].x, 2.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_4[1].y, 1.0f );

      Matrix2D <float> m2_5 (-1, -1, -1, 0);
      m2_5 += m2_4;

      CPPUNIT_ASSERT_EQUAL ( m2_5[0].x, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_5[0].y, 4.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_5[1].x, 1.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_5[1].y, 1.0f );

    }

    void testMultiplication ()
    {
      Matrix2D <float> m2_3 (3, 4, -1, -5);
      float scalar = 3;
      m2_3 = m2_3 * scalar;

      CPPUNIT_ASSERT_EQUAL ( m2_3[0].x, 9.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[0].y, 12.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].x, -3.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].y, -15.0f );

      m2_3 *= scalar;

      CPPUNIT_ASSERT_EQUAL ( m2_3[0].x, 27.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[0].y, 36.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].x, -9.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].y, -45.0f );
/*
      m2_3 = scalar * m2_3;

      CPPUNIT_ASSERT_EQUAL ( m2_3[0].x, 81.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[0].y, 108.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].x, -27.0f );
      CPPUNIT_ASSERT_EQUAL ( m2_3[1].y, -135.0f );
*/


    }

    void testDivision ()
    {
      Matrix2D <float> m2_3 (3, 4, -1, -5);
      float divisor = 2;
      m2_3 = m2_3 / divisor;

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 3/divisor, m2_3[0].x, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 4/divisor, m2_3[0].y, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( -1/divisor, m2_3[1].x, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( -5/divisor, m2_3[1].y, 0.01 );

      Matrix2D <float> m2_4 (-0.5, 67, -7, 2);
      m2_4 /= divisor;

      CPPUNIT_ASSERT_DOUBLES_EQUAL ( -0.5/divisor, m2_4[0].x, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 67/divisor, m2_4[0].y, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( -7/divisor, m2_4[1].x, 0.01 );
      CPPUNIT_ASSERT_DOUBLES_EQUAL ( 2/divisor, m2_4[1].y, 0.01 );
   
    }

  private:

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
  
      v2_2 = scalar * v2_0;
      CPPUNIT_ASSERT_EQUAL ( v2_2.x, -8.0f );
      CPPUNIT_ASSERT_EQUAL ( v2_2.y, 10.0f );

      v2_2 = scalar * v2_0;
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
CPPUNIT_TEST_SUITE_REGISTRATION ( MatricesTest );

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
