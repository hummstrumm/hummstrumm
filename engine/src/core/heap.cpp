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
#define HUMMSTRUMM_ENGINE_SOURCE
#include "hummstrummengine.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#if !defined (WIN32)
#include <unistd.h>
#endif

#include <iostream>
#include <string>
#include <sstream>

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#  pragma warning(disable:4267)
#  pragma warning(disable:4290)
#  pragma warning(disable:4715)
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS


namespace hummstrumm
{
namespace engine
{
namespace core
{

#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
#pragma init_seg(lib)
MasterHeap masterToAll;
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS

#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
MasterHeap masterToAll
  __attribute__ ((init_priority (2000)));
#endif


MasterHeap::Block::Block (Block *previous, Block *next, std::size_t size,
                          Heap *heap)
{
      // Fill in all our header values.
  this->previous = previous;
  this->next = next;
  this->size = size;
  this->heap = heap;

#ifdef HUMMSTRUMM_HEAP_ZERO_MEMORY
  std::memset (this->GetMemory (), size, 0);
#endif // #ifdef HUMMSTRUMM_HEAP_ZERO_MEMORY
}

MasterHeap::Block::~Block (void)
{}

MasterHeap::Block *
MasterHeap::Block::GetPrevious (void)
  throw ()
{
  return this->previous;
}

MasterHeap::Block *
MasterHeap::Block::GetNext (void)
  throw ()
{
  return this->next;
}

char *
MasterHeap::Block::GetMemory (void)
  throw ()
{
  return reinterpret_cast <char *> (this + 1);
}

std::ptrdiff_t
MasterHeap::Block::GetMemoryOffset (void)
  throw ()
{
  return (static_cast <std::ptrdiff_t> (sizeof (Block)));
}

MasterHeap::Segment::Segment (Segment *previous)
  : previous   (previous),
    next       (0),
    firstBlock (0),
    heap       (0)
{}

MasterHeap::Segment::~Segment (void)
{}

bool
MasterHeap::Segment::Allocate (char **newMemory, const std::size_t size)
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
          HUMMSTRUMM_THROW (OutOfMemory, "Segments are not large enough to fit"
                                         "a contiguous block of that size.")
        }
          // Use the placement new syntax.
      this->firstBlock = new (this->GetMemoryStart ())
        Block (0, 0, size, heap);
          // We have allocated a Block, but the user only cares about the
          // memory inside the Block.  Set the output pointer to the beginning
          // of the real memory.
      *newMemory = this->firstBlock->GetMemory ();
      
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
                                         sizeOfBlock)
                    Block (block, 0, size, heap);
                      // Tell the prior block about the new end block.
                  block->next = newBlock;
                      // Return the actual memory.
                  *newMemory = newBlock->GetMemory ();
                  
                  return true;
                }
            }
        }     
    }
  return false;
}

bool
MasterHeap::Segment::Free (char **oldMemory)
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
      
          // Now tell the next block down the list that there is no block
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
MasterHeap::Segment::IsInSegment (Block *block)
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

MasterHeap::Segment *
MasterHeap::Segment::GetPrevious (void)
  throw ()
{
  return this->previous;
}

MasterHeap::Segment *
MasterHeap::Segment::GetNext (void)
  throw ()
{
  return this->next;
}

char *
MasterHeap::Segment::GetMemoryStart (void)
  throw ()
{
  return this->memory;
}

MasterHeap::Block *
MasterHeap::Segment::GetFirstBlock (void)
  throw ()
{
  return this->firstBlock;
}


void
MasterHeap::Segment::SetNext (Segment *next)
  throw ()
{
  this->next = next;
}

MasterHeap::Heap::Heap (Segment *head)
  : head (head)
{}

MasterHeap::Heap::~Heap (void)
{
  MasterHeap::FreeSegment (this->head);
}

MasterHeap::Segment *
MasterHeap::Heap::GetHeadSegment (void)
  throw ()
{
  return this->head;
}

void
MasterHeap::Heap::Allocate (char **newMemory, std::size_t size)
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
MasterHeap::Heap::Free (char **oldMemory)
  throw ()
{
  std::cout << "Freeing a block...\n";

  Segment *currentSegment = this->head;
  
  if (!IsHeapMemory (oldMemory))
    {
      std::cerr << "WARNING: Non-heap memory could not be freed.\n";
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
MasterHeap::Heap::IsHeapMemory (const void *const memory)
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
MasterHeap::Heap::FreeHelper (char **oldMemory)
{
  if (!MasterHeap::GetMasterHeap ().IsHeapMemory (*oldMemory))
    {
      return;
    }
  
  Block *block;

  block = reinterpret_cast <Block *>
    (std::size_t (oldMemory) - std::size_t (Block::GetMemoryOffset ())); 
  
  if (block->heap->IsHeapMemory (block))
    {
      block->heap->Free (oldMemory);
    }
  else
    {
      HUMMSTRUMM_LOG (L"Trying to free a corrupt block.", ERROR);
    }
}

MasterHeap::MasterHeap (void)
  : heaps ((Heap **) std::malloc (sizeof (Heap *) *
                                  GetNumberOfHeapsInternal ()))
{
  
  for (unsigned int i = 0; i < GetNumberOfHeapsInternal (); i++)
    {
      void *memory = std::malloc (sizeof (Heap));
      heaps[i] = new (memory) Heap (AllocateSegment (0));
    }
}

MasterHeap::~MasterHeap (void)
{
  for (unsigned int i = 0; i < GetNumberOfHeapsInternal (); i++)
    {
      delete heaps[i];
    }
  delete [] heaps;
}

MasterHeap &
MasterHeap::GetMasterHeap (void)
  throw ()
{
  return masterToAll;
}

MasterHeap::Heap *
MasterHeap::GetHeap (unsigned int index)
  throw ()
{
  if (index > GetNumberOfHeapsInternal ())
    {
      HUMMSTRUMM_THROW (OutOfRange, "The heap selected does not exist.");
    }
  else
    {
      return heaps[index];
    }
}


bool
MasterHeap::IsHeapMemory (char *memory)
  const throw ()
{
  for (unsigned int i = 0; i < GetNumberOfHeapsInternal (); i++)
    {
      if (heaps[i]->IsHeapMemory (memory))
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


const hummstrumm::engine::types::Number
MasterHeap::GetHeapCount (void)
  const throw ()
{
  return hummstrumm::engine::types::Number (GetNumberOfHeapsInternal ());
}


MasterHeap::Segment *
MasterHeap::AllocateSegment (Segment *previous)
  throw ()
{
  void *memory = std::malloc (sizeof (Segment));
  return new (memory) Segment (previous);
}


void
MasterHeap::FreeSegment (Segment *segment)
  throw ()
{
  if (segment->GetFirstBlock () && segment->GetNext () != 0)
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


const unsigned int
MasterHeap::GetNumberOfHeapsInternal (void)
  const throw ()
{
  
  // Windows API
#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
  SYSTEM_INFO windowsSystemInfo;
  GetSystemInfo (&windowsSystemInfo);

  return static_cast <unsigned int> (windowsSystemInfo.dwNumberOfProcessors);
#endif // #ifdef HUMMSTRUM_PLATFORM_WINDOWS

  // Linux only
#ifdef HUMMSTRUMM_PLATFORM_GNULINUX
  return static_cast <unsigned int> (sysconf (_SC_NPROCESSORS_ONLN));
#endif // #ifdef HUMMSTRUM_PLATFORM_GNULINUX
  
}


}
}
}
