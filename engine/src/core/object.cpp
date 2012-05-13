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


Object::Object ()
  : referenceCount (!allocations.CheckAndRemove
                      (reinterpret_cast<void *> (this)))
{}


Object::~Object ()
{}


unsigned int
Object::GetReferenceCount ()
  const /* noexcept */
{
  return this->referenceCount;
}


const Type *
Object::GetType ()
  /* noexcept */
{
  return &type_HIDDEN_;
}


Object::Ptr
Object::CreateNew ()
  /* noexcept */
{
  return new Object ();
}


Object::ConstPtr
Object::GetPointer ()
  const /* noexcept */
{
  return this;
}


Object::ConstPtr
Object::operator& ()
  const /* noexcept */
{
  return this;
}


Object::Ptr
Object::GetPointer ()
  /* noexcept */
{
  return this;
}


Object::Ptr
Object::operator& ()
  /* noexcept */
{
  return this;
}


void
Object::AddReference ()
  const /* noexcept */
{
  ++(this->referenceCount);
}


void
Object::DropReference () const /* noexcept */
{
  --(this->referenceCount);
}


void *
Object::operator new (std::size_t size)
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
  /* noexcept */
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
  /* noexcept */
{
  free (p);
}


void *
Object::operator new[] (std::size_t size)
{
  void *pointer = malloc (size);
  if (!pointer)
    {
      // throw
    }
    
  // We DON'T WANT THIS line here.  All elements that are on an array shouldn't
  // be put in our allocation table.
  // TODO: Document why and point to there from here.
  // allocations.Allocate (pointer);

  return pointer;
}


void *
Object::operator new[] (std::size_t size, std::nothrow_t /* nt */)
  /* noexcept */
{
  void *pointer = malloc (size);
  if (pointer)
    {
      // We DON'T WANT THIS line here.  All elements that are on an array
      // shouldn't be put in our allocation table.
      // TODO: Document why and point to there from here.
      // allocations.Allocate (pointer);
    }

  return pointer;
}


void
Object::operator delete[] (void *p)
  /* noexcept */
{
  free (p);
}


}
}
}
