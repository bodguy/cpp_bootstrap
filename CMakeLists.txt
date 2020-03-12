cmake_minimum_required(VERSION 3.8)

project(MyProject)

set(CMAKE_CXX_STANDARD 14)

include(CTest)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(test)

if(APPLE)
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
elseif(LINUX)
    find_library(OPENGL_LIBRARY GL REQUIRED)
elseif(WIN32)
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
else()
    message(STATUS ">>> failed to find libary opengl")
endif()

add_executable(
    cmake-good 
    src/main.cpp
    )
target_link_libraries(cmake-good PRIVATE ${CONAN_LIBS} ${OPENGL_LIBRARY})