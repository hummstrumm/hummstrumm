// -*- mode: c++; c-file-style: hummstrumm -*-
/* Humm and Strumm Video Game
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

#include "hummstrummengine.hpp"

#include <cstdlib>
#include <memory>
#include <new>

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  pragma warning(disable: 4355)
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS

namespace hummstrumm
{
namespace engine
{
namespace core
{

Type
Object::type_HIDDEN_
  ("hummstrumm::engine::core::Object",
   sizeof (Object),
   0,
   Object::CreateNew);


AllocationTable
Object::allocations;


Object::Object (void)
  : referenceCount (!allocations.CheckAndRemove
                      (reinterpret_cast<void *> (this)))
{}


Object::~Object (void)
{}


unsigned int
Object::GetReferenceCount (void)
  const throw ()
{
  return this->referenceCount;
}


const Type *
Object::GetType (void)
  throw ()
{
  return &type_HIDDEN_;
}


Object::Ptr
Object::CreateNew (void)
  throw ()
{
  return new Object ();
}


Object::ConstPtr
Object::GetPointer (void)
  const throw ()
{
  return this;
}


Object::ConstPtr
Object::operator& (void)
  const throw ()
{
  return this;
}


Object::Ptr
Object::GetPointer (void)
  throw ()
{
  return this;
}


Object::Ptr
Object::operator& (void)
  throw ()
{
  return this;
}


void
Object::AddReference (void)
  const throw ()
{
  ++(this->referenceCount);
}


void
Object::DropReference (void) const throw ()
{
  --(this->referenceCount);
}


void *
Object::operator new (std::size_t size)
  throw (/*...*/)
{
  void *pointer = malloc (size);
  if (!pointer)
    {
      // throw
    }

  allocations.Allocate (pointer);

  return pointer;
}


void *
Object::operator new (std::size_t size, std::nothrow_t /* nt */)
  throw ()
{
  void *pointer = malloc (size);
  if (pointer)
    {
      allocations.Allocate (pointer);
    }

  return pointer;
}


void
Object::operator delete (void *p)
  throw ()
{
  free (p);
}


void *
Object::operator new[] (std::size_t size)
  throw (/*...*/)
{
  void *pointer = malloc (size);
  if (!pointer)
    {
      // throw
    }
    
  // We DON'T WANT THIS line here.  All elements that are on an arry shouldn't be put
  // in our allocation table.
  // TODO: Document why and point to there from here.
  // allocations.Allocate (pointer);

  return pointer;
}


void *
Object::operator new[] (std::size_t size, std::nothrow_t /* nt */)
  throw ()
{
  void *pointer = malloc (size);
  if (pointer)
    {
      // We DON'T WANT THIS line here.  All elements that are on an arry shouldn't be put
      // in our allocation table.
      // TODO: Document why and point to there from here.
      // allocations.Allocate (pointer);
    }

  return pointer;
}


void
Object::operator delete[] (void *p)
  throw ()
{
  free (p);
}


}
}
}
