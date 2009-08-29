// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2009, the people listed in the AUTHORS file. 
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

#ifndef GAMEENGINE_COMPILECONFIG
#define GAMEENGINE_COMPILECONFIG

// Game Engine SDK version
#define GAMEENGINE_SDK_VERSION "1.0"

// Platforms
#if defined (WIN32) || defined (_WIN32)   // Win32
#  define GAMEENGINE_PLATFORM_WIN32
#  define GAMEENGINE_PLATFORM_WINDOWS
#  define GAMEENGINE_WINDOWSYSYEM_WINDOWS
#elif defined (WIN64) || defined (_WIN64) // Win64
#  define GAMEENGINE_PLATFORM_WIN64
#  define GAMEENGINE_PLATFORM_WINDOWS
#  define GAMEENGINE_WINDOWSYSYEM_WINDOWS
#else                                     // Linux
#  define GAMEENGINE_PLATFORM_LINUX
#  define GAMEENGINE_WINDOWSYSYEM_X11
#endif

// Stating heap size
#define GAMEENGINE_HEAP_SIZE 65536

// Size by which to expand the heap each time it expands
#define GAMEENGINE_HEAP_EXPAND 4096

// Method of heap allocation
#define GAMEENGINE_HEAP_FIRSTFIT
// #define GAMEENGINE_HEAP_BESTFIT

// Method of math calculations
#define GAMEENGINE_MATH_FAST
// #define GAMEENGINE_MATH_PRECISE

// #define GAMEENGINE_LIBRARY_STATIC

#if defined (GAMEENGINE_PLATFORM_WINDOWS)
#  if !defined (GAMEENGINE_LIBRARY_STATIC)
#    if defined GAMEENGINE_LIBRARY_EXPORTS
#      define GAMEENGINE_API __declspec (dllexport)
#    else
#      define GAMEENGINE_API __declspec (dllimport)
#    endif
#  else
#  define GAMEENGINE_API
#  endif
#endif

#endif // #ifndef GAMEENGINE_CONFIG