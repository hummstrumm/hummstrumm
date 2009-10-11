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

#ifndef HUMMSTRUMM_COMPILECONFIG
#define HUMMSTRUMM_COMPILECONFIG

// Humm and Strumm version
#define HUMMSTRUMM_VERSION Humm and Strumm, version 0.0 (pre-alpha)

// Platforms
/* #undef HUMMSTRUMM_PLATFORM_WIN32 */
/* #undef HUMMSTRUMM_PLATFORM_WIN64 */
/* #undef HUMMSTRUMM_PLATFORM_WINDOWS */
#define HUMMSTRUMM_PLATFORM_GNULINUX

/* #undef HUMMSTRUMM_WINDOWSYSYEM_WINDOWS */
#define HUMMSTRUMM_WINDOWSYSYEM_X11

// Stating heap size
/* #undef HUMMSTRUMM_HEAP_SIZE */

// Size by which to expand the heap each time it expands
/* #undef HUMMSTRUMM_HEAP_EXPAND */

// Method of heap allocation
#define HUMMSTRUMM_HEAP_BESTFIT

// Method of math calculations
#define HUMMSTRUMM_MATH_PRECISE

#endif // #ifndef HUMMSTRUMM_CONFIG
