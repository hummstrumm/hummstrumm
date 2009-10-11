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

/**
 * \file pointer.hpp
 *
 * Defines the Pointer class.
 *
 * \see Pointer
 */

#ifndef HUMMSTRUMM_ENGINE_CORE_POINTER
#define HUMMSTRUMM_ENGINE_CORE_POINTER

namespace hummstrumm
{
namespace engine
{
namespace core
{

/**
 * A reference to an Object object.  This class is essentially a pointer
 * wrapper, integrating the C++ pointer derived type with the Object reference
 * count system.  This effectively eliminates memory leaks in the game engine.
 *
 * Internally, the game engine may use raw pointers if necessary.  Between
 * systems, however, Pointer objects are passed.  Almost all direct user
 * interface methods use Pointer objects as opposed to raw pointers.  We
 * suggest you use these objects, too, in an effort to minimize memory leaks.
 *
 * All memory operations using Pointer objects are checked for validity.
 * Whenever a Pointer object with a null reference is detected, an error is
 * reported.
 *
 * Only use this class with members of the Object/Type system!  This class
 * affects the reference count of its Object, so it requires the interface
 * ensured by the Object/Type system.  Pointer itself implements the
 * Object/Type system, so you can have a Pointer to a Pointer to an Object.
 *
 * \version 1.0.0.0.
 * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * \date 2009-07-20
 * \since 1.0.0.0
 *
 * \todo Actually implement this class!
 * \todo Make thread safe?
 */
template <typename T>
class Pointer<T> : public Object
{
  HUMMSTRUMM_DECLARE_TYPE (Pointer<T>)
  
  public:
    /**
     * Constructs a null Pointer object.  This Pointer does not point to any
     * Object.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \todo Implement
     */
    Pointer<T> (void);
    /**
     * Constructs a Pointer object that references an Object.  This Object must
     * exist.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0     *
     * \param object [in, out] The Object to point to.  Its reference count is
     *                         changed.
     *
     * \todo Implement
     */
    Pointer<T> (const T *object);
    /**
     * Destructs a Pointer object.  If the Pointer is valid, it will decrease
     * the reference count of its Object.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \todo Implement
     */
    ~Pointer<T> (void);
    
    /**
     * Returns a raw pointer to the Pointer object's Object, or a null pointer
     * if the Pointer is null.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \returns The raw pointer of the Pointer.
     *
     * \todo Implement
     */
    const T *GetPointer (void) const throw ();
    /**
     * Returns a raw pointer to the Pointer object's Object, or a null pointer
     * if the Pointer is null.  This allows the user to access the members of
     * the Pointer object's Object as if it were a raw pointer.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \returns The raw pointer of the Pointer.
     *
     * \todo Implement
     */
    const T *operator-> (void) const throw ();
    /**
     * Returns a raw pointer to the Pointer object's Object, or a null pointer
     * if the Pointer is null.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \returns The raw pointer of the Pointer.
     *
     * \todo Implement
     */
    T *GetPointer (void) throw ();
    /**
     * Returns a raw pointer to the Pointer object's Object, or a null pointer
     * if the Pointer is null.  This allows the user to access the members of
     * the Pointer object's Object as if it were a raw pointer.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \returns The raw pointer of the Pointer.
     *
     * \todo Implement
     */
    T *operator-> (void) throw ();
    
    /**
     * Returns a refence to the Pointer object's Object.  If the pointer is not
     * valid, an exception will be thrown.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \returns A reference to the Pointer object's Object.
     *
     * \todo Throw exception.
     * \todo Implement
     */
    const T &GetObject (void) const throw (...);
    /**
     * Returns a refence to the Pointer object's Object.  This allows the user
     * to dereference the Pointer as if it were a raw pointer.  If the pointer
     * is not valid, an exception will be thrown.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \returns A reference to the Pointer object's Object.
     *
     * \todo Throw exception.
     * \todo Implement
     */
    const T &operator* (void) const throw (...);
    /**
     * Returns a refence to the Pointer object's Object.  If the pointer is not
     * valid, an exception will be thrown.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \returns A reference to the Pointer object's Object.
     *
     * \todo Throw exception.
     * \todo Implement
     */
    T &GetObject (void) throw (...);
    /**
     * Returns a refence to the Pointer object's Object.  This allows the user
     * to dereference the Pointer as if it were a raw pointer.  If the pointer
     * is not valid, an exception will be thrown.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \returns A reference to the Pointer object's Object.
     *
     * \todo Throw exception.
     * \todo Implement
     */
    T &operator* (void) throw (...);
    
    /**
     * Returns a refence to the Pointer object's Object.  If the pointer is not
     * valid, and exception will be thrown.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \todo Implement
     */
    bool IsValid (void) const throw ();
    
    /**
     * Converts the Pointer of a certain type to another type in a valid
     * conversion.  The new type and the old type must be compatible; you
     * you cannot cast a StringPointer to a FloatPointer, for instance.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \todo Implement
     */
    template <typename NewType>
    operator Pointer<NewType> (void) const throw ();
    /*{
      return SmartPtr<newType>(pointee);
    }*/

    /**
     * Changes the Pointer object's Object to that of another Pointer object.
     * If the current Pointer is valid, the current Object will be
     * dereferenced, and the new Object will be referenced.  If the current
     * Pointer is not valid, the new Object will just be referenced.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \param pointer [in, out] The new Pointer which references the Object you
     *                          want to reference.
     *
     * \return The new Pointer (useful in chaining = statements)
     *
     * \todo Implement
     */
    const Pointer<T> &operator= (const Pointer<T> &pointer) throw ();
    /**
     * Changes the Pointer object's Object to that of another Pointer object.
     * If the current Pointer is valid, the current Object will be
     * dereferenced, and the new Object will be referenced.  If the current
     * Pointer is not valid, the new Object will just be referenced.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \param pointer [in, out] The new Pointer which references the Object you
     *                          want to reference.
     *
     * \todo Implement
     */
    void Set (const Pointer<T> &pointer) throw ();
    
    /**
     * Checks whether two Pointer objects reference the same Object.  The
     * two Pointer objects must point to the same memory to be the same.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \param pointer [in] The Pointer object to compare with.
     *
     * \return Whether the two Pointer objects reference the same Object.
     *
     * \todo Implement
     */
    bool operator== (const Pointer<T> &pointer) const throw ();
    /**
     * Checks whether two Pointer objects reference the same Object.  The
     * two Pointer objects must point to the same memory to be the same.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-10-11
     * \since 0.0
     *
     * \param pointer [in] The Pointer object to compare with.
     *
     * \return Whether the two Pointer objects reference the same Object.
     *
     * \todo Implement
     */
    bool IsEqualTo (const Pointer<T> &pointer) const throw ();
    
  private:
    /// The raw pointer to an Object.
    T *pointer_;
};

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_POINTER
