#pragma once

#include <cstddef>
#include <type_traits>
#include <utility>

#if __cpp_constexpr >= 201304
#define CONSTEXPR14 constexpr
#else
#define CONSTEXPR14 inline
#endif

template <typename T> using Value_type = typename T::value_type;

namespace py {

namespace detail {
template <typename T> struct _iterator {
  T i;
  constexpr auto operator!=(const _iterator &other) const -> bool {
    return this->i != other.i;
  }
  constexpr auto operator==(const _iterator &other) const -> bool {
    return this->i == other.i;
  }
  CONSTEXPR14 auto operator*() const -> const T & { return this->i; }
  CONSTEXPR14 auto operator*() -> T & { return this->i; }
  CONSTEXPR14 auto operator++() -> _iterator & {
    ++this->i;
    return *this;
  }
  CONSTEXPR14 auto operator++(int) -> _iterator {
    auto temp = *this;
    ++*this;
    return temp;
  }
};

template <typename T> struct iterable_wrapper {
public:
  using value_type = T; // luk:
  using key_type = T;   // luk:

  // static_assert(sizeof(value_type) >= 0, "make comipler happy");
  // static_assert(sizeof(key_type) >= 0, "make comipler happy");

  using iterator = _iterator<T>; // luk
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
CONSTEXPR14 auto range(T start, T stop) -> detail::iterable_wrapper<T> {
  if (stop < start) {
    stop = start;
  }
  return detail::iterable_wrapper<T>{start, stop};
}

template <typename T>
CONSTEXPR14 auto range(T stop) -> detail::iterable_wrapper<T> {
  return range(T(0), stop);
}

} // namespace py
