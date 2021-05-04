// -*- C++ -*-
//===-------------------------- memory ------------------------------------===//
//
//                     Created by Aaron Berry on 4/30/21.
//
//                        Allocator implementation
//
//===----------------------------------------------------------------------===//

#pragma once
#include <new>
#include "Exception.h"
#include "tools/utility.h"

namespace ft {
  template <class Tp> class Allocator;

  template<>
  class Allocator<void> {
   public:
    typedef void        *pointer;
    typedef const void  *const_pointer;
    typedef void        value_type;

    template<class Up>
    struct rebind { typedef Allocator<Up> other; };
  };

  template<class T>
  class Allocator {
   public:
    typedef size_t                                              size_type;
    typedef ptrdiff_t                                           difference_type;
    typedef T*                                                  pointer;
    typedef const T*                                            const_pointer;
    typedef T&                                                  reference;
    typedef const T&                                            const_reference;
    typedef T                                                   value_type;

    template<class U>
    struct rebind { typedef Allocator<U> other; };

    constexpr Allocator() noexcept = default;
    ~Allocator() noexcept = default;
    constexpr explicit Allocator(int other) noexcept {};
    template<class U>
    constexpr explicit Allocator(const Allocator<U> &other) noexcept {};

  //  obtains the address of an object, even if operator& is overloaded
    pointer address(reference x) const noexcept {
      return reinterpret_cast<pointer>(&x);
    }

  //  allocates uninitialized storage
    pointer allocate(size_type size,
                     Allocator<void>::const_pointer hint = nullptr) {
      if (size >= max_size()) {
        throw ft::Length_error("allocator<const T>::allocate(size_t n) 'n'"
                               " exceeds maximum supported size");
      }
      pointer ptr;
        return reinterpret_cast<pointer>(
            ::operator new(size * sizeof(value_type)));
    }

  //  deallocates storage
    void deallocate(pointer p, size_type) const noexcept {
      ::operator delete(const_cast<typename RemoveConst<T>::type*>(p));
    }

  //  returns the largest supported allocation size
    size_type max_size() const noexcept {
      return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }

  //  constructs an object in allocated storage
    template<class U, class... Args>
    void construct(U *p, Args &&... args) {
      new(const_cast<typename RemoveConst<T>::type*>(p)) U(args...);
    }

  //  destructs an object in allocated storage
    template<class U>
    void destroy(U *p) {
      p->~U();
    }
  };

  template<class T, class U>
  bool operator==(const Allocator<T> &target,
                  const Allocator<U> &other) noexcept {
    return true;
  }

  template<class T, class U>
  bool operator!=(const Allocator<T> &target,
                  const Allocator<U> &other) noexcept {
    return !operator==<T, U>(target, other);
  }
}