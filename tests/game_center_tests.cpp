#include "../include/game_center.h"
#include "../include/forbidden_action_exception.h"
#include "CinRedirector.h"
#include "CoutRedirector.h"
#include "doctest.h"


TEST_SUITE("game center tests") {

  TEST_CASE("run command") {
    SUBCASE("invalid command") {
      GameCenter game_center;
      CinRedirector cin_redirector("listar\nFS\n"); 
      CoutRedirector cout_redirector;

      game_center.start_game_center();

      std::vector<std::string> output = cout_redirector.get_content();
      std::vector<std::string> expected_output = { "Erro: Comando inexistente" };

      CHECK(output == expected_output);
    }
  }

  TEST_CASE("register player") {
    SUBCASE("register one player") {
      GameCenter game_center;
      CinRedirector cin_redirector("CJ er3n eren\nFS\n"); 
      CoutRedirector cout_redirector;

      game_center.start_game_center();

      std::vector<std::string> output = cout_redirector.get_content();
      std::vector<std::string> expected_output = { "Jogador er3n cadastrado com sucesso" };


      CHECK(output == expected_output);
    }

    SUBCASE("register a player that already exists") {
      GameCenter game_center;
      CinRedirector cin_redirector("CJ er3n eren\nCJ er3n yagger\nFS\n"); 
      CoutRedirector cout_redirector;

      game_center.start_game_center();

      std::vector<std::string> output = cout_redirector.get_content();
      std::vector<std::string> expected_output = {"Jogador er3n cadastrado com sucesso", "Erro: Apelido repetido" };

      CHECK(output == expected_output);
    }
  }


}
