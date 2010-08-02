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

#ifndef HUMMSTRUMM_ENGINE_CORE_POOL_INL
#define HUMMSTRUMM_ENGINE_CORE_POOL_INL

#include <cstring>

namespace hummstrumm
{
namespace engine
{
namespace core
{


template <typename T, unsigned int SIZE>
Pool<T, SIZE>::Pool (void)
  : firstFreeBlock (reinterpret_cast <T *> (this->pool))
{
  std::memset (this->pool,        0, sizeof this->pool);
  std::memset (this->allocations, 0, sizeof this->allocations);
  std::memset (this->arrays,      0, sizeof this->arrays);
}


template <typename T, unsigned int SIZE>
Pool<T, SIZE>::~Pool (void)
{
  if (!IsEmpty ())
    {
      HUMMSTRUMM_WARNING ("The Pool was not empty when it was freed.");
    }
}


template <typename T, unsigned int SIZE>
bool
Pool<T, SIZE>::IsPoolMemory (const T *const memory)
  const throw ()
{
  // I want a ``uintptr_t'' in C++...
  return (reinterpret_cast <std::size_t> (memory) >=
            reinterpret_cast <std::size_t> (this->pool) &&
          reinterpret_cast <std::size_t> (memory) <
            reinterpret_cast <std::size_t> (this->pool + SIZE));
}


template <typename T, unsigned int SIZE>
bool
Pool<T, SIZE>::IsFull (void)
  const throw ()
{
  // Let's check if there are any allocations on the Pool.
  for (unsigned int i = 0;
       i < ((SIZE % CHAR_BIT == 0) ? SIZE / CHAR_BIT :
                                     SIZE / CHAR_BIT + 1);
       ++i)
    {
      if (this->allocations[i] != UCHAR_MAX)
        {
          // Well, it could be that the final unused bits are 0, in which case,
          // we could care less.  Clever bit shifts to find out if what we care
          // about is allocated.
          if (SIZE % CHAR_BIT == 0 &&
              i < SIZE / CHAR_BIT - 1 &&
              (UCHAR_MAX << (SIZE % CHAR_BIT)) ==
                this->allocations[i] & (UCHAR_MAX << (SIZE % CHAR_BIT)))
            {
              return true; // Everything is all set.
            }
          else
            {
              // Break out, because this means all the bits were not set as
              // allocated.
              return false;
            }
        }
    }
  return true;
}


template <typename T, unsigned int SIZE>
bool
Pool<T, SIZE>::IsEmpty (void)
  const throw ()
{
  // Let's check if there are any allocations on the Pool.
  for (unsigned int i = 0;
       i < ((SIZE % CHAR_BIT == 0) ? SIZE / CHAR_BIT :
                                     SIZE / CHAR_BIT + 1);
       ++i)
    {
      if (this->allocations[i] != 0)
        {
          // Break out, because this means there was some bit set as allocated.
          return false;
        }
    }
  return true;
}


template <typename T, unsigned int SIZE>
void
Pool<T, SIZE>::Allocate (T **out)
  throw (hummstrumm::engine::error::MemoryCorruption)
{
  T *memoryBlock = 0;
  AllocateInternal (&memoryBlock);
  *out = new (memoryBlock) T;
}


template <typename T, unsigned int SIZE>
void
Pool<T, SIZE>::Allocate (T **out, unsigned int numberInArray)
  throw (hummstrumm::engine::error::MemoryCorruption)
{
  T *memoryBlock = 0;
  AllocateInternal (&memoryBlock, numberInArray);
  *out = new (memoryBlock) T [numberInArray];
}


template <typename T, unsigned int SIZE>
void
Pool<T, SIZE>::Free (T **oldMemory)
  throw ()
{
  // Note we do not call FreeInternal.

  if (!oldMemory || !*oldMemory || !IsPoolMemory (*oldMemory))
    {
      return;
    }
  
  unsigned int i = 0;
  while (true)
    {
      // Find the difference of the pointer addresses, and divide it by the size
      // of the type of the array.
#define GET_INDEX(pointer) (((pointer) -                                       \
                             reinterpret_cast <T *> (this->pool)) / sizeof (T))
      // Integer division to get the byte that the pointer's bit is in.
      unsigned int  arrayIndex = ((GET_INDEX (*oldMemory) + i) / CHAR_BIT);
      // Modulus to find the bit within the byte that the pointer's bit is.
      int           bitIndex   = ((GET_INDEX (*oldMemory) + i) % CHAR_BIT);
      // Create a mask that has a 1 for the right bit, and 0s for all else.
      unsigned char mask       = ((UCHAR_MAX << (CHAR_BIT - 1)) >> bitIndex);
#undef GET_INDEX

      // If this is past the end of the array.
      if (i != 0 && (this->arrays[arrayIndex] & mask) == 0)
        {
          break;
        }
      else
        {
          // We turn all these bits off, which frees them.
          this->allocations[arrayIndex] &= ~mask;
          this->arrays[arrayIndex]      &= ~mask;

          // We don't need to call delete on the memory, because we allocated it
          // with a placement new operator.  However, this means we must
          // explicitly call the destructor.
          (*oldMemory + i)->~T ();
  
          ++i;
          continue;
        }
    }

  // See if this is before the current first free block.
  if (this->firstFreeBlock > *oldMemory)
    {
      this->firstFreeBlock = *oldMemory;
    }

  // Null the old pointer so nothing gets confused.
  *oldMemory = 0;
}


template <typename T, unsigned int SIZE>
void
Pool<T, SIZE>::AllocateInternal (T **out)
  throw (hummstrumm::engine::error::MemoryCorruption)
{
  if (this->firstFreeBlock)
    {
      // Lotsa bit ops...we have bit arrays ``allocations'' and ``arrays'',
      // which have one bit for each pool element.  All of this is platform
      // independent in that it works for any char size.

      // Find the difference of the pointer addresses, and divide it by the size
      // of the type of the array.
#define GET_INDEX(pointer) (((pointer) -                                       \
                             reinterpret_cast <T *> (this->pool)) / sizeof (T))
      // Integer division to get the byte that the pointer's bit is in.
      unsigned int arrayIndex = (GET_INDEX (this->firstFreeBlock) / CHAR_BIT);
      // Modulus to find the bit within the byte that the pointer's bit is.
      int          bitIndex   = (GET_INDEX (this->firstFreeBlock) % CHAR_BIT);
      // Create a mask that has a 1 for the right bit, and 0s for all else.

      unsigned char mask      = ((UCHAR_MAX << (CHAR_BIT - 1)) >> bitIndex);
#undef GET_INDEX

      // Turn the bit on.
      this->allocations[arrayIndex] |= mask;

      // Return this block.
      *out = this->firstFreeBlock;

      // Set it to zero if configured to.
#ifdef HUMMSTRUMM_HEAP_ZERO_MEMORY
      std::memset (*out, 0, sizeof (T));
#endif // #ifdef HUMMSTRUMM_HEAP_ZERO_MEMORY

      // Now find the next free block.  We loop forever, because we break out in
      // the loop body.
      while (true)
        {
          // We can skip the rest of this byte if it is fully allocated.
          if (this->allocations[arrayIndex] == UCHAR_MAX)
            {
              ++arrayIndex;
              bitIndex = -1;  // We will increment it on the next step.
              // If out of range...
              if (arrayIndex * CHAR_BIT + bitIndex >= SIZE)
                {
                  // There is no other free block.
                  this->firstFreeBlock = 0;
                  break;
                }
              continue;
            }
              
          // See, this comes before the body, because we are on the block we
          // just allocated.  We need to increment to the next block.
          if (bitIndex == CHAR_BIT - 1)
            {
              ++arrayIndex;
              bitIndex = 0;
              // If out of range...
              if (arrayIndex * CHAR_BIT + bitIndex >= SIZE)
                {
                  // There is no other free block.
                  this->firstFreeBlock = 0;
                  break;
                }
            }
          else
            {
              ++bitIndex;
            }

          // Create a mask that has a 1 for the right bit, and 0s for all else.
          unsigned char mask = ((UCHAR_MAX << (CHAR_BIT - 1)) >> bitIndex);

          // Check if the bit is on.
          if ((this->allocations[arrayIndex] & mask) == 0)
            {
              // The bit is off.  This means there is no allocation.
              this->firstFreeBlock = reinterpret_cast <T *> (this->pool) +
                                       (arrayIndex * CHAR_BIT + bitIndex);
              return;
            }
          else
            {
              // The bit was on, so there was an allocation there.  Loop again.
              continue;
            }
        }
    }
  else if (IsFull ())
    {
      // Oops...we're full.  We don't need an error here, because the user can
      // always just allocate from the Heap.
      *out = 0;
    }
  else
    {
      // Odd Pool corruption, we'll throw an error.
      HUMMSTRUMM_THROW (MemoryCorruption,
                        "The Pool is not full, but has an invalid first free "
                        "block pointer.");
    }
}


template <typename T, unsigned int SIZE>
void
Pool<T, SIZE>::AllocateInternal (T **out, unsigned int numberInArray)
  throw (hummstrumm::engine::error::MemoryCorruption)
{
  if (this->firstFreeBlock)
    {
      // Lotsa bit ops...we have bit arrays ``allocations'' and ``arrays'',
      // which have one bit for each pool element.  All of this is platform
      // independent in that it works for any char size.

      // Find the difference of the pointer addresses, and divide it by the size
      // of the type of the array.
#define GET_INDEX(pointer) (((pointer) -                                       \
                             reinterpret_cast <T *> (this->pool)) / sizeof (T))

      // Iterate through all empty spaces we find, until we run out of them or
      // find one that will fit our array.  Start with the first free block.
      T *currentPointer = this->firstFreeBlock;
      
      unsigned int  arrayIndex;
      int           bitIndex;
      unsigned char mask;
      
      while (true)
        {
          bool          canFit = true;

          // Search to see if this open space has enough slots to fit the array.
          for (unsigned int i = 0; i < numberInArray; ++i)
            {
              // Integer division to get the byte that the pointer's bit is in.
              arrayIndex = ((GET_INDEX (currentPointer) + i) / CHAR_BIT);
              // Modulus to find the bit within the byte that the pointer's bit
              // is.
              bitIndex   = ((GET_INDEX (currentPointer) + i) % CHAR_BIT);
              // Create a mask that has a 1 for the right bit, and 0s for all
              // else.
              mask       = ((UCHAR_MAX << (CHAR_BIT - 1)) >> bitIndex);
          
              // Check if the bit is on.
              if ((this->allocations[arrayIndex] & mask) == 0)
                {
                  // The bit is off.  This means there is no allocation.  YAY.
                  continue;
                }
              else
                {
                  // The bit was on, so there was an allocation there.  STOP.
                  canFit = false;
                  break;
                }
            }
          if (!canFit)
            {
              // Look for another place to fit.
              while (true)
                {
                  // We can skip the rest of this byte if it is fully allocated.
                  if (this->allocations[arrayIndex] == UCHAR_MAX)
                    {
                      ++arrayIndex;
                      bitIndex = -1;  // We will increment it on the next step.
                      // If out of range...
                      if (arrayIndex * CHAR_BIT + bitIndex >= SIZE)
                        {
                          // There is no other free block.
                          this->firstFreeBlock = 0;
                          *out = 0;
                          return;
                        }
                      continue;
                    }
              
                  // See, this comes before the body, because we are on the
                  // block we just allocated.  We need to increment to the next
                  // block.
                  if (bitIndex == CHAR_BIT - 1)
                    {
                      ++arrayIndex;
                      bitIndex = 0;
                      // If out of range...
                      if (arrayIndex * CHAR_BIT + bitIndex >= SIZE)
                        {
                          // There is no other free block.
                          this->firstFreeBlock = 0;
                          *out = 0;
                          return;
                        }
                    }
                  else
                    {
                      ++bitIndex;
                    }

                  // Create a mask that has a 1 for the right bit, and 0s for
                  // all else.
                  unsigned char mask = ((UCHAR_MAX << (CHAR_BIT - 1)) >>
                                        bitIndex);
                  

                  // Check if the bit is on.
                  if ((this->allocations[arrayIndex] & mask) == 0)
                    {
                      // The bit is off.  This means there is no allocation.
                      currentPointer = this->pool + (arrayIndex * CHAR_BIT +
                                                     bitIndex);
                      break;
                    }
                  else
                    {
                      // The bit was on, so there was an allocation there.  Loop
                      // again.
                      continue;
                    }
                }
            }
          else
            {
              for (unsigned int i = 0; i < numberInArray; ++i)
                {
                  // Integer division to get the byte that the pointer's bit is
                  // in.
                  arrayIndex = ((GET_INDEX (currentPointer) + i) / CHAR_BIT);
                  // Modulus to find the bit within the byte that the pointer's
                  // bit is.
                  bitIndex   = ((GET_INDEX (currentPointer) + i) % CHAR_BIT);  
                  // Create a mask that has a 1 for the right bit, and 0s for
                  // all else.
                  mask       = ((UCHAR_MAX << (CHAR_BIT - 1)) >> bitIndex);
          
                  // Turn the bits on.
                  this->allocations[arrayIndex] |= mask;
                  // Turn all but the first bit on.
                  if (i != 0)
                    {
                      this->arrays[arrayIndex] |= mask;
                    }
                }
            }
        }
#undef GET_INDEX

      *out = currentPointer;

      // If the first block didn't fit, then we can keep it as open.  Otherwise,
      // we need to find the next block that is free.
      if (currentPointer != this->firstFreeBlock)
        {
          return;
        }
      else
        {
          // Now find the next free block.  We loop forever, because we break
          // out in the loop body.
          while (true)
            {
              // We can skip the rest of this byte if it is fully allocated.
              if (this->allocations[arrayIndex] == UCHAR_MAX)
                {
                  ++arrayIndex;
                  bitIndex = -1;  // We will increment it on the next step.
                  // If out of range...
                  if (arrayIndex * CHAR_BIT + bitIndex >= SIZE)
                    {
                      // There is no other free block.
                      this->firstFreeBlock = 0;
                      break;
                    }
                  continue;
                }
              
              // See, this comes before the body, because we are on the block we
              // just allocated.  We need to increment to the next block.
              if (bitIndex == CHAR_BIT - 1)
                {
                  ++arrayIndex;
                  bitIndex = 0;
                  // If out of range...
                  if (arrayIndex * CHAR_BIT + bitIndex >= SIZE)
                    {
                      // There is no other free block.
                      this->firstFreeBlock = 0;
                      break;
                    }
                }
              else
                {
                  ++bitIndex;
                }

              // Create a mask that has a 1 for the right bit, and 0s for all
              // else.
              unsigned char mask = ((UCHAR_MAX << (CHAR_BIT - 1)) >> bitIndex);

              // Check if the bit is on.
              if ((this->allocations[arrayIndex] & mask) == 0)
                {
                  // The bit is off.  This means there is no allocation.
                  this->firstFreeBlock = this->pool + (arrayIndex * CHAR_BIT +
                                                       bitIndex);
                  break;
                }
              else
                {
                  // The bit was on, so there was an allocation there.  Loop
                  // again.
                  continue;
                }
            }
        }
    }
  else if (IsFull ())
    {
      // Oops...we're full.  We don't need an error here, because the user can
      // always just allocate from the Heap.
      *out = 0;
    }
  else
    {
      // Odd Pool corruption, we'll throw an error.
      HUMMSTRUMM_THROW (MemoryCorruption,
                        "The Pool is not full, but has an invalid first free "
                        "block pointer.");
    }
}


template <typename T, unsigned int SIZE>
void
Pool<T, SIZE>::FreeInternal (T **oldMemory)
  throw ()
{
  if (!oldMemory || !*oldMemory || !IsPoolMemory (*oldMemory))
    {
      return;
    }
  
  unsigned int i = 0;
  while (true)
    {
      // Find the difference of the pointer addresses, and divide it by the size
      // of the type of the array.
#define GET_INDEX(pointer) (((pointer) -                                       \
                             reinterpret_cast <T *> (this->pool)) / sizeof (T))
      // Integer division to get the byte that the pointer's bit is in.
      unsigned int  arrayIndex = ((GET_INDEX (*oldMemory) + i) / CHAR_BIT);
      // Modulus to find the bit within the byte that the pointer's bit is.
      int           bitIndex   = ((GET_INDEX (*oldMemory) + i) % CHAR_BIT);
      // Create a mask that has a 1 for the right bit, and 0s for all else.
      unsigned char mask       = ((UCHAR_MAX << (CHAR_BIT - 1)) >> bitIndex);
#undef GET_INDEX

      // If this is past the end of the array.
      if (i != 0 && (this->arrays[arrayIndex] & mask) == 0)
        {
          break;
        }
      else
        {
          // We turn all these bits off, which frees them.
          this->allocations[arrayIndex] &= ~mask;
          this->arrays[arrayIndex]      &= ~mask;
          ++i;
          continue;
        }
    }

  // See if this is before the current first free block.
  if (this->firstFreeBlock > *oldMemory)
    {
      this->firstFreeBlock = *oldMemory;
    }

  // Null the old pointer so nothing gets confused.
  *oldMemory = 0;
}


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_POOL_INL
