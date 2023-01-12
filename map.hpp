#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <memory>
#include "Iterators/reverse_iterator.hpp"
#include "Iterators/iterator_map.hpp"
#include "utilities/red_black_tree.hpp"
#include "utilities/pair.hpp"
#include "utilities/enable_if.hpp"
#include "utilities/is_integral.hpp"

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
    class map
    {
      private:
        struct Node;

      public:
        typedef Key                                           key_type;
        typedef T                                             mapped_type;
        typedef ft::pair<const key_type, mapped_type>         value_type;
        typedef Compare                                       key_compare;
        typedef Compare                                       value_compare;
        typedef Alloc                                         allocator_type;
        typedef typename Alloc::template rebind<Node>::other  allocator_node_type;
        typedef typename allocator_type::reference            reference;
        typedef typename allocator_type::const_reference      const_reference;
        typedef typename allocator_type::pointer              pointer;
        typedef typename allocator_type::const_pointer        const_pointer;
        typedef typename allocator_type::difference_type      difference_type;
        typedef typename allocator_type::size_type            size_type;
        typedef ft::iterator_map<value_type, Node>            iterator;
        typedef ft::iterator_map<const value_type, Node>      const_iterator;
        typedef ft::reverse_iterator<iterator>                reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>          const_reverse_iterator;

      private:
        key_compare           _comp;
        allocator_type        _alloc;
        allocator_node_type   _alloc_node;
        RedBlackTree< Node >  _tree;

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
          , _alloc_node ( alloc )
          , _tree ( _comp, _alloc, _alloc_node )
        { }
        template < class InputIterator >
          map ( InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), SFINAAE(InputIterator) )
          : _comp ( comp )
          , _alloc ( alloc )
          , _alloc_node ( alloc )
          , _tree ( _comp, _alloc, _alloc_node )
        {
          while (first != last)
            insert(*(first++));
        }
        map ( const map& x )
          : _comp ( x._comp )
          , _alloc ( x._alloc )
          , _alloc_node ( x._alloc_node )
          , _tree ( x._tree )
        { }
        map& operator=( const map& x )
        {
          _tree = x._tree;
          return (*this);
        }
        ~map ( ) { }
        allocator_type get_allocator ( ) const { return (_alloc); }


        // [*] // mapped_type& at (const key_type& k);
        // [*] // const mapped_type& at (const key_type& k) const;
        // [*] // mapped_type& operator[] (const key_type& k);
        mapped_type& at (const key_type& k)
        {
          Node * findNode = _tree.find(k);
          if ( findNode )
            return (findNode->_value->second);
          else
            throw (std::out_of_range("<Something>"));
        }
        const mapped_type& at (const key_type& k) const
        {
          Node * findNode = _tree.find(k);
          if ( findNode )
            return (findNode->_value->second);
          else
            throw (std::out_of_range("map"));
        }
        mapped_type& operator[] (const key_type& k)
        {
          return (this->insert(ft::make_pair<key_type,mapped_type>(k, mapped_type())).first->second);
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
        const_iterator begin ( ) const { return (iterator(_tree.base(), _tree.smallest())); }
        iterator       end ( )         { return (iterator(_tree.base(), nullptr)); }
        const_iterator end ( ) const   { return (iterator(_tree.base(), nullptr)); }

        reverse_iterator       rbegin ( )       { return (reverse_iterator(this->end())); }
        const_reverse_iterator rbegin ( ) const { return (reverse_iterator(this->end())); }
        reverse_iterator       rend ( )         { return (reverse_iterator(this->begin())); }
        const_reverse_iterator rend ( ) const   { return (reverse_iterator(this->begin())); }

        // [*] // bool empty ( ) const;
        // [*] // size_type size ( ) const;
        // [*] // size_type max_size ( ) const;

        bool empty ( ) const { return (this->size() == 0); }
        size_type size ( ) const { return (_tree.size()); }
        size_type max_size ( ) const { return (_alloc.max_size()); }


        // [ ] // pair<iterator,bool> insert ( const value_type& val );
        // [ ] // iterator insert ( iterator position, const value_type& val );
        // [ ] // template < class InputIterator > void insert ( InputIterator first, InputIterator last );
        pair<iterator,bool> insert ( const value_type& val )
        {
          Node * findNode = _tree.find(val.first);
          if ( findNode )
          {
            _alloc.destroy(findNode->_value);
            _alloc.construct(findNode->_value, val);
            return (ft::make_pair<iterator,bool>(iterator(_tree.base(), findNode), false));
          }
          findNode = _tree.add(val);
          return (ft::make_pair<iterator,bool>(iterator(_tree.base(), findNode), true));
        }
        iterator insert ( iterator position, const value_type& val )
        {
          (void)position;
          return (this->insert(val).first);
        }
        template < class InputIterator > void insert ( InputIterator first, InputIterator last )
        {
          while (first != last)
            this->insert(*(first++));
        }


        // [ ] // void erase ( iterator position );
        // [ ] // size_type erase ( const key_type& k );
        // [ ] // void erase ( iterator first, iterator last );


        // [ ] // void swap ( map& x );


        // [ ] // void clear ( );
        void clear ( ) { _tree.clear(); }


        // ---------------- Node Class ----------------
      private:
        struct Node
        {
          typedef Key                                           key_type;
          typedef T                                             mapped_type;
          typedef ft::pair<const key_type, mapped_type>         value_type;

          typedef Compare                                       key_compare;
          typedef Alloc                                         allocator_type;
          typedef typename Alloc::template rebind<Node>::other  allocator_node_type;

          typedef typename allocator_type::size_type            size_type;
          typedef typename allocator_node_type::size_type       size_node_type;

          value_type          * _value;
          Node                * _left;
          Node                * _right;
          Node                * _parent;
          bool                _isRed, _isRight;

          Node (value_type * const & value = nullptr,
                Node * const & left = nullptr,
                Node * const & right = nullptr,
                Node * const & parent = nullptr,
                const bool & isRed = true,
                const bool & isRight = true)
            : _value(value)
            , _left(left)
            , _right(right)
            , _parent(parent)
            , _isRed(isRed)
            , _isRight(isRight)
          { }

          Node ( const Node & copy )
            : _value(nullptr)
            , _left(nullptr)
            , _right(nullptr)
            , _parent(nullptr)
            , _isRed(copy._isRed)
            , _isRight(copy._isRight)
          { /*std::cout << "NOOOOOOOOOOOOO COPY CONSTRUCTOOOOOOORR !" << std::endl;*/ }

          Node &operator=( const Node & copy )
          {
            _value = nullptr;
            _left = nullptr;
            _right = nullptr;
            _parent = nullptr;
            _isRed = copy._isRed;
            _isRight = copy._isRight;

            // std::cout << "NOOOOOOOOOOOOO COPY ASSIGNMENT OPERATOOOOOOOOOOORRR !" << std::endl;

            return (*this);
          }

          ~Node()
          { }

          void swapPosition ( Node * node, Node ** root )
          {
            Node * saveLeft = this->_left;
            Node * saveRight = this->_right;
            Node * saveParent = this->_parent;
            bool saveIsRed = this->_isRed;
            bool saveIsRight = this->_isRight;

            this->_left = node->_left;
            this->_right = node->_right;
            this->_parent = node->_parent;
            if ( node->_parent ) ( node->_isRight ) ? node->_parent->_right = this : node->_parent->_left = this;
            else *root = this;
            this->_isRed = node->_isRed;
            this->_isRight = node->_isRight;

            node->_left = saveLeft;
            node->_right = saveRight;
            node->_parent = saveParent;
            if ( saveParent ) ( saveIsRight ) ? saveParent->_right = node : saveParent->_left = node;
            else *root = node;
            node->_isRed = saveIsRed;
            node->_isRight = saveIsRight;
          }

          bool lessThan ( const Node * const node, const key_compare & comp )
          {
            return ( comp ( this->_value->first, node->_value->first ) );
          }
        };
    };
}

#endif
