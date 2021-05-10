//
// Created by Aaron Berry on 5/4/21.
//

#pragma once

#include <cstddef>
#include "../tools/utility.h"

namespace ft {
  template <class T>
  class random_access_iterator {
   public:
    typedef T                                           iterator_type;
    typedef std::random_access_iterator_tag             iterator_category;
    typedef typename RemoveConst<T>::type               value_type;
    typedef ptrdiff_t                                   difference_type;
    typedef typename QualifierType <T>::pointer         pointer;
    typedef typename QualifierType <T>::reference       reference;

    random_access_iterator() = default;

    explicit random_access_iterator(pointer data)
                                              : data_(data) {}

    random_access_iterator(random_access_iterator<value_type> const& other);

    random_access_iterator(random_access_iterator<const value_type> const& other);

    random_access_iterator(random_access_iterator&& other) noexcept;

    virtual ~random_access_iterator() = default;

    random_access_iterator& operator=(random_access_iterator const& other) {
      if (this == &other) {
        return *this;
      }
      data_ = other.data_;
      return *this;
    }

    random_access_iterator& operator=(random_access_iterator&& other) noexcept {
      if (this == &other) {
        return *this;
      }
      data_ = nullptr;
      std::swap(other.data_, data_);
      return *this;
    }

    reference operator*() const {
      return *data_;
    }

    pointer operator->() const {
      return std::addressof(operator*());
    }

    random_access_iterator& operator++() {
      ++data_;
      return *this;
    }

    random_access_iterator operator++(int) {
      random_access_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    random_access_iterator& operator--() {
      --data_;
      return *this;
    }

    random_access_iterator operator--(int) {
      random_access_iterator tmp(*this);
      --(*this);
      return tmp;
    }

    random_access_iterator operator+(difference_type n) const {
      random_access_iterator new_data(*this);
      new_data += n;
      return new_data;
    }

    random_access_iterator& operator+=(difference_type n) {
      data_ += n;
      return *this;
    }

    random_access_iterator operator-(difference_type n) const {
      return (*this + (-n));
    }

    random_access_iterator& operator-=(difference_type n) {
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

  template<class T>
  random_access_iterator<T>::random_access_iterator(const random_access_iterator<
      value_type> &other)
      : data_(other.base()) {}

  template<class T>
  random_access_iterator<T>::random_access_iterator(random_access_iterator &&other) noexcept
      : data_(std::move(other.data_)) {}

template<class T>
  random_access_iterator<T>::random_access_iterator(random_access_iterator<const
  value_type> const& other)
      : data_(other.base()) {}

template <class Iter1, class Iter2>
  inline
  bool operator==(const random_access_iterator<Iter1>& x,
                  const random_access_iterator<Iter2>& y) {
    return (x.base() == y.base());
  }

  template <class Iter1, class Iter2>
  inline
  bool operator<(const random_access_iterator<Iter1>& x,
                  const random_access_iterator<Iter2>& y) {
    return (x.base() < y.base());
  }

  template <class Iter1, class Iter2>
  inline
  bool operator!=(const random_access_iterator<Iter1>& x,
                 const random_access_iterator<Iter2>& y) {
    return !(x == y);
  }

  template <class Iter1, class Iter2>
  inline
  bool operator>(const random_access_iterator<Iter1>& x,
                 const random_access_iterator<Iter2>& y) {
    return (y < x);
  }

  template <class Iter1, class Iter2>
  inline
  bool operator>=(const random_access_iterator<Iter1>& x,
                 const random_access_iterator<Iter2>& y) {
    return !(x < y);
  }

  template <class Iter1, class Iter2>
  inline
  bool operator<=(const random_access_iterator<Iter1>& x,
                 const random_access_iterator<Iter2>& y) {
    return !(y < x);
  }


  template <class Iter1>
  inline
  bool operator!=(const random_access_iterator<Iter1>& x,
                  const random_access_iterator<Iter1>& y) {
    return !(x == y);
  }

  template <class Iter1>
  inline
  bool operator>(const random_access_iterator<Iter1>& x,
                 const random_access_iterator<Iter1>& y) {
    return (y < x);
  }

  template <class Iter1>
  inline
  bool operator>=(const random_access_iterator<Iter1>& x,
                  const random_access_iterator<Iter1>& y) {
    return !(x < y);
  }

  template <class Iter1>
  inline
  bool operator<=(const random_access_iterator<Iter1>& x,
                  const random_access_iterator<Iter1>& y) {
    return !(y < x);
  }

  template <class Iter1, class Iter2>
  inline
  auto
  operator-(const random_access_iterator<Iter1>& x,
            const random_access_iterator<Iter2>& y)
            -> decltype(x.base() - y.base()) {
    return x.base() - y.base();
  }

  template <class Iter>
  inline
  random_access_iterator<Iter>
  operator+(typename random_access_iterator<Iter>::difference_type n,
            random_access_iterator<Iter> x) {
    x += n;
    return x;
  }

}

