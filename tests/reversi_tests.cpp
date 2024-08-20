#include "../include/games/reversi.h"
#include "CinRedirector.h"
#include "CoutRedirector.h"
#include "doctest.h"

TEST_SUITE("reversi tests") {
  TEST_CASE("Base game running") {
    SUBCASE("Player 2 wins") {
      CinRedirector cin_redirector("5 6\n6 4\n5 3\n4 6\n3 5\n6 6\n5 7\n6 5\n7 5\n"); 
      CoutRedirector cout_redirector;

      Reversi reversi;
      reversi.play();

      CHECK(reversi.get_winner() == 2);
    }
  }
  TEST_CASE("Invalid input") {
    SUBCASE("Invalid Row/Column") {
      CinRedirector cin_redirector("20 20\n 5 6\n6 4\n5 3\n4 6\n3 5\n6 6\n5 7\n6 5\n7 5\n"); 
      CoutRedirector cout_redirector;

      Reversi reversi;
      reversi.play();

      std::vector<std::string> output = cout_redirector.get_content();
        
      bool exists = false;
      for (auto out : output) {
        if (out ==  "Input invalido: Insira novamente a linha e a coluna na qual voce deseja jogar") {
          exists = true;
          break;
        }
      }

      CHECK(exists);
      CHECK(reversi.get_winner() == 2);
    }
  }
}
