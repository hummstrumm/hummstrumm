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

#ifndef HUMMSTRUMM_ENGINE_UTIL_TERMCOLORS_INL
#define HUMMSTRUMM_ENGINE_UTIL_TERMCOLORS_INL

namespace hummstrummengine {
namespace util {
namespace termcolors {

namespace detail {

ForegroundImpl::ForegroundImpl(Color c)
  : newColor{c}
{}

BackgroundImpl::BackgroundImpl(Color c)
  : newColor{c}
{}

template <typename CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& out, const ForegroundImpl& c)
{
#ifndef _WIN32
  out << "\033[" << 30 + static_cast<int>(c.newColor) << 'm';
#endif
  return out;
}

template <typename CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& out, const BackgroundImpl& c)
{
#ifndef _WIN32
  out << "\033[" << 40 + static_cast<int>(c.newColor) << 'm';
#endif
  return out;
}

}

detail::ForegroundImpl
foreground(Color c)
{
  return detail::ForegroundImpl{c};
}

detail::BackgroundImpl
background(Color c)
{
  return detail::BackgroundImpl{c};
}

template<typename CharT, class Traits>
std::basic_ostream<CharT, Traits>&
bright(std::basic_ostream<CharT, Traits>& out)
{
#ifndef _WIN32
  out << "\033[1m";
#endif
  return out;
}
    
template<typename CharT, class Traits>
std::basic_ostream<CharT, Traits>&
normal(std::basic_ostream<CharT, Traits>& out)
{
#ifndef _WIN32
  out << "\033[22m";
#endif
  return out;
}

template<typename CharT, class Traits>
std::basic_ostream<CharT, Traits>&
reset(std::basic_ostream<CharT, Traits>& out)
{
#ifndef _WIN32
  out << "\033[0m";
#endif
  return out;
}

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_UTIL_TERMCOLORS_INL
