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
class vector {
/*
**                                Public Types
*/
 public:
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef ft::random_access_iterator<T> iterator;
  typedef ft::random_access_iterator<const T> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

/*
**                           Public Member Functions
*/

// ----------------------------Constructors vector------------------------------
  // default
  inline explicit vector(const allocator_type &alloc = allocator_type());
  //fill
  inline explicit vector(size_type n);
  inline explicit vector(size_type n, const value_type &value,
                         const allocator_type &a = allocator_type());
  // range
  template<typename InputIterator>
  inline vector(InputIterator first, InputIterator last,
                const allocator_type &a = allocator_type(),
                typename std::enable_if
      <!std::numeric_limits<InputIterator>::is_specialized>::type * = 0);
  // copy
  inline vector(const vector &x);
  inline vector(const vector &x,
                const allocator_type& alloc);
  // move
  inline vector(vector &&x) noexcept;
  inline vector(const vector &&x,
                const allocator_type& alloc) noexcept;
  // initializer list
  inline vector(std::initializer_list<value_type > l,
                const allocator_type &a = allocator_type());

// ----------------------------Destructor vector--------------------------------
  inline ~vector() noexcept;

// ----------------------------Assignment operator------------------------------
  // copy
  inline vector &operator=(const vector &x);
  // move
  inline vector &operator=(vector &&x) noexcept;
  // initializer list
  inline vector &operator=(std::initializer_list<value_type> l);

// --------------------------------Iterators------------------------------------
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

// --------------------------------Size-----------------------------------------
  inline size_type size() const noexcept;

// ------------------------------Max_Size---------------------------------------
  inline size_type max_size() const noexcept;

// -------------------------------Resize----------------------------------------
  inline void resize(size_type new_size);
  inline void resize(size_type new_size, const value_type &x);

// ------------------------------Capacity---------------------------------------
  inline size_type capacity() const noexcept;

// -------------------------------Empty-----------------------------------------
  inline bool empty() const noexcept;

// ------------------------------Reserve----------------------------------------
  void reserve(size_type n);

// ---------------------------Shrink_to_fit-------------------------------------
  inline void shrink_to_fit();

// ---------------------------Element access------------------------------------
  inline reference operator[](size_type n);
  inline const_reference operator[](size_type n) const;
  inline value_type *data() noexcept;
  inline const value_type *data() const noexcept;
  inline reference at(size_type n);
  inline const_reference at(size_type n) const;
  inline reference front();
  inline const_reference front() const;
  inline reference back();
  inline const_reference back() const;

// -------------------------------Assign----------------------------------------
  // range
  template<typename InputIterator>
  inline void assign(InputIterator first, InputIterator last,
                     typename std::enable_if
             <!std::numeric_limits<InputIterator>::is_specialized>::type * = 0);
  // fill
  inline void assign(size_type n, const value_type &val);
  // initializer list
  inline void assign(std::initializer_list<value_type> l);

// -----------------------------Push_back---------------------------------------
  inline void push_back(const value_type &x);
  inline void push_back(value_type &&x);

// ------------------------------Pop_back---------------------------------------
  inline void pop_back();

// -------------------------------Insert----------------------------------------
  // single element
  inline iterator insert(const_iterator position, const value_type &x);
  // fill
  iterator insert(const_iterator position, size_type n,
                  const value_type &x);
  // range
  template<typename InputIterator>
  inline iterator insert(const_iterator position, InputIterator first,
                         InputIterator last, typename std::enable_if
      <!std::numeric_limits<InputIterator>::is_specialized>::type * = 0);
  // move
  inline iterator insert(const_iterator position, value_type &&x);
  // initializer list
  inline iterator insert(const_iterator position,
                         std::initializer_list<value_type> l);

// -------------------------------Erase-----------------------------------------
  inline iterator erase(iterator position);
  inline iterator erase(iterator first, iterator last);

// -------------------------------Swap------------------------------------------
  inline void swap(vector &x);

// -------------------------------Clear-----------------------------------------
  inline void clear() noexcept;

// -----------------------------Emplace-----------------------------------------
  template<typename... Args>
  iterator emplace(const_iterator position, Args &&...args);
  template<typename... Args>
  inline void emplace_back(Args &&...args);
// --------------------------Get_allocator--------------------------------------
  inline allocator_type get_allocator() const noexcept;

/*
**                         Protected Member Functions
*/
// protected:
//    inline size_type get_new_capacity(size_type n);
//    inline bool compareForIdentity(const value_type& a, const value_type& b);
//    inline void move_range(iterator position, size_type n);
//    inline void default_initialize(size_type n);
//    inline void destroy_storage(pointer data, size_type n, size_type cap);
//    inline void clear_storage(pointer data, size_type n);
//    inline void fill_initialize(struct field &storage, const value_type& value,
//                                size_type offset, bool def);
//    inline pointer fill_initialize_for_copy(size_type n, size_type cap,
//                                            difference_type offset,
//                                            const value_type& value);
//    template<typename InputIterator>
//    inline pointer copy_range(InputIterator first, InputIterator last,
//                              typename vector<T, Alloc>::size_type cap,
//                              const Alloc& alloc);
//    template<typename InputIterator>
//    inline void range_initialize(InputIterator first, InputIterator last,
//                                 const Alloc& alloc);
//    template<class InputIt, class ForwardIt>
//    inline ForwardIt uninitialized_copy(InputIt first, InputIt last,
//                                        ForwardIt d_first, const Alloc& alloc);
//    template<typename InputIterator>
//    inline void erase_at_end(InputIterator first, InputIterator last);
//    inline void default_append(size_type append_size);
//    inline void append_end(pointer data, size_type append_size, size_type size, const value_type& value);
//    template<class InputIt, class ForwardIt>
//    inline ForwardIt uninitialized_move(InputIt first, InputIt last,
//                                        ForwardIt d_first, size_type capacity);
//    template<class InputIt, class ForwardIt>
//    inline ForwardIt uninitialized_move(InputIt first, InputIt last,
//                                        ForwardIt d_first);
//    inline void move_old_data(pointer data, size_type offset,
//                              iterator position, size_type size);

 private:
  struct field {
    pointer data_;
    size_type size_;
    size_type capacity_;
    allocator_type alloc_;
    field(pointer data,
          size_type size,
          size_type capacity,
          allocator_type alloc)
        : data_(data), size_(size), capacity_(capacity), alloc_(alloc) {}
    field(pointer data,
          size_type size,
          size_type capacity)
        : data_(data), size_(size), capacity_(capacity), alloc_() {}
    inline void set_zero() {
      data_ = nullptr;
      size_ = capacity_ = 0;
    }
  } attributes_;
  inline void initialize_storage(field &storage);
  inline void fill_initialize(field &storage, const value_type &value,
                              size_type offset);
  inline void default_initialize(field &storage);
  inline void clear_storage(field &storage);
  inline void destroy_storage(field &storage);
  template<class InputIt, class ForwardIt>
  inline ForwardIt uninitialized_copy(InputIt first, InputIt last,
                                      ForwardIt d_first, const Alloc& alloc);
  template<typename InputIterator>
  inline void range_initialize(field &storage, InputIterator first,
                               InputIterator last, size_type offset);

};

template<class T, class Alloc>
vector<T, Alloc>::vector(const allocator_type &alloc)
                        : attributes_(nullptr, 0, 0, alloc) {}

template<class T, class Alloc>
void vector<T, Alloc>::clear_storage(vector::field &storage) {
  for (size_type i = 0; i < storage.size_; ++i) {
    storage.alloc_.destroy(storage.data_ + i);
  }
}

template<class T, class Alloc>
void vector<T, Alloc>::destroy_storage(vector::field &storage) {
  clear_storage(storage);
  if(storage.data_) {
    storage.alloc_.deallocate(storage.data_, storage.capacity_);
  }
  storage.set_zero();
}

template<class T, class Alloc>
void vector<T, Alloc>::initialize_storage(vector::field &storage) {
  if (storage.capacity_ > max_size()){
    throw ft::length_error("vector");
  }
  try {
    if (storage.capacity_ > 0) {
      storage.data_ = storage.alloc_.allocate(storage.capacity_);
    }
  } catch (...) {
    throw;
  }
}

template<class T, class Alloc>
void vector<T, Alloc>::fill_initialize(vector::field &storage,
                                       const value_type &value,
                                       vector::size_type offset) {
  initialize_storage(storage);
  for (size_type i = 0; i < storage.size_; ++i) {
    try {
        storage.alloc_.construct(storage.data_ + offset + i, value);
    } catch (...) {
      destroy_storage(storage);
      throw;
    }
  }
}

template<class T, class Alloc>
void vector<T, Alloc>::default_initialize(vector::field &storage) {
  initialize_storage(storage);
  for (size_type i = 0; i < storage.size_; ++i) {
    try {
        storage.alloc_.construct(storage.data_ + i);
    } catch (...) {
      storage.size_ = i;
      destroy_storage(storage);
      throw;
    }
  }
}

template<class T, class Alloc>
vector<T, Alloc>::vector(vector::size_type n)
                        : attributes_(nullptr, n, n) {
  default_initialize(attributes_);
}

template<class T, class Alloc>
vector<T, Alloc>::vector(vector::size_type n,
                         const value_type &value,
                         const allocator_type &a)
                         : attributes_(nullptr, n, n, a) {
  fill_initialize(attributes_, value, 0);
}

template<class T, class Alloc>
vector<T, Alloc>::~vector() noexcept {
  destroy_storage(attributes_);
}

template<class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const noexcept {
  return attributes_.size_;
}

template<class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const noexcept {
  return std::min<size_type>(attributes_.alloc_.max_size(),
                             std::numeric_limits<difference_type>::max());
}

template<class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](
    vector::size_type n) {
  return attributes_.data_[n];
}

template<class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](
    vector::size_type n) const {
  return attributes_.data_[n];
}

template<class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const noexcept {
  return attributes_.capacity_;
}

template<class T, class Alloc>
template<typename InputIterator>
vector<T, Alloc>::vector(InputIterator first,
                         InputIterator last,
                         const allocator_type &a,
                         typename std::enable_if
<!std::numeric_limits<InputIterator>::is_specialized>::type *)
                        : attributes_(nullptr, 0, 0, a) {
  attributes_.size_ = attributes_.capacity_ = std::distance(first, last);
  range_initialize(attributes_, first, last, 0);
}

template<class T, class Alloc>
template<typename InputIterator>
void vector<T, Alloc>::range_initialize(vector::field &storage,
                                        InputIterator first,
                                        InputIterator last,
                                        vector::size_type offset) {
  initialize_storage(storage);
  try {
    uninitialized_copy(first, last, iterator(storage.data_ + offset),
                       storage.alloc_);
  } catch (...) {
    destroy_storage(storage);
    throw;
  }
}

template<class T, class Alloc>
template<class InputIt, class ForwardIt>
ForwardIt vector<T, Alloc>::uninitialized_copy(InputIt first, InputIt last,
                                               ForwardIt d_first,
                                               const allocator_type &alloc) {
  ForwardIt current = d_first;
  try {
    for (; first != last; ++first, ++current) {
      alloc.construct(current.base(), *first);
    }
    return current;
  } catch (...) {
    for (; d_first != current; ++d_first) {
      alloc.destroy(d_first.base());
    }
    throw;
  }
}

template<class T, class Alloc>
vector<T, Alloc>::vector(std::initializer_list<value_type> l,
                         const allocator_type &a)
                        : attributes_(nullptr, 0, 0, a) {
  attributes_.size_ = attributes_.capacity_ = std::distance(l.begin(), l.end());
  range_initialize(attributes_, l.begin(), l.end(), 0);
}

template<class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() noexcept {
  return ft::vector<T, Alloc>::iterator(attributes_.data_);
}

template<class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const noexcept {
  return ft::vector<T, Alloc>::const_iterator(attributes_.data_);
}

template<class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end() noexcept {
  return ft::vector<T, Alloc>::iterator(attributes_.data_ + attributes_.size_);
}

template<class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const noexcept {
  return ft::vector<T, Alloc>::const_iterator(attributes_.data_ + attributes_.size_);
}

template<class T, class Alloc>
vector<T, Alloc>::vector(const vector &x)
                         : attributes_(nullptr, x.attributes_.size_,
                                       x.attributes_.capacity_,
                                       x.attributes_.alloc_) {
  range_initialize(attributes_, x.begin(), x.end(), 0);
}

template<class T, class Alloc>
vector<T, Alloc>::vector(const vector &x, const allocator_type& alloc)
    : attributes_(nullptr, x.attributes_.size_,
                  x.attributes_.capacity_,
                  alloc) {
  range_initialize(attributes_, x.begin(), x.end(), 0);
}
template<class T, class Alloc>
vector<T, Alloc>::vector(vector &&x) noexcept
    : attributes_(nullptr, 0, 0) {
  std::swap(attributes_.data_, x.attributes_.data_);
  std::swap(attributes_.capacity_, x.attributes_.capacity_);
  std::swap(attributes_.size_, x.attributes_.size_);
  std::swap(attributes_.alloc_, x.attributes_.alloc_);
}

template<class T, class Alloc>
vector<T, Alloc>::vector(const vector &&x,
                         const allocator_type &alloc) noexcept
    : attributes_(nullptr, 0, 0, alloc) {
  std::swap(attributes_.data_, x.attributes_.data_);
  std::swap(attributes_.capacity_, x.attributes_.capacity_);
  std::swap(attributes_.size_, x.attributes_.size_);
  std::swap(attributes_.alloc_, x.attributes_.alloc_);
}

}
