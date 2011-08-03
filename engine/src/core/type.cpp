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
#define HUMMSTRUMM_ENGINE_SOURCE
#include "hummstrummengine.hpp"

#include <cstring>

namespace hummstrumm
{
namespace engine
{
namespace core
{

Type::Type (const hummstrumm::engine::types::String &name,
            std::size_t size,
            const Type *parent,
            Object::Ptr (*createFunction) (void))
  : name (new char [name.length () + 1]),
    size (size),
    parent (parent),
    createFunction (createFunction)
{
  // Copy into the internal buffer and be sure to NUL terminate it.
  std::strcpy (this->name, name.c_str ());
  this->name[name.length ()] = '\0';
}


Type::~Type (void)
{
  // Free up the buffer.
  delete this->name;
}
    

const hummstrumm::engine::types::String
Type::GetName (void)
  const throw ()
{
  return hummstrumm::engine::types::String (this->name);
}


std::size_t
Type::GetSize (void)
  const throw ()
{
  return this->size;
}


const Type *
Type::GetParent (void)
  const throw ()
{
  return this->parent;
}
    

bool
Type::IsRoot (void)
  const throw ()
{
  // If we don't have a parent, we are at the root of the tree.  This should
  // only happen for hummstrumm::engine::core::Object in our engine, but for the
  // sake of facilitating others using this code, we don't check.
  return (this->parent == 0);
}

bool
Type::IsParentClassOf (const Type *type)
  const throw ()
{
  return type->IsChildClassOf (this);
}


bool
Type::IsChildClassOf (const Type *type)
  const throw ()
{
  // Direct descendant.
  return (*this->parent == *type);
}


bool
Type::IsDerivedFrom (const Type *type)
  const throw ()
{
  return type->IsBaseOf (this);
}



bool
Type::IsBaseOf (const Type *type)
  const throw ()
{
  // If other type has no parents (through recursion or otherwise), this is
  // the end of the recursion chain, and return false all the way down.
  if (type->IsRoot ())
    {
      return false;
    }

  // If I am not the direct parent...
  if (!IsParentClassOf (type))
    {
      // Go one level up and check again
      return IsBaseOf (type->GetParent ());
    }
  // I am the direct parent, return true
  else
    {
      return true;
    }
}

  
bool
Type::IsEqualTo (const Type &type) const throw ()
{
  return ((this->size == type.GetSize ()) &&
          (*this->parent == *(type.GetParent ())) &&
          (GetName () == type.GetName ()));
}


bool
Type::IsEqualTo (const hummstrumm::engine::types::String &name) const throw ()
{
  // Maybe if we have a type registry then I could check everything
  return (GetName () == name);
}


bool
Type::operator== (const Type &type) const throw ()
{
  return IsEqualTo (type);
}


bool
Type::operator== (const hummstrumm::engine::types::String name) const throw ()
{
  return IsEqualTo (name);
}


Object::Ptr
Type::Create (void) const throw ()
{
  // Creates a new Object with a creation function for the Object.
  if (this->createFunction)
    {
      return this->createFunction ();
    }
  else
    {
      return 0;
    }
}


}
}
}
