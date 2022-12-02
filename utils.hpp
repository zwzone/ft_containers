#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "iterator_traits.hpp"

namespace ft
{
  template< bool Cond, class T = void >
    struct enable_if {};
  template< class T >
    struct enable_if<true, T> { typedef T type; };

  template< class T >
    struct is_integral { static const bool value = false; };
  template<> struct is_integral<bool>       { static const bool value = true; };
  template<> struct is_integral<char>       { static const bool value = true; };
  template<> struct is_integral<char16_t>   { static const bool value = true; };
  template<> struct is_integral<char32_t>   { static const bool value = true; };
  template<> struct is_integral<wchar_t>    { static const bool value = true; };
  template<> struct is_integral<short>      { static const bool value = true; };
  template<> struct is_integral<int>        { static const bool value = true; };
  template<> struct is_integral<long>       { static const bool value = true; };
  template<> struct is_integral<long long>  { static const bool value = true; };

  template< class InputIt1, class InputIt2 >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
    {
      while (first1 != last1)
      {
        if (*first1 != *first2) return (false);
        ++first1; ++first2;
      }
      return (true);
    }

  template< class InputIt1, class InputIt2, class BinaryPredicate >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
    {
      while (first1 != last1)
      {
        if (!p(*first1, *first2)) return (false);
        ++first1; ++first2;
      }
      return (true);
    }
  template< class InputIt1, class InputIt2 >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
    {
      while (first1 != last1 && first2 != last2)
      {
        if (*first1 < *first2) return (true);
        if (*first2 < *first1) return (false);
        ++first1; ++first2;
      }
      return (first1 == last1) && (first2 != last2);
    }

  template< class InputIt1, class InputIt2, class Compare >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp )
    {
      while (first1 != last1 && first2 != last2)
      {
        if (comp(*first1, *first2)) return (true);
        if (comp(*first2, *first1)) return (false);
        ++first1; ++first2;
      }
      return (first1 == last1) && (first2 != last2);
    }

  template< class InputIt >
    typename ft::iterator_traits<InputIt>::difference_type
    distance( InputIt first, InputIt last )
    {
      typename ft::iterator_traits<InputIt>::difference_type result = 0;
      while (first != last)
      { ++first; ++result; }
      return (result);
    }

  std::string to_string (unsigned long long val)
  {
    std::string str;
    unsigned long long ten = 1;
    while ( val / ten )
      ten *= 10;
    while ( val )
    {
      str.push_back('0' + ((val % ten) / (ten / 10)));
      val /= 10;
      ten /= 10;
    }
    return (str);
  }
}

#endif
