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

#ifndef HUMMSTRUMM_ENGINE_GEOMETRY_SEGMENT_INL
#define HUMMSTRUMM_ENGINE_GEOMETRY_SEGMENT_INL

namespace hummstrumm
{
namespace engine
{
namespace geometry
{

template <typename T>
Segment2D<T> &
Segment2D<T>::operator = (const Segment2D<T> &s)
{
  start = s.start;
  end = s.end;
  return *this;
}

template <typename T>
bool
Segment2D<T>::operator == (const Segment2D<T> &s)
{
  return start == s.start && end == s.end;
}

template <typename T>
bool
Segment2D<T>::operator != (const Segment2D<T> &s)
{
  return start != s.start || end != s.end;
}

template <typename T>
Segment3D<T> &
Segment3D<T>::operator = (const Segment3D<T> &s)
{
  start = s.start;
  end = s.end;
  return *this;
}

template <typename T>
bool
Segment3D<T>::operator == (const Segment3D<T> &s)
{
  return start == s.start && end == s.end;
}

template <typename T>
bool
Segment3D<T>::operator != (const Segment3D<T> &s)
{
  return start != s.start || end != s.end;
}

};
};
};

#endif //HUMMSTRUMM_ENGINE_GEOMETRY_SEGMENT_INL
