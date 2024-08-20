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

void GameCenter::execute_command() {
  IOHandler::print("Digite o comando que voce deseja executar: ");
  std::string command = IOHandler::get<std::string>();

  if(command == Commands::REGISTER_PLAYER) {
    try {
      register_player();
    }
    catch(forbidden_action_exception& exception) {
      if(exception.error_message == ErrorMessage::player_id_already_taken) {
        IOHandler::print("Erro: Apelido repetido");
      }
    }
  }
  else if(command == Commands::UNREGISTER_PLAYER) {
    try {
      unregister_player();
    }
    catch(forbidden_action_exception& exception) {
      if(exception.error_message == ErrorMessage::player_not_found) {
        IOHandler::print("Erro: Jogador inexistente");
      }
    }
  }
  else if(command == Commands::LIST_PLAYERS) {
    try {
      list_players();
    }
    catch(forbidden_action_exception& exception) {
      if(exception.error_message == ErrorMessage::invalid_player_sorting_criterion) {
        IOHandler::print("Erro: Criterio de ordenacao de jogadores invalido");
      }
    }
  }

  else if(command == Commands::EXECUTE_MATCH) {
    try {
      execute_match();
    }
    catch(forbidden_action_exception& exception) {
      if(exception.error_message == ErrorMessage::game_not_found) {
        IOHandler::print("Erro: Jogo inexistente");
      }
      if(exception.error_message == ErrorMessage::player_not_found) {
        IOHandler::print("Erro: Jogador inexistente");
      }
    }
  }
  else if(command == Commands::KILL_SYSTEM) {
    continue_game_center_execution = false;
  }

  else throw forbidden_action_exception(ErrorMessage::command_not_found);

  IOHandler::print("\n");
}

void GameCenter::register_player() {
  std::string username = IOHandler::get<std::string>();
  std::string name = IOHandler::get<std::string>();
 
  if(players.has(username)) {
    throw forbidden_action_exception(ErrorMessage::player_id_already_taken);
  }

  Player player = Player(username, name);

  players.add(player);

  std::string output = "Jogador " + username + " cadastrado com sucesso";
  IOHandler::print<std::string>(output);
}

void GameCenter::unregister_player() {
  std::string username = IOHandler::get<std::string>();

  if(!players.has(username)) {
    throw forbidden_action_exception(ErrorMessage::player_not_found);
  }

  players.remove(username);
  std::string output = "Jogador " + username + " removido com sucesso";
  IOHandler::print<std::string>(output);
}

void GameCenter::list_players() {
  std::string sorting_criterio = IOHandler::get<std::string>();

  if(sorting_criterio != "A" && sorting_criterio != "N") {
    throw forbidden_action_exception(ErrorMessage::invalid_player_sorting_criterion);
  }

  bool sort_by_username = sorting_criterio == "A";


  std::vector<const Player*> players_array = players.get_players();

  if(!sort_by_username) {
    sort(players_array.begin(), players_array.end(), [](const Player* a, const Player* b) {
      return a->get_name() < b->get_name();
    });
  }

  IOHandler::print<std::vector<consta   
  IOHandler::print_players<std::vector<const Player*>>>(players_array);
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
