// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2009, the people listed in the AUTHORS file. 
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

#ifndef HUMMSTRUMM_ENGINE
#error This file has been included independently.  Include it with \
the file "hummstrummengine.hpp".
#endif // #ifndef HUMMSTRUMM_ENGINE

#ifndef HUMMSTRUMM_ENGINE_CORE_OBJECT
#define HUMMSTRUMM_ENGINE_CORE_OBJECT

namespace hummstrumm::engine::core
{
  class Object
  {
    DECLARE_TYPE
    public:
      Object (void);
      virtual ~Object (void);
  
      bool IsHeapMemory (void) const throw ();
  
      void AddReference (void) const throw ();
      void DropReference (void) const throw ();
      unsigned int GetReferenceCount (void) const throw ();
  
      void *operator new (size_t objectSize) const throw (...);
      void *operator new (size_t objectSize, nothrow_t dontThrowException) const throw ();
      void *operator new[] (size_t objectsSize) const throw (...);
      void *operator new[] (size_t objectsSize, nothrow_t dontThrowException) const throw ();
      void operator delete (void *object) const throw ();
      void operator delete[] (void *objects) const throw ();
  
      Pointer<const Object> &GetPointer (void) const throw ();
      Pointer<const Object> &operator&  (void) const throw ();
      Pointer<Object> &GetPointer (void) throw ();
      Pointer<Object> &operator&  (void) throw ();
  
      template <typename T>
      void Serialize (const StreamOut<T> &streamOut) const throw ();
      template <typename T>
      void Serialize (const StreamIn<T> &streamIn) throw ();
  
    private:
      static Heap heap_;
      unsigned int referenceCount_;
  };
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_OBJECT