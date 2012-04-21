// -*- mode: c++; c-file-style: hummstrumm -*-
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
    CPPUNIT_TEST_SUITE (ErrorTest);
    CPPUNIT_TEST (testData);
    // Uncomment if you want to test serialization.
//    CPPUNIT_TEST ( testSerialization );
    CPPUNIT_TEST_EXCEPTION (testThrowDivisionByZeroError, DivisionByZero);
    CPPUNIT_TEST_EXCEPTION (testThrowInvalidParamError, InvalidParam);
    CPPUNIT_TEST_EXCEPTION (testThrowOutOfMemoryError, OutOfMemory);
    CPPUNIT_TEST_EXCEPTION (testThrowWindowSystemError, WindowSystem);
    CPPUNIT_TEST_EXCEPTION (testThrowOutOfRangeError, OutOfRange);
    CPPUNIT_TEST_EXCEPTION (testThrowGenericError, Generic);
    CPPUNIT_TEST_EXCEPTION (testThrowMemoryCorruptionError, MemoryCorruption);
    CPPUNIT_TEST_EXCEPTION (testThrowUnicodeError, Unicode);
    CPPUNIT_TEST_SUITE_END ();

  public:

    void setUp () {}

    void tearDown () {}

    void testThrowDivisionByZeroError ()
    {
      HUMMSTRUMM_THROW (DivisionByZero, "Undefined?  Ask Webster.");
    }

    void testThrowInvalidParamError ()
    {
      HUMMSTRUMM_THROW (InvalidParam, "Can't do that, man.");
    }

    void testThrowOutOfMemoryError ()
    {
      HUMMSTRUMM_THROW (OutOfMemory, "I'm out of memory!");
    }

    void testThrowWindowSystemError ()
    {
      HUMMSTRUMM_THROW (WindowSystem, "Something went wrong with the windows.");
    }

    void testThrowOutOfRangeError ()
    {
      HUMMSTRUMM_THROW (OutOfRange, "Keep track of your array indices.");
    }

    void testThrowGenericError ()
    {
      HUMMSTRUMM_THROW (Generic, "I'm just throwing an error to spite you.");
    }

    void testThrowMemoryCorruptionError ()
    {
      HUMMSTRUMM_THROW (MemoryCorruption, "Someone really screwed up.");
    }

    void testThrowUnicodeError ()
    {
      HUMMSTRUMM_THROW (Unicode, "Unicode nun ne bonas, ĉu?");
    }

    void testData ()
    {
      Generic error ("filename.txt", 51, "testFunction()", "This is a test");

      CPPUNIT_ASSERT( 0 == strcmp (error.GetFileName (), "filename.txt") );
      CPPUNIT_ASSERT( 0 == strcmp (error.GetFunction (), "testFunction()") );
      CPPUNIT_ASSERT( 0 == strcmp (error.GetText (), "This is a test") );
      CPPUNIT_ASSERT( error.GetLineNumber () == 51 );
    }

    void testSerialization ()
    {
      Generic error1 ("hello.cpp", 52, "main()", "Test error.");
      Generic error2 ("none", 45, "Foo::Bar(int)", "Another error.");

      std::cerr << error1 << std::endl << error2 << std::endl;
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
