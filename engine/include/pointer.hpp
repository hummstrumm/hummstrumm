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

#ifndef GAMEENGINE_CORE_POINTER
#define GAMEENGINE_CORE_POINTER

namespace gameengine
{
  namespace core
  {
    template <typename T>
    class Pointer : public Object
    {
      DECLARE_TYPE
      public:
        Pointer (void);
        Pointer (const T *object);
        ~Pointer (void);
    
        const T *GetPointer (void) const throw ();
        const T *operator-> (void) const throw ();
        T *GetPointer (void) throw ();
        T *operator-> (void) throw ();
        
        const T &GetObject (void) const throw ();
        const T &operator* (void) const throw ();
        T &GetObject (void) throw ();
        T &operator* (void) throw ();
        
        template <typename NewType>
        operator Pointer<NewType> (void) const throw ();
        /*{
          return SmartPtr<newType>(pointee);
        }*/

        const Pointer<T> &operator= (const Pointer<T> &pointer) throw ();
        void Set (const Pointer<T> &pointer) throw ();
    
        bool operator== (const Pointer<T> &pointer) const throw ();
        bool IsEqualTo (const Pointer<T> &pointer) const throw ();
    
      private:
        const T *GetPointer (void) const throw ();
        T *GetPointer (void) throw ();
    
      private:
        T *pointer_;
    };
    // IMPLEMENT_TYPE (Pointer, Object)
  }
}

#endif // #ifndef GAMEENGINE_CORE_POINTER