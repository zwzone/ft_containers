/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:26:52 by zwina             #+#    #+#             */
/*   Updated: 2023/01/19 10:26:53 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "Iterators/iterator_tree.hpp"
#include "Iterators/reverse_iterator.hpp"
#include "red_black_tree.hpp"

#define SFINAAE(X) typename ft::enable_if<!ft::is_integral<X>::value, X>::type* = 0

namespace ft
{
template
<
class Key,
class T,
class Compare = std::less<Key>,
class Alloc = std::allocator< ft::pair<const Key,T> >
>
class map {
public:
  typedef Key                                           key_type;
  typedef T                                             mapped_type;
  typedef ft::pair<const key_type, mapped_type>         value_type;
  typedef Alloc                                         allocator_type;
  typedef Compare                                       key_compare;
  struct                                                value_compare;
  typedef typename allocator_type::reference            reference;
  typedef typename allocator_type::const_reference      const_reference;
  typedef typename allocator_type::pointer              pointer;
  typedef typename allocator_type::const_pointer        const_pointer;
  typedef typename allocator_type::difference_type      difference_type;
  typedef typename allocator_type::size_type            size_type;
private:
  typedef typename RedBlackTree<map>::Node Node;
public:
  typedef ft::iterator_tree<value_type, Node>            iterator;
  typedef ft::iterator_tree<const value_type, Node>      const_iterator;
  typedef ft::reverse_iterator<iterator>                reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>          const_reverse_iterator;

private:
  key_compare         _comp;
  allocator_type      _alloc;
  RedBlackTree< map > _tree;

public:
  // [*] // explicit map ( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() );
  // [*] // template < class InputIterator > map ( InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() );
  // [*] // map ( const map& x );
  // [*] // map& operator=( const map& other );
  // [*] // ~map ( );
  // [*] // allocator_type get_allocator() const;
  explicit map ( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
    : _comp ( comp )
    , _alloc ( alloc )
    , _tree ( _comp, _alloc )
  { }
  template < class InputIterator >
  map ( InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), SFINAAE( InputIterator ) )
    : _comp ( comp )
    , _alloc ( alloc )
    , _tree ( _comp, _alloc )
  {
    while (first != last)
      insert(*(first++));
  }
  map ( const map& x )
    : _comp ( x._comp )
    , _alloc ( x._alloc )
    , _tree ( x._tree )
  { }
  map& operator=( const map& x )
  {
    _tree = x._tree;
    return (*this);
  }
  ~map ( ) { }
  allocator_type get_allocator ( ) const { return (_alloc); }

  // [*] // key_compare key_comp() const
  // [*] / value_compare value_comp() const;
  key_compare key_comp() const
  {
    return (_comp);
  }
  value_compare value_comp() const
  {
    return (_comp);
  }

  // [*] // mapped_type& at (const key_type& k);
  // [*] // const mapped_type& at (const key_type& k) const;
  // [*] // mapped_type& operator[] (const key_type& k);
  mapped_type& at (const key_type& k)
  {
    Node * findNode = _tree.find(k);
    if ( findNode )
      return (findNode->_value->second);
    else
      throw (std::out_of_range("map::at : key not found"));
  }
  const mapped_type& at (const key_type& k) const
  {
    Node * findNode = _tree.find(k);
    if ( findNode )
      return (findNode->_value->second);
    else
      throw (std::out_of_range("map::at : key not found"));
  }
  mapped_type& operator[] (const key_type& k)
  {
    return (insert(ft::make_pair<key_type, mapped_type>(k, mapped_type())).first->second);
  }


  // [*] // iterator begin ( );
  // [*] // const_iterator begin ( ) const;
  // [*] // iterator end ( );
  // [*] // const_iterator end ( ) const;
  //
  // [*] // reverse_iterator rbegin ( );
  // [*] // const_reverse_iterator rbegin ( ) const;
  // [*] // reverse_iterator rend ( );
  // [*] // const_reverse_iterator rend ( ) const;
  iterator       begin ( )       { return (iterator(_tree.base(), _tree.smallest())); }
  const_iterator begin ( ) const { return (const_iterator(_tree.base(), _tree.smallest())); }
  iterator       end ( )         { return (iterator(_tree.base(), nullptr)); }
  const_iterator end ( ) const   { return (const_iterator(_tree.base(), nullptr)); }

  reverse_iterator       rbegin ( )       { return (reverse_iterator(this->end())); }
  const_reverse_iterator rbegin ( ) const { return (const_reverse_iterator(this->end())); }
  reverse_iterator       rend ( )         { return (reverse_iterator(this->begin())); }
  const_reverse_iterator rend ( ) const   { return (const_reverse_iterator(this->begin())); }

  // [*] // bool empty ( ) const;
  // [*] // size_type size ( ) const;
  // [*] // size_type max_size ( ) const;
  bool empty ( ) const { return (this->size() == 0); }
  size_type size ( ) const { return (_tree.size()); }
  size_type max_size ( ) const { return (_alloc.max_size()); }


  // [*] // pair<iterator,bool> insert ( const value_type& val );
  // [*] // iterator insert ( iterator position, const value_type& val );
  // [*] // template < class InputIterator > void insert ( InputIterator first, InputIterator last );
  pair<iterator,bool> insert ( const value_type& val )
  {
    iterator it = find(val.first);
    if ( it != end() )
      return (ft::make_pair<iterator,bool>(it, false));
    it = iterator(_tree.base(), _tree.add(val));
    return (ft::make_pair<iterator,bool>(it, true));
  }
  iterator insert ( iterator position, const value_type& val )
  {
    (void)position;
    return (this->insert(val).first);
  }
  template < class InputIterator >
  void insert ( InputIterator first, InputIterator last, SFINAAE( InputIterator ) )
  {
    while (first != last)
      this->insert(*(first++));
  }

  // [*] // size_type erase ( const key_type& k );
  // [*] // void erase ( iterator position );
  // [*] // void erase ( iterator first, iterator last );
  size_type erase ( const key_type& k )
  { return (_tree._erase(k)); }
  void erase ( iterator position )
  { _tree._erase((*position).first); }
  void erase ( iterator first, iterator last )
  {
    while (first != last) {
      _tree._erase((*(first++)).first);
    }
  }

  // [*] // void swap ( map& x );
  void swap ( map& x )
  { _tree.swap(x._tree); }

  // [*] // void clear ( );
  void clear ( ) { _tree.clear(); }

  // [*] // iterator find (const key_type& k);
  // [*] // const_iterator find (const key_type& k) const;
  // [*] // size_type count( const key_type& k ) const;
  iterator find (const key_type& k)
  {
    return (iterator(_tree.base(), _tree.find(k)));
  }
  const_iterator find (const key_type& k) const
  {
    return (const_iterator(_tree.base(), _tree.find(k)));
  }
  size_type count( const key_type& k ) const
  {
    const_iterator it = find(k);
    if (it == end())
      return (0);
    return (1);
  }

  // [*] // iterator lower_bound (const key_type& k);
  // [*] // const_iterator lower_bound (const key_type& k) const;
  iterator lower_bound (const key_type& k)
  {
    Node * node = *_tree.base();
    while (node) {
      if (node->_right && _comp(node->_value->first, k)) {
        node = node->_right;
      } else if (node->_left && _comp(k, node->_value->first)) {
        node = node->_left;
      } else break;
    }
    iterator it = iterator(_tree.base(), node);
    if (it != end() && _comp((*it).first, k))
      ++it;
    return (it);
  }
  const_iterator lower_bound (const key_type& k) const
  {
    Node * node = *_tree.base();
    while (node) {
      if (node->_right && _comp(node->_value->first, k)) {
        node = node->_right;
      } else if (node->_left && _comp(k, node->_value->first)) {
        node = node->_left;
      } else break;
    }
    const_iterator it = iterator(_tree.base(), node);
    if (it != end() && _comp((*it).first, k))
      ++it;
    return (it);
  }

  // [*] // iterator upper_bound (const key_type& k);
  // [*] // const_iterator upper_bound (const key_type& k) const;
  iterator upper_bound (const key_type& k)
  {
    Node * node = *_tree.base();
    while (node) {
      if (node->_right && _comp(node->_value->first, k)) {
        node = node->_right;
      } else if (node->_left && _comp(k, node->_value->first)) {
        node = node->_left;
      } else break;
    }
    iterator it = iterator(_tree.base(), node);
    if (it != end() && !_comp(k, (*it).first))
      ++it;
    return (it);
  }
  const_iterator upper_bound (const key_type& k) const
  {
    Node * node = *_tree.base();
    while (node) {
      if (node->_right && _comp(node->_value->first, k)) {
        node = node->_right;
      } else if (node->_left && _comp(k, node->_value->first)) {
        node = node->_left;
      } else break;
    }
    const_iterator it = iterator(_tree.base(), node);
    if (it != end() && !_comp(k, (*it).first))
      ++it;
    return (it);
  }

  // [*] // pair<iterator,iterator>             equal_range (const key_type& k);
  // [*] // pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
  pair<iterator,iterator> equal_range (const key_type& k)
  { return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k))); }
  pair<const_iterator,const_iterator> equal_range (const key_type& k) const
  { return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k))); }

public:
  struct value_compare {
  public:
    typedef bool result_type;

    Compare comp;
    value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

    result_type operator() (const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
    result_type operator() (const key_type& x, const key_type& y) const {
      return comp(x, y);
    }
    result_type operator() (const value_type& x, const key_type& y) const {
      return comp(x.first, y);
    }
    result_type operator() (const key_type& x, const value_type& y) const {
      return comp(x, y.first);
    }
  };
};

template< class Key, class T, class Compare, class Alloc >
void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
{
  x.swap(y);
}

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
  if (lhs.size() != rhs.size()) return (false);
  typedef typename ft::map<Key,T,Compare,Alloc>::const_iterator const_iterator;
  const_iterator lbIt = lhs.begin();
  const_iterator leIt = lhs.end();
  const_iterator rbIt = rhs.begin();
  return (ft::equal(lbIt, leIt, rbIt));
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
  if (lhs.size() != rhs.size()) return (true);
  typedef typename ft::map<Key,T,Compare,Alloc>::const_iterator const_iterator;
  const_iterator lbIt = lhs.begin();
  const_iterator leIt = lhs.end();
  const_iterator rbIt = rhs.begin();
  return (!ft::equal(lbIt, leIt, rbIt));
}

template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
  typedef typename ft::map<Key,T,Compare,Alloc>::const_iterator const_iterator;
  const_iterator lbIt = lhs.begin();
  const_iterator leIt = lhs.end();
  const_iterator rbIt = rhs.begin();
  const_iterator reIt = rhs.end();
  return (ft::lexicographical_compare(lbIt, leIt, rbIt, reIt) && lhs != rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
  typedef typename ft::map<Key,T,Compare,Alloc>::const_iterator const_iterator;
  const_iterator lbIt = lhs.begin();
  const_iterator leIt = lhs.end();
  const_iterator rbIt = rhs.begin();
  const_iterator reIt = rhs.end();
  return (!ft::lexicographical_compare(lbIt, leIt, rbIt, reIt) && lhs != rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
  return (lhs < rhs || lhs == rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
  return (lhs > rhs || lhs == rhs);
}
}

#endif
