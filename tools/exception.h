//
// Created by Aaron Berry on 5/3/21.
//

#pragma once

#include <utility>

namespace ft {
  class Base_error : public std::exception {
   protected:
    std::string error_{};
   public:
    explicit Base_error(std::string error) : error_(std::move(error)) {}
    const char* what() const noexcept override { return error_.c_str(); }
  };


  class Length_error : public Base_error {
   public:
    explicit Length_error(std::string error)
            : Base_error(std::move(error)) {};
  };

  class OutOfRange : public Base_error {
   public:
    explicit OutOfRange(std::string error)
    : Base_error(std::move(error)) {};
  };
}
