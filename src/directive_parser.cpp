#include "directive_parser.h"
#include <vector>

bool is_end_of_line(const std::string::const_iterator& iter) {
  return *iter != '\n' && *iter != '\r' && *iter != 0;
}

bool is_white_space(const std::string::const_iterator& iter) {
  return *iter == ' ' || *iter == '\t';
}

void find_directive(const std::string& str) {
  static std::string keyword = "include";
  std::vector<Directive*> list;
  std::string::const_iterator iterator = str.begin();
  while(iterator != str.end()) {
    while (is_white_space(iterator)) iterator++;
    if (*iterator == '#') {
      iterator++;
      if (strncmp(&*iterator, keyword.c_str(), keyword.size()) == 0) {
        iterator += 7;
        while(is_white_space(iterator)) iterator++;
        if (*iterator == '"') {
          iterator++;
          // find end of quot
          auto end_of_quot = iterator;
          while(*end_of_quot != '"' && is_end_of_line(end_of_quot))
            end_of_quot++;
          if (*end_of_quot == '"') {
            list.emplace_back(new Directive(std::string(iterator, end_of_quot)));
            iterator = end_of_quot;
            while(is_end_of_line(iterator)) iterator++;
          }
        }
      }
    }
    while(is_end_of_line(iterator)) iterator++;
    if (*iterator == '\r' || *iterator == '\n') {
      iterator = iterator + (iterator[0] + iterator[1] == '\r' + '\n' ? 2 : 1);
    }
  }

// intentional comment out
//  for (auto i : list) {
//    printf("%s\n", i->GetFilename().c_str());
//    delete i;
//  }
}