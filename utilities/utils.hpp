#ifndef UTILS_HPP
#define UTILS_HPP

#include <memory>
#include "../Iterators/iterator_traits.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "pair.hpp"

namespace ft
{
template< class InputIt >
typename ft::iterator_traits<InputIt>::difference_type
distance( InputIt first, InputIt last )
{
  typename ft::iterator_traits<InputIt>::difference_type result = 0;
  while (first != last) { ++first; ++result; }
  return (result);
}
}

#endif
