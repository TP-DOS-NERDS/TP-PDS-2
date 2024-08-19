#include "doctest.h"
#include <iostream>
#include <string>
#include "../include/IOHandler.h"
#include "CinRedirector.h"


TEST_SUITE("IOHandler") {
  TEST_CASE("get string") {
    CinRedirector redirector("naruto\n");

    std::string string = IOHandler::get<std::string>();

    CHECK(string == "naruto");
  }  
}
