#ifndef COUT_REDIRECTOR_H
#define COUT_REDIRECTOR_H

#include <iostream>
#include <sstream>
#include <streambuf>
#include <vector>
#include <algorithm>
#include <string>

class CoutRedirector {
public:
  CoutRedirector() {
    original_buffer = std::cout.rdbuf(string_buffer.rdbuf());
  }

  std::vector<std::string> get_content() {
    std::vector<std::string> lines;
    std::string str = string_buffer.str();

    for(int i = 0; i < str.size(); i++) {
      std::string current_str;
      
      for(; i < str.size() && str[i] != '\n'; i++) {
        current_str.push_back(str[i]);
      }

      if(!current_str.empty() && current_str != "Digite o comando que voce deseja executar: ") lines.push_back(current_str);
    }

    return lines;
  }

  ~CoutRedirector() {
    std::cout.rdbuf(original_buffer);
  }

private:
  std::stringstream string_buffer;
  std::streambuf* original_buffer; 
};

#endif

