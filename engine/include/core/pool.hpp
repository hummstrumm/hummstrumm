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
 * Defines the Pool class.
 *
 * @file   pool.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-07-22
 * @see    Pool
 */

#ifndef HUMMSTRUMM_ENGINE_CORE_POOL
#define HUMMSTRUMM_ENGINE_CORE_POOL

#include <climits>

namespace hummstrumm
{
namespace engine
{
namespace core
{

/**
 * A memory pool for a single type.  The memory pool is of a fixed size,
 * specified in the template declaration.  A memory pool allows for allocation
 * of single blocks and arrays of a certain type.  This is the default
 * allocation method for certain engine classes, like Number and String.  You
 * can create a Pool yourself, too, for your own malicious purposes, if needed.
 *
 * The advantage of a memory pool over the standard MasterHeap approach we use
 * in the engine stems from the fact that we know the size of all data types we
 * will allocate, as they are of a single type.  Because we know the size of
 * these types, we can optimise the memory allocation to not have to deal with
 * checks we do for a memory heap that can contain several data types and
 * sizes.  This speeds up the allocation process, which, for common types that
 * will be allocated many times and have short lifespans, this makes sense.  For
 * classes like Number and String, which are common and of a known size, it
 * makes sense to use a Pool.
 *
 * The actual memory pool for a type is managed by the type.  Types that take
 * advantage of a Pool will use the HUMMSTRUMM_DECLARE_USE_POOL() macro to
 * create custom new and delete methods for itself that will manage pools for
 * the memory.  If the Pool is full, the method will give a warning, and then
 * allocate from the MasterHeap.  The default size of pools can be changed
 * through the HUMMSTRUMM_POOL_SIZE macro.  All of these macros have
 * corresponding IMPLEMENT methods that are placed in the source file.  You can
 * turn off these optimisations for data types via the HUMMSTRUMM_USE_POOL flag
 * (not to be confused with HUMMSTRUMM_<b>DECLARE</b>_USE_POOL).
 *
 * @version 0.3
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-07-22
 * @since 0.3
 *
 * @see MasterHeap
 * @see HUMMSTRUMM_DECLARE_USE_POOL
 * @see HUMMSTRUMM_IMPLEMENT_USE_POOL
 *
 * @todo Make macros for use with a class.  (This was annoying, I will think
 * about an efficient way to do this and then implement it in a later version.)
 */
template <typename T, unsigned int SIZE>
class Pool
{
  public:
    /**
     * Constructs a new Pool, with no allocations in it.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2009-07-22
     * @since  0.3
     */
    Pool (void);
    /**
     * Destructs an Pool.  If it is not empty, it emits a warning.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-07-22
     * @since  0.3
     */
    virtual ~Pool (void);

    /**
     * Returns whether the memory block is a member of the Pool.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-07-22
     * @since  0.3
     *
     * @returns If memory is in this Pool.
     */
    bool IsPoolMemory (const T *const memory)
      const throw ();
    /**
     * Returns whether there is any space in the Pool.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-07-22
     * @since  0.3
     *
     * @return If the Pool is full.
     */
    bool IsFull (void)
      const throw ();
    /**
     * Returns whether there are any allocations in the Pool.
     *
     * @author Patrick Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-07-22
     * @since  0.3
     *
     * @return If the Pool is empty.
     */
    bool IsEmpty (void)
      const throw ();

    /**
     * Allocates a free block of memory in the Pool, if a block exists.  This
     * allocates the first free block it finds in the Pool.  If no block exists,
     * the pointer is set to NULL.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-07-22
     * @since 0.3
     *
     * @param out [out] A pointer to the pointer to the newly allocated block.
     */
    void Allocate (T **out)
      throw (hummstrumm::engine::error::MemoryCorruption);
    /**
     * Allocates an array of free blocks of memory in the Pool, if such an array
     * exists.  This allocates the first array of the proper size it finds in
     * the Pool.  If no block exists, the pointer will be set to NULL.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-07-22
     * @since 0.3
     *
     * @param out [out] A pointer to the pointer to the newly allocated block.
     * @param numberInArray [in] The number of elements in the requested array.
     */
    void Allocate (T **out, unsigned int numberInArray)
      throw (hummstrumm::engine::error::MemoryCorruption);
    /**
     * Frees an array or single allocation from the Pool.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2001-07-22
     * @since 0.3
     *
     * @param oldMemory [inout] A pointer to the pointer to the memory to be
     * freed.
     */
    void Free (T **oldMemory)
      throw ();

  private:
    Pool (Pool &);
    void operator= (Pool &);
    
    /**
     * Allocates a free block of memory in the Pool, if a block exists.  This
     * allocates the first free block it finds in the Pool.  If no block exists,
     * the pointer is set to NULL.
     *
     * This is the internal method for allocating memory.  It will not work
     * directly with C++ objects.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-07-31
     * @since 0.3
     *
     * @param out [out] A pointer to the pointer to the newly allocated block.
     */
    void AllocateInternal (T **out)
      throw (hummstrumm::engine::error::MemoryCorruption);
    /**
     * Allocates an array of free blocks of memory in the Pool, if such an array
     * exists.  This allocates the first array of the proper size it finds in
     * the Pool.  If no block exists, the pointer will be set to NULL.
     *
     * This is the internal method for allocating memory.  It will not work
     * directly with C++ objects.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-07-31
     * @since 0.3
     *
     * @param out [out] A pointer to the pointer to the newly allocated block.
     * @param numberInArray [in] The number of elements in the requested array.
     */
    void AllocateInternal (T **out, unsigned int numberInArray)
      throw (hummstrumm::engine::error::MemoryCorruption);
    /**
     * Frees an array or single allocation from the Pool.
     *
     * This is the internal method for allocating memory.  It will not work
     * directly with C++ objects.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2001-07-31
     * @since 0.3
     *
     * @param oldMemory [inout] A pointer to the pointer to the memory to be
     * freed.
     */
    void FreeInternal (T **oldMemory)
      throw ();
    
    /// The pool of objects.
    unsigned char pool [SIZE][sizeof (T)];
    /// Which of the blocks in the pool have been allocated.  One bit per block.
    unsigned char allocations[(SIZE % CHAR_BIT == 0) ?
                              SIZE / CHAR_BIT :
                              SIZE / CHAR_BIT + 1];
    /// Which of the blocks is part of an array.  The first allocated block is a
    /// 0, while all subsequent blocks in the array are 1.  This allows one Free
    /// method to be used for both arrays and single allocations.  I cannot see
    /// any other way.  One bit per block.
    unsigned char arrays     [(SIZE % CHAR_BIT == 0) ?
                              SIZE / CHAR_BIT :
                              SIZE / CHAR_BIT + 1];
    /// A pointer to the first block, to simplify the allocation of single
    /// blocks.
    T *firstFreeBlock;
};

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_POOL
