// -*- C++ -*-
//===------------------------ reverse iterator ----------------------------===//
//
//                     Created by Aaron Berry on 5/4/21.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "utility.h"

namespace ft {
template<class Iter>
class reverse_iterator {
 public:
  typedef Iter iterator_type;
  typedef typename Iter::iterator_category iterator_category;
  typedef typename Iter::value_type value_type;
  typedef typename Iter::difference_type difference_type;
  typedef typename Iter::pointer pointer;
  typedef typename Iter::reference reference;

  inline reverse_iterator() = default;
  inline explicit reverse_iterator(iterator_type it);
  template<class Iterator>
  inline reverse_iterator(const reverse_iterator<Iterator> &rev_it);
  inline virtual ~reverse_iterator() = default;
  inline reverse_iterator &operator=(reverse_iterator const &x);
  inline reference operator*();
  inline pointer operator->();
  inline reverse_iterator operator++();
  inline reverse_iterator operator++(int);
  inline reverse_iterator operator--();
  inline reverse_iterator operator--(int);
  inline reverse_iterator operator+(difference_type n) const;
  inline reverse_iterator operator-(difference_type n) const;
  inline reverse_iterator &operator+=(difference_type n);
  inline reverse_iterator &operator-=(difference_type n);
  inline reference operator[](difference_type index);
  inline iterator_type base() const;
 private:
  iterator_type current_;
};

template<class Iter>
reverse_iterator<Iter>::reverse_iterator(iterator_type it) : current_(it) {}

template<class Iter>
template<class Iterator>
reverse_iterator<Iter>::reverse_iterator(
    const reverse_iterator<Iterator> &rev_it) : current_(rev_it.base()) {}

template<class Iter>
reverse_iterator<Iter> &reverse_iterator<Iter>::operator=(
    const reverse_iterator &x) {
  if (this == &x) {
    return *this;
  }
  current_ = x.current_;
  return *this;
}

template<class Iter>
typename reverse_iterator<Iter>::reference reverse_iterator<Iter>::operator*() {
  Iter tmp = current_;
  return *--tmp;
}

template<class Iter>
typename reverse_iterator<Iter>::pointer reverse_iterator<Iter>::operator->() {
  return std::addressof(operator*());
}

template<class Iter>
reverse_iterator<Iter> reverse_iterator<Iter>::operator++() {
  --current_;
  return *this;
}

template<class Iter>
reverse_iterator<Iter> reverse_iterator<Iter>::operator++(int) {
  reverse_iterator tmp(*this);
  --current_;
  return (tmp);
}

template<class Iter>
reverse_iterator<Iter> reverse_iterator<Iter>::operator--() {
  ++current_;
  return *this;
}

template<class Iter>
reverse_iterator<Iter> reverse_iterator<Iter>::operator--(int) {
  reverse_iterator tmp(*this);
  ++current_;
  return (tmp);
}

template<class Iter>
reverse_iterator<Iter>
    reverse_iterator<Iter>::operator+(difference_type n) const {
  return reverse_iterator(current_ - n);
}

template<class Iter>
reverse_iterator<Iter>
    reverse_iterator<Iter>::operator-(difference_type n) const {
  return reverse_iterator(current_ + n);
}

template<class Iter>
reverse_iterator<Iter> &reverse_iterator<Iter>::operator+=(difference_type n) {
  current_ -= n;
  return (*this);
}

template<class Iter>
reverse_iterator<Iter> &reverse_iterator<Iter>::operator-=(difference_type n) {
  current_ += n;
  return (*this);
}

template<class Iter>
typename reverse_iterator<Iter>::reference reverse_iterator<Iter>::operator[](
    difference_type index) {
  return *(*this + index);
}

template<class Iter>
typename reverse_iterator<Iter>::iterator_type
    reverse_iterator<Iter>::base() const {
  return current_;
}

template<class Iter1, class Iter2>
inline
bool operator==(const reverse_iterator<Iter1> &x,
                const reverse_iterator<Iter2> &y) {
  return (x.base() == y.base());
}

template<class Iter1, class Iter2>
inline
bool operator<(const reverse_iterator<Iter1> &x,
               const reverse_iterator<Iter2> &y) {
  return (x.base() > y.base());
}

template<class Iter1, class Iter2>
inline
bool operator!=(const reverse_iterator<Iter1> &x,
                const reverse_iterator<Iter2> &y) {
  return (x.base() != y.base());
}

template<class Iter1, class Iter2>
inline
bool operator>(const reverse_iterator<Iter1> &x,
               const reverse_iterator<Iter2> &y) {
  return (x.base() < y.base());
}

template<class Iter1, class Iter2>
inline
bool operator>=(const reverse_iterator<Iter1> &x,
                const reverse_iterator<Iter2> &y) {
  return (x.base() <= y.base());
}

template<class Iter1, class Iter2>
inline
bool operator<=(const reverse_iterator<Iter1> &x,
                const reverse_iterator<Iter2> &y) {
  return  (x.base() >= y.base());
}

template<class Iter1>
inline
bool operator<(const reverse_iterator<Iter1> &x,
                const reverse_iterator<Iter1> &y) {
  return (x.base() > y.base());
}

template<class Iter1>
inline
bool operator>(const reverse_iterator<Iter1> &x,
               const reverse_iterator<Iter1> &y) {
  return (x.base() < y.base());
}

template<class Iter1>
inline
bool operator>=(const reverse_iterator<Iter1> &x,
                const reverse_iterator<Iter1> &y) {
  return (x.base() <= y.base());
}

template<class Iter1>
inline
bool operator<=(const reverse_iterator<Iter1> &x,
                const reverse_iterator<Iter1> &y) {
  return (x.base() >= y.base());
}

template<class Iter1, class Iter2>
inline
auto
operator-(const reverse_iterator<Iter1> &x,
          const reverse_iterator<Iter2> &y)
-> decltype(y.base() - x.base()) {
  return y.base() - x.base();
}

}
