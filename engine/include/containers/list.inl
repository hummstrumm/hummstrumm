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


#ifndef HUMMSTRUMM_ENGINE_CONTAINERS_LIST_INL
#define HUMMSTRUMM_ENGINE_CONTAINERS_LIST_INL

namespace hummstrumm
{
namespace engine
{
namespace containers
{


HUMMSTRUMM_IMPLEMENT_GENERIC_TYPE (template <typename T>,
                                   hummstrumm::engine::containers::List<T>,
                                   hummstrumm::engine::core::Object);


template <typename T>
List<T>::Node::Node (T &data,
                     Node *previousNode,
                     Node *nextNode)
  : data (data),
    previous (previousNode),
    next (nextNode)
{
  if (this->previous)
    {
      this->previous->next = this;
    }
  if (this->next)
    {
      this->next->previous = next;
    }
}


template <typename T>
List<T>::Node::~Node (void)
{
  // Stitch up the whole;
  if (this->previous)
    {
      this->previous->next = this->next;
    }
  if (this->next)
    {
      this->next->previous = this->previous;
    }
}


template <typename T>
List<T>::Iterator::Iterator (const Node *node, const Ptr list)
  : node (node),
    list (list)
{}


template <typename T>
List<T>::Iterator::Iterator (const Iterator &iterator)
  : node (iterator->node),
    list (iterator->list)
{}


template <typename T>
List<T>::Iterator::~Iterator (void)
{}


template <typename T>
T &
List<T>::Iterator::operator* (void)
  const throw ()
{
  return this->node;
}


template <typename T>
void
List<T>::Iterator::operator++ (void)
  throw ()
{
  this->node = this->node->next;
}


template <typename T>
void
List<T>::Iterator::operator++ (int)
  throw ()
{
  this->node = this->node->next;
}


template <typename T>
void
List<T>::Iterator::operator-- (void)
  throw ()
{
  this->node = this->node->previous;
}

template <typename T>
void
List<T>::Iterator::operator-- (int)
  throw ()
{
  this->node = this->node->previous;
}


template <typename T>
List<T>::List (void)
  : head (0),
    tail (0)
{}


template <typename T>
List<T>::~List (void)
{
  for (List<T>::Iterator iterator (GetHead ());
       iterator != GetTail ();)
    {
      List<T>::Iterator toDelete (iterator);
      iterator++;
      Delete (toDelete);
    }
}


template <typename T>
typename List<T>::Iterator
List<T>::GetHead (void)
  const throw ()
{
  return List<T>::Iterator (this->head, GetPointer ());
}


template <typename T>
typename List<T>::Iterator
List<T>::GetTail (void)
  const throw ()
{
  return List<T>::Iterator (this->tail, GetPointer ());
}


template <typename T>
void
List<T>::Insert (T &data, const Iterator &nodeAfter)
  throw ()
{
  // Everything takes place in the constructor.
  Node *newNode = new Node (data, nodeAfter->node->previous, nodeAfter->node);
  // ...but we had better update ourselves.
  if (!newNode->previous)
    {
      this->head = newNode;
    }
  if (!newNode->next)
    {
      this->tail = newNode;
    }
}


template <typename T>
void
List<T>::Delete (const Iterator &iterator)
  throw ()
{
  // Update our head and tail nodes.
  if (this->tail == iterator->node)
    {
      this->tail = iterator->node->previous;
    }
  if (this->head == iterator->node)
    {
      this->head = iterator->node->next;
    }
  
  delete iterator->node;  // Clean up takes place in the destructor.
}


template <typename T>
hummstrumm::engine::types::Number
List<T>::Size (void)
  const throw ()
{
  hummstrumm::engine::types::Number count (0);
  for (List<T>::Iterator iterator = GetHead ();
       iterator != GetTail ();
       ++iterator, ++count);
  return count;
}


#ifdef HUMMSTRUMM_ENABLE_PRINTDEBUG
template <typename T>
void
List<T>::PrintDebug (void)
  const throw ()
{
  std::cout << "Printing debug output of list...\n";
  for (List<T>::Iterator iterator = GetHead ();
       iterator != GetTail ();
       iterator++)
    {
      std::cout << "\t" << *iterator;
    }
}


template <typename T>
void
List<T>::LogDebug (void)
  const throw ()
{
  hummstrumm::engine::types::String message
    ("Printing debug output of list...\n");
  
  for (List<T>::Iterator iterator = GetHead ();
       iterator != GetTail ();
       iterator++)
    {
      message += "\t";
      message += *iterator;
    }

  LOG (message.ToWchar_t (), MESSAGE);
}
#endif // #ifdef HUMMSTRUMM_ENABLE_PRINTDEBUG


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_CONTAINERS_LIST_INL
