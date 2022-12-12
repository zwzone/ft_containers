#ifndef RED_BLACK_TREE_MAP_HPP
#define RED_BLACK_TREE_MAP_HPP

namespace ft
{
  template < class Node >
    Node * make_node ( const Node * node )
    {
      typedef typename Node::allocator_node_type  allocator_node_type;
      typedef typename Node::size_type            size_type;

      allocator_node_type * _alloc = node->_alloc;
      Node * newNode = _alloc->allocate(size_type(1));
      _alloc->construct(newNode, *node);
      return (newNode);
    }

  template < class Node >
    Node * make_node ( typename Node::allocator_node_type * _alloc, const typename Node::value_type & val )
    {
      typedef typename Node::size_type            size_type;

      Node * newNode = _alloc->allocate(size_type(1));
      _alloc->construct(newNode, val);
      return (newNode);
    }

  template < class Node >
    void remove_node ( typename Node::allocator_node_type * _alloc, Node * node )
    {
      typedef typename Node::size_type            size_type;

      _alloc->destroy(node);
      _alloc->deallocate(node, size_type(1));
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
          , _root(nullptr)
          , _size(size_type())
        {}

        // ---------------- Copy Assignment Operator ----------------
      public:
        RedBlackTree &operator=( const RedBlackTree & copy )
        {
          _root = make_node<Node>(copy._root);
          _size = copy._size;
          return (*this);
        }

        // ---------------- Destructor ----------------
      public:
        ~RedBlackTree ()
        {
          if (_root != nullptr)
          {
            remove_node<Node>( &_alloc, _root );
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
          remove_node(&_alloc, _root);
          _root = nullptr;
          _size = 0;
        }

        // ---------------- Insertion ----------------
      public:
        void add ( const value_type & val )
        {
          Node * node = make_node<Node>(&_alloc, val);

          if (_root == nullptr)
          { _root = node; _root->_isRed = false; }
          else
            _addNode ( node );

          ++_size;
        }

      private:
        void _addNode ( Node * node )
        {
          Node * root = _root;
          while (true)
          {
            if (compare_f(node->_value, root->_value))
            {
              if (root->_left == nullptr)
              {
                root->_left = node;
                node->parent = root;
                node->_isRight = false;
                break;
              }
              else root = root->_left;
            }
            else
            {
              if (root->_right == nullptr)
              {
                root->_right = node;
                node->parent = root;
                break;
              }
              else root = root->_right;
            }
          }
          _addNode_fix ( node );
        }

      private:
        void _addNode_fix ( Node * node )
        {
          while (node != _root)
          {
            if (node->_isRed && node->parent->_isRed)
              _addNode_correct ( node );
            node = node->parent;
          }
          if (_root->isRed) _root->isRed = false;
        }

      private:
        void _addNode_correct ( Node * node )
        {
          if (node->parent->isRight)
          {
            if (node->parent->parent->left && node->parent->parent->left->isRed)
              _addNode_colorFlip ( node->parent->parent ); // color flip
            else
              _addNode_rotate ( node ); // rotate
          }
          else
          {
            if (node->parent->parent->right && node->parent->parent->right->isRed)
              _addNode_colorFlip ( node->parent->parent ); // color flip
            else
              _addNode_rotate ( node ); // rotate
          }
        }

      private:
        void _addNode_colorFlip ( Node * node )
        {
          node->isRed = true;
          if (node->right) node->right->isRed = false;
          if (node->left) node->left->isRed = false;
        }

      private:
        void _addNode_rotate ( Node * node )
        {
          if (node->isRight)
          {
            if (node->parent->isRight)
              _addNode_rotate_left ( node );
            else
              _addNode_rotate_left_right ( node );
            node->isRed = true;
            node->parent->isRed = false;
            if (node->parent->right) node->parent->right->isRed = true;
          }
          else
          {
            if (node->parent->isRight)
              _addNode_rotate_right_left ( node );
            else
              _addNode_rotate_right ( node );
            node->isRed = true;
            node->parent->isRed = false;
            if (node->parent->left) node->parent->left->isRed = true;
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
          Node * theParent = node->parent;
          Node * theGrandParent = node->parent->parent;

          theParent->parent = theGrandParent->parent;
          if (theGrandParent->parent)
          {
            if (theGrandParent->isRight)
            { theGrandParent->parent->right = theParent; theParent->isRight = true; }
            else
            { theGrandParent->parent->left = theParent; theParent->isRight = false; }
          }
          else
          {
            _root = theParent;
            theParent->isRight = true;
          }

          theGrandParent->right = theParent->left;
          if (theParent->left)
          {
            theParent->left->parent = theGrandParent;
            theParent->left->isRight = true;
          }

          theParent->left = theGrandParent;
          theGrandParent->parent = theParent;
          theGrandParent->isRight = false;
        }
        //        0
        //       /
        //      0
        //       \
        //        0 ( the node )
        void _addNode_rotate_left_right ( Node * node )
        {
          Node * theParent = node->parent;
          Node * theGrandParent = node->parent->parent;

          node->parent = theGrandParent;
          theGrandParent->left = node;
          node->isRight = false;

          theParent->right = node->left;
          if (node->left)
          {
            node->left->parent = theParent;
            node->left->isRight = true;
          }

          node->left = theParent;
          theParent->parent = node;
          theParent->isRight = false;

          _addNode_rotate_right ( theParent );
        }
        //      0
        //       \
        //        0
        //       /
        //      0 ( the node )
        void _addNode_rotate_right_left ( Node * node )
        {
          Node * theParent = node->parent;
          Node * theGrandParent = node->parent->parent;

          node->parent = theGrandParent;
          theGrandParent->right = node;
          node->isRight = true;

          theParent->left = node->right;
          if (node->left)
          {
            node->left->parent = theParent;
            node->left->isRight = false;
          }

          node->right = theParent;
          theParent->parent = node;
          theParent->isRight = true;

          _addNode_rotate_left ( theParent );
        }
        //          0
        //         /
        //        0
        //       /
        //      0 ( the node )
        void _addNode_rotate_right ( Node * node )
        {
          Node * theParent = node->parent;
          Node * theGrandParent = node->parent->parent;

          theParent->parent = theGrandParent->parent;
          if (theGrandParent->parent)
          {
            if (theGrandParent->isRight)
            { theGrandParent->parent->right = theParent; theParent->isRight = true; }
            else
            { theGrandParent->parent->left = theParent; theParent->isRight = false; }
          }
          else
          {
            _root = theParent;
            theParent->isRight = true;
          }

          theGrandParent->left = theParent->right;
          if (theParent->right)
          {
            theParent->right->parent = theGrandParent;
            theParent->right->isRight = false;
          }

          theParent->right = theGrandParent;
          theGrandParent->parent = theParent;
          theGrandParent->isRight = true;
        }

        // ---------------- Deletion ----------------
      public:
        void _erase ( const value_type & val ) // THIS IS THE FUNCTION THAT WE ARE GOING TO CALL IN OWR CONTAINERS.
        {
          Node * node = _root;
          while (node)
          {
            if (compare_f(val, node->_value))
              node = node->_left;
            else if (compare_f(node->_value, val))
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
          Node * DBparent = node->parent;
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
          remove_node<Node>( &_alloc, node );
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
