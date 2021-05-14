//
// Created by Aaron Berry on 4/30/21.
//

#include <memory>
#include <iostream>
#include <vector>
#include "tools/memory.h"
#include "tools/profile.h"
#include "vector/vector.h"
#include "vector/test.hpp"
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

class A {
 public:
  A();
  A(int count);
  A(A const & x);
  A &operator=(A const & other);
  A (A&& other) noexcept;
  A& operator=(A&& other) noexcept;
  ~A();
  int GetCount() const;
 private:
  int   count_;
  char* storage_;
};

A::A() {
  count_ = 10;
  storage_ = new char(count_);
}

A::A(int count) {
  count_ = count;
  storage_ = new char(count_);
}

A::A(const A& x){
  count_ = x.count_;
  storage_ = new char(count_);
}

A &A::operator=(const A& other) {
  if (this == &other) {
    return *this;
  }
  char* new_storage = new char(other.count_);
  delete storage_;
  storage_ = new_storage;
  count_ = other.count_;
  return *this;
}

A &A::operator=(A &&other) noexcept {
  delete storage_;
  count_ = other.count_;
  storage_ = other.storage_;
  other.count_ = 0;
  other.storage_ = nullptr;
  return *this;
}

A::A(A &&other) noexcept {
  count_ = other.count_;
  storage_ = other.storage_;
  other.count_ = 0;
  other.storage_ = nullptr;
}

A::~A() {
  delete storage_;
  count_ = 0;
}
int A::GetCount() const {
  return count_;
}

bool operator==(const A& a, const A& b) {
  return a.GetCount() == b.GetCount();
}

// Your namespace
#define my ft
#define vector_ vector
// STD namespace
#define stl std
#define _vector vector

#define lib std
#define con vector

void std_insert_iter_iter_iter_8390_leaks_test() {
  std::cout << "\nassign_iter_iter_1280_leaks\n" << std::endl;
  lib::con<Test> mouse(128);
  for (size_t i = 0; i < mouse.size(); ++i) {
    mouse[i].some_ = i;
  }
  lib::con<Test> fat_mouse(344);
  for (size_t i = 0; i < fat_mouse.size(); ++i) {
    fat_mouse[i].some_ = i + 1000;
  }

  try {
    mouse.insert(mouse.begin(), fat_mouse.begin() + 10, fat_mouse.begin());
  } catch(std::exception & e) {
    std::cout << e.what() << std::endl;
  }

  try {
    mouse.insert(mouse.begin(), fat_mouse.begin(), (fat_mouse.begin() + fat_mouse.max_size()));
  } catch(std::exception & e) {
    std::cout << e.what() << std::endl;
  }

}

int main() {
  stl::_vector<int> stl_vector(2);
  my::vector_<int> my_vector(2);
  my_vector.insert(stl_vector.begin(), my_vector.begin(), (my_vector.begin() + my_vector.max_size()));
  for (const auto &item : stl_vector) {
    std::cout << item << std::endl;
  }
}
