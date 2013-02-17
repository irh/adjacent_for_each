/*
 Copyright (c) Ian Hobson 2013

 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_ALGORITHM_ADJACENT_FOR_EACH_HPP
#define BOOST_ALGORITHM_ADJACENT_FOR_EACH_HPP

#include <iterator>
#include <boost/utility.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

template<typename Iterator, typename Function>
Function adjacent_for_each(Iterator first, Iterator last, Function f,
  std::forward_iterator_tag)
{
  if (first != last)
    for (Iterator next = boost::next(first); next != last; ++first, ++next)
      f(*first, *next);
  return f;
}

template<typename Iterator, typename Function>
Function adjacent_for_each(Iterator first, Iterator last, Function f,
  std::input_iterator_tag)
{
  if (first != last) {
    typename std::iterator_traits<Iterator>::value_type previous = *first++;
    while (first != last) {
      typename std::iterator_traits<Iterator>::value_type current = *first++;
      f(previous, current);
      previous = current;
    }
  }
  return f;
}

template<typename Iterator, typename Function>
Function adjacent_for_each(Iterator first, Iterator last, Function f)
{
  return adjacent_for_each(
    first, last, f,
    typename std::iterator_traits<Iterator>::iterator_category());
}

template<typename Range, typename Function>
Function adjacent_for_each(const Range& range, Function f)
{
  return adjacent_for_each(boost::begin(range), boost::end(range), f);
}

template<typename Range, typename Function>
Function adjacent_for_each(Range& range, Function f)
{
  return adjacent_for_each(boost::begin(range), boost::end(range), f);
}

}} // namespace

#endif // BOOST_ALGORITHM_ADJACENT_FOR_EACH_HPP

