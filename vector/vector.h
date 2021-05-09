//
// Created by Aaron Berry on 5/2/21.
//
#pragma once

#include <utility>

#include "tools/memory.h"
#include "tools/reverse_iterator.h"
#include "tools/utility.h"
#include "random_access_iterator.h"

using namespace std;
namespace ft {

  template<class T, class Alloc = ft::Allocator<T> >
  class vector {
/*
**                                Public Types
*/
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
    typedef ft::reverse_iterator<iterator>                     reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;

/*
**                           Public Member Functions
*/
    inline vector();
    inline explicit vector(const allocator_type &a);
    inline explicit vector(size_type n);
    inline explicit vector(size_type n, const value_type &value,
                  const allocator_type &a=allocator_type());
    inline vector(const vector &x);
    inline vector(vector &&x) noexcept;
    inline vector(initializer_list<value_type> l,
                  const allocator_type &a=allocator_type());
    template<typename InputIterator>
    inline vector(InputIterator first, InputIterator last,
                  const allocator_type &a=allocator_type(), typename enable_if
        <!std::numeric_limits<InputIterator>::is_specialized>::type* = 0);
    inline ~vector() ;
    inline void assign(size_type n, const value_type &val);
    template<typename InputIterator >
    inline void assign(InputIterator first, InputIterator last, typename enable_if
        < !std::numeric_limits<InputIterator>::is_specialized >::type* = 0);
    inline void assign(initializer_list< value_type > l);
    inline reference at(size_type n);
    inline const_reference at(size_type n) const;
    inline reference back();
    inline const_reference back() const;
    inline iterator begin();
    inline const_iterator begin() const;
    inline size_type capacity() const;
    inline const_iterator cbegin() const;
    inline const_iterator cend() const;
    inline void clear();
    inline const_reverse_iterator crbegin() const;
    inline const_reverse_iterator crend() const;
    inline T* data();
    inline const T* data() const;
    template<typename... Args>
    inline iterator emplace(const_iterator position, Args &&...args);
    template<typename... Args> inline void emplace_back(Args &&...args);
    inline bool empty() const;
    inline iterator end();
    inline const_iterator end() const;
    inline iterator erase(iterator position);
    inline iterator erase(iterator first, iterator last);
    inline reference front();
    inline const_reference front() const;
    inline iterator insert(const_iterator position, const value_type &x);
    inline iterator insert(const_iterator position, value_type &&x);
    inline iterator insert(const_iterator position, initializer_list< value_type > l);
    inline iterator insert(const_iterator position, size_type n, const value_type &x);
    template<typename InputIterator >
    inline iterator insert(const_iterator position, InputIterator first,
                           InputIterator last, typename enable_if
        < !std::numeric_limits<InputIterator>::is_specialized >::type* = 0);
    inline size_type max_size() const noexcept;
    inline vector& operator=(const vector &x);
    inline vector& operator=(vector &&x) noexcept;
    inline vector& operator=(initializer_list< value_type > l);
    inline reference operator[](size_type n);
    inline const_reference operator[](size_type n) const;
    inline void pop_back();
    inline void push_back(const value_type &x);
    inline void push_back(value_type &&x);
    inline reverse_iterator rbegin();
    inline const_reverse_iterator rbegin() const;
    inline reverse_iterator rend();
    inline const_reverse_iterator rend() const;
    inline void reserve(size_type n);
    inline void resize(size_type new_size);
    inline void resize(size_type new_size, const value_type &x);
    inline void shrink_to_fit();
    inline size_type size() const;
    inline void swap(vector &x);
    inline allocator_type get_allocator() const;
/*
**                         Protected Member Functions
*/
   protected:
    inline size_type get_new_capacity(size_type n);
    inline bool compareForIdentity(const value_type& a, const value_type& b);
    inline void move_range(iterator position, size_type n);
    inline void default_initialize(size_type n);
    inline void destroy_storage(pointer data, size_type n, size_type cap);
    inline void clear_storage(pointer data, size_type n);
    inline void fill_initialize(size_type n, const value_type& value);
    inline pointer fill_initialize_for_copy(size_type n, size_type cap,
                                            difference_type offset,
                                            const value_type& value);
    template<typename InputIterator>
    inline pointer copy_range(InputIterator first, InputIterator last,
                              typename vector<T, Alloc>::size_type cap,
                              const Alloc& alloc);
    template<typename InputIterator>
    inline void range_initialize(InputIterator first, InputIterator last,
                                 const Alloc& alloc);
    template<class InputIt, class ForwardIt>
    inline ForwardIt uninitialized_copy(InputIt first, InputIt last,
                                        ForwardIt d_first, const Alloc& alloc);
    template<typename InputIterator>
    inline void erase_at_end(InputIterator first, InputIterator last);
    inline void default_append(size_type append_size);
    inline void append_end(pointer data, size_type append_size, size_type size, const value_type& value);
    template<class InputIt, class ForwardIt>
    inline ForwardIt uninitialized_move(InputIt first, InputIt last,
                                        ForwardIt d_first, size_type capacity);
    template<class InputIt, class ForwardIt>
    inline ForwardIt uninitialized_move(InputIt first, InputIt last,
                                        ForwardIt d_first);
    inline void move_old_data(pointer data, size_type offset,
                              iterator position, size_type size);

   private:
    pointer          data_;
    size_type        size_;
    size_type        capacity_;
    ft::Allocator<T> alloc_;

  };

  template<class T, class Alloc>
  vector<T, Alloc>::vector(): data_(nullptr), size_(0),
                              capacity_(0), alloc_() {}

  template<class T, class Alloc>
  vector<T, Alloc>::vector(const allocator_type &a)
                          : data_(nullptr), size_(0),
                            capacity_(0), alloc_(a) {}

  template<class T, class Alloc>
  vector<T, Alloc>::vector(vector::size_type n) {
    fill_initialize(n, value_type());
  }

// TODO перенести функцию ниже
// Called by the vector(n) constructor.
  template<class T, class Alloc>
  void vector<T, Alloc>::default_initialize(vector::size_type n) {
    if (!n) return;
    if (n > max_size()) throw ft::Length_error("vector");
    try {
      data_ = alloc_.allocate(n);
    } catch (ft::Length_error &ex) {
      throw ft::Length_error("vector");
    } catch (...) {
      throw;
    }
    size_ = capacity_ = n;
  }

// Called by the vector(n,value) constructor.
  template<class T, class Alloc>
  void vector<T, Alloc>::fill_initialize(vector::size_type n,
                                         const value_type &value) {
    default_initialize(n);
    for (size_type i = 0; i < n; ++i) {
      try {
        alloc_.template construct(data_ + i, value);
      } catch (...) {
        destroy_storage(data_, i, capacity_);
        size_ = capacity_ = 0;
        throw;
      }
    }
  }

// Called alloc destroy for each element
  template<class T, class Alloc>
  void vector<T, Alloc>::clear_storage(pointer data, vector::size_type n) {
    for (size_type i = 0; i < n; ++i) {
      alloc_.destroy(data + i);
    }
  }

// Called clear_storage and alloc deallocate for storage
  template<class T, class Alloc>
  void vector<T, Alloc>::destroy_storage(pointer data, size_type n,
                                         size_type cap) {
    clear_storage(data, n);
    if(data) alloc_.deallocate(data, cap);
  }

  template<class T, class Alloc>
  vector<T, Alloc>::vector(vector::size_type n,
                           const value_type &value,
                           const allocator_type &a)
                           : data_(nullptr), size_(0),
                             capacity_(0), alloc_(a) {
    fill_initialize(n, value);
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::clear() {
    clear_storage(data_, size_);
    size_ = 0;
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const noexcept {
    return alloc_.max_size();
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
    return ft::vector<T, Alloc>::iterator(data_);
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const {
    return ft::vector<T, Alloc>::const_iterator(data_);
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::iterator vector<T, Alloc>::end() {
    return ft::vector<T, Alloc>::iterator(data_ + size_);
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const {
    return ft::vector<T, Alloc>::const_iterator(data_ + size_);
  }

  template<class T, class Alloc>
  vector<T, Alloc>::vector(const vector &x)
                          : data_(nullptr), alloc_(x.alloc_),
                            size_(x.size_), capacity_(x.capacity_) {
    if (!x.capacity_) return;
    default_initialize(x.capacity_);
    try {
      uninitialized_copy(x.begin(), x.end(), this->begin(), x.alloc_);
    } catch (...) {
      alloc_.deallocate(data_, x.capacity_);
      throw;
    }
  }

  template<class T, class Alloc>
  vector<T, Alloc>::vector(vector &&x) noexcept
                          : data_(nullptr), size_(0),
                            capacity_(0) {
    std::swap(data_, x.data_);
    std::swap(capacity_, x.capacity_);
    std::swap(size_, x.size_);
    std::swap(alloc_, x.alloc_);
  }

  template<class T, class Alloc>
  vector<T, Alloc>::vector(initializer_list<value_type> l,
                           const allocator_type &a)
                          : data_(nullptr), size_(0),
                            capacity_(0), alloc_(a) {
    range_initialize(l.begin(), l.end(), alloc_);
  }

  template<class T, class Alloc>
  template<typename InputIterator>
  void vector<T, Alloc>::range_initialize(InputIterator first,
                                          InputIterator last,
                                          const Alloc& alloc) {
    const difference_type n = std::distance(first, last);
    default_initialize(n);
    try {
      uninitialized_copy(first, last, this->begin(), alloc);
    } catch (...) {
      alloc_.deallocate(data_, n);
      throw;
    }
    size_ = n;
    capacity_ = n;
  }

  template<class T, class Alloc>
  template<typename InputIterator>
  vector<T, Alloc>::vector(InputIterator first,
                           InputIterator last,
                           const allocator_type &a,
                           typename enable_if
      <!std::numeric_limits<InputIterator>::is_specialized>::type*) {
    alloc_ = a;
    range_initialize(first, last, alloc_);
  }

  template<class T, class Alloc>
  vector<T, Alloc>::~vector() {
    destroy_storage(data_, size_, capacity_);
    data_ = nullptr;
    size_ = capacity_ = 0;
  }

  template<class T, class Alloc>
  vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &x) {
    if (this == &x) {
      return *this;
    }
    if (capacity_ < x.capacity_) {
      pointer new_data = copy_range(x.begin(), x.end(), x.capacity_, x.alloc_);
      destroy_storage(data_, size_, capacity_);
      data_ = new_data;
      capacity_ = x.capacity_;
    } else {
      this->clear();
      uninitialized_copy(x.begin(), x.end(), this->begin(), x.alloc_);
    }
    size_ = x.size_;
    alloc_ = x.alloc_;
    return *this;
  }



  template<class T, class Alloc>
  template<class InputIt, class ForwardIt>
  ForwardIt vector<T, Alloc>::uninitialized_copy(InputIt first,
                                                 InputIt last,
                                                 ForwardIt d_first,
                                                 const Alloc& alloc) {
    ForwardIt current = d_first;
    try {
      for (; first != last; ++first, ++current) {
        alloc.template construct(current.base(), *first);
      }
      return current;
    } catch (...) {
      for (; d_first != current; ++d_first) {
        alloc_.destroy(d_first.base());
      }
      throw;
    }
  }

  template<class T, class Alloc>
  vector<T, Alloc> &vector<T, Alloc>::operator=(vector &&x) noexcept {
    pointer old_data = data_;
    size_ = x.size_;
    capacity_ = x.capacity_;
    alloc_ = x.alloc_;
    data_ = x.data_;
    x.capacity_ = x.size_ = 0;
    x.data_ = old_data;
    return *this;
  }

template<class T, class Alloc>
  vector<T, Alloc> &vector<T, Alloc>::operator=(initializer_list<value_type> l) {
    this->assign(l.begin(), l.end());
    return *this;
  }

  template<class T, class Alloc>
  template<typename InputIterator>
  typename vector<T, Alloc>::pointer vector<T, Alloc>::copy_range(
                                       InputIterator first,
                                       InputIterator last,
                                       vector::size_type cap,
                                       const Alloc& alloc) {
    if (!cap) return nullptr;
    pointer new_data;
    try {
      new_data = alloc_.allocate(cap);
    } catch (ft::Length_error &ex) {
      throw ft::Length_error("vector");
    } catch (...) {
      throw;
    }
    try {
      uninitialized_copy(first, last, iterator(new_data), alloc);
    } catch (...) {
      alloc_.deallocate(new_data, cap);
      throw;
    }
    return new_data;
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::assign(vector::size_type n, const value_type &val) {
    if (n > max_size()) throw ft::Length_error("vector");
    if (capacity_ < n) {
      pointer old_data = data_;
      size_type old_size = size_;
      size_type old_capacity = capacity_;
      try {
        fill_initialize(n, val);
      } catch (...) {
        data_ = old_data;
        throw;
      }
      destroy_storage(old_data, old_size, old_capacity);
      capacity_ = n;
    } else {
      this->clear();
      for (size_type i = 0; i < n; ++i) {
        try {
          if (compareForIdentity(*(data_ + i), val)) {
            continue;
          }
          alloc_.template construct(data_ + i, val);
        } catch (...) {
          this->clear();
          throw;
        }
      }
    }
    size_ = n;
  }

  template<class T, class Alloc>
  template<typename InputIterator>
  void vector<T, Alloc>::assign(InputIterator first, InputIterator last,
  typename enable_if< !std::numeric_limits<InputIterator>::is_specialized >::type*) {
    const difference_type n = std::distance(first, last);
    if (n < 0) {
      this->~vector();
      throw ft::Length_error("vector");
    }
    if (capacity_ < n) {
      pointer new_data = copy_range(first, last, n, alloc_);
      destroy_storage(data_, size_, capacity_);
      data_ = new_data;
      capacity_ = n;
    } else {//TODO
      ft::vector<T> copy_range(first, last);
      first = copy_range.begin();
      last = copy_range.end();
      this->clear();
      uninitialized_copy(first, last, this->begin(), alloc_);
    }
    size_ = n;
  }

  template<class T, class Alloc>
  bool vector<T, Alloc>::compareForIdentity(const value_type &a,
                                            const value_type &b) {
    return &a==&b;
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::assign(initializer_list<value_type> l) {
    this->assign(l.begin(), l.end());
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::reference vector<T, Alloc>::at(vector::size_type n) {
    if (n >= size_) {
      throw ft::OutOfRange("vector");
    }
    return data_[n];
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(
                                                    vector::size_type n) const {
    if (n >= size_) {
      throw ft::OutOfRange("vector");
    }
    return data_[n];
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::reference vector<T, Alloc>::front() {
    return *data_;
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const {
    return *data_;
  }
  template<class T, class Alloc>

  typename vector<T, Alloc>::reference vector<T, Alloc>::back() {
    return data_[size_ - 1];
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const {
    return data_[size_ - 1];
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const {
    return capacity_;
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cbegin() const {
    return vector<T, Alloc>::begin();
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cend() const {
    return vector<T, Alloc>::end();
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::crbegin() const {
    return rbegin();
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::crend() const {
    return rend();
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin()  {
    return reverse_iterator(end());
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const {
    return const_reverse_iterator(end());
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend() {
    return reverse_iterator(begin());
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const {
    return const_reverse_iterator(begin());
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const {
    return size_;
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::reserve(vector::size_type n) {
    if (n <= capacity_) return;
    pointer new_data = alloc_.allocate(n);
    uninitialized_move(begin(), end(), iterator(new_data), n);
    if (data_ != 0) {
      destroy_storage(data_, size_, capacity_);
    }
    capacity_ = n;
    data_ = new_data;
  }

  template<class T, class Alloc>
  template<typename InputIterator>
  void vector<T, Alloc>::erase_at_end(InputIterator first, InputIterator last) {
    size_ -= (last - first);
    for (; first != last; ++first) {
      alloc_.destroy(first.base());
    }
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::resize(vector::size_type new_size) {
    if (new_size > size_)
      default_append(new_size - size_);
    else if (new_size < size_)
      erase_at_end(begin() + new_size, end());
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::append_end(pointer data, size_type append_size,
                                    size_type size,
                                    const value_type& value) {
    for (size_type i = 0; i < append_size; ++i) {
      try {
        alloc_.template construct(data + size + i, value);
      } catch (...) {
        clear_storage(data + size, i);
        throw;
      }
    }
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::default_append(vector::size_type append_size) {
    if (capacity_ >= size_ + append_size) {
      append_end(data_, append_size, size_, value_type());
      size_ += append_size;
      return;
    }
    size_type new_capacity = get_new_capacity(size_ + append_size);
    pointer new_data;
    try {
      new_data = alloc_.allocate(new_capacity);
    } catch (ft::Length_error &ex) {
      throw ft::Length_error("vector");
    } catch (...) {
      throw;
    }
    try {
      append_end(new_data, append_size, size_, value_type());
    } catch (...) {
      destroy_storage(new_data, 0, new_capacity);
      throw;
    }
    uninitialized_move(begin(), end(), iterator(new_data), new_capacity);
    destroy_storage(data_, size_, capacity_);
    data_ = new_data;
    size_ += append_size;
    capacity_ = size_;
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::size_type vector<T, Alloc>::get_new_capacity(
                                                    vector::size_type n) {
    if (capacity_ * 2 >= capacity_ + n) {
      size_type new_cap = capacity_ * 2;
      if (new_cap > max_size()) {
        new_cap = max_size();
      }
      return (new_cap);
    }
    return (capacity_ + n);
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::resize(vector::size_type new_size, const value_type &x) {
    if (new_size > size_)
      insert(end(), new_size - size_, x);
    else if (new_size < size_)
      erase_at_end(begin() + new_size, end());
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::shrink_to_fit() {
    if (size_ == capacity_) return;
    pointer new_data = alloc_.allocate(size_);
    uninitialized_move(begin(), end(), iterator(new_data), size_);
    if (data_ != 0) {
      destroy_storage(data_, size_, capacity_);
    }
    capacity_ = size_;
    data_ = new_data;
  }

  template<class T, class Alloc>
  template<class InputIt, class ForwardIt>
  ForwardIt vector<T, Alloc>::uninitialized_move(InputIt first,
                                                 InputIt last,
                                                 ForwardIt d_first,
                                                 size_type capacity) {
    iterator current = d_first;
    iterator first_copy = first;
    try {
      for (; first != last; ++first, ++current) {
        alloc_.template construct(current.base(), std::move_if_noexcept(*first));
      }
      return current;
    } catch (...) {
      std::move_backward(d_first, current, first_copy + (current - d_first));
      destroy_storage(d_first.base(), current - d_first, capacity);
      throw;
    }
  }

  template<class T, class Alloc>
  template<class InputIt, class ForwardIt>
  ForwardIt vector<T, Alloc>::uninitialized_move(InputIt first,
                                                 InputIt last,
                                                 ForwardIt d_first) {
    iterator current = d_first;
    iterator first_copy = first;
    try {
      for (; first != last; ++first, ++current) {
        alloc_.template construct(current.base(), std::move_if_noexcept(*first));
      }
      return current;
    } catch (...) {
      std::move_backward(d_first, current, first_copy + (current - d_first));
      clear_storage(d_first.base(), current - d_first);
      throw;
    }
  }

  template<class T, class Alloc>
  bool vector<T, Alloc>::empty() const {
    return (!size_);
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](
                                                          vector::size_type n) {
    return data_[n];
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](
                                                    vector::size_type n) const {
    return data_[n];
  }

  template<class T, class Alloc>
  T *vector<T, Alloc>::data() {
    return data_;
  }

  template<class T, class Alloc>
  const T *vector<T, Alloc>::data() const {
    return data_;
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator() const {
    return alloc_;
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::push_back(const value_type &x) {
    if (capacity_ != size_) {
      alloc_.template construct(data_ + size_, x);
      ++size_;
    } else {
      insert(end(), x);
    }
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::push_back(value_type &&x) {
    emplace_back(std::move(x));
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::swap(vector &x) {
    std::swap(data_, x.data_);
    std::swap(alloc_, x.alloc_);
    std::swap(capacity_, x.capacity_);
    std::swap(size_, x.size_);
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::pop_back() {
    --size_;
    alloc_.template destroy(data_ + size_);
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(vector::const_iterator position,
                                vector::size_type n,
                                const value_type &x) {
    if (size_ + n > max_size()) throw ft::Length_error("vector");
    pointer p = data_ + (position - begin());
    if (!n) return (iterator(p));
    if (capacity_ >= size_ + n) {
      if (position == end()) {
        for (size_type i = 0; i < n; ++i) {
          try {
            alloc_.template construct(data_ + size_ + i, x);
          } catch (...) {
            clear_storage(data_ + size_, i);
            throw;
          }
        }
      } else {
        const_reference val_copy(x);
        move_range(iterator(p), n);
        size_type i;
        for (i = 0; i < n; ++i, ++p) {
          *p = val_copy;
        }
        p-=i;
      }
    } else {
      difference_type offset = position - begin();
      size_type new_cap = get_new_capacity(n);
      pointer new_data = fill_initialize_for_copy(n, new_cap, offset, x);
      try {
        move_old_data(new_data, offset, iterator(p), n);
      } catch (...) {
        destroy_storage(new_data, 0, new_cap);
        throw;
      }
      destroy_storage(data_, size_, capacity_);
      p = new_data + offset;
      capacity_ = new_cap;
      data_ = new_data;
    }
    size_ += n;
    return (iterator(p));
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::move_range(vector::iterator position,
                                    vector::size_type n) {
    for (size_type i = 0; i < n; ++i) {
      try {
        alloc_.template construct(data_ + size_ + i,
                                  std::move_if_noexcept(data_[size_ + i - 1]));
      } catch (...){
        std::swap(*(data_ + size_ - 1), *(data_ + size_ + i));
        clear_storage(data_ + size_, i);
        throw;
      }
    }
    std::move_backward(position, end() - 1, end() + n - 1);
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::pointer vector<T, Alloc>::fill_initialize_for_copy(
                                                  vector::size_type n,
                                                  vector::size_type cap,
                                                  vector::difference_type offset,
                                                  const value_type &value) {
    pointer data = alloc_.allocate(cap);
    for (size_type i = 0; i < n; ++i) {
      try {
        alloc_.template construct(data + offset + i, value);
      } catch (...) {
        destroy_storage(data, i, cap);
        throw;
      }
    }
    return data;
  }

  template<class T, class Alloc>
  void vector<T, Alloc>::move_old_data(pointer data,
                                       vector::size_type offset,
                                       vector::iterator position,
                                       vector::size_type size) {
    size_type i = 0;
    try {
      uninitialized_move(begin(), position, iterator(data + i));
      size += offset;
      i = size;
      offset = 0;
      uninitialized_move(position, end(), iterator(data + i));
    } catch (...) {
      clear_storage(data + offset, size);
      throw;
    }
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
                                            vector::const_iterator position,
                                            const value_type &x) {
    return insert(position, 1, x);
  }

  template<class T, class Alloc>
  template<typename InputIterator>
  typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
                                vector::const_iterator position,
                                InputIterator first,
                                InputIterator last,
                                typename enable_if
                                    < !std::numeric_limits<InputIterator>::is_specialized >::type*) {
    pointer p = data_ + (position - begin());
    difference_type n = std::distance(first, last);
    if (first > last || !n) return iterator(p);
    if (size_ + n > max_size()) throw ft::Length_error("vector");
    if (capacity_ >= size_ + n) {
      if (position == end()) {
        for (size_type i = 0; i < n; ++i, ++first) {
          try {
            alloc_.template construct(data_ + size_ + i, *first);
          } catch (...) {
            clear_storage(data_ + size_, i);
            throw;
          }
        }
      } else {//TODO
        vector<T> vector(first, last);
        first = vector.begin();
        move_range(iterator(p), n);
        size_type i;
        for (i = 0; i < n; ++i, ++p, ++first) {
          *p = *first;
        }
        p-=i;
      }
    } else {
      difference_type offset = position - begin();
      size_type new_cap = get_new_capacity(n);
      pointer new_data = alloc_.allocate(new_cap);
      for (size_type i = 0; i < n; ++i, ++first) {
        try {
          alloc_.template construct(new_data + offset + i, *first);
        } catch (...) {
          destroy_storage(new_data + offset, i, new_cap);
          throw;
        }
      }
      try {
        move_old_data(new_data, offset, iterator(p), n);
      } catch (...) {
        destroy_storage(new_data, 0, new_cap);
        throw;
      }
      destroy_storage(data_, size_, capacity_);
      p = new_data + offset;
      capacity_ = new_cap;
      data_ = new_data;
    }
    size_ += n;
    return (iterator(p));
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
                                            vector::const_iterator position,
                                            initializer_list<value_type> l) {
    return insert(position, l.begin(), l.end());
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
                                           vector::iterator first,
                                           vector::iterator last) {
    pointer p = data_ + (first - begin());
    if (first != last) {
      std::move(last, end(), begin() + (first.base() - data_));
      difference_type n = last - first;
      for (; n; --n) {
        alloc_.template destroy(data_ + size_ - 1);
        --size_;
      }
    }
    return iterator(p);
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
                                                    vector::iterator position) {
    return erase(position, position + 1);
  }

  template<class T, class Alloc>
  template<typename... Args>
  typename vector<T, Alloc>::iterator vector<T, Alloc>::emplace(
                                             vector::const_iterator position,
                                             Args &&... args) {
    if (size_ + 1 > max_size()) throw ft::Length_error("vector");
    pointer p = data_ + (position - begin());
    if (capacity_ >= size_ + 1) {
      if (position == end()) {
        try {
          alloc_.template construct(data_ + size_, std::forward<T>(args) ...);
        } catch (...) {
          clear_storage(data_ + size_, 1);
          throw;
        }
      } else {
        const_reference val_copy(args ...);
        move_range(iterator(p), 1);
        *p = val_copy;
        --p;
      }
    } else {
      difference_type offset = position - begin();
      size_type new_cap = get_new_capacity(1);
      pointer new_data = alloc_.allocate(new_cap);
      try {
        alloc_.template construct(new_data + offset, std::forward<T>(args) ...);
      } catch (...) {
        destroy_storage(new_data, 1, new_cap);
        throw;
      }
      try {
        move_old_data(new_data, offset, iterator(p), 1);
      } catch (...) {
        destroy_storage(new_data, 0, new_cap);
        throw;
      }
      destroy_storage(data_, size_, capacity_);
      p = new_data + offset;
      capacity_ = new_cap;
      data_ = new_data;
    }
    ++size_;
    return (iterator(p));
  }

  template<class T, class Alloc>
  template<typename... Args>
  void vector<T, Alloc>::emplace_back(Args &&... args) {
    emplace(end(), std::forward<T>(args) ...);
  }

  template<class T, class Alloc>
  typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
                                            vector::const_iterator position,
                                            value_type &&x) {
    return emplace(position, std::forward<T>(x));
  }

}
