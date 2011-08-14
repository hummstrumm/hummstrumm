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

template<typename T>
class VectorMathProfilerTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( VectorMathProfilerTest );
  CPPUNIT_TEST ( vector4DSum );
  CPPUNIT_TEST_SUITE_END ();

  Vector4D<T> *vector4DTest;
  Vector3D<T> *vector3DTest;
  Vector2D<T> *vector2DTest;

  public:
    void setUp () 
    {
      vector4DTest = new Vector4D<T>[1024];
      vector3DTest = new Vector3D<T>[1024];
      vector2DTest = new Vector2D<T>[1024];
/*
      for (int i = 0; i < 1024; i++)
      {

        T x_val = static_cast<T> ((rand() % 1000));
        T y_val = static_cast<T> ((rand() % 1000));
        T w_val = static_cast<T> ((rand() % 1000));
        T z_val = static_cast<T> ((rand() % 1000));

        vector4DTest[i] = Vector4D<T> (x_val, y_val, z_val, w_val);
        vector3DTest[i] = Vector3D<T> (x_val, y_val, z_val);
        vector2DTest[i] = Vector2D<T> (x_val, y_val);

        std::cout << vector4DTest[i].x << " " 
                  << vector4DTest[i].y << " " 
                  << vector4DTest[i].z << " " 
                  << vector4DTest[i].w << std::endl;

      }
*/
    }

    void tearDown () 
    {
      delete [] vector4DTest;
      delete [] vector3DTest;
      delete [] vector2DTest;
    }

    void vector4DSum ()
    {
/*
      {
        HUMMSTRUMM_PROFILE(">> Vector << >> 4D Dot Product",Profiler::REPORT_IN_MILLISECONDS,
                            Profiler::LOGGER_AND_CONSOLE);
        for (int i = 0; i < 10000; i++)
        {
          for (int j = 0; j < 1024; j++)
          {
            Vector4D<T> sum = vector4DTest[j] + vector4DTest[j];
//              Vector4D<T> dot = Vec4DDot(vector4DTest[j], vector4DTest[j]);
          }
        }
        HUMMSTRUMM_PROFILE_ITERATION();
      }
*/
    }
};



CPPUNIT_TEST_SUITE_REGISTRATION ( VectorMathProfilerTest<float> );

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
