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
 * \file object.hpp
 *
 * Defines the Object class.
 *
 * \see Object
 */

#ifndef HUMMSTRUMM_ENGINE_CORE_OBJECT
#define HUMMSTRUMM_ENGINE_CORE_OBJECT

namespace hummstrumm
{
namespace engine
{
namespace core
{

/**
 * The base class for all classes in the game engine's Object/Type system.
 * This class provides operations common to all objects in the game engine.
 * Most every class inherits from this; we even provide wrapper classes for the
 * C++ basic types so that they implement the Object/Type system.  We suggest
 * you use these classes instead of C++ types; they only have the extra
 * overhead of virtual functions.
 *
 * Object provides integration with the Type, Heap, and Pointer<T> classes.
 *
 * All classes implementing the Object/Type system provide a Type object that
 * describes the class.  The macros HUMMSTRUMM_DECLARE_TYPE and
 * HUMMSTRUMM_IMPLEMENT_TYPE create this object automatically.  This Type can
 * be obtained using the Object::GetType method.
 *
 * An Object can dynamically create themselves with the Object::CreateNew
 * method.  Each Object's Type can also create a new Object using the
 * Type::Create method.
 *
 * Any allocation of the Object will occur on the Heap, using overloaded new,
 * new[], delete, and delete[] operators.  The user can find out whether an
 * Object is on the Heap using its Object::IsHeapMemory method.
 *
 * Object also overloads the & (address) operator to return a Pointer<T> to the
 * Object.  You can also access this through the Object::GetPointer method.  By
 * overloading the address operator, you will not be able to directly get the
 * address of the Object.  You can, however, get the raw pointer from a
 * Pointer<T> using the Pointer<T>::GetPointer method.
 *
 * Object objects provide a reference count, which is used to keep track of
 * what is using the Object.  Pointer<T> objects will change the reference
 * count of the object when they go in and out of scope.  When an Object's
 * reference count gets to zero (meaning there is no way to reference it), the
 * Object is freed.
 *
 * When an Object is created dynamically on the Heap, it starts with a
 * reference count of zero.  A Pointer<T> would be used to point to the new
 * memory, which would increment the reference count.  When an Object is
 * created on the Stack normally, it starts with a reference count of one.
 * This prevents the reference count from reaching zero, so the Object is never
 * freed.
 *
 * To make a class implement the Object/Type system, there are several
 * requirements:
 *
 *   1) The class must inherit from Object, directly or indirectly.  This can
 *      be achieved by inheriting from Object directly, or by inheriting from a
 *      class that is a descendent of Object.
 *
 *   2) The class must have the HUMMSTRUMM_DECLARE_TYPE macro in the class
 *      declaration.  This macro takes one argument--the name of the class.
 *      You should put this macro at the top of the class declaration, above
 *      even the access qualifiers.  Always put an access qualifier before the
 *      first member declaration after this macro; do not assume that this
 *      macro will leave the access in the default private access.
 *
 *   3) The class must have the HUMMSTRUMM_IMPLEMENT_TYPE macro in the class
 *      definition source file.  This macro takes three arguments--the template
 *      declaration for the class (this can be blank if the class is not a
 *      template class), the name of the class, including namespaces and
 *      a template qualifier if necissary, and the name of the parent class,
 *      including namespaces and a template qualifier if necissary.
 *
 *   4) The class must provide a default constructor.  This is necissary to
 *      dynamically create the class from its associated Type object.  A
 *      default constructor can contain arguments, but must have default values
 *      for each.
 *
 * A class implementing the Object/Type system will integrate completely with
 * the other classes of the engine.
 *
 * \version 1.0.0.0.
 * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * \date 2009-07-20
 * \since 1.0.0.0
 *
 * \todo Actually implement this class!
 *
 * \note This will be reworked when the multithreaded support is done (not for
 *       a while).  The API will stay mostly the same if used as specified.
 */
class Object
{
  /// This friendship allows the Pointer<T> to increment and decrement the
  /// reference count of the Object.
  template <typename T>
  friend class Pointer<T>;
  
  public:
    /**
     * Constructs a new Object.
     *
     * The Object has a starting reference count, which is either one or zero,
     * depending on whether the Object is on the stack or the Heap.  If the
     * Object is on the stack, it starts with a reference count of one, so
     * it will never reach zero, and thus never be deleted.  If the Object is
     * on the Heap, it starts out with a reference count of zero, until a
     * Pointer<T> points to it.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \todo Implement.
     */
    Object (void);
    /**
     * Destructs an Object.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \todo Implement.
     */
    virtual ~Object (void);

    /**
     * Returns whether the Object is on the Heap, dynamically allocated.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns If the Object is on the Heap.
     *
     * \todo Implement.
     */
    bool IsHeapMemory (void) const throw ();

    /**
     * Returns the current reference count of the Object.  This will be the
     * number of Pointer<T> objects that point to it, plus one if the Object
     * was allocated on the stack, not the Heap.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns The reference count of the Object.
     *
     * \todo Implement.
     */
    unsigned int GetReferenceCount (void) const throw ();

    /**
     * Allocates a new Object on the Heap.  This is the version which throws
     * an exception.
     *
     * Internally, this method calls Heap::Allocate.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param objectSize [in] The size of the memory to allocate on the Heap
     *                        (which may be different than the size of the
     *                        Object due to padding).
     *
     * \returns A pointer to the new memory for the Object.
     *
     * \todo Implement.
     * \todo Throw exception after failed allocation.
     */
    void *operator new (size_t objectSize) const throw (...);
    /**
     * Allocates a new Object on the Heap.  This is the version which does not
     * throw an exception.
     *
     * Internally, this method calls Heap::Allocate.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param objectSize [in] The size of the memory to allocate on the Heap
     *                        (which may be different than the size of the
     *                        Object due to padding).
     *
     * \param dontThrowException [in] The flag that differentiates the nothrow
     *                                version of new from the throwing version.
     *
     * \returns A pointer to the new memory for the Object, or a null pointer
     *          if the memory could not be allocated.
     *
     * \todo Implement.
     */
    void *operator new (size_t objectSize, nothrow_t dontThrowException)
      const throw ();
    /**
     * Allocates a new Object array on the Heap.  This is the version which
     * throws an exception.
     *
     * Internally, this method calls Heap::Allocate.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param objectsSize [in] The size of the memory to allocate on the Heap
     *                         (which may be different than the size of the
     *                         Object objects due to padding).
     *
     * \returns A pointer to the new memory for the Object objects.
     *
     * \todo Implement.
     * \todo Throw exception after failed allocation.
     */
    void *operator new[] (size_t objectsSize) const throw (...);
    /**
     * Allocates a new Object array on the Heap.  This is the version which
     * does not throw an exception.
     *
     * Internally, this method calls Heap::Allocate.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param objectsSize [in] The size of the memory to allocate on the Heap
     *                         (which may be different than the size of the
     *                         Object objects due to padding).
     *
     * \param dontThrowException [in] The flag that differentiates the nothrow
     *                                version of new from the throwing version.
     *
     * \returns A pointer to the new memory for the Objects, or a null pointer
     *          if the memory could not be allocated.
     *
     * \todo Implement.
     */
    void *operator new[] (size_t objectsSize, nothrow_t dontThrowException)
      const throw ();
    /**
     * Unallocates an Object from the Heap.  This function will fail and return
     * if called on an Object that is not on the Heap.
     *
     * Internally, this method calls Heap::Free.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param object [in, out] The Object which will be freed from the Heap.
     *                         This pointer to the Object will no longer be
     *                         valid after this operation.
     *
     * \todo Implement.
     */
    void operator delete (void *object) const throw ();
    /**
     * Unallocates an Object array from the Heap.  This function will fail and
     * return if called on an Object array that is not on the Heap.
     *
     * Internally, this method calls Heap::Free.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param objects [in, out] The Object objectss which will be freed from
     *                          the Heap.  This pointer to the Object objects
     *                          will no longer be valid after this operation.
     *
     * \todo Implement.
     */
    void operator delete[] (void *objects) const throw ();

    /**
     * Returns the Type of the Object.  This Type contains runtime type
     * information for the class.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns A pointer to the Type of this Object.
     *
     * \see Type
     *
     * \todo Implement.
     */
    static hummstrumm::engine::core::Type *GetType (void) throw ();
    /**
     * Returns a new object of this class.  This method uses the default
     * constructor, so to dynamically create an Object, you need to have one.
     * It's a good idea to always do, but...
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns A Pointer<Object> to a new Object.
     *
     * \warning You will have to have a default constructor for this method to
     *          work.
     *
     * \see Type
     *
     * \todo Implement.
     * \todo Throw an exception if the memory allocation fails.
     */
    static hummstrumm::engine::core::Pointer<Object> CreateNew (void)
      throw ();
    /**
     * Returns a Pointer<const Object> to this Object.  There are two versions
     * of this method: one const and one not.  This is the const version, which
     * returns a Pointer<const Object> to this Object.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns A Pointer<const Object> to this Object.
     *
     * \see operator&
     *
     * \todo Implement.
     */
    virtual Pointer<const Object> GetPointer (void) const throw ();
    /**
     * Returns a Pointer<const Object> to this Object.  There are two versions
     * of this method: one const and one not.  This is the const version, which
     * returns a Pointer<const Object> to this Object.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns A Pointer<const Object> to this Object.
     *
     * \warning This is the overloaded & (address) operator.  This means you
     *          will not be able to get the exact address using this operator.
     *          Instead, you can get the raw pointer from the Pointer<T>
     *          wrapper via its Pointer<T>::GetPointer method.
     *
     * \see GetPointer
     *
     * \todo Implement.
     */
    virtual Pointer<const Object> operator& (void) const throw ();
    /**
     * Returns a Pointer<Object> to this Object.  There are two versions of
     * this method: one const and one not.  This it the non-const version,
     * which returns a Pointer<Object> to this Object.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns A Pointer<Object> to this Object.
     *
     * \see operator&
     *
     * \todo Implement.
     */
    virtual Pointer<Object> GetPointer (void) throw ();
    /**
     * Returns a Pointer<Object> to this Object.  There are two versions of
     * this method: one const and one not.  This is the non-const version,
     * which returns a Pointer<Object> to this Object.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns A Pointer<Object> to this Object.
     *
     * \warning This is the overloaded & (address) operator.  This means you
     *          will not be able to get the exact address using this operator.
     *          Instead, you can get the raw pointer from the Pointer<T>
     *          wrapper via its Pointer<T>::GetPointer method.
     *
     * \see GetPointer
     *
     * \todo Implement.
     */
    virtual Pointer<Object> operator& (void) throw ();
    
/*  =AFTER STREAM CLASSES CREATED=
    template <typename T>
    void Serialize (const StreamOut<T> &streamOut) const throw ();
    template <typename T>
    void Serialize (const StreamIn<T> &streamIn) throw ();
*/
 
  private:
    /**
     * Adds a reference to this Object.  This increments the reference count of
     * the Object.  Pointer<T> objects automatically increment the reference
     * count of their Object when they start to point to it.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \todo Implement.
     */
    void AddReference (void) const throw ();
    /**
     * Drops a reference to this Object.  This decrements the reference count
     * of the Object.  Pointer<T> objects automatically decrement the reference
     * count of their Object when they go out of scope or are assigned to a
     * different Object.  When the reference count reachs zero, the Object is
     * deleted, which will not happen if the Object was allocated on the stack.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \todo Implement.
     */
    void DropReference (void) const throw ();
    
    /// The Heap to allocate new Object objects on.
    /// \note Move this in the multithreaded version
    static Heap heap_;
    /// The current reference count of the Object.
    unsigned int referenceCount_;
    /// The Type for this Object.
    static hummstrumm::engine::core::Type _type_;
};

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_OBJECT