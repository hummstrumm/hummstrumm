// -*- mode: c++; c-file-style: hummstrumm -*-
/* Humm and Strumm Engine
 * Copyright (C) 2012, 2014, the people listed in the AUTHORS file.
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
 * Provides the ability to output colored text to various streambuffers.
 *
 * @file   util/termcolors.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2014-02-09
 */

#ifndef HUMMSTRUMM_ENGINE_UTIL_TERMCOLORS
#define HUMMSTRUMM_ENGINE_UTIL_TERMCOLORS

#include <ostream>

namespace hummstrummengine {
namespace util {
namespace termcolors {

/**
 * A color for drawing text to the terminal.  Colors come in two variants,
 * normal and bright, which can be set with the termcolors::normal() and
 * termcolors::bright() functions.
 *
 * @version 0.7
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2014-02-09
 * @since   0.7
 *
 * @note The integer values of the enumerations are unspecified, so do not rely
 * on these being any specific values!
 */
enum class Color
{
  reset   = 9,            ///< Reset to the standard color
  black   = 0,            ///< Black (Dark Gray)
  red     = 1,            ///< Red
  green   = 2,            ///< Green
  yellow  = 3,            ///< Yellow
  blue    = 4,            ///< Blue
  magenta = 5,            ///< Magenta
  cyan    = 6,            ///< Cyan
  white   = 7,            ///< White (Pure White)
};

namespace detail {

struct ForegroundImpl
{
  inline explicit ForegroundImpl(Color c);
  Color newColor;
};

template <typename CharT, class Traits = std::char_traits<CharT>>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>&, const ForegroundImpl&);

}

/**
 * Changes the foreground color of the terminal to the specified color when sent
 * to the streambuffers of any of the standard output stream objects defined in
 * `<iostream>`.  The result of applying this manipulator on a stream whose
 * stream buffer does not output to an ANSI terminal is undefined.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2014-02-09
 * @since  0.7
 *
 * @todo Make this work on Windows.  Will probably require a redesign.
 */
inline detail::ForegroundImpl
foreground(Color c);

namespace detail {

struct BackgroundImpl
{
  inline explicit BackgroundImpl(Color c);
  Color newColor;
};

template <typename CharT, class Traits = std::char_traits<CharT>>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>&, const BackgroundImpl&);

}

/**
 * Changes the background color of the terminal to the specified color when sent
 * to the streambuffers of any of the standard output stream objects defined in
 * `<iostream>`.  The result of applying this manipulator on a stream whose
 * stream buffer does not output to an ANSI terminal is undefined.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2014-02-09
 * @since  0.7
 *
 * @todo Make this work on Windows.  Will probably require a redesign.
 */
inline detail::BackgroundImpl
background(Color c);

/**
 * Use the bright variant for foreground and background colors.  The result of
 * applying this manipulator on a stream whose stream buffer does not output to
 * an ANSI terminal is undefined.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2014-02-09
 * @since  0.7
 */
template <typename CharT, class Traits = std::char_traits<CharT>>
inline std::basic_ostream<CharT, Traits>&
bright(std::basic_ostream<CharT, Traits>&);
/**
 * Use the normal variant for foreground and background colors.  The result of
 * applying this manipulator on a stream whose stream buffer does not output to
 * an ANSI terminal is undefined.
 *
 * This is the default variant.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2014-02-09
 * @since  0.7
 */
template <typename CharT, class Traits = std::char_traits<CharT>>
inline std::basic_ostream<CharT, Traits>&
normal(std::basic_ostream<CharT, Traits>&);

/**
 * Reset all traits to default.  The result of applying this manipulator on a
 * stream whose stream buffer does not output to  an ANSI terminal is
 * undefined.
 */
template <typename CharT, class Traits = std::char_traits<CharT>>
inline std::basic_ostream<CharT, Traits>&
reset(std::basic_ostream<CharT, Traits>&);

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_UTIL_TERMCOLORS
