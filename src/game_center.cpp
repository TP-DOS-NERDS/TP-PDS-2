#include "../include/game_center.h"

const std::string Commands::REGISTER_PLAYER = "CJ";
const std::string Commands::UNREGISTER_PLAYER = "RJ";
const std::string Commands::LIST_PLAYERS = "LJ";
const std::string Commands::EXECUTE_MATCH = "EP";
const std::string Commands::KILL_SYSTEM = "FS";


GameCenter::GameCenter() {
  players = PlayersRepository();
  continue_game_center_execution = true;
}

void GameCenter::start_game_center() {
  while(continue_game_center_execution) {
    try {
      execute_command();
    }
    catch(forbidden_action_exception& exception) {
      if(exception.error_message == ErrorMessage::command_not_found) {
        IOHandler::print("Erro: Comando inexistente");
      }
    }
  }
}

void GameCenter::execute_match() {
  std::string game_name = IOHandler::get<std::string>();
  GameId game_id = string_to_game_id(game_name);

  bool multiplayer_game = game_id != GameId::snake;
  if(!game_exists(game_name)) {
    throw forbidden_action_exception(ErrorMessage::game_not_found);
  }
  
  if(multiplayer_game) {
    std::string player1_username = IOHandler::get<std::string>();
    std::string player2_username = IOHandler::get<std::string>();

    Player* player1 = players.get(player1_username);
    Player* player2 = players.get(player2_username);

    if(!players.has(player1_username) || !players.has(player2_username)) {
      throw forbidden_action_exception(ErrorMessage::player_not_found);
    }

    execute_multiplayer_match(game_id, player1, player2);
  }

  else {
    std::string player_username = IOHandler::get<std::string>();

    Player* player = players.get(player_username);

    if(!players.has(player_username)) {
      throw forbidden_action_exception(ErrorMessage::player_not_found);
    }

    execute_single_player_match(game_id, player);
  }
}

void GameCenter::execute_multiplayer_match(GameId game_id, Player* player1, Player* player2) {
  const int FIRST_PLAYER = 1;
  const int SECOND_PLAYER = 2;

  Game* game;
  if(game_id == GameId::lig4) {
    game = new Lig4();
    game->play();
  }

  int winner = game->get_winner();
  if(winner == FIRST_PLAYER) {
    player1->increase_wins(game_id);
    player2->increase_defeats(game_id);
  }

  else if(winner == SECOND_PLAYER) {
    player2->increase_wins(game_id);
    player1->increase_defeats(game_id);
  }
}

void GameCenter::execute_single_player_match(GameId game_id, Player* player) {
  const int FIRST_PLAYER = 1;

  Game* game;
  if(game_id == GameId::snake) {
    game = new Snake();
    game->play();
  }

  int winner = game->get_winner();
  if(winner == FIRST_PLAYER) {
    player->increase_wins(game_id);
  }
  else {
    player->increase_defeats(game_id);
  }
}
