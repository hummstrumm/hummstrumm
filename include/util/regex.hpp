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
 * Conditionally includes the proper regex header and sets the correct
 * namespace prefix, depending on how we were configured.
 *
 * @file   util/regex.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-08-10
 */

#ifndef HUMMSTRUMM_ENGINE_UTIL_REGEX
#define HUMMSTRUMM_ENGINE_UTIL_REGEX

#ifdef HUMMSTRUMM_ENGINE_REGEX_USE_BOOST
#  include <boost/regex.hpp>
#  define HUMMSTRUMM_ENGINE_REGEX_NS_PREFIX boost
#else
#  include <regex>
#  define HUMMSTRUMM_ENGINE_REGEX_NS_PREFIX std
#endif

#endif // #ifndef HUMMSTRUMM_ENGINE_UTIL_REGEX
