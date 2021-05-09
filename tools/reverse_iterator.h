//
// Created by Aaron Berry on 5/4/21.
//

#pragma once

#include "tools/utility.h"

namespace ft {
  template < class Iterator >
  class reverse_iterator {
   public:

    // Typedef -------------------------------------------------------------

    typedef Iterator                             iterator_type;
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;

    // ---------------------------------------------------------------------

    // Constructor - Destructor --------------------------------------------

    reverse_iterator() : it_()
    {}
    explicit reverse_iterator(iterator_type it) : it_(it)
    {}
    template <class Iter>
    reverse_iterator(const reverse_iterator<Iter> & rev_it)
        : it_(rev_it.base())
    {}
    virtual ~reverse_iterator()
    {}

    // ---------------------------------------------------------------------

    // Member-funcs --------------------------------------------------------

    iterator_type base() const {
      return this->it_;
    }

    // ---------------------------------------------------------------------

    // Operators -----------------------------------------------------------

    // '='
    reverse_iterator & operator=(reverse_iterator const & x) {
      if (this == &x) {
        return *this;
      }
      this->it_ = x.base();
      return *this;
    }
    // '*'
    reference       operator*() {
      Iterator tmp = it_;
      return *--tmp;
    }

    // '->'
    pointer         operator->() {
      return this->it_.get_pointer();
    }

    // '++iter'
    reverse_iterator operator++() {
      --this->it_;
      return (*this);
    }

    // 'iter++'
    reverse_iterator operator++(int) {
      reverse_iterator tmp(*this);
      --this->it_;
      return (tmp);
    }

    // '--iter'
    reverse_iterator operator--() {
      ++this->it_;
      return (*this);
    }

    // 'iter--'
    reverse_iterator operator--(int) {
      reverse_iterator tmp(*this);
      ++this->it_;
      return (tmp);
    }

    // '+'
    reverse_iterator operator+(difference_type n) const {
      return reverse_iterator(this->it_ - n);
    }

    // '-'
    reverse_iterator operator-(difference_type n) const {
      return (reverse_iterator(this->it_ + n));
    }

    // '+='
    reverse_iterator &operator+=(difference_type n) {
      this->it_ -= n;
      return (*this);
    }

    // '-='
    reverse_iterator &operator-=(difference_type n) {
      this->it_ += n;
      return (*this);
    }

    // '<'
    bool            operator<(reverse_iterator const & x) const {
      return this->it_ > x.base();
    }

    // '>'
    bool            operator>(reverse_iterator const & x) const {
      return this->it_ < x.base();
    }

    // '>='
    bool            operator<=(reverse_iterator const & x) const {
      return this->it_ >= x.base();
    }

    // '>='
    bool            operator>=(reverse_iterator const & x) const {
      return this->it_ <= x.base();
    }

    reference       operator[](difference_type index) {
      return this->it_[-index];
    }

    // ---------------------------------------------------------------------

   private:
    iterator_type it_;
  };

// Relational Operators ----------------------------------------------------

// 'n + iter'
template < class Iterator >
reverse_iterator<Iterator> operator+
    (
        typename reverse_iterator<Iterator>::difference_type n,
        reverse_iterator<Iterator> const & x
    )
{
  return x + n;
}

// // 'iter - iter'
template < class Iterator >
typename reverse_iterator<Iterator>::difference_type operator-
    (
        reverse_iterator<Iterator> const & a,
        reverse_iterator<Iterator> const & b
    )
{
  return b.base() - a.base();
}

template<class lIterator, class rIterator>
bool operator>
    (
        const reverse_iterator<lIterator> & a,
        const reverse_iterator<rIterator> & b
    )
{
  return a.base() > b.base();
}

template<class lIterator, class rIterator>
bool operator>=
    (
        const reverse_iterator<lIterator> & a,
        const reverse_iterator<rIterator> & b
    )
{
  return a.base() >= b.base();
}

template<class lIterator, class rIterator>
bool operator<
    (
        const reverse_iterator<lIterator> & a,
        const reverse_iterator<rIterator> & b
    )
{
  return a.base() < b.base();
}

template<class lIterator, class rIterator>
bool operator<=
    (
        const reverse_iterator<lIterator> & a,
        const reverse_iterator<rIterator> & b
    )
{
  return a.base() <= b.base();
}

template<class lIterator, class rIterator>
bool operator==
    (
        const reverse_iterator<lIterator> & a,
        const reverse_iterator<rIterator> & b
    )
{
  return a.base() == b.base();
}

template<class lIterator, class rIterator>
bool operator!=
    (
        const reverse_iterator<lIterator> & a,
        const reverse_iterator<rIterator> & b
    )
{
  return a.base() != b.base();
}

}
