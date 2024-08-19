#include "../include/game_center.h"
#include "../include/forbidden_action_exception.h"
#include "CinRedirector.h"
#include "CoutRedirector.h"
#include "doctest.h"


TEST_SUITE("game center tests") {
  GameCenter game_center = GameCenter();

  TEST_CASE("run command") {
    SUBCASE("invalid command") {
      CinRedirector cin_redirector("listar\nFS\n"); 
      CoutRedirector* cout_redirector = new CoutRedirector();

      game_center.start_game_center();

      std::string output = cout_redirector->get_content();

      CHECK(output == "Digite o comando que voce deseja executar:\nErro: Comando inexistente\n")
    }
  }
}
