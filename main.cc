//
// Created by Aaron Berry on 4/30/21.
//

#include <memory>
#include <iostream>
#include <vector>
#include "tools/memory.h"
#include "tools/profile.h"
#include "vector/vector.h"
#include "vector/RandomAccessIterator.h"

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
int main() {
//    {
//      LOG_DURATION("my");
//      ft::Vector<const int> the_vector(1000000);
//    }
//    {
//      LOG_DURATION("stl");
//      std::vector<int> the_vector(1000000);
//    }
//    {
//      LOG_DURATION("stl");
//      std::vector<int> foo (30,0);
//      std::vector<int> bar (5,0);
//
//      std::cout << "capacity of bar: " << int(bar.capacity()) << '\n';
//      std::cout << "capacity of foo: " << int(foo.capacity()) << '\n';
//      bar = foo;
//      foo = std::vector<int>();
//      std::cout << "capacity of bar: " << int(bar.capacity()) << '\n';
//      std::cout << "capacity of foo: " << int(foo.capacity()) << '\n';
//      std::cout << "Size of foo: " << int(foo.size()) << '\n';
//      std::cout << "Size of bar: " << int(bar.size()) << '\n';
//    }
//    std::cout << "______________________" << '\n';
//
//    {
//      LOG_DURATION("my");
//      ft::Vector<int> foo (30,0);
//      ft::Vector<int> bar (5,0);
//
//      std::cout << "capacity of bar: " << int(bar.capacity()) << '\n';
//      std::cout << "capacity of foo: " << int(foo.capacity()) << '\n';
//      bar = foo;
//
//      foo = ft::Vector<int>();
//      std::cout << "capacity of bar: " << int(bar.capacity()) << '\n';
//      std::cout << "capacity of foo: " << int(foo.capacity()) << '\n';
//      std::cout << "Size of foo: " << int(foo.size()) << '\n';
//      std::cout << "Size of bar: " << int(bar.size()) << '\n';
//    }

//  {
//    std::vector<int> myvector (3,2);
//    std::cout << "capacity " << myvector.capacity() << '\n';
//    myvector.reserve(4);
//    std::cout << "capacity " << myvector.capacity() << '\n';
//    std::cout << "size " << myvector.size() << '\n';
//  }
//  std::cout << "____________________________________" << '\n';
//  {
//    ft::Vector<int> myvector (3,2);
//    std::cout << "capacity " << myvector.capacity() << '\n';
//    myvector.resize(10, myvector[1]);
//    std::cout << "capacity " << myvector.capacity() << '\n';
//    std::cout << "size " << myvector.size() << '\n';
//    for (int i = 0; i < myvector.size(); ++i) {
//      std::cout << ' ' << myvector[i];
//    }
//    std::cout << '\n';
//  }

  {
    std::vector<const int> myvector (5,2);
    std::vector<const int> myvector2 (5,1);



    std::vector<const int> myvector_2(myvector.end(), myvector.begin());




    for (const auto &item : myvector_2) {
      std::cout << item << ' ' ;
    }
    std::cout << '\n' ;
  }
  std::cout << "____________________________________" << '\n';
  {
    ft::Vector<const int> myvector (3,2);
    ft::Vector<const int> myvector_2(myvector);

    auto iter = myvector.begin();
    for (const auto &item : myvector) {
      std::cout << item << ' ' ;
    }
    std::cout << '\n' ;
  }


}