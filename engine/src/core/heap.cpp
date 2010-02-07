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

#include <cstddef>
#include <cstdlib>
#include <cstring>

#if !defined (WIN32)
#include <unistd.h>
#endif

#include <iostream>
#include <string>
#include <sstream>

#include <core/heap.cpp>

namespace hummstrumm
{
namespace engine
{
namespace core
{

#if defined (WINDOWS)
// Windows API
const unsigned int
GetProcessorCount_hidden_ (void)
  throw ()
{
  SYSTEM_INFO windowsSystemInfo;
  GetSystemInfo (&windowsSystemInfo);

  return static_cast <unsigned int> (windowsSystemInfo.dwNumberOfProcessors);
}
#else
// Linux only
const unsigned int
GetProcessorCount_hidden_ (void)
  throw ()
{
  return static_cast <unsigned int> (sysconf (_SC_NPROCESSORS_ONLN));
}
#endif

Block::Block (Block *previous, Block *next, std::size_t size, Heap *heap)
{
      // Fill in all our header values.
  this->previous = previous;
  this->next = next;
  this->size = size;
  this->heap = heap;

  std::memset (this->GetMemory (), size, 0);
}

Block::~Block (void)
{}

Block *
Block::GetPrevious (void)
  throw ()
{
  return this->previous;
}

Block *
Block::GetNext (void)
  throw ()
{
  return this->next;
}

char *
Block::GetMemory (void)
  throw ()
{
  return reinterpret_cast <char *> (this + 1);
}

std::ptrdiff_t
Block::GetMemoryOffset (void)
  throw ()
{
  return (static_cast <std::ptrdiff_t> (sizeof (Block)));
}

Segment::Segment (Segment *previous)
  : previous   (previous),
    next       (0),
    firstBlock (0),
    heap       (0)
{}

Segment::~Segment (void)
{}

bool
Segment::Allocate (char **newMemory, const std::size_t size)
  throw (hummstrumm::engine::error::OutOfMemory)
{
  char *iterator = this->GetMemoryStart ();
  Block *nextBlockToLookFor = this->GetFirstBlock ();
  
  if (!this->GetFirstBlock ())
    {
          // This Segment is completely empty, so just use the start of the
          // memory block.  But first check to make sure the segment can fit
          // the allocation.
      std::size_t sizeOfBlock  = size + sizeof (Block);
      if (sizeOfBlock > Segment::SEGMENT_SIZE)
        {
          THROW (OutOfMemory, "Segments are not large enough to fit a "
                 "contiguous block of that size.")
        }
          // Use the placement new syntax.
      this->firstBlock = new (this->GetMemoryStart ())
        Block (0, 0, size, heap);
          // We have allocated a Block, but the user only cares about the
          // memory inside the Block.  Set the output pointer to the beginning
          // of the real memory.
      *newMemory = this->firstBlock->GetMemory ();
          // Debug Message TO BE REMOVED.
      std::cout << "First Allocation...\n";
      return true;
    }

  if (std::size_t (this->GetFirstBlock ()) -
      std::size_t (this->GetMemoryStart ()) >= size)
    {
          // We know both that there is space before the first Block and that
          // there is enough space to fit a Block for type T.  This shouldn't
          // happen very often, but can.  We set the first block to our new
          // Block.  Again, we use placement new syntax here.
      Block *newBlock = new (this->GetMemoryStart ())
        Block (0, this->GetFirstBlock (), size, heap);
          // Change the old first block so that there is a new block before it.
      this->GetFirstBlock ()->previous = newBlock;
          // Set the new first block.
      this->firstBlock = newBlock;
          // And return the actual memory.
      *newMemory = newBlock->GetMemory ();
          // Debug Message TO BE REMOVED.
      std::cout << "Allocated New First Block...\n";
      return true;
    }
  
  while (iterator != &this->endByte)
    {
          // Iterate through the memory heap looking for free space that is
          // large enough to fit the new Block.
      
          // Loop until we get to first Block.
      if (iterator != reinterpret_cast <char *> (nextBlockToLookFor))
        {
              // Continue searching...
          iterator = reinterpret_cast <char *> (nextBlockToLookFor);
          continue;
        }
      else
        {
              // We've got a hit.  See if there is a block after this one.
          Block *block = reinterpret_cast <Block *> (iterator);
          
#define ROUND_TO_NATURAL(size) (((size % sizeof (void *) == 0) ?  \
                                 size/sizeof (void *) :          \
                                 size/sizeof (void *) + 1) * sizeof (void *))
          std::size_t sizeOfMemory = ROUND_TO_NATURAL (block->size);
#undef ROUND_TO_NATURAL
          
          std::size_t sizeOfBlock  = sizeOfMemory + sizeof (Block);
          
          if (block->next)
            {
                  // Yes, there is.  Calculate the difference between the end
                  // of this block and the start of the next one to see if
                  // there is enough space to fit a new Block.
              std::size_t sizeBetweenBlocks;
              sizeBetweenBlocks = reinterpret_cast <std::size_t>
                (block->next) - reinterpret_cast <std::size_t> (
                  reinterpret_cast <char *> (block) + sizeOfBlock);
              if (sizeBetweenBlocks < sizeof (Block))
                {
                      // We can't fit a block between the two.  Carry on.
                  nextBlockToLookFor = block->next;
                  iterator = reinterpret_cast <char *> (block->next);
                  continue;
                }
              else
                {
                      // We want to put a new block here.  Use placement new
                      // syntax.
                  Block *newBlock = new (reinterpret_cast <char *>
                    (block) + sizeOfBlock)
                    Block (block, block->next, size, heap);
                      // Insert into the linked list of blocks.
                  block->next->previous = newBlock;
                  block->next = newBlock;
                      // Return the actual memory.
                  *newMemory = newBlock->GetMemory ();
                      // Debug Message TO BE REMOVED.
                  std::cout << "Placed new block between other Blocks...\n";
                  return true;
                }
            }
          else
            {
                  // This is the last block.  Make sure there is enough memory
                  // in the segment to hold it.
              std::size_t sizeUntilEnd = reinterpret_cast <std::size_t>
                (&endByte) - reinterpret_cast <std::size_t> (
                  reinterpret_cast <char *> (block) + sizeOfBlock);
              if (sizeUntilEnd < sizeof (Block))
                {
                      // I can't fit a new block in this segment.
                  return false;
                }
              else
                {                  
                      // Allocate a new block with placement new syntax.
                  Block *newBlock = new (reinterpret_cast <char *> (block) +
                                         sizeOfBlock, heap)
                    Block (block, 0, size);
                      // Tell the prior block about the new end block.
                  block->next = newBlock;
                      // Return the actual memory.
                  *newMemory = newBlock->GetMemory ();
                      // Debug message TO BE REMOVED.
                  std::cout << "Placed new block after last allocated...\n";
                  return true;
                }
            }
        }     
    }
  return false;
}

bool
Segment::Free (char **oldMemory)
  throw ()
{
      // We need to find the block address from the memory address.  Instead of
      // subtracting the size of the header fields (which could change in
      // future updates, and is not guarranteed to be equal to the actual block
      // pointer) from the memory address, we use pointer arithmetic and
      // the offset from GetMemoryOffset().

      // A pointer to the block that owns the memory location.  We will compute
      // this.
  Block *block;
  
  char *memoryLocation = *(reinterpret_cast <char **> (oldMemory));

  block = reinterpret_cast <Block *>
    (reinterpret_cast <std::size_t> (memoryLocation) -
     static_cast <std::size_t> (Block::GetMemoryOffset ()));
  
  
      // First off, make sure this is in our Segment.
  if (!this->IsInSegment (block))
    {      
          // Sorry, it's not.      
      return false;
    }

      // If this block is the first block of the segment, we don't need to
      // worry about a previous block, but we need to tell the segment that we
      // have a new first block.
  if (this->GetFirstBlock () == block)
    { 
          // Tell the segment that the first block is the next down the line.
      this->firstBlock = block->next;
      
          // Now tell the next blsock down the list that there is no block
          // before it.
      if (block->next)
        {
          block->next->previous = 0;
        }
    }
      // Otherwise, we want to change both the previous block and next block's
      // pointers, because this is just a giant linked list.
  else
    { 
          // If there is a previous block, set its next pointer to skip over me
          // and point to my next block.
      if (block->previous)
        {
          block->previous->next = block->next;
        }
          // If there is a next block, set its previous pointer to skip over me
          // and point to my previous block.
      if (block->next)
        {
          block->next->previous = block->previous;
        }
    }

      // We don't need to call delete on the block, because we allocated it
      // with a placement new operator.  However, this means we must explicitly
      // call the destructor.
  block->~Block ();

      // Just for safety, null the input pointer.
  *oldMemory = 0;

  return true;
}

bool
Segment::IsInSegment (Block *block)
  throw ()
{
      // If the block exists after the memory start but before the memory
      // end, then it is in the segment.
  std::size_t blockLocation = reinterpret_cast <std::size_t> (block);
  std::size_t startLocation = reinterpret_cast <std::size_t>
    (this->GetMemoryStart ());
  std::size_t endLocation   = reinterpret_cast <std::size_t> (&this->endByte);
  
  if (blockLocation >= startLocation && blockLocation < endLocation)
    { 
      return true;
    }
  else
    { 
      return false;
    }
}

Segment *
Segment::GetPrevious (void)
  throw ()
{
  return this->previous;
}

Segment *
Segment::GetNext (void)
  throw ()
{
  return this->next;
}

char *
Segment::GetMemoryStart (void)
  throw ()
{
  return this->memory;
}

Block *
Segment::GetFirstBlock (void)
  throw ()
{
  return this->firstBlock;
}


void
Segment::SetNext (Segment *next)
  throw ()
{
  this->next = next;
}

Heap::Heap (Segment *head)
  : head (head)
{}

Heap::~Heap (void)
{
  MasterHeap::FreeSegment (this->head);
}

Segment *
Heap::GetHeadSegment (void)
  throw ()
{
  return this->head;
}

void
Heap::Allocate (char **newMemory, std::size_t size)
  throw (hummstrumm::engine::error::OutOfMemory)
{
  Segment *currentSegment = this->head;
  
  while (!currentSegment->Allocate (newMemory, size))
    {
          // This means we failed to allocate new memory in the segment.  Make
          // a new segment to store more stuff if needed.
      if (!currentSegment->next)
        {
          currentSegment->next =
            MasterHeap::AllocateSegment (currentSegment->next);
        }
      currentSegment = currentSegment->next;
      continue;
          // TODO: What if AllocateSegment fails?!
    }
      // Otherwise, newMemory contains allocated memory, and we can continue on
      // as normal.
}

void
Heap::Free (char **oldMemory)
  throw ()
{
  std::cout << "Freeing a block...\n";

  Segment *currentSegment = this->head;
  
  if (!IsHeapMemory (memory))
    {
      std::cerr << "WARNING: Non-heap memory could not be freed.\n");
      return;
    }
  
  while (!currentSegment->Free (oldMemory))
    {
          // The memory does not belong to this segment.  Ask for next.
      if (currentSegment->next)
        {
          currentSegment = currentSegment->next;
          continue;
        }
      else
        {
          std::cerr << "WARNING: Non-segment memory could not be freed.\n";
          break;
        }
    }
      // Otherwise, oldMemory was freed.
}

bool
Heap::IsHeapMemory (const void *const memory)
  throw ()
{
  Block *block; 
  
  const char *memoryLocation = (reinterpret_cast <const char *> (memory));

  block = reinterpret_cast <Block *>
    (std::size_t (memoryLocation) - std::size_t (Block::GetMemoryOffset ()));

  if (block->heap == this)
    {
      // Just make sure...
      Segment *currentSegment = GetHeadSegment ();
      while (currentSegment != 0)
        {
          if (currentSegment->IsInSegment (block))
            {
              return true;
            }
          else
            {
              currentSegment = currentSegment->GetNext ();
            }
        }
    }
  else
    {
      return false;
    }
}

void
Heap::FreeHelper (char **oldMemory)
{
  Block *block; 

  block = reinterpret_cast <Block *>
    (std::size_t (oldMemory) - std::size_t (Block::GetMemoryOffset ()));
  
  if (block->heap->IsHeapMemory (block))
    {
      block->heap->Free ();
    }
}

MasterHeap::MasterHeap (void)
  : heaps (new Heap *[GetProcessorCount_hidden_ ()])
{
  for (unsigned int i = 0; i < GetProcessorCount_hidden_ (); i++)
    {
      heaps[i] = new Heap (AllocateSegment (0));
    }
}

MasterHeap::~MasterHeap (void)
{
  for (unsigned int i = 0; i < GetProcessorCount_hidden_ (); i++)
    {
      delete heaps[i];
    }
  delete [] heaps;
}

Heap *
MasterHeap::GetHeap (unsigned int processor)
  throw ()
{
  return heaps[processor];
}

bool
MasterHeap::IsHeapMemory (char *memory)
  throw ()
{
  for (unsigned int i = 0; i < GetProcessorCount_hidden_ (); i++)
    {
      if (heaps[i]->IsHeapMemory ())
        {
          return true;
        }
      else
        {
          continue;
        }
    }
  
  return false;
}

Segment *
MasterHeap::AllocateSegment (Segment *previous)
  throw ()
{
  return new Segment (previous);
}

void
MasterHeap::FreeSegment (Segment *segment)
  throw ()
{
  if (segment->GetFirstBlock ())
    {
      std::cerr << "Attempting to free a segment that has allocations.\n";
      std::abort ();
    }

  if (segment->GetNext ())
    {
      FreeSegment (segment->GetNext ());
    }
  
  delete segment;
}


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_HEAP
