cmake_minimum_required(VERSION 3.8)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

#include(cmake/Conan.cmake)
#run_conan()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_14)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

enable_testing()

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
    message(SEND_ERROR "failed to find libary OpenGL")
endif()

add_executable(bootstrap)
target_sources(bootstrap
    PRIVATE
    src/main.cpp
    src/stub.h
    src/file_reader.h
    src/file_reader.cpp
    src/wav_file_data.h
    src/wav_file_data.cpp
    src/lua_include.h
    src/directive_parser.h
    src/directive_parser.cpp
)
target_link_libraries(bootstrap
    PRIVATE
    ${CONAN_LIBS}
    ${OPENGL_LIBRARY}
    project_options
    project_warnings
)

if(APPLE)
    target_link_libraries(bootstrap PRIVATE ${COCOA_LIBS} ${IOKIT_LIBS} ${CORE_LIBS})
endif()
