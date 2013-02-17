/*
 Copyright (c) Ian Hobson 2013

 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include <algorithm>
#include <iterator>
#include <list>
#include <sstream>
#include <vector>

#include <boost/algorithm/adjacent_for_each.hpp>
#include <boost/assign/list_of.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>


namespace ba = boost::algorithm;

template<typename T>
struct CheckAdjacentElements
{
  typedef std::vector<std::pair<T, T> > ElementPairs;

  CheckAdjacentElements() : index_(0) {}

  CheckAdjacentElements(const ElementPairs& expectations)
    : expectations_(expectations)
    , index_(0)
  {}

  void operator()(T A, T B) {
    BOOST_CHECK_EQUAL(expectations_[index_].first, A);
    BOOST_CHECK_EQUAL(expectations_[index_].second, B);
    ++index_;
  }

  ElementPairs expectations_;
  int index_;
};


BOOST_AUTO_TEST_CASE(adjacent_for_each_test_const)
{
  BOOST_CHECK_EQUAL(
    0,
    ba::adjacent_for_each(
      std::list<int>(), CheckAdjacentElements<int>()).index_);

  BOOST_CHECK_EQUAL(
    0,
    ba::adjacent_for_each(
      std::list<int>(1), CheckAdjacentElements<int>()).index_);

  const std::list<int> v = boost::assign::list_of(0)(1)(2)(3)(4);

  const CheckAdjacentElements<int>::ElementPairs expected =
    boost::assign::list_of
      (std::make_pair(0, 1))
      (std::make_pair(1, 2))
      (std::make_pair(2, 3))
      (std::make_pair(3, 4));

  BOOST_CHECK_EQUAL(
    expected.size(),
    ba::adjacent_for_each(v, CheckAdjacentElements<int>(expected)).index_);

  BOOST_CHECK_EQUAL(
    expected.size(),
    ba::adjacent_for_each(
      v.begin(), v.end(),
      CheckAdjacentElements<int>(expected)).index_);
}


BOOST_AUTO_TEST_CASE(adjacent_for_each_test_non_const)
{
  std::list<int> v = boost::assign::list_of(0)(1)(2)(3)(4);

  ba::adjacent_for_each(v, std::swap<int>);

  const std::list<int> expected = boost::assign::list_of(1)(2)(3)(4)(0);
  BOOST_CHECK_EQUAL_COLLECTIONS(
    v.begin(), v.end(), expected.begin(), expected.end());

  ba::adjacent_for_each(v.begin(), v.end(), std::swap<int>);

  const std::list<int> expected2 = boost::assign::list_of(2)(3)(4)(0)(1);
  BOOST_CHECK_EQUAL_COLLECTIONS(
    v.begin(), v.end(), expected2.begin(), expected2.end());
}


BOOST_AUTO_TEST_CASE(adjacent_for_each_input_iterator)
{
  const std::istream_iterator<char> end;

  std::istringstream empty_stream;
  BOOST_CHECK_EQUAL(
    0,
    ba::adjacent_for_each(
      std::istream_iterator<char>(empty_stream), end,
      CheckAdjacentElements<char>()).index_);

  std::istringstream single_char_stream("a");
  BOOST_CHECK_EQUAL(
    0,
    ba::adjacent_for_each(
      std::istream_iterator<char>(single_char_stream), end,
      CheckAdjacentElements<char>()).index_);

  std::istringstream multi_char_stream("abcde");
  const CheckAdjacentElements<char>::ElementPairs expected =
    boost::assign::list_of
      (std::make_pair('a', 'b'))
      (std::make_pair('b', 'c'))
      (std::make_pair('c', 'd'))
      (std::make_pair('d', 'e'));

  BOOST_CHECK_EQUAL(
    expected.size(),
    ba::adjacent_for_each(
      std::istream_iterator<char>(multi_char_stream), end,
      CheckAdjacentElements<char>(expected)).index_);
}

