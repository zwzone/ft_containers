#ifndef RED_BLACK_TREE_MAP_HPP
#define RED_BLACK_TREE_MAP_HPP

#include "iostream"
#include "utils.hpp"

namespace ft
{
template < class Node >
Node * make_node (typename Node::allocator_type & _alloc,
                  typename Node::allocator_node_type & _alloc_node,
                  const Node * node)
{
  if (node == nullptr) return (nullptr);

  typedef typename Node::size_node_type size_node_type;
  typedef typename Node::size_type      size_type;

  Node * newNode;

  newNode = _alloc_node.allocate(size_node_type(1));
  _alloc_node.construct(newNode, *node);

  newNode->_value = _alloc.allocate(size_type(1));
  _alloc.construct(newNode->_value, *node->_value);

  if (node->_right) {
    newNode->_right = make_node(_alloc, _alloc_node, node->_right);
    newNode->_right->_parent = newNode;
  }
  if (node->_left) {
    newNode->_left = make_node(_alloc, _alloc_node, node->_left);
    newNode->_left->_parent = newNode;
  }

  return (newNode);
}

template < class Node >
Node * make_node (typename Node::allocator_type & _alloc,
                  typename Node::allocator_node_type & _alloc_node,
                  const typename Node::value_type & val)
{
  typedef typename Node::size_node_type size_node_type;
  typedef typename Node::size_type      size_type;

  Node * newNode;

  newNode = _alloc_node.allocate(size_node_type(1));
  _alloc_node.construct(newNode, Node());

  newNode->_value = _alloc.allocate(size_type(1));
  _alloc.construct(newNode->_value, val);

  return (newNode);
}

template < class Node >
void remove_node (typename Node::allocator_type & _alloc,
                  typename Node::allocator_node_type & _alloc_node,
                  Node * node)
{
  if (node == nullptr) return ;

  typedef typename Node::size_node_type size_node_type;
  typedef typename Node::size_type      size_type;

  _alloc.destroy(node->_value);
  _alloc.deallocate(node->_value, size_type(1));
  if (node->_right)
    remove_node(_alloc, _alloc_node, node->_right);
  if (node->_left)
    remove_node(_alloc, _alloc_node, node->_left);
  _alloc_node.destroy(node);
  _alloc_node.deallocate(node, size_node_type(1));
}

template < typename Node >
class RedBlackTree
  {
    // ---------------- Typedefs ----------------
  public:
    typedef typename Node::key_type             key_type;
    typedef typename Node::mapped_type          mapped_type;
    typedef typename Node::value_type           value_type;

    typedef typename Node::key_compare          key_compare;
    typedef typename Node::allocator_type       allocator_type;
    typedef typename Node::allocator_node_type  allocator_node_type;

    typedef typename Node::size_type            size_type;

    // ---------------- Attributes ----------------
  private:
    key_compare         & _comp;
    allocator_type      & _alloc;
    allocator_node_type & _alloc_node;
    Node                *_root;
    size_type           _size;

    // ---------------- Constructor ----------------
  public:
    explicit RedBlackTree
    (
      key_compare & comp = key_compare(),
      allocator_type & alloc = allocator_type(),
      allocator_node_type & alloc_node = allocator_node_type()
    )
      : _comp(comp)
      , _alloc(alloc)
      , _alloc_node(alloc_node)
      , _root(nullptr)
      , _size(size_type())
    { }

    // ---------------- Copy Constructor ----------------
  public:
    RedBlackTree ( const RedBlackTree & copy )
      : _comp(copy._comp)
      , _alloc(copy._alloc)
      , _alloc_node(copy._alloc_node)
      , _root(make_node<Node>(_alloc, _alloc_node, copy._root))
      , _size(copy._size)
    { }

    // ---------------- Copy Assignment Operator ----------------
  public:
    RedBlackTree &operator=( const RedBlackTree & copy )
    {
      remove_node(_alloc, _alloc_node, _root);
      _root = make_node<Node>(_alloc, _alloc_node, copy._root);
      _size = copy._size;
      return (*this);
    }

    // ---------------- Destructor ----------------
  public:
    ~RedBlackTree ()
    {
      if (_root != nullptr)
      {
        remove_node<Node>( _alloc, _alloc_node, _root );
        _root = nullptr;
      }
    }
    // ---------------- Base ----------------
  public:
    Node ** base ( void ) { return (&_root); }

    // ---------------- Smallest ----------------
  public:
    Node * smallest ( void ) const
    {
      Node * small = _root;
      while (small && small->_left)
        small = small->_left;
      return (small);
    }
    // ---------------- Size ----------------
  public:
    size_type size ( void ) const
    { return (_size); }

    // ---------------- Clear ----------------
  public:
    void clear ( void )
    {
      remove_node( _alloc, _alloc_node, _root );
      _root = nullptr;
      _size = 0;
    }

    // ---------------- Find ----------------
  public:
    Node * find ( const key_type & k ) const {
      Node * node = _root;

      while (node) {
        if (_comp(k , node->_value->first))
          node = node->_left;
        else if (_comp(node->_value->first, k))
            node = node->_right;
        else
          return (node);
      }
      return (nullptr);
    }

    // ---------------- Insertion ----------------
  public:
    Node * add ( const value_type & val )
    {
      Node * node = make_node<Node>(_alloc, _alloc_node, val);

      if (_root == nullptr)
      { _root = node; _root->_isRed = false; }
      else
        _addNode ( node );
      ++_size;
      return (node);
    }

  private:
    void _addNode ( Node * node ) {
      Node * tmp = _root;
      while (true) {
        if (_comp(node->_value->first, tmp->_value->first)) {
          if (tmp->_left == nullptr) {
            tmp->_left = node;
            node->_parent = tmp;
            node->_isRight = false;
            break;
          } else tmp = tmp->_left;
        } else {
          if (tmp->_right == nullptr) {
            tmp->_right = node;
            node->_parent = tmp;
            node->_isRight = true;
            break;
          } else tmp = tmp->_right;
        }
      }
      _addNode_fix ( node );
    }

  private:
    void _addNode_fix ( Node * node ) {
      while (node && node->_parent) {
        if (node->_isRed && node->_parent->_isRed) {
          if (node->_parent->_parent)
            _addNode_correct ( node );
        }
        node = node->_parent;
      }
      if (_root->_isRed) _root->_isRed = false;
    }

  private:
    void _addNode_correct ( Node * node )
    {
      if (node->_parent->_isRight) {
        if (node->_parent->_parent->_left && node->_parent->_parent->_left->_isRed)
          _addNode_colorFlip ( node->_parent->_parent ); // color flip
        else
          _addNode_rotate ( node ); // rotate
      } else {
        if (node->_parent->_parent->_right && node->_parent->_parent->_right->_isRed)
          _addNode_colorFlip ( node->_parent->_parent ); // color flip
        else
          _addNode_rotate ( node ); // rotate
      }
    }

  private:
    void _addNode_colorFlip ( Node * node )
    {
      node->_isRed = true;
      if (node->_right) node->_right->_isRed = false;
      if (node->_left) node->_left->_isRed = false;
    }

  private:
    void _addNode_rotate ( Node * node )
    {
      if (node->_isRight) {
        if (node->_parent->_isRight) {
          _addNode_rotate_left ( node );
          node->_parent->_isRed = false;
          node->_isRed = true;
          node->_parent->_left->_isRed = true;
        } else {
          _addNode_rotate_left_right ( node );
          node->_isRed = false;
          node->_left->_isRed = true;
          node->_right->_isRed = true;
        }
      } else {
        if (node->_parent->_isRight) {
          _addNode_rotate_right_left ( node );
          node->_isRed = false;
          node->_left->_isRed = true;
          node->_right->_isRed = true;
        } else {
          _addNode_rotate_right ( node );
          node->_parent->_isRed = false;
          node->_isRed = true;
          node->_parent->_right->_isRed = true;
        }
      }
    }

  private:
    //      0
    //       \
    //        0
    //         \
    //          0 ( the node )
    void _addNode_rotate_left ( Node * node )
    {
      Node * theParent = node->_parent;
      Node * theGrandParent = node->_parent->_parent;

      theParent->_parent = theGrandParent->_parent;
      if (theGrandParent->_parent)
      {
        if (theGrandParent->_isRight)
        { theGrandParent->_parent->_right = theParent; theParent->_isRight = true; }
        else
        { theGrandParent->_parent->_left = theParent; theParent->_isRight = false; }
      }
      else
      {
        _root = theParent;
        theParent->_isRight = true;
      }

      theGrandParent->_right = theParent->_left;
      if (theParent->_left)
      {
        theParent->_left->_parent = theGrandParent;
        theParent->_left->_isRight = true;
      }
      theParent->_left = theGrandParent;
      theGrandParent->_parent = theParent;
      theGrandParent->_isRight = false;
    }
    //        0
    //       /
    //      0
    //       \
    //        0 ( the node )
    void _addNode_rotate_left_right ( Node * node )
    {
      Node * theParent = node->_parent;
      Node * theGrandParent = node->_parent->_parent;

      node->_parent = theGrandParent;
      theGrandParent->_left = node;
      node->_isRight = false;

      theParent->_right = node->_left;
      if (node->_left)
      {
        node->_left->_parent = theParent;
        node->_left->_isRight = true;
      }

      node->_left = theParent;
      theParent->_parent = node;
      theParent->_isRight = false;

      _addNode_rotate_right ( theParent );
    }
    //      0
    //       \
    //        0
    //       /
    //      0 ( the node )
    void _addNode_rotate_right_left ( Node * node )
    {
      Node * theParent = node->_parent;
      Node * theGrandParent = node->_parent->_parent;

      node->_parent = theGrandParent;
      theGrandParent->_right = node;
      node->_isRight = true;

      theParent->_left = node->_right;
      if (node->_right)
      {
        node->_right->_parent = theParent;
        node->_right->_isRight = false;
      }

      node->_right = theParent;
      theParent->_parent = node;
      theParent->_isRight = true;

      _addNode_rotate_left ( theParent );
    }
    //          0
    //         /
    //        0
    //       /
    //      0 ( the node )
    void _addNode_rotate_right ( Node * node )
    {
      Node * theParent = node->_parent;
      Node * theGrandParent = node->_parent->_parent;

      theParent->_parent = theGrandParent->_parent;
      if (theGrandParent->_parent)
      {
        if (theGrandParent->_isRight)
        { theGrandParent->_parent->_right = theParent; theParent->_isRight = true; }
        else
        { theGrandParent->_parent->_left = theParent; theParent->_isRight = false; }
      }
      else
      {
        _root = theParent;
        theParent->_isRight = true;
      }

      theGrandParent->_left = theParent->_right;
      if (theParent->_right)
      {
        theParent->_right->_parent = theGrandParent;
        theParent->_right->_isRight = false;
      }

      theParent->_right = theGrandParent;
      theGrandParent->_parent = theParent;
      theGrandParent->_isRight = true;
    }

    // ---------------- Deletion ----------------
  public:
    void _erase ( const value_type & val ) // THIS IS THE FUNCTION THAT WE ARE GOING TO CALL IN OWR CONTAINERS.
    {
      Node * node = _root;
      while (node)
        {
          if (_comp(val.first, node->_value->first))
            node = node->_left;
          else if (_comp(node->_value->first, val.first))
              node = node->_right;
          else
            break ;
        }
      if (node == nullptr) return ;
      else
        {
          _eraseNode ( node );
          --_size;
        }
    }

  private:
    void _eraseNode ( Node * node ) // This is the node that have the value that we want to erase.
    {
      if (node->_right)
        node = _eraseNode_successor ( node );
      else if (node->_left)
          node = _eraseNode_predecessor ( node );
      _eraseNode_R_or_B ( node );
    }

  private:
    Node * _eraseNode_successor ( Node * node )
    {
      Node * leafNode = node->_right;
      while (leafNode->_left) leafNode = leafNode->_left;
      node->swapPosition(leafNode, &_root);
      return (node);
    }
    Node * _eraseNode_predecessor ( Node * node )
    {
      Node * leafNode = node->_left;
      while (leafNode->_right) leafNode = leafNode->_right;
      node->swapPosition(leafNode, &_root);
      return (node);
    }

  private:
    void _eraseNode_R_or_B ( Node * node ) // This function erases the actual node and fixes the violations.
    {
      Node * DBparent = node->_parent;
      bool ItWasRed = node->_isRed;
      bool ItWasRight = node->_isRight;

      _erasingTheNode ( node );

      if ( _root && ItWasRed == false )
        _eraseNode_fix ( DBparent, ItWasRight );
    }

  private:
    void _erasingTheNode ( Node * node ) // ERASE THE NOOOOOODE.
    {
      if ( node->_parent )
      {
        if ( node->_right )
        {
          node->_parent->_left = node->_right;
          node->_right->_parent = node->_parent;
        }
        else if ( node->_left )
        {
          node->_parent->_right = node->_left;
          node->_left->_parent = node->_parent;
        }
      }
      else
        _root = nullptr;
      remove_node<Node>( _alloc, _alloc_node, node );
    }

  private:
    void _eraseNode_fix ( Node * DBparent, const bool & DBisRight ) // Fix the violations.
    {
      Node * DBsibling = ( DBisRight ) ? DBparent->_left : DBparent->_right;

      if (DBsibling->_isRed)
        _eraseNode_fix_sbR ( DBparent, DBisRight ); // the sibling is Red
      else
        {
          if ((DBsibling->_right == nullptr || DBsibling->_right->_isRed = false) && \
            (DBsibling->_left == nullptr || DBsibling->_left->_isRed = false)) // the sibling is Black & both nephews are Black
            _eraseNode_fix_sbB_nsB ( DBparent, DBisRight );
          else if ( (DBisRight) ? (DBsibling->_left && DBsibling->_left->_isRed) : (DBsibling->_right && DBsibling->_right->_isRed) ) // the sibling is Black & far nephew is Red
              _eraseNode_fix_sbB_fnR ( DBparent, DBisRight );
          else if ( (DBisRight) ? \
                ((DBsibling->_left == nullptr || DBsibling->_left->_isRed == false) && DBsibling->_right && DBsibling->_right->_isRed) : \
                ((DBsibling->_right == nullptr || DBsibling->_right->_isRed == false) && DBsibling->_left && DBsibling->_left->_isRed)) // the sibling is Black & far nephew is Black & near nephew is Red
                _eraseNode_fix_sbB_fnB_nnR ( DBparent, DBisRight );
        }
    }

  private:
    void _eraseNode_fix_sbR ( Node * DBparent, const bool & DBisRight ) // the sibling is Red
    {
      Node * DBsibling = ( DBisRight ) ? DBparent->_left : DBparent->_right;

      bool color = DBparent->_isRed;
      DBparent->_isRed = DBsibling->_isRed;
      DBsibling->_isRed = color;

      if ( DBisRight ) _eraseNode_fix_rotate_right ( DBparent );
      else             _eraseNode_fix_rotate_left ( DBparent );

      _eraseNode_fix ( DBparent, DBisRight );
    }
    void _eraseNode_fix_sbB_nsB ( Node * DBparent, const bool & DBisRight ) // the sibling is Black & both nephews are Black
    {
      Node * DBsibling = ( DBisRight ) ? DBparent->_left : DBparent->_right;

      DBsibling->_isRed = true;
      if (DBparent->_isRed)
        DBparent->_isRed = false;
      else
        _eraseNode_fix ( DBparent->_parent, DBparent->_isRight );
    }
    void _eraseNode_fix_sbB_fnR ( Node * DBparent, const bool & DBisRight ) // the sibling is Black & far nephew is Red
    {
      Node * DBsibling = ( DBisRight ) ? DBparent->_left : DBparent->_right;

      bool color = DBparent->_isRed;
      DBparent->_isRed = DBsibling->_isRed;
      DBsibling->_isRed = color;

      ( DBisRight ) ? (DBsibling->_left->_isRed = false) : (DBsibling->_right->_isRed = false);

      if ( DBisRight ) _eraseNode_fix_rotate_right ( DBparent );
      else             _eraseNode_fix_rotate_left ( DBparent );
    }
    void _eraseNode_fix_sbB_fnB_nnR ( Node * DBparent, const bool & DBisRight ) // the sibling is Black & far nephew is Black & near nephew is Red
    {
      Node * DBsibling = ( DBisRight ) ? DBparent->_left : DBparent->_right;
      Node * DBnearNephew = ( DBisRight ) ? DBsibling->_right : DBsibling->_left;

      bool color = DBsibling->_isRed;
      DBsibling->_isRed = DBnearNephew->_isRed;
      DBnearNephew->_isRed = color;

      if ( DBisRight ) _eraseNode_fix_rotate_left ( DBsibling );
      else             _eraseNode_fix_rotate_right ( DBsibling );

      _eraseNode_fix_sbB_fnR ( DBparent, DBisRight );
    }

  private:
    //        0 ( the node )
    //       / \
    //      0   0
    void _eraseNode_fix_rotate_right ( Node * node )
    {
      Node * leftChild = node->_left;

      leftChild->_parent = node->_parent;
      if (node->_parent)
      {
        if (node->_isRight)
        { node->_parent->_right = leftChild; leftChild->_isRight = true; }
        else
        { node->_parent->_left = leftChild; leftChild->_isRight = false; }
      }
      else
      {
        _root = leftChild;
        leftChild->_isRight = true;
      }

      node->_left = leftChild->_right;
      if (leftChild->_right)
      {
        leftChild->_right->_parent = node;
        leftChild->_right->_isRight = false;
      }

      leftChild->_right = node;
      node->_parent = leftChild;
      node->_isRight = true;
    }
    //        0 ( the node )
    //       / \
    //      0   0
    void _eraseNode_fix_rotate_left ( Node * node )
    {
      Node * rightChild = node->_right;

      rightChild->_parent = node->_parent;
      if (node->_parent)
      {
        if (node->_isRight)
        { node->_parent->_right = rightChild; rightChild->_isRight = true; }
        else
        { node->_parent->_left = rightChild; rightChild->_isRight = false; }
      }
      else
      {
        _root = rightChild;
        rightChild->_isRight = true;
      }

      node->_right = rightChild->_left;
      if (rightChild->_left)
      {
        rightChild->_left->_parent = node;
        rightChild->_left->_isRight = true;
      }

      rightChild->_left = node;
      node->_parent = rightChild;
      node->_isRight = false;
    }
  };
}

#endif
