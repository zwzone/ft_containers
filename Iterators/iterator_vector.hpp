#ifndef ITERATOR_VECTOR_HPP
#define ITERATOR_VECTOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
template< class InputIt >
typename ft::iterator_traits<InputIt>::difference_type
distance( InputIt first, InputIt last )
{
  typename ft::iterator_traits<InputIt>::difference_type result = 0;
  while (first != last) { ++first; ++result; }
  return (result);
}

template < class T >
class iterator_vector : public ft::iterator<std::random_access_iterator_tag, T> {
public:
  using typename ft::iterator<std::random_access_iterator_tag, T>::value_type;
  using typename ft::iterator<std::random_access_iterator_tag, T>::pointer;
  using typename ft::iterator<std::random_access_iterator_tag, T>::reference;
  using typename ft::iterator<std::random_access_iterator_tag, T>::difference_type;
  using typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category;

private:
  pointer _p;

public:
  // ========>> Default Constructor <<========
  iterator_vector ( )
  : _p(nullptr)
  { }

  // ========>> Copy Constructor <<========
  template < class U >
  iterator_vector ( const iterator_vector<U> & copy )
  : _p(copy.base())
  { }

  // ========>> Custom Constructor <<========
  iterator_vector ( const pointer p )
  : _p(p)
  { }
  iterator_vector ( const reference r )
  : _p(&r)
  { }

  // ========>> Copy Assignment Operator <<========
  template < class U >
  iterator_vector &operator= ( const iterator_vector<U> & copy )
  { _p = copy.base(); return (*this); }

  // ========>> Destructor <<========
  ~iterator_vector ( )
  { }

  // ========>> Base <<========
  pointer base() const { return (_p); }

  // ========>> Dereferencing <<========
  reference       operator* ()        { return (*_p); }
  const reference operator* () const  { return (*_p); }
  pointer         operator-> ()       { return (_p); }
  const pointer   operator-> () const { return (_p); }

  // ========>> Increment Operators <<========
  iterator_vector & operator++ ()
  { ++_p; return (*this); }
  iterator_vector operator++ ( int )
  {
    iterator_vector tmp(*this);
    ++(*this);
    return (tmp);
  }

  // ========>> Decrement Operators <<========
  iterator_vector & operator-- ()
  { --_p; return (*this); }
  iterator_vector operator-- ( int )
  {
    iterator_vector tmp(*this);
    --(*this);
    return (tmp);
  }

  // ========>> Arithmetic Operators <<========
  iterator_vector operator- ( const difference_type & n ) const
  { return (iterator_vector(_p - n)); }
  friend difference_type operator- ( const iterator_vector & lhs, const iterator_vector & rhs )
  { return (lhs._p - rhs._p); }

  iterator_vector operator+ ( const difference_type & n ) const
  { return (iterator_vector(_p + n)); }
  friend iterator_vector operator+ ( typename iterator_vector::difference_type n, const iterator_vector & it )
  { return (it + n); }

  iterator_vector & operator-= ( const difference_type & n )
  { _p -= n; return (*this); }
  iterator_vector & operator+= ( const difference_type & n )
  { _p += n; return (*this); }

  // ========>> Offset dereference operator <<========
  reference       operator[] ( const difference_type & n )       { return (*(_p + n)); }
  const reference operator[] ( const difference_type & n ) const { return (*(_p + n)); }
};

// ========>> Relational Operators <<========
template < class Itr1, class Itr2 > bool operator== ( const iterator_vector<Itr1> & lhs, const iterator_vector<Itr2> & rhs ) { return (lhs.base() == rhs.base()); }
template < class Itr1, class Itr2 > bool operator!= ( const iterator_vector<Itr1> & lhs, const iterator_vector<Itr2> & rhs ) { return (lhs.base() != rhs.base()); }
template < class Itr1, class Itr2 > bool operator>  ( const iterator_vector<Itr1> & lhs, const iterator_vector<Itr2> & rhs ) { return (lhs.base() >  rhs.base()); }
template < class Itr1, class Itr2 > bool operator<  ( const iterator_vector<Itr1> & lhs, const iterator_vector<Itr2> & rhs ) { return (lhs.base() <  rhs.base()); }
template < class Itr1, class Itr2 > bool operator>= ( const iterator_vector<Itr1> & lhs, const iterator_vector<Itr2> & rhs ) { return (lhs.base() >= rhs.base()); }
template < class Itr1, class Itr2 > bool operator<= ( const iterator_vector<Itr1> & lhs, const iterator_vector<Itr2> & rhs ) { return (lhs.base() <= rhs.base()); }
}

#endif
