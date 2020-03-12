cmake_minimum_required(VERSION 3.8)

project(MyProject)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(cmake-good main.cpp)
target_link_libraries(cmake-good PRIVATE ${CONAN_LIBS})
