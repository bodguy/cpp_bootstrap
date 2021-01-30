find_package(Catch2 REQUIRED)
add_library(CatchMain STATIC test_main.cpp)
target_link_libraries(CatchMain PUBLIC Catch2::Catch2)

add_executable(UnitTest)
target_sources(UnitTest
    PRIVATE
    src/simple_test.cpp
    src/simple_test2.cpp
    ../../src/heap/heap_alloc.cpp
    )
target_link_libraries(UnitTest
    PRIVATE
    CatchMain
    project_warnings
    project_options
    )
include(Catch)
catch_discover_tests(UnitTest
    TEST_PREFIX
    "unittests."
    EXTRA_ARGS
    -s
    --reporter=xml
    --out=tests.xml
    )