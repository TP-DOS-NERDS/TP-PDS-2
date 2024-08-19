#include "../include/games/lig4.h"
#include "CinRedirector.h"
#include "CoutRedirector.h"
#include "doctest.h"

TEST_SUITE("reversi tests") {

  TEST_CASE("Base game running") {
    SUBCASE("Player 1 wins") {
      CinRedirector cin_redirector("1\n2\n1\n2\n1\n2\n1\n"); 
      CoutRedirector cout_redirector;

      Lig4 lig;
      lig.play();

      CHECK(lig.get_winner() == 1);
    }
  }
}
