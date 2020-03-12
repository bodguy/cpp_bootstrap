#include <catch.hpp>
#include <string>

TEST_CASE("test for test") {
    SECTION("string test") {
      REQUIRE(std::string("Hello") == "Hello");
    }

    SECTION("one plus one is two") {
      REQUIRE(1 + 1 == 2);
    }
}
