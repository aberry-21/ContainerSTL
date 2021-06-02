//
// Created by Aaron Berry on 5/14/21.
//

#pragma once
#include "tools/utility.h"
#include "list_base.h"

namespace ft {
template<typename T, class Node>
class bidirectional_iterator {
 public:
  typedef T iterator_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef typename remove_const<T>::type value_type;
  typedef ptrdiff_t difference_type;
  typedef typename qualifier_type<T>::pointer pointer;
  typedef typename qualifier_type<T>::reference reference;

  inline bidirectional_iterator() = default;
  inline ~bidirectional_iterator() = default;
  inline explicit bidirectional_iterator(Node *node);
  inline bidirectional_iterator(bidirectional_iterator<value_type,
                                                       Node> const &other);
  inline bidirectional_iterator(bidirectional_iterator<const value_type,
                                                       Node> const &other);
  inline reference operator*();
  inline pointer operator->();
  inline bidirectional_iterator operator++();
  inline bidirectional_iterator operator--();
  inline bidirectional_iterator operator++(int);
  inline bidirectional_iterator operator--(int);
  inline bool operator==(const bidirectional_iterator &x);
  inline bool operator!=(const bidirectional_iterator &x);
  inline Node *base() const;
 private:
  Node *node_;
};

template<typename T, class Node>
bidirectional_iterator<T, Node>::bidirectional_iterator(Node *node)
    : node_(node) {}

template<typename T, class Node>
bidirectional_iterator<T, Node>::
bidirectional_iterator(const bidirectional_iterator<value_type, Node> &other)
    : node_(other.base()) {}

template<typename T, class Node>
bidirectional_iterator<T, Node>::
bidirectional_iterator(const bidirectional_iterator<const value_type,
                                                    Node> &other)
    : node_(other.base()) {}

template<typename T, class Node>
typename bidirectional_iterator<T, Node>::
reference bidirectional_iterator<T, Node>::operator*() {
  return node_->value_;
}

template<typename T, class Node>
typename bidirectional_iterator<T, Node>::
pointer bidirectional_iterator<T, Node>::operator->() {
  return std::addressof(node_->value_);
}

template<typename T, class Node>
bidirectional_iterator<T, Node> bidirectional_iterator<T, Node>::operator++() {
  node_ = node_->next_;
  return *this;
}

template<typename T, class Node>
bidirectional_iterator<T, Node> bidirectional_iterator<T, Node>::operator--() {
  node_ = node_->prev_;
  return *this;
}

template<typename T, class Node>
bidirectional_iterator<T, Node> bidirectional_iterator<T,
                                                       Node>::operator++(int) {
  auto tmp = *this;
  node_ = node_->next_;
  return tmp;
}

template<typename T, class Node>
bidirectional_iterator<T, Node> bidirectional_iterator<T,
                                                       Node>::operator--(int) {
  auto tmp = *this;
  node_ = node_->prev_;
  return tmp;
}

template<typename T, class Node>
Node *bidirectional_iterator<T, Node>::base() const {
  return node_;
}

template<typename T, class Node>
bool bidirectional_iterator<T, Node>
::operator==(const bidirectional_iterator &x) {
  return node_ == x.node_;
}

template<typename T, class Node>
bool bidirectional_iterator<T, Node>
::operator!=(const bidirectional_iterator &x) {
  return node_ != x.node_;
}

}