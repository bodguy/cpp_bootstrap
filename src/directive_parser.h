#ifndef DIRECTIVE_PARSER_H
#define DIRECTIVE_PARSER_H

#include <iostream>
#include <string>
#include "heap_alloc.h"

class Directive : public heap_alloc {
public:
  Directive(const std::string& name) : filename(name) {}
  std::string GetFilename() const { return filename; }

private:
  std::string filename;
};

bool is_end_of_line(const std::string::const_iterator& iter);
bool is_white_space(const std::string::const_iterator& iter);
void find_directive(const std::string& str);

#endif
