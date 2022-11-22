#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "MyIterVector.hpp"
#include "utils.hpp"
#include <iterator> // must be removed after !
#include <string> // must be removed after !

#define SFINAAE(X) typename std::enable_if<!std::is_integral<X>::value, X>::type* = 0

namespace ft
{
  template<typename T, class Allocator = std::allocator<T> >
    class vector
    {
      public:
        typedef T                                        value_type;
        typedef Allocator                                allocator_type;
        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
        typedef ft::MyIterVector<value_type>             iterator;
        typedef ft::MyIterVector<const value_type>       const_iterator;
        typedef std::reverse_iterator<iterator>          reverse_iterator;
        typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

      private:
        allocator_type  _alloc;
        pointer         _start;
        pointer         _end_S;
        pointer         _end_C;

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
        // [*] // template< class InputIt > vector ( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
        // [*] // vector ( const vector& other );
        vector () 
          : _alloc(allocator_type()),
          _start(nullptr),
          _end_S(nullptr),
          _end_C(nullptr)
      {}

        explicit vector ( const allocator_type& alloc )
          : _alloc(alloc),
          _start(nullptr),
          _end_S(nullptr),
          _end_C(nullptr)
      {}
        explicit vector ( size_type count, const_reference val = value_type(),
            const allocator_type& alloc = allocator_type() )
          : _alloc(alloc),
          _start(nullptr),
          _end_S(nullptr),
          _end_C(nullptr)
      {
        this->assign(count, val);
      }
        template< class InputIt >
          vector ( InputIt first, InputIt last, const allocator_type& alloc = allocator_type(), SFINAAE(InputIt) )
          : _alloc(alloc),
          _start(nullptr),
          _end_S(nullptr),
          _end_C(nullptr)
      {
        this->assign(first, last);
      }
        vector ( const vector& other )
          : _alloc(other._alloc),
          _start(nullptr),
          _end_S(nullptr),
          _end_C(nullptr)
      {
        this->assign(other.begin(), other.end());
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
          if (&other != this)
            this->assign(other.begin(), other.end());
          return (*this);
        }
        // [*] // void assign ( size_type count, const T& value );
        // [*] // template< class InputIt > void assign ( InputIt first, InputIt last );
        void assign ( size_type count, const_reference value )
        {
          this->clear();
          if (count == 0)
            return ;
          if (this->capacity() < count)
          {
            if (_start) _alloc.deallocate(_start, this->capacity());
            _start = _alloc.allocate( count );
            _end_S = _start;
            _end_C = _start + count;
          }
          while (count--)
            _alloc.construct(_end_S++, value);
        }
        template< class InputIt >
        void assign ( InputIt first, InputIt last , SFINAAE(InputIt) )
        {
          while (first != last)
          { this->push_back(*first); first++; }
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
        reference back ( void ) { return (*(_end_S - 1)); }
        // [*] // const_reference back () const;
        const_reference back ( void ) const { return (*(_end_S - 1)); }
        // [*] // value_type* data ();
        pointer data ( void ) { return (_start); };
        // [*] // const value_type* data () const;
        const_pointer data ( void ) const { return (_start); };

        // ==========================>> Iterators <<==========================

        // [*] // iterator begin ();
        // [*] // const_iterator begin () const;
        iterator begin ( void ) { return (iterator(_start)); }
        const_iterator begin () const { return (const_iterator(_start)); }
        // [*] // iterator end ();
        // [*] // const_iterator end () const;
        iterator end ( void ) { return (iterator(_end_S)); }
        const_iterator end ( void ) const { return (const_iterator(_end_S)); }
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
        size_type size ( void ) const { return (_end_S - _start); }
        // [*] // size_type max_size () const;
        size_type max_size ( void ) const { return (_alloc.max_size()); };
        // [*] // void reserve ( size_type new_cap );
        void reserve ( size_type new_cap )
        {
          if (new_cap > this->max_size())
            throw (std::length_error("vector::reserve"));
          else if (new_cap > this->capacity())
          {
            pointer new_start = _alloc.allocate( new_cap );
            pointer new_end_S = new_start;
            pointer new_end_C = new_start + new_cap;

            for (pointer ptr = _start; ptr < _end_S; ptr++, new_end_S++)
              _alloc.construct(new_end_S, *ptr);
            if (_start) _alloc.deallocate(_start, this->capacity());

            _start = new_start;
            _end_S = new_end_S;
            _end_C = new_end_C;
          }
        }
        // [*] // size_type capacity () const;
        size_type capacity ( void ) const { return (_end_C - _start); }

        // ========================>> Modifiers <<==========================

        // [*] // void clear();
        void clear ( void )
        {
          while (_start < _end_S)
          { _end_S--; _alloc.destroy(_end_S); }
        }
        // [*] // iterator insert( const_iterator pos, const T& value );
        // [*] // iterator insert( const_iterator pos, size_type count, const T& value );
        // [ ] // template< class InputIt > iterator insert( const_iterator pos, InputIt first, InputIt last );
        iterator insert ( const_iterator pos, const_reference value )
        { this->insert(pos, 1, value); }
        iterator insert( const_iterator pos, size_type count, const_reference value )
        {
          const_pointer ptr_pos = &(*pos);
          if (count == 0) return (iterator(ptr_pos));
          else if (this->capacity() >= count + this->size())
          {
            pointer ptr = _end_S;
            while (ptr-- > ptr_pos)
            {
              _alloc.construct(ptr + count, *ptr);
              _alloc.destroy(ptr);
            }
            for (size_type i = size_type(); i < count; i++)
              _alloc.construct(ptr + i, value);
          }
          else
          {
            size_type new_cap = (this->capacity() == 0) ? 1 : this->capacity() * 2;
            if (this->capacity() * 2 < this->size() + count)
              new_cap = this->size() + count;

            pointer new_start = _alloc.allocate( new_cap );
            pointer new_end_S = new_start;
            pointer new_end_C = new_start + new_cap;

            pointer ptr1 = _start, ptr2 = new_start;

            while (ptr1 < ptr_pos)
            {
              _alloc.construct(ptr2, *ptr1);
              _alloc.destroy(ptr1);
              ptr1++; ptr2++;
            }
            ptr_pos = ptr2;
            for (size_type i = size_type(); i < count; i++)
            {
              _alloc.construct(ptr2, value);
              ptr2++;
            }
            while (ptr1 < _end_S)
            {
              _alloc.construct(ptr2, *ptr1);
              _alloc.destroy(ptr1);
              ptr1++; ptr2++;
            }

            _alloc.deallocate(_start, this->capacity());

            _start = new_start;
            _end_S = new_end_S;
            _end_C = new_end_C;
          }
          return (iterator(ptr_pos));
        }
        template< class InputIt >
        iterator insert( const_iterator pos, InputIt first, InputIt last, SFINAAE(InputIt) )
        {
          (void)pos;
          (void)first;
          (void)last;
          return (nullptr);
        }
        // [*] // iterator erase( iterator pos );
        // [*] // iterator erase( iterator first, iterator last );
        iterator erase ( iterator pos )
        {
          pointer ptr_pos = &(*pos);
          pointer ptr = ptr_pos;
          _alloc.destroy(ptr);
          while (++ptr < _end_S)
            *(ptr - 1) = *ptr;
          _alloc.destroy(--_end_S);
          return (iterator(ptr_pos));
        }
        iterator erase( iterator first, iterator last )
        {
          pointer ptr_first = &(*first);
          pointer ptr_last = &(*last);
          pointer ptr_f = ptr_first;
          pointer ptr_l = ptr_last;
          while (ptr_l < _end_S)
          { *ptr_f = *ptr_l; ptr_f++; ptr_l++; }
          while (ptr_f < ptr_l)
            _alloc.destroy(--ptr_l);
          _end_S = ptr_f;
          return (iterator(ptr_first));
        }
        // [*] // void push_back( const T& value );
        void push_back ( const value_type value )
        {
          if (_end_S == _end_C)
          {
            size_type new_capacity = (this->capacity() == 0) ? 1 : this->size() * 2;
            this->reserve(new_capacity);
          }
          _alloc.construct(_end_S, value);
          _end_S++;
        }
        // [*] // void pop_back();
        void pop_back ( void )
        {
          _end_S--;
          _alloc.destroy(_end_S);
        }
        // [*] // void resize( size_type count, T value = T() );
        void resize ( size_type count, value_type value = value_type() )
        {
          if (count > this->max_size())
            throw (std::length_error("vector::resize"));
          else if (count > this->size())
            this->insert(this->end(), count - this->size(), value);
          else if (count < this->size())
          {
            while (count < this->size())
              _alloc.destroy(--_end_S);
          }
        }
        // [*] // void swap( vector& other );
        void swap ( vector& other )
        {
          if (*this == other)
            return ;

          allocator_type save_alloc = other._alloc;
          pointer save_start = other._start;
          pointer save_end_S = other._end_S;
          pointer save_end_C = other._end_C;

          other._alloc = this->_alloc;
          other._start = this->_start;
          other._end_S = this->_end_S;
          other._end_C = this->_end_C;

          this->_alloc = save_alloc;
          this->_start = save_start;
          this->_end_S = save_end_S;
          this->_end_C = save_end_C;
        }
    };

  template< class T, class Alloc >
    bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
    {
      if (lhs.size() != rhs.size()) return (false);

      typedef typename ft::vector<T,Alloc>::const_iterator const_iterator;

      const_iterator lbIt = lhs.begin();
      const_iterator leIt = lhs.end();
      const_iterator rbIt = rhs.begin();

      return (ft::equal(lbIt, leIt, rbIt));
    }

  template< class T, class Alloc >
    bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
    {
      if (lhs.size() != rhs.size()) return (true);

      typedef typename ft::vector<T,Alloc>::const_iterator const_iterator;

      const_iterator lbIt = lhs.begin();
      const_iterator leIt = lhs.end();
      const_iterator rbIt = rhs.begin();

      return (!ft::equal(lbIt, leIt, rbIt));
    }

  template< class T, class Alloc >
    bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
    {
      typedef typename ft::vector<T,Alloc>::const_iterator const_iterator;

      const_iterator lbIt = lhs.begin();
      const_iterator leIt = lhs.end();
      const_iterator rbIt = rhs.begin();
      const_iterator reIt = lhs.end();

      return (ft::lexicographical_compare(lbIt, leIt, rbIt, reIt));
    }

  template< class T, class Alloc >
    bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
    {
      typedef typename ft::vector<T,Alloc>::const_iterator const_iterator;

      const_iterator lbIt = lhs.begin();
      const_iterator leIt = lhs.end();
      const_iterator rbIt = rhs.begin();
      const_iterator reIt = lhs.end();

      return (!ft::lexicographical_compare(lbIt, leIt, rbIt, reIt));
    }

  template< class T, class Alloc >
    bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
    {
      return (lhs < rhs || lhs == rhs);
    }

  template< class T, class Alloc >
    bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
    {
      return (lhs > rhs || lhs == rhs);
    }

  template< class T, class Alloc >
    void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
    { lhs.swap(rhs); }
};


#endif
