#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iterator> // must be removed after !
#include <string> // must be removed after !

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

        void boundChecking(const size_type& n) const
        {
          if (n >= this->size())
            throw ( std::out_of_range
                (
                 "vector::boundChecking: n (which is "
                 +std::to_string(n)+
                 ") >= this->size() (which is "
                 +std::to_string(this->size())+
                 ")"
                )
                );
        }

      public:

        // ==========================>> Constructors <<==========================

        // [*] // vector (); 
        // [*] // explicit vector ( const Allocator& alloc );
        // [*] // explicit vector ( size_type count, const T& value = T(), const Allocator& alloc = Allocator());
        // [ ] // template< class InputIt > vector ( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
        // [*] // vector ( const vector& other );
        vector () 
          : _alloc(allocator_type()),
          _start(nullptr),
          _end_size(nullptr),
          _end_capacity(nullptr)
      {}

        explicit vector ( const allocator_type& alloc )
          : _alloc(alloc),
          _start(nullptr),
          _end_size(nullptr),
          _end_capacity(nullptr)
      {}

        explicit vector ( size_type n, const_reference val = value_type(),
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
        template< class InputIt >
          vector ( InputIt first, InputIt last, const allocator_type& alloc = allocator_type() )
          : _alloc(alloc),
          _start(nullptr),
          _end_size(nullptr),
          _end_capacity(nullptr)
      {
      }
        vector ( const vector& other )
          :_alloc(other._alloc),
          _start(nullptr),
          _end_size(nullptr),
          _end_capacity(nullptr)
      {
        this->insert(this->begin(), other.begin(), other.end());
      }

        // ==========================>> Destructor <<==========================

        // [*] // ~vector ();
        ~vector ()
        {
          this->clear();
          _alloc.deallocate(_start, this->capacity());
        }

        // ==========================>> Assignment <<==========================

        // [*] // vector& operator= ( const vector& other );
        vector& operator= ( const vector& other )
        {
          if (other == *this)
            return (*this);
          this->clear();
          this->insert(this->end(), other.begin(), other.end());
          return (*this);
        }
        // [*] // void assign ( size_type count, const T& value );
        // [ ] // template< class InputIt > void assign ( InputIt first, InputIt last );
        void assign ( size_type count, const value_type& value)
        {
          this->clear();
          if (count == 0)
            return ;
          if (size_type(this->capacity()) < count)
          {
            _alloc.deallocate(_start, this->capacity());
            _start = _alloc.allocate( count );
            _end_size = _start;
            _end_capacity = _start + count;
          }
          while (count--)
            _alloc.construct(_end_size++, value);
        }
        // [*] // allocator_type get_allocator () const;
        allocator_type get_allocator ( void ) const { return ( _alloc ); }

        // ==========================>> Element access <<==========================

        // [*] // reference at ( size_type pos );
        reference at ( size_type pos )
        {
          this->boundChecking(pos);
          return ((*this)[pos]);
        }
        // [*] // const_reference at ( size_type pos ) const;
        const_reference at ( size_type pos ) const
        {
          this->boundChecking(pos);
          return ((*this)[pos]);
        }
        // [*] // reference operator[] ( size_type pos );
        reference operator[] ( size_type pos ) { return (*(_start + pos)); }
        // [*] // const_reference operator[] ( size_type pos ) const;
        const_reference operator[] ( size_type pos ) const { return (*(_start + pos)); }
        // [*] // reference front ();
        reference front ( void ) { return (*_start); }
        // [*] // const_reference front () const;
        const_reference front ( void ) const { return (*_start); }
        // [*] // reference back ();
        reference back ( void ) { return (*(_end_size - 1)); }
        // [*] // const_reference back () const;
        const_reference back ( void ) const { return (*(_end_size - 1)); }
        // [*] // value_type* data ();
        pointer data ( void ) { return (_start); };
        // [*] // const value_type* data () const;
        const_pointer data ( void ) const { return (_start); };

        // ==========================>> Iterators <<==========================

        // [*] // iterator begin ();
        // [*] // const_iterator begin () const;
        iterator begin ( void ) { return (_start); }
        const_iterator begin () const { return (_start); }
        // [*] // iterator end ();
        // [*] // const_iterator end () const;
        iterator end ( void ) { return (_end_size); }
        const_iterator end ( void ) const { return (_end_size); }
        // [*] // reverse_iterator rbegin ();
        // [*] // const_reverse_iterator rbegin () const;
        reverse_iterator rbegin ( void ) { return (reverse_iterator(this->end())); }
        const_reverse_iterator rbegin ( void ) const { return (reverse_iterator(this->end())); }
        // [*] // reverse_iterator rend ();
        // [*] // const_reverse_iterator rend () const;
        reverse_iterator rend ( void ) { return (reverse_iterator(this->begin())); }
        const_reverse_iterator rend ( void ) const { return (reverse_iterator(this->begin())); }

        // ============================>> Capacity <<============================

        // [*] // bool empty () const;
        bool empty ( void ) const { return (this->size() == 0); }
        // [*] // size_type size () const;
        size_type size ( void ) const { return (_end_size - _start); }
        // [*] // size_type max_size () const;
        size_type max_size ( void ) const { return (_alloc.max_size()); };
        // [*] // void reserve ( size_type new_cap );
        void reserve ( size_type new_cap )
        {
          if (new_cap > this->max_size())
            throw (std::length_error("vector::reserve"));
          else if (new_cap > this->capacity())
          {
            pointer prev_start = _start;
            pointer prev_end_size = _end_size;
            size_type prev_capacity = this->capacity();

            _start = _alloc.allocate( new_cap );
            _end_size = _start;
            _end_capacity = _start + new_cap;
            for (pointer ptr = prev_start; ptr != prev_end_size; ptr++)
            {
              _alloc.construct(_end_size, *ptr);
              _end_size++;
            }
            _alloc.deallocate(prev_start, prev_capacity);
          }
        }
        // [*] // size_type capacity () const;
        size_type capacity ( void ) const { return (_end_capacity - _start); }

        // ========================>> Modifiers <<==========================

        // [*] // void clear();
        void clear ( void )
        {
          while (_start < _end_size)
          { _end_size--; _alloc.destroy(_end_size); }
        }
        // [*] // iterator insert( const_iterator pos, const T& value );
        // [*] // iterator insert( const_iterator pos, size_type count, const T& value );
        // [ ] // constexpr iterator insert( const_iterator pos, size_type count, const T& value );
        // [ ] // template< class InputIt > iterator insert( const_iterator pos, InputIt first, InputIt last );
        iterator insert ( const_iterator pos, const_reference value )
        {
          size_type pos_index = &(*pos) - _start;
          if (this->capacity() >= this->size() + 1)
          {
            for (size_type i = this->size(); i > pos_index; i--)
              _alloc.construct(i + _start, *(i + _start - 1));
            _end_size++;
            _alloc.construct(&(*pos), value);
          }
          else
          {
            size_type new_capacity = (this->capacity() == 0) ? 1 : this->size() * 2;
            pointer new_start = _alloc.allocate( new_capacity );
            pointer new_end_size = new_start + this->size() + 1;
            pointer new_end_capacity = new_start + new_capacity;

            for (size_type i = 0; i < pos_index; i++)
              _alloc.construct(new_start + i, *(_start + i));
            _alloc.construct(new_start + pos_index, value);
            for (size_type i = pos_index + 1; i < this->size() + 1; i++)
              _alloc.construct(new_start + i, *(_start + i - 1));

            for (size_type i = 0; i < this->size(); i++)
              _alloc.destroy(_start + i);
            _alloc.deallocate(_start, this->capacity());

            _start = new_start;
            _end_size = new_end_size;
            _end_capacity = new_end_capacity;
          }
          return (iterator(_start + pos_index));
        }
        iterator insert( const_iterator pos, size_type count, const_reference value )
        {
          size_type pos_index = &(*pos) - _start;
          if (this->capacity() >= this->size() + count)
          {
            for (size_type i = this->size() + count - 1; i > pos_index; i--)
              _alloc.construct(i + _start, *(i + _start - 1));
            _end_size++;
            for (size_type i = 0; i < count; i++)
              _alloc.construct(&(*pos) + i, value);
          }
          else
          {
            size_type new_capacity = (this->capacity() == 0) ? 1 : this->size() * 2;
            pointer new_start = _alloc.allocate( new_capacity );
            pointer new_end_size = new_start + this->size() + count;
            pointer new_end_capacity = new_start + new_capacity;

            for (size_type i = 0; i < pos_index; i++)
              _alloc.construct(new_start + i, *(_start + i));
            for (size_type i = pos_index; i < pos_index + count; i++)
              _alloc.construct(new_start + i, value);
            for (size_type i = pos_index + count; i < this->size() + count; i++)
              _alloc.construct(new_start + i, *(_start + i - count));

            for (size_type i = 0; i < this->size(); i++)
              _alloc.destroy(_start + i);
            _alloc.deallocate(_start, this->capacity());

            _start = new_start;
            _end_size = new_end_size;
            _end_capacity = new_end_capacity;
          }
          return (iterator(_start + pos_index));
        }
        // [*] // iterator erase( iterator pos );
        // [*] // iterator erase( iterator first, iterator last );
        iterator erase ( iterator pos )
        {
          pointer ptr_pos = &(*pos);
          _alloc.destroy(ptr_pos);
          for (pointer ptr = ptr_pos + 1; ptr < _end_size; ptr++)
          {
            _alloc.construct(ptr - 1, *(ptr));
            _alloc.destroy(ptr);
          }
          _end_size--;
          return (iterator(ptr_pos));
        }
        iterator erase( iterator first, iterator last )
        {
          pointer ptr_first = &(*first);
          while (first != last)
          { _alloc.destroy(&(*first)); first++; }
          for (pointer ptr = &(*last); ptr < _end_size; ptr++)
          {
            _alloc.construct(ptr_first, *ptr);
            _alloc.destroy(ptr);
            ptr_first++;
          }
          _end_size -= (&(*last) - ptr_first);
          return (iterator(ptr_first));
        }
        // [*] // void push_back( const T& value );
        void push_back ( const value_type value )
        {
          if (_end_size == _end_capacity)
          {
            size_type new_capacity = (this->capacity() == 0) ? 1 : this->size() * 2;
            this->reserve(new_capacity);
          }
          _alloc.construct(_end_size, value);
          _end_size++;
        }
        // [*] // void pop_back();
        void pop_back ( void )
        {
          _end_size--;
          _alloc.destroy(_end_size);
        }
        // [*] // void resize( size_type count, T value = T() );
        void resize ( size_type count, value_type value = value_type() )
        {
          if (count > this->max_size())
            throw (std::length_error("vector::resize"));
          else if (count < this->size())
          {
            while (this->size() > count)
            {
              _end_size--;
              _alloc.destroy(_end_size);
            }
          }
          else if (count > this->size())
            this->insert(this->end(), count - this->size(), value);
        }
        // [*] // void swap( vector& other );
        void swap ( vector& other )
        {
          if (*this == other)
            return ;

          allocator_type save_alloc = other._alloc;
          pointer save_start = other._start;
          pointer save_end_size = other._end_size;
          pointer save_end_capacity = other._end_capacity;

          other._alloc = this->_alloc;
          other._start = this->_start;
          other._end_size = this->_end_size;
          other._end_capacity = this->_end_capacity;

          this->_alloc = save_alloc;
          this->_start = save_start;
          this->_end_size = save_end_size;
          this->_end_capacity = save_end_capacity;
        }
    };
};

#endif
