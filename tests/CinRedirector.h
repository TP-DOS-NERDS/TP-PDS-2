#ifndef CIN_REDIRECTOR_H
#define CIN_REDIRECTOR_H

#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>

class CinRedirector {
public:
  CinRedirector(std::string string) : string_buffer(string) {
    std::streambuf* new_buffer = string_buffer.rdbuf();
    original_buffer = std::cin.rdbuf(new_buffer);
  }

  ~CinRedirector() {
    std::cin.rdbuf(original_buffer);
  }

private:
  std::stringstream string_buffer;
  std::streambuf* original_buffer; 
};

#endif
