// -*- C++ -*-
//===------------------------------- list ---------------------------------===//
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
  typedef ft::bidirectional_iterator<T> iterator;
  typedef ft::bidirectional_iterator<const T> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
/*
**                           Public Member Functions
*/
  inline list() noexcept(is_nothrow_default_constructible<allocator_type>::value);
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
  noexcept(is_nothrow_move_constructible<allocator_type>::value);
  inline list(list &&x, const allocator_type &a);
  inline list(initializer_list<value_type> l,
              const allocator_type &a = allocator_type());
  inline virtual ~list();
  inline list &operator=(const list &x);
  inline list &operator=(list &&x)
  noexcept(
  allocator_type::propagate_on_container_move_assignment::value &&
      is_nothrow_move_assignable<allocator_type>::value);
  inline list &operator=(initializer_list<value_type>);
  template<class Iter>
  inline void assign(Iter first, Iter last,
                     typename std::enable_if
                         <!std::numeric_limits<Iter>::is_specialized>::type * = 0);
  inline void assign(size_type n, const value_type &t);
  inline void assign(initializer_list<value_type>);

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
  void pop_front();
  template<class... Args>
  void emplace_back(Args &&... args);
  void pop_back();
  void push_front(const value_type &x);
  void push_front(value_type &&x);
  inline void push_back(const value_type &x);
  inline void push_back(value_type &&x);
  template<class... Args>
  iterator emplace(const_iterator position, Args &&... args);
  iterator insert(const_iterator position, const value_type &x);
  iterator insert(const_iterator position, value_type &&x);
  iterator insert(const_iterator position, size_type n, const value_type &x);
  template<class Iter>
  iterator insert(const_iterator position, Iter first, Iter last,
                  typename std::enable_if
                      <!std::numeric_limits<Iter>::is_specialized>::type * = 0);
  iterator insert(const_iterator position, initializer_list<value_type> il);

  iterator erase(const_iterator position);
  iterator erase(const_iterator first, const_iterator last);

  void resize(size_type sz);
  void resize(size_type sz, const value_type &c);

  void swap(list &)
  noexcept(allocator_traits<allocator_type>::is_always_equal::value);
  inline void clear() noexcept;

  void splice(const_iterator position, list &x);
  void splice(const_iterator position, list &&x);
  void splice(const_iterator position, list &x, const_iterator i);
  void splice(const_iterator position, list &&x, const_iterator i);
  void splice(const_iterator position, list &x, const_iterator first,
              const_iterator last);
  void splice(const_iterator position, list &&x, const_iterator first,
              const_iterator last);

  void remove(const value_type &value);
  template<class Pred>
  void remove_if(Pred pred);
  void unique();
  template<class BinaryPredicate>
  void unique(BinaryPredicate binary_pred);
  void merge(list &x);
  void merge(list &&x);
  template<class Compare>
  void merge(list &x, Compare comp);
  template <class Compare>
  void merge(list&& x, Compare comp);
  void sort();
  template <class Compare>
  void sort(Compare comp);
  void reverse() noexcept;

 private:
  list_base<T, Alloc> head_;
  ft::Allocator<T> alloc_;

  void link_node_back(list_node<T> *p);
  void link_node_front(list_node<T> *p);
  list_node<T> *create_node_without_value();
  list_node<T> *create_node_with_lvalue(const value_type &x);
  template<typename... Args>
  list_node<T> *create_node_with_args(Args &&... args);
  void unlink_node(list_node<T> *p);
  void delete_node(list_node<T> *p);
  void link_node(const_iterator position, list_node<T> *p);
  void default_append(size_type n);
  void value_append(size_type n, const value_type &x);
  void erase_at_end(const_iterator position);
  unsigned long get_size(const_iterator first, const_iterator last);

  list_node<T> *split(list_node<T> *head);
  template<class Compare>
  list_node<T> *merge(list_node<T> *first, list_node<T> *second, Compare comp);
  template<class Compare>
  list_node<T> *mergeSort(list_node<T> *head, Compare comp);
};

template<class T, class Alloc>
list<T, Alloc>::list()
noexcept(is_nothrow_default_constructible<allocator_type>::value)
    : head_(), alloc_() {}

template<class T, class Alloc>
list<T, Alloc>::list(const allocator_type &a)
    : alloc_(a), head_() {}

template<class T, class Alloc>
list<T, Alloc>::list(list::size_type n, const allocator_type &a) : alloc_(a) {
  for (size_type i = 0; i < n; ++i) {
    list_node<T> *p = create_node_without_value();
    link_node_back(p);
  }
}

template<class T, class Alloc>
list_node<T> *list<T, Alloc>::create_node_without_value() {
  list_node<T> *p = head_.get_node();
  try {
    alloc_.construct(&p->data_);
  } catch (...) {
    head_.put_node(p);
    throw;
  }
  return p;
}

template<class T, class Alloc>
list_node<T> *list<T, Alloc>::create_node_with_lvalue(const value_type &x) {
  list_node<T> *p = head_.get_node();
  try {
    alloc_.construct(&p->data_, x);
  } catch (...) {
    head_.put_node(p);
    throw;
  }
  return p;
}

template<class T, class Alloc>
template<typename... Args>
list_node<T> *list<T, Alloc>::create_node_with_args(Args &&... args) {
  list_node<T> *p = head_.get_node();
  try {
    alloc_.construct(&p->data_, std::forward<T>(args) ...);
  } catch (...) {
    head_.put_node(p);
    throw;
  }
  return p;
}

template<class T, class Alloc>
void list<T, Alloc>::push_back(const value_type &x) {
  list_node<T> *p = create_node_with_lvalue(x);
  link_node_back(p);
}

template<class T, class Alloc>
void list<T, Alloc>::push_back(value_type &&x) {
  list_node<T> *p = create_node_with_args(std::forward<T>(x));
  link_node_back(p);
}

template<class T, class Alloc>
list<T, Alloc>::list(list::size_type n,
                     const value_type &value,
                     const allocator_type &a) : alloc_(a) {
  for (size_type i = 0; i < n; ++i) {
    push_back(value);
  }
}

template<class T, class Alloc>
void list<T, Alloc>::unlink_node(list_node<T> *p) {
  p->prev_->next_ = p->next_;
  p->next_->prev_ = p->prev_;
  --head_.size_;
}

template<class T, class Alloc>
void list<T, Alloc>::link_node_back(list_node<T> *p) {
  link_node(cend(), p);
}

template<class T, class Alloc>
void list<T, Alloc>::link_node_front(list_node<T> *p) {
  link_node(cbegin(), p);
}

template<class T, class Alloc>
void list<T, Alloc>::link_node(list::const_iterator position, list_node<T> *p) {
  auto pos = position.base();
  p->next_ = pos;
  p->prev_ = pos->prev_;
  pos->prev_->next_ = p;
  pos->prev_ = p;
  ++head_.size_;
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::begin() noexcept {
  return iterator(static_cast<list_node<T> *>(head_.next_));
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator list<T, Alloc>::begin() const noexcept {
  return const_iterator(static_cast<list_node<T> *>(head_.next_));
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::end() noexcept {
  return iterator(static_cast<list_node<T> *>(head_.prev_->next_));
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator list<T, Alloc>::end() const noexcept {
  return const_iterator(static_cast<list_node<T> *>(head_.prev_->next_));
}

template<class T, class Alloc>
template<class Iter>
list<T, Alloc>::list(Iter first, Iter last, const allocator_type &a,
                     typename std::enable_if
                         <!std::numeric_limits<Iter>::is_specialized>::type *)
    : alloc_(a) {
  for (; first != last; ++first) {
    push_back(*first);
  }
}

template<class T, class Alloc>
list<T, Alloc>::list(const list &list, const allocator_type &a) : alloc_(a) {
  auto first = list.begin();
  auto last = list.end();
  for (; first != last; ++first) {
    push_back(*first);
  }
}

template<class T, class Alloc>
list<T, Alloc>::list(list &&x) noexcept(is_nothrow_move_constructible<
    allocator_type>::value) {
  head_.next_ = x.head_.next_;
  head_.prev_ = x.head_.prev_;
  head_.size_ = x.head_.size_;
  x.head_.size_ = 0;
  x.head_.prev_ = x.head_.next_ = &x.head_;
}

template<class T, class Alloc>
list<T, Alloc>::list(list &&x, const allocator_type &a) : alloc_(a) {
  head_.next_ = x.head_.next_;
  head_.prev_ = x.head_.prev_;
  head_.size_ = x.head_.size_;
  x.head_.size_ = 0;
  x.head_.prev_ = x.head_.next_ = &x.head_;
}

template<class T, class Alloc>
list<T, Alloc>::list(initializer_list<value_type> l, const allocator_type &a)
    : alloc_(a) {
  auto first = l.begin();
  auto last = l.end();
  for (; first != last; ++first) {
    push_back(*first);
  }
}

//TODO
template<class T, class Alloc>
list<T, Alloc>::~list() {
  clear();
}

template<class T, class Alloc>
list<T, Alloc> &list<T, Alloc>::operator=(const list &x) {
  if (this == &x) {
    return *this;
  }
  clear();
  auto first = x.begin();
  auto last = x.end();
  for (; first != last; ++first) {
    push_back(*first);
  }
  return *this;
}

template<class T, class Alloc>
void list<T, Alloc>::clear() noexcept {
//  auto first = begin();
//  auto last = end();
//  for (; first != last; ++first) {
//    alloc_.destroy(&*first);
//  }
//  first = ++begin();
//  ++last;
//  for (; first != last; ++first) {
//    auto iter = first;
//    --iter;
//    head_.put_node(iter.base());
//  }
//  head_.next_ = head_.prev_ = &head_;
  erase_at_end(begin());
  head_.size_ = 0;
}

//TODO maybe add swap in head class
template<class T, class Alloc>
list<T, Alloc> &list<T, Alloc>::operator=(list &&x) noexcept(
allocator_type::propagate_on_container_move_assignment::value &&
    is_nothrow_move_assignable<allocator_type>::value) {
  clear();
  head_.size_ = x.head_.size_;
  head_.next_ = x.head_.next_;
  head_.prev_ = x.head_.prev_;
  x.head_.prev_ = x.head_.next_ = &x.head_;
  x.head_.size_ = 0;
  return *this;
}

template<class T, class Alloc>
list<T, Alloc> &list<T, Alloc>::operator=(initializer_list<value_type> l) {
  clear();
  auto first = l.begin();
  auto last = l.end();
  for (; first != last; ++first) {
    push_back(*first);
  }
  return *this;
}

template<class T, class Alloc>
template<class Iter>
void list<T, Alloc>::assign(Iter first, Iter last,
                            typename std::enable_if
                                <!std::numeric_limits<Iter>::is_specialized>::type *) {
  list<T, Alloc> l(std::move(*this));
  for (; first != last; ++first) {
    push_back(*first);
  }
}

template<class T, class Alloc>
void list<T, Alloc>::assign(list::size_type n, const value_type &t) {
  list<T, Alloc> l(std::move(*this));
  for (size_type i = 0; i < n; ++i) {
    push_back(t);
  }
}

template<class T, class Alloc>
void list<T, Alloc>::assign(initializer_list<value_type> l) {
  *this = l;
}

template<class T, class Alloc>
typename list<T, Alloc>::allocator_type list<T, Alloc>
::get_allocator() const noexcept {
  return alloc_;
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
  return static_cast<list_node<T> *>(head_.next_)->data_;
}

//TODO maybe const T
template<class T, class Alloc>
typename list<T, Alloc>::const_reference list<T, Alloc>::front() const {
  return static_cast<list_node<T> *>(head_.next_)->data_;
}

template<class T, class Alloc>
typename list<T, Alloc>::reference list<T, Alloc>::back() {
  return static_cast<list_node<T> *>(head_.prev_)->data_;
}

template<class T, class Alloc>
typename list<T, Alloc>::const_reference list<T, Alloc>::back() const {
  return static_cast<list_node<T> *>(head_.prev_)->data_;
}

template<class T, class Alloc>
bool list<T, Alloc>::empty() const noexcept {
  return head_.size_ == 0;
}

template<class T, class Alloc>
typename list<T, Alloc>::size_type list<T, Alloc>::size() const noexcept {
  return head_.size_;
}

template<class T, class Alloc>
typename list<T, Alloc>::size_type list<T, Alloc>::max_size() const noexcept {
  return std::min<size_type>(alloc_.max_size(),
                             std::numeric_limits<difference_type>::max());
}

template<class T, class Alloc>
template<class... Args>
void list<T, Alloc>::emplace_front(Args &&... args) {
  auto node = create_node_with_args(std::forward<T>(args) ...);
  link_node_front(node);
}

template<class T, class Alloc>
void list<T, Alloc>::pop_front() {
  delete_node(static_cast<list_node<T> *>(head_.next_));
}

template<class T, class Alloc>
template<class... Args>
void list<T, Alloc>::emplace_back(Args &&... args) {
  auto node = create_node_with_args(std::forward<T>(args) ...);
  link_node_back(node);
}
template<class T, class Alloc>
void list<T, Alloc>::pop_back() {
  delete_node(static_cast<list_node<T> *>(head_.prev_));
}

template<class T, class Alloc>
void list<T, Alloc>::delete_node(list_node<T> *p) {
  auto front_node = p;
  unlink_node(front_node);
  alloc_.destroy(&front_node->data_);
  head_.put_node(front_node);
}

template<class T, class Alloc>
void list<T, Alloc>::push_front(const value_type &x) {
  list_node<T> *p = create_node_with_lvalue(x);
  link_node_front(p);
}

template<class T, class Alloc>
void list<T, Alloc>::push_front(value_type &&x) {
  list_node<T> *p = create_node_with_rvalue(std::forward<T>(x));
  link_node_front(p);
}

template<class T, class Alloc>
template<class... Args>
typename list<T, Alloc>::iterator list<T, Alloc>::emplace(
    list::const_iterator position,
    Args &&... args) {
  auto node = create_node_with_args(std::forward<T>(args) ...);
  link_node(position, node);
  return iterator(node);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(
    list::const_iterator position,
    const value_type &x) {
  insert(position, 1, x);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(
    list::const_iterator position,
    value_type &&x) {
  auto node = create_node_with_args(std::move_if_noexcept(x));
  link_node(position, node);
  return iterator(node);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(
    list::const_iterator position,
    list::size_type n,
    const value_type &x) {
  for (; n > 0; --n) {
    auto node = create_node_with_lvalue(x);
    link_node(position, node);
  }
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
  for (; first != last; ++first) {
    auto node = create_node_with_lvalue(*first);
    link_node(position, node);
  }
  return iterator(--position);
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(
    list::const_iterator position,
    initializer_list<value_type> il) {
  return insert(position, il.begin(), il.end());
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
  for (; first != last; ++first) {
    delete_node(first.base());
  }
  return iterator(last);
}

template<class T, class Alloc>
void list<T, Alloc>::default_append(list::size_type n) {
  for (; n > 0; --n) {
    list_node<T> *p = create_node_without_value();
    link_node_back(p);
  }
}

template<class T, class Alloc>
void list<T, Alloc>::value_append(list::size_type n, const value_type &x) {
  for (; n > 0; --n) {
    list_node<T> *p = create_node_with_lvalue(x);
    link_node_back(p);
  }
}

//[pos;end())
template<class T, class Alloc>
void list<T, Alloc>::erase_at_end(const_iterator position) {
  auto first = position;
  auto last = end();
  for (; first != last; ++first) {
    alloc_.destroy(&*first);
  }
  first = ++iterator(position);
  --position;
  ++last;
  for (; first != last; ++first) {
    auto iter = first;
    --iter;
    head_.put_node(iter.base());
  }
  position.base()->next_ = &head_;
  head_.prev_ = position.base();
}

template<class T, class Alloc>
void list<T, Alloc>::resize(list::size_type sz) {
  if (sz > head_.size_) {
    default_append(sz - head_.size_);
  } else if (sz < head_.size_) {
    const_iterator iter = begin();
    std::advance(iter, sz);
    erase_at_end(iter);
  }
}

template<class T, class Alloc>
void list<T, Alloc>::resize(list::size_type sz, const value_type &c) {
  if (sz > head_.size_) {
    value_append(sz - head_.size_, c);
  } else if (sz < head_.size_) {
    const_iterator iter = begin();
    std::advance(iter, sz);
    erase_at_end(iter);
  }
}

template<class T, class Alloc>
void list<T, Alloc>::swap(list &l)
noexcept(allocator_traits<allocator_type>::is_always_equal::value) {
  (void) l;
  //swap head node
}

template<class T, class Alloc>
void list<T, Alloc>::splice(list::const_iterator position, list &x) {
  if (x.head_.size_ == 0) {
    return;
  }
  auto pos = position.base();
  x.head_.prev_->next_ = pos;
  x.head_.next_->prev_ = pos->prev_;
  pos->prev_->next_ = x.head_.next_;
  pos->prev_ = x.head_.prev_;
  head_.size_ += x.head_.size_;
  x.head_.prev_ = x.head_.next_ = &x.head_;
  x.head_.size_ = 0;
}

template<class T, class Alloc>
void list<T, Alloc>::splice(list::const_iterator position, list &&x) {
  splice(position, x);
}

template<class T, class Alloc>
typename list<T, Alloc>::size_type list<T, Alloc>::get_size(
    list::const_iterator first,
    list::const_iterator last) {
  return (std::distance(first, last));
}

template<class T, class Alloc>
void list<T, Alloc>::splice(list::const_iterator position,
                            list &x,
                            list::const_iterator first,
                            list::const_iterator last) {
  size_type size = get_size(first, last);
  if (size == 0) {
    return;
  }
  x.head_.size_ -= size;
  head_.size_ += size;
  auto n_pos = position.base();
  auto n_first = first.base();
  auto n_last = last.base();
  n_first->prev_->next_ = n_last;
  n_last = static_cast<list_node<value_type> *>(n_last->prev_);
  n_last->next_->prev_ = n_first->prev_;
  n_pos->prev_->next_ = n_first;
  n_first->prev_ = n_pos->prev_;
  n_pos->prev_ = n_last;
  n_last->next_ = n_pos;
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
void list<T, Alloc>::splice(list::const_iterator position,
                            list &&x,
                            list::const_iterator first,
                            list::const_iterator last) {
  splice(position, x, first, last);
}

template<class T, class Alloc>
void list<T, Alloc>::remove(const value_type &value) {
  for (auto it = begin(); it != end();) {
    if (*it == value) {
      auto p = it.base();
      ++it;
      delete_node(static_cast<list_node<T> *>(p));
    } else {
      ++it;
    }
  }
}

template<class T, class Alloc>
template<class Pred>
void list<T, Alloc>::remove_if(Pred pred) {
  for (auto it = begin(); it != end();) {
    if (pred(*it)) {
      auto p = it.base();
      ++it;
      delete_node(static_cast<list_node<T> *>(p));
    } else {
      ++it;
    }
  }
}

template<class T, class Alloc>
void list<T, Alloc>::unique() {
  unique(equal_to<value_type>());
}

template<class T, class Alloc>
template<class BinaryPredicate>
void list<T, Alloc>::unique(BinaryPredicate binary_pred) {
  for (auto it = begin(); it != end();) {
    auto iter = it++;
    if (binary_pred(*iter, *it)) {
      auto p = it.base();
      ++it;
      delete_node(static_cast<list_node<T> *>(p));
    } else {
      ++it;
    }
  }
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
template<class Compare>
void list<T, Alloc>::sort(Compare comp) {
  if (head_.size_ <= 1) {
    return;
  }
  head_.prev_->next_ = NULL;
  head_.next_->prev_ = NULL;
  head_.next_ = mergeSort(static_cast<list_node<T> *>(head_.next_), comp);
  head_.next_->prev_ = &head_;
  auto end = begin();
  std::advance(end, head_.size_ - 1);
  head_.prev_ = end.base();
  head_.prev_->next_ = &head_;
}


template<class T, class Alloc>
inline list_node<T> *list<T, Alloc>::split(list_node<T> *head) {
  list_node<T> *fast = head;
  list_node<T> *slow = head;
  while (fast->next_ && fast->next_->next_)
  {
    fast = static_cast<list_node<T> *>(fast->next_->next_);
    slow = static_cast<list_node<T> *>(slow->next_);
  }
  auto *temp = static_cast<list_node<T> *>(slow->next_);
  slow->next_ = NULL;
  return temp;
}

template<class T, class Alloc>
template<class Compare>
inline list_node<T> *list<T, Alloc>::merge(list_node<T> *first, list_node<T> *second, Compare comp) {
  if (!first)
    return second;

  if (!second)
    return first;

  if (comp(first->data_, second->data_))
  {
    first->next_ = merge(static_cast<list_node<T> *>(first->next_), second, comp);
    first->next_->prev_ = first;
    first->prev_ = &head_;
    return first;
  }
  else
  {
    second->next_ = merge(first, static_cast<list_node<T> *>(second->next_), comp);
    second->next_->prev_ = second;
    second->prev_ = &head_;
    return second;
  }
}

template<class T, class Alloc>
template<class Compare>
inline list_node<T> *list<T, Alloc>::mergeSort(list_node<T> *head, Compare comp) {
  if (!head || !head->next_)
    return head;
  list_node<T> *second = split(head);
  head = mergeSort(head, comp);
  second = mergeSort(second, comp);
  return merge(head,second, comp);
}

template<class T, class Alloc>
void list<T, Alloc>::sort() {
  sort(std::less<value_type>());
}

template<class T, class Alloc>
void list<T, Alloc>::reverse() noexcept {
  if (head_.size_ <= 1) {
    return;
  }
  iterator e = end();
  for (iterator i = begin(); i != e;)
  {
    std::swap(i.base()->prev_, i.base()->next_);
    std::advance(i, -1);
  }
  std::swap(head_.next_, head_.prev_);
}


}