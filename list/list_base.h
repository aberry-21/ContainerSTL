//
// Created by Aaron Berry on 5/15/21.
//

#pragma once
namespace ft {
struct list_node_base {
  list_node_base *next_;
  list_node_base *prev_;
};

template<typename T>
struct list_node : public list_node_base {
  T data_;
  list_node(T data) : data_(data) {}
};

template<typename T, class Alloc>
class list_base : public list_node_base {
  typedef typename Alloc::template rebind<list_node<T> >::other node_alloc_type;
  node_alloc_type alloc_;
 public:
  size_t size_;
  list_base() : list_node_base() , size_(0) {
    prev_ = this;
    next_ = this;
  }
  list_node<T> *get_node() {
    return alloc_.allocate(1);
  }

  void put_node(list_node<T> *p) {
    return alloc_.deallocate(p, 1);
  }
};
}