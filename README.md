Adjacent For Each
=================

    template<typename InputIterator, typename Function>
    Function adjacent_for_each(InputIterator first, InputIterator last, Function f)

    template<typename Range, typename Function>
    Function adjacent_for_each(const Range& range, Function f)

    template<typename Range, typename Function>
    Function adjacent_for_each(Range& range, Function f)

Calls function *f* for each adjacent pair of elements in a range.


Example
-------

    #include <iostream>
    #include <boost/algorithm/adjacent_for_each.hpp>

    void PrintInts(int a, int b) {
      std::cout << '(' << a << ", " << b << ")\n";
    }

    int main() {
      const int ints[] = {0, 1, 2, 3, 4};
      boost::algorithm::adjacent_for_each(ints, ints + 5, PrintInts);
    }

Output:

    (0, 1)
    (1, 2)
    (2, 3)
    (3, 4)
