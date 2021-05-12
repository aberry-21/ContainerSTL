//
// Created by Aaron Berry on 5/10/21.
//

#pragma once

class A {
 public:
  A();
  A(int count);
  A(A const & x);
  A &operator=(A const & other);
  A (A&& other) noexcept;
  A& operator=(A&& other) noexcept;
  ~A();
  int GetCount() const;
 private:
  int   count_;
  char* storage_;
};

A::A() {
  count_ = 10;
  storage_ = new char(count_);
}

A::A(int count) {
  count_ = count;
  storage_ = new char(count_);
}

A::A(const A& x){
  count_ = x.count_;
  storage_ = new char(count_);
}

A &A::operator=(const A& other) {
  if (this == &other) {
    return *this;
  }
  char* new_storage = new char(other.count_);
  delete storage_;
  storage_ = new_storage;
  count_ = other.count_;
  return *this;
}

A &A::operator=(A &&other) noexcept {
  delete storage_;
  count_ = other.count_;
  storage_ = other.storage_;
  other.count_ = 0;
  other.storage_ = nullptr;
  return *this;
}

A::A(A &&other) noexcept {
  count_ = other.count_;
  storage_ = other.storage_;
  other.count_ = 0;
  other.storage_ = nullptr;
}

A::~A() {
  delete storage_;
  count_ = 0;
}
int A::GetCount() const {
  return count_;
}

bool operator==(const A& a, const A& b) {
  return a.GetCount() == b.GetCount();
}