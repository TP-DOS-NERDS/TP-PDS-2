#include "../include/games/lig4.h"
#include "CinRedirector.h"
#include "CoutRedirector.h"
#include "doctest.h"


TEST_SUITE("lig4 tests") {

  TEST_CASE("Base game running") {
    SUBCASE("Player 1 wins") {
      CinRedirector cin_redirector("1\n2\n1\n2\n1\n2\n1\n"); 
      CoutRedirector* cout_redirector = new CoutRedirector();

      Lig4 lig;
      lig.play();

      CHECK(lig.get_winner() == 1);

      delete cout_redirector;
    }
    SUBCASE("Player 2 wins") {
      CinRedirector cin_redirector("1\n2\n1\n2\n1\n2\n3\n2\n"); 
      CoutRedirector* cout_redirector = new CoutRedirector();

      Lig4 lig;
      lig.play();

      CHECK(lig.get_winner() == 2);

      delete cout_redirector;
    }
  }
  TEST_CASE("Invalid input") {
    SUBCASE("Non digit") {
      CinRedirector cin_redirector("c\n1\n2\n1\n2\n1\n2\n1\n"); 
      CoutRedirector* cout_redirector = new CoutRedirector();

      Lig4 lig;
      lig.play();

      std::string output = cout_redirector->get_content();
      CHECK(output.find("Input invalido: Insira novamente a coluna na qual voce deseja jogar"));
      CHECK(lig.get_winner() == 1);

      delete cout_redirector;
    }
    SUBCASE("Invalid Collumn") {
      CinRedirector cin_redirector("9\n1\n2\n1\n2\n1\n2\n1\n"); 
      CoutRedirector* cout_redirector = new CoutRedirector();

      Lig4 lig;
      lig.play();

      std::string output = cout_redirector->get_content();
      CHECK(output.find("Coluna invalida: Insira novamente a coluna na qual voce deseja jogar"));
      CHECK(lig.get_winner() == 1);

      delete cout_redirector;
    }

  }
  TEST_CASE("Tied Game") {
    SUBCASE("") {
      CinRedirector cin_redirector("1\n1\n1\n1\n1\n1\n2\n2\n2\n2\n2\n2\n3\n3\n3\n3\n3\n3\n4\n4\n4\n4\n4\n4\n1\n1\n1\n1\n1\n1\n2\n2\n2\n2\n2\n2\n3\n3\n3\n3\n3\n3\n4\n4\n4\n4\n4\n4\n");
      CoutRedirector* cout_redirector = new CoutRedirector();

      Lig4 lig;
      lig.play();

      std::string output = cout_redirector->get_content();
      CHECK(output.find("Input invalido: Insira novamente a coluna na qual voce deseja jogar"));
      CHECK(lig.get_winner() == 1);

      delete cout_redirector;
    }
  }
}
