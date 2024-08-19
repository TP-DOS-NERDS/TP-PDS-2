#include "doctest.h"
#include <iostream>
#include <iterator>
#include <sstream>
#include <streambuf>
#include "../include/IOHandler.h"

class CinRedirector {
  public:
    CinRedirector(std::string string)  {
      std::stringstream string_buffer(string); 
      std::streambuf* new_buffer = string_buffer.rdbuf();

      original_buf = std::cin.rdbuf(new_buffer);
    }

  ~CinRedirector() {
      delete (std::cin.rdbuf(original_buf));
  }

private:
  std::streambuf* original_buf;
};


TEST_SUITE("IOHandler") {
  TEST_CASE("get string") {
    CinRedirector redirector("123456\n");

    std::string string = IOHandler::get<std::string>();

    CHECK(string == "123456");
  }  
}
