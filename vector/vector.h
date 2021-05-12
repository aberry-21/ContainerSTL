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

 private:
  struct field {
    pointer data_;
    size_type size_;
    size_type capacity_;
    allocator_type alloc_;
    inline field(pointer data,
          size_type size,
          size_type capacity,
          allocator_type alloc)
        : data_(data), size_(size), capacity_(capacity), alloc_(alloc) {}
    inline field(pointer data,
          size_type size,
          size_type capacity)
        : data_(data), size_(size), capacity_(capacity), alloc_() {}
    inline void set_zero() {
      data_ = nullptr;
      size_ = capacity_ = 0;
    }
    inline field& operator=(const field &x) = delete;
    inline field& operator=(field &&x) noexcept{
      if (this == &x) {
        return *this;
      }
      size_ = x.size_;
      capacity_ = x.capacity_;
      alloc_ = x.alloc_;
      data_ = x.data_;
      x.capacity_ = x.size_ = 0;
      x.data_ = nullptr;
      return *this;
    }
    inline void swap(field &x) {
      std::swap(size_, x.size_);
      std::swap(capacity_, x.capacity_);
      std::swap(alloc_, x.alloc_);
      std::swap(data_, x.data_);
    }
  } attributes_;

/*
**                         Private Member Functions
*/

  inline void initialize_storage(field &storage);
  inline void fill_initialize(field &storage, const value_type &value,
                              size_type size, size_type offset);
  inline void default_initialize(field &storage, size_type size, size_type offset);
  inline void clear_storage(field &storage, size_type offset);
  inline void destroy_storage(field &storage, size_type offset);
  template<class InputIt, class ForwardIt>
  inline ForwardIt uninitialized_copy(InputIt first, InputIt last,
                                      ForwardIt d_first, const Alloc& alloc);
  template<typename InputIterator>
  inline void range_initialize(field &storage, InputIterator first,
                               InputIterator last, size_type offset);
  template<typename ForwardIt>
  inline void erase_at_end(ForwardIt first, ForwardIt last);
  inline size_type get_new_capacity(size_type n);
  inline void append_end(field &storage, size_type append_size);
  inline void default_append(size_type append_size);
  template<class InputIt>
  inline void uninitialized_move(InputIt first, InputIt last,
                                      field &storage);
  inline bool compareForIdentity(const value_type& a, const value_type& b);
};

template<class T, class Alloc>
vector<T, Alloc>::vector(const allocator_type &alloc)
                        : attributes_(nullptr, 0, 0, alloc) {}

template<class T, class Alloc>
void vector<T, Alloc>::clear_storage(vector::field &storage, size_type offset) {
  for (size_type i = offset; i < storage.size_; ++i) {
    storage.alloc_.destroy(storage.data_ + i);
  }
}

template<class T, class Alloc>
void vector<T, Alloc>::destroy_storage(vector::field &storage, size_type offset) {
  clear_storage(storage, offset);
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
                                       vector::size_type size,
                                       vector::size_type offset) {
  initialize_storage(storage);
  for (size_type i = 0; i < size; ++i) {
    try {
        storage.alloc_.construct(storage.data_ + offset + i, value);
    } catch (...) {
      destroy_storage(storage, offset);
      throw;
    }
  }
}

template<class T, class Alloc>
void vector<T, Alloc>::default_initialize(vector::field &storage,
                                          vector::size_type size,
                                          vector::size_type offset) {
  initialize_storage(storage);
  for (size_type i = 0; i < size; ++i) {
    try {
        storage.alloc_.construct(storage.data_ + offset + i);
    } catch (...) {
      destroy_storage(storage, offset);
      throw;
    }
  }
}

template<class T, class Alloc>
vector<T, Alloc>::vector(vector::size_type n)
                        : attributes_(nullptr, n, n) {
  default_initialize(attributes_, attributes_.size_, 0);
}

template<class T, class Alloc>
vector<T, Alloc>::vector(vector::size_type n,
                         const value_type &value,
                         const allocator_type &a)
                         : attributes_(nullptr, n, n, a) {
  fill_initialize(attributes_, value, attributes_.size_, 0);
}

template<class T, class Alloc>
vector<T, Alloc>::~vector() noexcept {
  destroy_storage(attributes_, 0);
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
    destroy_storage(storage, 0);
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
                                       x.attributes_.size_,
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
template<class T, class Alloc>
vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &x) {
  if (this == &x) {
    return *this;
  }
  if (attributes_.capacity_ < x.attributes_.capacity_) {
    field new_storage(nullptr, x.attributes_.size_, x.attributes_.capacity_,
                      x.attributes_.alloc_);
    range_initialize(new_storage, x.begin(), x.end(), 0);
    destroy_storage(attributes_, 0);
    attributes_ = std::move(new_storage);
  } else {
    this->clear();
    uninitialized_copy(x.begin(), x.end(), this->begin(), x.attributes_.alloc_);
    attributes_.size_ = x.attributes_.size_;
    attributes_.alloc_ = x.attributes_.alloc_;
  }
  return *this;
}

template<class T, class Alloc>
void vector<T, Alloc>::clear() noexcept {
  clear_storage(attributes_, 0);
  attributes_.size_ = 0;
}

template<class T, class Alloc>
vector<T, Alloc> &vector<T, Alloc>::operator=(vector &&x) noexcept {
  this->~vector();
  attributes_ = std::move(x.attributes_);
  return *this;
}
template<class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cbegin() const noexcept{
  return vector<T, Alloc>::begin();
}

template<class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cend() const noexcept{
  return vector<T, Alloc>::end();
}

template<class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::crbegin() const noexcept{
  return rbegin();
}

template<class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::crend() const noexcept{
  return rend();
}

template<class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin() noexcept{
  return reverse_iterator(end());
}

template<class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const noexcept{
  return const_reverse_iterator(end());
}

template<class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend() noexcept{
  return reverse_iterator(begin());
}

template<class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const noexcept{
  return const_reverse_iterator(begin());
}

template<class T, class Alloc>
template<typename ForwardIt>
void vector<T, Alloc>::erase_at_end(ForwardIt first, ForwardIt last) {
  attributes_.size_ -= (last - first);
  for (; first != last; ++first) {
    attributes_.alloc_.destroy(first.base());
  }
}

template<class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::get_new_capacity(
                                                          vector::size_type n) {
  if (attributes_.capacity_ * 2 < attributes_.size_ + n) {
    return (attributes_.size_ + n);
  }
  size_type new_cap = attributes_.capacity_ * 2;
  if (new_cap > max_size()) {
    new_cap = max_size();
  }
  return (new_cap);
}

template<class T, class Alloc>
void vector<T, Alloc>::append_end(vector::field &storage,
                                  size_type append_size) {
  for (size_type i = 0; i < append_size; ++i) {
    try {
      storage.alloc_.construct(storage.data_ + storage.size_ + i);
    } catch (...) {
      for (; i > 0; --i) {
        clear_storage(storage, storage.size_);
      }
      throw;
    }
  }
}

template<class T, class Alloc>
template<class InputIt>
void vector<T, Alloc>::uninitialized_move(InputIt first, InputIt last,
                                          field &storage) {
  iterator current = iterator(storage.data_);
  iterator first_copy = first;
  try {
    for (; first != last; ++first, ++current) {
      attributes_.alloc_.construct(current.base(), std::move_if_noexcept(*first));
    }
  } catch (...) {
    std::move_backward(iterator(storage.data_), current,
                       first_copy + (current - iterator(storage.data_)));
    destroy_storage(storage, storage.size_);
    throw;
  }
}

template<class T, class Alloc>
void vector<T, Alloc>::default_append(vector::size_type append_size) {
  if (attributes_.capacity_ >= attributes_.size_ + append_size) {
    attributes_.size_ += append_size;
    try {
      append_end(attributes_, append_size);
    } catch (...) {
      attributes_.size_ -= append_size;
    }
    return;
  }
  field new_storage(nullptr, attributes_.size_,
                    get_new_capacity(append_size),
                    attributes_.alloc_);
  default_initialize(new_storage, append_size, new_storage.size_);
  uninitialized_move(begin(), end(), new_storage);
  new_storage.size_ += append_size;
  destroy_storage(attributes_, 0);
  attributes_ = std::move(new_storage);
}

template<class T, class Alloc>
void vector<T, Alloc>::resize(vector::size_type new_size) {
  if (new_size > max_size()) {
    throw ft::length_error("vector");
  }
  if (new_size > attributes_.size_) {
    default_append(new_size - attributes_.size_);
  } else if (new_size < attributes_.size_) {
    erase_at_end(begin() + new_size, end());
  }
}

template<class T, class Alloc>
bool vector<T, Alloc>::empty() const noexcept {
  return (!attributes_.size_);
}

template<class T, class Alloc>
void vector<T, Alloc>::reserve(vector::size_type n) {
  if (n <= attributes_.capacity_) return;
  field new_storage(nullptr, 0, n, attributes_.alloc_);
  new_storage.data_ = new_storage.alloc_.allocate(new_storage.capacity_);
  new_storage.size_ = attributes_.size_;
  uninitialized_move(begin(), end(), new_storage);
  destroy_storage(attributes_, 0);
  attributes_ = std::move(new_storage);
}

template<class T, class Alloc>
void vector<T, Alloc>::shrink_to_fit() {
  if (attributes_.size_ == attributes_.capacity_) {
    return;
  }
  field new_storage(nullptr, 0, attributes_.size_, attributes_.alloc_);
  new_storage.data_ = new_storage.alloc_.allocate(new_storage.capacity_);
  new_storage.size_ = attributes_.size_;
  uninitialized_move(begin(), end(), new_storage);
  destroy_storage(attributes_, 0);
  attributes_ = std::move(new_storage);
}

template<class T, class Alloc>
T *vector<T, Alloc>::data() noexcept {
  return attributes_.data_;
}

template<class T, class Alloc>
const T *vector<T, Alloc>::data() const noexcept {
  return attributes_.data_;
}

template<class T, class Alloc>
typename vector<T, Alloc>::allocator_type vector<T, Alloc>
    ::get_allocator() const noexcept {
  return attributes_.alloc_;
}
template<class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front() {
  return *attributes_.data_;
}

template<class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const {
  return *attributes_.data_;
}
template<class T, class Alloc>

typename vector<T, Alloc>::reference vector<T, Alloc>::back() {
  return attributes_.data_[attributes_.size_ - 1];
}

template<class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const {
  return attributes_.data_[attributes_.size_ - 1];
}

template<class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(vector::size_type n) {
  if (n >= attributes_.size_) {
    throw ft::out_of_range("vector");
  }
  return attributes_.data_[n];
}

template<class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(
    vector::size_type n) const {
  if (n >= attributes_.size_) {
    throw ft::out_of_range("vector");
  }
  return attributes_.data_[n];
}
template<class T, class Alloc>
template<typename InputIterator>
void vector<T, Alloc>::assign(InputIterator first,
                              InputIterator last,
                              typename std::enable_if<!std::numeric_limits<
                                  InputIterator>::is_specialized>::type *) {
  const difference_type n = std::distance(first, last);
  if (n < 0) {
    this->~vector();
    throw ft::length_error("vector");
  }
  field new_storage(nullptr, n, n);
  range_initialize(new_storage, first, last, 0);
  if (attributes_.capacity_ < n) {
    destroy_storage(attributes_, 0);
    attributes_.swap(new_storage);
  } else {
    ft::vector<T, Alloc> copy_vector(begin(), end());
    clear();
    try {
      uninitialized_move(iterator(new_storage.data_), iterator(new_storage.data_ +
      new_storage.size_), attributes_);
    } catch (...) {
      attributes_ = std::move(copy_vector.attributes_);
    }
  }
  destroy_storage(new_storage, 0);
  attributes_.size_ = n;
}

template<class T, class Alloc>
void vector<T, Alloc>::resize(vector::size_type new_size, const value_type &x) {
  if (new_size > attributes_.size_)
    insert(end(), new_size - attributes_.size_, x);
  else if (new_size < attributes_.size_)
    erase_at_end(begin() + new_size, end());
}

template<class T, class Alloc>
bool vector<T, Alloc>::compareForIdentity(const value_type &a,
                                          const value_type &b) {
  return &a==&b;
}

template<class T, class Alloc>
void vector<T, Alloc>::assign(vector::size_type n, const value_type &val) {
  if (n < 0) {
    this->~vector();
    throw ft::length_error("vector");
  }
  if (attributes_.capacity_ < n) {
    field new_storage(nullptr, n, n);
    fill_initialize(new_storage, val, n, 0);
    destroy_storage(attributes_, 0);
    attributes_.swap(new_storage);
    destroy_storage(new_storage, 0);
  } else {
    ft::vector<T, Alloc> copy_vector(begin(), end());
    for (int i = 0; i < attributes_.size_; ++i) {
      if (compareForIdentity(*(attributes_.data_ + i), val)) {
        continue;
      }
      attributes_.alloc_.destroy(attributes_.data_ + i);
    }
    for (size_type i = 0; i < n; ++i) {
      try {
        if (compareForIdentity(*(attributes_.data_ + i), val)) {
          continue;
        }
        attributes_.alloc_.construct(attributes_.data_ + i, val);
      } catch (...) {
        attributes_ = std::move(copy_vector.attributes_);
        throw;
      }
    }
  };
  attributes_.size_ = n;
}
template<class T, class Alloc>
void vector<T, Alloc>::assign(std::initializer_list<value_type> l) {
  assign(l.begin(), l.end());
}

}
