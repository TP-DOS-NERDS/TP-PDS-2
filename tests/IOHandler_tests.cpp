#include "doctest.h"
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include "../include/IOHandler.h"
#include "cin_redirector.h"



TEST_SUITE("IOHandler") {
  TEST_CASE("get string") {
    std::string string = "123456\n";
    redirect_cin(string);
    std::string s = IOHandler::get<std::string>();
    std::cout << s;
  }  
}
