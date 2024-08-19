#include "../include/games/lig4.h"
#include "CinRedirector.h"
#include "CoutRedirector.h"
#include "doctest.h"


TEST_SUITE("lig4 tests") {

  TEST_CASE("Base game running") {
    SUBCASE("Player 1 wins") {
      CinRedirector cin_redirector("1\n2\n1\n2\n1\n2\n1\n"); 
      CoutRedirector cout_redirector;

      Lig4 lig;
      lig.play();

      CHECK(lig.get_winner() == 1);
    }
    SUBCASE("Player 2 wins") {
      CinRedirector cin_redirector("1\n2\n1\n2\n1\n2\n3\n2\n"); 
      CoutRedirector cout_redirector;

      Lig4 lig;
      lig.play();

      CHECK(lig.get_winner() == 2);
    }
  }
  TEST_CASE("Invalid input") {
    SUBCASE("Non digit") {
      CinRedirector cin_redirector("c\n1\n2\n1\n2\n1\n2\n1\n"); 
      CoutRedirector cout_redirector;

      Lig4 lig;
      lig.play();

      std::vector<std::string> output = cout_redirector.get_content();
  
      bool exists = false;
      for (auto out : output) {
        if (out ==  "Input invalido: Insira novamente a coluna na qual voce deseja jogar") {
          exists = true;
          break;
        }
      }
      CHECK(exists);
      CHECK(lig.get_winner() == 1);
    }
    SUBCASE("Invalid Collumn") {
      CinRedirector cin_redirector("9\n1\n2\n1\n2\n1\n2\n1\n"); 
      CoutRedirector cout_redirector;

      Lig4 lig;
      lig.play();

      std::vector<std::string> output = cout_redirector.get_content();
        
      bool exists = false;
      for (auto out : output) {
        if (out ==  "Coluna invalida: Insira novamente a coluna na qual voce deseja jogar") {
          exists = true;
          break;
        }
      }

      CHECK(exists);
      CHECK(lig.get_winner() == 1);
    }
  }
}
