#include "file_reader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>

bool read_file(const std::string& filename, std::string& text) {
  std::ifstream file(filename, std::ios::in);
  if (!file.is_open())
    return false;
  file.unsetf(std::ios::skipws);

  file.seekg(0, std::ios::end);
  std::streampos file_size = file.tellg();
  file.seekg(0, std::ios::beg);

  text.reserve(file_size);
  std::copy(std::istream_iterator<uint8_t>(file), std::istream_iterator<uint8_t>(), std::back_inserter(text));
  file.close();

  return true;
}

unsigned int read_shader(const std::string& vs, const std::string& fs) {
  std::string vertexSource, fragmentSource;
  if (!read_file(vs, vertexSource))
    return 0;
  if (!read_file(fs, fragmentSource))
    return 0;

  // vertex shader
  unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  const char* vertexShaderSource = vertexSource.c_str();
  glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShaderID);

  int success;
  char infoLog[512];
  // check for shader compile errors
  glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
    std::cout << "shader compile error in " << vs << std::endl << infoLog << std::endl;
    return 0;
  }

  // fragment shader
  unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  const char* fragmentShaderSource = fragmentSource.c_str();
  glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShaderID);
  // check for shader compile errors
  glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
    std::cout << "shader compilation error in " << fs << std::endl << infoLog << std::endl;
    return 0;
  }

  // link program
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShaderID);
  glAttachShader(shaderProgram, fragmentShaderID);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "program linking error with " << vs << "and " << fs << std::endl << infoLog << std::endl;
    return 0;
  }
  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  return shaderProgram;
}
