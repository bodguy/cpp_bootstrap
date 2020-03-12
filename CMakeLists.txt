cmake_minimum_required(VERSION 3.8)

project(MyProject)

set(CMAKE_CXX_STANDARD 14)

include(CTest)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(test)

if(APPLE)
    message(STATUS ">>> MACOS")
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
elseif(UNIX AND NOT APPLE) # LINUX
    message(STATUS ">>> LINUX")
    find_library(OPENGL_LIBRARY GL REQUIRED)
elseif(WIN32)
    message(STATUS ">>> WIN32")
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
else()
    message(FATAL ">>> failed to find libary opengl")
endif()

add_executable(
    cmake-good 
    src/main.cpp
    )
target_link_libraries(cmake-good PRIVATE ${CONAN_LIBS} ${OPENGL_LIBRARY})