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

/**
 * Defines a base class for accessors.
 *
 * @file   accessors/accessor.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2011-03-01
 * @see    Accessor
 */

#ifndef HUMMSTRUMM_ENGINE_ACCESSORS_ACCESSOR
#define HUMMSTRUMM_ENGINE_ACCESSORS_ACCESSOR

namespace hummstrumm
{
namespace engine
{
namespace accessors
{

/**
 * The base class for all accessors.  An accessor is a class that allows access
 * to the members of an arbitrary data structure.  They support a superset of
 * the operations that an iterator does, and thus support more complex data
 * structures, like graphs and certain types of trees.  The interface is
 * slightly more complex than that of Iterator, and so whenever possible and
 * applicable, you should use Iterator objects.
 *
 * Accessor objects function as pointers to nodes in an arbitrary graph.  They
 * are able to traverse the edges connecting nodes in the data structure.  These
 * edges are abstractions of a data structure's connections or ordering.  In a
 * linked list iterator, for example, each node has two edges: one leading to
 * the previous list node and one leading to the next node.  While in an
 * Iterator, these distinctions would be easily exposed, the Accessor's API
 * would label one of these edges as edge 0 and one as edge 1, as defined in the
 * documentation.
 *
 * Accessors may be read-only or read-write, determined by whether the DataType
 * is const or not.
 * 
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2011-03-14
 * @since  0.3
 */
template <typename DataType>
class Accessor
{
    HUMMSTRUMM_DECLARE_TYPE (Accessor);
  protected:
    /**
     * Creates a new Accessor.  Only containers should be able to make Accessor
     * objects, not the user, so this is protected.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-03-18
     * @since  0.3
     */
    Accessor (void);
    
  public:
    /**
     * Creates an Accessor that is a copy of an existing Accessor.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-03-18
     * @since  0.3
     *
     * @param [in] accessor Another Accessor to copy into a new Accessor.
     */
    Accessor (const Accessor &accessor)
      throw ();

    /**
     * Returns whether a specified number edge exists from the node referenced
     * by this Accessor in the data structure.  Edges are directional, so in a
     * data structure in which node connections are not two-way, no edge will
     * register on the receiving end of the connection.
     *
     * Indexes of edges are enumerated starting with 0.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-03-20
     * @since  0.3
     *
     * @param [in] edge An edge index for whose existance we want to check.
     */
    virtual bool HasEdge (hummstrumm::engine::types::Number edge)
      const throw () = 0;
    /**
     * Returns the number of edges from the current node in a data structure.
     * This method gives a value of one plus the highest edge index.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-05-04
     * @since  0.3
     *
     * @return The number of edges leading from the currently referenced node.
     */
    virtual int GetNumberOfEdges (void)
      const throw () = 0;
    /**
     * Traverses a specified number edge from the node referenced by this
     * Accessor in the data structure.  If the edge requested does not exist, as
     * determined in the HasEdge() method, the Accessor does not change.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-03-20
     * @since  0.3
     *
     * @todo We probably want to throw an exception or something if there is no
     * edge we can follow.  That would be nicer to the programmer.
     */
    virtual void FollowEdge (hummstrumm::engine::types::Number edge)
      throw () = 0;
    /**
     * Returns a reference to the data element currently referenced by this
     * Accessor.  If DataType is const, this will be read-only; otherwise, it
     * will be read-write.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-03-20
     * @since  0.3
     */
    virtual DataType &Get (void)
      const throw () = 0;

    /**
     * Returns a reference to the data element currently referenced by this
     * Accessor.  If DataType is const, this will be read-only; otherwise, it
     * will be read-write.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-03-20
     * @since  0.3
     */
    DataType &operator* (void)
      const throw () = 0;
    /**
     * Accesses a method of the data element currently referenced by this
     * Accessor.  If DataType is const, this can only access const methods of
     * the data element; otherwise, all public methods can be accessed.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-03-20
     * @since  0.3
     */
    DataType *operator-> (void)
      const throw () = 0;
};


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_ACCESSORS_ACCESSOR
