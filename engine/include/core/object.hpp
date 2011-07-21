// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2011, the people listed in the AUTHORS file. 
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
 * Defines the Object class.
 *
 * @file   core/object.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-01-03
 * @see    Object
 */

#ifndef HUMMSTRUMM_ENGINE_CORE_OBJECT
#define HUMMSTRUMM_ENGINE_CORE_OBJECT

#include <memory>
#include <new>

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
 * Object provides integration with the Type and Pointer<T> classes.
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
 * When an Object is created dynamically on the heap, it starts with a
 * reference count of zero.  A Pointer<T> would be used to point to the new
 * memory, which would increment the reference count.  When an Object is
 * created on the Stack normally, it starts with a reference count of one.
 * This prevents the reference count from reaching zero, so the Object is never
 * freed.  The same is true of member variables and array elements.
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
 * @version 0.3
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2009-07-20
 * @since   0.1
 *
 * @note This will be reworked when the multithreaded support is done (not for
 * a while).  The API will stay mostly the same if used as specified.
 */
class Object
{
  /// This friendship allows the Pointer<T> to increment and decrement the
  /// reference count of the Object.
  template <typename T>
  friend class Pointer;
  
  public:
    typedef hummstrumm::engine::core::Pointer<Object> Ptr;
    typedef hummstrumm::engine::core::Pointer<const Object> ConstPtr;
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
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     */
    Object (void);
    /**
     * Destructs an Object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     */
    virtual ~Object (void);

    /**
     * Returns the current reference count of the Object.  This will be the
     * number of Pointer<T> objects that point to it, plus one if the Object
     * was allocated on the stack, not the Heap.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @returns The reference count of the Object.
     */
    unsigned int GetReferenceCount (void)
      const throw ();

    /**
     * Returns the Type of the Object.  This Type contains runtime type
     * information for the class.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @returns A pointer to the Type of this Object.
     *
     * @see Type
     */
    static const Type *GetType (void)
      throw ();
    /**
     * Returns a new object of this class.  This method uses the default
     * constructor, so to dynamically create an Object, you need to have one.
     * It's a good idea to always do, but...
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @returns A Pointer<Object> to a new Object.
     *
     * @warning You will have to have a default constructor for this method to
     * work.
     *
     * @see Type
     *
     * @todo Throw an exception if the memory allocation fails.
     */
    static Ptr CreateNew (void)
      throw ();
    /**
     * Returns a Pointer<const Object> to this Object.  There are two versions
     * of this method: one const and one not.  This is the const version, which
     * returns a Pointer<const Object> to this Object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @returns A Pointer<const Object> to this Object.
     *
     * @see operator&
     */
    ConstPtr GetPointer (void)
      const throw ();
    /**
     * Returns a Pointer<const Object> to this Object.  There are two versions
     * of this method: one const and one not.  This is the const version, which
     * returns a Pointer<const Object> to this Object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @returns A Pointer<const Object> to this Object.
     *
     * @warning This is the overloaded & (address) operator.  This means you
     * will not be able to get the exact address using this operator. Instead,
     * you can get the raw pointer from the Pointer<T> wrapper via its
     * Pointer<T>::GetPointer method.
     *
     * @see GetPointer
     */
     ConstPtr operator& (void)
       const throw ();
    /**
     * Returns a Pointer<Object> to this Object.  There are two versions of
     * this method: one const and one not.  This it the non-const version,
     * which returns a Pointer<Object> to this Object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @returns A Pointer<Object> to this Object.
     *
     * @see operator&
     */
    Ptr GetPointer (void)
      throw ();
    /**
     * Returns a Pointer<Object> to this Object.  There are two versions of
     * this method: one const and one not.  This is the non-const version,
     * which returns a Pointer<Object> to this Object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @returns A Pointer<Object> to this Object.
     *
     * @warning This is the overloaded & (address) operator.  This means you
     * will not be able to get the exact address using this operator.  Instead,
     * you can get the raw pointer from the Pointer<T> wrapper via its
     * Pointer<T>::GetPointer method.
     *
     * @see GetPointer
     */
    Ptr operator& (void)
      throw ();

    /**
     * Returns the memory for an Object and adds it to the AllocationTable.
     *
     * @author Patrick M. Niedzielski <PatickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param [in] size The size of the block to allocate.
     * 
     * @return A block of memory in which an Object can fit.
     */
    void *operator new (std::size_t size)
      throw (/*...*/);
    /**
     * @overload
     *
     * Won't throw an exception on failure.
     *
     * @author Patrick M. Niedzielski <PatickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     */
    void *operator new (std::size_t size, std::nothrow_t)
      throw ();
    /**
     * Deletes an Object from the heap.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param [in,out] p The Object to delete.
     */
    void operator delete (void *p)
      throw ();
    /**
     * Returns the memory for an array of Objects and adds it to the
     * AllocationTable.
     *
     * @author Patrick M. Niedzielski <PatickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param [in] size The size of the block to allocate.
     * 
     * @return A block of memory in which an array of Objects can fit.
     */
    void *operator new[] (std::size_t size)
      throw (/*...*/);
    /**
     * @overload
     *
     * Won't throw an exception on failure.
     *
     * @author Patrick M. Niedzielski <PatickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     */
    void *operator new[] (std::size_t size, std::nothrow_t)
      throw ();
    /**
     * Deletes an array of Objects from the heap.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param [in,out] p The Object array to delete.
     */
    void operator delete[] (void *p)
      throw ();
    
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
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     */
    void AddReference (void)
      const throw ();
    /**
     * Drops a reference to this Object.  This decrements the reference count
     * of the Object.  Pointer<T> objects automatically decrement the reference
     * count of their Object when they go out of scope or are assigned to a
     * different Object.  When the reference count reachs zero, the Object is
     * deleted, which will not happen if the Object was allocated on the stack.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     */
    void DropReference (void)
      const throw ();
    
    mutable unsigned int referenceCount;  /**< The Object's reference count. */
    static Type type_HIDDEN_;             /**< The Type for this Object.     */
    static AllocationTable allocations;   /**< New allocations.              */
};

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_OBJECT
