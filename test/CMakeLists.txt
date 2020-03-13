add_executable(unittest)
target_sources(unittest
    PRIVATE
    test_main.cpp
    simple_test.cpp
)
target_link_libraries(unittest INTERFACE ${CONAN_LIBS})