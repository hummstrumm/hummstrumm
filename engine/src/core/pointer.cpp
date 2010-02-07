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

#include <config.h>
#include <core/type.hpp>
#include <core/object.hpp>
#include <core/pointer.hpp>

template <typename T>
hummstrumm::engine::core::Type hummstrumm::engine::core::Pointer<T>::_type_
  ("hummstrumm::engine::core::Pointer<T>",
   sizeof (hummstrumm::engine::core::Pointer<T>),
   hummstrumm::engine::core::Object::GetType (), 0);

template <typename T>
hummstrumm::engine::core::Type *
hummstrumm::engine::core::Pointer<T>::GetType (void) throw ()
{
  return &_type_;
}

namespace hummstrumm
{
namespace engine
{
namespace core
{


template <typename T>
Pointer<T>::Pointer (void)
  : pointer_ (0),
    Object ()
{}


template <typename T>
Pointer<T>::Pointer (T *object)
  : pointer_ (object),
    Object ()
{
  pointer_->AddReference ();
}


template <typename T>
Pointer<T>::~Pointer (void)
{
  if (pointer_ != 0)
    {
      pointer_->DropReference ();
    }
}


template <typename T>
T *
Pointer<T>::GetObjectPointer (void) const throw ()
{
  return pointer_;
}


template <typename T>
T *
Pointer<T>::operator-> (void) const throw ()
{
  return GetObjectPointer ();
}


template <typename T>
T &
Pointer<T>::GetObject (void) const
{
  if (!IsValid ())
    {
      throw 1;  // TODO: Change once Exception class is added.
    }
  else
    {
      return *pointer_;
    }
}


template <typename T>
T &
Pointer<T>::operator* (void) const
{
  return GetObject ();
}


template <typename T>
bool
Pointer<T>::IsValid (void) const throw ()
{
  return (pointer_ != 0);
}


template <typename T>
template <typename NewType>
Pointer<T>::operator Pointer<NewType> (void) const throw ()
{
  return Pointer<NewType>(pointer_);
}


template <typename T>
const Pointer<T> &
Pointer<T>::operator= (const Pointer<T> &pointer) throw ()
{
  Set (pointer);
  
  // For = chaining.
  return *this;
}


template <typename T>
void
Pointer<T>::Set (const Pointer<T> pointer) throw ()
{
  // If I'm pointing to something already, the the Object I am pointing to that
  // it has lost a reference.
  if (IsValid ())
    {
      pointer_->DropReference ();
    }
  
  // Set my pointer.
  pointer_ = pointer->GetPointer ();
  
  // Tell the Object I now point to that it has gotten another reference.
  pointer_->AddReference ();
}

    
template <typename T>
bool
Pointer<T>::operator== (const Pointer<T> &pointer) const throw ()
{
  return IsEqualTo (pointer);
}


template <typename T>
bool
Pointer<T>::IsEqualTo (const Pointer<T> &pointer) const throw ()
{
  return (pointer_ == pointer->GetPointer ());
}


}
}
}
