#pragma once

#include <vector>

namespace fun {

namespace detail {

/**
 * @brief Singly linked list
 *
 * The code is defining a struct called `RobinSlNode` which represents a node in
 * a singly linked list. It has two members: `next`, which is a pointer to the
 * next node in the list, and `key`, which stores the value of the node. The
 * template parameter `T` represents the type of the value stored in the node.
 *
 * @tparam T
 */
template <typename T> struct RobinSlNode {
  RobinSlNode *next;
  T key;
};

/**
 * @brief RobinIterator
 *
 * The code is defining a struct called `RobinIterator` which represents an
 * iterator for the `Robin` class. It is used to iterate over the elements in
 * the round-robin cycle.
 *
 * @tparam T
 */
template <typename T> struct RobinIterator {
  const RobinSlNode<T> *cur;

  /**
   * @brief Not equal to
   *
   * The code is defining the `operator!=` function for the `RobinIterator`
   * struct. This function is used to compare two `RobinIterator` objects for
   * inequality. It takes another `RobinIterator` object `other` as a parameter
   * and returns `true` if the `cur` member of the current object is not equal
   * to the `cur` member of the `other` object, and `false` otherwise.
   *
   * @param other
   * @return true
   * @return false
   */
  auto operator!=(const RobinIterator &other) const -> bool {
    return cur != other.cur;
  }

  /**
   * @brief Equal to
   *
   * The code is defining the `operator==` function for the `RobinIterator`
   * struct. This function is used to compare two `RobinIterator` objects for
   * equality. It takes another `RobinIterator` object `other` as a parameter
   * and returns `true` if the `cur` member of the current object is equal
   * to the `cur` member of the `other` object, and `false` otherwise.
   *
   * @param other
   * @return true
   * @return false
   */
  auto operator==(const RobinIterator &other) const -> bool {
    return cur == other.cur;
  }

  /**
   * @brief
   *
   * The code is defining the `operator++` function for the `RobinIterator`
   * struct. This function is used to increment the iterator to the next element
   * in the round-robin cycle.
   *
   * @return RobinIterator&
   */
  auto operator++() -> RobinIterator & {
    cur = cur->next;
    return *this;
  }

  /**
   * @brief
   *
   * The code is defining the `operator*` function for the `RobinIterator`
   * struct. This function is used to dereference the iterator and return a
   * reference to the value stored in the current node of the linked list. In
   * this case, it returns a reference to the `key` member of the current node.
   * The `const` qualifier indicates that the function does not modify the state
   * of the iterator.
   *
   * @return const T&
   */
  auto operator*() const -> const T & { return cur->key; }
};

/**
 * @brief RobinIterableWrapper
 *
 * The code is defining a struct called `RobinIterableWrapper` which is used as
 * a wrapper for iterating over a round-robin cycle in the `Robin` class.
 *
 * @tparam T
 */
template <typename T> struct RobinIterableWrapper {
  const detail::RobinSlNode<T> *node;
  // const Robin<T> *rr;
  // T from_part;

  /**
   * @brief begin
   *
   * The code is defining a member function called `begin()` for the
   * `RobinIterableWrapper` struct. This function is used to return an iterator
   * pointing to the first element in the round-robin cycle.
   *
   * @return RobinIterator<T>
   */
  auto begin() const -> RobinIterator<T> {
    return RobinIterator<T>{node->next};
  }

  /**
   * @brief
   *
   * The code is defining a member function called `end()` for the
   * `RobinIterableWrapper` struct. This function is used to return an iterator
   * pointing to the end of the round-robin cycle. In this case, it returns a
   * `RobinIterator` object initialized with the `node` member of the
   * `RobinIterableWrapper` object. This iterator represents the end of the
   * cycle and is used to determine when the iteration is complete.
   *
   * @return RobinIterator<T>
   */
  auto end() const -> RobinIterator<T> { return RobinIterator<T>{node}; }
  // auto size() const -> size_t { return rr->cycle.size() - 1; }
};
} // namespace detail

/**
 * @brief Round Robin
 *
 * The `Robin` class is implementing a round-robin algorithm. It is used to
 * cycle through a sequence of elements in a circular manner. The constructor
 * initializes the cycle with a specified number of parts, and each part is
 * assigned a unique key. The `exclude` method returns an iterable wrapper that
 * excludes a specified part from the cycle.
 *
 * @tparam T
 */
template <typename T> struct Robin {
  std::vector<detail::RobinSlNode<T>> cycle;

  /**
   * @brief Construct a new Robin object
   *
   * The code is defining a constructor for the `Robin` class. The constructor
   * takes a parameter `num_parts` of type `T`, which represents the number of
   * parts in the round-robin cycle.
   *
   * @param num_parts
   */
  explicit Robin(T num_parts) : cycle(num_parts) {
    auto *slptr = &this->cycle[num_parts - 1];
    auto k = T(0);
    for (auto &sl : this->cycle) {
      sl.key = k;
      slptr->next = &sl;
      slptr = slptr->next;
      ++k;
    }
  }

  /**
   * @brief exclude
   *
   * The `exclude` method in the `Robin` class returns an iterable wrapper that
   * excludes a specified part from the cycle.
   *
   * @param from_part
   * @return detail::RobinIterableWrapper<T>
   */
  auto exclude(T from_part) const -> detail::RobinIterableWrapper<T> {
    return detail::RobinIterableWrapper<T>{&this->cycle[from_part]};
  }
};

} // namespace fun
