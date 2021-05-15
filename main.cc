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

int main() {
  std::vector<int> vec(10, 6);
//  {
//    ft::list<int> lst;
//    std::cout << ( lst.begin() == lst.end() )<< std::endl;
//    std::list<int> std_lst;
//    std::cout << ( std_lst.begin() == std_lst.end() )<< std::endl;
//  }
  {
    ft::list<int> my_lst(vec.begin(), vec.end());
    ft::list<int> my_lst_new(my_lst);
    std::list<int> std_lst(vec.begin(), vec.end());
    std::list<int> std_lst_new(std_lst);
    for (const auto &item : std_lst_new) {
      std::cout << item << std::endl;
    }
    std::cout << "___________________________" << std::endl;
    for (const auto &item : my_lst_new) {
      std::cout << item << std::endl;
    }
  }


}
