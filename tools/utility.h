//
// Created by Aaron Berry on 5/4/21.
//

#pragma once

namespace ft {

  template <class T>
  struct QualifierType
  {
    typedef T* pointer;
    typedef T& reference;
  };

  template <class T>
  struct QualifierType <const T>
  {
    typedef const T* pointer;
    typedef const T& reference;
  };

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

  template<class T>
  inline
  typename std::remove_reference<T>::type&& move(T &&t) noexcept {
    typedef typename std::remove_reference<T>::type Up;
    return static_cast<Up &&>(t);
  }

  template<class T>
  inline
  void swap(T &a, T &b) noexcept {
    T c(ft::move(a));
    a = ft::move(b);
    b = ft::move(c);
  }
}