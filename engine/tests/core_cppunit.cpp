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

#include <cstring>

#include "hummstrummengine.hpp"

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

using namespace hummstrumm::engine::math;

template<typename T>
class MathCoreTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( MathCoreTest );
  CPPUNIT_TEST ( testMathCore );
  CPPUNIT_TEST_SUITE_END ();

  public:
    Vector4D<T> *vector4DTest;
//    Vector3D<T> *vector3DTest;
//    Vector2D<T> *vector2DTest;

    void setUp () 
    {
      vector4DTest = new Vector4D<T>[1024];
//      vector3DTest = new Vector3D<T>[1024];
//      vector2DTest = new Vector2D<T>[1024];

    }

    void tearDown () 
    {
      delete [] vector4DTest;
    }

    void testMathCore ()
    {
    }

  private:

};


CPPUNIT_TEST_SUITE_REGISTRATION ( MathCoreTest<float> );

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
