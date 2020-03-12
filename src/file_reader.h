#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>

bool read_file(const std::string& path, std::string& out);
unsigned int read_shader(const std::string& vs, const std::string& fs);

#endif