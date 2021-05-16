//
// Created by Aaron Berry on 5/14/21.
//

#pragma once
#include "tools/utility.h"
#include "list_base.h"

namespace ft {
template<class T>
    //TODO refactor!
class bidirectional_iterator {
 public:
  typedef T iterator_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef typename remove_const<T>::type value_type;
  typedef ptrdiff_t difference_type;
  typedef typename qualifier_type<T>::pointer pointer;
  typedef typename qualifier_type<T>::reference reference;

  bidirectional_iterator() = default;
  ~bidirectional_iterator() = default;
  explicit bidirectional_iterator(list_node<value_type> *node);
  inline bidirectional_iterator(bidirectional_iterator<value_type> const &other);
  inline bidirectional_iterator(bidirectional_iterator<const value_type> const &other);
  bidirectional_iterator& operator=(const bidirectional_iterator& x);
  reference operator*();
  pointer operator->();
  bidirectional_iterator operator++();
  bidirectional_iterator operator--();
  bidirectional_iterator operator++(int);
  bidirectional_iterator operator--(int);
  bool operator==(const bidirectional_iterator& x);
  bool operator!=(const bidirectional_iterator& x);
  list_node<value_type> *base() const;
 private:
  list_node<value_type> *node_;
};

template<class T>
bidirectional_iterator<T>::bidirectional_iterator(list_node<value_type> *node)
                          : node_(node) {}

template<class T>
bidirectional_iterator<T> &bidirectional_iterator<T>::
    operator=(const bidirectional_iterator &x) {
  if (this == &x) {
    return *this;
  }
  node_ = x.node_;
  return *this;
}

template<class T>
typename bidirectional_iterator<T>::reference bidirectional_iterator<T>
    ::operator*() {
  return node_->data_;
}

template<class T>
typename bidirectional_iterator<T>::pointer bidirectional_iterator<T>
    ::operator->() {
  return std::addressof(node_->data_);
}

template<class T>
bidirectional_iterator<T> bidirectional_iterator<T>
    ::operator++() {
  node_ = static_cast<list_node<value_type> *>(node_->next_);
  return *this;
}

template<class T>
bidirectional_iterator<T> bidirectional_iterator<T>
    ::operator--() {
  node_ = static_cast<list_node<value_type> *>(node_->prev_);
  return *this;
}

template<class T>
bidirectional_iterator<T> bidirectional_iterator<T>::operator++(int) {
  bidirectional_iterator<T> tmp = *this;
  node_ = static_cast<list_node<value_type> *>(node_->next_);
  return tmp;
}

template<class T>
bidirectional_iterator<T> bidirectional_iterator<T>::operator--(int) {
  bidirectional_iterator<T> tmp = *this;
  node_ = static_cast<list_node<value_type> *>(node_->prev_);
  return tmp;
}

template<class T>
bool bidirectional_iterator<T>::operator==(const bidirectional_iterator &x) {
  return node_ == x.node_;
}

template<class T>
bool bidirectional_iterator<T>::operator!=(const bidirectional_iterator &x) {
  return node_ != x.node_;
}

template<class T>
list_node<typename bidirectional_iterator<T>::value_type>
    *bidirectional_iterator<T>::base() const {
  return node_;
}

//TODO
template<class T>
bidirectional_iterator<T>::bidirectional_iterator(const bidirectional_iterator<
    value_type> &other)  : node_(other.base()) {}

template<class T>
bidirectional_iterator<T>::bidirectional_iterator(
    bidirectional_iterator<const value_type> const &other)
    : node_(other.base()) {}

}
