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
 * Defines the Type class and macros with which to implement and use typed
 * objects.
 * 
 * @file   core/type.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-01-03
 * @see    Type
 */

#ifndef HUMMSTRUMM_ENGINE_CORE_TYPE
#define HUMMSTRUMM_ENGINE_CORE_TYPE


namespace hummstrumm
{
namespace engine
{
namespace core
{

template <typename T>
class Pointer;
class Object;

/**
 * Specifies type attributes for a class.  A Type object contains
 * information about the class it represents.  The exact name is stored in
 * the Type object, as well as its size in C++ bytes.
 *
 * All objects in the Object/Type system of the game engine have a Type
 * object, which is created through a combination of the
 * HUMMSTRUMM_DECLARE_TYPE and HUMMSTRUMM_IMPLEMENT_TYPE macros.
 *
 * To obtain the Type of a certain Object or class, you can use the
 * Object::GetType method, which will return a pointer to the Type member of
 * the class.
 *
 * The Type class stores the hierarchy of the current type.  Only single
 * inheritance is supported by the Object/Type system.  You can access the
 * parent class, and check whether another type appears in the hierarchy with
 * a certain relationship to the current Type.
 *
 * Type objects also store a pointer to a static creation function in their
 * Object, which calls the default constructor of the Object.  <b>This
 * functionality only works if there is a default constructor of the Object!
 * </b>  You can call the Create method to return a new Object of the Type.
 * This is equivalent to calling the Object::CreateNew method.
 *
 * You can also access certain attributes in the Type, such as the name of
 * the class (which includes the full namespace hierarchy) and the size, in
 * bytes, of the Object.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2009-09-02
 * @since 0.1
 *
 * @see Object
 * @see HUMMSTRUMM_DECLARE_TYPE
 * @see HUMMSTRUMM_IMPLEMENT_TYPE
 */
class Type
{
  public:
    /**
     * Constructs a Type object for a certain Object.  The Object's name,
     * size in bytes, parent Type, and creation function are stored by the
     * Type.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @param name [in] The name of the Object, including the namespaces it is
     * under.
     * @param size [in] The size, in bytes, of the Object.
     * @param parent [in] The Object's parent class's Type.  This is only a
     * null pointer at the root of the hierarchy.
     * @param createFunction [in] The Object's static create function, which
     * should return a Pointer<Object> to the newly-created Object.
     *
     * @warning Do not create your own Type.  If you are using the engine's
     * Object/Type system, this will be done for you.
     */
    Type (const hummstrumm::engine::types::String &name,
          std::size_t size,
          const Type *parent,
          Object::Ptr (*createFunction) (void));
    /**
     * Destructs a Type object for a certain Object.  Since all Type objects
     * in the Object/Type system are static members of an Object, this
     * destructor will be called at program termination.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     */
    virtual ~Type (void);
    
    /**
     * Returns the name of the Object, including a full namespace hierarchy.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @return The name of the Object, as a String.
     */
    const hummstrumm::engine::types::String GetName (void) const throw ();
    /**
     * Returns the size of the Object, in C++ bytes.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @return The size of the Object, in C++ bytes.
     */
    std::size_t GetSize (void) const throw ();
    /**
     * Returns the parent Type of the Object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @return A pointer to the parent Type of this Object.
     */
    const Type *GetParent (void) const throw ();
    
    /**
     * Returns whether this Object is the root of the hierarchy.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @return Whether this Object is the root of the hierarchy.
     */
    bool IsRoot (void) const throw ();
    /**
     * Returns whether this Object is the direct parent of another Type.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @param type [in] A Type to test for inheritance.
     *
     * @return Whether this Object is a direct parent of type.
     */
     bool IsParentClassOf (const Type *type) const throw ();
    /**
     * Returns whether this Object is a direct child of another Type.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @param type [in] A Type to test for inheritance.
     *
     * @return Whether this Object is a direct child of type.
     */
    bool IsChildClassOf (const Type *type) const throw ();
    /**
     * Returns whether this Object is a descendant of another Type.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @param type [in] A Type to test for inheritance.
     *
     * @return Whether this Object is a descendant of type.
     */
    bool IsDerivedFrom (const Type *type) const throw ();
    /**
     * Returns whether this Object is an ancestor of another Type.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @param type [in] A Type to test for inheritance.
     *
     * @return Whether this Object is an ancestor of type.
     */
    bool IsBaseOf (const Type *type) const throw ();
    
    /**
     * Returns whether this Type is the same as another Type.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @param type [in] A Type to test for equality.
     *
     * @return Whether this Type is equal to type.
     *
     * @warning This does not check the creation function for each type.
     *
     * @see operator==(const Type *type)
     */
    bool IsEqualTo (const Type &type) const throw ();
    /**
     * Returns whether this Type has the same name as a String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @param name [in] A String to test for equality.
     *
     * @return Whether this Type is equal to name.
     *
     * @warning This does not check the creation function for each type.
     *
     * @see operator==(const hummstrumm::engine::types::String &)
     */
    bool IsEqualTo (const hummstrumm::engine::types::String &name) const
      throw ();
    /**
     * Returns whether this Type is the same as another Type.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @param type [in] A Type to test for equality.
     *
     * @return Whether this Type is equal to type.
     *
     * @warning This does not check the creation function for each type.
     *
     * @see IsEqualTo(const Type *type)
     */
    bool operator== (const Type &type) const throw ();
    /**
     * Returns whether this Type has the same name as a String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @param name [in] A String to test for equality.
     *
     * @return Whether this Type is equal to name.
     *
     * @warning This does not check the creation function for each type.
     *
     * @see IsEqualTo(const hummstrumm::engine::types::String &)
     */
    bool operator== (const hummstrumm::engine::types::String name) const
      throw ();
    
    /**
     * Creates a new Object of this Type using the default constructor.  A
     * Pointer<Object> to this new Object will be returned.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-09-02
     * @since 0.1
     *
     * @return A Pointer<Object> to a new Object of this Type.
     *
     * @warning This functionality will only be available if the Object has a
     * default constructor.
     *
     * @see Object::CreateNew
     */
    Object::Ptr Create (void)
      const throw ();
  
  private:
    // Hide
    Type (Type &);
    void operator= (Type &);
    Type (void);
    
    char *name;          /**< The name of the Object, including namespaces. */
    std::size_t size;    /**< The size, in bytes, of the Object. */
    const Type *parent;  /**< The parent Type of the Object. */
    /// The static creation function of the Object, which returns a
    /// Pointer<Object> to a new object.
    Object::Ptr (*createFunction) (void);
};

}
}
}

/**
 * Adds support for the engine's Object/Type system to an Object.  Place this
 * macro at the top of the class declaraction.
 *
 * This macro adds a Type object, a method to return a pointer to this Type,
 * several methods that return a Pointer<className> (with const versions),
 * overloaded & (address) operators that give a Pointer<className> (with const
 * versions), and a method to create a new Object.  It also gives typedefs for
 * easy use with Pointer<className>.
 *
 * If you use this macro, you will also have to use the
 * HUMMSTRUMM_IMPLEMENT_TYPE macro, which adds the definitions of these
 * members.
 *
 * This macro takes one argument, which is the name of the class.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2009-09-02
 * @since 0.1
 *
 * @param className [in] The name of the class.
 *
 * @see Object
 * @see Object::GetType
 * @see Object::CreateNew
 * @see Type
 * @see HUMMSTRUMM_IMPLEMENT_TYPE
 */
#define HUMMSTRUMM_DECLARE_TYPE(className) \
  private: \
    static hummstrumm::engine::core::Type type_HIDDEN_; \
  public: \
    typedef hummstrumm::engine::core::Pointer<className> Ptr; \
    typedef hummstrumm::engine::core::Pointer<const className> ConstPtr; \
    static hummstrumm::engine::core::Type *GetType (void) \
      throw (); \
    static hummstrumm::engine::core::Object::Ptr CreateNew (void); \
    ConstPtr GetPointer (void) \
      const throw (); \
    ConstPtr operator&  (void) \
      const throw (); \
    Ptr      GetPointer (void) \
      throw (); \
    Ptr      operator&  (void) \
      throw ();

/**
 * Adds support for the engine's Object/Type system to an Object.  Place this
 * macro at the top of the class's source file.
 *
 * This macro implements the members added by the HUMMSTRUMM_DECLARE_TYPE
 * macro.  You must supply the full class name (including the namespaces) and
 * the full parent class name (including the namespaces).
 *
 * If you use this macro, you will also have to use the HUMMSTRUMM_DECLARE_TYPE
 * macro, which adds the definitions of these members.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2009-09-02
 * @since 0.1
 *
 * @param className [in] The full name of the class, including namespaces.
 * @param parentName [in] The full name of the parent class, including
 *                        namespaces.
 *
 * @see Object
 * @see Object::GetType
 * @see Object::CreateNew
 * @see Type
 * @see HUMMSTRUMM_DECLARE_TYPE
 */
#define HUMMSTRUMM_IMPLEMENT_TYPE(className, parentName) \
  hummstrumm::engine::core::Type className::type_HIDDEN_ (#className, \
    sizeof (className), parentName::GetType (), className::CreateNew); \
   \
  hummstrumm::engine::core::Type * \
  className::GetType (void) \
    throw () \
  { \
    return &type_HIDDEN_; \
  } \
   \
  hummstrumm::engine::core::Object::Ptr \
  className::CreateNew (void) \
  { \
    return new className; \
  } \
   \
  className::ConstPtr \
  className::GetPointer (void) \
    const throw () \
  { \
    return className::ConstPtr (this); \
  } \
  className::ConstPtr \
  className::operator& (void) \
    const throw () \
  { \
    return className::ConstPtr (this); \
  } \
  className::Ptr \
  className::GetPointer (void) \
    throw () \
  { \
    return className::Ptr (this); \
  } \
  className::Ptr \
  className::operator& (void) \
    throw () \
  { \
    return className::Ptr (this); \
  }

/**
 * Adds support for the engine's Object/Type system to an Object.  Place this
 * macro at the top of the class's source file.
 *
 * This macro implements the members added by the HUMMSTRUMM_DECLARE_TYPE
 * macro.  You must supply the full class name (including the namespaces) and
 * the full parent class name (including the namespaces), and a template
 * definition.
 *
 * If you use this macro, you will also have to use the HUMMSTRUMM_DECLARE_TYPE
 * macro, which adds the definitions of these members.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2009-09-02
 * @since 0.1
 *
 * @param templateDefinition [in] The template definition to prefix definitions
 *                                of the class members.
 * @param className [in] The full name of the class, including namespaces.
 * @param parentName [in] The full name of the parent class, including
 *                        namespaces.
 *
 * @see Object
 * @see Object::GetType
 * @see Object::CreateNew
 * @see Type
 * @see HUMMSTRUMM_DECLARE_TYPE
 */
#define HUMMSTRUMM_IMPLEMENT_GENERIC_TYPE(templateDefinition, className, parentName) \
  templateDefinition \
  hummstrumm::engine::core::Type className::type_HIDDEN_ (#className, \
    sizeof (className), parentName::GetType (), className::CreateNew); \
   \
  templateDefinition \
  hummstrumm::engine::core::Type * \
  className::GetType (void) \
    throw () \
  { \
    return &type_HIDDEN_; \
  } \
   \
  templateDefinition \
  hummstrumm::engine::core::Object::Ptr \
  className::CreateNew (void) \
  { \
    return new className; \
  } \
   \
  templateDefinition \
  typename className::ConstPtr \
  className::GetPointer (void) \
    const throw () \
  { \
    return className::Ptr (this); \
  } \
  templateDefinition \
  typename className::ConstPtr \
  className::operator& (void)  \
    const throw () \
  { \
    return className::Ptr (this); \
  } \
  templateDefinition \
  typename className::Ptr \
  className::GetPointer (void) \
    throw () \
  { \
    return className::Ptr (this); \
  } \
  templateDefinition \
  typename className::Ptr \
  className::operator& (void) \
    throw () \
  { \
    return className::Ptr (this); \
  }

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_TYPE
