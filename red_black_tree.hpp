#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

namespace ft
{
  template < typename K, typename V >
    class RedBlackTree
    {
        // ---------------- Node Class ----------------
      private:
        struct Node
        {
          K       _key;
          V       _value;
          Node *  _left, _right, _parent;
          bool    _isRed, _isRight;

          Node ()
            : _key(K())
            , _value(V())
            , _left(nullptr)
            , _right(nullptr)
            , _parent(nullptr)
            , _isRed(true)
            , _isRight(true)
          { }

          Node (const K & key = K(),
                const V & value = V(),
                Node * const & left = nullptr,
                Node * const & right = nullptr,
                Node * const & parent = nullptr,
                const bool & isRed = true,
                const bool & isRight = true)
            : _key(key)
            , _value(value)
            , _left(left)
            , _right(right)
            , _parent(parent)
            , _isRed(isRed)
            , _isRight(_isRight)
          { }

          Node ( const Node & copy )
            : _key(key)
            , _value(value)
            , _parent(nullptr)
            , _isRed(copy._isRed)
            , _isRight(copy._isRight)
          {
            if (copy._left != nullptr) { _left = new Node(*copy._left); _left->_parent = this; }
            if (copy._right != nullptr) { _right = new Node(*copy._right); _right->_parent = this; }
          }

          Node &operator=( const Node & copy )
          {
            _key = copy._key;
            _value = copy._value;
            _parent = nullptr;
            _isRed = copy._isRed;
            _isRight = copy._isRight;

            if (copy._left != nullptr) { _left = new Node(*copy._left); _left->_parent = this; }
            if (copy._right != nullptr) { _right = new Node(*copy._right); _right->_parent = this; }

            return (*this);
          }
          
          ~Node()
          {
            if (_left != nullptr) { delete _left; _left = nullptr; }
            if (_right != nullptr) { delete _right; _right = nullptr; }
          }
        };

        // ---------------- Attributes ----------------
      private:
        Node * _root;

        // ---------------- Constructor ----------------
      public:
        RedBlackTree ()
          : _root(nullptr)
        { }

        // ---------------- Copy Constructor ----------------
      public:
        RedBlackTree ( const RedBlackTree & copy )
          : _root(new Node(*copy._root))
        { }

        // ---------------- Copy Assignment Operator ----------------
      public:
        RedBlackTree &operator=( const RedBlackTree & copy )
        { _root = new Node(*copy._root); return (*this); }

        // ---------------- Destructor ----------------
      public:
        ~RedBlackTree ()
        { if (_root != nullptr) { delete _root; _root = nullptr;} }

        // ---------------- Insertions ----------------
      public:
        void add ( const T & obj )
        {
          Node * node ( new Node(obj) );
          if (_root == nullptr)
            _root = node;
          else
            _addNode ( node );
        }

      private:
        void _addNode ( Node * const node )
        {
          Node * tmpRoot  { _root };
          while (true)
          {
            if (node->_value < tmpRoot->_value)
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
            else if (node->_value >= tmpRoot->_value)
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
        }
    };
}

#endif
