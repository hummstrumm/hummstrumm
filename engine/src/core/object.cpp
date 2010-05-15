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
#define HUMMSTRUMM_ENGINE_SOURCE

#include <cstdlib>
#include <memory>
#include <new>

#include "hummstrummengine.hpp"

#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
#include <utmpx.h>
#endif

    // Thanks to Jeremy Jones for this code for Windows.
    // <https://www.cs.tcd.ie/Jeremy.Jones/GetCurrentProcessorNumberXP.htm>
const unsigned int
GetCurrentProcessor_hidden_ (void)
  throw ()
{
#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
  _asm { mov eax, 1 }
  _asm { cpuid }
  _asm { shr ebx, 24 }
  _asm { mov eax, ebx }
#else
  return sched_getcpu ();
#endif
}

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


Object::Object (void)
  : referenceCount_ (!MasterHeap::GetMasterHeap ().IsHeapMemory
      (reinterpret_cast<char *> (this)))
{}


Object::~Object (void)
{}


bool
Object::IsHeapMemory (void) const throw ()
{
  return MasterHeap::GetMasterHeap ().IsHeapMemory (reinterpret_cast<char *>
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


void *
operator new (std::size_t objectSize)
{
  char *memory = 0;
  
  hummstrumm::engine::core::MasterHeap::GetMasterHeap ().GetHeap (GetCurrentProcessor_hidden_ ())->
    Allocate (&memory, objectSize);
  
  return memory;
}


void *
operator new (std::size_t objectSize,
                      std::nothrow_t dontThrowException)
  throw ()
{
  char *memory = 0;
  
  try
    {
      hummstrumm::engine::core::MasterHeap::GetMasterHeap ().GetHeap (GetCurrentProcessor_hidden_ ())->
        Allocate (&memory, objectSize);
    }
  catch (...)
    {
      return 0;
    }
  
  return memory;
}


void *
operator new[] (std::size_t objectsSize)
{
  char *memory = 0;
  
  hummstrumm::engine::core::MasterHeap::GetMasterHeap ().GetHeap (GetCurrentProcessor_hidden_ ())->
    Allocate (&memory, objectsSize);
  
  return memory;
}


void *
operator new[] (std::size_t objectsSize,
                        std::nothrow_t dontThrowException) throw ()
{
  char *memory = 0;
  
  try
    {
      hummstrumm::engine::core::MasterHeap::GetMasterHeap ().GetHeap (GetCurrentProcessor_hidden_ ())->
        Allocate (&memory, objectsSize);
    }
  catch (...)
    {
      return 0;
    }
  
  return memory;
}


void
operator delete (void *object) throw ()
{
  hummstrumm::engine::core::Heap::FreeHelper (reinterpret_cast<char **> (&object));
}


void
operator delete[] (void *objects) throw ()
{
  hummstrumm::engine::core::Heap::FreeHelper (reinterpret_cast<char **> (&objects));
}
