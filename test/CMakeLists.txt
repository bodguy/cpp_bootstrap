add_library(CatchMain STATIC test_main.cpp)
target_link_libraries(CatchMain PUBLIC ${CONAN_LIBS})

add_executable(MyTest)
target_sources(MyTest
  PRIVATE
  simple_test.cpp
)
target_link_libraries(MyTest PRIVATE CatchMain project_warnings project_options)