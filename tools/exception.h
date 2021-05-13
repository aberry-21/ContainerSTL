// -*- C++ -*-
//===------------------------- exception ----------------------------------===//
//
//                     Created by Aaron Berry on 5/3/21.
//
//===----------------------------------------------------------------------===//

#pragma once

#include <utility>

namespace ft {
  class base_error : public std::exception {
   protected:
    std::string error_{};
   public:
    explicit base_error(std::string error) : error_(std::move(error)) {}
    const char* what() const noexcept override { return error_.c_str(); }
  };


  class length_error : public base_error {
   public:
    explicit length_error(std::string error)
            : base_error(std::move(error)) {};
  };

  class out_of_range : public base_error {
   public:
    explicit out_of_range(std::string error)
    : base_error(std::move(error)) {};
  };
}
