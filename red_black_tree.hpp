#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

namespace ft
{
  template
    <
      typename T,
      typename Compare = less<T>,
      typename Alloc = std::allocator<T>
    >
    class RedBlackTree
    {
        // ---------------- Typedefs ----------------
      public:
        typedef T                         value_type;
        typedef Alloc                     allocator_type;
        typedef allocator_type::size_type size_type;
        typedef Compare                   compare_f;

        // ---------------- Attributes ----------------
      private:
        allocator_type  _alloc;
        size_type       _size;
        Node *          _root;

        // ---------------- Node Class ----------------
      private:
        struct Node
        {
          value_type  _value;
          Node *      _left, _right, _parent;
          bool        _isRed, _isRight;

          Node ()
            , _value(value_type())
            , _left(nullptr)
            , _right(nullptr)
            , _parent(nullptr)
            , _isRed(true)
            , _isRight(true)
          { }

          Node (const value_type & value = V(),
                Node * const & left = nullptr,
                Node * const & right = nullptr,
                Node * const & parent = nullptr,
                const bool & isRed = true,
                const bool & isRight = true)
            , _value(value)
            , _left(left)
            , _right(right)
            , _parent(parent)
            , _isRed(isRed)
            , _isRight(_isRight)
          { }

          Node ( const Node & copy )
            , _value(copy.value)
            , _parent(nullptr)
            , _isRed(copy._isRed)
            , _isRight(copy._isRight)
          {
            if (copy._left != nullptr)
            {
              _left = _alloc.allocate(size_type(1));
              _alloc.construct(_left, *copy._left);
              _left->_parent = this;
            }
            if (copy._right != nullptr)
            {
              _right = _alloc.allocate(size_type(1));
              _alloc.construct(_right, *copy._right);
              _right->_parent = this;
            }
          }

          Node &operator=( const Node & copy )
          {
            _value = copy._value;
            _parent = nullptr;
            _isRed = copy._isRed;
            _isRight = copy._isRight;

            if (copy._left != nullptr)
            {
              _left = _alloc.allocate(size_type(1));
              _alloc.construct(_left, *copy._left);
              _left->_parent = this;
            }
            if (copy._right != nullptr)
            {
              _right = _alloc.allocate(size_type(1));
              _alloc.construct(_right, *copy._right);
              _right->_parent = this;
            }

            return (*this);
          }
          
          ~Node()
          {
            if (copy._left != nullptr)
            {
              _alloc.destroy(_left);
              _alloc.deallocate(_left, size_type(1));
              _left->_parent = this;
            }
            if (copy._right != nullptr)
            {
              _alloc.destroy(_right);
              _alloc.deallocate(_right, size_type(1));
              _right->_parent = this;
            }
          }
        };

        // ---------------- Constructor ----------------
      public:
        RedBlackTree ()
          : _alloc(allocator_type())
          , _size(size_type())
          , _root(nullptr)
        { }

        // ---------------- Copy Constructor ----------------
      public:
        RedBlackTree ( const RedBlackTree & copy )
          : _alloc(allocator_type())
          , _size(size_type(1))
          , _root(_alloc.allocate(_size))
        { _alloc.construct(_root, *copy._root); }

        // ---------------- Copy Assignment Operator ----------------
      public:
        RedBlackTree &operator=( const RedBlackTree & copy )
        {
          _root = _alloc.allocate(size_type(1));
          _alloc.construct(_root, *copy._root);
          return (*this);
        }

        // ---------------- Destructor ----------------
      public:
        ~RedBlackTree ()
        {
          if (_root != nullptr)
          {
            _alloc.destroy(_root);
            _alloc.deallocate(_root, size_type(1));
            _root = nullptr;
          }
        }

        // ---------------- Insertions ----------------
      public:
        void add ( const value_type & obj )
        {
          Node * node;

          node = _alloc.allocate(size_type(1));
          _alloc.construct(node, obj)

          if (_root == nullptr)
          { _root = node; _root->isRed = false; }
          else
            _addNode ( node );

          ++_size;
        }

      private:
        void _addNode ( Node * node )
        {
          Node * root  { _root };
          while (true)
          {
            if (compare_f(node->_value, root->_value))
            {
              if (tmpRoot->_left == nullptr)
              {
                tmpRoot->_left = node;
                node->parent = tmpRoot;
                node->_isRight = false;
                break;
              }
              else tmpRoot = tmpRoot->_left;
            }
            else
            {
              if (tmpRoot->_right == nullptr)
              {
                tmpRoot->_right = node;
                node->parent = tmpRoot;
                break;
              }
              else tmpRoot = tmpRoot->_right;
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
              _addNode_colorFlip ( node->parent->parent );
            else
              _addNode_rotate ( node ); // rotate
          }
          else
          {
            if (node->parent->parent->right && node->parent->parent->right->isRed)
              _addNode_colorFlip ( node->parent->parent );
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
        //          0
        void _addNode_rotate_left ( Node * node )
        {
          Node * theParent { node->parent };
          Node * theGrandParent { node->parent->parent };

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
        //        0
        void _addNode_rotate_left_right ( Node * node )
        {
          Node * theParent { node->parent };
          Node * theGrandParent { node->parent->parent };

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
        //      0
        void _addNode_rotate_right_left ( Node * node )
        {
          Node * theParent { node->parent };
          Node * theGrandParent { node->parent->parent };

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
        //      0
        void _addNode_rotate_right ( Node * node )
        {
          Node * theParent { node->parent };
          Node * theGrandParent { node->parent->parent };

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
    };
}

#endif
