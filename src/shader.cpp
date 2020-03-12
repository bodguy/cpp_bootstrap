#include "shader.hpp"
#include <iostream>

bool loadFile(const std::string& filepath, std::string& out_source) {
  FILE* fp = NULL;
  fp = fopen(filepath.c_str(), "r");
  if (!fp) return false;
  fseek(fp, 0, SEEK_END);
  size_t size = static_cast<size_t>(ftell(fp));
  fseek(fp, 0, SEEK_SET);
  char* buffer = (char*)malloc(sizeof(char) * size);
  if (!buffer) return false;
  fread(buffer, size, 1, fp);
  out_source.assign(buffer, size);
  free(buffer);
  fclose(fp);
  return true;
}

unsigned int loadShaderFromFile(const std::string& vs_name, const std::string& fs_name) {
  std::string vertexSource, fragmentSource;
  bool result = loadFile(vs_name, vertexSource);
  if (!result) return 0;
  result = loadFile(fs_name, fragmentSource);
  if (!result) return 0;

  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const char* vertexShaderSource = vertexSource.c_str();
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  // check for shader compile errors
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "shader compile error in " << vs_name << std::endl << infoLog << std::endl;
    return 0;
  }

  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const char* fragmentShaderSource = fragmentSource.c_str();
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "shader compile error in " << fs_name << std::endl << infoLog << std::endl;
    return 0;
  }

  // link program
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "program linking error with " << vs_name << " and " << fs_name << std::endl << infoLog << std::endl;
    return 0;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}