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
#include <cipra/cipra.h>

#include "hummstrummengine.hpp"
using namespace hummstrumm::engine::math;
using namespace hummstrumm::engine::geometry;

int
main ()
{
  class PlaneTest : public cipra::fixture
  {
      virtual void
      test () override
      {
        plan (16);

        TestConstructor ();
      }

      void
      TestConstructor ()
      {
        auto p1 = new_ok<Vector3D<float>> (0.0f,  1.0f, -7.0f);
        auto p2 = new_ok<Vector3D<float>> (3.0f,  1.0f, -9.0f);
        auto p3 = new_ok<Vector3D<float>> (0.0f, -5.0f, -8.0f);

        auto p = new_ok<Plane3D<float>> (p1, p2, p3);

        ok ([&]() { return std::abs (-12.0f - p.normal.coord.x ) < 0.001f; },
            "plane constructor from vectors");
        ok ([&]() { return std::abs (  3.0f - p.normal.coord.y ) < 0.001f; },
            "plane constructor from vectors");
        ok ([&]() { return std::abs (-18.0f - p.normal.coord.z ) < 0.001f; },
            "plane constructor from vectors");
        ok ([&]() { return std::abs (129.0f - p.d ) < 0.001f; },
            "plane constructor from vectors");

        nothrows ([&]() { p.Normalize (); },
                  "plane normalization doesn't throw");

        auto q = new_ok<Plane3D<float>> (1.0f, 2.0f, 2.0f, 6.0f);
        ok ([&]() { return std::abs (1.0f - q.normal.coord.x ) < 0.001f; },
            "plane constructor");
        ok ([&]() { return std::abs (2.0f - q.normal.coord.y ) < 0.001f; },
            "plane constructor");
        ok ([&]() { return std::abs (2.0f - q.normal.coord.z ) < 0.001f; },
            "plane constructor");
        ok ([&]() { return std::abs (6.0f - q.d ) < 0.001f; },
            "plane constructor");

        auto point = new_ok<Vector3D<float>> (3.0f, 1.0f, 0.5f);
        nothrows ([&]() { q.Normalize (); },
                  "plane normalization doesn't throw");
      }
  } test;

  return test.run ();
}
