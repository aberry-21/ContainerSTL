//
// Created by Aaron Berry on 5/4/21.
//

#pragma once

#include <cstddef>
#include "tools/utility.h"

namespace ft {
  template <class T>
  class RandomAccessIterator {
   public:
    typedef T                                           iterator_type;
    typedef std::random_access_iterator_tag             iterator_category;
    typedef typename RemoveConst<T>::type               value_type;
    typedef ptrdiff_t                                   difference_type;
    typedef typename QualifierType <T>::pointer         pointer;
    typedef typename QualifierType <T>::reference       reference;

    RandomAccessIterator() = default;

    explicit RandomAccessIterator(pointer data)
                                              : data_(data) {}

    RandomAccessIterator(RandomAccessIterator const& other)
                                              : data_(other.data_) {}

    RandomAccessIterator(RandomAccessIterator&& other) noexcept
                                              : data_(move(other.data_)) {}

    virtual ~RandomAccessIterator() = default;

    RandomAccessIterator& operator=(RandomAccessIterator const& other) {
      if (this == &other) {
        return *this;
      }
      data_ = other.data_;
      return *this;
    }

    RandomAccessIterator& operator=(RandomAccessIterator&& other) noexcept {
      if (this == &other) {
        return *this;
      }
      data_ = nullptr;
      swap(other.data_, data_);
      return *this;
    }

    reference operator*() const {
      return *data_;
    }

    pointer operator->() const {
      return addressof(operator*());
    }

    RandomAccessIterator& operator++() {
      ++data_;
      return *this;
    }

    RandomAccessIterator operator++(int) {
      RandomAccessIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    RandomAccessIterator& operator--() {
      --data_;
      return *this;
    }

    RandomAccessIterator operator--(int) {
      RandomAccessIterator tmp(*this);
      --(*this);
      return tmp;
    }

    RandomAccessIterator operator+(difference_type n) const {
      RandomAccessIterator new_data(*this);
      new_data += n;
      return new_data;
    }

    RandomAccessIterator& operator+=(difference_type n) {
      data_ + n;
      return *this;
    }

    RandomAccessIterator operator-(difference_type n) const {
      return (*this + (-n));
    }

    RandomAccessIterator& operator-=(difference_type n) {
      *this += -n;
      return *this;
    }

    reference operator[](difference_type index) {
      return (data_[index]);
    }

    pointer base() const {
      return data_;
    }

   private:
    pointer data_;
  };

  template <class Iter1, class Iter2>
  inline
  bool operator==(const RandomAccessIterator<Iter1>& x,
                  const RandomAccessIterator<Iter2>& y) {
    return (x.base() == y.base());
  }

  template <class Iter1, class Iter2>
  inline
  bool operator<(const RandomAccessIterator<Iter1>& x,
                  const RandomAccessIterator<Iter2>& y) {
    return (x.base() < y.base());
  }

  template <class Iter1, class Iter2>
  inline
  bool operator!=(const RandomAccessIterator<Iter1>& x,
                 const RandomAccessIterator<Iter2>& y) {
    return !(x == y);
  }

  template <class Iter1, class Iter2>
  inline
  bool operator>(const RandomAccessIterator<Iter1>& x,
                 const RandomAccessIterator<Iter2>& y) {
    return (y < x);
  }

  template <class Iter1, class Iter2>
  inline
  bool operator>=(const RandomAccessIterator<Iter1>& x,
                 const RandomAccessIterator<Iter2>& y) {
    return !(x < y);
  }

  template <class Iter1, class Iter2>
  inline
  bool operator<=(const RandomAccessIterator<Iter1>& x,
                 const RandomAccessIterator<Iter2>& y) {
    return !(y < x);
  }


  template <class Iter1>
  inline
  bool operator!=(const RandomAccessIterator<Iter1>& x,
                  const RandomAccessIterator<Iter1>& y) {
    return !(x == y);
  }

  template <class Iter1>
  inline
  bool operator>(const RandomAccessIterator<Iter1>& x,
                 const RandomAccessIterator<Iter1>& y) {
    return (y < x);
  }

  template <class Iter1>
  inline
  bool operator>=(const RandomAccessIterator<Iter1>& x,
                  const RandomAccessIterator<Iter1>& y) {
    return !(x < y);
  }

  template <class Iter1>
  inline
  bool operator<=(const RandomAccessIterator<Iter1>& x,
                  const RandomAccessIterator<Iter1>& y) {
    return !(y < x);
  }

  template <class Iter1, class Iter2>
  inline
  auto
  operator-(const RandomAccessIterator<Iter1>& x,
            const RandomAccessIterator<Iter2>& y)
            -> decltype(x.base() - y.base()) {
    return x.base() - y.base();
  }

  template <class Iter>
  inline
  RandomAccessIterator<Iter>
  operator+(typename RandomAccessIterator<Iter>::difference_type n,
            RandomAccessIterator<Iter> x) {
    x += n;
    return x;
  }

}

