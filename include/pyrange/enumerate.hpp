#pragma once

#include <cstddef>  // import size_t
#include <iterator> // import std::begin() std::end()
#include <type_traits>
#include <utility>

namespace py {

namespace detail {

template <typename T> struct EnumerateIterator {
  typedef decltype(std::begin(std::declval<T>())) TIter;
  using iter_ref = typename std::iterator_traits<TIter>::reference;

  size_t i;
  TIter iter;

  auto operator!=(const EnumerateIterator &other) const -> bool {
    return iter != other.iter;
  }

  EnumerateIterator &operator++() {
    ++i;
    ++iter;
    return *this;
  }

  auto operator*() const -> std::pair<size_t, iter_ref> {
    return std::make_pair(i, *iter);
  }
};

template <typename T> struct EnumerateIterableWrapper {
  T &iterable;
  auto begin() const -> EnumerateIterator<T> {
    return EnumerateIterator<T>{0, std::begin(iterable)};
  }
  auto end() const -> EnumerateIterator<T> {
    return EnumerateIterator<T>{0, std::end(iterable)};
  }
};

} // namespace detail

/**
 * @brief
 *
 * @tparam T
 * @tparam decltype(std::begin(std::declval<T>()))
 * @tparam decltype(std::end(std::declval<T>()))
 * @param[in] iterable
 * @return constexpr auto
 */
template <typename T>
inline auto enumerate(T &iterable) -> detail::EnumerateIterableWrapper<T> {
  return detail::EnumerateIterableWrapper<T>{iterable};
}

/**
 * @brief
 *
 * @tparam T
 * @tparam decltype(std::begin(std::declval<T>()))
 * @tparam decltype(std::end(std::declval<T>()))
 * @param[in] iterable
 * @return constexpr auto
 */
template <typename T>
inline auto const_enumerate(const T &iterable)
    -> detail::EnumerateIterableWrapper<const T> {
  return detail::EnumerateIterableWrapper<const T>{iterable};
}

} // namespace py
