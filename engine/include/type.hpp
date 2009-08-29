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

namespace hummstrumm::engine::core
{
  /**
   * Specifies type attributes for a class.  A Type object contains
   * information about the class it represents.  The exact name is stored in
   * the Type object, as well as its size in C++ bytes.
   *
   * 
   *
   * The heap can dynamically expand itself, from the base size specified at
   * construction, by a certain amount specified at construction.  These
   * amounts are able to be configured via flags in the compileconfig.hpp
   * file, GAMEENGINE_HEAP_SIZE, GAMEENGINE_HEAP_EXPAND.
   *
   * There are two memory management models: first fit and best fit, which
   * can be chosen through flags in compileconfig.hpp, called
   * GAMEENGINE_HEAP_FIRSTFIT and GAMEENGINE_HEAP_BESTFIT.  The first fit
   * model finds the first openning large enough for the size to allocation,
   * going linearly through the heap memory.  The best fit model finds the
   * smallest free openning that will fit the object.  If two or more free
   * spaces are found that are the best size, the first one, selected
   * linearly, will be chosen to be allocated.  Two subclasses implement these
   * memory models.  You can also override this class to create a new memory
   * management model.
   *

   * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
   * \date 2009-07-29
   * \since 1.0.0.0
   *
   * \todo Actually implement this class!
   * \todo Finish documenting everything (maybe I can get someone else to do
   *       this for me.)
   * \todo Add class registry?
   */
  class Type
  {
    public:
      Type (const hummstrumm::engine::types::String &name,
            std::size_t size,
            const Type *parent,
            hummstrumm::engine::core::Pointer<Object> (*createFunction) (void));
      ~Type (void);
      
      const hummstrumm::engine::types::String &GetName (void) const;
      std::size_t GetSize   (void) const;
      const Type *GetParent (void) const;
      
      bool IsRoot          (void)             const;
      bool IsParentClassOf (const Type *type) const;
      bool IsChildClassOf  (const Type *type) const;
      bool IsDerivedFrom   (const Type *type) const;
      bool IsBaseOf        (const Type *type) const;
      
      bool IsEqualTo  (const Type *type)   const;
      bool IsEqualTo  (const hummstrumm::engine::types::String &name) const;
      bool operator== (const Type *type)   const;
      bool operator== (const hummstrumm::engine::types::String &name) const;
      
      hummstrumm::engine::core::Pointer<Object> Create (void) const;
    
    private:
      char *name_;
      std::size_t size_;
      const Type *parent_;
      hummstrumm::engine::core::Pointer<Object> (*createFunction_) (void);
  };
}

#define GET_TYPE_OF_CLASS (className) \
  (&(className)::type__)

#define GET_TYPE_OF_OBJECT (objectName) \
  (&(object).type__)

#define DECLARE_TYPE \
  public: \
    static hummstrumm::engine::core::Type _type_; \
    static hummstrumm::engine::core::Pointer<hummstrumm::engine::core::Object> _Create_ (void);

#define IMPLEMENT_TYPE(className, parentName) \
  hummstrumm::engine::core::Type className::type__ (#className, sizeof (className), \
    GET_TYPE_OF_CLASS (parentName), className::_Create_); \
   \
  hummstrumm::engine::core::Pointer<hummstrumm::engine::core::Object> \
  className::_Create_ (void) \
  { \
    return new className; \
  }

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_TYPE