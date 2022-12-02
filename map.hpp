#ifndef MAP_HPP
#define MAP_HPP

namespace ft
{
  template <
    class Key,
    class T,
    class Compare = less<Key>,
    class Alloc = allocator<pair<const Key,T> >
  class map
  {
    public:
      typedef Key                                       key_type;
      typedef T                                         mapped_type;
      typedef ft::pair<const key_type, mapped_type>     value_type;
      typedef Compare                                   key_compare;
      typedef /**/                                      value_compare;
      typedef Alloc                                     allocator_type;
      typedef typename allocator_type::reference        reference;
      typedef typename allocator_type::const_reference  const_reference;
      typedef typename allocator_type::pointer          pointer;
      typedef typename allocator_type::const_pointer    const_pointer;
      typedef typename allocator_type::difference_type  difference_type;
      typedef typename allocator_type::size_type        size_type;
      typedef ft::iterator_map<value_type>              iterator;
      typedef ft::iterator_map<const value_type>        const_iterator;
      typedef ft::reverse_iterator<iterator_map>        reverse_iterator;
      typedef ft::reverse_iterator<const_iterator>      const_reverse_iterator;

    private:

    public:
  };
}

#endif
