/*
 Copyright (c) Ian Hobson 2013

 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_ALGORITHM_ADJACENT_FOR_EACH_HPP
#define BOOST_ALGORITHM_ADJACENT_FOR_EACH_HPP

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

template<typename ForwardIterator, typename Function>
Function adjacent_for_each(ForwardIterator first, ForwardIterator last, Function f)
{
  if (first != last)
    for (ForwardIterator next = first; ++next != last; first++)
      f(*first, *next);
  return f;
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

