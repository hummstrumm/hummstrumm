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

/**
 * Defines several debugging macros.
 * 
 * @file   utils.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-03
 */

#ifndef HUMMSTRUMM_ENGINE_DEBUG_UTILS
#define HUMMSTRUMM_ENGINE_DEBUG_UTILS

#include <iostream>
#include <stdlib.h>

#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
#  include <signal.h>
#else
#  include <windows.h>
#endif


/**
 * Aborts the program with a nonzero return value.
 *
 * This is only available in a debug build.
 *
 * @def    ABORT()
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-03
 * @since  0.2
 */
#ifdef HUMMSTRUMM_DEBUG

#define ABORT()                                 \
  do {                                          \
    abort ();                                   \
  } while (true)

#else // #ifdef HUMMSTRUMM_DEBUG

#define ABORT()

#endif // #ifdef HUMMSTRUMM_DEBUG

/**
 * Attempts to break into the debugger.  On Windows systems, this is
 * accomplished through a call to the DebugBreak() function.  On UNIX
 * systems, a SIGINT signal is raised for the current process.
 *
 * This is only available in a debug build.
 *
 * @def    BREAK()
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-03
 * @since  0.2
 */
#ifdef HUMMSTRUMM_DEBUG
#ifdef HUMMSTRUMM_PLATFORM_GNULINUX

#define BREAK()                                 \
  do {                                          \
    raise (SIGINT);                             \
  } while (true)

#else

#define BREAK()                                 \
  do {                                          \
    DebugBreak ();                              \
  } while (true)

#endif

#else // #ifdef HUMMSTRUMM_DEBUG

#define BREAK()

#endif // #ifdef HUMMSTRUMM_DEBUG


/**
 * Prompts the user after an error on how to procede.  The user can
 * abort the program, break into the debugger, or ignore the error.
 *
 * This is only available in a debug build.
 *
 * @def    ERROR()
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-03
 * @since  0.2
 */
#ifdef HUMMSTRUMM_DEBUG

#define ERROR()                                             \
  do {                                                      \
    std::wcerr << L"An error has occured in the program.  " \
               << L"Press A to abort, B to break into the " \
               << L"debugger, or any key to ignore it.\n";  \
    switch (std::wcin.get ())                               \
      {                                                     \
      case 'A':                                             \
      case 'a':                                             \
        ABORT ();                                           \
        break;                                              \
      case 'B':                                             \
      case 'b':                                             \
        BREAK ();                                           \
        break;                                              \
      default:                                              \
        break;                                              \
      }                                                     \
  } while (true)

#else // #ifdef HUMMSTRUMM_DEBUG

#define ERROR()

#endif // #ifdef HUMMSTRUMM_DEBUG

/**
 * Asserts that the specified value is true.  If it is not, an error
 * message is displayed.
 *
 * This is only available in a debug build.
 *
 * @def    ASSERT(mustBeTrue)
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-03-03
 * @since  0.2
 */
#ifdef HUMMSTRUMM_DEBUG

#define ASSERT(mustBeTrue)                      \
  do {                                          \
    if (!mustBeTrue) {                          \
      ERROR();                                  \
    }                                           \
  } while (true)

#else // #ifdef HUMMSTRUMM_DEBUG

#define ASSERT(mustBeTrue)

#endif // #ifdef HUMMSTRUMM_DEBUG


#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_UTILS
