// -*- C++ -*-
//===------------------------------ vector --------------------------------===//
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

template < class T, class Alloc = ft::Allocator<T> >
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
  inline explicit list(const allocator_type& a);
  inline explicit list(size_type n, const allocator_type& a = allocator_type());
  inline list(size_type n, const value_type& value, const allocator_type& a = allocator_type());
  template <class Iter>
  list(Iter first, Iter last, const allocator_type& a = allocator_type());
  list(const list& list, const allocator_type& a = allocator_type());
  list(list&& x)
  noexcept(is_nothrow_move_constructible<allocator_type>::value);
  list(list&& x, const allocator_type& a);
  list(initializer_list<value_type> l, const allocator_type& a);
  ~list();

//  list& operator=(const list& x);
//  list& operator=(list&& x)
//  noexcept(
//  allocator_type::propagate_on_container_move_assignment::value &&
//      is_nothrow_move_assignable<allocator_type>::value);
//  list& operator=(initializer_list<value_type>);
//  template <class Iter>
//  void assign(Iter first, Iter last);
//  void assign(size_type n, const value_type& t);
//  void assign(initializer_list<value_type>);
//
//  allocator_type get_allocator() const noexcept;
//
  inline iterator begin() noexcept;
  inline const_iterator begin() const noexcept;
  inline iterator end() noexcept;
  inline const_iterator end() const noexcept;
//  inline reverse_iterator rbegin() noexcept;
//  inline const_reverse_iterator rbegin() const noexcept;
//  inline reverse_iterator rend() noexcept;
//  inline const_reverse_iterator rend() const noexcept;
//  inline const_iterator cbegin() const noexcept;
//  inline const_iterator cend() const noexcept;
//  inline const_reverse_iterator crbegin() const noexcept;
//  inline const_reverse_iterator crend() const noexcept;
//
//  inline reference front();
//  inline const_reference front() const;
//  inline reference back();
//  inline const_reference back() const;
//
//  bool empty() const noexcept;
//  size_type size() const noexcept;
//  size_type max_size() const noexcept;
//
//  template <class... Args>
//  void emplace_front(Args&&... args);
//  void pop_front();
//  template <class... Args>
//  void emplace_back(Args&&... args);
//  void pop_back();
//  void push_front(const value_type& x);
//  void push_front(value_type&& x);
  inline void push_back(const value_type& x);
  inline void push_back(value_type&& x);
//  template <class... Args>
//  iterator emplace(const_iterator position, Args&&... args);
//  iterator insert(const_iterator position, const value_type& x);
//  iterator insert(const_iterator position, value_type&& x);
//  iterator insert(const_iterator position, size_type n, const value_type& x);
//  template <class Iter>
//  iterator insert(const_iterator position, Iter first, Iter last);
//  iterator insert(const_iterator position, initializer_list<value_type> il);
//
//  iterator erase(const_iterator position);
//  iterator erase(const_iterator position, const_iterator last);
//
//  void resize(size_type sz);
//  void resize(size_type sz, const value_type& c);
//
//  void swap(list&)
//  noexcept(allocator_traits<allocator_type>::is_always_equal::value);
//  void clear() noexcept;
//
//  void splice(const_iterator position, list& x);
//  void splice(const_iterator position, list&& x);
//  void splice(const_iterator position, list& x, const_iterator i);
//  void splice(const_iterator position, list&& x, const_iterator i);
//  void splice(const_iterator position, list& x, const_iterator first,
//              const_iterator last);
//  void splice(const_iterator position, list&& x, const_iterator first,
//              const_iterator last);
//
//  void remove(const value_type& value);
//  template <class Pred> void remove_if(Pred pred);
//  void unique();
//  template <class BinaryPredicate>
//  void unique(BinaryPredicate binary_pred);
//  void merge(list& x);
//  void merge(list&& x);
//  template <class Compare>
//  void merge(list& x, Compare comp);
//  template <class Compare>
//  void merge(list&& x, Compare comp);
//  void sort();
//  template <class Compare>
//  void sort(Compare comp);
//  void reverse() noexcept;

 private:
  list_base<T, Alloc> head_;
  ft::Allocator<T>    alloc_;
  void link_node(list_node<T> *p);
  list_node<T> *create_node_without_value();
  list_node<T> *create_node_with_lvalue(const value_type& x);
  template<typename... Args>
  list_node<T> *create_node_with_args(Args &&... args);
};

template<class T, class Alloc>
list<T, Alloc>::list()
  noexcept(is_nothrow_default_constructible<allocator_type>::value)
  : head_(), alloc_() {}

template<class T, class Alloc>
list<T, Alloc>::list(const allocator_type &a)
    : alloc_(a), head_() {}

template<class T, class Alloc>
list<T, Alloc>::list(list::size_type n, const allocator_type &a) : alloc_(a){
  for (size_type i = 0; i < n; ++i) {
    list_node<T> *p = create_node_without_value();
    link_node(p);
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
  link_node(p);
}

template<class T, class Alloc>
void list<T, Alloc>::push_back(value_type &&x) {
  list_node<T> *p = create_node_with_rvalue(std::forward<T>(x));
  link_node(p);
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
void list<T, Alloc>::link_node(list_node<T> *p) {
  head_.prev_->next_ = p;
  p->prev_ = head_.prev_;
  head_.prev_ = p;
  p->next_ = &head_;
  head_.size_++;
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::begin() noexcept {
  return iterator(static_cast<list_node<T> *>(head_.next_));
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator list<T, Alloc>::begin() const noexcept {
  return const_iterator(static_cast<list_node<const T> *>(head_.next_));
}

template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::end() noexcept {
  return iterator(static_cast<list_node<T> *>(head_.prev_->next_));
}

template<class T, class Alloc>
typename list<T, Alloc>::const_iterator list<T, Alloc>::end() const noexcept {
  return const_iterator(static_cast<list_node<const T> *>(head_.prev_->next_));
}

template<class T, class Alloc>
template<class Iter>
list<T, Alloc>::list(Iter first, Iter last, const allocator_type& a) : alloc_(a) {
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
  (void)x;//splice
}

template<class T, class Alloc>
list<T, Alloc>::list(list &&x, const allocator_type &a) : alloc_(a) {
  (void)x;//splice
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
  auto first = begin();
  auto last = end();
  for (; first != last; ++first) {
    alloc_.destroy(&*first);
  }
  first = ++begin();
  for (; first != last; ++first) {
    auto iter = first;
    --iter;
    head_.put_node(iter.base());
  }
}

}