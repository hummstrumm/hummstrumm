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

#include <cstdlib>
#include <memory>
#include <new>

#include <config.h>
#include <core/type.hpp>
#include <core/pointer.hpp>
#include <core/object.hpp>
#include <core/heap.hpp>

#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
#include <utmpx.h>
#endif 

namespace hummstrumm
{
namespace engine
{
namespace core
{

Type type_HIDDEN_
  ("hummstrumm::engine::core::Object",
   sizeof (Object),
   0,
   Object::CreateNew);


Object::Object (void)
  : referenceCount_ (!masterHeap_HIDDEN_.IsHeapMemory
      (reinterpret_cast<char *> (this)))
{}


Object::~Object (void)
{}


bool
Object::IsHeapMemory (void) const throw ()
{
  return masterHeap_HIDDEN_.IsHeapMemory (reinterpret_cast<char *>
    (const_cast<Object *> (this)));
}


unsigned int
Object::GetReferenceCount (void) const throw ()
{
  return referenceCount_;
}


Type *
Object::GetType (void) throw ()
{
  return &type_HIDDEN_;
}


ObjectPtr
Object::CreateNew (void) throw ()
{
  return new Object ();
}


ConstObjectPtr
Object::GetPointer (void) const throw ()
{
  return this;
}


ConstObjectPtr
Object::operator& (void) const throw ()
{
  return this;
}


ObjectPtr
Object::GetPointer (void) throw ()
{
  return this;
}


ObjectPtr
Object::operator& (void) throw ()
{
  return this;
}


void
Object::AddReference (void) const throw ()
{
  ++referenceCount_;
}


void
Object::DropReference (void) const throw ()
{
  if (referenceCount_ <= 1)
    {
      delete this;
    }
  else
    {
      --referenceCount_;
    }
}


}
}
}
