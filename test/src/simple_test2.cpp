#include <catch.hpp>
#include <vector>

TEST_CASE("vectors can be sized and resized", "[vector]") {
  // initialization block executed for each section
  std::vector<int> v(5);
  REQUIRE(v.size() == 5);
  REQUIRE(v.capacity() >= 5);
  // end of initialization block

  SECTION("resizing bigger changes size and capacity") {
    v.resize(10);

    REQUIRE(v.size() == 10);
    REQUIRE(v.capacity() >= 10);
  }
  SECTION("resizing smaller changes size but not capacity") {
    v.resize(0);

    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() >= 5);
  }
  SECTION("reserving bigger changes capacity but not size") {
    v.reserve(10);

    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() >= 10);

    // verify that attempting to reserve a smaller capacity changes nothing
    SECTION("reserving smaller again does not change capacity") {
      v.reserve(7);
      REQUIRE(v.capacity() >= 10);
    }
  }
}