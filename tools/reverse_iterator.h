//
// Created by Aaron Berry on 5/4/21.
//

#pragma once

#include "tools/utility.h"

namespace ft {
  template<class T>
  class reverse_iterator {
   public:
    typedef T                                           iterator_type;
    typedef std::random_access_iterator_tag             iterator_category;
    typedef typename RemoveConst<T>::type               value_type;
    typedef ptrdiff_t                                   difference_type;
    typedef typename QualifierType <T>::pointer         pointer;
    typedef typename QualifierType <T>::reference       reference;

    reverse_iterator() = default;
    
    explicit reverse_iterator(iterator_type it)
                                              : it_(it) {}

    template <class Iter>
    explicit reverse_iterator(const reverse_iterator<Iter>& rev_it)
                                              : it_(rev_it.it) {}

    reverse_iterator(reverse_iterator&& other) noexcept
                                      : it_(move(other.it_)) {}

    virtual ~reverse_iterator() = default;

    reverse_iterator& operator=(reverse_iterator const& other) {
      if (this == &other) {
        return *this;
      }
      it_ = other.it_;
      return *this;
    }

    reverse_iterator& operator=(reverse_iterator&& other) noexcept {
      if (this == &other) {
        return *this;
      }
      it_ = nullptr;
      swap(other.it_, it_);
      return *this;
    }

    iterator_type base() const {
      return it_;
    }

    reference operator*() const {
      return *it_;
    }

    pointer operator->() const {
      return addressof(operator*());
    }

    reverse_iterator operator++() {
      --it_;
      return *this;
    }

    reverse_iterator operator++(int) {
      reverse_iterator temp = *this;
      ++(*this);
      return temp;
    }

    reverse_iterator& operator--() {
      ++it_;
      return *this;
    }

    reverse_iterator operator--(int) {
      reverse_iterator tmp(*this);
      --(*this);
      return tmp;
    }

    reverse_iterator operator+(difference_type n) const {
      reverse_iterator new_data(*this);
      new_data += n;
      return new_data;
    }

    reverse_iterator& operator+=(difference_type n) {
      it_ - n;
      return *this;
    }

    reverse_iterator operator-(difference_type n) const {
      return (*this + (-n));
    }

    reverse_iterator& operator-=(difference_type n) {
      *this += -n;
      return *this;
    }

    reference operator[](difference_type index) {
      return (it_[-index]);
    }

   private:
    iterator_type it_;
  };

  template <class Iter1, class Iter2>
  inline
  bool operator==(const reverse_iterator<Iter1>& x,
                  const reverse_iterator<Iter2>& y) {
    return (x.base() == y.base());
  }
  
  template <class Iter1, class Iter2>
  inline
  bool operator<(const reverse_iterator<Iter1>& x,
                 const reverse_iterator<Iter2>& y) {
    return (x.base() > y.base());
  }
  
  template <class Iter1, class Iter2>
  inline
  bool operator!=(const reverse_iterator<Iter1>& x,
                  const reverse_iterator<Iter2>& y) {
    return !(x == y);
  }
  
  template <class Iter1, class Iter2>
  inline
  bool operator>(const reverse_iterator<Iter1>& x,
                 const reverse_iterator<Iter2>& y) {
    return (y < x);
  }
  
  template <class Iter1, class Iter2>
  inline
  bool operator>=(const reverse_iterator<Iter1>& x,
                  const reverse_iterator<Iter2>& y) {
    return !(x < y);
  }
  
  template <class Iter1, class Iter2>
  inline
  bool operator<=(const reverse_iterator<Iter1>& x,
                  const reverse_iterator<Iter2>& y) {
    return !(y < x);
  }
  
  
  template <class Iter1>
  inline
  bool operator!=(const reverse_iterator<Iter1>& x,
                  const reverse_iterator<Iter1>& y) {
    return !(x == y);
  }
  
  template <class Iter1>
  inline
  bool operator>(const reverse_iterator<Iter1>& x,
                 const reverse_iterator<Iter1>& y) {
    return (y < x);
  }
  
  template <class Iter1>
  inline
  bool operator>=(const reverse_iterator<Iter1>& x,
                  const reverse_iterator<Iter1>& y) {
    return !(x < y);
  }
  
  template <class Iter1>
  inline
  bool operator<=(const reverse_iterator<Iter1>& x,
                  const reverse_iterator<Iter1>& y) {
    return !(y < x);
  }
  
  template <class Iter1, class Iter2>
  inline
  auto
  operator-(const reverse_iterator<Iter1>& x,
            const reverse_iterator<Iter2>& y)
  -> decltype(y.base() - x.base()) {
    return y.base() - x.base();
  }
  
  template <class Iter>
  inline
  reverse_iterator<Iter>
  operator+(typename reverse_iterator<Iter>::difference_type n,
            reverse_iterator<Iter> x) {
    x += n;
    return x;
  }

}
