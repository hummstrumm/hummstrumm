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

using namespace hummstrumm::engine::types;

class NumberTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( NumberTest );
  CPPUNIT_TEST ( testConstructor );
  CPPUNIT_TEST ( testAssignment );
  CPPUNIT_TEST ( testEquality );
  CPPUNIT_TEST ( testNegate );
  CPPUNIT_TEST ( testSubtraction );
  CPPUNIT_TEST ( testAdd );
  CPPUNIT_TEST ( testMultiplication );
  CPPUNIT_TEST ( testDivision );
  CPPUNIT_TEST ( testAbsoluteValue );
  CPPUNIT_TEST ( testSign );
  CPPUNIT_TEST ( testPower );
  CPPUNIT_TEST ( testLog );
  CPPUNIT_TEST ( testSquareRoot );
  CPPUNIT_TEST ( testRound );
  CPPUNIT_TEST ( testInteger );
  CPPUNIT_TEST_SUITE_END ();

  public:

    void setUp () {}

    void tearDown () {}

    void testConstructor ()
    {
      Number n0;                        // Default constructor
      Number n1 (n0);                   // Copy constructor
      Number n2 (1.0);
      Number n3 (3.5f);
      Number n4 (4527);
      Number n5 (36751);
      Number n6 (761170);
      Number n7 (6731712);
      Number n8 (70610630153);
      Number n9 (99999999999); 
      
      CPPUNIT_ASSERT ( n0 == 0 );
      CPPUNIT_ASSERT ( n1 == 0 );
      CPPUNIT_ASSERT ( n2 == 1 );
      CPPUNIT_ASSERT ( n3 == 3.5 );
      CPPUNIT_ASSERT ( n4 == 4527 );
      CPPUNIT_ASSERT ( n5 == 36751 );
      CPPUNIT_ASSERT ( n6 == 761170 );
      CPPUNIT_ASSERT ( n7 == 6731712 );
      CPPUNIT_ASSERT ( n8 == 70610630153 );
      CPPUNIT_ASSERT ( n9 == 99999999999 );     
    }

    void testAssignment ()
    {

      Number n1 = 3.0;
      Number n2 = 5.5;
      Number n3 = 67;
      
      n1 = n2;
      CPPUNIT_ASSERT ( n1 == n2 );
      
      n1 = n3;
      CPPUNIT_ASSERT ( n1 == n3 );
      CPPUNIT_ASSERT ( n1 != n2 );
      
      n2 = n3;
      CPPUNIT_ASSERT ( n1 == n2 );
      CPPUNIT_ASSERT ( n1 == n3 );
    }

    void testEquality ()
    {
      Number n1 = 45;
      Number n2 = 45;
      Number n3 = 72;

      CPPUNIT_ASSERT (n1 == n1);
      CPPUNIT_ASSERT (n2 == n1);
      CPPUNIT_ASSERT (n2 != n3);
      
      CPPUNIT_ASSERT (n3 < n1 + n2);
      CPPUNIT_ASSERT (n1 <= n3);
      CPPUNIT_ASSERT (n1 <= n2);
      
      CPPUNIT_ASSERT (n3 > n2);
      CPPUNIT_ASSERT (n3 >= n2);
      CPPUNIT_ASSERT (n3 >= n2 + 27);
    }

    void testNegate ()
    {
      Number n1 = 0;
      Number n2 = 1;
      Number n3 = -1;
      Number n4 = 172.67;
      
      CPPUNIT_ASSERT (+n1 == n1);
      CPPUNIT_ASSERT (+n2 == n2);
      CPPUNIT_ASSERT (+n3 == n3);
      CPPUNIT_ASSERT (+n4 == n4);
      
      CPPUNIT_ASSERT (-n1 == 0);
      CPPUNIT_ASSERT (-n2 == -1);
      CPPUNIT_ASSERT (-n3 == 1);
      CPPUNIT_ASSERT (-n4 == -172.67);
    }

    void testSubtraction ()
    {
      Number n1 = 17.8;
      Number n2 = 7;
      Number n3 = 832;

      CPPUNIT_ASSERT (n1 - n2 == 10.8);
      CPPUNIT_ASSERT (n2 - n1 == -10.8);
      CPPUNIT_ASSERT (n1 - n1 == 0);
      CPPUNIT_ASSERT (n3 - n2 == 825);
      CPPUNIT_ASSERT (n1 - n3 == -814.2);
      CPPUNIT_ASSERT (n1 - 0  == n1);
      CPPUNIT_ASSERT (n1 - n1 == 0);
      
      n1 -= n2;
      CPPUNIT_ASSERT (n1 == 10.8);
      CPPUNIT_ASSERT (n1 + n2 == 17.8);
      
      n1 = 17.8;
      n3 -= n2 - n1;
      CPPUNIT_ASSERT (n3 == 842.8);
    }

    void testAdd ()
    {
      Number n1 = 0.2;
      Number n2 = 1;
      Number n3 = 99;
      
      CPPUNIT_ASSERT (n1 + n2 == 1.2);
      CPPUNIT_ASSERT (n1 + n3 == 99.2);
      CPPUNIT_ASSERT (n2 + n3 == 100);
      CPPUNIT_ASSERT (n1 + n2 == n2 + n1);
      CPPUNIT_ASSERT (n3 + 0  == n3);
      
      n2 += n3;
      CPPUNIT_ASSERT (n2 == 100);
      
      n3 += n3 + n1;
      CPPUNIT_ASSERT (n3 == 198.2);
    }

    void testMultiplication ()
    {
      Number n1 = 0;
      Number n2 = 1;
      Number n3 = 43.2;
      Number n4 = 17;
      Number n5 = -7;
      
      CPPUNIT_ASSERT (n1 * n3 == 0);
      CPPUNIT_ASSERT (n2 * n4 == 17);
      CPPUNIT_ASSERT (n5 * n4 == -119);
      CPPUNIT_ASSERT (n5 * n2 == n5);
      CPPUNIT_ASSERT (n4 * n3 == n3 * n4);
      CPPUNIT_ASSERT (n3 * -1 == -43.2);
      
      n1 *= 14;
      CPPUNIT_ASSERT (n1 == 0);

      n5 *= n1 - n2;
      CPPUNIT_ASSERT (n5 == 7);
    }

    void testDivision ()
    {
      Number n1 = 0;
      Number n2 = 1;
      Number n3 = 48;
      Number n4 = 2.5;
      Number n5 = -6;
      
      CPPUNIT_ASSERT (n1 / n4 == 0);
      CPPUNIT_ASSERT (n3 / n2 == n3);
      CPPUNIT_ASSERT (n3 / n5 == -8);
      CPPUNIT_ASSERT (n5 / -n4 == 2.4);
      CPPUNIT_ASSERT (n2 / n3 == 1.0 / 48);
      CPPUNIT_ASSERT (n3 % n5 == 0);
      CPPUNIT_ASSERT (n5 % n4 == -1);
      
      n1 /= n5;
      CPPUNIT_ASSERT (n1 == 0);
      
      n5 %= n4;
      CPPUNIT_ASSERT (n5 == -1);
      
      n3 %= n2;
      CPPUNIT_ASSERT (n3 == 0);
    }
  
    void testAbsoluteValue ()
    {
      Number n1 = 0;
      Number n2 = 1;
      Number n3 = -1;
      
      CPPUNIT_ASSERT (n1.Abs () == 0);
      CPPUNIT_ASSERT (n2.Abs () == 1);
      CPPUNIT_ASSERT (n3.Abs () == 1);
    }
    
    void testSign ()
    {
      Number n1 = +0;
      Number n2 = -3;
      Number n3 = 1;
      
      CPPUNIT_ASSERT (n1.Sign () == 1);
      CPPUNIT_ASSERT (n2.Sign () == -1);
      CPPUNIT_ASSERT (n3.Sign () == 1);
    }
    
    void testPower ()
    {
      Number n1 = 2;
      Number n2 = 0;
      Number n3 = -1;
      
      CPPUNIT_ASSERT (n1.Power (5) == 32);
      CPPUNIT_ASSERT (n2.Power (72) == 0);
      CPPUNIT_ASSERT (n3.Power (23) == -1);
    }
    
    void testLog ()
    {
      Number n1 = 64;
      Number n2 = 8;
      Number n3 = 81;
      
      CPPUNIT_ASSERT (n1.Log (2) == 6);
      CPPUNIT_ASSERT (n2.Log (2) == 3);
      CPPUNIT_ASSERT (n3.Log (3) == 4);
    }
    
    void testSquareRoot ()
    {
      Number n1 = 1024;
      Number n2 = 4;
      Number n3 = 225;
      
      CPPUNIT_ASSERT (n1.Sqrt () == 32);
      CPPUNIT_ASSERT (n2.Sqrt () == 2);
      CPPUNIT_ASSERT (n3.Sqrt () == 15);
    }
    
    void testRound ()
    {
      Number n1 = 10;
      Number n2 = -6.7;
      Number n3 = 7.5;
      Number n4 = 1.1;
      
      CPPUNIT_ASSERT (n1.Round () == 10);
      CPPUNIT_ASSERT (n1.Floor () == 10);
      CPPUNIT_ASSERT (n1.Ceil  () == 10);
      
      CPPUNIT_ASSERT (n2.Round () == -7);
      CPPUNIT_ASSERT (n2.Floor () == -7);
      CPPUNIT_ASSERT (n2.Ceil  () == -6);
      
      CPPUNIT_ASSERT (n3.Round () == 8);
      CPPUNIT_ASSERT (n3.Floor () == 7);
      CPPUNIT_ASSERT (n3.Ceil  () == 8);
      
      CPPUNIT_ASSERT (n4.Round () == 1);
      CPPUNIT_ASSERT (n4.Floor () == 1);
      CPPUNIT_ASSERT (n4.Ceil  () == 2);
    }
    
    void testInteger ()
    {
      Number n1 = 3.2;
      Number n2 = 0;
      Number n3 = 3.0001;
      Number n4 = 1;
      
      CPPUNIT_ASSERT (!n1.IsInteger ());
      CPPUNIT_ASSERT (n2.IsInteger ());
      CPPUNIT_ASSERT (!n3.IsInteger ());
      CPPUNIT_ASSERT (n4.IsInteger ());
    }

  private:

};


class StringTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( StringTest );
  CPPUNIT_TEST ( testConstructor );
  CPPUNIT_TEST ( testAssignment );
  CPPUNIT_TEST ( testEquality );
  CPPUNIT_TEST ( testConcatenation );
  CPPUNIT_TEST ( testCharacter );
  CPPUNIT_TEST ( testIndex );
  CPPUNIT_TEST ( testLength );
  CPPUNIT_TEST ( testUnicode );
  CPPUNIT_TEST ( testAscii );
  CPPUNIT_TEST_SUITE_END ();

  public:

    void setUp () {}

    void tearDown () {}

    void testConstructor ()
    {
      String s0;                        // Default constructor
      String s1 (s0);                   // Copy constructor
      String s2 (L'w');
      String s3 (L"Test Unicode String");
      String s4 ('a');
      String s5 ("Test ASCII String");
      String s6 (Number (34.6));
      
      CPPUNIT_ASSERT ( s0 == "" );
      CPPUNIT_ASSERT ( s1 == s0 );
      CPPUNIT_ASSERT ( s2 == L'w' );
      CPPUNIT_ASSERT ( s3 == L"Test Unicode String" );
      CPPUNIT_ASSERT ( s4 == 'a' );
      CPPUNIT_ASSERT ( s5 == "Test ASCII String" );
      CPPUNIT_ASSERT ( s6 == String (Number (34.6)) );
    }

    void testAssignment ()
    {
      String s1 ("String");
      String s2 (L'c');
      String s3 (Number (4.5));
      
      s1 = s2;
      CPPUNIT_ASSERT ( s1 == s2 );
      
      s1 = s3;
      CPPUNIT_ASSERT ( s1 == s3 );
      CPPUNIT_ASSERT ( s1 != s2 );
      
      s2 = s3;
      CPPUNIT_ASSERT ( s1 == s2 );
      CPPUNIT_ASSERT ( s1 == s3 );
    }

    void testEquality ()
    {
      String s1 = "Test";
      String s2 = L"Test";
      String s3 = "test";
      String s4 = 'f';

      CPPUNIT_ASSERT (s1 == s1);
      CPPUNIT_ASSERT (s2 == s1);
      CPPUNIT_ASSERT (s2 != s3);
      CPPUNIT_ASSERT (s4 == L'f');
    }

    void testConcatenation ()
    {
      String s1 = L"Hi!  My name is ";
      String s2 = "C++";
      String s3 = String (Number (15));
      
      CPPUNIT_ASSERT (s1 + s2 == "Hi!  My name is C++");
      CPPUNIT_ASSERT (s1 + s3 == String (L"Hi!  My name is ") +
                                 String (Number (15)));
      CPPUNIT_ASSERT (s3 + ""  == s3);
      
      s2 += s3;
      CPPUNIT_ASSERT (s2 == String ("C++") + String (Number (15)));
      
      s3 += s3 + s1;
      CPPUNIT_ASSERT (s3 == String (Number (15)) + String (Number (15)) + s1);
    }
  
    void testCharacter ()
    {
      String s1 = L"Not a char";
      String s2 = "C";
      String s3 = L"m";
      
      CPPUNIT_ASSERT (!s1.IsCharacter ());
      CPPUNIT_ASSERT (s2.IsCharacter ());
      CPPUNIT_ASSERT (s3.IsCharacter ());
    }
    
    void testIndex ()
    {
      String s1 = L"abcdefghijklmnopqrstuvwxyz";
      String s2 = "The quick brown fox jumps over the lazy dog.";
      String s3 = "Yes";
      
      CPPUNIT_ASSERT (s1[0] == L'a');
      CPPUNIT_ASSERT (s1[18] == L's');
      CPPUNIT_ASSERT (s2[24] == L's');
      CPPUNIT_ASSERT (s3[18] == L'\0');
    }
    
    void testLength ()
    {
      String s1 = L"abcdefghijklmnopqrstuvwxyz";
      String s2 = "The quick brown fox jumps over the lazy dog.";
      String s3 = "Yes";
      
      CPPUNIT_ASSERT (s1.GetLength () == 26);
      CPPUNIT_ASSERT (s2.GetLength () == 44);
      CPPUNIT_ASSERT (s3.GetLength () == 3);
    }
    
    void testAscii ()
    {
      String s1 = L"abcdefghijklmnopqrstuvwxyz";
      String s2 = "The quick brown fox jumps over the lazy dog.";
      String s3 = "Yes";
      
      CPPUNIT_ASSERT (std::strcmp (s1.ToAscii (),
                                   "abcdefghijklmnopqrstuvwxyz") == 0);
      CPPUNIT_ASSERT (std::strcmp (s2.ToAscii (),
                                   "The quick brown fox jumps over the lazy "
                                   "dog.") == 0);
      CPPUNIT_ASSERT (std::strcmp (s3.ToAscii (), "Yes") == 0);
    }
    
    void testUnicode ()
    {
      String s1 = L"abcdefghijklmnopqrstuvwxyz";
      String s2 = "The quick brown fox jumps over the lazy dog.";
      String s3 = "Yes";
      
      CPPUNIT_ASSERT (wcscmp (s1.ToUnicode (),
                              L"abcdefghijklmnopqrstuvwxyz") == 0);
      CPPUNIT_ASSERT (wcscmp (s2.ToUnicode (),
                              L"The quick brown fox jumps over the lazy "
                              L"dog.") == 0);
      CPPUNIT_ASSERT (wcscmp (s3.ToUnicode (), L"Yes") == 0);
    }

  private:

};


class CharacterTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE ( CharacterTest );
  CPPUNIT_TEST ( testConstructor );
  CPPUNIT_TEST ( testAssignment );
  CPPUNIT_TEST ( testEquality );
  CPPUNIT_TEST ( testAscii );
  CPPUNIT_TEST ( testConversions );
  CPPUNIT_TEST ( testCategories );
  CPPUNIT_TEST_SUITE_END ();

  public:

    void setUp () {}

    void tearDown () {}

    void testConstructor ()
    {
      Character c0;                        // Default constructor
      Character c1 (c0);                   // Copy constructor
      Character c2 (L'ぽ');                // Mmhm...it's Hiragana...
      Character c3 ('a');                  // Latin alphabet
      char bytes[4] = { (char)232,
                        (char)135,
                        (char)187,
                        (char)0 };
      Character c4 (bytes);                // Han character 臻

      CPPUNIT_ASSERT ( c0 == '\0' );
      CPPUNIT_ASSERT ( c1 == c0 );
      CPPUNIT_ASSERT ( c2 == L'ぽ' );
      CPPUNIT_ASSERT ( c3 == 'a' );
      CPPUNIT_ASSERT ( c3 == L'a' );
      
#ifndef HUMMSTRUMM_PLATFORM_WINDOWS
      Character c5 (L'𐏉');                // Old Persian, just in case...
      Character c6 (L'臻');
      CPPUNIT_ASSERT ( c5 == L'𐏉');
      CPPUNIT_ASSERT ( c4 == L'臻');
#endif // #if HUMMSTRUMM_PLATFORM_WINDOWS
    }

    void testAssignment ()
    {
      Character c1 (L'β');
      Character c2 (L'c');
      Character c3 ('a');
      
      c1 = c2;
      CPPUNIT_ASSERT ( c1 == c2 );
      
      c1 = c3;
      CPPUNIT_ASSERT ( c1 == c3 );
      CPPUNIT_ASSERT ( c1 != c2 );
      
      c2 = c3;
      CPPUNIT_ASSERT ( c1 == c2 );
      CPPUNIT_ASSERT ( c1 == c3 );
    }

    void testEquality ()
    {
      Character c1 = L'a';
      Character c2 = 'a';
      Character c3 = L'ເ';
      Character c4 = 'f';

      CPPUNIT_ASSERT (c1 == c1);
      CPPUNIT_ASSERT (c2 == c1);
      CPPUNIT_ASSERT (c2 != c3);
      CPPUNIT_ASSERT (c4 == L'f');
    }

    void testAscii ()
    {
      Character c1 = L'4';
      Character c2 = L'ᤣ';
      Character c3 = '\0';
      
      CPPUNIT_ASSERT (c1.IsAscii ());
      CPPUNIT_ASSERT (!c2.IsAscii ());
      CPPUNIT_ASSERT (c3.IsAscii ());
    }
  
    void testConversions ()
    {
      Character c1 = L'N';
      Character c2 = L'𐤇';
      Character c3 = 'a';

      CPPUNIT_ASSERT (c1.ToChar () == 'N');
      CPPUNIT_ASSERT (c1.ToWchar_t () == L'N');
      CPPUNIT_ASSERT (c2.ToWchar_t () == L'𐤇');
      CPPUNIT_ASSERT (c3.ToChar () == 'a');
      CPPUNIT_ASSERT (c3.ToWchar_t () == L'a');
    }
    
    void testCategories ()
    {
      Character c1 = 'e';
      Character c2 = ';';
      Character c3 = 'P';
      // Maybe add some more later...?
      
      CPPUNIT_ASSERT (c1.GetCategory () == Character::Ll);
      CPPUNIT_ASSERT (c2.GetCategory () == Character::Po);
      CPPUNIT_ASSERT (c3.GetCategory () == Character::Lu);
    }

  private:

};


CPPUNIT_TEST_SUITE_REGISTRATION ( NumberTest );
CPPUNIT_TEST_SUITE_REGISTRATION ( StringTest );
CPPUNIT_TEST_SUITE_REGISTRATION ( CharacterTest );


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
