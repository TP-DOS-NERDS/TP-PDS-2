#ifndef COUT_REDIRECTOR_H
#define COUT_REDIRECTOR_H

#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>

class CoutRedirector {
public:
  CoutRedirector() {
    original_buffer = std::cout.rdbuf(string_buffer.rdbuf());
  }

  std::string get_content() const {
    return string_buffer.str(); 
  }

  ~CoutRedirector() {
    std::cout.rdbuf(original_buffer);
  }

private:
  std::stringstream string_buffer;
  std::streambuf* original_buffer; 
};

#endif

