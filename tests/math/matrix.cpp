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

#include <cmath>

#include "hummstrummengine.hpp"
using namespace hummstrumm::engine::math;

int
main ()
{
  class MatrixTest : public cipra::fixture
  {
      virtual void
      test () override
      {
        plan (315);

        TestConstructor ();
        TestAssignment ();
        TestEquality ();
        TestInequality ();
        TestNegate ();
        TestSubtraction ();
        TestAdd ();
        TestMultiplication ();
        TestDivision ();
        TestDeterminant ();
        TestInverse ();
      }

      void
      TestConstructor ()
      {
        auto m2_1 = new_ok<Matrix2D<float>> ();
        auto m3_1 = new_ok<Matrix3D<float>> ();
        auto m4_1 = new_ok<Matrix4D<float>> ();

        // safe to use is() here because there's no arithmetic being done.
        is (m2_1[0].coord.x, 0.0f, "m2_1 storage");
        is (m2_1[0].coord.y, 0.0f, "m2_1 storage");
        is (m2_1[1].coord.x, 0.0f, "m2_1 storage");
        is (m2_1[1].coord.y, 0.0f, "m2_1 storage");

        is (m3_1[0].coord.x, 0.0f, "m3_1 storage");
        is (m3_1[0].coord.y, 0.0f, "m3_1 storage");
        is (m3_1[0].coord.z, 0.0f, "m3_1 storage");
        is (m3_1[1].coord.x, 0.0f, "m3_1 storage");
        is (m3_1[1].coord.y, 0.0f, "m3_1 storage");
        is (m3_1[1].coord.z, 0.0f, "m3_1 storage");
        is (m3_1[2].coord.x, 0.0f, "m3_1 storage");
        is (m3_1[2].coord.y, 0.0f, "m3_1 storage");
        is (m3_1[2].coord.z, 0.0f, "m3_1 storage");

        is (m4_1[0].coord.x, 0.0f, "m4_1 storage");
        is (m4_1[0].coord.y, 0.0f, "m4_1 storage");
        is (m4_1[0].coord.z, 0.0f, "m4_1 storage");
        is (m4_1[0].coord.w, 0.0f, "m4_1 storage");
        is (m4_1[1].coord.x, 0.0f, "m4_1 storage");
        is (m4_1[1].coord.y, 0.0f, "m4_1 storage");
        is (m4_1[1].coord.z, 0.0f, "m4_1 storage");
        is (m4_1[1].coord.w, 0.0f, "m4_1 storage");
        is (m4_1[2].coord.x, 0.0f, "m4_1 storage");
        is (m4_1[2].coord.y, 0.0f, "m4_1 storage");
        is (m4_1[2].coord.z, 0.0f, "m4_1 storage");
        is (m4_1[2].coord.w, 0.0f, "m4_1 storage");

        auto m2_2 = new_ok<Matrix2D<float>> (2, 3,
                                             4, 5);
        auto m3_2 = new_ok<Matrix3D<float>> (2,   3,  4,
                                             5,   6,  7,
                                             -1, -2, -3);
        auto m4_2 = new_ok<Matrix4D<float>> (     2,      3,      4,       5,
                                             -0.01f,   0.5f,  3.24f,      -3,
                                             -1.4f,  -20.1f,   -300, -41.23f,
                                                  0,   -678, -1.02f,     -10);

        is (m2_2[0].coord.x,  2.0f, "m2_2 storage");
        is (m2_2[0].coord.y,  3.0f, "m2_2 storage");
        is (m2_2[1].coord.x,  4.0f, "m2_2 storage");
        is (m2_2[1].coord.y,  5.0f, "m2_2 storage");

        is (m3_2[0].coord.x,  2.0f, "m3_2 storage");
        is (m3_2[0].coord.y,  3.0f, "m3_2 storage");
        is (m3_2[0].coord.z,  4.0f, "m3_2 storage");
        is (m3_2[1].coord.x,  5.0f, "m3_2 storage");
        is (m3_2[1].coord.y,  6.0f, "m3_2 storage");
        is (m3_2[1].coord.z,  7.0f, "m3_2 storage");
        is (m3_2[2].coord.x, -1.0f, "m3_2 storage");
        is (m3_2[2].coord.y, -2.0f, "m3_2 storage");
        is (m3_2[2].coord.z, -3.0f, "m3_2 storage");

        is (m4_2[0].coord.x,    2.0f, "m4_2 storage");
        is (m4_2[0].coord.y,    3.0f, "m4_2 storage");
        is (m4_2[0].coord.z,    4.0f, "m4_2 storage");
        is (m4_2[0].coord.w,    5.0f, "m4_2 storage");
        is (m4_2[1].coord.x,  -0.01f, "m4_2 storage");
        is (m4_2[1].coord.y,    0.5f, "m4_2 storage");
        is (m4_2[1].coord.z,   3.24f, "m4_2 storage");
        is (m4_2[1].coord.w,   -3.0f, "m4_2 storage");
        is (m4_2[2].coord.x,   -1.4f, "m4_2 storage");
        is (m4_2[2].coord.y,  -20.1f, "m4_2 storage");
        is (m4_2[2].coord.z, -300.0f, "m4_2 storage");
        is (m4_2[2].coord.w, -41.23f, "m4_2 storage");
        is (m4_2[3].coord.x,    0.0f, "m4_2 storage");
        is (m4_2[3].coord.y, -678.0f, "m4_2 storage");
        is (m4_2[3].coord.z,  -1.02f, "m4_2 storage");
        is (m4_2[3].coord.w,  -10.0f, "m4_2 storage");

        auto m2_3 = new_ok<Matrix2D<float>> (
          Vector2D<float> {6, 7},
          Vector2D<float> {9, 0});
        auto m3_3 = new_ok<Matrix3D<float>> (
          Vector3D<float> {6, 7, 8},
          Vector3D<float> {9, 0, -1},
          Vector3D<float> {-10, -0.01f, -0.1f});
        auto m4_3 = new_ok<Matrix4D<float>> (
          Vector4D<float> {6, 7, 8, -1.3f},
          Vector4D<float> {9, 0,-1, -3.1f},
          Vector4D<float> {-10, -0.01f, -0.1f, -4.2f},
          Vector4D<float> {-0.1f,  -134, -1.9f, -5.5f});

        is (m2_3[0].coord.x,  6.0f, "m2_3 storage");
        is (m2_3[0].coord.y,  7.0f, "m2_3 storage");
        is (m2_3[1].coord.x,  9.0f, "m2_3 storage");
        is (m2_3[1].coord.y,  0.0f, "m2_3 storage");

        is (m3_3[0].coord.x,   6.0f, "m3_3 storage");
        is (m3_3[0].coord.y,   7.0f, "m3_3 storage");
        is (m3_3[0].coord.z,   8.0f, "m3_3 storage");
        is (m3_3[1].coord.x,   9.0f, "m3_3 storage");
        is (m3_3[1].coord.y,   0.0f, "m3_3 storage");
        is (m3_3[1].coord.z,  -1.0f, "m3_3 storage");
        is (m3_3[2].coord.x, -10.0f, "m3_3 storage");
        is (m3_3[2].coord.y, -0.01f, "m3_3 storage");
        is (m3_3[2].coord.z,  -0.1f, "m3_3 storage");

        is (m4_3[0].coord.x,    6.0f, "m4_3 storage");
        is (m4_3[0].coord.y,    7.0f, "m4_3 storage");
        is (m4_3[0].coord.z,    8.0f, "m4_3 storage");
        is (m4_3[0].coord.w,   -1.3f, "m4_3 storage");
        is (m4_3[1].coord.x,    9.0f, "m4_3 storage");
        is (m4_3[1].coord.y,    0.0f, "m4_3 storage");
        is (m4_3[1].coord.z,   -1.0f, "m4_3 storage");
        is (m4_3[1].coord.w,   -3.1f, "m4_3 storage");
        is (m4_3[2].coord.x,  -10.0f, "m4_3 storage");
        is (m4_3[2].coord.y,  -0.01f, "m4_3 storage");
        is (m4_3[2].coord.z,   -0.1f, "m4_3 storage");
        is (m4_3[2].coord.w,   -4.2f, "m4_3 storage");
        is (m4_3[3].coord.x,   -0.1f, "m4_3 storage");
        is (m4_3[3].coord.y, -134.0f, "m4_3 storage");
        is (m4_3[3].coord.z,   -1.9f, "m4_3 storage");
        is (m4_3[3].coord.w,   -5.5f, "m4_3 storage");

        // copy constructor
        auto m2_4 = new_ok<Matrix2D<float>> (m2_3);
        is (m2_4[0].coord.x, m2_3[0].coord.x, "copy constructed m2_4 storage");
        is (m2_4[0].coord.y, m2_3[0].coord.y, "copy constructed m2_4 storage");
        is (m2_4[1].coord.x, m2_3[1].coord.x, "copy constructed m2_4 storage");
        is (m2_4[1].coord.y, m2_3[1].coord.y, "copy constructed m2_4 storage");
        auto m3_4 = new_ok<Matrix3D<float>> (m3_3);
        is (m3_4[0].coord.x, m3_3[0].coord.x, "copy constructed m3_4 storage");
        is (m3_4[0].coord.y, m3_3[0].coord.y, "copy constructed m3_4 storage");
        is (m3_4[0].coord.z, m3_3[0].coord.z, "copy constructed m3_4 storage");
        is (m3_4[1].coord.x, m3_3[1].coord.x, "copy constructed m3_4 storage");
        is (m3_4[1].coord.y, m3_3[1].coord.y, "copy constructed m3_4 storage");
        is (m3_4[1].coord.z, m3_3[1].coord.z, "copy constructed m3_4 storage");
        is (m3_4[2].coord.x, m3_3[2].coord.x, "copy constructed m3_4 storage");
        is (m3_4[2].coord.y, m3_3[2].coord.y, "copy constructed m3_4 storage");
        is (m3_4[2].coord.z, m3_3[2].coord.z, "copy constructed m3_4 storage");
        auto m4_4 = new_ok<Matrix4D<float>> (m4_3);
        is (m4_4[0].coord.x, m4_3[0].coord.x, "copy constructed m4_4 storage");
        is (m4_4[0].coord.y, m4_3[0].coord.y, "copy constructed m4_4 storage");
        is (m4_4[0].coord.z, m4_3[0].coord.z, "copy constructed m4_4 storage");
        is (m4_4[0].coord.w, m4_3[0].coord.w, "copy constructed m4_4 storage");
        is (m4_4[1].coord.x, m4_3[1].coord.x, "copy constructed m4_4 storage");
        is (m4_4[1].coord.y, m4_3[1].coord.y, "copy constructed m4_4 storage");
        is (m4_4[1].coord.z, m4_3[1].coord.z, "copy constructed m4_4 storage");
        is (m4_4[1].coord.w, m4_3[1].coord.w, "copy constructed m4_4 storage");
        is (m4_4[2].coord.x, m4_3[2].coord.x, "copy constructed m4_4 storage");
        is (m4_4[2].coord.y, m4_3[2].coord.y, "copy constructed m4_4 storage");
        is (m4_4[2].coord.z, m4_3[2].coord.z, "copy constructed m4_4 storage");
        is (m4_4[2].coord.w, m4_3[2].coord.w, "copy constructed m4_4 storage");
        is (m4_4[3].coord.x, m4_3[3].coord.x, "copy constructed m4_4 storage");
        is (m4_4[3].coord.y, m4_3[3].coord.y, "copy constructed m4_4 storage");
        is (m4_4[3].coord.z, m4_3[3].coord.z, "copy constructed m4_4 storage");
        is (m4_4[3].coord.w, m4_3[3].coord.w, "copy constructed m4_4 storage");
      }

      void
      TestAssignment ()
      {
        auto m2_3 = new_ok<Matrix2D<float>> (3, 4, -2, -5);
        auto m2_4 = new_ok<Matrix2D<float>> ();
        m2_4 = m2_3;

        is (m2_4[0].coord.x, m2_3[0].coord.x, "assigment of two matrices");
        is (m2_4[0].coord.y, m2_3[0].coord.y, "assigment of two matrices");
        is (m2_4[1].coord.x, m2_3[1].coord.x, "assigment of two matrices");
        is (m2_4[1].coord.y, m2_3[1].coord.y, "assigment of two matrices");
      }

      void
      TestEquality ()
      {
        auto m2_3 = new_ok<Matrix2D<float>> (3, 4, -2, -5);
        auto m2_4 = new_ok<Matrix2D<float>> (3.0, 4.0, -2, -5.0);
        ok (m2_3 == m2_4, "equality of two matrices");
      }

      void
      TestInequality ()
      {
        auto m2_3 = new_ok<Matrix2D<float>> (3, 4, -1, -5);
        auto m2_4 = new_ok<Matrix2D<float>> (3.0, 4.0, -2, -5.0);
        ok (m2_3 != m2_4, "inequality of two matrices");
      }

      void
      TestNegate ()
      {
        auto m2_3 = new_ok<Matrix2D<float>> (3, 4, -1, -5);
        auto m2_4 = new_ok<Matrix2D<float>> (-m2_3);
        is (m2_4[0].coord.x, -3.0f, "negated matrix has proper components");
        is (m2_4[0].coord.y, -4.0f, "negated matrix has proper components");
        is (m2_4[1].coord.x,  1.0f, "negated matrix has proper components");
        is (m2_4[1].coord.y,  5.0f, "negated matrix has proper components");
      }

      void
      TestSubtraction ()
      {
        auto m2_3 = new_ok<Matrix2D<float>> (3, 4, -1, -5);
        auto m2_4 = new_ok<Matrix2D<float>> (2, 1,  3,  6);
        nothrows ([&]() { m2_4 = m2_4 - m2_3; },
                 "matrix subtraction doesn't throw");
        ok ([&]() { return std::abs (m2_4[0].coord.x - -1.0f) < 0.01f; },
            "matrix subtraction");
        ok ([&]() { return std::abs (m2_4[0].coord.y - -3.0f) < 0.01f; },
            "matrix subtraction");
        ok ([&]() { return std::abs (m2_4[1].coord.x -  4.0f) < 0.01f; },
            "matrix subtraction");
        ok ([&]() { return std::abs (m2_4[1].coord.y - 11.0f) < 0.01f; },
            "matrix subtraction");
        auto m2_5 = new_ok<Matrix2D<float>> (-1, -1, -1, 0);
        nothrows ([&]() { m2_5 -= m2_4; },
                 "matrix subtraction/assignment doesn't throw");
        ok ([&]() { return std::abs (m2_5[0].coord.x -  0.0f)  < 0.01f; },
            "matrix subtraction/assignment");
        ok ([&]() { return std::abs (m2_5[0].coord.y -  2.0f)  < 0.01f; },
            "matrix subtraction/assignment");
        ok ([&]() { return std::abs (m2_5[1].coord.x - -5.0f)  < 0.01f; },
            "matrix subtraction/assignment");
        ok ([&]() { return std::abs (m2_5[1].coord.y - -11.0f) < 0.01f; },
            "matrix subtraction/assignment");
      }

      void
      TestAdd ()
      {
        auto m2_3 = new_ok<Matrix2D<float>> (3, 4, -1, -5);
        auto m2_4 = new_ok<Matrix2D<float>> (2, 1, 3, 6);
        nothrows ([&]() { m2_4 = m2_4 + m2_3; },
                 "matrix addition doesn't throw");
        ok ([&]() { return std::abs (m2_4[0].coord.x - 5.0f) < 0.01f; },
            "matrix addition");
        ok ([&]() { return std::abs (m2_4[0].coord.y - 5.0f) < 0.01f; },
            "matrix addition");
        ok ([&]() { return std::abs (m2_4[1].coord.x - 2.0f) < 0.01f; },
            "matrix addition");
        ok ([&]() { return std::abs (m2_4[1].coord.y - 1.0f) < 0.01f; },
            "matrix addition");
        auto m2_5 = new_ok<Matrix2D<float>> (-1, -1, -1, 0);
        nothrows ([&]() { m2_5 += m2_4; },
                 "matrix addition/assignment doesn't throw");
        ok ([&]() { return std::abs (m2_5[0].coord.x - 4.0f) < 0.01f; },
            "matrix addition/assignment");
        ok ([&]() { return std::abs (m2_5[0].coord.y - 4.0f) < 0.01f; },
            "matrix addition/assignment");
        ok ([&]() { return std::abs (m2_5[1].coord.x - 1.0f) < 0.01f; },
            "matrix addition/assignment");
        ok ([&]() { return std::abs (m2_5[1].coord.y - 1.0f) < 0.01f; },
            "matrix addition/assignment");
      }

      void
      TestMultiplication ()
      {
        auto m2_3 = new_ok<Matrix2D<float>> (3, 4, -1, -5);

        // Scalar multiplication
        float scalar = 3;
        nothrows ([&]() { m2_3 = m2_3 * scalar; },
                  "scalar multiplication doesn't throw");
        ok ([&]() { return std::abs (m2_3[0].coord.x -   9.0f) < 0.01f; },
            "scalar multiplication");
        ok ([&]() { return std::abs (m2_3[0].coord.y -  12.0f) < 0.01f; },
            "scalar multiplication");
        ok ([&]() { return std::abs (m2_3[1].coord.x -  -3.0f) < 0.01f; },
            "scalar multiplication");
        ok ([&]() { return std::abs (m2_3[1].coord.y - -15.0f) < 0.01f; },
            "scalar multiplication");
        nothrows ([&]() { m2_3 *= scalar; },
                  "scalar multiplication/assignment doesn't throw");
        ok ([&]() { return std::abs (m2_3[0].coord.x -  27.0f) < 0.01f; },
            "scalar multiplication/assignment");
        ok ([&]() { return std::abs (m2_3[0].coord.y -  36.0f) < 0.01f; },
            "scalar multiplication/assignment");
        ok ([&]() { return std::abs (m2_3[1].coord.x -  -9.0f) < 0.01f; },
            "scalar multiplication/assignment");
        ok ([&]() { return std::abs (m2_3[1].coord.y - -45.0f) < 0.01f; },
            "scalar multiplication/assignment");
        nothrows ([&]() { m2_3 = scalar * m2_3; },
                  "scalar multiplication commutativity doesn't throw");
        ok ([&]() { return std::abs (m2_3[0].coord.x -   81.0f) < 0.01f; },
            "scalar multiplication commutativity");
        ok ([&]() { return std::abs (m2_3[0].coord.y -  108.0f) < 0.01f; },
             "scalar multiplication commutativity");
        ok ([&]() { return std::abs (m2_3[1].coord.x -  -27.0f) < 0.01f; },
            "scalar multiplication commutativity");
        ok ([&]() { return std::abs (m2_3[1].coord.y - -135.0f) < 0.01f; },
            "scalar multiplication commutativity");

        // Matrix multiplcation
        auto m2_4 = new_ok<Matrix2D<float>> (4, 5, 6, -0.5);
        auto m2_5 = new_ok<Matrix2D<float>> ();
        nothrows ([&]() { m2_5 = m2_3 * m2_4; },
                  "matrix multiplication doesn't throw");
        ok ([&]() { return std::abs ( 972.0f - m2_5[0].coord.x) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs ( 351.0f - m2_5[0].coord.y) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (-918.0f - m2_5[1].coord.x) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs ( -67.5f - m2_5[1].coord.y) < 0.01f; },
            "matrix multiplication");
        nothrows ([&]() { m2_5 *= m2_4; },
                  "matrix multiplication/assignment doesn't throw");
        ok ([&]() { return std::abs (  5994.0f -  m2_5[0].coord.x) < 0.01f; },
            "matrix multiplication/assignment");
        ok ([&]() { return std::abs (  4684.5f -  m2_5[0].coord.y) < 0.01f; },
            "matrix multiplication/assignment");
        ok ([&]() { return std::abs ( -4077.0f -  m2_5[1].coord.x) < 0.01f; },
            "matrix multiplication/assignment");
        ok ([&]() { return std::abs (-4556.250f - m2_5[1].coord.y) < 0.01f; },
            "matrix multiplication/assignment");

        auto m3_1 = new_ok<Matrix3D<float>> ( 3,  6,  1,
                                              4,  3, -5,
                                             -1, -3,  9);
        auto m3_2 = new_ok<Matrix3D<float>> ( 5,  7,  1,
                                              4,  2, -5,
                                             -1, -1,  9);
        auto m3_0 = new_ok<Matrix3D<float>> ();
        nothrows ([&]() { m3_0 = m3_1 * m3_2; },
                  "matrix multiplication doesn't throw");
        ok ([&]() { return std::abs ( 38.0f - m3_0[0].coord.x) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs ( 32.0f - m3_0[0].coord.y) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (-18.0f - m3_0[0].coord.z) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs ( 37.0f - m3_0[1].coord.x) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs ( 39.0f - m3_0[1].coord.y) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (-56.0f - m3_0[1].coord.z) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (-26.0f - m3_0[2].coord.x) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (-22.0f - m3_0[2].coord.y) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs ( 95.0f - m3_0[2].coord.z) < 0.01f; },
            "matrix multiplication");
        nothrows ([&]() { m3_0 *= m3_2; },
                  "matrix multiplication/assignment doesn't throw");
        ok ([&]() { return std::abs ( 336.0f - m3_0[0].coord.x) < 0.01f; },
            "matrix multiplication/assignment");
        ok ([&]() { return std::abs ( 348.0f - m3_0[0].coord.y) < 0.01f; },
            "matrix multiplication/assignment");
        ok ([&]() { return std::abs (-284.0f - m3_0[0].coord.z) < 0.01f; },
            "matrix multiplication/assignment");
        ok ([&]() { return std::abs ( 397.0f - m3_0[1].coord.x) < 0.01f; },
            "matrix multiplication/assignment");
        ok ([&]() { return std::abs ( 393.0f - m3_0[1].coord.y) < 0.01f; },
            "matrix multiplication/assignment");
        ok ([&]() { return std::abs (-662.0f - m3_0[1].coord.z) < 0.01f; },
            "matrix multiplication/assignment");
        ok ([&]() { return std::abs (-313.0f - m3_0[2].coord.x) < 0.01f; },
            "matrix multiplication/assignment");
        ok ([&]() { return std::abs (-321.0f - m3_0[2].coord.y) < 0.01f; },
            "matrix multiplication/assignment");
        ok ([&]() { return std::abs ( 939.0f - m3_0[2].coord.z) < 0.01f; },
            "matrix multiplication/assignment");

        auto m4_4 = new_ok<Matrix4D<float>> ( 3, 4, -1, -0.5f,
                                             -5, 3,  2,    2,
                                              3, 6,  7,    4,
                                              7, 0,  0,    8);
        auto m4_5 = new_ok<Matrix4D<float>> (0.035f,  -0.133f,  0.043f,  0.014f,
                                             0.181f,   0.092f,  0.000f, -0.012f,
                                             -0.153f, -0.089f,  0.146f, -0.061f,
                                             -0.031f,  0.117f, -0.038f,  0.113f);
        auto m4_6 = new_ok<Matrix4D<float>> ();
        nothrows ([&]() { m4_6 = m4_4 * m4_5; },
                  "matrix multiplication doesn't throw");
        ok ([&]() { return std::abs (m4_6[0].coord.x - 1) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (m4_6[0].coord.y - 0) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (m4_6[0].coord.z - 0) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (m4_6[0].coord.w - 0) < 0.01f; },
            "matrix multiplication");

        ok ([&]() { return std::abs (m4_6[1].coord.x - 0) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (m4_6[1].coord.y - 1) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (m4_6[1].coord.z - 0) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (m4_6[1].coord.w - 0) < 0.01f; },
            "matrix multiplication");

        ok ([&]() { return std::abs (m4_6[2].coord.x - 0) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (m4_6[2].coord.y - 0) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (m4_6[2].coord.z - 1) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (m4_6[2].coord.w - 0) < 0.01f; },
            "matrix multiplication");

        ok ([&]() { return std::abs (m4_6[3].coord.x - 0) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (m4_6[3].coord.y - 0) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (m4_6[3].coord.z - 0) < 0.01f; },
            "matrix multiplication");
        ok ([&]() { return std::abs (m4_6[3].coord.w - 1) < 0.01f; },
            "matrix multiplication");

        nothrows ([&]() { m4_6 *= m4_4; }, // precision loss
                  "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[0].coord.x - m4_6[0].coord.x) <
          0.05f; }, "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[0].coord.y - m4_6[0].coord.y) <
          0.05f; }, "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[0].coord.z - m4_6[0].coord.z) <
          0.05f; }, "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[0].coord.w - m4_6[0].coord.w) <
          0.05f; }, "matrix multiplication/assignment");

        ok ([&]() { return std::abs (m4_4[1].coord.x - m4_6[1].coord.x) <
          0.05f; }, "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[1].coord.y - m4_6[1].coord.y) <
          0.05f; }, "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[1].coord.z - m4_6[1].coord.z) <
          0.05f; }, "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[1].coord.w - m4_6[1].coord.w) <
          0.05f; }, "matrix multiplication/assignment");

        ok ([&]() { return std::abs (m4_4[2].coord.x - m4_6[2].coord.x) <
          0.05f; }, "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[2].coord.y - m4_6[2].coord.y) <
          0.05f; }, "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[2].coord.z - m4_6[2].coord.z) <
          0.05f; }, "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[2].coord.w - m4_6[2].coord.w) <
          0.05f; }, "matrix multiplication/assignment");

        ok ([&]() { return std::abs (m4_4[3].coord.x - m4_6[3].coord.x) <
          0.05f; }, "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[3].coord.y - m4_6[3].coord.y) <
          0.05f; }, "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[3].coord.z - m4_6[3].coord.z) <
          0.05f; }, "matrix multiplication/assignment");
        ok ([&]() { return std::abs (m4_4[3].coord.w - m4_6[3].coord.w) <
          0.05f; }, "matrix multiplication/assignment");
      }

      void
      TestDivision ()
      {
        auto m2_3 = Matrix2D<float> (3, 4, -1, -5);
        float divisor = 2;
        nothrows ([&]() { m2_3 = m2_3 / divisor; },
                  "matrix division doesn't throw");
        ok ([&]() { return std::abs ( 3/divisor - m2_3[0].coord.x) < 0.01f; },
            "matrix division");
        ok ([&]() { return std::abs ( 4/divisor - m2_3[0].coord.y) < 0.01f; },
            "matrix division");
        ok ([&]() { return std::abs (-1/divisor - m2_3[1].coord.x) < 0.01f; },
            "matrix division");
        ok ([&]() { return std::abs (-5/divisor - m2_3[1].coord.y) < 0.01f; },
            "matrix division");

        auto m2_4 = Matrix2D<float> (-0.5f, 67, -7, 2);
        nothrows ([&]() { m2_4 /= divisor; },
                  "matrix division/assignment doesn't throw");
        ok ([&]() { return std::abs (-0.5/divisor - m2_4[0].coord.x) < 0.01f; },
            "matrix division/assignment");
        ok ([&]() { return std::abs (67/divisor - m2_4[0].coord.y) < 0.01f; },
            "matrix division/assignment");
        ok ([&]() { return std::abs (-7/divisor - m2_4[1].coord.x) < 0.01f; },
            "matrix division/assignment");
        ok ([&]() { return std::abs (2/divisor - m2_4[1].coord.y) < 0.01f; },
            "matrix division/assignment");
      }

      void
      TestDeterminant ()
      {
        auto m2_3 = new_ok<Matrix2D<float>> (3, 4, -1, -5);
        auto m3_1 = new_ok<Matrix3D<float>> ( 3.0f, -2.0f,  0.0f,
                                              1.0f,  4.0f, -3.0f,
                                              -1.0f,  0.0f,  2.0f);
        auto m3_2 = new_ok<Matrix3D<float>> ( 3.0f, -1.0f, -0.5f,
                                              -5.0f,  2.0f,  2.0f,
                                              3.0f,  7.0f,  4.0f);
        auto m4_1 = new_ok<Matrix4D<float>> (-2.0f, 2.0f,  2.0f, 7.0f,
                                             5.0f, 8.0f, -5.0f, 2.0f,
                                             5.0f, 8.0f,  9.0f, 2.0f,
                                             2.0f, 5.0f,  6.0f, 4.0f);
        ok ([&]() { return std::abs (m2_3.Determinant() -  -11.0f) < 0.01f; },
            "determinant of matrix");
        ok ([&]() { return std::abs (m3_1.Determinant() -   22.0f) < 0.01f; },
            "determinant of matrix");
        ok ([&]() { return std::abs (m3_2.Determinant() -  -23.5f) < 0.01f; },
            "determinant of matrix");
        ok ([&]() { return std::abs (m4_1.Determinant() - -182.0f) < 0.01f; },
            "determinant of matrix");
      }

      void
      TestInverse ()
      {
        auto m2_3 = new_ok<Matrix2D<float>> (0.455f, 0.364f, -0.091f, -0.273f);
        auto m2_4 = new_ok<Matrix2D<float>> (3, 4, -1, -5);
        auto m2_4Inv = new_ok<Matrix2D<float>> ();

        auto m3_4 = new_ok<Matrix3D<float>> ( 3, 4, -1,
                                              -5, 3,  2,
                                              3, 6,  7);

        auto m3_5 = new_ok<Matrix3D<float>> ( 0.039f, -0.148f,  0.048f,
                                              0.178f,  0.104f, -0.004f,
                                              -0.170f, -0.026f,  0.126f);
        auto m3_4Inv = new_ok<Matrix3D<float>> ();

        auto m4_4 = new_ok<Matrix4D<float>> ( 3, 4, -1, -5,
                                              -5, 3,  2,  2,
                                              3, 6,  7,  4,
                                              7, 0,  0,  8);
        auto m4_5 = new_ok<Matrix4D<float>> ( 0.031f, -0.117f,  0.038f,  0.030f,
                                              0.159f,  0.176f, -0.028f,  0.069f,
                                              -0.134f, -0.159f,  0.169f, -0.129f,
                                              -0.027f,  0.102f, -0.033f,  0.099f);
        auto m4_4Inv = new_ok<Matrix4D<float>> ();


        nothrows ([&]() { m2_4Inv = Mat2DInverse (m2_4); },
                  "matrix inverse doesn't throw");
        nothrows ([&]() { m3_4Inv = Mat3DInverse(m3_4); },
                  "matrix inverse doesn't throw");
        nothrows ([&]() { m4_4Inv = Mat4DInverse(m4_4); },
                  "matrix inverse doesn't throw");

        ok ([&]() { return std::abs (m2_3[0].coord.x - m2_4Inv[0].coord.x) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m2_3[0].coord.y - m2_4Inv[0].coord.y) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m2_3[1].coord.x - m2_4Inv[1].coord.x) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m2_3[1].coord.y - m2_4Inv[1].coord.y) <
          0.01f; }, "matrix inverse");

        ok ([&]() { return std::abs (m3_5[0].coord.x - m3_4Inv[0].coord.x) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m3_5[0].coord.y - m3_4Inv[0].coord.y) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m3_5[0].coord.z - m3_4Inv[0].coord.z) <
          0.01f; }, "matrix inverse");

        ok ([&]() { return std::abs (m3_5[1].coord.x - m3_4Inv[1].coord.x) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m3_5[1].coord.y - m3_4Inv[1].coord.y) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m3_5[1].coord.z - m3_4Inv[1].coord.z) <
          0.01f; }, "matrix inverse");

        ok ([&]() { return std::abs (m3_5[2].coord.x - m3_4Inv[2].coord.x) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m3_5[2].coord.y - m3_4Inv[2].coord.y) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m3_5[2].coord.z - m3_4Inv[2].coord.z) <
          0.01f; }, "matrix inverse");

        ok ([&]() { return std::abs (m4_5[0].coord.x - m4_4Inv[0].coord.x) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m4_5[0].coord.y - m4_4Inv[0].coord.y) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m4_5[0].coord.z - m4_4Inv[0].coord.z) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m4_5[0].coord.w - m4_4Inv[0].coord.w) <
          0.01f; }, "matrix inverse");

        ok ([&]() { return std::abs (m4_5[1].coord.x - m4_4Inv[1].coord.x) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m4_5[1].coord.y - m4_4Inv[1].coord.y) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m4_5[1].coord.z - m4_4Inv[1].coord.z) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m4_5[1].coord.w - m4_4Inv[1].coord.w) <
          0.01f; }, "matrix inverse");

        ok ([&]() { return std::abs (m4_5[2].coord.x - m4_4Inv[2].coord.x) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m4_5[2].coord.y - m4_4Inv[2].coord.y) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m4_5[2].coord.z - m4_4Inv[2].coord.z) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m4_5[2].coord.w - m4_4Inv[2].coord.w) <
          0.01f; }, "matrix inverse");

        ok ([&]() { return std::abs (m4_5[3].coord.x - m4_4Inv[3].coord.x) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m4_5[3].coord.y - m4_4Inv[3].coord.y) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m4_5[3].coord.z - m4_4Inv[3].coord.z) <
          0.01f; }, "matrix inverse");
        ok ([&]() { return std::abs (m4_5[3].coord.w - m4_4Inv[3].coord.w) <
          0.01f; }, "matrix inverse");
      }

      void
      TestTranspose ()
      {
        auto m2_4 = new_ok<Matrix2D<float>> ( 3,  4,
                                             -1, -5);
        auto m2_4t = new_ok<Matrix2D<float>> (3, -1,
                                              4, -5);

        auto m3_4 = new_ok<Matrix3D<float>> ( 3, 4, -1,
                                             -5, 3,  2,
                                              3, 6,  7);
        auto m3_4t = new_ok<Matrix3D<float>> ( 3, -5, 3,
                                               4,  3, 6,
                                              -1,  2, 7);

        auto m4_4 = new_ok<Matrix4D<float>> ( 3,  4, -1, -0.5,
                                             -5,  3,  2,    2,
                                              3,  6,  7,    4,
                                              7,  0,  0,    8);
        auto m4_4t = new_ok<Matrix4D<float>> (   3,  -5,  3,  7,
                                                 4,   3,  6,  0,
                                                -1,   2,  7,  0,
                                              -0.5,   2,  4,  8);

        nothrows ([&]() { m2_4t = Mat2DTranspose (m2_4); },
                  "matrix transpose doesn't throw");
        nothrows ([&]() { m3_4t = Mat3DTranspose (m3_4); },
                  "matrix transpose doesn't throw");
        nothrows ([&]() { m4_4t = Mat4DTranspose (m4_4); },
                  "matrix transpose doesn't throw");
        ok ([&]() { return std::abs (m2_4[0].coord.x - m2_4t[0].coord.x) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m2_4[0].coord.y - m2_4t[1].coord.x) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m2_4[1].coord.x - m2_4t[0].coord.y) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m2_4[1].coord.y - m2_4t[1].coord.y) <
          0.01f; }, "matrix transpose");

        ok ([&]() { return std::abs (m3_4[0].coord.x - m3_4t[0].coord.x) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m3_4[0].coord.y - m3_4t[1].coord.x) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m3_4[0].coord.z - m3_4t[2].coord.x) <
          0.01f; }, "matrix transpose");

        ok ([&]() { return std::abs (m3_4[1].coord.x - m3_4t[0].coord.y) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m3_4[1].coord.y - m3_4t[1].coord.y) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m3_4[1].coord.z - m3_4t[2].coord.y) <
          0.01f; }, "matrix transpose");

        ok ([&]() { return std::abs (m3_4[2].coord.x - m3_4t[0].coord.z) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m3_4[2].coord.y - m3_4t[1].coord.z) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m3_4[2].coord.z - m3_4t[2].coord.z) <
          0.01f; }, "matrix transpose");

        ok ([&]() { return std::abs (m4_4[0].coord.x - m4_4t[0].coord.x) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m4_4[0].coord.y - m4_4t[1].coord.x) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m4_4[0].coord.z - m4_4t[2].coord.x) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m4_4[0].coord.w - m4_4t[3].coord.x) <
          0.01f; }, "matrix transpose");

        ok ([&]() { return std::abs (m4_4[1].coord.x - m4_4t[0].coord.y) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m4_4[1].coord.y - m4_4t[1].coord.y) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m4_4[1].coord.z - m4_4t[2].coord.y) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m4_4[1].coord.w - m4_4t[3].coord.y) <
          0.01f; }, "matrix transpose");

        ok ([&]() { return std::abs (m4_4[2].coord.x - m4_4t[0].coord.z) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m4_4[2].coord.y - m4_4t[1].coord.z) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m4_4[2].coord.z - m4_4t[2].coord.z) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m4_4[2].coord.w - m4_4t[3].coord.z) <
          0.01f; }, "matrix transpose");

        ok ([&]() { return std::abs (m4_4[3].coord.x - m4_4t[0].coord.w) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m4_4[3].coord.y - m4_4t[1].coord.w) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m4_4[3].coord.z - m4_4t[2].coord.w) <
          0.01f; }, "matrix transpose");
        ok ([&]() { return std::abs (m4_4[3].coord.w - m4_4t[3].coord.w) <
          0.01f; }, "matrix transpose");
      }
  } test;

  return test.run ();
}
