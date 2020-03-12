cmake_minimum_required(VERSION 3.8)

project(MyProject)

set(CMAKE_CXX_STANDARD 14)

include(CTest)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(test)

add_executable(
    cmake-good 
    src/main.cpp
    )
target_link_libraries(cmake-good PRIVATE ${CONAN_LIBS})