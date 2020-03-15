add_library(CatchMain STATIC test_main.cpp)
target_link_libraries(CatchMain PUBLIC ${CONAN_LIBS})

add_executable(UnitTest)
target_sources(UnitTest
    PRIVATE
    src/simple_test.cpp
    src/simple_test2.cpp
    )
target_link_libraries(UnitTest
    PRIVATE
    CatchMain
    project_warnings
    project_options
    )
