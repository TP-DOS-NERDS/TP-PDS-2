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
    std::string line;

    while (std::getline(string_buffer, line)) {
        line.erase(line.begin(), std::find_if_not(line.begin(), line.end(), ::isspace));
        line.erase(std::find_if_not(line.rbegin(), line.rend(), ::isspace).base(), line.end());

        if (!line.empty()) {
            lines.push_back(line);
        }
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

