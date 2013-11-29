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
#include <vector>

#include "hummstrummengine.hpp"
using namespace hummstrumm::engine::math;

int
main ()
{
  class VectorTest : public cipra::fixture
  {
      virtual void
      test () override
      {
        plan (152);

        TestConstructor ();
        TestCopyConstructor ();
        TestAssignment ();
        TestEquality ();
        TestInequality ();
        TestMinus ();
        TestNegation ();
        TestSum ();
        TestDivision ();
        TestMultiplication ();
        TestNormalize ();
        TestPerpendicular ();
        TestUnitPerpendicular ();
        TestOrthonormalize ();
        TestDotProduct ();
      }

      void
      TestConstructor ()
      {
        auto v2_0 = new_ok<Vector2D<float>> ();
        auto v2_1 = new_ok<Vector2D<float>> (3.0f, 4.0f);

        auto v4_0 = new_ok<Vector4D<float>> ();
        auto v4_1 = new_ok<Vector4D<float>> (3.0f, 4.0f, 1.0f, -0.5f);

        // is() is okay here, because there's no arithmetic
        is (v2_0.coord.x, 0.0f, "Vector2D constructed properly");
        is (v2_0.coord.y, 0.0f, "Vector2D constructed properly");
        is (v2_1.coord.x, 3.0f, "Vector2D constructed properly");
        is (v2_1.coord.y, 4.0f, "Vector2D constructed properly");

        is (v4_0.coord.x, 0.0f, "Vector4D constructed properly");
        is (v4_0.coord.y, 0.0f, "Vector4D constructed properly");
        is (v4_0.coord.z, 0.0f, "Vector4D constructed properly");
        is (v4_0.coord.w, 0.0f, "Vector4D constructed properly");

        is (v4_1.coord.x, 3.0f, "Vector4D constructed properly");
        is (v4_1.coord.y, 4.0f, "Vector4D constructed properly");
        is (v4_1.coord.z, 1.0f, "Vector4D constructed properly");
        is (v4_1.coord.w, -0.5f, "Vector4D constructed properly");
      }

      void
      TestCopyConstructor ()
      {
        auto v2_0 = new_ok<Vector2D<float>> ();
        auto v2_1 = new_ok<Vector2D<float>> (3.0f, 4.0f);
        auto v2_2 = new_ok<Vector2D<float>>(v2_1);

        auto v4_0 = new_ok<Vector4D<float>> ();
        auto v4_1 = new_ok<Vector4D<float>> (3.0f, 4.0f, 1.0f, -0.5f);
        auto v4_2 = new_ok<Vector4D<float>> (v4_1);

        // is() is okay here again
        is (v2_2.coord.x, 3.0f, "copy constructor stores properly");
        is (v2_2.coord.y, 4.0f, "copy constructor stores properly");

        is (v4_2.coord.x, 3.0f, "copy constructor stores properly");
        is (v4_2.coord.y, 4.0f, "copy constructor stores properly");
        is (v4_2.coord.z, 1.0f, "copy constructor stores properly");
        is (v4_2.coord.w, -.5f, "copy constructor stores properly");

      }

      void
      TestAssignment ()
      {
        auto v2_0 = new_ok<Vector2D<float>> (-4.0f, 5.0f);
        auto v2_1 = new_ok<Vector2D<float>> ();
        nothrows ([&]() { v2_1 = v2_0; }, "assignment doesn't throw");

        auto v4_0 = new_ok<Vector4D<float>> (-4.0f, 5.0f, 1.0f, -0.5f);
        auto v4_1 = new_ok<Vector4D<float>> ();
        nothrows ([&]() { v4_1 = v4_0; }, "assignment doesn't throw");

        // is() is okay here, because only assignment
        is (v2_1.coord.x, -4.0f, "assignment stores properly");
        is (v2_1.coord.y,  5.0f, "assignment stores properly");

        is (v4_1.coord.x, -4.0f, "assignment stores properly");
        is (v4_1.coord.y,  5.0f, "assignment stores properly");
        is (v4_1.coord.z,  1.0f, "assignment stores properly");
        is (v4_1.coord.w,  -.5f, "assignment stores properly");
      }

      void
      TestEquality ()
      {
        auto v2_0 = new_ok<Vector2D<float>> (-4.0f, 5.0f);
        auto v2_1 = new_ok<Vector2D<float>> (v2_0);

        auto v4_0 = new_ok<Vector4D<float>> (-4.0f, 5.0f, 1.0f, -.5f);
        auto v4_1 = new_ok<Vector4D<float>> (v4_0);

        ok ([&]() { return v2_0 == v2_1; }, "Vector2D equality");
        ok ([&]() { return v4_0 == v4_1; }, "Vector4D equality");
      }

      void
      TestInequality ()
      {
        Vector2D<float> v2_0 (-4.0f,5.0f);
        Vector2D<float> v2_1;

        Vector4D<float> v4_0 ( -4.0f, 5.0f, 1.0f, -.5f);
        Vector4D<float> v4_1;

        ok ([&]() { return v2_0 != v2_1; }, "Vector2D equality");
        ok ([&]() { return v4_0 != v4_1; }, "Vector4D equality");
      }

      void
      TestMinus ()
      {
        auto v2_0 = new_ok<Vector2D<float>> (-4.0f, 5.0f);
        auto v2_1 = new_ok<Vector2D<float>> (3.0f, 10.0f);
        auto v2_2 = new_ok<Vector2D<float>> ();

        auto v4_0 = new_ok<Vector4D<float>> (-4.0f, 5.0f, 1.0f, -1.0f);
        auto v4_1 = new_ok<Vector4D<float>> (3.0f, 10.0f, 1.0f, -.5f);
        auto v4_2 = new_ok<Vector4D<float>> ();

        nothrows ([&]() { v2_2 = v2_0 - v2_1; },
                  "vector subtraction doesn't throw");
        ok ([&]() { return std::abs (v2_2.coord.x - -7.0f) < 0.01f; },
            "vector subtraction");
        ok ([&]() { return std::abs (v2_2.coord.y - -5.0f) < 0.01f; },
            "vector subtraction");

        nothrows ([&]() { v4_2 = v4_0 - v4_1; },
                  "vector subtraction doesn't throw");
        ok ([&]() { return std::abs (v4_2.coord.x - -7.0f) < 0.01f; },
            "vector subtraction");
        ok ([&]() { return std::abs (v4_2.coord.y - -5.0f) < 0.01f; },
            "vector subtraction");
        ok ([&]() { return std::abs (v4_2.coord.z -  0.0f) < 0.01f; },
            "vector subtraction");
        ok ([&]() { return std::abs (v4_2.coord.w - -0.5f) < 0.01f; },
            "vector subtraction");
      }

      void
      TestNegation ()
      {
        auto v2_0 = new_ok<Vector2D<float>> (-4.0f, 5.0f);
        auto v2_2 = new_ok<Vector2D<float>> ();

        auto v4_0 = new_ok<Vector4D<float>> (-4.0f, 5.0f, 1.0f, -1.0f);
        auto v4_2 = new_ok<Vector4D<float>> ();

        nothrows ([&]() { v2_2 = -v2_0; },
                  "vector negation and assignment doesn't throw");
        ok ([&]() { return std::abs (v2_2.coord.x -  4.0f) < 0.01f; },
            "vector negation");
        ok ([&]() { return std::abs (v2_2.coord.y - -5.0f) < 0.01f; },
            "vector negation");

        nothrows ([&]() { v4_2 = -v4_0; },
                  "vector negation and assignment doesn't throw");
        ok ([&]() { return std::abs (v4_2.coord.x - 4.0f) < 0.01f; },
            "vector negation");
        ok ([&]() { return std::abs (v4_2.coord.y - -5.0f) < 0.01f; },
            "vector negation");
        ok ([&]() { return std::abs (v4_2.coord.z - -1.0f) < 0.01f; },
            "vector negation");
        ok ([&]() { return std::abs (v4_2.coord.w -  1.0f) < 0.01f; },
            "vector negation");
      }

      void
      TestSum ()
      {
        auto v2_0 = new_ok<Vector2D<float>> (-4.0f, 5.0f);
        auto v2_1 = new_ok<Vector2D<float>> (3.0f, 10.0f);
        auto v2_2 = new_ok<Vector2D<float>> ();

        nothrows ([&]() { v2_2 = v2_0 + v2_1; },
                  "vector sum and assignment doesn't throw");
        ok ([&]() { return std::abs (v2_2.coord.x - -1.0f) < 0.01f; },
            "vector sum");
        ok ([&]() { return std::abs (v2_2.coord.y - 15.0f) < 0.01f; },
            "vector sum");
      }

      void
      TestDivision ()
      {
        auto v2_0 = new_ok<Vector2D<float>> (-4.0f, 5.0f);
        auto v2_2 = new_ok<Vector2D<float>> ();

        auto v4_0 = new_ok<Vector4D<float>> (-4.0f, 5.0f, 2.0f, -1.0f);
        auto v4_2 = new_ok<Vector4D<float>> ();

        float scalar = 2.0f;

        nothrows ([&]() { v2_2 = v2_0 / scalar; },
                  "vector division by scalar doesn't throw");
        ok ([&]() { return std::abs (v2_2.coord.x - -2.0f) < 0.01f; },
            "vector division by scalar");
        ok ([&]() { return std::abs (v2_2.coord.y -  5.0f/scalar) < 0.01f; },
            "vector division by scalar");

        nothrows ([&]() { v4_2 = v4_0 / scalar; },
                  "vector division by scalar doesn't throw");
        ok ([&]() { return std::abs (v4_2.coord.x - -2.0f) < 0.01f; },
            "vector division by scalar");
        ok ([&]() { return std::abs (v4_2.coord.y -  5.0f/scalar) < 0.01f; },
            "vector division by scalar");
        ok ([&]() { return std::abs (v4_2.coord.z -  1.0f) < 0.01f; },
            "vector division by scalar");
        ok ([&]() { return std::abs (v4_2.coord.w -  -0.5f) < 0.01f; },
            "vector division by scalar");
      }

      void
      TestMultiplication ()
      {
        auto v2_0 = new_ok<Vector2D<float>> (-4.0f, 5.0f);
        auto v2_2 = new_ok<Vector2D<float>> ();

        auto v4_0 = new_ok<Vector4D<float>> (-4.0f, 5.0f, 2.0f, -1.0f);
        auto v4_2 = new_ok<Vector4D<float>> ();

        float scalar = 2.0f;

        nothrows ([&]() { v2_2 = scalar * v2_0; },
                  "vector multiplication by scalar doesn't throw");
        ok ([&]() { return std::abs (v2_2.coord.x - -8.0f) < 0.01f; },
            "vector multiplication");
        ok ([&]() { return std::abs (v2_2.coord.y - 10.0f) < 0.01f; },
            "vector multiplication");

        nothrows ([&]() { v4_2 = scalar * v4_0; },
                  "vector multiplication by scalar doesn't throw");
        ok ([&]() { return std::abs (v4_2.coord.x - -8.0f) < 0.01f; },
            "vector multiplication");
        ok ([&]() { return std::abs (v4_2.coord.y - 10.0f) < 0.01f; },
            "vector multiplication");
        ok ([&]() { return std::abs (v4_2.coord.z - 4.0f) < 0.01f; },
            "vector multiplication");
        ok ([&]() { return std::abs (v4_2.coord.w - -2.0f) < 0.01f; },
            "vector multiplication");
      }

      void
      TestNormalize ()
      {
        auto v2_0 = new_ok<Vector2D<float>> (-4.0f, 5.0f);
        nothrows ([&]() { v2_0.Normalize (); }, "normalization doesn't throw");

        float expectedX = (1 / std::sqrt (41.0f)) * -4.0f;
        float expectedY = (1 / std::sqrt (41.0f)) *  5.0f;
        float expectedZ, expectedW;
        ok ([&]() { return std::abs (v2_0.coord.x - expectedX) < 0.001f; },
            "vector normalization");
        ok ([&]() { return std::abs (v2_0.coord.y - expectedY) < 0.001f; },
            "vector normalization");

        auto v4_0 = new_ok<Vector4D<float>> (-4.0f, 5.0f, 1.0f, 0.5f);
        nothrows ([&]() { v4_0.Normalize (); }, "normalization doesn't throw");

        expectedX = (1 / std::sqrt (42.25f)) * -4.0f;
        expectedY = (1 / std::sqrt (42.25f)) *  5.0f;
        expectedZ = (1 / std::sqrt (42.25f)) *  1.0f;
        expectedW = (1 / std::sqrt (42.25f)) *  0.5f;
        ok ([&]() { return std::abs (v4_0.coord.x - expectedX) < 0.001f; },
            "vector normalization");
        ok ([&]() { return std::abs (v4_0.coord.y - expectedY) < 0.001f; },
            "vector normalization");
        ok ([&]() { return std::abs (v4_0.coord.z - expectedZ) < 0.001f; },
            "vector normalization");
        ok ([&]() { return std::abs (v4_0.coord.w - expectedW) < 0.001f; },
            "vector normalization");
      }

      void
      TestPerpendicular ()
      {
        auto v2_0 = new_ok<Vector2D<float>> (-4.0f, 5.0f);
        auto v2_2 = new_ok<Vector2D<float>> ();

        nothrows ([&]() { v2_2 = Vec2DPerpendicular (v2_0); },
                  "2D perpendicular vector doesn't throw");
        ok ([&]() { return std::abs (v2_2.coord.x - 5.0f) < 0.0001f; },
            "2D perpendicular vector");
        ok ([&]() { return std::abs (v2_2.coord.y - 4.0f) < 0.0001f; },
            "2D perpendicular vector");
      }

      void
      TestUnitPerpendicular ()
      {
        auto v2_0 = new_ok<Vector2D<float>> (-4.0f, 5.0f);
        auto v2_2 = new_ok<Vector2D<float>> ();
        float mag = std::sqrt (v2_0.coord.x * v2_0.coord.x +
                               v2_0.coord.y * v2_0.coord.y);
        nothrows ([&]() { v2_2 = Vec2DUnitPerpendicular (v2_0); },
                  "2D perpendicular unit vector doesn't throw");

        float expectedX = 5.0f / mag;
        float expectedY = 4.0f / mag;
        ok ([&]() { return std::abs (expectedX - v2_2.coord.x ) < 0.0001f; },
            "2D perpendicular unit vector");
        ok ([&]() { return std::abs (expectedY - v2_2.coord.y ) < 0.0001f; },
            "2D perpendicular unit vector");
      }

      void
      TestOrthonormalize ()
      {
        std::vector<Vector4D<float>> v4;
        std::vector<Vector3D<float>> v3;
        std::vector<Vector2D<float>> v2;

        auto v2_0 = new_ok<Vector2D<float>> (1.0f, 3.0f);
        auto v2_1 = new_ok<Vector2D<float>> (0.0f, 2.0f);

        auto v3_0 = new_ok<Vector3D<float>> (2.0f, -1.0f,  0.0f);
        auto v3_1 = new_ok<Vector3D<float>> (1.0f,  0.0f, -1.0f);
        auto v3_2 = new_ok<Vector3D<float>> (3.0f,  7.0f, -1.0f);

        auto v4_0 = new_ok<Vector4D<float>> (2.0f, -1.0f,  0.0f, 1.0f);
        auto v4_1 = new_ok<Vector4D<float>> (1.0f,  0.0f, -1.0f, 5.0f);
        auto v4_2 = new_ok<Vector4D<float>> (3.0f,  7.0f, -1.0f, 9.0f);
        auto v4_3 = new_ok<Vector4D<float>> (3.0f,  7.0f, -1.0f, 2.0f);

        v2.push_back (v2_0);
        v2.push_back (v2_1);
        nothrows ([&]() { Orthonormalize2D (v2); },
                  "2D orthonormalize doesn't throw");
        v2_1 = v2.back ();
        v2.pop_back ();
        v2_0 = v2.back ();
        v2.pop_back ();
        ok ([&]() { return std::abs (0 - Vec2DDot (v2_0, v2_1)) < 0.01f; },
            "2D orthonormalize");

        v3.push_back (v3_0);
        v3.push_back (v3_1);
        v3.push_back (v3_2);
        nothrows ([&]() { Orthonormalize3D (v3); },
                  "3D orthonormalize doesn't throw");
        v3_2 = v3.back ();
        v3.pop_back ();
        v3_1 = v3.back ();
        v3.pop_back ();
        v3_0 = v3.back ();
        v3.pop_back ();
        ok ([&]() { return std::abs (0 - Vec3DDot (v3_0, v3_1)) < 0.01f; },
            "3D orthonormalize");
        ok ([&]() { return std::abs (0 - Vec3DDot (v3_0, v3_2)) < 0.01f; },
            "3D orthonormalize");
        ok ([&]() { return std::abs (0 - Vec3DDot (v3_1, v3_2)) < 0.01f; },
            "3D orthonormalize");

        v4.push_back (v4_0);
        v4.push_back (v4_1);
        v4.push_back (v4_2);
        v4.push_back (v4_3);
        nothrows ([&]() { Orthonormalize4D (v4); },
                  "4D orthonormalize doesn't throw");
        v4_3 = v4.back ();
        v4.pop_back ();
        v4_2 = v4.back ();
        v4.pop_back ();
        v4_1 = v4.back ();
        v4.pop_back ();
        v4_0 = v4.back ();
        v4.pop_back ();
        ok ([&]() { return std::abs (0 - Vec4DDot (v4_0, v4_1)) < 0.001f; },
            "4D orthonormalize");
        ok ([&]() { return std::abs (0 - Vec4DDot (v4_0, v4_2)) < 0.001f; },
            "4D orthonormalize");
        ok ([&]() { return std::abs (0 - Vec4DDot (v4_0, v4_2)) < 0.001f; },
            "4D orthonormalize");
        ok ([&]() { return std::abs (0 - Vec4DDot (v4_1, v4_2)) < 0.001f; },
            "4D orthonormalize");
        ok ([&]() { return std::abs (0 - Vec4DDot (v4_2, v4_3)) < 0.001f; },
            "4D orthonormalize");
      }

      void
      TestDotProduct ()
      {
        auto v2_0 = new_ok<Vector2D<float>> ();
        auto v2_1 = new_ok<Vector2D<float>> (3.0f, 4.0f);

        auto v4_0 = new_ok<Vector4D<float>> ();
        auto v4_1 = new_ok<Vector4D<float>> (3.0f, 4.0f, 1.0f, 4.0f);

        ok ([&]() { return std::abs (0.0f - Vec2DDot (v2_0, v2_1)) < 0.001f; },
            "vector dot product");
        ok ([&]() { return std::abs (0.0f - Vec4DDot (v4_0, v4_1)) < 0.001f; },
            "vector dot product");
        ok ([&]() { return std::abs (42.0f - Vec4DDot (v4_1, v4_1)) < 0.001f; },
            "vector dot product");
      }
  } test;

  return test.run ();
}
