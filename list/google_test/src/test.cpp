// -*- C++ -*-
//===---------------------------- list test -------------------------------===//
//
//                     Created by Aaron Berry on 4/13/21.
//
//===----------------------------------------------------------------------===//

#include <list>
#include <random>
#include "gtest/gtest.h"
//Your include
#include "list/list.h"

// Your namespace
#define my ft
#define list_ list
// STD namespace
#define stl std
#define _list list

template<class T>
void compare_lst(my::list_<T> &my_lst, stl::_list<T> &stl_lst) {
  EXPECT_EQ(my_lst.size(), stl_lst.size())
            << "\nVectors x and y are of unequal length\n";
  auto my_iter = my_lst.cbegin();
  auto stl_iter = stl_lst.cbegin();
  for (; my_iter != my_lst.cend() || stl_iter != stl_lst.cend(); ++my_iter, ++stl_iter) {
    EXPECT_EQ(*my_iter, *stl_iter)
              << "list x and y differ";
  }
}

template<class T>
void init_lst(my::list_<T> &my_lst, stl::_list<T> &stl_lst) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  auto my_iter = my_lst.begin();
  auto stl_iter = stl_lst.begin();
  for (; my_iter != my_lst.end() || stl_iter != stl_lst.end(); ++my_iter, ++stl_iter) {
    std::uniform_int_distribution<T> eng_rand(-10000, 10000);
    T value = eng_rand(eng);
    *my_iter = *stl_iter = value;
  }
}

// =============================================================================
// ============================= Constructor ===================================
// =============================================================================
template<class T, class U>
// Default constructor creates no elements.
void default_constructor() {
  {
    my::list_<T> my_lst;
    stl::_list<T> stl_lst;
    compare_lst<T>(my_lst, stl_lst);
  }
  {
    my::list_<U> my_lst;
    stl::_list<U> stl_lst;
    compare_lst<U>(my_lst, stl_lst);
  }
}
template<class T, class U>
// Creates a list with default constructed elements.
void default_elem_constructor() {
  {
    my::list_<T> my_lst(12);
    stl::_list<T> stl_lst(12);
    compare_lst<T>(my_lst, stl_lst);
  }
  {
    my::list_<U> my_lst(12);
    stl::_list<U> stl_lst(12);
    compare_lst<U>(my_lst, stl_lst);
  }
}

template<class T, class U>
// Creates a list with copies of an exemplar element.
void value_constructor(T t_val, U u_val) {
  {
    my::list_<T> my_lst(12, t_val);
    stl::_list<T> stl_lst(12, t_val);
    compare_lst<T>(my_lst, stl_lst);
  }
  {
    my::list_<U> my_lst(12, u_val);
    stl::_list<U> stl_lst(12, u_val);
    compare_lst<U>(my_lst, stl_lst);
  }
}

template<class T, class U>
// List copy constructor.
void copy_constructor() {
  {
    my::list_<T> my_lst_tmp(40);
    stl::_list<T> stl_lst_tmp(40);
    init_lst(my_lst_tmp, stl_lst_tmp);
    my::list_<T> my_lst(my_lst_tmp);
    stl::_list<T> stl_lst(stl_lst_tmp);
    compare_lst<T>(my_lst, stl_lst);
    compare_lst<T>(my_lst_tmp, stl_lst_tmp);
  }
  {
    my::list_<U> my_lst_tmp(40);
    stl::_list<U> stl_lst_tmp(40);
    init_lst(my_lst_tmp, stl_lst_tmp);
    my::list_<U> my_lst(my_lst_tmp);
    stl::_list<U> stl_lst(stl_lst_tmp);
    compare_lst<U>(my_lst, stl_lst);
    compare_lst<U>(my_lst_tmp, stl_lst_tmp);
  }
}

template<class T, class U>
// List move constructor.
void move_constructor() {
  {
    my::list_<T> my_lst_tmp(40);
    stl::_list<T> stl_lst_tmp(40);
    init_lst(my_lst_tmp, stl_lst_tmp);
    my::list_<T> my_lst(std::move(my_lst_tmp));
    stl::_list<T> stl_lst(std::move(stl_lst_tmp));
    compare_lst<T>(my_lst, stl_lst);
    compare_lst<T>(my_lst_tmp, stl_lst_tmp);
  }
  {
    my::list_<U> my_lst_tmp(40);
    stl::_list<U> stl_lst_tmp(40);
    init_lst(my_lst_tmp, stl_lst_tmp);
    my::list_<U> my_lst(std::move(my_lst_tmp));
    stl::_list<U> stl_lst(std::move(stl_lst_tmp));
    compare_lst<U>(my_lst, stl_lst);
    compare_lst<U>(my_lst_tmp, stl_lst_tmp);
  }
}

// Builds a list from an initializer_list.
void initializer_list_constructor() {
  {
    std::initializer_list<int> l = {2, 3, 3};
    my::list_<int> my_lst(l);
    stl::_list<int> stl_lst(l);
    compare_lst<int>(my_lst, stl_lst);
  }
  {
    std::initializer_list<std::string> l = {"2 ", "3", "3"};
    my::list_<std::string> my_lst(l);
    stl::_list<std::string> stl_lst(l);
    compare_lst<std::string>(my_lst, stl_lst);
  }
}

// Builds a list from a range.
void range_constructor() {
  {
    std::initializer_list<int> l = {2, 3, 3};
    my::list_<int> my_lst(l.begin(), l.end());
    stl::_list<int> stl_lst(l.begin(), l.end());
    compare_lst<int>(my_lst, stl_lst);
  }
  {
    std::vector<std::string> v = {"2 ", "3", "3", "9"};
    my::list_<std::string> my_lst(v.begin(), v.begin() + 2);
    stl::_list<std::string> stl_lst(v.begin(), v.begin() + 2);
    compare_lst<std::string>(my_lst, stl_lst);
  }
}

TEST(list, default_constructor) {
  default_constructor<int, std::string>();
}

TEST(list, default_elem_constructor) {
  default_elem_constructor<int, std::string>();
}

TEST(list, value_constructor) {
  value_constructor<int, std::string>(4, "234");
}


TEST(list, copy_constructor) {
  copy_constructor<int, float>();
}

TEST(list, move_constructor) {
  move_constructor<int, float>();
}

TEST(list, initializer_list_constructor) {
  initializer_list_constructor();
}

TEST(list, range_constructor) {
  range_constructor();
}
// -----------------------------------------------------------------------------

// =============================================================================
// =========================== Member Function =================================
// =============================================================================

// =============================== ASSIGN ======================================

template<class T, class U>
// List move constructor.
void assign_value(T t_val, U u_val) {
  {
    my::list_<T> my_lst(40);
    stl::_list<T> stl_lst(40);
    init_lst(my_lst, stl_lst);
    my_lst.assign(4, t_val);
    stl_lst.assign(4, t_val);
    compare_lst<T>(my_lst, stl_lst);
  }
  {
    my::list_<U> my_lst(40);
    stl::_list<U> stl_lst(40);
    init_lst(my_lst, stl_lst);
    my_lst.assign(4, u_val);
    stl_lst.assign(4, u_val);
    compare_lst<U>(my_lst, stl_lst);
  }
}

// Assigns a range to a list.
void assign_range() {
  {
    std::initializer_list<int> l = {2, 3, 3};
    my::list_<int> my_lst(40);
    stl::_list<int> stl_lst(40);
    init_lst(my_lst, stl_lst);
    my_lst.assign(l.begin(), l.begin() + 2);
    stl_lst.assign(l.begin(), l.begin() + 2);
    compare_lst<int>(my_lst, stl_lst);
  }
  {
    my::list_<std::string> my_lst(40);
    stl::_list<std::string> stl_lst(40);
    std::vector<std::string> v = {"2 ", "3", "3", "9"};
    my_lst.assign(v.begin(), v.begin() + 2);
    stl_lst.assign(v.begin(), v.begin() + 2);
    compare_lst<std::string>(my_lst, stl_lst);
  }
  {
    my::list_<int> my_lst(2);
    stl::_list<int> stl_lst(4);
    my_lst.assign({1, 23, 5, 68, 8988, 0});
    stl_lst.assign({1, 23, 5, 68, 8988, 0});
    compare_lst<int>(my_lst, stl_lst);
  }
}

TEST(list, assign_value) {
  assign_value<int, float>(9999, -02.3);
}

TEST(list, assign_range) {
  assign_range();
}

// =============================== BACK ========================================

// Returns a read/write reference to the data at the last element of the list.
TEST(list, back) {
  {
    stl::_list<int> stl_list(6);
    my::list_<int> my_list(6);
    for (stl::_list<int>::size_type i = 0; i < 6; ++i) {
      stl_list.push_back(i);
      my_list.push_back(i);
    }
    EXPECT_EQ(stl_list.back(), my_list.back())
              << "Vectors x and y differ in back";
  }
  {
    stl::_list<float> stl_list(6);
    my::list_<float> my_list(6);
    for (stl::_list<float>::size_type i = 0; i < 6; ++i) {
      stl_list.push_back(i);
      my_list.push_back(i);
    }
    EXPECT_EQ(stl_list.back(), my_list.back())
              << "Vectors x and y differ in back";
  }
  {
    stl::_list<const int> stl_list;
    my::list_<const int> my_list;
    stl_list.back();
    my_list.back();
  }
}





// =============================================================================
// =============================== FINISH ======================================
// =============================================================================
