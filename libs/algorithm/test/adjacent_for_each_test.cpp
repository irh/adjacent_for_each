/*
 Copyright (c) Ian Hobson 2013

 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include <algorithm>
#include <list>
#include <vector>

#include <boost/algorithm/adjacent_for_each.hpp>
#include <boost/assign/list_of.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>


namespace ba = boost::algorithm;

struct CheckAdjacentElements
{
  typedef std::vector<std::pair<int, int> > IntPairs;

  CheckAdjacentElements() : index_(0) {}

  CheckAdjacentElements(const IntPairs& expectations)
    : expectations_(expectations)
    , index_(0)
  {}

  void operator()(int A, int B) {
    BOOST_CHECK_EQUAL(expectations_[index_].first, A);
    BOOST_CHECK_EQUAL(expectations_[index_].second, B);
    ++index_;
  }

  IntPairs expectations_;
  int index_;
};


BOOST_AUTO_TEST_CASE(adjacent_for_each_test_const)
{
  BOOST_CHECK_EQUAL(
    0,
    ba::adjacent_for_each(std::list<int>(), CheckAdjacentElements()).index_);

  BOOST_CHECK_EQUAL(
    0,
    ba::adjacent_for_each(std::list<int>(1), CheckAdjacentElements()).index_);

  const std::list<int> v = boost::assign::list_of(0)(1)(2)(3)(4);

  const CheckAdjacentElements::IntPairs expected = boost::assign::list_of
    (std::make_pair(0, 1))
    (std::make_pair(1, 2))
    (std::make_pair(2, 3))
    (std::make_pair(3, 4));

  BOOST_CHECK_EQUAL(
    expected.size(),
    ba::adjacent_for_each(v, CheckAdjacentElements(expected)).index_);

  BOOST_CHECK_EQUAL(
    expected.size(),
    ba::adjacent_for_each(
      v.begin(), v.end(),
      CheckAdjacentElements(expected)).index_);
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

