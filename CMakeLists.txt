cmake_minimum_required(VERSION 3.8)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(test)
add_executable(bootstrap)

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
    message(FATAL "failed to find libary OpenGL")
endif()

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(bootstrap)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

target_compile_features(bootstrap PRIVATE cxx_std_14)
target_sources(bootstrap
    PRIVATE
    src/main.cpp
    src/stub.h
    src/file_reader.h
    src/file_reader.cpp
    src/wav_file_data.h
    src/wav_file_data.cpp
    src/lua_include.h
)
target_link_libraries(bootstrap
    PRIVATE
    ${CONAN_LIBS}
    ${OPENGL_LIBRARY}
)

if(APPLE)
    target_link_libraries(bootstrap PRIVATE ${COCOA_LIBS} ${IOKIT_LIBS} ${CORE_LIBS})
endif()
