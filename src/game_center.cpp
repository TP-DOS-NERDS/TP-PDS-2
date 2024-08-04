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
    execute_command();
  }
}

void GameCenter::execute_command() {
  std::string command = IOHandler::get<std::string>();

  if(command == Commands::REGISTER_PLAYER) {
    register_player();
  }
  else if(command == Commands::UNREGISTER_PLAYER) {
    unregister_player();
  }
  else if(command == Commands::LIST_PLAYERS) {
    list_players();
  }
  
  else if(command == Commands::EXECUTE_MATCH) {
    execute_match();
  }
  else if(command == Commands::KILL_SYSTEM) {
    continue_game_center_execution = false;
  }
}

void GameCenter::register_player() {
  std::string username = IOHandler::get<std::string>();
  std::string name = IOHandler::get<std::string>();
 
  if(players.has(username)) {
    throw new forbidden_action_exception(ErrorMessage::player_id_already_taken);
  }

  Player player = Player(username, name);

  players.add(player);

  std::string output = "Jogador " + username + " cadastrado com sucesso";
  IOHandler::print<std::string>(output);
}

void GameCenter::unregister_player() {
  std::string username = IOHandler::get<std::string>();

  if(!players.has(username)) {
    throw new forbidden_action_exception(ErrorMessage::player_not_found);
  }

  players.remove(username);
  std::string output = "Jogador " + username + " removido com sucesso";
  IOHandler::print<std::string>(output);
}

void GameCenter::list_players() {
  bool sort_by_username = IOHandler::get<std::string>() == "A";

  std::vector<const Player*> players_array = players.get_players();

  if(!sort_by_username) {
    sort(players_array.begin(), players_array.end(), [](const Player* a, const Player* b) {
      return a->get_name() < b->get_name();
    });
  }

  IOHandler::print<std::vector<const Player*>>(players_array);
}

void GameCenter::execute_match() {
}




