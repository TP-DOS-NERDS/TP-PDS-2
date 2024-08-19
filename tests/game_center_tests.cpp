#include "../include/game_center.h"
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

  TEST_CASE("unregister player") {
    SUBCASE("unregister one player") {
      GameCenter game_center;
      CinRedirector cin_redirector("CJ er3n eren\nRJ er3n\nFS\n"); 
      CoutRedirector cout_redirector;

      game_center.start_game_center();

      std::vector<std::string> output = cout_redirector.get_content();
      std::vector<std::string> expected_output = { "Jogador er3n cadastrado com sucesso", "Jogador er3n removido com sucesso"};

      CHECK(output == expected_output);
    }

    SUBCASE("unregister a player that does not exist") {
      GameCenter game_center;
      CinRedirector cin_redirector("CJ er3n eren\nRJ er3n\nFS\n"); 
      CoutRedirector cout_redirector;

      game_center.start_game_center();

      std::vector<std::string> output = cout_redirector.get_content();
      std::vector<std::string> expected_output = { "Jogador er3n cadastrado com sucesso", "Jogador er3n removido com sucesso"};

      CHECK(output == expected_output);
    }
  }

  TEST_CASE("play a game") {
    SUBCASE("playing a inexistent game") {
      GameCenter game_center;
      CinRedirector cin_redirector("EP lig5 luffy ace\nFS\n"); 
      CoutRedirector cout_redirector;

      game_center.start_game_center();

      std::vector<std::string> output = cout_redirector.get_content();
      std::vector<std::string> expected_output = { "Erro: Jogo inexistente" };

      CHECK(output == expected_output);
    }

    SUBCASE("playing a game with a inexistent player") {
      GameCenter game_center;
      CinRedirector cin_redirector("EP lig4 luffy ace\nFS\n"); 
      CoutRedirector cout_redirector;

      game_center.start_game_center();

      std::vector<std::string> output = cout_redirector.get_content();
      std::vector<std::string> expected_output = { "Erro: Jogador inexistente" };

      CHECK(output == expected_output);
    }
  }

  TEST_CASE("list players") {
    SUBCASE("list two players sorted by username") {
      GameCenter game_center;
      CinRedirector cin_redirector("CJ er3n eren\nCJ mik4sa mikasa\nLJ A\nFS\n"); 
      CoutRedirector cout_redirector;

      game_center.start_game_center();

      std::vector<std::string> output = cout_redirector.get_content();
      
      std::vector<std::string> expected_output = {"Jogador er3n cadastrado com sucesso", "Jogador mik4sa cadastrado com sucesso", "er3n eren", "lig4: - V: 0 D: 0", "reversi: - V: 0 D: 0", "mik4sa mikasa", "lig4: - V: 0 D: 0", "reversi: - V: 0 D: 0" };

      CHECK(output == expected_output);
    }

    SUBCASE("list two players sorted by name") {
      GameCenter game_center;
      CinRedirector cin_redirector("CJ er3n eren\nCJ mik4sa ackerman\nLJ N\nFS\n"); 
      CoutRedirector cout_redirector;

      game_center.start_game_center();

      std::vector<std::string> output = cout_redirector.get_content();
      
      std::vector<std::string> expected_output = {"Jogador er3n cadastrado com sucesso", "Jogador mik4sa cadastrado com sucesso", "mik4sa ackerman", "lig4: - V: 0 D: 0", "reversi: - V: 0 D: 0", "er3n eren", "lig4: - V: 0 D: 0", "reversi: - V: 0 D: 0" };

      CHECK(output == expected_output);
    }

    SUBCASE("listing player using a invalid sorting criterio") {
      GameCenter game_center;
      CinRedirector cin_redirector("LJ K\nFS\n"); 
      CoutRedirector cout_redirector;

      game_center.start_game_center();

      std::vector<std::string> output = cout_redirector.get_content();
      
      std::vector<std::string> expected_output = { "Erro: Criterio de ordenacao de jogadores invalido" };

      CHECK(output == expected_output);
    }

    SUBCASE("list zero players") {
      GameCenter game_center;
      CinRedirector cin_redirector("LJ A\nFS\n"); 
      CoutRedirector cout_redirector;

      game_center.start_game_center();

      std::vector<std::string> output = cout_redirector.get_content();
      
      std::vector<std::string> expected_output = {  };

      CHECK(output == expected_output);
    }
  }

}
