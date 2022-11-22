#ifndef MYITERVECTOR
#define MYITERVECTOR

#include "iterator_traits.hpp"

namespace ft
{
  template < class T >
    class MyIterVector : public ft::iterator<random_access_iterator_tag, T>
    {
      public:
        using typename ft::iterator<random_access_iterator_tag, T>::value_type;
        using typename ft::iterator<random_access_iterator_tag, T>::pointer;
        using typename ft::iterator<random_access_iterator_tag, T>::reference;
        using typename ft::iterator<random_access_iterator_tag, T>::difference_type;
        using typename ft::iterator<random_access_iterator_tag, T>::iterator_category;

      private:
        pointer _p;

      public:
        // ========>> Default Constructor <<========
        MyIterVector() : _p(nullptr)                                        { }

        // ========>> Copy Constructor <<========
        MyIterVector ( const MyIterVector & copy ) : _p(copy._p)  { }

        // ========>> Custom Constructor <<========
        MyIterVector ( pointer p ) : _p(p)                                  { }

        // ========>> Copy Assignment Operator <<========
        MyIterVector &operator= ( const MyIterVector & copy )     { _p = copy._p; return (*this); }

        // ========>> Destructor <<========
        ~MyIterVector()                                                     { }

        // ========>> Equality/Inequality <<========
        bool operator== ( const MyIterVector & itr ) const { return (_p == itr._p); }
        bool operator!= ( const MyIterVector & itr ) const { return (_p != itr._p); }

        // ========>> Dereferencing <<========
        reference       operator* ()        { return (*_p); }
        const reference operator* () const  { return (*_p); }
        pointer         operator-> ()       { return (_p); }
        const pointer   operator-> () const { return (_p); }

        // ========>> Increment Operators <<========
        MyIterVector & operator++ ()
        { _p++; return (*this); }
        MyIterVector operator++ ( int )
        {
          MyIterVector &tmp(*this);
          ++(*this);
          return (tmp);
        }

        // ========>> Decrement Operators <<========
        MyIterVector & operator-- ()
        { _p--; return (*this); }
        MyIterVector operator-- ( int )
        {
          MyIterVector &tmp(*this);
          --(*this);
          return (tmp);
        }

        // ========>> Arithmetic Operators <<========
        MyIterVector        operator- ( const difference_type & n ) const                      { return (MyIterVector(_p - n)); }
        difference_type     operator- ( const MyIterVector<T> & itr ) const                    { return (this->_p - itr._p); }

        MyIterVector        operator+ ( const difference_type & n ) const                      { return (MyIterVector(_p + n)); }
        friend MyIterVector operator+ ( const difference_type & n, const MyIterVector<T> itr ) { return (itr + n); }

        MyIterVector &      operator-= ( const difference_type & n )                           { _p -= n; return (*this); }
        MyIterVector &      operator+= ( const difference_type & n )                           { _p += n; return (*this); }

        // ========>> Relational Operators <<========
        bool operator> ( const MyIterVector & itr ) const  { return (_p > itr._p); }
        bool operator< ( const MyIterVector & itr ) const  { return (_p < itr._p); }
        bool operator>= ( const MyIterVector & itr ) const { return (_p >= itr._p); }
        bool operator<= ( const MyIterVector & itr ) const { return (_p <= itr._p); }

        // ========>> Offset dereference operator <<========
        reference       operator[] ( const int & n )       { return (*(_p + n)); }
        const reference operator[] ( const int & n ) const { return (*(_p + n)); }

        // ========>> Base <<========
        pointer base() { return (_p); }
    };
}

#endif
