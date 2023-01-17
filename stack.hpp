#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
template
<
class T,
class Container = ft::vector<T>
>
class stack {
public:
  typedef typename Container::value_type      value_type;
  typedef typename Container::size_type       size_type;
  typedef typename Container::reference       reference;
  typedef typename Container::const_reference const_reference;
  typedef Container                           container_type;

private:
  container_type _c;

public:
  explicit stack ( const container_type & ctnr = container_type() )
  : _c(ctnr)
  { }

  stack( const stack& other )
  : _c(other._c)
  { }

  stack& operator=( const stack & other )
  { _c = other._c; return (*this); }

  ~stack()
  { }

  bool empty() const
  { return ( _c.empty() ); }

  size_type size() const
  { return ( _c.size() ); }

  value_type&       top()
  { return ( _c.back() ); }
  const value_type& top() const
  { return ( _c.back() ); }

  void push ( const value_type& val )
  { _c.push_back( val ); }

  void pop()
  { _c.pop_back(); }

  void swap ( stack & x )
  { _c.swap(x._c); }

  template < class U, class _Container > friend bool operator== ( const stack<U,_Container>& lhs, const stack<U,_Container>& rhs );
  template < class U, class _Container > friend bool operator!= ( const stack<U,_Container>& lhs, const stack<U,_Container>& rhs );
  template < class U, class _Container > friend bool operator<  ( const stack<U,_Container>& lhs, const stack<U,_Container>& rhs );
  template < class U, class _Container > friend bool operator<= ( const stack<U,_Container>& lhs, const stack<U,_Container>& rhs );
  template < class U, class _Container > friend bool operator>  ( const stack<U,_Container>& lhs, const stack<U,_Container>& rhs );
  template < class U, class _Container > friend bool operator>= ( const stack<U,_Container>& lhs, const stack<U,_Container>& rhs );
};

template < class T, class Container > bool operator== ( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return ( lhs._c == rhs._c ); }
template < class T, class Container > bool operator!= ( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return ( lhs._c != rhs._c ); }
template < class T, class Container > bool operator<  ( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return ( lhs._c < rhs._c ); }
template < class T, class Container > bool operator<= ( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return ( lhs._c <= rhs._c ); }
template < class T, class Container > bool operator>  ( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return ( lhs._c > rhs._c ); }
template < class T, class Container > bool operator>= ( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return ( lhs._c >= rhs._c ); }
}

#endif
