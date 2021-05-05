//
// Created by Aaron Berry on 5/4/21.
//

#pragma once

#include "tools/utility.h"

namespace ft {
  template<class T>
  class ReverseIterator {
   public:
    typedef T                                           iterator_type;
    typedef std::random_access_iterator_tag             iterator_category;
    typedef typename RemoveConst<T>::type               value_type;
    typedef ptrdiff_t                                   difference_type;
    typedef typename QualifierType <T>::pointer         pointer;
    typedef typename QualifierType <T>::reference       reference;

    ReverseIterator() = default;
    
    explicit ReverseIterator(iterator_type it)
                                              : it_(it) {}

    template <class Iter>
    explicit ReverseIterator(const reverse_iterator<Iter>& rev_it)
                                              : it_(rev_it.it) {}

    ReverseIterator(ReverseIterator&& other) noexcept
                                      : it_(move(other.it_)) {}

    virtual ~ReverseIterator() = default;

    ReverseIterator& operator=(ReverseIterator const& other) {
      if (this == &other) {
        return *this;
      }
      it_ = other.it_;
      return *this;
    }

    ReverseIterator& operator=(ReverseIterator&& other) noexcept {
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

    ReverseIterator operator++() {
      --it_;
      return *this;
    }

    ReverseIterator operator++(int) {
      ReverseIterator temp = *this;
      ++(*this);
      return temp;
    }

    ReverseIterator& operator--() {
      ++it_;
      return *this;
    }

    ReverseIterator operator--(int) {
      ReverseIterator tmp(*this);
      --(*this);
      return tmp;
    }

    ReverseIterator operator+(difference_type n) const {
      ReverseIterator new_data(*this);
      new_data += n;
      return new_data;
    }

    ReverseIterator& operator+=(difference_type n) {
      it_ - n;
      return *this;
    }

    ReverseIterator operator-(difference_type n) const {
      return (*this + (-n));
    }

    ReverseIterator& operator-=(difference_type n) {
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
  bool operator==(const ReverseIterator<Iter1>& x,
                  const ReverseIterator<Iter2>& y) {
    return (x.base() == y.base());
  }
  
  template <class Iter1, class Iter2>
  inline
  bool operator<(const ReverseIterator<Iter1>& x,
                 const ReverseIterator<Iter2>& y) {
    return (x.base() > y.base());
  }
  
  template <class Iter1, class Iter2>
  inline
  bool operator!=(const ReverseIterator<Iter1>& x,
                  const ReverseIterator<Iter2>& y) {
    return !(x == y);
  }
  
  template <class Iter1, class Iter2>
  inline
  bool operator>(const ReverseIterator<Iter1>& x,
                 const ReverseIterator<Iter2>& y) {
    return (y < x);
  }
  
  template <class Iter1, class Iter2>
  inline
  bool operator>=(const ReverseIterator<Iter1>& x,
                  const ReverseIterator<Iter2>& y) {
    return !(x < y);
  }
  
  template <class Iter1, class Iter2>
  inline
  bool operator<=(const ReverseIterator<Iter1>& x,
                  const ReverseIterator<Iter2>& y) {
    return !(y < x);
  }
  
  
  template <class Iter1>
  inline
  bool operator!=(const ReverseIterator<Iter1>& x,
                  const ReverseIterator<Iter1>& y) {
    return !(x == y);
  }
  
  template <class Iter1>
  inline
  bool operator>(const ReverseIterator<Iter1>& x,
                 const ReverseIterator<Iter1>& y) {
    return (y < x);
  }
  
  template <class Iter1>
  inline
  bool operator>=(const ReverseIterator<Iter1>& x,
                  const ReverseIterator<Iter1>& y) {
    return !(x < y);
  }
  
  template <class Iter1>
  inline
  bool operator<=(const ReverseIterator<Iter1>& x,
                  const ReverseIterator<Iter1>& y) {
    return !(y < x);
  }
  
  template <class Iter1, class Iter2>
  inline
  auto
  operator-(const ReverseIterator<Iter1>& x,
            const ReverseIterator<Iter2>& y)
  -> decltype(y.base() - x.base()) {
    return y.base() - x.base();
  }
  
  template <class Iter>
  inline
  ReverseIterator<Iter>
  operator+(typename ReverseIterator<Iter>::difference_type n,
            ReverseIterator<Iter> x) {
    x += n;
    return x;
  }


}
