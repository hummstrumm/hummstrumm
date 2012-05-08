// -*- mode: c++; c-file-style: hummstrumm -*-
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

/**
 * Defines the AllocationTable class.
 *
 * @file   core/allocationtable.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-11-25
 * @see    AllocationTable
 */

#ifndef HUMMSTRUMM_ENGINE_CORE_ALLOCATIONTABLE
#define HUMMSTRUMM_ENGINE_CORE_ALLOCATIONTABLE


namespace hummstrumm
{
namespace engine
{
namespace core
{


/**
 * A table of recent allocations on the heap.  This table is internally a linked
 * list of AllocationTable::Allocation objects, each of which represent a single
 * allocation on the Heap.
 *
 * The initial reference count of an Object depends on where it was created.
 * Objects created on the stack or in static memory should never be deleted, so
 * such Objects should always have a reference count greater than 0.  We
 * accomplish this by setting the initial reference count to 1, so 0 can never
 * be reached.  This makes sense intuitively, also, because variables created in
 * these locations all have references pointing to them for the duration of
 * their lives (the name you give them), whereas heap variables have no name
 * automatically assigned to them, and no references automatically created.
 *
 * Even if the Object is created on the heap, we need to take care to make sure
 * the user actually created it themselves via new.  If the Object is a
 * by-product of something else, like creating an array of Objects with new[] or
 * an Object that is a member of another Object being created on the heap, then
 * we cannot ever call delete on it!  The lifespans of these Objects is already
 * managed.  Thus, we need to give them an initial reference count on them as
 * well.
 *
 * This is solved by the following method:
 *
 * Whenever there is an allocation on the Heap of any single reference counted
 * Object instances, ones not in an array, we add an entry to the list of
 * Allocations.  Then, whenever an Object is constructed, we check to see if
 * address of that Object is in the list of Allocations.  If it isn't, that
 * means the Object either isn't on the heap (could be in static or stack
 * memory), or it is a member of an allocated data structure on the heap
 * (including elements of an array).  Either way, we shouldn't call delete on
 * it.  Otherwise, we allow it to be deleted.
 *
 * This rules out stack variables, static/global variables, member variables,
 * and all array elements.  The only remaining Object instances are ones that
 * are directly allocated on the heap by the user.
 *
 * To keep the size of the AllocationTable down, we remove an
 * AllocationTable::Allocation once it has been checked, as it will no longer be
 * necessary.
 * 
 * @version 0.3
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2009-11-25
 * @since 0.3
 *
 * @note I consider this one big HACK, but I really cannot think of a way around
 * this that is stable (like, it won't randomly fail (you laugh, but lots of
 * them do)) and deterministic (it wouldn't be a Good Thing if all threads
 * stopped so the garbage collector could mark-and-sweep; this is a game!).
 * Maybe we can discover a more efficient way in the future, or perhaps just
 * avoid this altogether?  Whatever, for now.
 */
class AllocationTable
{
  public:
    /**
     * Constructs a new AllocationTable object.  It starts out as empty.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     */
    AllocationTable ()
      throw ();
    /**
     * Destructs an AllocationTable object.  All memory used in the linked list
     * is freed.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     */
    virtual ~AllocationTable ();

    /**
     * Adds a new Allocation to the head of the list.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param [in] memoryLocation The memory location to add. 
     * 
     * @todo Make thread safe.
     */
    void Allocate (void *memoryLocation)
      throw ();
    /**
     * Checks to see if the Allocation is in the list, and if so, removes it.
     * If it was in the list, we return true, and if it wasn't, we return false.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     *
     * @param memoryLocation [in] The memory location to check.
     *
     * @return If the Allocation was on the list. 
     * @retval true The reference count of the new Object should be 0.
     * @retval false The reference count of the new Object should be 1.
     * 
     * @todo Make thread safe.
     */
    bool CheckAndRemove (void *memoryLocation)
      throw ();
    
  private:
    /**
     * A single allocation on the heap.  This data structure holds the memory
     * address of the allocation and whether the allocation was made with new or
     * new[].  It also functions as a linked list in the doubly-linked list of
     * AllocationTable.
     *
     * All member fields are public because only AllocationTable can access them
     * anyways.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-27
     * @since  0.3
     */
    class Allocation
    {
      public:
        /**
         * Constructs a new Allocation object.  All Allocation objects are
         * created at the head of the list.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2010-11-27
         * @since  0.3
         *
         * @param [in] memoryLocation The memory location that was allocated.
         * @param [in] next The next node in the linked list.
         */
        Allocation (void *memoryLocation,
                    Allocation *next)
          throw ();
        /**
         * Destructs an Allocation object.  If there are previous or next nodes
         * in the linked list, they are updated.
         *
         * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
         * @date   2010-11-27
         * @since  0.3
         */
        virtual ~Allocation ();

        void *memoryLocation;           ///< The allocated memory.
        Allocation *previousAllocation; ///< Last allocation in the list.
        Allocation *nextAllocation;     ///< Next allocation in the list.
    };

    /// The start of the current Allocation stack.
    Allocation *head;
    /// A pool in which to allocate Allocation objects for speed.
    char *allocationsPool;
    /// A bitfield for tracking which elements of the pool are used.
    hummstrumm::engine::types::uint32 usedInPool;
};


}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_ALLOCATIONTABLE
