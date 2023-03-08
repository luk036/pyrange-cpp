#include <doctest/doctest.h> // for ResultBuilder, CHECK, TestCase, TEST...

#include <list>
#include <pyrange/enumerate.hpp> // for enumerate, iterable_wrapper
#include <utility>               // for pair

TEST_CASE("Test enumerate") {
  std::list<int> lst{1, 3, 4, 5, 3, 5};

  auto count = 0U;
  for (auto p : py::const_enumerate(lst)) {
    CHECK_EQ(p.first, count);
    ++count;
  }
  CHECK_EQ(count, lst.size());
}
