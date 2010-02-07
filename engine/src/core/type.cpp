// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2010, the people listed in the AUTHORS file. 
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

#include <cstring>
#include <string> // HACK: Until String class is made

#include <config.h>
#include <core/type.hpp>
#include <core/pointer.hpp>
#include <core/object.hpp>

namespace hummstrumm
{
namespace engine
{
namespace core
{

Type::Type (const std::string name,
            std::size_t size,
            const Type *parent,
            hummstrumm::engine::core::ObjectPtr (*createFunction) (void))
  : name_ (new char [name.length ()+1]),
    size_ (size),
    parent_ (parent),
    createFunction_ (createFunction)
{
  std::strcpy (name_, name.c_str ());
  name_[name.length ()] = '\0';
}


Type::~Type (void)
{
  delete name_;
}
    

const std::string
Type::GetName (void) const throw ()
{
  return std::string (name_);
}


std::size_t
Type::GetSize (void) const throw ()
{
  return size_;
}


const Type *
Type::GetParent (void) const throw ()
{
  return parent_;
}
    

bool
Type::IsRoot (void) const throw ()
{
  return (parent_ == 0);
}

bool
Type::IsParentClassOf (const Type *type) const throw ()
{
  return type->IsChildClassOf (this);
}


bool
Type::IsChildClassOf (const Type *type) const throw ()
{
  return (*parent_ == *type);
}


bool
Type::IsDerivedFrom (const Type *type) const throw ()
{
  return type->IsBaseOf (this);
}



bool
Type::IsBaseOf (const Type *type) const throw ()
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
  return ((size_ == type.GetSize ()) &&
          (*parent_ == *(type.GetParent ())) &&
          (GetName () == type.GetName ()));
}


bool
Type::IsEqualTo (const std::string name) const throw ()
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
Type::operator== (const std::string name) const throw ()
{
  return IsEqualTo (name);
}


ObjectPtr
Type::Create (void) const throw ()
{
  // Creates a new Object with a creation function for the Object.
  if (createFunction_)
    {
      return createFunction_ ();
    }
  else
    {
      return 0;
    }
}


}
}
}
