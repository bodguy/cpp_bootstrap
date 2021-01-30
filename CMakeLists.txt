cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(MyProject LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CONAN_DISABLE_CHECK_COMPILER ON)

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

# Static Analyzer settings (cppcheck, clang-tidy, iwyu)
include(cmake/StaticAnalyzers.cmake)

find_program(CCACHE ccache)
if(CCACHE)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
else()
    message(STATUS "ccache not found cannot use")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
    find_package(OpenGL REQUIRED)
else()
    message(SEND_ERROR "failed to find libary OpenGL")
endif()

add_executable(bootstrap)
target_sources(bootstrap
    PRIVATE
    src/root_dir.h
    src/stub.h
    src/reader/file_reader.h
    src/wav/wav_file_data.h
    src/lua_include.h
    src/parser/directive_parser.h
    src/heap/heap_alloc.h
    src/main.cpp
    src/reader/file_reader.cpp
    src/wav/wav_file_data.cpp
    src/parser/directive_parser.cpp
    src/heap/heap_alloc.cpp
    )
target_link_libraries(bootstrap
    PRIVATE
    ${CONAN_LIBS}
    ${OPENGL_LIBRARY}
    project_options
    project_warnings
    )
target_include_directories(bootstrap PRIVATE "src")
set(RESOURCE_DIR "resource")
set(SHADER_DIR "shader")
set(SCRIPT_DIR "script")
configure_file("${CMAKE_SOURCE_DIR}/cmake/root_dir.h.in" "${CMAKE_SOURCE_DIR}/src/root_dir.h")

if(APPLE)
    target_link_libraries(bootstrap PRIVATE ${COCOA_LIBS} ${IOKIT_LIBS} ${CORE_LIBS})
endif()

if(MSVC_IDE)
    # Macro to preserve source files hierarchy in the IDE
    macro(GroupSources curdir)
        file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

        foreach(child ${children})
            if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
                GroupSources(${curdir}/${child})
            else()
                string(REPLACE "/" "\\" groupname ${curdir})
                string(REPLACE "src" "src" groupname ${groupname})
                source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            endif()
        endforeach()
    endmacro()

    # Run macro
    GroupSources(src)
endif()
