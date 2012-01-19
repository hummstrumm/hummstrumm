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

#include "hummstrummengine.hpp"

#include <cstring>

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

using namespace hummstrumm::engine::error;

class ErrorTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( ErrorTest );
  CPPUNIT_TEST_EXCEPTION( testThrowOutOfMemoryError, OutOfMemory);
  CPPUNIT_TEST_EXCEPTION( testThrowInvalidParamError,InvalidParam);
  CPPUNIT_TEST ( testErrorData );
  CPPUNIT_TEST_SUITE_END ();

  public:

    void setUp () {}

    void tearDown () {}

    void testThrowOutOfMemoryError ()
    {
      HUMMSTRUMM_THROW (OutOfMemory, "I'm out of memory!");
    }

    void testThrowInvalidParamError ()
    {
      HUMMSTRUMM_THROW (InvalidParam, "Can't do that, man.");
    }

    void testErrorData ()
    {
      Generic error ("filename.txt", 51, "testFunction()", "This is a test");

      CPPUNIT_ASSERT( 0 == strcmp (error.GetFileName (), "filename.txt") );
      CPPUNIT_ASSERT( 0 == strcmp (error.GetFunction (), "testFunction()") );
      CPPUNIT_ASSERT( 0 == strcmp (error.GetText (), "This is a test") );
      CPPUNIT_ASSERT( error.GetLineNumber () == 51 );
    }

  private:

};


CPPUNIT_TEST_SUITE_REGISTRATION ( ErrorTest );


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
