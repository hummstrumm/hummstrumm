// -*- c++ -*-
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

#include "hummstrummengine.hpp"

#include <cstring>

namespace hummstrumm
{
namespace engine
{
namespace core
{


AllocationTable::AllocationTable (void)
  throw ()
  : head (0),
    allocationsPool (new char [sizeof (Allocation) * 32]),
    usedInPool (0)
{
  std::memset (this->allocationsPool, 0, sizeof (Allocation) * 32);
}


AllocationTable::~AllocationTable (void)
{
  for (Allocation *currentNode = this->head; currentNode;)
    {
      Allocation *temp = currentNode;
      currentNode = currentNode->nextAllocation;

      // Check if we're on the pool.
      if (reinterpret_cast <char *> (temp) >= this->allocationsPool &&
          reinterpret_cast <char *> (temp) < this->allocationsPool +
            sizeof (Allocation) * 32)
        {
          temp->~Allocation (); // Because of placement new.
        }
      else
        {
          delete temp;
        }
    }

  delete [] this->allocationsPool;
}


void
AllocationTable::Allocate (void *memoryLocation)
  throw ()
{
  char *memoryPlace = 0;
  Allocation *temp = 0;

  // Find place in pool to allocate.
  for (unsigned char i = 0; i < 32; ++i)
    {
      if ((this->usedInPool & (1 << i)) == 0)
        {
          memoryPlace = this->allocationsPool + sizeof (Allocation) * i;
          this->usedInPool |= (1 << i);
          break;
        }
    }

  // We have a place in the pool.
  if (memoryPlace)
    {
      temp = new (memoryPlace) Allocation (memoryLocation, this->head);
    }
  else
    {
      // Allocate from heap...we have to...
      temp = new Allocation (memoryLocation, this->head);
    }
  
  this->head = temp;
}


bool
AllocationTable::CheckAndRemove (void *memoryLocation)
  throw ()
{
  if (!this->head)
    {
      // If we don't even have one node in the table, then the memoryLocation
      // cannot possibly be on the heap.
      return false;
    }
  for (Allocation *currentNode = this->head;
       currentNode;
       currentNode = currentNode->nextAllocation)
    {
      if (currentNode->memoryLocation == memoryLocation)
        {
          if (currentNode == this->head)
            {
              this->head = currentNode->nextAllocation;
            }

          // Check if we're on the pool.
          if (reinterpret_cast <char *> (currentNode) >= this->allocationsPool &&
              reinterpret_cast <char *> (currentNode) < this->allocationsPool +
                sizeof (Allocation) * 32)
            {
              std::ptrdiff_t i = (reinterpret_cast <char *> (currentNode) -
                                  this->allocationsPool) / sizeof (Allocation);
              this->usedInPool &= ~(1 << i);

              currentNode->~Allocation (); // Because of placement new.
            }
          else
            {
              delete currentNode;
            }
          
          return true;
        }
    }

  return false;
}


AllocationTable::Allocation::Allocation (void *memoryLocation, Allocation *next)
  throw ()
  : memoryLocation (memoryLocation),
    nextAllocation (next),
    previousAllocation (0)
{
  if (next)
    {
      next->previousAllocation = this;
    }
}


AllocationTable::Allocation::~Allocation (void)
{
  if (this->previousAllocation)
    {
      this->previousAllocation->nextAllocation = this->nextAllocation;
    }
  if (this->nextAllocation)
    {
      this->nextAllocation->previousAllocation = this->previousAllocation;
    }
}


}
}
}
