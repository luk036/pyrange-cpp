#pragma once

#include <cstddef>
#include <iterator>
#include <type_traits>

#if __cpp_constexpr >= 201304
#define CONSTEXPR14 constexpr
#else
#define CONSTEXPR14 inline
#endif

namespace py {

/**
 * @brief
 *
 * @tparam T
 */
template <typename T> struct RangeIterator {
  using iterator_category = std::output_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T *;               // or also value_type*
  using reference = T &;             // or also value_type&
  using const_reference = const T &; // or also value_type&
  using key_type = T;                // luk:

  T i;

  /**
   * @brief Not equal to
   *
   * The `operator!=` function is an overloaded operator that checks if the
   * current iterator is not equal to another iterator. It takes another
   * `RangeIterator` object `other` as a parameter and returns a boolean value
   * indicating whether the two iterators are not equal.
   *
   * @param other
   * @return true
   * @return false
   */
  constexpr auto operator!=(const RangeIterator &other) const -> bool {
    return this->i != other.i;
  }

  /**
   * @brief Equal to operator
   *
   * The `operator==` function is an overloaded operator that checks if the
   * current iterator is equal to another iterator. It takes another
   * `RangeIterator` object `other` as a parameter and returns a boolean value
   * indicating whether the two iterators are equal.
   *
   * @param other
   * @return true
   * @return false
   */
  constexpr auto operator==(const RangeIterator &other) const -> bool {
    return this->i == other.i;
  }

  /**
   * @brief
   *
   * The code snippet you provided is defining the `operator*()` function for
   * the `RangeIterator` struct. This function is used to dereference the
   * iterator and return the value it points to.
   *
   * @return const_reference
   */
  CONSTEXPR14 auto operator*() const -> const_reference { return this->i; }

  /**
   * @brief
   *
   * The code snippet you provided is defining the `operator*()` function for
   * the `RangeIterator` struct. This function is used to dereference the
   * iterator and return the value it points to.
   *
   * @return reference
   */
  CONSTEXPR14 auto operator*() -> reference { return this->i; }

  /**
   * @brief
   *
   * The code snippet you provided is defining the pre-increment operator
   * (`operator++()`) for the `RangeIterator` struct. This operator is used to
   * increment the iterator to the next element in the range.
   *
   * @return RangeIterator&
   */
  CONSTEXPR14 auto operator++() -> RangeIterator & {
    ++this->i;
    return *this;
  }

  /**
   * @brief
   *
   * The code snippet you provided is defining the post-increment operator
   * (`operator++(int)`) for the `RangeIterator` struct. This operator is used
   * to increment the iterator to the next element in the range, but it returns
   * a copy of the iterator before the increment.
   *
   * @return RangeIterator
   */
  CONSTEXPR14 auto operator++(int) -> RangeIterator {
    auto temp = *this;
    ++(*this);
    return temp;
  }
};

/**
 * @brief Range
 *
 * The code snippet defines a struct template called `Range` that represents a
 * range of values. It has two template parameters, `T` which represents the
 * type of the values in the range.
 *
 * @tparam T
 */
template <typename T> struct Range {
public:
  using iterator = RangeIterator<T>;
  using value_type = T;
  using key_type = T;

  // static_assert(sizeof(value_type) >= 0, "make compiler happy");
  // static_assert(sizeof(key_type) >= 0, "make compiler happy");

  T start;
  T stop;

  /**
   * @brief begin
   *
   * The `begin()` function is a member function of the `Range` struct
   * template. It returns an iterator pointing to the beginning of the range. In
   * this case, it creates a `RangeIterator` object with the `start` value of
   * the range and returns it.
   *
   * @return iterator
   */
  constexpr auto begin() const -> iterator { return iterator{this->start}; }

  /**
   * @brief end
   *
   * The `end()` function is a member function of the `Range` struct template.
   * It returns an iterator pointing to the end of the range. In this case, it
   * creates a `RangeIterator` object with the `stop` value of the range and
   * returns it. This iterator represents the position one past the last element
   * in the range.
   *
   * @return iterator
   */
  constexpr auto end() const -> iterator { return iterator{this->stop}; }

  /**
   * @brief empty
   *
   * The `empty()` function is a member function of the `Range` struct template.
   * It checks if the range is empty, meaning if the `start` and `stop` values
   * are equal.
   *
   * @return true
   * @return false
   */
  constexpr auto empty() const -> bool { return this->stop == this->start; }

  /**
   * @brief size
   *
   * The `size()` function is a member function of the `Range` struct template.
   * It calculates and returns the size of the range, which is the number of
   * elements in the range.
   *
   * @return size_t
   */
  constexpr auto size() const -> size_t {
    return static_cast<size_t>(this->stop - this->start);
  }

  /**
   * @brief
   *
   * @param n
   * @return T
   */
  constexpr auto operator[](size_t n) const -> T {
    return T(this->start + n);
  } // no bounds checking

  /**
   * @brief
   *
   * @param n
   * @return true
   * @return false
   */
  constexpr auto contains(T n) const -> bool {
    return !(n < this->start) && n < this->stop;
  }
};

/**
 * @brief range(T start, T stop)
 *
 * The `range(T start, T stop)` function is creating a range of values from
 * `start` to `stop`. It returns a `Range<T>` object that represents the range.
 * The range includes all values from `start` up to, but not including, `stop`.
 *
 * @tparam T
 * @param start
 * @param stop
 * @return Range<T>
 */
template <typename T> CONSTEXPR14 auto range(T start, T stop) -> Range<T> {
  if (stop < start) {
    stop = start;
  }
  return Range<T>{start, stop};
}

/**
 * @brief range(T stop)
 *
 * The `range(T stop)` function is creating a range of values from 0 to `stop`.
 * It returns a `Range<T>` object that represents the range. The range includes
 * all values from 0 up to, but not including, `stop`.
 *
 * @tparam T
 * @param stop
 * @return Range<T>
 */
template <typename T> CONSTEXPR14 auto range(T stop) -> Range<T> {
  return range(T(0), stop);
}

} // namespace py
