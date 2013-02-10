#include <iostream>
#include <boost/algorithm/adjacent_for_each.hpp>

void PrintInts(int a, int b) {
  std::cout << '(' << a << ", " << b << ")\n";
}

int main() {
  const int ints[] = {0, 1, 2, 3, 4};
  boost::algorithm::adjacent_for_each(ints, ints + 5, PrintInts);
}

