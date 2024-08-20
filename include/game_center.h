#ifndef GAME_CENTER_H
#define GAME_CENTER_H

#include "player_repository.h"
#include "player.h"
#include "IOHandler.h"
#include "forbidden_action_exception.h"
#include "game.h"
#include "./games/lig4.h"
#include "./games/reversi.h"
#include "./games/snake.h"
#include <algorithm>

class Commands {
  public:
    static const std::string REGISTER_PLAYER;
    static const std::string UNREGISTER_PLAYER;
    static const std::string LIST_PLAYERS;
    static const std::string EXECUTE_MATCH;
    static const std::string KILL_SYSTEM;
  };


class GameCenter {
public:
  GameCenter();
  void start_game_center();
  void execute_match();

private:
  PlayersRepository players;  
  bool continue_game_center_execution;
  
  void execute_command();
  void register_player();
  void unregister_player();
  void list_players();


  void execute_multiplayer_match(GameId game_id, Player* player1, Player* player2);
  void execute_single_player_match(GameId game_id, Player* player); 
};

#endif

