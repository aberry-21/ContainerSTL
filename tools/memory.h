// -*- C++ -*-
//===-------------------------- memory ------------------------------------===//
//
//                     Created by Aaron Berry on 4/30/21.
//
//                        Allocator implementation
//
//===----------------------------------------------------------------------===//

/*
    memory synopsis

namespace ft
{
template <class T>
class allocator
{
public:
    typedef size_t                                size_type;
    typedef ptrdiff_t                             difference_type;
    typedef T*                                    pointer;
    typedef const T*                              const_pointer;
    typedef typename add_lvalue_reference<T>::type       reference;
      typedef typename add_lvalue_reference<const T>::type const_reference;
    typedef T                                     value_type;

    template <class U> struct rebind {typedef allocator<U> other;};

    constexpr allocator() noexcept;                      // constexpr in C++20
    constexpr allocator(const allocator&) noexcept;      // constexpr in C++20
    template <class U>
      constexpr allocator(const allocator<U>&) noexcept; // constexpr in C++20
    ~allocator();
    pointer address(reference x) const noexcept;
    const_pointer address(const_reference x) const noexcept;
    pointer allocate(size_type, allocator<void>::const_pointer hint = 0);
    void deallocate(pointer p, size_type n) noexcept;
    size_type max_size() const noexcept;
    template<class U, class... Args>
        void construct(U* p, Args&&... args);
    template <class U>
        void destroy(U* p);
};

template <class T, class U>
bool operator==(const allocator<T>&, const allocator<U>&) noexcept;

template <class T, class U>
bool operator!=(const allocator<T>&, const allocator<U>&) noexcept;
*/

#pragma once
#include <new>

namespace ft {

  template <class T>
  struct RemoveConst
  {
    typedef T type;
  };

  template <class T>
  struct RemoveConst<const T>
  {
    typedef T type;
  };

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

    constexpr Allocator() noexcept {};
    ~Allocator() {};
    constexpr Allocator(const Allocator &other) noexcept {};
    template<class U>
    constexpr Allocator(const Allocator<U> &other) noexcept {};

  //  obtains the address of an object, even if operator& is overloaded
    pointer address(reference x) const noexcept {
      return reinterpret_cast<pointer>(&x);
    }

  //  allocates uninitialized storage
    pointer allocate(size_type size, Allocator<void>::const_pointer hint = 0) {
      if (size >= max_size())
        throw ;
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
  bool operator==(const Allocator<T> &target, const Allocator<U> &other) noexcept {
    return true;
  }

  template<class T, class U>
  bool operator!=(const Allocator<T> &target, const Allocator<U> &other) noexcept {
    return !operator==<T, U>(target, other);
  }
}