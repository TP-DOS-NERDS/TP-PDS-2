#ifndef GAME_CENTER_H
#define GAME_CENTER_H

#include "player_repository.h"
#include "player.h"
#include "IOHandler.h"
#include "forbidden_action_exception.h"
#include "game.h"
#include "./games/lig4.h"
#include "./games/minesweeper.h"
#include "./games/snake.h"
#include "./games/reversi.h"
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
/**
 * @brief Instancia um objeto do tipo GameCenter.
 *
 * @return Um objeto do tipo GameCenter. 
 */
  GameCenter();

/**
 * @brief Inicia o sistema.
 */
  void start_game_center();

private:
  PlayersRepository players;  
  bool continue_game_center_execution;

 /**
 * @brief Executa um comando.
 */
  void execute_command();

 /**
 * @brief Inicia uma partida.
 */ 

  void execute_match();
 /**
 * @brief Registra um jogador.
 */ 
  void register_player();

 /**
 * @brief Remove o registro de um jogador.
 */
  void unregister_player();

 /**
 * @brief Lista os jogadores registrados.
 */
  void list_players();


  void execute_multiplayer_match(GameId game_id, Player* player1, Player* player2);
  void execute_single_player_match(GameId game_id, Player* player); 
};

#endif

