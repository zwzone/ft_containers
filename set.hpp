#ifndef SET_HPP
#define SET_HPP

#include "Iterators/iterator_tree.hpp"
#include "Iterators/reverse_iterator.hpp"
#include "red_black_tree.hpp"

#define SFINAAE(X) typename ft::enable_if<!ft::is_integral<X>::value, X>::type* = 0

namespace ft
{
template
<
class T,
class Compare = std::less<T>,
class Alloc = std::allocator<T>
>
class set {
public:
  typedef T                                             key_type;
  typedef T                                             mapped_type;
  typedef T                                             value_type;
  typedef Alloc                                         allocator_type;
  typedef Compare                                       key_compare;
  typedef Compare                                       value_compare;
  typedef typename allocator_type::reference            reference;
  typedef typename allocator_type::const_reference      const_reference;
  typedef typename allocator_type::pointer              pointer;
  typedef typename allocator_type::const_pointer        const_pointer;
  typedef typename allocator_type::difference_type      difference_type;
  typedef typename allocator_type::size_type            size_type;
private:
  typedef typename RedBlackTree<set>::Node Node;
public:
  typedef ft::iterator_tree<value_type, Node>           iterator;
  typedef ft::iterator_tree<const value_type, Node>     const_iterator;
  typedef ft::reverse_iterator<iterator>                reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>          const_reverse_iterator;

private:
  key_compare         _comp;
  allocator_type      _alloc;
  RedBlackTree< set > _tree;

public:
  // [*] // explicit set ( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() );
  // [*] // template <class InputIterator>  set ( InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() );
  // [*] // set ( const set& x );
  // [*] // set& operator=( const set& x )
  // [*] // ~set ( );
  // [*] // allocator_type get_allocator() const;
  explicit set ( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
    : _comp ( comp )
    , _alloc ( alloc )
    , _tree ( _comp, _alloc )
  { }
  template < class InputIterator >
  set ( InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
    : _comp ( comp )
    , _alloc ( alloc )
    , _tree ( _comp, _alloc )
  {
    while (first != last)
      insert(*(first++));
  }
  set ( const set& x )
    : _comp ( x._comp )
    , _alloc ( x._alloc )
    , _tree ( x._tree )
  { }
  set& operator=( const set& x )
  {
    _tree = x._tree;
    return (*this);
  }
  ~set ( ) { }
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
    iterator it = find(val);
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
  { _tree._erase((*position)); }
  void erase ( iterator first, iterator last )
  {
    while (first != last) {
      _tree._erase((*(first++)));
    }
  }

  // [*] // void swap ( map& x );
  void swap ( set& x )
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
      if (node->_right && _comp(*node->_value, k)) {
        node = node->_right;
      } else if (node->_left && _comp(k, *node->_value)) {
        node = node->_left;
      } else break;
    }
    iterator it = iterator(_tree.base(), node);
    if (it != end() && _comp((*it), k))
      ++it;
    return (it);
  }
  const_iterator lower_bound (const key_type& k) const
  {
    Node * node = *_tree.base();
    while (node) {
      if (node->_right && _comp(*node->_value, k)) {
        node = node->_right;
      } else if (node->_left && _comp(k, *node->_value)) {
        node = node->_left;
      } else break;
    }
    const_iterator it = iterator(_tree.base(), node);
    if (it != end() && _comp((*it), k))
      ++it;
    return (it);
  }

  // [*] // iterator upper_bound (const key_type& k);
  // [*] // const_iterator upper_bound (const key_type& k) const;
  iterator upper_bound (const key_type& k)
  {
    Node * node = *_tree.base();
    while (node) {
      if (node->_right && _comp(*node->_value, k)) {
        node = node->_right;
      } else if (node->_left && _comp(k, *node->_value)) {
        node = node->_left;
      } else break;
    }
    iterator it = iterator(_tree.base(), node);
    if (it != end() && !_comp(k, (*it)))
      ++it;
    return (it);
  }
  const_iterator upper_bound (const key_type& k) const
  {
    Node * node = *_tree.base();
    while (node) {
      if (node->_right && _comp(*node->_value, k)) {
        node = node->_right;
      } else if (node->_left && _comp(k, *node->_value)) {
        node = node->_left;
      } else break;
    }
    const_iterator it = iterator(_tree.base(), node);
    if (it != end() && !_comp(k, (*it)))
      ++it;
    return (it);
  }

  // [*] // pair<iterator,iterator>             equal_range (const key_type& k);
  // [*] // pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
  pair<iterator,iterator> equal_range (const key_type& k)
  { return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k))); }
  pair<const_iterator,const_iterator> equal_range (const key_type& k) const
  { return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k))); }
};

template< class T, class Compare, class Alloc >
void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
{
  x.swap(y);
}

template< class T, class Compare, class Alloc >
bool operator==( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs )
{
  if (lhs.size() != rhs.size()) return (false);
  typedef typename ft::set<T,Compare,Alloc>::const_iterator const_iterator;
  const_iterator lbIt = lhs.begin();
  const_iterator leIt = lhs.end();
  const_iterator rbIt = rhs.begin();
  return (ft::equal(lbIt, leIt, rbIt));
}

template< class T, class Compare, class Alloc >
bool operator!=( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs )
{
  if (lhs.size() != rhs.size()) return (true);
  typedef typename ft::set<T,Compare,Alloc>::const_iterator const_iterator;
  const_iterator lbIt = lhs.begin();
  const_iterator leIt = lhs.end();
  const_iterator rbIt = rhs.begin();
  return (!ft::equal(lbIt, leIt, rbIt));
}

template< class T, class Compare, class Alloc >
bool operator<( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs )
{
  typedef typename ft::set<T,Compare,Alloc>::const_iterator const_iterator;
  const_iterator lbIt = lhs.begin();
  const_iterator leIt = lhs.end();
  const_iterator rbIt = rhs.begin();
  const_iterator reIt = rhs.end();
  return (ft::lexicographical_compare(lbIt, leIt, rbIt, reIt) && lhs != rhs);
}

template< class T, class Compare, class Alloc >
bool operator>( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs )
{
  typedef typename ft::set<T,Compare,Alloc>::const_iterator const_iterator;
  const_iterator lbIt = lhs.begin();
  const_iterator leIt = lhs.end();
  const_iterator rbIt = rhs.begin();
  const_iterator reIt = rhs.end();
  return (!ft::lexicographical_compare(lbIt, leIt, rbIt, reIt) && lhs != rhs);
}

template< class T, class Compare, class Alloc >
bool operator<=( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs )
{
  return (lhs < rhs || lhs == rhs);
}

template< class T, class Compare, class Alloc >
bool operator>=( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs )
{
  return (lhs > rhs || lhs == rhs);
}
}

#endif
