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
 * \file type.hpp
 *
 * Defines the Type class and macros with which to implement and use typed
 * objects.
 *
 * \see Type
 */

#ifndef HUMMSTRUMM_ENGINE_CORE_TYPE
#define HUMMSTRUMM_ENGINE_CORE_TYPE

namespace hummstrumm
{
namespace engine
{
namespace core
{

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
 * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * \date 2009-09-02
 * \since 0.0
 *
 * \todo Actually implement this class!
 * \todo Add class registry?
 *
 * \see Object
 * \see HUMMSTRUMM_DECLARE_TYPE
 * \see HUMMSTRUMM_IMPLEMENT_TYPE
 */
class Type
{
  public:
    /**
     * Constructs a Type object for a certain Object.  The Object's name,
     * size in bytes, parent Type, and creation function are stored by the
     * Type.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param name [in] The name of the Object, including the namespaces it is
     *                  under.
     * \param size [in] The size, in bytes, of the Object.
     * \param parent [in] The Object's parent class's Type.  This is only a
     *                    null pointer at the root of the hierarchy.
     * \param createFunction [in] The Object's static create function, which
     *                            should return a Pointer<Object> to the newly-
     *                            created Object.
     *
     * \todo Implement
     *
     * \warning Do not create your own Type.  If you are using the engine's
     *          Object/Type system, this will be done for you.
     */
    Type (const hummstrumm::engine::types::String &name,
          std::size_t size,
          const Type *parent,
          hummstrumm::engine::core::Pointer<Object> (*createFunction) (void));
    /**
     * Destructs a Type object for a certain Object.  Since all Type objects
     * in the Object/Type system are static members of an Object, this
     * destructor will be called at program termination.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \todo Implement
     */
    ~Type (void);
    
    /**
     * Returns the name of the Object, including a full namespace hierarchy.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns The name of the Object, as a String.
     *
     * \todo Implement
     */
    const hummstrumm::engine::types::String &GetName (void) const;
    /**
     * Returns the size of the Object, in C++ bytes.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns The size of the Object, in C++ bytes.
     *
     * \todo Implement
     */
    std::size_t GetSize   (void) const;
    /**
     * Returns the parent Type of the Object.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns A pointer to the parent Type of this Object.
     *
     * \todo Implement
     */
    const Type *GetParent (void) const;
    
    /**
     * Returns whether this Object is the root of the hierarchy.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns Whether this Object is the root of the hierarchy.
     *
     * \todo Implement
     */
    bool IsRoot          (void)             const;
    /**
     * Returns whether this Object is the direct parent of another Type.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param type [in] A Type to test for inheritance.
     *
     * \returns Whether this Object is the direct parent of type.
     *
     * \todo Implement
     */
    bool IsParentClassOf (const Type *type) const;
    /**
     * Returns whether this Object is a direct child of another Type.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param type [in] A Type to test for inheritance.
     *
     * \returns Whether this Object is a direct child of type.
     *
     * \todo Implement
     */
    bool IsChildClassOf  (const Type *type) const;
    /**
     * Returns whether this Object is a descendant of another Type.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param type [in] A Type to test for inheritance.
     *
     * \returns Whether this Object is a descendant of type.
     *
     * \todo Implement
     */
    bool IsDerivedFrom   (const Type *type) const;
    /**
     * Returns whether this Object is an ancestor of another Type.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param type [in] A Type to test for inheritance.
     *
     * \returns Whether this Object is an ancestor of type.
     *
     * \todo Implement
     */
    bool IsBaseOf        (const Type *type) const;
    
    /**
     * Returns whether this Type is the same as another Type.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param type [in] A Type to test for equality.
     *
     * \returns Whether this Type is equal to type.
     *
     * \todo Implement
     *
     * \see operator==(const Type *type)
     */
    bool IsEqualTo  (const Type *type)   const;
    /**
     * Returns whether this Type has the same name as a String.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param name [in] A String to test for equality.
     *
     * \returns Whether this Type is equal to name.
     *
     * \todo Implement
     *
     * \see operator==(const hummstrumm::engine::types::String &)
     */
    bool IsEqualTo  (const hummstrumm::engine::types::String &name) const;
    /**
     * Returns whether this Type is the same as another Type.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param type [in] A Type to test for equality.
     *
     * \returns Whether this Type is equal to type.
     *
     * \todo Implement
     *
     * \see IsEqualTo(const Type *type)
     */
    bool operator== (const Type *type)   const;
    /**
     * Returns whether this Type has the same name as a String.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \param name [in] A String to test for equality.
     *
     * \returns Whether this Type is equal to name.
     *
     * \todo Implement
     *
     * \see IsEqualTo(const hummstrumm::engine::types::String &)
     */
    bool operator== (const hummstrumm::engine::types::String &name) const;
    
    /**
     * Creates a new Object of this Type using the default constructor.  A
     * Pointer<Object> to this new Object will be returned.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-09-02
     * \since 0.0
     *
     * \returns A Pointer<Object> to a new Object of this Type.
     *
     * \todo Implement
     *
     * \warning This functionality will only be available if the Object has a
     *          default constructor.
     *
     * \see Object::CreateNew
     */
    hummstrumm::engine::core::Pointer<Object> Create (void) const;
  
  private:
    /// The name of the Object, including a namespace hierarchy.
    char *name_;
    /// The size, in bytes, of the Object.
    std::size_t size_;
    /// The parent Type of the Object.
    const Type *parent_;
    /// The static creation function of the Object, which returns a
    /// Pointer<Object> to a new object.
    hummstrumm::engine::core::Pointer<Object> (*createFunction_) (void);
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
 * versions), and a method to create a new Object.
 *
 * If you use this macro, you will also have to use the
 * HUMMSTRUMM_IMPLEMENT_TYPE macro, which adds the definitions of these
 * members.
 *
 * This macro takes one argument, which is the name of the class.
 *
 * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * \date 2009-09-02
 * \since 0.0
 *
 * \param className [in] The name of the class.
 *
 * \see Object
 * \see Object::GetType
 * \see Object::CreateNew
 * \see Type
 * \see HUMMSTRUMM_IMPLEMENT_TYPE
 */
#define HUMMSTRUMM_DECLARE_TYPE(className) \
  private: \
    static hummstrumm::engine::core::Type _type_; \
  public: \
    static hummstrumm::engine::core::Type *GetType (void) throw (); \
    static hummstrumm::engine::core::Pointer<className> \
      CreateNew (void) throw (...); \
    virtual Pointer<const className> GetPointer (void) const throw (); \
    virtual Pointer<const className> operator&  (void) const throw (); \
    virtual Pointer<className>       GetPointer (void) throw (); \
    virtual Pointer<className>       operator&  (void) throw ();

/**
 * Adds support for the engine's Object/Type system to an Object.  Place this
 * macro at the top of the class's source file.
 *
 * This macro implements the members added by the HUMMSTRUMM_DECLARE_TYPE
 * macro.  You must supply the full class name (including the namespaces) and
 * the full parent class name (including the namespaces), and a template
 * definition, if you use one.
 *
 * If you use this macro, you will also have to use the HUMMSTRUMM_DECLARE_TYPE
 * macro, which adds the definitions of these members.
 *
 * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * \date 2009-09-02
 * \since 0.0
 *
 * \param templateDefinition [in] The template definition to prefix definitions
 *                                of the class members.
 * \param className [in] The full name of the class, including namespaces.
 * \param parentName [in] The full name of the parent class, including
 *                        namespaces.
 *
 * \see Object
 * \see Object::GetType
 * \see Object::CreateNew
 * \see Type
 * \see HUMMSTRUMM_DECLARE_TYPE
 */
#define HUMMSTRUMM_IMPLEMENT_TYPE(templateDefinition, className, parentName) \
  templateDefinition \
  hummstrumm::engine::core::Type className::type__ (#className, \
    sizeof (className), parentName::GetType (), className::CreateNew); \
   \
  templateDefinition \
  hummstrumm::engine::core::Type * \
  (className)::GetType (void) \
  { \
    return &_type_; \
  } \
   \
  templateDefinition \
  hummstrumm::engine::core::Pointer<hummstrumm::engine::core::Object> \
  className::CreateNew (void) \
  { \
    return new className; \
  } \
   \
  templateDefinition \
  hummstrumm::engine::core::Pointer<const className> \
  className::GetPointer (void) const throw () \
  { \
    return hummstrumm::engine::core::Pointer<const className> (this); \
  } \
  templateDefinition \
  hummstrumm::engine::core::Pointer<const className> \
  className::operator& (void) const throw () \
  { \
    return hummstrumm::engine::core::Pointer<const className> (this); \
  } \
  templateDefinition \
  hummstrumm::engine::core::Pointer<className> \
  className::GetPointer (void) throw () \
  { \
    return hummstrumm::engine::core::Pointer<className> (this); \
  } \
  templateDefinition \
  hummstrumm::engine::core::Pointer<className> \
  className::operator& (void) throw () \
  { \
    return hummstrumm::engine::core::Pointer<className> (this); \
  }

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_TYPE
