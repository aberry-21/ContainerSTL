//
// Created by Aaron Berry on 4/30/21.
//

#include <memory>
#include <iostream>
#include <vector>
#include <list>
#include "tools/memory.h"
#include "tools/profile.h"
#include "vector/vector.h"
#include "list/list.h"
#include "vector/random_access_iterator.h"

//void* operator new(std::size_t sz) // no inline, required by [replacement.functions]/3
//{
//  std::printf("global op new called, size = %zu\n", sz);
//  if (sz == 0)
//    ++sz; // avoid std::malloc(0) which may return nullptr on success
//
//  if (void *ptr = std::malloc(sz))
//    return ptr;
//
//  throw std::bad_alloc{}; // required by [new.delete.single]/3
//}
//
//void operator delete(void* ptr) noexcept
//{
//  std::puts("global op delete called");
//  std::free(ptr);
//}


int main () {
  ft::list<int> my_lst;
  std::list<int> std_lst;
  for (int i = 100000; i > -100000; --i) {
    my_lst.push_back(i);
    std_lst.push_back(i);
  }
  {
    LOG_DURATION("TEST")
    my_lst.sort();
  }
  {
    LOG_DURATION("TEST")
    std_lst.sort();
  }
//  for (const auto &item : my_lst) {
//    std::cout << item << ' ';
//  }
  cout << std::endl;
}
