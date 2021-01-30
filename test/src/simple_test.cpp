#include <catch.hpp>
#include <string>
#include "../../src/heap/heap_alloc.h"

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

class Foo : public heap_alloc {
public:
  Foo() { std::cout << "con\n"; }
  ~Foo() { std::cout << "des\n"; }
  int get_int() const { return a; }

private:
  int a{19};
};

class Bar {
public:
  Bar() { std::cout << "con\n"; }
  ~Bar() { std::cout << "des\n"; }
  int get_int() const { return a; }

private:
  int a{11};
};

TEST_CASE("malloc test suite") {
  SECTION("malloc") {
    auto* f = new Foo{};
    std::cout << f->get_int() << std::endl;
    auto *b = new Bar{};
    std::cout << b->get_int() << std::endl;
    dumpmem();
  }
}