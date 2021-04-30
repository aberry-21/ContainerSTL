//
// Created by Aaron Berry on 4/30/21.
//

#include <memory>
#include <iostream>

#include "tools/memory.h"

int main() {
  ft::Allocator<const int> a1;   // default allocator for ints
  int* a = a1.allocate(10);  // space for one int
  a1.construct(&a[0], 7);
  a1.construct(&a[1], 8);
  std::cout << a[0] << '\n';
  std::cout << a[1] << '\n';
  a1.deallocate(a, 10);      // deallocate space for one int
}