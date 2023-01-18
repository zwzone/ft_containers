#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
template < class Iterator >
class reverse_iterator {
public:
  typedef Iterator                                                  iterator_type;
  typedef typename ft::iterator_traits<iterator_type>::value_type        value_type;
  typedef typename ft::iterator_traits<iterator_type>::pointer           pointer;
  typedef typename ft::iterator_traits<iterator_type>::reference         reference;
  typedef typename ft::iterator_traits<iterator_type>::difference_type   difference_type;
  typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;

private:
  iterator_type _it;

public:
  // ========>> Default Constructor <<========
  reverse_iterator ( )
  : _it()
  { }

  // ========>> Copy Constructor <<========
  template < class Iter >
  reverse_iterator ( const reverse_iterator<Iter> & copy )
  : _it(copy.base())
  { }

  // ========>> Custom Constructor <<========
  reverse_iterator ( iterator_type it )
  : _it(it)
  { }

  // ========>> Copy Assignment Operator <<========
  template < class U >
  reverse_iterator &operator= ( const reverse_iterator<U> & copy )
  { _it = copy.base(); return (*this); }

  // ========>> Destructor <<========
  ~reverse_iterator ( )
  { }

  // ========>> Base <<========
  iterator_type base() const { return (_it); }

  // ========>> Dereferencing <<========
  reference       operator*  ()       { iterator_type it(_it); return (*(--it)); }
  const reference operator*  () const { iterator_type it(_it); return (*(--it)); }
  pointer         operator-> ()       { return (&operator*()); }
  const pointer   operator-> () const { return (&operator*()); }

  // ========>> Increment Operators <<========
  reverse_iterator & operator++ ()
  { --_it; return (*this); }
  reverse_iterator operator++ ( int )
  {
    reverse_iterator tmp(*this);
    ++(*this);
    return (tmp);
  }

  // ========>> Decrement Operators <<========
  reverse_iterator & operator-- ()
  { ++_it; return (*this); }
  reverse_iterator operator-- ( int )
  {
    reverse_iterator tmp(*this);
    --(*this);
    return (tmp);
  }

  // ========>> Arithmetic Operators <<========
  reverse_iterator operator- ( const difference_type & n ) const
  { return (reverse_iterator(_it + n)); }
  template < class Iter1, class Iter2 >
  friend reverse_iterator::difference_type operator- ( const reverse_iterator<Iter1> & lhs, const reverse_iterator<Iter2> & rhs )
  { return (rhs._it - lhs._it); }

  reverse_iterator operator+ ( const difference_type & n ) const
  { return (reverse_iterator(_it - n)); }
  friend reverse_iterator operator+ ( typename reverse_iterator::difference_type n, const reverse_iterator & rIt )
  { return (rIt + n); }

  reverse_iterator & operator-= ( const difference_type & n )      { _it += n; return (*this); }
  reverse_iterator & operator+= ( const difference_type & n )      { _it -= n; return (*this); }

  // ========>> Offset dereference operator <<========
  reference       operator[] ( const difference_type & n )       { return (*(_it - n - 1)); }
  const reference operator[] ( const difference_type & n ) const { return (*(_it - n - 1)); }
};

// ========>> Relational Operators <<========
template < class rIter1, class rIter2 > bool operator== ( const reverse_iterator<rIter1> & lhs, const reverse_iterator<rIter2> & rhs ) { return (lhs.base() == rhs.base()); }
template < class rIter1, class rIter2 > bool operator!= ( const reverse_iterator<rIter1> & lhs, const reverse_iterator<rIter2> & rhs ) { return (lhs.base() != rhs.base()); }
template < class rIter1, class rIter2 > bool operator<  ( const reverse_iterator<rIter1> & lhs, const reverse_iterator<rIter2> & rhs ) { return (lhs.base() >  rhs.base()); }
template < class rIter1, class rIter2 > bool operator>  ( const reverse_iterator<rIter1> & lhs, const reverse_iterator<rIter2> & rhs ) { return (lhs.base() <  rhs.base()); }
template < class rIter1, class rIter2 > bool operator<= ( const reverse_iterator<rIter1> & lhs, const reverse_iterator<rIter2> & rhs ) { return (lhs.base() >= rhs.base()); }
template < class rIter1, class rIter2 > bool operator>= ( const reverse_iterator<rIter1> & lhs, const reverse_iterator<rIter2> & rhs ) { return (lhs.base() <= rhs.base()); }
}

#endif
