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
}
