// -*- C++ -*-
//===---------------------------- utility ---------------------------------===//
//
//                     Created by Aaron Berry on 5/4/21.
//
//===----------------------------------------------------------------------===//
#pragma once

namespace ft {
  template <class T>
  struct qualifier_type
  {
    typedef T* pointer;
    typedef T& reference;
  };

  template <class T>
  struct qualifier_type <const T>
  {
    typedef const T* pointer;
    typedef const T& reference;
  };

  template <class T>
  struct remove_const
  {
    typedef T type;
  };

  template <class T>
  struct remove_const<const T>
  {
    typedef T type;
  };
}
