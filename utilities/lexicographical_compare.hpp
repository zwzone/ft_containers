/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:28:59 by zwina             #+#    #+#             */
/*   Updated: 2023/01/19 10:29:02 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{
template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
{
  while (first1 != last1 && first2 != last2) {
    if (*first1 < *first2) return (true);
    if (*first2 < *first1) return (false);
    ++first1; ++first2;
  }
  return (first1 == last1) && (first2 != last2);
}

template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp )
{
  while (first1 != last1 && first2 != last2) {
    if (comp(*first1, *first2)) return (true);
    if (comp(*first2, *first1)) return (false);
    ++first1; ++first2;
  }
  return (first1 == last1) && (first2 != last2);
}
}

#endif
