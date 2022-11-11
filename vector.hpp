#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iterator> // must be removed after !

namespace ft
{
  template<typename T, class Allocator = std::allocator<T> >
    class vector
    {
      public:
        typedef T                                                                 value_type;
        typedef Allocator                                                         allocator_type;
        // references
        typedef typename allocator_type::reference                                reference;
        typedef typename allocator_type::const_reference                          const_reference;
        // pointers
        typedef typename allocator_type::pointer                                  pointer;
        typedef typename allocator_type::const_pointer                            const_pointer;
        // iterators
        typedef std::iterator<std::random_access_iterator_tag, value_type>        iterator;
        typedef std::iterator<std::random_access_iterator_tag, const value_type>  const_iterator;
        typedef std::reverse_iterator<iterator>                                   reverse_iterator;
        typedef typename std::reverse_iterator<const_iterator>                    const_reverse_iterator;
        // sizes
        typedef typename allocator_type::size_type                                size_type;
        typedef typename std::iterator_traits<const_iterator>::difference_type    difference_type;

      private:
        allocator_type  _alloc;
        pointer         _start;
        pointer         _end_size;
        pointer         _end_capacity;

      public:
        // [*] // vector(); 
        // [*] // explicit vector( const Allocator& alloc );
        // [*] // explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator());
        // [ ] // template< class InputIt > vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
        // [*] // vector( const vector& other );
        explicit vector ( const allocator_type& alloc = allocator_type() )
          : _alloc(alloc),
          _start(nullptr),
          _end_size(nullptr),
          _end_capacity(nullptr)
      {}

        explicit vector ( size_type n, const value_type& val = value_type(),
            const allocator_type& alloc = allocator_type() )
          : _alloc(alloc),
          _start(nullptr),
          _end_size(nullptr),
          _end_capacity(nullptr)
      {
        _start = _alloc.allocate( n );
        _end_capacity = _start + n;
        _end_size = _start;
        while (n--)
        {
          _alloc.construct(_end_size, val);
          _end_size++;
        }
      }
        vector( const vector& other )
          : _alloc(other._alloc),
          _start(nullptr),
          _end_size(nullptr),
          _end_capacity(nullptr)
      {
        insert(begin(), other.begin(), other.end());
      }
        // [*] // ~vector();
        ~vector()
        {
          clear();
          _alloc.deallocate(_start, capacity());
        }
        // [*] // vector& operator=( const vector& other );
        vector& operator=( const vector& other )
        {
          if (other == *this)
            return (*this);
          clear();
          insert(end(), other.begin(), other.end());
          return (*this);
        }
        // [*] // void assign( size_type count, const T& value );
        // [ ] // template< class InputIt > void assign( InputIt first, InputIt last );
        void assign( size_type count, const value_type& value)
        {
          clear();
          if (count == 0)
            return ;
          if (size_type(capacity()) < count)
          {
            _alloc.deallocate(_start, capacity());
            _start = _alloc.allocate( count );
            _end_size = _start;
            _end_capacity = _start + count;
          }
          while (count--)
            _alloc.construct(_end_size++, value);
        }

        // [*] // allocator_type get_allocator() const;
        allocator_type get_allocator( void ) const { return ( _alloc ); }

            // ==>> Element access <<==
        // [ ] // reference at( size_type pos );
        // [ ] // const_reference at( size_type pos ) const;
        // [ ] // reference operator[]( size_type pos );
        // [ ] // const_reference operator[]( size_type pos ) const;
        // [ ] // reference front();
        // [ ] // const_reference front() const;
        // [ ] // reference back();
        // [ ] // const_reference back() const;
        // [ ] // value_type* data();
        // [ ] // const value_type* data() const;

            // ==>> Iterators <<==
        // [ ] // iterator begin();
        // [ ] // const_iterator begin() const;
        // [ ] // iterator end();
        // [ ] // const_iterator end() const;
        // [ ] // reverse_iterator rbegin();
        // [ ] // const_reverse_iterator rbegin() const;
        // [ ] // reverse_iterator rend();
        // [ ] // const_reverse_iterator rend() const;

            // ==>> Capacity <<==
        // [*] // bool empty() const;
        // [*] // size_type size() const;
        // [*] // size_type max_size() const;
        // [*] // void reserve( size_type new_cap );
        // [*] // size_type capacity() const;
        bool empty ( void ) const { return (size() == 0 ? true : false); }
        size_type size ( void ) const { return (this->_end_size - this->start); }
        size_type max_size ( void ) const { return (allocator_type().max_size()); };
        void reserve ( size_type new_cap )
        {
          if (new_cap > max_size())
            throw (std::length_error("vector::reserve"));
          else if (new_cap > capacity())
          {
            pointer prev_start = _start;
            pointer prev_end_size = _end_size;
            size_type prev_size = size();
            size_type prev_capacity = capacity();

            _start = _alloc.allocate( new_cap );
            _end_size = _start;
            _end_capacity = _start + new_cap;
            while (prev_start != prev_end_size)
            {
              _alloc.construct(_end_size, *prev_start);
              _end_size++;
              prev_start++;
            }
            _alloc.deallocate(prev_start - prev_size, prev_capacity);
          }
        }
        size_type capacity ( void ) const { return (this->_end_capacity - this->_start); }
    };
};

#endif
