//
// Created by Aaron Berry on 4/30/21.
//

#include <memory>
#include <iostream>
#include <vector>
#include "tools/memory.h"
#include "vector/vector.h"

int main() {
  {
    ft::Allocator<int> a1;   // default allocator for ints
    int* a = a1.allocate(10);  // space for one int
    a1.construct(&a[0], 7);
    a1.construct(&a[1], 8);
    std::cout << a[0] << '\n';
    std::cout << a[1] << '\n';
    a[1] = 2;
    std::cout << a[1] << '\n';
    std::cout << *a1.address(*a) << '\n';
    a1.deallocate(a, 10);      // deallocate space for one int
  }
  std::cout << "_____________________________________________" << '\n';
  {
    ft::Allocator<const int> a1;   // default allocator for ints
    const int* a = a1.allocate(10);  // space for one int
    a1.construct(&a[0], 7);
    a1.construct(&a[1], 8);
    std::cout << a[0] << '\n';
    std::cout << a[1] << '\n';
    a1.construct(&a[1], 3);
    std::cout << a[1] << '\n';
    std::cout << *a1.address(*a) << '\n';
    a1.deallocate(a, 10);      // deallocate space for one int
  }
  std::cout << "_____________________________________________" << '\n';
  {
    std::allocator_traits<std::allocator<int>>d;
    std::allocator<int> a1;   // default allocator for ints
    int* a = a1.allocate(10);  // space for one int
    a1.construct(&a[0], 7);
    a1.construct(&a[1], 8);
    std::cout << a[0] << '\n';
    std::cout << a[1] << '\n';
    a[1] = 2;
    std::cout << a[1] << '\n';
    std::cout << *a1.address(*a) << '\n';
    a1.deallocate(a, 10);      // deallocate space for one int
  }
  std::cout << "_____________________________________________" << '\n';
  {
    std::allocator<const int> a1;   // default allocator for ints
    const int* a = a1.allocate(10);  // space for one int
    a1.construct(&a[0], 7);
    a1.construct(&a[1], 8);
    std::cout << a[0] << '\n';
    std::cout << a[1] << '\n';
    a1.construct(&a[1], 3);
    std::cout << a[1] << '\n';
    std::cout << *a1.address(*a) << '\n';
    a1.deallocate(a, 10);      // deallocate space for one int
  }


  std::vector<int> the_vector;
  ft::Vector<int> the_vector_1(the_vector.max_size() + 1222);

}
