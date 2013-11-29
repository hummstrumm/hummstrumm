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
using namespace hummstrumm::engine::geometry;

int
main ()
{
  class SegmentTest : public cipra::fixture
  {
      virtual void
      test () override
      {
        plan (5);

        TestConstructor ();
      }

      void
      TestConstructor ()
      {
        auto v1 = new_ok<Vector3D<float>> (1.0f,  2.0f, -2.0f);
        auto v2 = new_ok<Vector3D<float>> (3.0f, -2.0f,  1.0f);

        auto s = new_ok<Segment3D<float>> (v1, v2);

        ok ([&]() { return v1 == s.start; }, "segment constructor from vectors");
        ok ([&]() { return v2 == s.end; }, "segment constructor from vectors");
      }
  } test;

  return test.run ();
}
