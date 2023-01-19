/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:29:09 by zwina             #+#    #+#             */
/*   Updated: 2023/01/19 10:29:14 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
#define EQUAL_HPP

namespace ft
{
template< class InputIt1, class InputIt2 >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
{
  while (first1 != last1) {
    if (*first1 != *first2) return (false);
    ++first1; ++first2;
  }
  return (true);
}

template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
{
  while (first1 != last1) {
    if (!p(*first1, *first2)) return (false);
    ++first1; ++first2;
  }
  return (true);
}
}

#endif
