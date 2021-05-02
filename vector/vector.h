//
// Created by Aaron Berry on 5/2/21.
//
#pragma once

#include <utility>

#include "tools/memory.h"

namespace ft {

  class Length_error : public std::exception {
   public:
    Length_error() noexcept = default;
    Length_error(Length_error const &other) noexcept : m_error(other.m_error) {}
    Length_error &operator=(const Length_error &other) noexcept {
      if (this == &other) {
        return *this;
      }
      m_error = other.m_error;
      return *this;
    }
    ~Length_error() noexcept override = default;
    explicit Length_error(std::string error) : m_error(std::move(error)) {}
    const char *what() const noexcept override { return m_error.c_str(); }
   private:
    std::string m_error;
  };

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

    explicit Vector(size_type n) {
      try {
        alloc_.allocate(n);
      } catch (...) {
        throw ft::Length_error("vector");
      }
    }
   private:
    pointer          array_;
    size_type        size_;
    size_type        capacity_;
    ft::Allocator<T> alloc_;

  };
}