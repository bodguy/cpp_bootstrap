#ifndef STUB_H
#define STUB_H

#include "root_dir.h"
#include <string>

// clang-format off
float cube_vertices[] = {
  -0.5f, -0.5f, -0.5f,
  0.5f,  -0.5f, -0.5f,
  0.5f,  0.5f,  -0.5f,
  0.5f,  0.5f,  -0.5f,
  -0.5f, 0.5f,  -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f, 0.5f,
  0.5f,  -0.5f, 0.5f,
  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  -0.5f, 0.5f,  0.5f,
  -0.5f, -0.5f, 0.5f,
  -0.5f, 0.5f,  0.5f,
  -0.5f, 0.5f,  -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f, 0.5f,
  -0.5f, 0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f,  -0.5f,
  0.5f,  -0.5f, -0.5f,
  0.5f,  -0.5f, -0.5f,
  0.5f,  -0.5f, 0.5f,
  0.5f,  0.5f,  0.5f,
  -0.5f, -0.5f, -0.5f,
  0.5f,  -0.5f, -0.5f,
  0.5f,  -0.5f, 0.5f,
  0.5f,  -0.5f, 0.5f,
  -0.5f, -0.5f, 0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, 0.5f,  -0.5f,
  0.5f,  0.5f,  -0.5f,
  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  -0.5f, 0.5f,  0.5f,
  -0.5f, 0.5f,  -0.5f
};
// clang-format on

std::string get_resource_dir() { return std::string(RESOURCE_DIR); }
std::string get_shader_dir() { return std::string(SHADER_DIR); }
std::string get_script_dir() { return std::string(SCRIPT_DIR); }

#endif