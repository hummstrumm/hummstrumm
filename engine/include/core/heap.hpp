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

/**
 * Defines the Heap class and the helper classes MasterHeap, Segment, and
 * Block.
 * 
 * @file   heap.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-01-03
 * @see    Heap
 */

#ifndef HUMMSTRUMM_ENGINE_CORE_HEAP
#define HUMMSTRUMM_ENGINE_CORE_HEAP

#include <error/error.hpp>
#include <error/outofmemory.hpp>

namespace hummstrumm
{
namespace engine
{
namespace core
{

// Forward declarations
class MasterHeap;
class Heap;
class Segment;

/**
 * A single allocated block of memory.  A Block is created for every call to
 * the Heap::Allocate method.
 *
 * The Block class is only the header for an allocated Block; the actual memory
 * comes after the Block object.  This class contains information like the size
 * of the memory block and the next and previous blocks in the linked list for
 * the Segment.
 *
 * This class is theoretically portable to all system archetectures, 32-bit or
 * 64-bit.
 *
 * @version 1.0.0.0 
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-01-03
 * @since 1.0.0.0
 *
 * @note All members of this class are equal in size to the natural size of the
 * system.  Because this means it will be aligned properly no matter what,
 * because the greatest necessary alignment is the natural boundary.  The
 * memory after this header Block is therefor guarranteed to be aligned
 * properly, too.
 *
 * @note This class should never be seen by the user.  It is a helper class for
 * Heap.
 */
class Block
{
        // So Segment can access private members.
    friend class Segment;
    friend class Heap;
  public:
    /**
     * Constructs a new Block.  Zeros the new Block's memory.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @param previous The Block before this one in the Segment.
     * @param next The Block after this one in the Segment.
     * @param size The size of the allocated memory for this Block.
     * @param heap The Heap on which this Block is allocated.
     *
     * @todo Allow users to select whether to zero all new memory through a
     * compile time definition.
     */
    Block (Block *previous, Block *next, std::size_t size, Heap *heap);
    /** 
     * Destructs a Block.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     */
    ~Block (void);

    /** 
     * Returns the previous Block in the Segment.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     *
     * @returns The previous Block in the Segment.
     */
    Block *GetPrevious (void)
      throw ();
    /** 
     * Returns the next Block in the Segment.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     *
     * @returns The next Block in the Segment.
     */
    Block *GetNext     (void)
      throw ();
    /** 
     * Returns the memory of the Block.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     *
     * @returns The memory of the Block.
     */
    char *GetMemory   (void)
      throw ();

    /** 
     * Returns the offset of the memory from the Block start.  This is always
     * equal to the sizeof the Block.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @returns The offset of the memory from the Block start.
     */
    static std::ptrdiff_t GetMemoryOffset (void)
      throw ();
    
  private:
        // This is important.  We have a header, an object of the specified
        // type, then a footer.  The block is guarranteed to be aligned
        // properly, by C++'s built-in alignment.
    Block *previous;            /**< The previous Block in the Segment. */
    Block *next;                /**< The next Block in the Segment. */
    std::size_t size;           /**< The size of the Block's memory.  */
    Heap  *heap;                /**< The Heap of this Block.  */
        // This alignment works because Block * and std::size_t are guarranteed
        // to be of the largest aligmnent size on a system (either 32-bits or
        // 64-bits depending on the architecture).
};

/**
 * A contiguous segment of memory in which Block objects are allocated.
 * Several of these make up a single Heap.  A Segment contains a linked list of
 * Blocks.
 *
 * To allocate memory, the Block calculates a place to fit the block starting
 * from the beginning of the Segment's memory.  It updates the linked list
 * accordingly.  If the memory can't be allocated, it fails and returns false.
 * If the requested memory is greater than the size of the Segment, then an
 * OutOfMemory exception is thrown, because no Segment can hold that size.
 *
 * To free memory, the Block takes the memory pointer to free and calculates
 * the location of the Block.  It then takes deletes the Block and resets the
 * linked list accordingly.
 *
 * @version 1.0.0.0
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-01-03
 * @since 1.0.0.0
 *
 * @todo Make the Segment size changable in the configuration.
 *
 * @note This class should never be seen by the user.  It is a helper class to
 * Heap.
 */
class Segment
{
    friend class Heap;
  public:
    /** 
     * Constructs a new Segment to put at the end of the Heap.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @param previous The last Segment allocated in the Heap.
     */
    Segment (Segment *previous);
    /** 
     * Destructs a Segment.  This should only be called at the end of the
     * program, when the Segment is freed from the Heap.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     */
    ~Segment (void);

    /** 
     * Allocates a new Block in the Segment, then sets an input pointer to the
     * Block's actual memory.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @param newMemory A pointer to a pointer to the new memory.
     * @param size The size to allocate.
     * 
     * @returns Whether or not the allocation succeeded.
     * @retval true The allocation succeeded.
     * @retval false The allocation failed.
     *
     * @exception OutOfMemory The requested Block is too large to fit in any
     * Segment.
     */
    bool Allocate (char **newMemory, const std::size_t size)
      throw (hummstrumm::engine::error::OutOfMemory);

    /** 
     * Frees a Segment of allocateed memory.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @param oldMemory A pointer to a pointer to old memory to free.
     * 
     * @returns Whether the old memory was successfully freed from the segment.
     * @retval true The old block was freed.
     * @retval false The old block was not freed.  It was either not in this
     * Segment or could not be freed.
     *
     * @todo Throw an exception on a failed allocation.
     *
     * @warning This method does not check to make sure the pointer passed in
     * is actually allocated.  It checks whether the memory is within Segment
     * boundaries using the IsInSegment() method.
     */
    bool Free (char **oldMemory)
      throw ();

    /** 
     * Returns whether a certain Block is within the Segment memory
     * boundaries.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @param block A pointer to the Block of memory to check.
     * 
     * @returns Whether the memory is with Segment boundaries.
     * @retval true The Block is within the Segment boundaries.
     * @retval false The Block is not within Segment boundaries.
     *
     * @warning This method does not check whether the memory is currently
     * allocated in the Segment.
     */
    bool IsInSegment (Block *block)
      throw ();

    /** 
     * Returns the previous Segment in the linked list of the Heap.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @returns The previous Segment in the Heap.
     */
    Segment *GetPrevious    (void)
      throw ();
    /** 
     * Returns the next Segment in the linked list of Heap.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @returns The next Segment in the Heap.
     */
    Segment *GetNext        (void)
      throw ();
    /** 
     * Returns a pointer to the beginning of the Segment's memory.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @returns A pointer to the beginning of the Segment's memory.
     */
    char    *GetMemoryStart (void)
      throw ();
    /** 
     * Returns the first Block in the Segment.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @returns The first Block in the Segment.
     */
    Block   *GetFirstBlock  (void)
      throw ();

    /** 
     * Sets the next Segment for this one.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @param next The new next Segment.
     *
     * @note There is no SetPrevious() method, because Segments cannot be freed
     * while the heap is in use with the current implementation.
     * 
     * @warning Do not call this method yourself.  It is only needed when the
     * Heap is expanding in size.
     */
    void SetNext (Segment *next)
      throw ();

  private:
    /** The size of the memory in a Segment. **/
    static const std::size_t SEGMENT_SIZE = 50003*sizeof(std::size_t);
    Segment *previous;          /**< The previous Segment in the Heap. */
    Segment *next;              /**< The next Segment in the Heap. */
    Block   *firstBlock;        /**< The first Block in the Segment. */
    char memory[SEGMENT_SIZE];  /**< The memory in which Blocks are stored. */
    char endByte;               /**< An end byte for calculation. */
    Heap    *heap;              /**< The Heap of this Segment */
};

/**
 * An interface to a collection of non-contiguous Segment objects through which
 * dynamic memory allocation is provided.  Each Heap is expandable; new Segment
 * objects are automatically created when there is no longer any room in the
 * Heap for a requested allocation.  Segment objects are stored in a linked
 * list.
 *
 * The Heap class works in conjunction with the Object::new and Object::delete
 * methods to provide a transparent memory allocation method that works more
 * quickly than the system memory heap does.  Certain subclasses of Object,
 * such as Character, use a Pool to increase efficiency in allocation.
 *
 * New Heap objects should not be created by the user.  During the program's
 * initialization, a Heap is created for every processor or processor core on
 * the system, allowing only one processor to be locked during a memory
 * allocation attempt.
 *
 * @version 1.0.0.0
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-01-24
 * @since 1.0.0.0
 *
 * @note This class should never be seen by the user.  The Object::new method
 * and Object::delete method provide the user level interface.
 * @note The maximum allocation size allowed by the Heap is equal to 50,000
 * pointer objects.
 * @note Segments are currently not able to be removed from the Heap when they
 * become empty.
 */
class Heap
{
  public:
    /** 
     * Constructs a Heap using a head Segment that was allocated by the
     * MasterHeap that created the Heap.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @param head The first Segment from which to construct the Heap.  This is
     * Allocated by MasterHeap::AllocateSegment.
     */
    Heap (Segment *head);
    /** 
     * Destructs a Heap.  This is called at the end of the program, so Heap
     * objects are valid for the lifespan of the program.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     */
    ~Heap (void);

    /** 
     * Returns the first Segment in the Heap object's linked list.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @returns The head Segment of the Heap.
     */
    Segment *GetHeadSegment (void)
      throw ();
    
    /** 
     * Allocates a block of new memory from the first openning in the Heap's
     * Segments.  The Allocate method iterates through each Segment in the
     * Heap looking for an open space of the right size to return.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @param newMemory [out] A pointer to the pointer to newly allocated
     * memory, to be set.
     * @param size [in] The size of the block of memory to allocate.
     * 
     * @throws OutOfMemory If the memory requested was too large for any
     * Segment to hold.
     */
    void Allocate (char **newMemory, std::size_t size)
      throw (hummstrumm::engine::error::OutOfMemory);

    /** 
     * Frees a block of memory from the Heap.  If the memory is not from the
     * Heap, a warning message is printed, and nothing else occurs.  The old
     * memory space is reclaimed immediately, and it can be used in new
     * allocations.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @param oldMemory [in, out] A pointer to the pointer to already allocated
     * memory to be freed.
     */
    void Free (char **oldMemory)
      throw ();
    
    /** 
     * Returns whether a chuck of allocated memory exists on this Heap.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @param memory [in] Memory to check whether is on the Heap.
     *
     * @returns Whether the memory passed in is on the Heap.
     */
    bool IsHeapMemory (const void *const memory)
      throw ();
      
    /** 
     * Chooses the Heap from which the memory to free is on (if any), and then
     * call that Heap::Free method.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     * 
     * @param oldMemory [in, out] A pointer to the pointer to already allocated
     * memory to be freed.
     */
    static void FreeHelper (char **oldMemory);

  private:
    Segment *head;    /**< The first Segment of the Heap. **/
};

/**
 * The interface between a Heap and the system memory allocator.  All Segment
 * allocations are done by the MasterHeap.  This allows different allocation
 * interfaces to be used below the Heap level, with just a simple change.
 *
 * During initialization, the MasterHeap allocates the same number of Heaps as
 * there are processors.  Because each processor has its own Heap, concurrency
 * issues are minimized.  Two processors can be allocating memory at the same
 * time with no issues.  An allocated Object will then remember which Heap it
 * was allocated on, and then free itself from the correct Heap.
 *
 * @version 1.0.0.0
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-01-24
 * @since 1.0.0.0
 *
 * @note This class should never be seen by the user.  It is a helper class to
 * Heap.
 */
class MasterHeap
{
    friend class Heap;
    
  public:
    /** 
     * Constructs a MasterHeap that will in turn allocate new Heap objects.
     * One Heap will be allocated per processor.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     */
    MasterHeap (void);
    /** 
     * Destructs the MasterHeap and all of its Heap objects.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     */
    ~MasterHeap (void);

    /** 
     * Returns a Heap object based on the processor with which it is
     * associated.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     *
     * @param processor [in] The processor of the Heap to return.
     *
     * @returns The Heap associated with the processor passed in.
     */
    Heap *GetHeap (unsigned int processor)
      throw ();
    
    /** 
     * Returns whether the memory is on any Heap, regardless of processor.  It
     * checks all allocated Heaps until it finds one that contains the memory.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     *
     * @param memory [in] Memory to check whether is on any Heap.
     *
     * @returns Whether the memory is dynamically allocated through a Heap.
     */ 
    bool IsHeapMemory (char *memory)
      throw ();

  private:
    /** 
     * Allocates a new Segment from system memory.  This is the only way
     * through which the Heap class interacts with the system memory heap.  Any
     * Segment objects allocated with this method must be freed using the
     * FreeSegment() method.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     *
     * @param previous [in] The Segment before this one on the Heap.
     *
     * @returns The newly-allocated Segment.
     */ 
    static Segment *AllocateSegment (Segment *previous)
      throw ();
    /** 
     * Frees Segment from system memory.  This is the only way through which
     * the Heap class interacts with the system memory heap.  Any Segment
     * objects passed to this Segment must have been allocated with the
     * AllocateSegment() method.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2009-02-06
     * @since 0.1
     *
     * @param segment [in] The Segment to free.
     */ 
    static void FreeSegment (Segment *segment)
      throw ();
    
    Heap **heaps;      /**< A dynamicly-sized array of Heap objects. **/
};

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_HEAP
