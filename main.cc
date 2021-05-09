//
// Created by Aaron Berry on 4/30/21.
//

#include <memory>
#include <iostream>
#include <vector>
#include "tools/memory.h"
#include "tools/profile.h"
#include "vector/vector.h"
#include "vector/random_access_iterator.h"

void* operator new(std::size_t sz) // no inline, required by [replacement.functions]/3
{
  std::printf("global op new called, size = %zu\n", sz);
  if (sz == 0)
    ++sz; // avoid std::malloc(0) which may return nullptr on success

  if (void *ptr = std::malloc(sz))
    return ptr;

  throw std::bad_alloc{}; // required by [new.delete.single]/3
}

void operator delete(void* ptr) noexcept
{
  std::puts("global op delete called");
  std::free(ptr);
}

class MyClass {
 public:
  MyClass( ) = default;
  MyClass(int x) : x_(x) {
    std::cout << "Create class" << std::endl;
  }

  ~MyClass() {
    std::cout << "Destroy class" << std::endl;
  }

  // Copy Constructor
  MyClass(const MyClass& my_class);
  // Move Constructor
  MyClass (MyClass&& my_class) noexcept;

  MyClass& operator=(const MyClass& other);

  MyClass& operator= (MyClass&& other) noexcept;

 public:
  int x_ = 0;

};

MyClass::MyClass(const MyClass &my_class) {
  std::cout << "Copy Constructor Called" << std::endl;
  x_ = my_class.x_;
}

MyClass::MyClass(MyClass &&my_class) noexcept {
  std::cout << "Move Constructor Called" << std::endl;
  x_ = std::move(my_class.x_);
  my_class.x_ = 0;
}
MyClass &MyClass::operator=(const MyClass &my_class) {
  x_ = my_class.x_;
  return *this;
}
MyClass &MyClass::operator=(MyClass &&my_class) noexcept {
  x_ = std::move(my_class.x_);
  my_class.x_ = 0;
  return  *this;
}

int main() {
  {
    std::vector<MyClass> vector(4, 0);
    vector.reserve(100);
    std::cout << "\n_______________insert___________________\n";
    vector.insert(vector.begin() + 2, MyClass(1));
    std::cout << "\n______________insert____________________\n";
    for (const auto &item : vector) {
      std::cout << item.x_ << ' ';
    }
  }
  std::cout << "\n__________________________________\n";
  {
    ft::vector<MyClass> vector(4, 0);
    vector.reserve(100);
    std::cout << "\n________________insert__________________\n";
    vector.insert(vector.begin() + 2, MyClass(1));
    std::cout << "\n________________insert__________________\n";
    for (const auto &item : vector) {
      std::cout << item.x_ << ' ';
    }
    std::cout << "\n__________________________________\n";
  }
}
