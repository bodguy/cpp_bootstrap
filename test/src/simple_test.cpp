#include <catch.hpp>
#include <string>

TEST_CASE("test suite1") {
    SECTION("one plus one is two") {
      REQUIRE(1 + 1 == 2);
    }
}

TEST_CASE("test suite2") {
  SECTION("Hello test") {
    REQUIRE(std::string("Hello") == "Hello");
  }
}