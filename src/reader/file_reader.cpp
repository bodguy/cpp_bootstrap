#include "file_reader.h"
#include <GL/glew.h>
#include <iostream>

bool read_file(const std::string& filename, std::string& text) {
  FILE* fp = NULL;
  fp = fopen(filename.c_str(), "r");
  if (!fp) return false;
  fseek(fp, 0, SEEK_END);
  size_t size = static_cast<size_t>(ftell(fp));
  fseek(fp, 0, SEEK_SET);
  char* buffer = (char*)malloc(sizeof(char) * size);
  if (!buffer) return false;
  fread(buffer, size, 1, fp);
  text.assign(buffer, size);
  free(buffer);
  fclose(fp);
  return true;

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
