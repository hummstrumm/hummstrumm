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
 * Defines a linked list data structure.
 *
 * @file   containers/list.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-06-22
 * @see    List
 */

#ifndef HUMMSTRUMM_ENGINE_CONTAINERS_LIST
#define HUMMSTRUMM_ENGINE_CONTAINERS_LIST

namespace hummstrumm
{
namespace engine
{
namespace containers
{


template <typename T>
class List
{
    HUMMSTRUMM_DECLARE_TYPE (List);
  private:
    class ServiceCentreNode;
    class Node
    {
      protected:
        Node (T &data, Node *previousNode = 0, Node *nextNode = 0);
        virtual ~Node (void);
        
        T data;
        Node *previous;
        Node *next;

        friend class List<T>;
        friend class Iterator;
    };

    class Iterator
    {
      public:
        Iterator (const Iterator &iterator);
        virtual ~Iterator (void);

        inline T &operator* (void)
          const throw ();
        
        inline void operator++ (void)
          throw ();
        inline void operator++ (int)
          throw ();
        inline void operator-- (void)
          throw ();
        inline void operator-- (int)
          throw ();
        
      private:
        Iterator (const Node *node, const Ptr list);
        
        Node *node;
        Ptr *list;

        friend class List<T>;
    };

    Node *head;
    Node *tail;

  public:
    List (void);
    virtual ~List (void);

    inline Iterator GetHead (void)
      const throw ();
    inline Iterator GetTail (void)
      const throw ();

    void Insert (T &data, const Iterator &nodeAfter)
      throw ();
    void Delete (const Iterator &iterator)
      throw ();

    hummstrumm::engine::types::Number Size (void)
      const throw ();

#ifdef HUMMSTRUMM_ENABLE_PRINTDEBUG
    void PrintDebug (void)
      const throw ();
    void LogDebug (void)
      const throw ();
#endif // #ifdef HUMMSTRUMM_ENABLE_PRINTDEBUG
};


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_CONTAINERS_LIST
