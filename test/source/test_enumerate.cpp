#include <doctest/doctest.h> // for ResultBuilder, CHECK, TestCase, TEST...

#include <py2cpp/enumerate.hpp> // for enumerate, iterable_wrapper
#include <py2cpp/range.hpp>     // for range, iterable_wrapper
#include <utility>              // for pair

TEST_CASE("Test enumerate") {
  auto R = py::range(10);
  auto count = 0;
  for (const auto &p : py::enumerate(R)) {
    static_assert(sizeof p.first >= 0, "make comipler happy");
    CHECK(p.first == count);
    ++count;
  }
  CHECK(count == R.size());
}
