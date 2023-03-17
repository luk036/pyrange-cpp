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

namespace detail {

template <typename T> struct RangeIterator {
  using iterator_category = std::output_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T *;               // or also value_type*
  using reference = T &;             // or also value_type&
  using const_reference = const T &; // or also value_type&
  using key_type = T;                // luk:

  T i;
  constexpr auto operator!=(const RangeIterator &other) const -> bool {
    return this->i != other.i;
  }
  constexpr auto operator==(const RangeIterator &other) const -> bool {
    return this->i == other.i;
  }
  CONSTEXPR14 auto operator*() const -> const_reference { return this->i; }
  CONSTEXPR14 auto operator*() -> reference { return this->i; }
  CONSTEXPR14 auto operator++() -> RangeIterator & {
    ++this->i;
    return *this;
  }
  CONSTEXPR14 auto operator++(int) -> RangeIterator {
    auto temp = *this;
    ++(*this);
    return temp;
  }
};

template <typename T> struct RangeIterableWrapper {
public:
  using iterator = RangeIterator<T>;
  using value_type = T;
  using key_type = T;

  // static_assert(sizeof(value_type) >= 0, "make compiler happy");
  // static_assert(sizeof(key_type) >= 0, "make compiler happy");

  T start;
  T stop;
  constexpr auto begin() const -> iterator { return iterator{this->start}; }
  constexpr auto end() const -> iterator { return iterator{this->stop}; }
  constexpr auto empty() const -> bool { return this->stop == this->start; }
  constexpr auto size() const -> size_t {
    return static_cast<size_t>(this->stop - this->start);
  }
  constexpr auto operator[](size_t n) const -> T {
    return T(this->start + n);
  } // no bounds checking
  constexpr auto contains(T n) const -> bool {
    return !(n < this->start) && n < this->stop;
  }
};

} // namespace detail

template <typename T>
CONSTEXPR14 auto range(T start, T stop) -> detail::RangeIterableWrapper<T> {
  if (stop < start) {
    stop = start;
  }
  return detail::RangeIterableWrapper<T>{start, stop};
}

template <typename T>
CONSTEXPR14 auto range(T stop) -> detail::RangeIterableWrapper<T> {
  return range(T(0), stop);
}

} // namespace py
