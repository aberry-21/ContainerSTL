// -*- C++ -*-
//===-------------------------- memory ------------------------------------===//
//
//                     Created by Aaron Berry on 4/30/21.
//
//===----------------------------------------------------------------------===//

#pragma once
#include <new>
#include <utility>
#include "exception.h"
#include "utility.h"

namespace ft {
template<class Tp>
class Allocator;

template<>
class Allocator<void> {
 public:
  typedef void *pointer;
  typedef const void *const_pointer;
  typedef void value_type;

  template<class Up>
  struct rebind { typedef Allocator<Up> other; };
};

template<class T>
class Allocator {
 public:
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T value_type;

  template<class U>
  struct rebind { typedef Allocator<U> other; };

  constexpr Allocator() noexcept = default;
  ~Allocator() noexcept = default;
  constexpr explicit Allocator(__attribute__((unused)) int other) noexcept {};
  template<class U>
  constexpr explicit Allocator(__attribute__((unused))
                               const Allocator<U> &other) noexcept {};

  //  obtains the address of an object, even if operator& is overloaded
  pointer address(reference x) const noexcept {
    return reinterpret_cast<pointer>(&x);
  }

  //  allocates uninitialized storage
  pointer allocate(size_type size,
                   __attribute__((unused)) Allocator<void>::const_pointer hint = nullptr) {
    if (size >= max_size()) {
      throw ft::length_error("allocator<T>::allocate(size_t n) 'n'"
                             " exceeds maximum supported size");
    }
    return reinterpret_cast<pointer>(
        ::operator new(size * sizeof(value_type)));
  }

  //  deallocates storage
  void deallocate(pointer p, size_type) const noexcept {
    ::operator delete(const_cast<typename remove_const<T>::type *>(p));
  }

  //  returns the largest supported allocation size
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  //  constructs an object in allocated storage
  template<class U, class... Args>
  void construct(U *p, Args &&... args) const {
    new(const_cast<
            typename remove_const<T>::type *>(p)) U(std::forward<Args>(args) ...);
  }

  //  destructs an object in allocated storage
  template<class U>
  void destroy(U *p) const {
    p->~U();
  }
};

template<class T, class U>
bool operator==(__attribute__((unused)) const Allocator<T> &target,
                __attribute__((unused)) const Allocator<U> &other) noexcept {
  return true;
}

template<class T, class U>
bool operator!=(const Allocator<T> &target,
                const Allocator<U> &other) noexcept {
  return !operator==<T, U>(target, other);
}
}
