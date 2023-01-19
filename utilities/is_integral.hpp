/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:29:04 by zwina             #+#    #+#             */
/*   Updated: 2023/01/19 10:29:06 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft
{
template< class T >
struct is_integral { static const bool value = false; };

template<> struct is_integral<bool>                   { static const bool value = true; };
template<> struct is_integral<char>                   { static const bool value = true; };
template<> struct is_integral<char16_t>               { static const bool value = true; };
template<> struct is_integral<char32_t>               { static const bool value = true; };
template<> struct is_integral<wchar_t>                { static const bool value = true; };
template<> struct is_integral<short int>              { static const bool value = true; };
template<> struct is_integral<int>                    { static const bool value = true; };
template<> struct is_integral<long int>               { static const bool value = true; };
template<> struct is_integral<long long int>          { static const bool value = true; };
template<> struct is_integral<signed char>            { static const bool value = true; };
template<> struct is_integral<unsigned char>          { static const bool value = true; };
template<> struct is_integral<unsigned short int>     { static const bool value = true; };
template<> struct is_integral<unsigned int>           { static const bool value = true; };
template<> struct is_integral<unsigned long int>      { static const bool value = true; };
template<> struct is_integral<unsigned long long int> { static const bool value = true; };

template< class T >
struct is_integral<const T> { static const bool value = is_integral<T>::value; };
template< class T >
struct is_integral<volatile T> { static const bool value = is_integral<T>::value; };
template< class T >
struct is_integral<const volatile T> { static const bool value = is_integral<T>::value; };
}

#endif
