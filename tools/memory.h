// -*- C++ -*-
//===-------------------------- memory ------------------------------------===//
//
//                     Created by Aaron Berry on 4/30/21.
//
//                allocator_traits and allocator implementation
//
//===----------------------------------------------------------------------===//

/*
    memory synopsis

namespace ft
{

template <class Alloc>
struct allocator_traits
{
    typedef Alloc                        allocator_type;
    typedef typename allocator_type::value_type
                                         value_type;

    typedef Alloc::pointer | value_type* pointer;
    typedef Alloc::const_pointer
          | pointer_traits<pointer>::rebind<const value_type>
                                         const_pointer;
    typedef Alloc::void_pointer
          | pointer_traits<pointer>::rebind<void>
                                         void_pointer;
    typedef Alloc::const_void_pointer
          | pointer_traits<pointer>::rebind<const void>
                                         const_void_pointer;
    typedef Alloc::difference_type
          | pointer_traits<pointer>::difference_type
                                         difference_type;
    typedef Alloc::size_type
          | make_unsigned<difference_type>::type
                                         size_type;
    typedef Alloc::propagate_on_container_copy_assignment
          | false_type                   propagate_on_container_copy_assignment;
    typedef Alloc::propagate_on_container_move_assignment
          | false_type                   propagate_on_container_move_assignment;
    typedef Alloc::propagate_on_container_swap
          | false_type                   propagate_on_container_swap;
    typedef Alloc::is_always_equal
          | is_empty                     is_always_equal;

    template <class T> using rebind_alloc  = Alloc::rebind<U>::other | Alloc<T, Args...>;
    template <class T> using rebind_traits = allocator_traits<rebind_alloc<T>>;

    static pointer allocate(allocator_type& a, size_type n);                          // [[nodiscard]] in C++20
    static pointer allocate(allocator_type& a, size_type n, const_void_pointer hint); // [[nodiscard]] in C++20

    static void deallocate(allocator_type& a, pointer p, size_type n) noexcept;

    template <class T, class... Args>
        static void construct(allocator_type& a, T* p, Args&&... args);

    template <class T>
        static void destroy(allocator_type& a, T* p);

    static size_type max_size(const allocator_type& a); // noexcept in C++14

    static allocator_type
        select_on_container_copy_construction(const allocator_type& a);
};

template <>
class allocator<void>
{
public:
    typedef void*                                 pointer;
    typedef const void*                           const_pointer;
    typedef void                                  value_type;

    template <class _Up> struct rebind {typedef allocator<_Up> other;};
};

template <class T>
class allocator
{
public:
    typedef size_t                                size_type;
    typedef ptrdiff_t                             difference_type;
    typedef T*                                    pointer;
    typedef const T*                              const_pointer;
    typedef typename add_lvalue_reference<T>::type       reference;
    typedef typename add_lvalue_reference<const T>::type const_reference;
    typedef T                                     value_type;

    template <class U> struct rebind {typedef allocator<U> other;};

    constexpr allocator() noexcept;                      // constexpr in C++20
    constexpr allocator(const allocator&) noexcept;      // constexpr in C++20
    template <class U>
      constexpr allocator(const allocator<U>&) noexcept; // constexpr in C++20
    ~allocator();
    pointer address(reference x) const noexcept;
    const_pointer address(const_reference x) const noexcept;
    pointer allocate(size_type, allocator<void>::const_pointer hint = 0);
    void deallocate(pointer p, size_type n) noexcept;
    size_type max_size() const noexcept;
    template<class U, class... Args>
        void construct(U* p, Args&&... args);
    template <class U>
        void destroy(U* p);
};

template <class T, class U>
bool operator==(const allocator<T>&, const allocator<U>&) noexcept;

template <class T, class U>
bool operator!=(const allocator<T>&, const allocator<U>&) noexcept;
*/

#include "iostream"
#include <new>

namespace ft {

  template <class Tp> class Allocator;

  template<>
  class Allocator<void> {
   public:
    typedef void        *pointer;
    typedef const void  *const_pointer;
    typedef void        value_type;

    template<class Up>
    struct rebind { typedef Allocator<Up> other; };
  };

  template<class T>
  class Allocator {
   public:
    typedef size_t                                              size_type;
    typedef ptrdiff_t                                           difference_type;
    typedef T*                                                  pointer;
    typedef const T*                                            const_pointer;
    typedef T                                                   value_type;
    typedef value_type&                                         reference;
    typedef const value_type&                                   const_reference;

    template<class U>
    struct rebind { typedef Allocator<U> other; };

    constexpr Allocator() noexcept {};
    ~Allocator() {};
    constexpr Allocator(const Allocator &other) noexcept {};
    template<class U>
    constexpr Allocator(const Allocator<U> &other) noexcept {};

  //  obtains the address of an object, even if operator& is overloaded
    pointer address(reference x) const noexcept {
      return reinterpret_cast<pointer>(&x);
    }

    const_pointer address(const_reference x) const noexcept {
      return reinterpret_cast<const_pointer>(address(x));
    }

  //  allocates uninitialized storage
    pointer allocate(size_type size, Allocator<void>::const_pointer hint = 0) {
      return reinterpret_cast<pointer>(
          ::operator new(size * sizeof(value_type)));
    }

  //  deallocates storage
    void deallocate(pointer p, size_type n) noexcept {
      ::operator delete(p);
    }

  //  returns the largest supported allocation size
    size_type max_size() const noexcept {
      return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }

  //  constructs an object in allocated storage
    template<class U, class... Args>
    void construct(U *p, Args &&... args) {
      new(p) U(args...);
    }

  //  destructs an object in allocated storage
    template<class U>
    void destroy(U *p) {
      p->~U();
    }
  };

  template<class T, class U>
  bool operator==(const Allocator<T> &target, const Allocator<U> &other) noexcept {
    return true;
  }

  template<class T, class U>
  bool operator!=(const Allocator<T> &target, const Allocator<U> &other) noexcept {
    return !operator==<T, U>(target, other);
  }
}