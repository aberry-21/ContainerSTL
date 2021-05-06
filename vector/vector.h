//
// Created by Aaron Berry on 5/2/21.
//
#pragma once

#include <utility>

#include "tools/memory.h"
#include "tools/reverse_iterator.h"
#include "tools/utility.h"
#include "random_access_iterator.h"

namespace ft {

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
    typedef ft::random_access_iterator<T>                              iterator;
    typedef ft::random_access_iterator<const T>                  const_iterator;
    typedef ft::reverse_iterator<iterator>                      reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>          const_reverse_iterator;

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

//    template <class InputIterator>
//    Vector(InputIterator first, InputIterator last,
//           const allocator_type& alloc = allocator_type()) {
//
//    }

    Vector(const Vector& other);
    Vector(const Vector& other, const allocator_type& alloc);
    Vector& operator=(const Vector& other);

    Vector(Vector&& other) noexcept;
    Vector(Vector&& other, const allocator_type& alloc) noexcept;
    Vector& operator= (Vector&& other) noexcept;

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
      for (size_type i = 0; i < size_; ++i) {
        alloc_.template destroy(array_ + i);
      }
      alloc_.deallocate(array_, capacity_);
      size_ = 0;
      capacity_ = 0;
      array_ = nullptr;
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
    size_type GetNewCapacity(const size_type n,
                             const size_type max_size) {
      if (capacity_ * 2 >= n ) {
        size_type new_cap = capacity_ * 2;
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
      size_type new_cap = GetNewCapacity(n, max_size());
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

    void reserve(size_type n) {
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

    iterator begin() noexcept {
      return iterator(array_);
    }

    const_iterator begin() const noexcept {
      return const_iterator(array_);
    }

    iterator end() noexcept {
      return iterator(array_ + size_);
    }

    const_iterator end() const noexcept {
      return const_iterator(array_ + size_);
    }

    reverse_iterator rbegin() noexcept {
      return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
      return const_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept {
      return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept {
      return const_reverse_iterator(begin());
    }

    const_iterator cbegin() const noexcept {
      return begin();
    }

    const_iterator cend() const noexcept {
      return end();
    }

    const_reverse_iterator crbegin() const noexcept {
      return rbegin();
    }

    const_reverse_iterator crend() const noexcept {
      return rend();
    }

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last) {
      //emplace back
    }

    void ConstructObj(const pointer array,
                      const int counter,
                      const value_type& val) {
      try {
        alloc_.construct(array + counter, val);
      } catch (...) {
        for (size_type i = 0; i < counter; ++i) {
          alloc_.template destroy(array + i);
        }
        alloc_.deallocate(array, counter);
        throw std::bad_alloc();
      }
    }

    void clear() noexcept {
        for (size_type i = 0; i < size_; ++i) {
          alloc_.destroy(array_ + i);
        }
      size_ = 0;
    }

    inline
    bool compareForIdentity(const value_type& a, const value_type& b) {
      return &a==&b;
    }

    void assign(size_type n, const value_type& val) {
      if (n > max_size()) {
        throw ft::Length_error("vector");
      }
      if (n <= capacity_) {
        for (size_type i = 0; i < size_; ++i) {
          if (compareForIdentity(*(array_ + i), val)) {
            continue;
          }
          alloc_.template destroy(array_ + i);
        }
        for (size_type i = 0; i < n; ++i) {
          ConstructObj(array_, i, val);
        }
        size_ = n;
      } else {
        pointer new_array;
        size_type new_cap;
        try {
          new_cap = GetNewCapacity(n, max_size());
          new_array = alloc_.allocate(new_cap);
        } catch (...) {
          throw std::bad_alloc();
        }
        for (size_type i = 0; i < n; ++i) {
          ConstructObj(new_array, i, val);
        }
        this->~Vector();
        array_ = new_array;
        size_ = n;
        capacity_ = new_cap;
      }
    }

    void assign(initializer_list<value_type> il) {
      if (il.size() > max_size()) {
        throw ft::Length_error("vector");
      }
      if (il.size() <= capacity_) {
        initializer_list<value_type> copy_il(il);
        this->clear();
        for (size_type i = 0; i < il.size(); ++i) {
          ConstructObj(alloc_, array_, i, *(copy_il + i));
        }
        size_ = il.size();
      } else {
        pointer new_array;
        size_type new_cap;
        try {
          new_cap = GetNewCapacity(il.size(), max_size());
          new_array = alloc_.allocate(new_cap);
        } catch (...) {
          throw std::bad_alloc();
        }
        for (size_type i = 0; i < il.size(); ++i) {
          ConstructObj(alloc_, new_array, i, *(il + i));
        }
        this->~Vector();
        array_ = new_array;
        size_ = il.size();
        capacity_ = new_cap;
      }
    }

    inline
    pointer emplaceBySize(const_iterator position, size_type n) {
      if (capacity_ >= size_ + n) {
        // { *pos = 4, n = 3}
        //[1 2 3 4 5 6 0 0 0 0]
        //[1 2 3 4 5 6 4 5 6 0]
        memcpy(position.base() + n, position.base(), sizeof(value_type) * n);
//        size_ += n;??
        return array_;
      }
      pointer new_array;
      size_type new_cap;
      try {
        new_cap = GetNewCapacity(size_ + n, max_size());
        new_array = alloc_.allocate(new_cap);
      } catch (...) {
        throw std::bad_alloc();
      }
      // { *pos = 4, n = 3}
      //[1 2 3 4 5 0 0 0 0 0]
      //[1 2 3 0 0 0 4 5 0 0]
      memcpy(new_array, begin(), sizeof(value_type) * (position.base() - begin()));
      memcpy(new_array + (position.base() - begin()) + n,
             position.base(), sizeof(value_type) * (end() - position.base() ));
      return new_array;
    }

    inline
    void move_range(iterator position, size_type n);
//    inline
//    iterator insert(const_iterator position, const value_type& val);
    inline
    iterator insert(iterator position, size_type n, const value_type& val);
//    template <class InputIterator>
//    iterator insert(const_iterator position, InputIterator first, InputIterator last);
//    iterator insert(const_iterator position, value_type&& val);
//    iterator insert(const_iterator position, initializer_list<value_type> il);







    template <class... Args>
    iterator emplace(const_iterator position, Args&&... args) {
      if (capacity_ == size_) {

      }
    }

   private:
    pointer          array_;
    size_type        size_;
    size_type        capacity_;
    ft::Allocator<T> alloc_;

  };
  template<class T, class Alloc>
  Vector<T, Alloc>::Vector(const Vector &other)
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
  template<class T, class Alloc>
  Vector<T, Alloc>::Vector(const Vector &other, const allocator_type &alloc)
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

  template<class T, class Alloc>
  Vector<T, Alloc>& Vector<T, Alloc>::operator=(const Vector &other) {
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
  template<class T, class Alloc>
  Vector<T, Alloc>::Vector(Vector &&other) noexcept
      : array_(other.array_),
        size_(other.size_),
        capacity_(other.capacity_),
        alloc_(other.alloc_) {
    other.array_ = nullptr;
    other.size_ = other.capacity_ = 0;
  }
  template<class T, class Alloc>
  Vector<T, Alloc>::Vector(Vector &&other, const allocator_type &alloc) noexcept
      : array_(other.array_),
        size_(other.size_),
        capacity_(other.capacity_),
        alloc_(alloc) {
    other.array_ = nullptr;
    other.size_ = other.capacity_ = 0;
  }
  template<class T, class Alloc>
  Vector<T, Alloc> &Vector<T, Alloc>::operator=(Vector &&other) noexcept  {
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

//template<class T, class Alloc>
//typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(
//    Vector::const_iterator position,
//    const value_type &val) {
//}


  template<class T, class Alloc>
  typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(
      Vector::iterator position,
      Vector::size_type n,
      const value_type &val) {
    if (size_ + n > max_size()) {
      throw ft::Length_error("vector");
    }
    if (!n) {
      return (begin());
    }
    if (capacity_ >= size_ + n) {
      if (position < end()) {
          const_reference val_copy(val);
          move_range(position, n);
          for (size_type i = 0; i < n; ++i, ++position) {
            *position = val_copy;
          }
      } else {
        for (size_type i = 0; i < n; ++i) {
          alloc_.template construct(array_ + size_ + i, val);
          }
        size_ += n;
      }
      return (begin());
    }
    pointer new_array;
    size_type new_cap;
    try {
      new_cap = GetNewCapacity(n, max_size());
      new_array = alloc_.allocate(new_cap);
    } catch (...) {
      throw std::bad_alloc();
    }
    difference_type offset = (position - begin());
    for (size_type i = 0; i < n; ++i) {
      ConstructObj(new_array + offset, i, val);
    }
    size_type i = 0;
    for (auto iter = begin(); iter < position; ++iter, ++i) {
      alloc_.template construct(new_array + i, std::move_if_noexcept(*iter));
    }
    i += n;
    for (auto iter = position; iter < end(); ++iter, ++i) {
      alloc_.template construct(new_array + i, std::move_if_noexcept(*iter));
    }
    for (size_type i = 0; i < size_; ++i) {
      alloc_.template destroy(array_ + i);
    }
    alloc_.deallocate(array_, capacity_);
    capacity_ = new_cap;
    size_ += n;
    array_ = new_array;
    return begin();
  }

  template<class T, class Alloc>
  void Vector<T, Alloc>::move_range(iterator position, size_type n) {
    for (size_type i = 0; i < n; ++i) {
      alloc_.template construct(array_ + size_ + i,
                              std::move_if_noexcept(array_[size_ + i - 1]));
    }
    std::move_backward(position, end() - 1, end() + n - 1);
    size_+=n;
  }

}