// -*- C++ -*-
//===----------------------- random_access_iterator -----------------------===//
//
//                     Created by Aaron Berry on 5/4/21.
//
//===----------------------------------------------------------------------===//

#pragma once

#include <cstddef>
#include "tools/utility.h"

namespace ft {
template<class T>
class random_access_iterator {
 public:
  typedef T iterator_type;
  typedef std::random_access_iterator_tag iterator_category;
  typedef typename remove_const<T>::type value_type;
  typedef ptrdiff_t difference_type;
  typedef typename qualifier_type<T>::pointer pointer;
  typedef typename qualifier_type<T>::reference reference;

  inline random_access_iterator() = default;
  inline explicit random_access_iterator(pointer data);
  inline random_access_iterator(random_access_iterator<value_type> const &other);
  inline random_access_iterator(random_access_iterator<const value_type> const &other);
  inline random_access_iterator(random_access_iterator &&other) noexcept;
  inline virtual ~random_access_iterator() = default;
  inline random_access_iterator &operator=(random_access_iterator const &other);
  inline random_access_iterator &operator=(random_access_iterator &&other) noexcept;
  inline reference operator*() const;
  inline pointer operator->() const;
  inline random_access_iterator &operator++();
  inline random_access_iterator operator++(int);
  inline random_access_iterator &operator--();
  inline random_access_iterator operator--(int);
  inline random_access_iterator operator+(difference_type n) const;
  inline random_access_iterator &operator+=(difference_type n);
  inline random_access_iterator operator-(difference_type n) const;
  inline random_access_iterator &operator-=(difference_type n);
  inline reference operator[](difference_type index);
  inline pointer base() const;
 private:
  pointer data_;
};
template<class T>
random_access_iterator<T>::random_access_iterator(
    random_access_iterator::pointer data) : data_(data) {}

template<class T>
random_access_iterator<T>::random_access_iterator(
    const random_access_iterator<value_type> &other)
    : data_(other.base()) {}

template<class T>
random_access_iterator<T>::random_access_iterator(random_access_iterator<
    const value_type> const& other) : data_(other.base()) {}

template<class T>
random_access_iterator<T>::random_access_iterator(
    random_access_iterator &&other)
    noexcept : data_(std::move(other.data_)) {}

template<class T>
random_access_iterator<T> &random_access_iterator<T>::operator=(
    const random_access_iterator &other) {
  if (this == &other) {
    return *this;
  }
  data_ = other.data_;
  return *this;
}

template<class T>
random_access_iterator<T> &random_access_iterator<T>::operator=(
    random_access_iterator &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  data_ = nullptr;
  std::swap(other.data_, data_);
  return *this;
}

template<class T>
typename random_access_iterator<T>::reference
    random_access_iterator<T>::operator*() const {
  return *data_;
}

template<class T>
typename random_access_iterator<T>::pointer
    random_access_iterator<T>::operator->() const {
  return std::addressof(operator*());
}

template<class T>
random_access_iterator<T> &random_access_iterator<T>::operator++() {
  ++data_;
  return *this;
}

template<class T>
random_access_iterator<T> random_access_iterator<T>::operator++(int) {
  random_access_iterator tmp(*this);
  ++(*this);
  return tmp;
}
template<class T>

random_access_iterator<T> &random_access_iterator<T>::operator--() {
  --data_;
  return *this;
}

template<class T>
random_access_iterator<T> random_access_iterator<T>::operator--(int) {
  random_access_iterator tmp(*this);
  --(*this);
  return tmp;
}

template<class T>
random_access_iterator<T> random_access_iterator<T>::operator+(
    random_access_iterator::difference_type n) const {
  random_access_iterator new_data(*this);
  new_data += n;
  return new_data;
}

template<class T>
random_access_iterator<T> &random_access_iterator<T>::operator+=(
    random_access_iterator::difference_type n) {
  data_ += n;
  return *this;
}

template<class T>
random_access_iterator<T> random_access_iterator<T>::operator-(
    random_access_iterator::difference_type n) const {
  return (*this + (-n));
}

template<class T>
random_access_iterator<T> &random_access_iterator<T>::operator-=(
    random_access_iterator::difference_type n) {
  *this += -n;
  return *this;
}

template<class T>
typename random_access_iterator<T>::reference
    random_access_iterator<T>::operator[](
        random_access_iterator::difference_type index) {
  return (data_[index]);
}

template<class T>
typename random_access_iterator<T>::pointer
    random_access_iterator<T>::base() const {
  return data_;
}

template<class Iter1, class Iter2>
inline
bool operator==(const random_access_iterator<Iter1> &x,
                const random_access_iterator<Iter2> &y) {
  return (x.base() == y.base());
}

template<class Iter1, class Iter2>
inline
bool operator<(const random_access_iterator<Iter1> &x,
               const random_access_iterator<Iter2> &y) {
  return (x.base() < y.base());
}

template<class Iter1, class Iter2>
inline
bool operator!=(const random_access_iterator<Iter1> &x,
                const random_access_iterator<Iter2> &y) {
  return !(x == y);
}

template<class Iter1, class Iter2>
inline
bool operator>(const random_access_iterator<Iter1> &x,
               const random_access_iterator<Iter2> &y) {
  return (y < x);
}

template<class Iter1, class Iter2>
inline
bool operator>=(const random_access_iterator<Iter1> &x,
                const random_access_iterator<Iter2> &y) {
  return !(x < y);
}

template<class Iter1, class Iter2>
inline
bool operator<=(const random_access_iterator<Iter1> &x,
                const random_access_iterator<Iter2> &y) {
  return !(y < x);
}

template<class Iter1>
inline
bool operator!=(const random_access_iterator<Iter1> &x,
                const random_access_iterator<Iter1> &y) {
  return !(x == y);
}

template<class Iter1>
inline
bool operator>(const random_access_iterator<Iter1> &x,
               const random_access_iterator<Iter1> &y) {
  return (y < x);
}

template<class Iter1>
inline
bool operator>=(const random_access_iterator<Iter1> &x,
                const random_access_iterator<Iter1> &y) {
  return !(x < y);
}

template<class Iter1>
inline
bool operator<=(const random_access_iterator<Iter1> &x,
                const random_access_iterator<Iter1> &y) {
  return !(y < x);
}

template<class Iter1, class Iter2>
inline
auto
operator-(const random_access_iterator<Iter1> &x,
          const random_access_iterator<Iter2> &y)
-> decltype(x.base() - y.base()) {
  return x.base() - y.base();
}

template<class Iter>
inline
random_access_iterator<Iter>
operator+(typename random_access_iterator<Iter>::difference_type n,
          random_access_iterator<Iter> x) {
  x += n;
  return x;
}

}
