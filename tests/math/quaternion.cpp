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

#include "hummstrummengine.hpp"
using namespace hummstrumm::engine::math;

int
main ()
{
  class QuaternionTest : public cipra::fixture
  {
      virtual void
      test () override
      {
        plan (63);

        TestMultiplication ();
        TestLogExpPow ();
      }

      void
      TestMultiplication ()
      {
        auto q0 = new_ok<Quaternion<float>> (1, 2, 3, 4),
          q5 = new_ok<Quaternion<float>> (1, 1, 1, 1),
          q1 = new_ok<Quaternion<float>> (3, 2, 5, 4),
          q2 = new_ok<Quaternion<float>> (4, 5, 3, 1),
          qExpected = new_ok<Quaternion<float>> ();

        q0.Normalize ();
        q5.Normalize ();
        qExpected = q0 * q5;
        ok ([&]() { return QuatMagnitude (qExpected) == 1; },
            "Expect a unit quaternion after multiplication of "
            "normalized quaternions");

        qExpected = q1 * q2;
        ok ([&]() { return std::abs (-17 - qExpected.w)        < 0.01; },
            "(q1*q2) scalar part");
        ok ([&]() { return std::abs (16 - qExpected.v.coord.x) < 0.01; },
            "(q1*q2) vector part x");
        ok ([&]() { return std::abs (47 - qExpected.v.coord.y) < 0.01; },
            "(q1*q2) vector part y");
        ok ([&]() { return std::abs (0 - qExpected.v.coord.z)  < 0.01; },
            "(q1*q2) vector part z");
      }

      void
      TestLogExpPow ()
      {
        float exponent = 2;
        auto q0 = new_ok<Quaternion<float>> (4, 1, 2, 3 ),
          q1 = new_ok<Quaternion<float>> (1, 0, 0, 0 ),
          q2 = new_ok<Quaternion<float>> (2, 0, 0, 0 ),
          q3 = new_ok<Quaternion<float>> (0, 1, 0, 0 ),
          q4 = new_ok<Quaternion<float>> (0, 2, 0, 0 ),
          q5 = new_ok<Quaternion<float>> (1, 1, 1, 1 ),
          q6 = new_ok<Quaternion<float>> (3, 3, 3, 3 ),
          q7 = new_ok<Quaternion<float>> (-4,-4,-4,-4 ),
          qExpected = new_ok<Quaternion<float>> ();

        qExpected = QuatLog (q0);
        ok ([&]() { return std::abs (1.7006 - qExpected.w)           < 0.01; },
            "ln q0 scalar part");
        ok ([&]() { return std::abs (0.200991 - qExpected.v.coord.x) < 0.01; },
            "ln q0 vector part x");
        ok ([&]() { return std::abs (0.401982 - qExpected.v.coord.y) < 0.01; },
            "ln q0 vector part y");
        ok ([&]() { return std::abs (0.602974 - qExpected.v.coord.z) < 0.01; },
            "ln q0 vector part z");

        qExpected = QuatLog (q1);
        ok ([&]() { return std::abs (0 - qExpected.w)         < 0.01; },
          "ln q1 scalar part");
        ok ([&]() { return std::abs (0 - qExpected.v.coord.x) < 0.01; },
          "ln q1 vector part x");
        ok ([&]() { return std::abs (0 - qExpected.v.coord.y) < 0.01; },
          "ln q1 vector part y");
        ok ([&]() { return std::abs (0 - qExpected.v.coord.z) < 0.01; },
          "ln q1 vector part z");

        qExpected = QuatLog (q2);
        ok ([&]() { return std::abs (0.693147 - qExpected.w)  < 0.01; },
            "ln q2 scalar part");
        ok ([&]() { return std::abs (0 - qExpected.v.coord.x) < 0.01; },
            "ln q2 vector part x");
        ok ([&]() { return std::abs (0 - qExpected.v.coord.y) < 0.01; },
            "ln q2 vector part y");
        ok ([&]() { return std::abs (0 - qExpected.v.coord.z) < 0.01; },
            "ln q2 vector part z");

        qExpected = QuatLog (q3);
        ok ([&]() { return std::abs (0 - qExpected.w)              < 0.01; },
            "ln q3 scalar part");
        ok ([&]() { return std::abs (1.5708 - qExpected.v.coord.x) < 0.01; },
            "ln q3 vector part x");
        ok ([&]() { return std::abs (0 - qExpected.v.coord.y)      < 0.01; },
            "ln q3 vector part y");
        ok ([&]() { return std::abs (0 - qExpected.v.coord.z)      < 0.01; },
            "ln q3 vector part z");

        qExpected = QuatLog (q4);
        ok ([&]() { return std::abs (0.693147 - qExpected.w)       < 0.01; },
            "ln q4 scalar part");
        ok ([&]() { return std::abs (1.5708 - qExpected.v.coord.x) < 0.01; },
            "ln q4 vector part x");
        ok ([&]() { return std::abs (0 - qExpected.v.coord.y)      < 0.01; },
            "ln q4 vector part y");
        ok ([&]() { return std::abs (0 - qExpected.v.coord.z)      < 0.01; },
            "ln q4 vector part z");

        qExpected = QuatLog (q5);
        ok ([&]() { return std::abs (0.693147 - qExpected.w)       < 0.01; },
            "ln q5 scalar part");
        ok ([&]() { return std::abs (0.6046 - qExpected.v.coord.x) < 0.01; },
            "ln q5 vector part x");
        ok ([&]() { return std::abs (0.6046 - qExpected.v.coord.y) < 0.01; },
            "ln q5 vector part y");
        ok ([&]() { return std::abs (0.6046 - qExpected.v.coord.z) < 0.01; },
            "ln q5 vector part z");

        qExpected = QuatLog (q6);
        ok ([&]() { return std::abs (1.79176 - qExpected.w)        < 0.01; },
            "ln q6 scalar part");
        ok ([&]() { return std::abs (0.6046 - qExpected.v.coord.x) < 0.01; },
            "ln q6 vector part x");
        ok ([&]() { return std::abs (0.6046 - qExpected.v.coord.y) < 0.01; },
            "ln q6 vector part y");
        ok ([&]() { return std::abs (0.6046 - qExpected.v.coord.z) < 0.01; },
            "ln q6 vector part z");

        qExpected = QuatLog (q7);
        ok ([&]() { return std::abs (2.07944 - qExpected.w)         < 0.01; },
            "ln q7 scalar part");
        ok ([&]() { return std::abs (-1.2092 - qExpected.v.coord.x) < 0.01; },
            "ln q7 vector part x");
        ok ([&]() { return std::abs (-1.2092 - qExpected.v.coord.y) < 0.01; },
            "ln q7 vector part y");
        ok ([&]() { return std::abs (-1.2092 - qExpected.v.coord.z) < 0.01; },
            "ln q7 vector part z");

        qExpected = QuatExp (QuatLog (q0));
        ok ([&]() { return std::abs (q0.w - qExpected.w) < 0.01; },
            "e^(ln q0) scalar part");
        ok ([&]() { return std::abs (q0.v.coord.x - qExpected.v.coord.x) <
          0.01; }, "e^(ln q0) vector part x");
        ok ([&]() { return std::abs (q0.v.coord.y - qExpected.v.coord.y) <
          0.01; }, "e^(ln q0) vector part y");
        ok ([&]() { return std::abs (q0.v.coord.z - qExpected.v.coord.z) <
          0.01; }, "e^(ln q0) vector part z");

        qExpected = QuatLog (QuatExp (q0));
        ok ([&]() { return std::abs (4 - qExpected.w) < 0.01; },
            "ln e^q0 scalar part");
        ok ([&]() { return std::abs (-0.679252 - qExpected.v.coord.x) < 0.01; },
            "ln e^q0 vector part x");
        ok ([&]() { return std::abs (-1.3585 - qExpected.v.coord.y)   < 0.01; },
            "ln e^q0 vector part y");
        ok ([&]() { return std::abs (-2.03776 - qExpected.v.coord.z)  < 0.01; },
            "ln e^q0 vector part z");

        qExpected = QuatPow (q0, q0);
        ok ([&]() { return std::abs (-53.8975 - qExpected.w) < 0.01; },
            "q0^q0 scalar part");
        ok ([&]() { return std::abs (0.772254 - qExpected.v.coord.x) < 0.01; },
            "q0^q0 vector part x");
        ok ([&]() { return std::abs (1.54451 - qExpected.v.coord.y) < 0.01; },
            "q0^q0 vector part y");
        ok ([&]() { return std::abs (2.31676 - qExpected.v.coord.z) < 0.01; },
            "q0^q0 vector part z");
      }
  } test;

  return test.run ();
}
