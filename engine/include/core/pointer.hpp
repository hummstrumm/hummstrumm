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

/**
 * Defines and implements the Pointer class.
 *
 * @file   core/pointer.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-01-03
 * @see    Pointer
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
 * @version 0.3
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2009-07-20
 * @since 0.1
 *
 * @note This class does not entirely implement the Object-Type System, to
 * avoid infinite recursion with templates.  You cannot get a Pointer to this
 * pointer or create a new Pointer object dynamically from a Type.
 * 
 * @todo Make thread safe?
 */
template <typename T>
class Pointer : public Object
{
  private:
    static Type type_HIDDEN_;
  public:
    static inline Type *GetType (void) throw ();
  
  public:
    /// The type of object this Pointer can point to.
    typedef T DataType;
    /// The type returned by dereferencing the Pointer.
    typedef T& DereferenceType; // T&, not T&, for legibility
    /// The type of pointer this Pointer is equivalent to.
    typedef T* PointerType;     // T*, not T *, for legibility
    /**
     * Constructs a null Pointer object.  This Pointer does not point to any
     * Object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     */
    Pointer<DataType> (void);
    /**
     * Constructs a Pointer object that references an Object.  This Object must
     * exist.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     *
     * @param [in, out] object The Object to point to.  Its reference count is
     * changed.
     */
    Pointer<DataType> (PointerType object);
    /**
     * Constructs a Pointer object that clones another Pointer.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-11-27
     * @since 0.3
     *
     * @param [in] pointer A Pointer to copy.
     */
    Pointer<DataType> (const Pointer<T> &pointer);
    /**
     * Destructs a Pointer object.  If the Pointer is valid, it will decrease
     * the reference count of its Object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     */
    virtual ~Pointer<DataType> (void);
    
    /**
     * Returns a raw pointer to the Pointer object's Object, or a null pointer
     * if the Pointer is null.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     *
     * @return The raw pointer of the Pointer.
     */
    inline PointerType GetObjectPointer (void) const throw ();
    /**
     * Returns a raw pointer to the Pointer object's Object, or a null pointer
     * if the Pointer is null.  This allows the user to access the members of
     * the Pointer object's Object as if it were a raw pointer.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     *
     * @return The raw pointer of the Pointer.
     */
    inline PointerType operator-> (void) const throw ();
    
    /**
     * Returns a refence to the Pointer object's Object.  If the pointer is not
     * valid, an exception will be thrown.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     *
     * @return A reference to the Pointer object's Object.
     *
     * @todo Throw exception.
     */
    inline DereferenceType GetObject (void) const;
    /**
     * Returns a refence to the Pointer object's Object.  This allows the user
     * to dereference the Pointer as if it were a raw pointer.  If the pointer
     * is not valid, an exception will be thrown.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     *
     * @return A reference to the Pointer object's Object.
     *
     * @todo Throw exception.
     */
    inline DereferenceType operator* (void) const;
    
    /**
     * Returns whether the Pointer object is valid (that is, whether it is not a
     * null pointer).
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     */
    inline bool IsValid (void) const throw ();
    
    /**
     * Converts the Pointer of a certain type to another type in a valid
     * conversion.  The new type and the old type must be compatible; you
     * you cannot cast a StringPtr to a FloatPtr, for instance.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     */
    template <typename NewType>
    operator Pointer<NewType> (void) const throw ();

    /**
     * Changes the Pointer object's Object to that of another Pointer object.
     * If the current Pointer is valid, the current Object will be
     * dereferenced, and the new Object will be referenced.  If the current
     * Pointer is not valid, the new Object will just be referenced.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     *
     * @param [in, out] pointer The new Pointer which references the Object you
     *  want to reference.
     *
     * @return The new Pointer (useful in chaining = statements)
     */
    const Pointer<DataType> &operator= (const Pointer<DataType> &pointer)
      throw ();
    /**
     * @overload
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-11-27
     * @since 0.3
     *
     * @param [in] pointer The object you want to set this Pointer to.
     */
    const Pointer<DataType> &operator= (const PointerType &pointer)
      throw ();
    /**
     * Changes the Pointer object's Object to that of another Pointer object.
     * If the current Pointer is valid, the current Object will be
     * dereferenced, and the new Object will be referenced.  If the current
     * Pointer is not valid, the new Object will just be referenced.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     *
     * @param [in] pointer The new Pointer which references the Object you
     * want to reference.
     */
    void Set (const Pointer<DataType> pointer) throw ();
    /**
     * @overload
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-11-27
     * @since 0.3
     *
     * @param [in] pointer The new Pointer which references the Object you
     * want to reference.
     */
    void Set (const PointerType pointer) throw ();
    
    /**
     * Checks whether two Pointer objects reference the same Object.  The
     * two Pointer objects must point to the same memory to be the same.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     *
     * @param [in] pointer The Pointer object to compare with.
     *
     * @return Whether the two Pointer objects reference the same Object.
     */
    inline bool operator== (const Pointer<DataType> &pointer) const throw ();
    /**
     * Checks whether two Pointer objects reference the same Object.  The
     * two Pointer objects must point to the same memory to be the same.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-10-11
     * @since 0.1
     *
     * @param [in] pointer The Pointer object to compare with.
     *
     * @return Whether the two Pointer objects reference the same Object.
     */
    inline bool IsEqualTo (const Pointer<DataType> &pointer) const throw ();
    
  private:
    /// The raw pointer to an Object.
    PointerType pointer;
};


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_POINTER
