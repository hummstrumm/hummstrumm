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
 * \file heap.hpp
 *
 * Defines the Heap class.
 *
 * \see Heap
 */

#ifndef HUMMSTRUMM_ENGINE_CORE_HEAP
#define HUMMSTRUMM_ENGINE_CORE_HEAP

namespace hummstrumm
{
namespace engine
{
namespace core
{

/**
 * Manages all heap memory used in by Object objects.  Together with the
 * overloaded new and delete methods in the Object class, this allows
 * Objects and their subclasses to be allocated and freed.  The Objects are
 * also able to tell if they are on the heap at runtime, allowing them to
 * know whether to delete themselves.
 *
 * You can get information about the heap, such as the current number of
 * allocated object, the size of the heap, and the amount of free space
 * left on the heap.
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
 * \version 1.0.0.0.
 * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * \date 2009-07-20
 * \since 1.0.0.0
 *
 * \todo Actually implement this class!
 * \todo Finish documenting everything (maybe I can get someone else to do
 *       this for me.)
 * \todo Implement Best-fit Method (should be fun)
 *
 * \note This will be reworked when the multithreaded support is done (not for
 *       a while).  The API will stay mostly the same if used as specified.
 */
class Heap
{
  public:
    /**
     * Constructs a Heap object with a starting size and a size by which
     * to expand each time we need more space.  The actual heap in memory
     * is allocated here to the specified starting size.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \param sizeAtStart The amount of memory, in C++ bytes, allocate at
     *                    construction.
     * \param sizeToExpandBy (ARG!!! Ending on a preposition!!!) The amount
     *                       of memory by which to expand each time the
     *                       heap runs out of space.
     *
     * \todo Implement
     *
     * \warning This class is constructed by the engine internally.  You do
     *          not need to create an object of this class on your own.
     */
    Heap (std::size_t sizeAtStart, std::size_t sizeToExpandBy);
    /**
     * Destructs a Heap object.  Frees the heap memory.  No pointer
     * obtained through the Allocate method (or, indirectly, the
     * <code>new</code> operator of the Object class) will be valid after
     * this destructor is called.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \todo Implement
     */
    ~Heap (void);
    
    /**
     * "Allocates" memory from the Heap object.  The pointer passed in will
     * now point to the block of memory.  Make sure the pointer is of the
     * type you want to allocate.
     *
     * This method works in conjunction with the new operator of the Object
     * class.  The new operator hides this implementation, though you can
     * bypass this hiding by accessing the heap object directly.
     *
     * Because this method is a template function, the heap can allocate
     * any size objects, from an int to an Object, for example.  The heap
     * supports having several different types and sizes of objects.  If
     * the heap does not have a free block large enough to allocate the
     * object specified, the Heap expands by the amount specified in the
     * constructor.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \param memory A pointer to a pointer which will point to the new
     *               object's memory.
     *
     * \todo Implement
     *
     * \see Free ()
     */
    template <typename T>
    void Allocate (T **memory) throw ();
    /**
     * "Frees" memory allocated from the Heap object.  The pointer passed in
     * will no longer be a valid pointer, and the memory will be returned
     * for recycling in the heap.  The memory to which the pointer
     * referenceswill be checked to be valid heap allocated memory.  If it
     * is not, the function throws an exeption.
     *
     * This method works in conjunction with the delete operator of the
     * Object class.  The delete operator hides this implementation, though
     * you can bypass this hiding by accessing the heap object directly.
     *
     * Because this method is a template function, the heap can free
     * any type on the heap, from an int to an Object, for example.  The heap
     * supports having several different types and sizes of objects.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \param memory A pointer to the memory which will be freed.
     *
     * \todo Implement
     * \todo Throw exception (after Exception class is created)
     *
     * \see Allocate ()
     */
    template <typename T>
    void Free (const T *memory) throw ();
  
    /**
     * Returns whether a pointer points to an allocated block of heap
     * memory.
     *
     * The pointer must point to the beginning of a block allocated with
     * Allocate, not an area within a block allocated with Allocate.  This
     * method will fail otherwise.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \param memory A pointer to the memory which will be checked.
     *
     * \returns Whether the pointer is valid, allocated heap memory.
     *
     * \todo Implement
     */
    bool IsAllocatedHeapMemory (const void *memory) const throw ();
    /**
     * Returns the number of allocated blocks of memory.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \returns The number of allocated blocks of memory, the number of
     *          times the Allocate method has been called.
     *
     * \todo Implement
     */
    unsigned int GetAllocatedCount (void) const throw ();
    /**
     * Returns the current total size of the heap.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \returns The size of the heap.
     *
     * \todo Implement
     */
    size_t GetTotalSpace (void) const throw ();
    /**
     * Returns the current size of the free space in the heap.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \returns The amount of free space left.
     *
     * \todo Implement
     */
    size_t GetTotalFreeSpace (void) const throw ();
    /**
     * Returns the current size of the allocated space in the heap.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \returns The amount of allocated space used.
     *
     * \todo Implement
     */
    size_t GetTotalAllocatedSpace (void) const throw ();
    /**
     * Returns the size of the largest free block in the heap.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \returns The size of the largest free block in the heap.
     *
     * \todo Implement
     */
    size_t GetLargestFreeBlockSize (void) const throw ();
    /**
     * Returns the size by which to expand when the heap is too small to
     * fulfill a memory request.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \returns The size by which to expand the heap on expansion.
     */
    void *GetExpansionSize (void) const throw ();

    /**
     * Expands the heap by the size passed into the constructor.  The heap
     * is reallocated to be larger by a certain amount.  This method is
     * usually called when the Allocate method can't find a block large
     * enough to fit a request.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \todo Implement
     *
     * \see Heap ()
     * \see Allocate ()
     */
    void Expand (void) throw ();
    
  protected:
    /**
     * Returns a pointer to a block of memory that fulfills the request, or
     * a null pointer if none can be found.
     *
     * This method is overridden in two subclasses to create the two
     * standard memory management models: GAMEENGINE_HEAP_FIRSTFIT and
     * GAMEENGINE_HEAP_BESTFIT.  You can also create a subclass for custom
     * behaviour in finding a block of free space.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \see Allocate ()
     */
    virtual void *GetContiguousSpaceOfSize (size_t size) const throw () = 0;
    /**
     * Returns an array of free memory locations in the heap.  This array is
     * dynamically calculated in this method.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \returns An array of free memory locations in the heap.
     *
     * \warning Because this array is created in this method, this method
     *          may take a while to execute.  Not much performance boost
     *          over new and delete, is there?
     */
    void **GetFreeMemoryLocations (void) const throw ();
    /**
     * Returns an array of free memory block sizes in the heap.  This array
     * is dynamically calculated in this method.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \returns An array of free memory block sizes in the heap.
     *
     * \warning Because this array is created in this method, this method
     *          may take a while to execute.  Not much performance boost
     *          over new and delete, is there?
     */
    size_t *GetFreeMomorySizes (void) const throw ();
    /**
     * Returns the pointer to the base of the heap in memory.
     *
     * \author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * \date 2009-07-24
     * \since 1.0.0.0
     *
     * \returns The pointer to the base of the heap.
     */
    void *GetHeapBase (void) const throw ();
    
  private:
    /// The pointer to the base of the heap.
    void *heapBase_;
    /// The size of the heap.
    size_t heapSize_;
    /// An array of allocated memory pointers.
    void **allocatedMemoryLocations_;
    /// An array of allocated memory sizes.
    size_t *allocatedMemorySizes_;
    /// The size by which to expand when the heap is too small.
    size_t sizeToExpandBy_;
};
}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_CORE_HEAP