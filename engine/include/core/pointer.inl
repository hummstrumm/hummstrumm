// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2011, the people listed in the AUTHORS file. 
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

#ifndef HUMMSTRUMM_ENGINE_CORE_POINTER_INL
#define HUMMSTRUMM_ENGINE_CORE_POINTER_INL

namespace hummstrumm
{
namespace engine
{
namespace core
{


template <typename T>
Type
Pointer<T>::type_HIDDEN_
  ("hummstrumm::engine::core::Pointer<T>",
   sizeof (Pointer<T>),
   Object::GetType (), 0);

template <typename T>
Type *
Pointer<T>::GetType (void) throw ()
{
  return &type_HIDDEN_;
}


template <typename T>
Pointer<T>::Pointer (void)
  : pointer (0),
    Object ()
{
}


template <typename T>
Pointer<T>::Pointer (const Pointer<T> &pointer)
  : pointer (pointer.pointer),
    Object ()
{
  this->pointer->AddReference ();
}


template <typename T>
Pointer<T>::Pointer (PointerType object)
  : pointer (object),
    Object ()
{
  this->pointer->AddReference ();
}


template <typename T>
Pointer<T>::~Pointer (void)
{
  if (IsValid ())
    {
      this->pointer->DropReference ();
      if (this->pointer->GetReferenceCount () <= 0)
        {
          delete this->pointer;
        }
    }
}


template <typename T>
T *
Pointer<T>::GetObjectPointer (void) const throw ()
{
  return this->pointer;
}


template <typename T>
T *
Pointer<T>::operator-> (void) const throw ()
{
  HUMMSTRUMM_ASSERT (IsValid ());
  
  return GetObjectPointer ();
}


template <typename T>
T &
Pointer<T>::GetObject (void) const
{
  HUMMSTRUMM_ASSERT (IsValid ());
  
  return *this->pointer;
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
  // If I am not null...
  return (this->pointer != 0);
}


template <typename T>
template <typename NewType>
Pointer<T>::operator Pointer<NewType> (void) const throw ()
{
  return Pointer<NewType>(this->pointer);
}


template <typename T>
const Pointer<T> &
Pointer<T>::operator= (const Pointer<DataType> &pointer) throw ()
{
  Set (pointer);
  
  // For = chaining.
  return *this;
}


template <typename T>
const Pointer<T> &
Pointer<T>::operator= (const PointerType &pointer) throw ()
{
  Set (pointer);
  
  // For = chaining.
  return *this;
}


template <typename T>
void
Pointer<T>::Set (const Pointer<DataType> pointer) throw ()
{
  // If I'm pointing to something already, the the Object I am pointing to that
  // it has lost a reference.
  if (IsValid ())
    {
      this->pointer->DropReference ();
      if (this->pointer->GetReferenceCount () <= 0)
        {
          delete this->pointer;
        }
    }
  
  // Set my pointer.
  this->pointer = pointer.GetObjectPointer ();
  
  // Tell the Object I now point to that it has gotten another reference.
  this->pointer->AddReference ();
}

template <typename T>
void
Pointer<T>::Set (PointerType pointer) throw ()
{
  // If I'm pointing to something already, the the Object I am pointing to that
  // it has lost a reference.
  if (IsValid ())
    {
      this->pointer->DropReference ();
      if (this->pointer->GetReferenceCount () <= 0)
        {
          delete this->pointer;
        }
    }
  
  // Set my pointer.
  this->pointer = pointer;
  
  // Tell the Object I now point to that it has gotten another reference.
  this->pointer->AddReference ();
}

    
template <typename T>
bool
Pointer<T>::operator== (const Pointer<DataType> &pointer) const throw ()
{
  return IsEqualTo (pointer);
}


template <typename T>
bool
Pointer<T>::IsEqualTo (const Pointer<DataType> &pointer) const throw ()
{
  // Do I point to the same memory?
  return (this->pointer == pointer->GetPointer ());
}


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_POINTER_INL
