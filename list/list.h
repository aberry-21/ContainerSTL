//===------------------------------- list ---------------------------------===//
// -*- C++ -*-
//
//                     Created by Aaron Berry on 5/14/21.
//
//===----------------------------------------------------------------------===//

#pragma once

#include <utility>

#include "tools/memory.h"
#include "tools/reverse_iterator.h"
#include "bidirectional_iterator.h"
#include "tools/utility.h"
#include "list_base.h"

namespace ft {

template<class T, class Alloc = ft::Allocator<T> >
class list {
 private:
  struct Node_;
/*
**                                Public Types
*/
 public:
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef ft::bidirectional_iterator<T, Node_> iterator;
  typedef ft::bidirectional_iterator<const T, Node_> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef typename Alloc::template rebind<Node_>::other node_alloc_;
/*
**                           Public Member Functions
*/
  inline list() noexcept(std::is_nothrow_default_constructible<allocator_type>::value);
  inline explicit list(const allocator_type &a);
  inline explicit list(size_type n, const allocator_type &a = allocator_type());
  inline list(size_type n,
              const value_type &value,
              const allocator_type &a = allocator_type());
  template<class Iter>
  inline list(Iter first, Iter last, const allocator_type &a = allocator_type(),
              typename std::enable_if
                  <!std::numeric_limits<Iter>::is_specialized>::type * = 0);
  inline list(const list &list, const allocator_type &a = allocator_type());
  inline list(list &&x)
  noexcept(std::is_nothrow_move_constructible<allocator_type>::value);
  inline list(list &&x, const allocator_type &a);
  inline list(std::initializer_list<value_type> l,
              const allocator_type &a = allocator_type());
  inline virtual ~list();
  inline list &operator=(const list &x);
  inline list &operator=(list &&x)
  noexcept(std::is_nothrow_move_assignable<allocator_type>::value);
  inline list &operator=(std::initializer_list<value_type>);
  template<class Iter>
  inline void assign(Iter first, Iter last,
                     typename std::enable_if
                         <!std::numeric_limits<Iter>::is_specialized>::type * = 0);
  inline void assign(size_type n, const value_type &t);
  inline void assign(std::initializer_list<value_type>);
  inline allocator_type get_allocator() const noexcept;
  inline iterator begin() noexcept;
  inline const_iterator begin() const noexcept;
  inline iterator end() noexcept;
  inline const_iterator end() const noexcept;
  inline reverse_iterator rbegin() noexcept;
  inline const_reverse_iterator rbegin() const noexcept;
  inline reverse_iterator rend() noexcept;
  inline const_reverse_iterator rend() const noexcept;
  inline const_iterator cbegin() const noexcept;
  inline const_iterator cend() const noexcept;
  inline const_reverse_iterator crbegin() const noexcept;
  inline const_reverse_iterator crend() const noexcept;
  inline reference front();
  inline const_reference front() const;
  inline reference back();
  inline const_reference back() const;
  inline bool empty() const noexcept;
  inline size_type size() const noexcept;
  inline size_type max_size() const noexcept;
  template<class... Args>
  inline void emplace_front(Args &&... args);
  inline void pop_front();
  template<class... Args>
  void emplace_back(Args &&... args);
  inline void pop_back();
  inline void push_front(const value_type &x);
  inline void push_front(value_type &&x);
  inline void push_back(const value_type &x);
  inline void push_back(value_type &&x);
  template<class... Args>
  inline iterator emplace(const_iterator position, Args &&... args);
  inline iterator insert(const_iterator position, const value_type &x);
  inline iterator insert(const_iterator position, value_type &&x);
  inline iterator insert(const_iterator position,
                         size_type n,
                         const value_type &x);
  template<class Iter>
  inline iterator insert(const_iterator position, Iter first, Iter last,
                         typename std::enable_if
                             <!std::numeric_limits<Iter>::is_specialized>::type * = 0);
  inline iterator insert(const_iterator position,
                         std::initializer_list<value_type> il);
  inline iterator erase(const_iterator position);
  inline iterator erase(const_iterator first, const_iterator last);
  inline void resize(size_type sz);
  inline void resize(size_type sz, const value_type &c);
  inline void swap(list &)
  noexcept(std::allocator_traits<allocator_type>::is_always_equal::value);
  inline void clear() noexcept;
  inline void splice(const_iterator position, list &x);
  inline void splice(const_iterator position, list &&x);
  inline void splice(const_iterator position, list &x, const_iterator i);
  inline void splice(const_iterator position, list &&x, const_iterator i);
  inline void splice(const_iterator position, list &x, const_iterator first,
                     const_iterator last);
  inline void splice(const_iterator position, list &&x, const_iterator first,
                     const_iterator last);
  inline void remove(const value_type &value);
  template<class Pred>
  inline void remove_if(Pred pred);
  void unique();
  template<class BinaryPredicate>
  void unique(BinaryPredicate binary_pred);
  void merge(list &x);
  void merge(list &&x);
  template<class Compare>
  void merge(list &x, Compare comp);
  template<class Compare>
  void merge(list &&x, Compare comp);
  void sort();
  template<class Compare>
  void sort(Compare comp);
  void reverse() noexcept;
 private:
  struct Node_ {
    Node_ *next_;
    Node_ *prev_;
    value_type value_;
  };
  Node_ *head_;
  Alloc alloc_;
  node_alloc_ n_alloc_;
  size_type size_;
 protected:
  Node_ *get_node_();
  void put_node_(Node_ *p);
  void init_head_();
  void link_node_(const_iterator position, Node_ *p);
  Node_ *create_node_without_value_();
  Node_ *create_node_with_lvalue_(const value_type &x);
  template<typename... Args>
  Node_ *create_node_with_args_(Args &&... args);
  void default_append_(const_iterator position, size_type n);
  void value_append_(const_iterator position, size_type n, const value_type &x);
  template<class Iter>
  size_type range_append_(const_iterator position, Iter first, Iter last);
};

template<class T, class Alloc>
typename list<T, Alloc>::Node_ *list<T, Alloc>::create_node_without_value_() {
  Node_ *p = get_node_();
  try {
    alloc_.construct(&p->value_);
  } catch (...) {
    put_node_(p);
    throw;
  }
  return p;
}

template<class T, class Alloc>
typename list<T, Alloc>::Node_ *list<T, Alloc>::
create_node_with_lvalue_(const value_type &x) {
  Node_ *p = get_node_();
  try {
    alloc_.construct(&p->value_, x);
  } catch (...) {
    put_node_(p);
    throw;
  }
  return p;
}

template<class T, class Alloc>
template<typename... Args>
typename list<T, Alloc>::Node_ *list<T, Alloc>::
create_node_with_args_(Args &&... args) {
  Node_ *p = get_node_();
  try {
    alloc_.construct(&p->value_, std::forward<T>(args) ...);
  } catch (...) {
    put_node_(p);
    throw;
  }
  return p;
}

template<class T, class Alloc>
void list<T, Alloc>::link_node_(list::const_iterator position, list::Node_ *p) {
  auto pos = position.base();
  p->next_ = pos;
  p->prev_ = pos->prev_;
  pos->prev_->next_ = p;
  pos->prev_ = p;
}

template<class T, class Alloc>
void list<T, Alloc>::init_head_() {
  head_ = get_node_();
  head_->prev_ = head_;
  head_->next_ = head_;
}

template<class T, class Alloc>
typename list<T, Alloc>::Node_ *list<T, Alloc>::get_node_() {
  return n_alloc_.allocate(1);
}

template<class T, class Alloc>
void list<T, Alloc>::put_node_(list::Node_ *p) {
  return n_alloc_.deallocate(p, 1);
}

template<class T, class Alloc>
void list<T, Alloc>::default_append_(const_iterator position,
                                     list::size_type n) {
  for (size_type i = 0; i < n; ++i) {
    try {
      link_node_(position, create_node_without_value_());
    } catch (...) {
      erase(std::next(position, -static_cast<difference_type>(i)), position);
      throw std::runtime_error("Error value append");
    }
  }
}

template<class T, class Alloc>
void list<T, Alloc>::value_append_(const_iterator position,
                                   list::size_type n,
                                   const value_type &x) {
  for (size_type i = 0; i < n; ++i) {
    try {
      link_node_(position, create_node_with_lvalue_(x));
    } catch (...) {
      erase(std::next(position, -static_cast<difference_type>(i)), position);
      throw std::runtime_error("Error value append");
    }
  }
}

template<class T, class Alloc>
template<class Iter>
typename list<T, Alloc>::size_type list<T, Alloc>::range_append_(
    list::const_iterator position,
    Iter first,
    Iter last) {
  size_type size = 0;
  for (; first != last; ++first) {
    try {
      link_node_(position, create_node_with_lvalue(*first));
      ++size;
    } catch (...) {
      erase(std::next(position, -static_cast<difference_type>(size)), position);
      throw std::runtime_error("Error range append");
    }
  }
  return size;
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::begin() noexcept {
  return iterator(head_->next_);
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator list<T, Alloc>::begin() const noexcept {
  return const_iterator(head_->next_);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::end() noexcept {
  return iterator(head_);
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator list<T, Alloc>::end() const noexcept {
  return const_iterator(head_);
}

template<class T, class Alloc>
typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rbegin() noexcept {
  return reverse_iterator(end());
}

template<class T, class Alloc>
typename list<T, Alloc>::const_reverse_iterator list<T,
                                                     Alloc>::rbegin() const noexcept {
  return const_reverse_iterator(end());
}

template<class T, class Alloc>
typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rend() noexcept {
  return reverse_iterator(begin());
}

template<class T, class Alloc>
typename list<T, Alloc>::const_reverse_iterator list<T,
                                                     Alloc>::rend() const noexcept {
  return const_reverse_iterator(begin());
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator list<T,
                                             Alloc>::cbegin() const noexcept {
  return begin();
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator list<T, Alloc>::cend() const noexcept {
  return end();
}

template<class T, class Alloc>
typename list<T, Alloc>::const_reverse_iterator list<T,
                                                     Alloc>::crbegin() const noexcept {
  return rbegin();
}

template<class T, class Alloc>
typename list<T, Alloc>::const_reverse_iterator list<T,
                                                     Alloc>::crend() const noexcept {
  return rend();
}

template<class T, class Alloc>
typename list<T, Alloc>::reference list<T, Alloc>::front() {
  return head_->next_->value_;
}

template<class T, class Alloc>
typename list<T, Alloc>::const_reference list<T, Alloc>::front() const {
  return head_->next_->value_;
}

template<class T, class Alloc>
typename list<T, Alloc>::reference list<T, Alloc>::back() {
  return head_->prev_->value_;
}

template<class T, class Alloc>
typename list<T, Alloc>::const_reference list<T, Alloc>::back() const {
  return head_->prev_->value_;
}

template<class T, class Alloc>
void list<T, Alloc>::push_back(const value_type &x) {
  link_node_(cend(), create_node_with_lvalue_(x));
  ++size_;
}

template<class T, class Alloc>
void list<T, Alloc>::push_back(value_type &&x) {
  link_node_(cend(), create_node_with_args_(std::forward<T>(x)));
  ++size_;
}

template<class T, class Alloc>
void list<T, Alloc>::push_front(const value_type &x) {
  link_node_(cbegin(), create_node_with_args_(std::forward<T>(x)));
  ++size_;
}

template<class T, class Alloc>
void list<T, Alloc>::push_front(value_type &&x) {
  link_node_(cbegin(), create_node_with_args_(std::forward<T>(x)));
  ++size_;
}

template<class T, class Alloc>
list<T, Alloc>::list() noexcept(std::is_nothrow_default_constructible<
    allocator_type>::value) : head_(), alloc_(), size_(0) {
  init_head_();
}

template<class T, class Alloc>
list<T, Alloc>::list(const allocator_type &a)
    : head_(), alloc_(a), size_(0) {
  init_head_();
}

template<class T, class Alloc>
list<T, Alloc>::list(list::size_type n, const allocator_type &a)
    : head_(), alloc_(a), size_(n) {
  init_head_();
  default_append_(cend(), n);
}

template<class T, class Alloc>
list<T, Alloc>::list(list::size_type n,
                     const value_type &value,
                     const allocator_type &a)
    : head_(), alloc_(a), size_(n) {
  init_head_();
  value_append_(cend(), n, value);
}

template<class T, class Alloc>
void list<T, Alloc>::clear() noexcept {
  erase(begin(), end());
  size_ = 0;
}

template<class T, class Alloc>
list<T, Alloc>::~list() {
  erase(begin(), end());
  put_node_(head_);
}

template<class T, class Alloc>
void list<T, Alloc>::pop_back() {
  erase(const_iterator(head_->prev_), end());
  --size_;
}

template<class T, class Alloc>
void list<T, Alloc>::pop_front() {
  erase(const_iterator(head_->next_), end());
  --size_;
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::erase(
    list::const_iterator position) {
  return erase(position, ++position);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::erase(
    list::const_iterator first,
    list::const_iterator last) {
  Node_ *prev = std::next(first, -1).base();
  for (; first != last;) {
    ++first;
    Node_ *p = std::next(first, -1).base();
    alloc_.destroy(&p->value_);
    put_node_(p);
  }
  prev->next_ = head_;
  head_->prev_ = prev;
  return (last);
}

template<class T, class Alloc>
template<class Iter>
list<T, Alloc>::list(Iter first, Iter last, const allocator_type &a,
                     typename std::enable_if
                         <!std::numeric_limits<Iter>::is_specialized>::type *)
    : alloc_(a), size_(0) {
  init_head_();
  try {
    range_append_(cend(), first, last);
  } catch (...) {
    put_node_(head_);
  }
}

template<class T, class Alloc>
list<T, Alloc>::list(const list &list, const allocator_type &a) : list::list(
    list.begin(),
    list.end(),
    a) {}

template<class T, class Alloc>
list<T, Alloc>::list(list &&x) noexcept(std::is_nothrow_move_constructible<
    allocator_type>::value) : size_(0) {
  init_head_();
  *this = std::move(x);
}

template<class T, class Alloc>
list<T, Alloc>::list(list &&x, const allocator_type &a)
    : list::list(x, get_allocator()), alloc_(a) {}

template<class T, class Alloc>
list<T, Alloc>::list(std::initializer_list<value_type> l,
                     const allocator_type &a)
    : list::list(
    l.begin(),
    l.end(),
    a) {}

template<class T, class Alloc>
list<T, Alloc> &list<T, Alloc>::operator=(const list &x) {
  if (this == &x) {
    return *this;
  }
  *this = std::move(list(x.begin(), x.end(), x.alloc_));
  return *this;
}

template<class T, class Alloc>
list<T, Alloc> &list<T, Alloc>::operator=(list &&x) noexcept(
std::is_nothrow_move_assignable<allocator_type>::value) {
  if (this == &x) {
    return *this;
  }
  clear();
  swap(x);
  return *this;
}

template<class T, class Alloc>
list<T, Alloc> &list<T, Alloc>::operator=(initializer_list<value_type> l) {
  if (this == &l) {
    return *this;
  }
  *this = std::move(list(l.begin(), l.end(), get_allocator()));
  return *this;
}

template<class T, class Alloc>
template<class Iter>
void list<T, Alloc>::assign(Iter first, Iter last,
                            typename std::enable_if
                                <!std::numeric_limits<Iter>::is_specialized>::type *) {
  list<T, Alloc> lst_(first, last, get_allocator());
  *this = std::move(lst_);
}

template<class T, class Alloc>
void list<T, Alloc>::assign(list::size_type n, const value_type &t) {
  list<T, Alloc> lst_(n, t, get_allocator());
  *this = std::move(lst_);
}

template<class T, class Alloc>
void list<T, Alloc>::assign(initializer_list<value_type> l) {
  *this = std::move(l);
}

template<class T, class Alloc>
typename list<T, Alloc>::allocator_type list<T,
                                             Alloc>::get_allocator() const noexcept {
  return alloc_;
}

template<class T, class Alloc>
bool list<T, Alloc>::empty() const noexcept {
  return !size_;
}

template<class T, class Alloc>
typename list<T, Alloc>::size_type list<T, Alloc>::size() const noexcept {
  return size_;
}
template<class T, class Alloc>
typename list<T, Alloc>::size_type list<T, Alloc>::max_size() const noexcept {
  return std::min<size_type>(alloc_.max_size(),
                             std::numeric_limits<difference_type>::max());
}

template<class T, class Alloc>
template<class... Args>
void list<T, Alloc>::emplace_front(Args &&... args) {
  link_node_(cbegin(), create_node_with_args_(std::forward<T>(args)) ...);
  ++size_;
}

template<class T, class Alloc>
template<class... Args>
void list<T, Alloc>::emplace_back(Args &&... args) {
  link_node_(cend(), create_node_with_args_(std::forward<T>(args)) ...);
  ++size_;
}

template<class T, class Alloc>
void list<T,
          Alloc>::swap(list &x) noexcept(std::allocator_traits<allocator_type>::is_always_equal::value) {
  std::swap(head_, x.head_);
  std::swap(size_, x.size_);
  std::swap(alloc_, x.alloc_);
}

template<class T, class Alloc>
void list<T, Alloc>::splice(list::const_iterator position, list &x) {
  if (x.size_ == 0) {
    return;
  }
  Node_ *p = position.base();
  x.head_->prev_->next_ = p;
  x.head_->next_->prev_ = p->prev_;
  p->prev_->next_ = x.head_->next_;
  p->prev_ = x.head_->prev_;
  size_ += x.size_;
  x.head_->prev_ = x.head_->next_ = x.head_;
  x.size_ = 0;
}

template<class T, class Alloc>
void list<T, Alloc>::splice(list::const_iterator position, list &&x) {
  splice(position, x);
}

template<class T, class Alloc>
void list<T, Alloc>::splice(list::const_iterator position,
                            list &x,
                            list::const_iterator first,
                            list::const_iterator last) {
  size_type size = std::distance(first, last);
  if (size == 0) {
    return;
  }
  x.size_ -= size;
  size_ += size;
  Node_ *n_pos = position.base();
  Node_ *n_first = first.base();
  Node_ *n_last = last.base();
  n_first->prev_->next_ = n_last;
  n_last = n_last->prev_;
  n_last->next_->prev_ = n_first->prev_;
  n_pos->prev_->next_ = n_first;
  n_first->prev_ = n_pos->prev_;
  n_pos->prev_ = n_last;
  n_last->next_ = n_pos;
}

template<class T, class Alloc>
void list<T, Alloc>::splice(list::const_iterator position,
                            list &&x,
                            list::const_iterator first,
                            list::const_iterator last) {
  splice(position, x, first, last);
}

template<class T, class Alloc>
void list<T, Alloc>::splice(list::const_iterator position,
                            list &x,
                            list::const_iterator i) {
  splice(position, x, i, ++i);
}

template<class T, class Alloc>
void list<T, Alloc>::splice(list::const_iterator position,
                            list &&x,
                            list::const_iterator i) {
  splice(position, x, i);
}

template<class T, class Alloc>
template<class... Args>
typename list<T, Alloc>::iterator list<T, Alloc>::emplace(
    list::const_iterator position,
    Args &&... args) {
  Node_ *node = create_node_with_args_(std::forward<T>(args) ...);
  link_node_(position, node);
  ++size_;
  return iterator(node);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(
    list::const_iterator position,
    const value_type &x) {
  return insert(position, 1, x);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(
    list::const_iterator position,
    value_type &&x) {
  Node_ *node = create_node_with_args(std::move_if_noexcept(x));
  link_node_(position, node);
  ++size_;
  return iterator(node);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(
    list::const_iterator position,
    list::size_type n,
    const value_type &x) {
  value_append_(position, n, x);
  size_ += n;
  return iterator(--position);
}

template<class T, class Alloc>
template<class Iter>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(
    list::const_iterator position,
    Iter first,
    Iter last,
    typename std::enable_if
        <!std::numeric_limits<Iter>::is_specialized>::type *) {
  size_ += range_append_(position, first, last);
  return iterator(--position);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(
    list::const_iterator position,
    std::initializer_list<value_type> il) {
  return insert(position, il.begin(), il.end());
}

template<class T, class Alloc>
void list<T, Alloc>::resize(list::size_type sz) {
  if (sz > size_) {
    default_append_(sz - size_);
  } else if (sz < size_) {
    const_iterator iter = begin();
    std::advance(iter, sz);
    erase(iter, end());
  }
}

template<class T, class Alloc>
void list<T, Alloc>::resize(list::size_type sz, const value_type &c) {
  if (sz > size_) {
    value_append(sz - size_, c);
  } else if (sz < size_) {
    const_iterator iter = begin();
    std::advance(iter, sz);
    erase(iter, end());
  }
}

template<class T, class Alloc>
void list<T, Alloc>::remove(const value_type &value) {
  for (const_iterator i = begin(), e = end(); i != e;) {
    if (*i == value) {
      const_iterator j = std::next(i);
      for (; j != e && *i == value; ++j);
      i = erase(i, j);
      if (i != e) {
        ++i;
      }
    } else {
      ++i;
    }
  }
}

template<class T, class Alloc>
template<class Pred>
void list<T, Alloc>::remove_if(Pred pred) {
  for (const_iterator i = begin(), e = end(); i != e;) {
    if (pred(*i)) {
      const_iterator j = std::next(i);
      for (; j != e && pred(*j); ++j);
      i = erase(i, j);
      if (i != e) {
        ++i;
      }
    } else {
      ++i;
    }
  }
}

template<class T, class Alloc>
template<class BinaryPredicate>
void list<T, Alloc>::unique(BinaryPredicate binary_pred) {
  for (const_iterator i = begin(), e = end(); i != e;) {
    const_iterator j = std::next(i);
    for (; j != e && binary_pred(*i, *j); ++j);
    if (++i != j) {
      i = erase(i, j);
    }
  }
}

template<class T, class Alloc>
void list<T, Alloc>::unique() {
  unique(std::equal_to<value_type>());
}

template<class T, class Alloc>
void list<T, Alloc>::merge(list &x) {
  merge(x, std::less<value_type>());
}

template<class T, class Alloc>
template<class Compare>
void list<T, Alloc>::merge(list &x, Compare comp) {
  if (this == std::addressof(x)) {
    return;
  }
  iterator b_1 = begin();
  iterator e_1 = end();
  iterator b_2 = x.begin();
  iterator e_2 = x.end();
  while (b_1 != e_1 && b_2 != e_2) {
    if (comp(*b_2, *b_1)) {
      iterator current_2 = std::next(b_2);
      for (; current_2 != e_2 && comp(*current_2, *b_1); ++current_2);
      splice(b_1, x, b_2, current_2);
      b_2 = current_2;
    }
    ++b_1;
  }
  splice(e_1, x);
}

template<class T, class Alloc>
template<class Compare>
void list<T, Alloc>::merge(list &&x, Compare comp) {
  merge(x, comp);
}

template<class T, class Alloc>
void list<T, Alloc>::merge(list &&x) {
  merge(x);
}

template<class T, class Alloc>
void list<T, Alloc>::reverse() noexcept {
  if (size_ <= 1) {
    return;
  }
  iterator e = end();
  for (iterator i = begin(); i != e;) {
    std::swap(i.base()->prev_, i.base()->next_);
    std::advance(i, -1);
  }
  std::swap(head_->next_, head_->prev_);
}

template<class T, class Alloc>
template<class Compare>
void list<T, Alloc>::sort(Compare comp) {
  if (size_ <= 1)
    return;
  list divided(get_allocator());
  iterator b = begin();
  std::advance(b, size_ / 2);
  divided.splice(divided.begin(), *this, b, end());
  divided.sort();
  sort();
  merge(divided, comp);
}

template<class T, class Alloc>
void list<T, Alloc>::sort() {
  sort(std::less<value_type>());
}

template<class T, class Alloc>
inline
bool
operator==(const list<T, Alloc> &x, const list<T, Alloc> &y) {
  return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

template<class T, class Alloc>
inline
bool
operator<(const list<T, Alloc> &x, const list<T, Alloc> &y) {
  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template<class T, class Alloc>
inline
bool
operator!=(const list<T, Alloc> &x, const list<T, Alloc> &y) {
  return !(x == y);
}

template<class T, class Alloc>
inline
bool
operator>(const list<T, Alloc> &x, const list<T, Alloc> &y) {
  return y < x;
}

template<class T, class Alloc>
inline
bool
operator>=(const list<T, Alloc> &x, const list<T, Alloc> &y) {
  return !(x < y);
}

template<class T, class Alloc>
inline
bool
operator<=(const list<T, Alloc> &x, const list<T, Alloc> &y) {
  return !(y < x);
}

template<class T, class Alloc>
inline
void
swap(list<T, Alloc> &x, list<T, Alloc> &y) noexcept(noexcept(x.swap(y))) {
  x.swap(y);
}

}
