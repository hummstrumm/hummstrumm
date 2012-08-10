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
 * Some macros to take advantage of optimizations that
 * compilers/platforms can give us.
 * 
 * @file   util/optimizations.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-08-10
 */

#ifndef HUMMSTRUMM_ENGINE_UTIL_OPTIMAZATIONS
#define HUMMSTRUMM_ENGINE_UTIL_OPTIMIZATIONS

#if __GNUC__
#  define HUMMSTRUMM_ENGINE_LIKELY(cond)   __builtin_expect (cond, true)
#  define HUMMSTRUMM_ENGINE_UNLIKELY(cond) __builtin_expect (cond, false)
#else
#  define HUMMSTRUMM_ENGINE_LIKELY(cond)
#  define HUMMSTRUMM_ENGINE_UNLIKELY(cond)
#endif

#if __GNUC__
#  define HUMMSTRUMM_ENGINE_PREFETCH(address) __builtin_prefetch (address)
#elif defined (HUMMSTRUMM_ENGINE_HAVE_SSE_SUPPORT)
#  define HUMMSTRUMM_ENGINE_PREFETCH(address)	\
     __mm_prefetch (address, _MM_HINT_NTA)
#else
#  define HUMMSTRUMM_ENGINE_PREFETCH(address)
#endif

#endif // #ifndef HUMMSTRUMM_ENGINE_UTIL_OPTIMIZATIONS
