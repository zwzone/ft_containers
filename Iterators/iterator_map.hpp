#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

namespace ft
{
  template < class T, class Node>
    class iterator_map : public ft::iterator<bidirectional_iterator_tag, T>
  {
    public:
      using typename ft::iterator<bidirectional_iterator_tag, T>::value_type;
      using typename ft::iterator<bidirectional_iterator_tag, T>::pointer;
      using typename ft::iterator<bidirectional_iterator_tag, T>::reference;
      using typename ft::iterator<bidirectional_iterator_tag, T>::difference_type;
      using typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category;
      typedef Node *        nodePointer;

    private:
      nodePointer * _root;
      nodePointer   _p;

    public:
      // ========>> Default Constructor <<========
      iterator_map ( nodePointer * root )
        : _root(root) , _p(nullptr)
      { }

      // ========>> Copy Constructor <<========
      template < class U, class tmpNode >
        iterator_map ( const iterator_map<U, tmpNode > & copy )
          : _root(copy.baseRoot()) , _p(copy.base())
        { }

      // ========>> Custom Constructor <<========
      iterator_map ( nodePointer * root, nodePointer p ) : _root(root) , _p(p)
      { }

      // ========>> Copy Assignment Operator <<========
      template < class U, class tmpNode >
        iterator_map &operator= ( const iterator_map<U, tmpNode > & copy )
        { _root = copy.baseRoot(); _p = copy.base(); return (*this); }

      // ========>> Destructor <<========
      ~iterator_map()
      { }

      // ========>> Base <<========
      nodePointer * baseRoot() const { return (_root); }
      nodePointer   base() const     { return (_p); }

      // ========>> Dereferencing <<========
      reference       operator* ()        { return (_p->_value); }
      const reference operator* () const  { return (_p->_value); }
      pointer         operator-> ()       { return (&operator*()); }
      const pointer   operator-> () const { return (&operator*()); }

      // ========>> Increment Operators <<========
      iterator_map & operator++ ()
      {
        if ( _p == nullptr )
        {
          _p = *_root;
          while (_p && _p->_left)
            _p = _p->_left;
        }
        else if ( _p->_right )
        {
          _p = _p->_right;
          while (_p->_left)
            _p = _p->_left;
        }
        else if ( _p->_parent )
        {
          if (_p->_isRight)
          {
            while (_p && _p->_isRight)
              _p = _p->_parent;
          }
          if (_p) _p = _p->_parent;
        }
        return (*this);
      }
      iterator_map operator++ ( int )
      {
        iterator_map tmp(*this);
        ++(*this);
        return (tmp);
      }

      // ========>> Decrement Operators <<========
      iterator_map & operator-- ()
      {
        if ( _p == nullptr )
        {
          _p = *_root;
          while (_p && _p->_right)
            _p = _p->_right;
        }
        if ( _p->_left )
        {
          _p = _p->_left;
          while (_p->_right)
            _p = _p->_right;
        }
        else if ( _p->_parent )
        {
          if (!_p->_isRight)
          {
            while (_p && !_p->isRight)
              _p = _p->_parent;
          }
          if (_p) _p = _p->_parent;
        }
        return (*this);
      }
      iterator_map operator-- ( int )
      {
        iterator_map tmp(*this);
        --(*this);
        return (tmp);
      }
  };

  // ========>> Relational Operators <<========
  template < class Itr1, class Node1, class Itr2, class Node2 >
    bool operator== ( const iterator_map<Itr1, Node1> & lhs, const iterator_map<Itr2, Node2> & rhs )
    { return (lhs.base() == rhs.base()); }
  template < class Itr1, class Node1, class Itr2, class Node2 >
    bool operator!= ( const iterator_map<Itr1, Node1> & lhs, const iterator_map<Itr2, Node2> & rhs )
    { return (lhs.base() != rhs.base()); }
}

#endif
