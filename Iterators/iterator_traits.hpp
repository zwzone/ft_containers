/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:28:03 by zwina             #+#    #+#             */
/*   Updated: 2023/01/19 10:28:04 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iterator>

namespace ft
{
template< class Iterator >
struct iterator_traits {
  typedef typename Iterator::value_type         value_type;
  typedef typename Iterator::pointer            pointer;
  typedef typename Iterator::reference          reference;
  typedef typename Iterator::difference_type    difference_type;
  typedef typename Iterator::iterator_category  iterator_category;
};
template< class T >
struct iterator_traits< T * > {
  typedef T                               value_type;
  typedef T*                              pointer;
  typedef T&                              reference;
  typedef ptrdiff_t                       difference_type;
  typedef std::random_access_iterator_tag iterator_category;
};
template< class T >
struct iterator_traits< const T * > {
  typedef T                               value_type;
  typedef const T*                        pointer;
  typedef const T&                        reference;
  typedef ptrdiff_t                       difference_type;
  typedef std::random_access_iterator_tag iterator_category;
};

template
<
class Category,
class T,
class Value     = typename iterator_traits<T*>::value_type,
class Pointer   = typename iterator_traits<T*>::pointer,
class Reference = typename iterator_traits<T*>::reference,
class Distance  = typename iterator_traits<T*>::difference_type
>
struct iterator {
  typedef Value     value_type;
  typedef Pointer   pointer;
  typedef Reference reference;
  typedef Distance  difference_type;
  typedef Category  iterator_category;
};
}

#endif
