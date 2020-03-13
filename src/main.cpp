#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "file_reader.h"
#include "wav_file_data.h"
#include "stub.h"
#include "lua_include.h"

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  int window_width = 500;
  int window_height = 500;

  GLFWwindow* window = glfwCreateWindow(window_width, window_height, "OpenGL Bootstrap", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize glew" << std::endl;
    return -1;
  }
  glEnable(GL_DEPTH_TEST);

  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  std::string script_path = "../../script/eight-queen.lua";
  luaL_dofile(L, script_path.c_str());

  unsigned int cubeVAO, cubeVBO;
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &cubeVBO);
  glBindVertexArray(cubeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), &cube_vertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  unsigned int shaderProgram = read_shader("../../shader/vs.glsl", "../../shader/fs.glsl");
  if (shaderProgram == 0) {
    std::cout << "Failed to read shader file" << std::endl;
    return -1;
  }

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 3.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  std::string buffer_str;
  if (!read_file("../../resource/dragonquest.wav", buffer_str)) {
    std::cout << "Failed to read wav file" << std::endl;
    return -1;
  }
  wav_file_data wav_data{};
  std::vector<uint8_t> raw_data;
  raw_data.reserve(buffer_str.length());
  std::copy(buffer_str.begin(), buffer_str.end(), std::back_inserter(raw_data));
  if (!read_wav(raw_data, &wav_data)) {
    std::cout << "Failed to parse wav file" << std::endl;
    return -1;
  }

  ALCdevice* device = alcOpenDevice(NULL);
  ALboolean enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
  if (enumeration == AL_FALSE) {
    std::cout << "Enumeration extension not support!" << std::endl;
    return -1;
  }
  list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

  ALCcontext* context = alcCreateContext(device, NULL);
  if (!alcMakeContextCurrent(context)) {
    std::cout << "Create AL context failed" << std::endl;
    return -1;
  }

  ALfloat listenerOri[] = { 0.f, 0.f, 1.f, 0.f, 1.f , 0.f };
  alListener3f(AL_POSITION, 0, 0, 1.f);
  alListener3f(AL_VELOCITY, 0, 0, 0);
  alListenerfv(AL_ORIENTATION, listenerOri);

  ALuint source;
  alGenSources((ALuint)1, &source);
  alSourcef(source, AL_PITCH, 1);
  alSourcef(source, AL_GAIN, 1);
  alSource3f(source, AL_POSITION, 0, 0, 0);
  alSource3f(source, AL_VELOCITY, 0, 0, 0);
  alSourcei(source, AL_LOOPING, AL_FALSE);

  ALuint buffer;
  alGenBuffers((ALuint)1, &buffer);
  alBufferData(buffer, wav_data.format, wav_data.buffer_data, wav_data.size, wav_data.sample_rate);
  alSourcei(source, AL_BUFFER, buffer);
  alSourcePlay(source);

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model = glm::rotate(model, deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glUseProgram(NULL);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffer);
  device = alcGetContextsDevice(context);
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);

  glDeleteProgram(shaderProgram);
  glDeleteVertexArrays(1, &cubeVAO);
  glDeleteBuffers(1, &cubeVBO);
  glfwTerminate();

  return 0;
}
