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

/**
 * Defines several debugging macros.
 * 
 * @file   debug/utils.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-03
 */

#ifndef HUMMSTRUMM_ENGINE_DEBUG_UTILS
#define HUMMSTRUMM_ENGINE_DEBUG_UTILS

#include <iostream>
#include <stdlib.h>

#ifdef HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX
#  include <signal.h>
#endif
#ifdef HUMMSTRUMM_ENGINE_PLATFORM_WINDOWS
#  include <windows.h>
#endif
#ifdef HUMMSTRUMM_ENGINE_PLATFORM_BSD
#  include <signal.h>
#endif


/**
 * Returns an error on compile if the given condition is false.
 *
 * @def    HUMMSTRUMM_STATIC_ASSERT
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2011-12-23
 * @since  0.5
 *
 * @param [in] condition The condition to check for truth.
 * @param [in] message   The message to affix to the error.
 */
#if HUMMSTRUMM_ENGINE_HAVE_NATIVE_STATIC_ASSERT
#  define HUMMSTRUMM_ENGINE_STATIC_ASSERT(condition, message) \
  static_assert (condition, message)
#else
template <bool condition> struct StaticAssertionFailed;
template <> struct StaticAssertionFailed<true> {};
#  define HUMMSTRUMM_ENGINE_STATIC_ASSERT(condition, message) \
  StaticAssertionFailed<(condition) && message>        \
    static_assert_##__COUNTER__##_no_clash__;
#endif


/**
 * Aborts the program with a nonzero return value.
 *
 * This is only available in a debug build.
 *
 * @def    HUMMSTRUMM_ABORT()
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-03
 * @since  0.2
 */
#ifdef HUMMSTRUMM_ENGINE_DEBUG

#define HUMMSTRUMM_ENGINE_ABORT()		\
  do {                                          \
    abort ();                                   \
  } while (false)

#else // #ifdef HUMMSTRUMM_ENGINE_DEBUG

#define HUMMSTRUMM_ENGINE_ABORT()

#endif // #ifdef HUMMSTRUMM_ENGINE_DEBUG

/**
 * Attempts to break into the debugger.  On Windows systems, this is
 * accomplished through a call to the DebugBreak() function.  On UNIX
 * systems, a SIGINT signal is raised for the current process.
 *
 * This is only available in a debug build.
 *
 * @def    HUMMSTRUMM_BREAK()
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-03
 * @since  0.2
 */
#ifdef HUMMSTRUMM_ENGINE_DEBUG
#if defined (HUMMSTRUMM_ENGINE_PLATFORM_GNULINUX) || \
    defined (HUMMSTRUMM_ENGINE_PLATFORM_BSD)

#define HUMMSTRUMM_ENGINE_BREAK()                      \
  do {                                          \
    raise (SIGINT);                             \
  } while (false)

#else

#define HUMMSTRUMM_ENGINE_BREAK()                      \
  do {                                          \
    DebugBreak ();                              \
  } while (false)

#endif

#else // #ifdef HUMMSTRUMM_ENGINE_DEBUG

#define HUMMSTRUMM_ENGINE_BREAK()

#endif // #ifdef HUMMSTRUMM_ENGINE_DEBUG


/**
 * Prompts the user after an error on how to procede.  The user can
 * abort the program, break into the debugger, or ignore the error.
 *
 * This is only available in a debug build.
 *
 * @def    HUMMSTRUMM_ENGINE_ERROR()
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-03
 * @since  0.2
 */
#ifdef HUMMSTRUMM_ENGINE_DEBUG

#define HUMMSTRUMM_ENGINE_ERROR()                                  \
  do {                                                      \
    std::wcerr << L"An error has occured in the program.  " \
               << L"Press A to abort, B to break into the " \
               << L"debugger, or any key to ignore it.\n";  \
    switch (std::wcin.get ())                               \
      {                                                     \
      case 'A':                                             \
      case 'a':                                             \
        HUMMSTRUMM_ENGINE_ABORT ();                                \
        break;                                              \
      case 'B':                                             \
      case 'b':                                             \
        HUMMSTRUMM_ENGINE_BREAK ();                                \
        break;                                              \
      default:                                              \
        break;                                              \
      }                                                     \
  } while (false)

#else // #ifdef HUMMSTRUMM_ENGINE_DEBUG

#define HUMMSTRUMM_ENGINE_ERROR()

#endif // #ifdef HUMMSTRUMM_ENGINE_DEBUG

/**
 * Asserts that the specified value is true.  If it is not, an error
 * message is displayed.
 *
 * This is only available in a debug build.
 *
 * @def    HUMMSTRUMM_ENGINE_ASSERT(mustBeTrue)
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-03
 * @since  0.2
 */
#ifdef HUMMSTRUMM_ENGINE_DEBUG

#define HUMMSTRUMM_ENGINE_ASSERT(mustBeTrue)           \
  do {                                          \
    if (!mustBeTrue) {                          \
      HUMMSTRUMM_ENGINE_ERROR();                       \
    }                                           \
  } while (false)

#else // #ifdef HUMMSTRUMM_ENGINE_DEBUG

#define HUMMSTRUMM_ENGINE_ASSERT(mustBeTrue)

#endif // #ifdef HUMMSTRUMM_ENGINE_DEBUG

/**
 * Prints a warning to the screen and to the logs.
 *
 * This is only available in a debug build.
 *
 * @def    HUMMSTRUMM_ENGINE_WARNING(text)
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-07-26
 * @since  0.3
 */
#ifdef HUMMSTRUMM_ENGINE_DEBUG

#define HUMMSTRUMM_ENGINE_WARNING(text)                                               \
  do {                                                                         \
    HUMMSTRUMM_ENGINE_LOG(text, WARNING);                                             \
    std::cerr << "WARNING: " << text << "\n";                                  \
  } while (false)

#else // #ifdef HUMMSTRUMM_ENGINE_DEBUG

#define HUMMSTRUMM_ENGINE_WARNING(text)

#endif // #ifdef HUMMSTRUMM_ENGINE_DEBUG


#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_UTILS
