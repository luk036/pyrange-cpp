#pragma once

#include <cstddef>  // import size_t
#include <iterator> // import std::begin() std::end()
#include <type_traits>
#include <utility>

namespace py {

namespace detail {

/**
 * @brief EnumerateIterator
 *
 * The code defines a struct called `EnumerateIterator` that is used to iterate
 * over a container or range and provide the index of each element in the
 * iteration.
 *
 * @tparam T
 */
template <typename T> struct EnumerateIterator {
  typedef decltype(std::begin(std::declval<T>())) TIter;
  using iter_ref = typename std::iterator_traits<TIter>::reference;

  size_t i;
  TIter iter;

  /**
   * @brief Not equal to
   *
   * The `operator!=` function is an overloaded operator that checks for
   * inequality between two `EnumerateIterator` objects. It compares the `iter`
   * member of the current object with the `iter` member of the `other` object.
   * If they are not equal, it returns `true`, indicating that the two iterators
   * are not pointing to the same element. Otherwise, it returns `false`,
   * indicating that the two iterators are equal.
   *
   * @param other
   * @return true
   * @return false
   */
  auto operator!=(const EnumerateIterator &other) const -> bool {
    return iter != other.iter;
  }

  /**
   * @brief
   *
   * The `operator++()` function is an overloaded operator that increments the
   * `EnumerateIterator` object. It increases the value of the `i` member
   * variable by 1 and advances the `iter` member variable to the next element
   * in the iteration. It then returns a reference to the updated
   * `EnumerateIterator` object.
   *
   * @return EnumerateIterator&
   */
  EnumerateIterator &operator++() {
    ++i;
    ++iter;
    return *this;
  }

  /**
   * @brief
   *
   * The `operator*()` function is an overloaded operator that returns the
   * current element in the iteration as a `std::pair<size_t, iter_ref>`. The
   * `size_t` value represents the index of the element, and the `iter_ref`
   * value represents a reference to the element itself. This allows you to
   * access both the index and the element in a single expression when using the
   * `enumerate()` function.
   *
   * @return std::pair<size_t, iter_ref>
   */
  auto operator*() -> std::pair<size_t, iter_ref> {
    return std::pair<size_t, iter_ref>{i, *iter};
  }
};

/**
 * @brief EnumerateIterableWrapper
 *
 * The code defines a struct called `EnumerateIterableWrapper` that acts as a
 * wrapper for an iterable object. It provides two member functions, `begin()`
 * and `end()`, which return instances of the `EnumerateIterator` struct.
 *
 * @tparam T
 */
template <typename T> struct EnumerateIterableWrapper {
  T &iterable;

  /**
   * @brief begin
   *
   * The `begin()` function is a member function of the
   * `EnumerateIterableWrapper` struct. It returns an instance of the
   * `EnumerateIterator<T>` struct, which is used to iterate over the elements
   * of the iterable object.
   *
   * @return EnumerateIterator<T>
   */
  auto begin() const -> EnumerateIterator<T> {
    return EnumerateIterator<T>{0, std::begin(iterable)};
  }

  /**
   * @brief end
   *
   * The `end()` function is a member function of the `EnumerateIterableWrapper`
   * struct. It returns an instance of the `EnumerateIterator<T>` struct, which
   * is used to mark the end of the iteration over the elements of the iterable
   * object.
   *
   * @return EnumerateIterator<T>
   */
  auto end() const -> EnumerateIterator<T> {
    return EnumerateIterator<T>{0, std::end(iterable)};
  }
};

} // namespace detail

/**
 * @brief enumerate(T &iterable)
 *
 * The `enumerate(T &iterable)` function is a utility function that allows you
 * to iterate over a container or range and also get the index of each element
 * in the iteration. It returns an instance of the
 * `detail::EnumerateIterableWrapper<T>` class, which provides a range-based for
 * loop compatible interface.
 *
 * @tparam T
 * @param[in] iterable
 * @return detail::EnumerateIterableWrapper<T>
 */
template <typename T>
inline auto enumerate(T &iterable) -> detail::EnumerateIterableWrapper<T> {
  return detail::EnumerateIterableWrapper<T>{iterable};
}

/**
 * @brief const_enumerate(const T &iterable)
 *
 * The `const_enumerate(const T &iterable)` function is a utility function that
 * allows you to iterate over a constant container or range and also get the
 * index of each element in the iteration. It returns an instance of the
 * `detail::EnumerateIterableWrapper<const T>` class, which provides a
 * range-based for loop compatible interface. This function is useful when you
 * want to iterate over a constant container without modifying its elements.
 *
 * @tparam T
 * @param iterable
 * @return detail::EnumerateIterableWrapper<const T>
 */
template <typename T>
inline auto const_enumerate(const T &iterable)
    -> detail::EnumerateIterableWrapper<const T> {
  return detail::EnumerateIterableWrapper<const T>{iterable};
}

} // namespace py
