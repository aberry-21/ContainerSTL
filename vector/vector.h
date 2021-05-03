//
// Created by Aaron Berry on 5/2/21.
//
#pragma once

#include <utility>

#include "tools/memory.h"

namespace ft {

  template <class T>
  inline
  typename remove_reference<T>::type&& move(T&& t) noexcept {
    typedef typename remove_reference<T>::type Up;
    return static_cast<Up&&>(t);
  }

  template <class T>
  inline
  void swap(T& a, T& b) noexcept{
    T c(ft::move(a));
    a=ft::move(b);
    b=ft::move(c);
  }


  template<class T, class Alloc = ft::Allocator<T> >
  class Vector {

   public:
    typedef T                                                        value_type;
    typedef Alloc                                                allocator_type;
    typedef size_t                                                    size_type;
    typedef ptrdiff_t                                           difference_type;
    typedef value_type&                                               reference;
    typedef const value_type&                                   const_reference;
    typedef typename allocator_type::pointer                            pointer;
    typedef typename allocator_type::const_pointer                const_pointer;
//    typedef ft::VectorRandomAccessIterator<T, T*, T&>                  iterator;
//    typedef ft::VectorRandomAccessIterator<T, const T*, const T&>
//                                                                 const_iterator;
//    typedef ft::ReverseIterator<iterator>                      reverse_iterator;
//    typedef ft::ReverseIterator<const_iterator>          const_reverse_iterator;

    explicit Vector(const allocator_type& alloc = allocator_type())
                          : array_(0), size_(0), capacity_(0), alloc_(alloc) {}

    explicit Vector(size_type n) : size_(n), capacity_(n) {
      if (!n) {
        return;
      }
      try {
        array_ = alloc_.allocate(n);
      } catch (ft::Length_error &ex) {
        throw ft::Length_error("vector");
      }
    }

    Vector(size_type n,
           const value_type& val,
           const allocator_type& alloc = allocator_type())
           : size_(n), capacity_(n), alloc_(alloc) {
      if (!n) {
        return;
      }
      try {
        array_ = alloc_.allocate(n);
      } catch (ft::Length_error &ex) {
        throw ft::Length_error("vector");
      }
      for (int i = 0; i < n; ++i) {
        alloc_.template construct(array_ + i, val);
      }
    }

    //template <class InputIterator>
    //Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

    Vector(const Vector& other)
      : size_(other.size_), capacity_(other.capacity_), alloc_(other.alloc_) {
      if (!capacity_) {
        return;
      }
      try {
        array_ = alloc_.allocate(capacity_);
      } catch (ft::Length_error &ex) {
        throw ft::Length_error("vector");
      }
      for (size_type i = 0; i < size_; ++i) {
        alloc_.template construct(array_ + i, other[i]);
      }
    }

    Vector(const Vector& other, const allocator_type& alloc)
    : size_(other.size_), capacity_(other.capacity_), alloc_(alloc_) {
      if (!capacity_) {
        return;
      }
      try {
        array_ = alloc_.allocate(capacity_);
      } catch (ft::Length_error &ex) {
        throw ft::Length_error("vector");
      }
      for (size_type i = 0; i < size_; ++i) {
        alloc_.template construct(array_ + i, other[i]);
      }
    }

    //TODO (aberry):alloc ?
    Vector(Vector&& other) noexcept
    : array_(other.array_),
      size_(other.size_),
      capacity_(other.capacity_),
      alloc_(other.alloc_) {
      other.array_ = nullptr;
      other.size_ = other.capacity_ = 0;
    }

    //TODO (aberry):alloc ?
    Vector(Vector&& other, const allocator_type& alloc) noexcept
    : array_(other.array_),
      size_(other.size_),
      capacity_(other.capacity_),
      alloc_(alloc) {
      other.array_ = nullptr;
      other.size_ = other.capacity_ = 0;
    }

    Vector(std::initializer_list<value_type> il,
           const allocator_type& alloc = allocator_type())
    : size_(il.size()),
      capacity_(il.size()),
      alloc_(alloc) {
      if (il.size() > max_size()) {
        throw ft::Length_error("vector");
      }
      if (!capacity_) {
        return;
      }
      try {
        array_ = alloc_.allocate(capacity_);
      } catch (ft::Length_error &ex) {
        throw ft::Length_error("vector");
      }
      for (size_type i = 0; i < size_; ++i) {
        alloc_.template construct(array_ + i, il[i]);
      }
    }

    ~Vector() {
      if (array_){
        for (size_type i = 0; i < size_; ++i) {
          alloc_.template destroy(array_ + i);
        }
        alloc_.deallocate(array_, capacity_);
      }
    }

    //TODO (aberry):for ? replace move iter
    Vector& operator= (const Vector& other) {
      if (this == &other) {
        return *this;
      }
      pointer new_array;
      if (capacity_ < other.capacity_) {
        try {
          new_array = alloc_.allocate(other.capacity_);
        } catch (ft::Length_error &ex) {
          throw ft::Length_error("vector");
        }
        this->~Vector();
        capacity_ = other.capacity_;
      } else {
        for (size_type i = 0; i < size_; ++i) {
          alloc_.template destroy(array_ + i);
        }
        new_array = array_;
      }
      for (size_type i = 0; i < other.size_; ++i) {
        alloc_.template construct(new_array + i, other.array_[i]);
      }
      size_ = other.size_;
      alloc_ = other.alloc_;
      array_ = new_array;
      return *this;
    }

    Vector& operator= (Vector&& other) noexcept {
      if (this == &other) {
        return *this;
      }
      pointer old_array = array_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      alloc_ = other.alloc_;
      array_ = other.array_;
      other.capacity_ = other.size_ = 0;
      other.array_ = old_array;
      return *this;
    }

    Vector& operator= (initializer_list<value_type> il) {
      pointer new_array;
      size_type size_il = il.size();
      if (size_il > max_size()) {
        throw ft::Length_error("vector");
      }
      if (capacity_ < size_il) {
        try {
          new_array = alloc_.allocate(size_il);
        } catch (ft::Length_error &ex) {
          throw ft::Length_error("vector");
        }
        this->~Vector();
        capacity_ = size_il;
      } else {
        for (size_type i = 0; i < size_; ++i) {
          alloc_.template destroy(array_ + i);
        }
        new_array = array_;
      }
      for (size_type i = 0; i < size_il; ++i) {
        alloc_.template construct(new_array + i, il[i]);
      }
      size_ = size_il;
      array_ = new_array;
      return *this;
    }

    size_type size() const noexcept {
      return size_;
    }

    size_type max_size() const noexcept {
      return alloc_.max_size();
    }

    inline
    static size_type GetNewCapacity(const size_type old_cap,
                                    const size_type n,
                                    const size_type max_size) {
      if (old_cap * 2 >= n ) {
        size_type new_cap = old_cap * 2;
        if (new_cap > max_size) {
          new_cap = max_size;
        }
        return (new_cap);
      }
      return (n);
    }

    void resize(size_type n, const value_type& val) {
      if (n > max_size()) {
        throw ft::Length_error("vector");
      }
      if (n <= size_) {
        for (size_type i = n; i < size_; ++i) {
          alloc_.template destroy(array_ + i);
        }
        size_ = n;
        return;
      }
      if (n <= capacity_) {
        for (size_type i = size_; i < n; ++i) {
          alloc_.construct(array_ + i, val);
        }
        size_ = n;
        return;
      }
      size_type new_cap = GetNewCapacity(capacity_, n, max_size());
      pointer new_array = alloc_.allocate(new_cap);
      memcpy(new_array, array_, sizeof(T) * size_);
      for (size_type i = size_; i < n; ++i) {
        alloc_.construct(new_array + i, val);
      }
      if (array_ != 0) {
        alloc_.deallocate(array_, capacity_);
      }
      array_ = new_array;
      size_ = n;
      capacity_ = new_cap;
    }

    void resize(size_type n) {
      resize(n, value_type());
    }

    size_type capacity() const noexcept {
      return capacity_;
    }

    bool empty() const noexcept {
      return (!size_);
    }

    void reserve (size_type n) {
      if (n <= capacity_) {
        return;
      }
      pointer new_array = alloc_.allocate(n);
      memcpy(new_array, array_, sizeof(T) * size_);
      if (array_ != 0) {
        alloc_.deallocate(array_, capacity_);
      }
      capacity_ = n;
      array_ = new_array;
    }

    void shrink_to_fit() {
      pointer new_array = alloc_.allocate(size_);
      memcpy(new_array, array_, sizeof(T) * size_);
      if (array_ != 0) {
        alloc_.deallocate(array_, capacity_);
      }
      capacity_ = size_;
      array_ = new_array;
    }

    reference operator[] (size_type n) {
      return array_[n];
    }

    const_reference operator[] (size_type n) const {
      return array_[n];
    }

    reference at(size_type n) {
      if (n >= size_) {
        throw ft::OutOfRange("vector subscript out of range");
      }
      return array_[n];
    }

    const_reference at(size_type n) const {
      if (n >= size_) {
        throw ft::OutOfRange("vector subscript out of range");
      }
      return array_[n];
    }

    reference front() {
      return *array_;
    }

    const_reference front() const {
      return *array_;
    }

    reference back() {
      return array_[size_ - 1];
    }

    const_reference back() const {
      return array_[size_ - 1];
    }
    value_type* data() noexcept {
      return array_;
    }

    const value_type* data() const noexcept {
      return array_;
    }

    allocator_type get_allocator() const noexcept {
      return alloc_;
    }

   private:
    pointer          array_;
    size_type        size_;
    size_type        capacity_;
    ft::Allocator<T> alloc_;

  };
}