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
//
//void operator delete(void* ptr) noexcept
//{
//  std::puts("global op delete called");
//  std::free(ptr);
//}

class MyClass {
 public:
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

int main()
{
//  {
//
//    std::vector<MyClass> from_vector;
//    from_vector.reserve(10);
//    from_vector.emplace_back(0);
//    from_vector.emplace_back(1);
//    from_vector.emplace_back(2);
//    from_vector.emplace_back(3);
//    for (const auto &item : from_vector) {
//      std::cout << item.x_ << ' ';
//    }
//    std::cout << '\n';
//    std::cout << "_____________insert___________" << std::endl;
//    from_vector.insert(from_vector.end() - 4 , 3, 22);
//    std::cout << "______________________________" << std::endl;
//    for (const auto &item : from_vector) {
//      std::cout << item.x_ << ' ';
//    }
//    std::cout << '\n';
//  }
//  {
//    std::cout << "_______________MY_______________" << std::endl;
//    ft::Vector<MyClass> from_vector(4);
//    from_vector[0].x_ = 0;
//    from_vector[1].x_ = 1;
//    from_vector[2].x_ = 2;
//    from_vector[3].x_ = 3;
//    for (const auto &item : from_vector) {
//      std::cout << item.x_ << ' ';
//    }
//    from_vector.reserve(10);
//    from_vector.move_range(from_vector.end() - 4 , 3);
//    for (const auto &item : from_vector) {
//      std::cout << item.x_ << ' ';
//    }
//    std::cout << '\n';
//  }
//  {
//    std::vector<MyClass> vector;
//    auto iter = vector.insert(vector.begin(),5, 1);
//    std::cout << '\n';
//    iter = vector.insert(vector.begin(),2, 4);
//    std::cout << iter->x_;
//    for (const auto &item : vector) {
//      std::cout << item.x_ << ' ';
//    }
//    std::cout << '\n';
//  }

  {
    ft::Vector<MyClass> vector;
//    vector.reserve(100);
    auto iter = vector.insert(vector.begin(),2, 1);
    std::cout << "__________________________________\n";
    iter = vector.insert(vector.begin() + 2,2, -1);
    std::cout << "__________________________________\n";
    for (const auto &item : vector) {
      std::cout << item.x_ << ' ';
    }
    std::cout << '\n';
  }
  std::cout << "__________________________________\n";
  {
    std::vector<MyClass> vector;
//    vector.reserve(100);
    auto iter = vector.insert(vector.begin(),2, 1);
    std::cout << "__________________________________\n";
    iter = vector.insert(vector.begin() + 2,2, -1);
    std::cout << "__________________________________\n";

    for (const auto &item : vector) {
      std::cout << item.x_ << ' ';
    }
    std::cout << '\n';
  }

}


void Test1() {
  {
    ft::Vector<MyClass> vector;
    ft::Vector<MyClass> vector2;
    vector.insert(vector2.begin(), 10, 10);
  }
  std::cout << "__________________________________\n";
  {
    std::vector<MyClass> vector;
    std::vector<MyClass> vector2;
    vector.insert(vector2.begin(), 10, 10);
  }
}

void Test2() {
  {
    ft::Vector<MyClass> vector;
  }
  std::cout << "__________________________________\n";
  {
    std::vector<MyClass> vector;
  }
}

void Test3() {
  {
    ft::Vector<MyClass> vector;
  }
  std::cout << "__________________________________\n";
  {
    std::vector<MyClass> vector;
  }
}
