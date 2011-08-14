// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2011, the people listed in the AUTHORS file. 
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

using namespace hummstrumm::engine::core;

class HeapTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( HeapTest );
  CPPUNIT_TEST ( testAllocation );
//  CPPUNIT_TEST ( testFragmentation );
  CPPUNIT_TEST_SUITE_END ();

  public:

    void setUp () {}

    void tearDown () {}

    void testAllocation ()
    {
      Object *a = new Object;
      Object *b = new Object[5];
      Object::Ptr c[65];
      
      int i;
      
      for (i = 0; i < 65; i++)
        {
          c[i] = new Object;
        }
      delete[] b;
      delete a;
    }
    
    void testFragmentation ()
    {
      Object::Ptr c[65];
      
      int i;
      
      for (i = 0; i < 65; i++)
        {
          c[i] = new Object;
        }
      
      for (i = 0; i < 65; i += 2)
        {
          c[i] = new Object;
        }
    }

  private:

};

/*class PoolTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( PoolTest );
  CPPUNIT_TEST ( testAllocation );
  CPPUNIT_TEST ( testFragmentation );
  CPPUNIT_TEST_SUITE_END ();

  public:

    void setUp () {}

    void tearDown () {}

    void testAllocation ()
    {
      Pool<int, 1009> p; // Unless your characters are 1009 bits each, then this
                         // prime number will not be a multiple of CHAR_BIT.
      
      int *a; p.Allocate (&a);
      int *b; p.Allocate (&b);
      int *c[65];
      
      int i;
      
      for (i = 0; i < 65; i++)
        {
          p.Allocate (&c[i]);
        }
      
      for (i = 0; i < 65; i++)
        {
          p.Free (&c[i]);
        }
      
      p.Free (&b);
      p.Free (&a);
    }
    
    void testFragmentation ()
    {
      Pool<Object, 1009> p; // Unless your characters are 1009 bits each, then this
                         // prime number will not be a multiple of CHAR_BIT.
      Object *c[65];
      
      int i;
      
      for (i = 0; i < 65; i++)
        {
          p.Allocate (&c[i]);
        }
      
      for (i = 0; i < 65; i += 2)
        {
          p.Free (&c[i]);
        };
      
      for (i = 0; i < 65; i += 2)
        {
          p.Allocate (&c[i]);
        }
        
      for (i = 0; i < 65; i++)
        {
          p.Free (&c[i]);
        }
    }

  private:

  };*/

class TypeTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( TypeTest );
  CPPUNIT_TEST ( testConstructor );
  CPPUNIT_TEST_SUITE_END ();

  public:

    void setUp () {}

    void tearDown () {}

    void testConstructor ()
    {
      Type root ("Root", 8, 0, 0);
      Type d1 ("Derived1", 44, &root, 0);
      Type d2 ("Derived2", 162, &root, 0);
      Type gc ("Grandchild", 340, &d1, 0);
    }

  private:

};

CPPUNIT_TEST_SUITE_REGISTRATION ( HeapTest );
//CPPUNIT_TEST_SUITE_REGISTRATION ( PoolTest );
CPPUNIT_TEST_SUITE_REGISTRATION ( TypeTest );

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
