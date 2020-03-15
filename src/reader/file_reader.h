#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>

bool read_file(const std::string& filename, std::string& text);
unsigned int read_shader(const std::string& vs, const std::string& fs);

#endif