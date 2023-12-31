/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_tree.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:27:54 by zwina             #+#    #+#             */
/*   Updated: 2023/01/19 10:28:00 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TREE_HPP
#define ITERATOR_TREE_HPP

#include "iterator_traits.hpp"

namespace ft
{
template < class T, class Node>
class iterator_tree : public ft::iterator<std::bidirectional_iterator_tag, T> {
public:
  using typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type;
  using typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer;
  using typename ft::iterator<std::bidirectional_iterator_tag, T>::reference;
  using typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type;
  using typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category;
  typedef Node *        nodePointer;

private:
  nodePointer const * _root;
  nodePointer   _p;

public:
  // ========>> Default Constructor <<========
  iterator_tree ( nodePointer * root = nullptr )
  : _root(root) , _p(nullptr)
  { }

  // ========>> Copy Constructor <<========
  iterator_tree ( const iterator_tree & copy )
  : _root(copy.baseRoot()) , _p(copy.base())
  { }

  // ========>> Custom Constructor <<========
  iterator_tree ( nodePointer const * root, nodePointer p ) : _root(root) , _p(p)
  { }

  // ========>> Copy Assignment Operator <<========
  iterator_tree &operator= ( const iterator_tree & copy )
  { _root = copy.baseRoot(); _p = copy.base(); return (*this); }

  // ========>> Destructor <<========
  ~iterator_tree()
  { }

  // ========>> Converter <<========
  operator iterator_tree<const T, Node>() { return iterator_tree<const T, Node>(_root, _p); }

  // ========>> Base <<========
  nodePointer const * baseRoot() const { return (_root); }
  nodePointer   base() const           { return (_p); }

  // ========>> Dereferencing <<========
  reference       operator* ()        { return (*_p->_value); }
  const reference operator* () const  { return (*_p->_value); }
  pointer         operator-> ()       { return (&operator*()); }
  const pointer   operator-> () const { return (&operator*()); }

  // ========>> Increment Operators <<========
  iterator_tree & operator++ () {
    if ( _p == nullptr ) {
      _p = *_root;
      while (_p && _p->_left)
        _p = _p->_left;
    } else if ( _p->_right ) {
      _p = _p->_right;
      while (_p->_left)
        _p = _p->_left;
    } else {
      while (_p && _p->_isRight)
        _p = _p->_parent;
      if (_p) _p = _p->_parent;
    }
    return (*this);
  }
  iterator_tree operator++ ( int ) {
    iterator_tree tmp(*this);
    ++(*this);
    return (tmp);
  }

  // ========>> Decrement Operators <<========
  iterator_tree & operator-- () {
    if ( _p == nullptr ) {
      _p = *_root;
      while (_p && _p->_right)
        _p = _p->_right;
    } else if ( _p->_left ) {
      _p = _p->_left;
      while (_p->_right)
        _p = _p->_right;
    } else {
      while (_p && !_p->_isRight)
        _p = _p->_parent;
      if (_p) _p = _p->_parent;
    }
    return (*this);
  }
  iterator_tree operator-- ( int ) {
    iterator_tree tmp(*this);
    --(*this);
    return (tmp);
  }
};

// ========>> Relational Operators <<========
template < class Itr1, class Node1, class Itr2, class Node2 > bool operator== ( const iterator_tree<Itr1, Node1> & lhs, const iterator_tree<Itr2, Node2> & rhs ) { return (lhs.base() == rhs.base()); }
template < class Itr1, class Node1, class Itr2, class Node2 > bool operator!= ( const iterator_tree<Itr1, Node1> & lhs, const iterator_tree<Itr2, Node2> & rhs ) { return (lhs.base() != rhs.base()); }
}

#endif
