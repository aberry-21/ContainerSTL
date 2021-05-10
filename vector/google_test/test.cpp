//
// Created by Aaron Berry on 4/13/21.
//

#include <vector>
#include <list>
#include "gtest/gtest.h"
#include "vector.h"
#include "A.h"

template<class T>
void equal_vector(ft::vector<T> &my_vector, std::vector<T> &std_vector) {
  EXPECT_EQ(my_vector.size(), std_vector.size())
            << "\nVectors x and y are of unequal length\n";
  EXPECT_EQ(my_vector.capacity(), std_vector.capacity())
                << "\nVectors x and y are of unequal capacity\n";
  size_t size = std_vector.size();
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(my_vector[i], std_vector[i])
              << "Vectors x and y differ at index " << i;
  }
}

template<class T, class Alloc>
void equal_vector(ft::vector<T, Alloc> &my_vector,
                  std::vector<T, Alloc> &std_vector) {
  EXPECT_EQ(my_vector.size(), std_vector.size())
                << "\nVectors x and y are of unequal length\n";
  EXPECT_EQ(my_vector.capacity(), std_vector.capacity())
                << "\nVectors x and y are of unequal capacity\n";
  size_t size = std_vector.size();
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(my_vector[i], std_vector[i])
              << "Vectors x and y differ at index " << i;
  }
}
// =============================================================================
// ============================= Constructor ===================================
// =============================================================================

// --------------------Default constructor creates no elements.-----------------
template<class T>
void default_constructor() {
  std::vector<T> std_vector;
  ft::vector<T> my_vector;
  equal_vector<T>(my_vector, std_vector);
}

TEST(vector, default_constructor) {
  default_constructor<A>();
  default_constructor<int>();
  default_constructor<const int>();
  default_constructor<bool>();
  default_constructor<std::string>();
}
// -----------------------------------------------------------------------------

// ---------------------Creates a vector with no elements.----------------------
template<class T>
void constructor_with_no_elements() {
  std::vector<T> std_vector(ft::Allocator<T>);
  ft::vector<T> my_vector(std::allocator<T>);
}

TEST(vector, constructor_with_no_elements) {
  constructor_with_no_elements<A>();
  constructor_with_no_elements<int>();
  constructor_with_no_elements<const int>();
  constructor_with_no_elements<bool>();
  constructor_with_no_elements<std::string>();
}
// -----------------------------------------------------------------------------

// --------------Creates a vector with default constructed elements.------------
template<class T>
void constructor_with_default_elements(int count) {
  std::vector<T> std_vector(count);
  ft::vector<T> my_vector(count);
  equal_vector<T>(my_vector, std_vector);
}

TEST(vector, constructor_with_default_elements) {
  constructor_with_default_elements<A>(13);
  constructor_with_default_elements<int>(100);
  constructor_with_default_elements<const int>(12);
  constructor_with_default_elements<std::string>(10);
  try {
    ft::vector<int> my_vector(-10);
  } catch (std::exception const &ex) {
    EXPECT_EQ(ex.what(),std::string("vector"));
  }
  try {
    std::vector<int> std_vector(10);
    ft::vector<int> my_vector(std_vector.max_size() + 2);
  } catch (std::exception const &ex) {
    EXPECT_EQ(ex.what(),std::string("vector"));
  }
}
// -----------------------------------------------------------------------------

// -------------Creates a vector with copies of an exemplar element.------------
template<class T>
void constructor_with_value(int count,const T& value) {
  {
    std::vector<T> std_vector(count, value);
    ft::vector<T> my_vector(count, value);
    equal_vector<T>(my_vector, std_vector);
  }
  {
    std::vector<T, std::allocator<T>> std_vector(count, value);
    ft::vector<T, std::allocator<T>> my_vector(count, value);
    equal_vector<T, std::allocator<T>>(my_vector, std_vector);
  }
  {
    std::vector<T, ft::Allocator<T>> std_vector(count, value);
    ft::vector<T, ft::Allocator<T>> my_vector(count, value);
    equal_vector<T, ft::Allocator<T>>(my_vector, std_vector);
  }
}

TEST(vector, constructor_with_value) {
  constructor_with_value<A>(13, 4);
  constructor_with_value<int>(13, 4);
  constructor_with_value<const int>(12, 2);
  constructor_with_value<std::string>(10, std::string("vector"));
  try {
    ft::vector<int> my_vector(-10, 1);
  } catch (std::exception const &ex) {
    EXPECT_EQ(ex.what(),std::string("vector"));
  }
}
// -----------------------------------------------------------------------------

// ---------------------------Vector copy constructor.--------------------------
template<class T>
void copy_constructor(int count, const T& value) {
  std::vector<T> std_vector(count, value);
  std::vector<T> std_vector_copy(std_vector);
  ft::vector<T> my_vector(count, value);
  ft::vector<T> my_vector_copy(my_vector);
  equal_vector<T>(my_vector, std_vector);
  equal_vector<T>(my_vector_copy, std_vector_copy);
}

TEST(vector, copy_constructor) {
  copy_constructor<A>(13000, 4);
  copy_constructor<int>(13, 4);
  copy_constructor<const int>(12, 2);
  copy_constructor<std::string>(10, std::string("vector"));
}
// -----------------------------------------------------------------------------

// ----------------------Vector move constructor.-------------------------------
template<class T>
void move_constructor(int count, const T& value) {
  std::vector<T> std_vector(count, value);
  std::vector<T> std_vector_copy(std::move(std_vector));
  ft::vector<T> my_vector(count, value);
  ft::vector<T> my_vector_copy(std::move(my_vector));
  equal_vector<T>(my_vector, std_vector);
  equal_vector<T>(my_vector_copy, std_vector_copy);
}

TEST(vector, move_constructor) {
  move_constructor<A>(13000, 4);
  move_constructor<int>(13, 4);
  move_constructor<const int>(12, 2);
  move_constructor<std::string>(10, std::string("vector"));
}
// -----------------------------------------------------------------------------

// -------------------Builds a vector from an initializer list.-----------------
TEST(vector, initializer_list_constructor) {
  {
    std::vector<int> std_vector = {1, 2, 43, 4};
    ft::vector<int> my_vector = {1, 2, 43, 4};
    equal_vector<int>(my_vector, std_vector);
  }
  {
    std::vector<const int> std_vector = {1, 2, 43, 4};
    ft::vector<const int> my_vector = {1, 2, 43, 4};
    equal_vector<const int>(my_vector, std_vector);
  }
  {
    std::vector<std::string> std_vector = {"h", "e", "l", "l", "o"};
    ft::vector<std::string> my_vector = {"h", "e", "l", "l", "o"};
    equal_vector<std::string>(my_vector, std_vector);
  }
  {
    std::vector<A> std_vector = {A(1), A(2)};
    ft::vector<A> my_vector = {A(1), A(2)};
    equal_vector<A>(my_vector, std_vector);
  }
}
// -----------------------------------------------------------------------------

// ---Create a vector consisting of copies of the elements from [first,last-----
template<class T>
void iterator_constructor(int count, const T& value) {
  std::vector<T> std_vector(count, value);
  ft::vector<T> my_vector(count, value);
  {
    std::vector<T> std_vector_copy(std_vector.begin() + 2, std_vector.end());
    ft::vector<T> my_vector_copy(my_vector.begin() + 2, my_vector.end());
    equal_vector<T>(my_vector, std_vector);
    equal_vector<T>(my_vector_copy, std_vector_copy);
  }
  {
    std::vector<T> std_vector_copy(my_vector.begin() + 2, my_vector.end());
    ft::vector<T> my_vector_copy(std_vector.begin() + 2, std_vector.end());
    equal_vector<T>(my_vector, std_vector);
    equal_vector<T>(my_vector_copy, std_vector_copy);
  }
  {
    std::list<T> lst(count, value);
    std::vector<T> std_vector_copy(++lst.begin(), lst.end());
    ft::vector<T> my_vector_copy(++lst.begin(), lst.end());
    equal_vector<T>(my_vector_copy, std_vector_copy);
  }
}

TEST(vector, iterator_constructor) {
  iterator_constructor<A>(13000, 4);
  iterator_constructor<int>(13, 4);
  iterator_constructor<const int>(12, 2);
  iterator_constructor<std::string>(10, std::string("vector"));
  try {
    ft::vector<int> my_vector(10, 1);
    ft::vector<int> my_vector_copy(my_vector.end(), my_vector.begin());
  } catch (std::exception const &ex) {
    EXPECT_EQ(ex.what(),std::string("vector"));
  }
}
// -----------------------------------------------------------------------------

// =============================================================================
// =========================== Member Function =================================
// =============================================================================

// =============================== ASSIGN ======================================

// -----------------------Assigns a given value to a vector.--------------------
template<class T>
void assign_value(int count, const T& value) {
  // capacity < count
  {
    std::vector<T> std_vector(0, value);
    ft::vector<T> my_vector(0, value);
    equal_vector<T>(my_vector, std_vector);
    std_vector.assign(count, value);
    my_vector.assign(count, value);
    equal_vector<T>(my_vector, std_vector);
  }
  // capacity >= count
  {
    std::vector<T> std_vector(20000, value);
    ft::vector<T> my_vector(20000, value);
    equal_vector<T>(my_vector, std_vector);
    std_vector.assign(count, value);
    my_vector.assign(count, value);
    equal_vector<T>(my_vector, std_vector);
  }
}

TEST(vector, assign_value) {
  assign_value<A>(13000, 4);
  assign_value<int>(13, 4);
  assign_value<char>(12, 2);
  assign_value<std::string>(10, std::string("vector"));
}
// -----------------------------------------------------------------------------

// ----------------------Assigns a range to a vector.---------------------------
template<class T>
void assign_range_test(ft::vector<T> &my_vector, std::vector<T> &std_vector,
                       const T& value) {
  // self
  {
    std_vector.assign(std_vector.begin() + 2, std_vector.end());
    my_vector.assign(my_vector.begin() + 2, my_vector.end());
    equal_vector<T>(my_vector, std_vector);
  }
  // other vector
  {
    std::vector<T> copy_stl(std_vector);
    ft::vector<T> copy_my(my_vector);
    equal_vector<T>(my_vector, std_vector);
    equal_vector<T>(copy_my, copy_stl);
    std_vector.assign(copy_stl.begin() + 2, copy_stl.end());
    my_vector.assign(copy_stl.begin() + 2, copy_stl.end());
    equal_vector<T>(my_vector, std_vector);
    std_vector.assign(copy_my.begin() + 2, copy_my.end());
    my_vector.assign(copy_my.begin() + 2, copy_my.end());
    equal_vector<T>(my_vector, std_vector);
  }
  // list
  {
    std::list<T> lst(10, value);
    std_vector.assign(++lst.begin(), lst.end());
    my_vector.assign(++lst.begin(), lst.end());
    equal_vector<T>(my_vector, std_vector);
  }
  // all self
  {
    std_vector.assign(std_vector.begin(), std_vector.begin());
    my_vector.assign(my_vector.begin(), my_vector.begin());
    equal_vector<T>(my_vector, std_vector);
  }
  // first==last
  {
    std_vector.assign(std_vector.begin(), std_vector.begin());
    my_vector.assign(my_vector.end(), my_vector.end());
    equal_vector<T>(my_vector, std_vector);
  }
  {
    std_vector.assign(std_vector.rbegin(), std_vector.rend());
    my_vector.assign(std_vector.rbegin(), std_vector.rend());
    equal_vector<T>(my_vector, std_vector);
  }
}

template<class T, typename InputIterator>
void assign_range_ex(const T& value, InputIterator first, InputIterator last) {
  ft::vector<T> my_vector(10, value);
  std::vector<T> std_vector(10, value);
  try {
    my_vector.assign(first, last);
  } catch (std::exception const &ex) {
    EXPECT_EQ(ex.what(), std::string("vector"));
  }
  try {
    std_vector.assign(first, last);
  } catch (std::exception const &ex) {
    EXPECT_EQ(ex.what(), std::string("vector"));
  }
  equal_vector<T>(my_vector, std_vector);
}

template<class T>
void assign_range(const T& value) {
  // ex test
  {
    std::vector<T> std_vector(100, value);
    assign_range_ex(value, std_vector.rbegin(), std_vector.rend());
    assign_range_ex(value, std_vector.begin(), std_vector.end());
    assign_range_ex(value, std_vector.rend(), std_vector.rbegin());
    assign_range_ex(value, std_vector.end(), std_vector.begin());
  }
  // capacity < count
  {
    std::vector<T> std_vector(5, value);
    ft::vector<T> my_vector(5, value);
    assign_range_test<T>(my_vector, std_vector, value);
  }
  // capacity >= count
  {
    std::vector<T> std_vector(20000, value);
    ft::vector<T> my_vector(20000, value);
    assign_range_test<T>(my_vector, std_vector, value);
  }
}

TEST(vector, assign_range) {
  assign_range<A>(4);
  assign_range<int>(4);
  assign_range<char>(2);
  assign_range<std::string>(std::string("vector"));
}
// -----------------------------------------------------------------------------

// --------------------Assigns an initializer list to a vector.-----------------
template<class T>
void assign_initializer_list(const T& value, initializer_list<T> l) {
  // capacity < count
  {
    std::vector<T> std_vector(5, value);
    ft::vector<T> my_vector(5, value);
    std_vector.assign(l);
    my_vector.assign(l);
    equal_vector<T>(my_vector, std_vector);
  }
  // capacity >= count
  {
    std::vector<T> std_vector(20000, value);
    ft::vector<T> my_vector(20000, value);
    std_vector.assign(l);
    my_vector.assign(l);
    equal_vector<T>(my_vector, std_vector);
  }
}

TEST(vector, assign_initializer_list) {
  assign_initializer_list<A>(4, {A(1), A(2)});
  assign_initializer_list<int>(4, {1, 2});
  assign_initializer_list<char>(2, {1, 2});
  assign_initializer_list<std::string>(std::string("vector"), {"a", "b"});
}
// -----------------------------------------------------------------------------

// ================================ AT =========================================

// --------------Provides access to the data contained in the vector.-----------
template<class T>
void at(int count, const T& value, int index) {
  std::vector<T> std_vector(count, value);
  ft::vector<T> my_vector(count, value);
  EXPECT_EQ(my_vector.at(index), std_vector.at(index))
            << "Vectors x and y differ at index " << index;
}

TEST(vector, at) {
  at<const A>(4, 2, 2);
  at<int>(4, 3, 1);
  at<char>(2, 4, 0);
  at<std::string>(3 ,std::string("vector"), 1);
  try {
    std::vector<int> my_vector(10, 1);
    my_vector.at(92929292);
  } catch (std::exception const &ex) {
    EXPECT_EQ(ex.what(), std::string("vector"));
  }
}
// -----------------------------------------------------------------------------

// =============================== BACK ========================================

// -----Returns a reference to the data at the last element of the vector.------
TEST(vector, back) {
  {
    std::vector<int> std_vector(6);
    ft::vector<int> my_vector(6);
    for (std::vector<int>::size_type i = 0; i < 6; ++i) {
      std_vector[i] = static_cast<int>(i);
    }
    for (ft::vector<int>::size_type i = 0; i < 6; ++i) {
      my_vector[i] = static_cast<int>(i);
    }
    EXPECT_EQ(std_vector.back(), my_vector.back())
              << "Vectors x and y differ in back";
  }
  {
    std::vector<A> std_vector(6);
    ft::vector<A> my_vector(6);
    for (std::vector<A>::size_type i = 0; i < 6; ++i) {
      std_vector[i] = A(static_cast<int>(i));
    }
    for (ft::vector<A>::size_type i = 0; i < 6; ++i) {
      my_vector[i] = A(static_cast<int>(i));
    }
    EXPECT_EQ(std_vector.back(), my_vector.back())
              << "Vectors x and y differ in back";
  }
  {
    std::vector<A> std_vector;
    ft::vector<A> my_vector;
    std_vector.back();
    my_vector.back();
  }
}
// -----------------------------------------------------------------------------

// =============================== FRONT =======================================

// -----Returns a reference to the data at the first element of the vector.-----
TEST(vector, front) {
  {
    std::vector<int> std_vector(6);
    ft::vector<int> my_vector(6);
    for (std::vector<int>::size_type i = 0; i < 6; ++i) {
      std_vector[i] = static_cast<int>(i);
    }
    for (ft::vector<int>::size_type i = 0; i < 6; ++i) {
      my_vector[i] = static_cast<int>(i);
    }
    EXPECT_EQ(std_vector.front(), my_vector.front())
              << "Vectors x and y differ in front";
  }
  {
    std::vector<A> std_vector(6);
    ft::vector<A> my_vector(6);
    for (std::vector<A>::size_type i = 0; i < 6; ++i) {
      std_vector[i] = A(static_cast<int>(i));
    }
    for (ft::vector<A>::size_type i = 0; i < 6; ++i) {
      my_vector[i] = A(static_cast<int>(i));
    }
    EXPECT_EQ(std_vector.front(), my_vector.front())
              << "Vectors x and y differ in front";
  }
  {
    std::vector<A> std_vector;
    ft::vector<A> my_vector;
    std_vector.front();
    my_vector.front();
  }
}
// -----------------------------------------------------------------------------

// =============================== BEGIN =======================================

// Returns a iterator that points to the first element in the vector.
// Iteration is done in ordinary element order.

TEST(vector, begin) {
  {
    std::vector<int> std_vector(10);
    ft::vector<int> my_vector(10);
    for (std::vector<int>::size_type i = 0; i < std_vector.size(); ++i) {
      std_vector[i] = static_cast<int>(i);
    }
    for (ft::vector<int>::size_type i = 0; i < my_vector.size(); ++i) {
      my_vector[i] = static_cast<int>(i);
    }
    EXPECT_EQ(*std_vector.begin(), *my_vector.begin())
              << "Vectors x and y differ in begin";
  }
  {
    std::vector<A> std_vector(1);
    ft::vector<A> my_vector(1);
    for (std::vector<A>::size_type i = 0; i < std_vector.size(); ++i) {
      std_vector[i] = A(static_cast<int>(i));
    }
    for (ft::vector<A>::size_type i = 0; i < my_vector.size(); ++i) {
      my_vector[i] = A(static_cast<int>(i));
    }
    EXPECT_EQ(*std_vector.begin(), *my_vector.begin())
              << "Vectors x and y differ in begin";
  }
  {
    std::vector<A> std_vector;
    ft::vector<A> my_vector;
    std_vector.begin();
    my_vector.begin();
  }
}
// -----------------------------------------------------------------------------

// ============================= CAPACITY ======================================

// -----------------------------------------------------------------------------
TEST(vector, capacity) {
  {
    std::vector<int> std_vector(10);
    ft::vector<int> my_vector(10);
    EXPECT_EQ(std_vector.capacity(), my_vector.capacity())
              << "Vectors x and y are of unequal capacity";
  }
  {
    std::vector<A> std_vector(1);
    ft::vector<A> my_vector(1);
    EXPECT_EQ(std_vector.capacity(), my_vector.capacity())
              << "Vectors x and y are of unequal capacity";
  }
  {
    std::vector<A> std_vector;
    ft::vector<A> my_vector;
    EXPECT_EQ(std_vector.capacity(), my_vector.capacity())
              << "Vectors x and y are of unequal capacity";
  }
}
// -----------------------------------------------------------------------------

// ============================== CLEAR ========================================

// Erases all the elements. Note that this function only erases the elements,
// and that if the elements themselves are pointers,
// the pointed-to memory is not touched in any way.
// Managing the pointer is the user's responsibility.
template<class T>
void clear(int count, const T& value) {
  std::vector<T> std_vector(count, value);
  ft::vector<T> my_vector(count, value);
  equal_vector<T>(my_vector, std_vector);
  std_vector.clear();
  my_vector.clear();
  equal_vector<T>(my_vector, std_vector);
}

TEST(vector, clear) {
  clear<A>(13000, 4);
  clear<int>(13, 4);
  clear<const int>(12, 2);
  clear<std::string>(10, std::string("vector"));
}
// -----------------------------------------------------------------------------
