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
#include "hummstrummengine.hpp"

#include <wchar.h>
#include <cstring>

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

using namespace hummstrumm::engine::system;

class EndiannessTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( EndiannessTest );
  CPPUNIT_TEST ( testEndianStorage );
  CPPUNIT_TEST_SUITE_END ();

  public:

    void setUp () {}

    void tearDown () {}

    void testEndianStorage ()
    {
      Endianness::Endian littleEndian (Endianness::Little);
      Endianness::Endian bigEndian (Endianness::Big);
      Endianness::Endian anotherLittleEndian (Endianness::Little);
      Endianness::Endian anotherBigEndian (bigEndian);
      
      CPPUNIT_ASSERT ( littleEndian == Endianness::Little );
      CPPUNIT_ASSERT ( bigEndian == Endianness::Big );
      CPPUNIT_ASSERT ( anotherLittleEndian == Endianness::Little );
      CPPUNIT_ASSERT ( anotherBigEndian == Endianness::Big );
      
      CPPUNIT_ASSERT ( littleEndian == littleEndian );
      CPPUNIT_ASSERT ( bigEndian == bigEndian );
      CPPUNIT_ASSERT ( anotherLittleEndian == anotherLittleEndian );
      CPPUNIT_ASSERT ( anotherBigEndian == anotherBigEndian );
      
      CPPUNIT_ASSERT ( anotherLittleEndian == littleEndian );
      CPPUNIT_ASSERT ( littleEndian == anotherLittleEndian );
      CPPUNIT_ASSERT ( anotherBigEndian == bigEndian );
      CPPUNIT_ASSERT ( bigEndian == anotherBigEndian );
      
      CPPUNIT_ASSERT ( littleEndian != bigEndian );
      CPPUNIT_ASSERT ( littleEndian != anotherBigEndian );
      CPPUNIT_ASSERT ( bigEndian != littleEndian );
      CPPUNIT_ASSERT ( bigEndian != anotherLittleEndian );
      CPPUNIT_ASSERT ( anotherLittleEndian != bigEndian );
      CPPUNIT_ASSERT ( anotherLittleEndian != anotherBigEndian );
      CPPUNIT_ASSERT ( anotherBigEndian != littleEndian );
      CPPUNIT_ASSERT ( anotherBigEndian != anotherLittleEndian );
    }

  private:

};


CPPUNIT_TEST_SUITE_REGISTRATION ( EndiannessTest );


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
