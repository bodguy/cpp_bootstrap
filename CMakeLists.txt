cmake_minimum_required(VERSION 3.8)

project(MyProject)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

add_subdirectory(test)

if(APPLE)
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
    find_library(COCOA_LIBS Cocoa REQUIRED)
    find_library(IOKIT_LIBS IOKit REQUIRED)
    find_library(CORE_LIBS CoreVideo REQUIRED)
elseif(UNIX AND NOT APPLE) # LINUX
    find_library(OPENGL_LIBRARY GL REQUIRED)
elseif(WIN32)
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
else()
    message(FATAL ">>> failed to find libary opengl")
endif()

add_executable(
    cmake-good 
    src/main.cpp
    src/stub.h
    src/file_reader.h
    src/file_reader.cpp
    )
target_link_libraries(cmake-good PRIVATE ${CONAN_LIBS} ${OPENGL_LIBRARY})

if(APPLE)
    target_link_libraries(cmake-good PRIVATE ${COCOA_LIBS} ${IOKIT_LIBS} ${CORE_LIBS})
endif()
