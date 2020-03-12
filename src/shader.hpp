#include <GL/glew.h>
#include <string>

bool loadFile(const std::string& filepath, std::string& out_source);
unsigned int loadShaderFromFile(const std::string& vs_name, const std::string& fs_name);