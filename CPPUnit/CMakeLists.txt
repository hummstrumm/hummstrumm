# CMake File for CPPUnit, Windows OS
# Written by Patrick Niedzielski <PatrickNiedzielski@gmail.com>
#
# This is free and unencumbered software released into the public domain.
#
# Anyone is free to copy, modify, publish, use, compile, sell, or
# distribute this software, either in source code form or as a compiled
# binary, for any purpose, commercial or non-commercial, and by any
# means.
#
# In jurisdictions that recognize copyright laws, the author or authors
# of this software dedicate any and all copyright interest in the
# software to the public domain. We make this dedication for the benefit
# of the public at large and to the detriment of our heirs and
# successors. We intend this dedication to be an overt act of
# relinquishment in perpetuity of all present and future rights to this
# software under copyright law.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# For more information, please refer to <http://unlicense.org/>


# Right, so what is this file?  This is the CMake file for compiling CPPUnit
# on Windows systems...  I make no guarantees that this works on anything
# besides Windows, because if you are on any other platform, you would be using
# the actual release, now wouldn't you?

set (cppunit_SRCS
  src/AdditionalMessage.cpp
  src/Asserter.cpp
  src/BriefTestProgressListener.cpp
  src/CompilerOutputter.cpp
  src/DefaultProtector.cpp
  src/DynamicLibraryManager.cpp
  src/DynamicLibraryManagerException.cpp
  src/Exception.cpp
  src/Message.cpp
  src/RepeatedTest.cpp
  src/PlugInManager.cpp
  src/PlugInParameters.cpp
  src/Protector.cpp
  src/ProtectorChain.cpp
  src/SourceLine.cpp
  src/StringTools.cpp
  src/SynchronizedObject.cpp
  src/Test.cpp
  src/TestAssert.cpp
  src/TestCase.cpp
  src/TestCaseDecorator.cpp
  src/TestComposite.cpp
  src/TestDecorator.cpp
  src/TestFactoryRegistry.cpp
  src/TestFailure.cpp
  src/TestLeaf.cpp
  src/TestNamer.cpp
  src/TestPath.cpp
  src/TestPlugInDefaultImpl.cpp
  src/TestResult.cpp
  src/TestResultCollector.cpp
  src/TestSuccessListener.cpp
  src/TestRunner.cpp
  src/TestSetUp.cpp
  src/TestSuite.cpp
  src/TestSuiteBuilderContext.cpp
  src/TextOutputter.cpp
  src/TextTestProgressListener.cpp
  src/TextTestResult.cpp
  src/TextTestRunner.cpp
  src/TypeInfoHelper.cpp
  src/XmlDocument.cpp
  src/XmlElement.cpp
  src/XmlOutputter.cpp
  src/XmlOutputterHook.cpp)

include_directories (include/)
if (HUMMSTRUMM_PLATFORM_WINDOWS)
  set (CMAKE_CXX_FLAGS_DEBUG "/Od /Zi")
  set (CMAKE_CXX_FLAGS "/w /EHsc")
endif (HUMMSTRUMM_PLATFORM_WINDOWS)
add_library (cppunit STATIC ${cppunit_SRCS})