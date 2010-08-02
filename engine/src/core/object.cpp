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
#include "hummstrummengine.hpp"

#include <cstdlib>
#include <memory>
#include <new>

#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
#include <utmpx.h>
#endif

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  pragma warning(disable: 4355)
#  ifdef HUMMSTRUMM_ARCHITECTURE_64
extern "C" int __cdecl GetCurrentProcessor_asmforwin64_ (void);
#  endif // #ifdef HUMMSTRUMM_ARCHITECTURE_64
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS

    // Thanks to Jeremy Jones for this code for Windows.
    // <https://www.cs.tcd.ie/Jeremy.Jones/GetCurrentProcessorNumberXP.htm>
const unsigned int
GetCurrentProcessor_hidden_ (void)
  throw ()
{
#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#ifdef HUMMSTRUMM_ARCHITECTURE_32
  __asm { mov eax, 1 }
  __asm { cpuid }
  __asm { shr ebx, 24 }
  __asm { mov eax, ebx }
#else // #ifdef HUMMSTRUMM_ARCHITECTURE_32
  return GetCurrentProcessor_asmforwin64_ ();
#endif // #ifdef HUMMSTRUMM_ARCHITECTURE_32
#else // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS
  return sched_getcpu ();
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS
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
  : referenceCount (!MasterHeap::GetMasterHeap ().IsHeapMemory
      (reinterpret_cast<char *> (this)))
{}


Object::~Object (void)
{}


bool
Object::IsHeapMemory (void)
  const throw ()
{
  return MasterHeap::GetMasterHeap ().IsHeapMemory (reinterpret_cast<char *>
    (const_cast<Object *> (this)));
}


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
  ++this->referenceCount;
}


void
Object::DropReference (void) const throw ()
{
  if (this->referenceCount <= 1)
    {
      delete this;
    }
  else
    {
      --this->referenceCount;
    }
}

}
}
}


void *
operator new (std::size_t objectSize)
{
  char *memory = 0;
  
  hummstrumm::engine::core::MasterHeap::GetMasterHeap ().GetHeap
    (GetCurrentProcessor_hidden_ ())->Allocate (&memory, objectSize);
  
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
      hummstrumm::engine::core::MasterHeap::GetMasterHeap ().GetHeap
        (GetCurrentProcessor_hidden_ ())->Allocate (&memory, objectSize);
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
  
  hummstrumm::engine::core::MasterHeap::GetMasterHeap ().GetHeap
    (GetCurrentProcessor_hidden_ ())->Allocate (&memory, objectsSize);
  
  return memory;
}


void *
operator new[] (std::size_t objectsSize,
                std::nothrow_t dontThrowException)
  throw ()
{
  char *memory = 0;
  
  try
    {
      hummstrumm::engine::core::MasterHeap::GetMasterHeap ().GetHeap
        (GetCurrentProcessor_hidden_ ())->Allocate (&memory, objectsSize);
    }
  catch (...)
    {
      return 0;
    }
  
  return memory;
}


void
operator delete (void *object)
  throw ()
{
  hummstrumm::engine::core::MasterHeap::Heap::FreeHelper
    (reinterpret_cast<char **> (&object));
}


void
operator delete[] (void *objects)
  throw ()
{
  hummstrumm::engine::core::MasterHeap::Heap::FreeHelper
    (reinterpret_cast<char **> (&objects));
}
