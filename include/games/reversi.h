#ifndef REVERSI_H
#define REVERSI_H

#include <string>
#include <vector>
#include "../game.h"
#include "../player.h"

class Reversi: public Game {
private:
  std::vector<Player> players; 
  Player next_move_player;
  int board_size;
  std::vector<std::string> board;
public:
  void apply_visual_move(int,int);

/**
 * @brief Construtor que inicializa os atributos principais do Reversi.
 *
 * @param Player primeira jogador.
 * @param Player segunda jogador.
 */
  Reversi(Player, Player);

/**
 * @brief Verifica o tabuleiro e determina se algum jogador venceu.
 *
 * @return True se algum jogador venceu ou se o tabuleiro encheu. False caso contrario.
 */
  bool game_ended();
  void after_move();
  void mark_valid_moves();
  void clear_valid_moves();
  void move(int,int);
  void move_non_check(int, int);
  char get_next_move_player_mark();
  char get_next_next_move_player_mark();
  std::vector<std::pair<int,int>> get_valid_moves(int, int);
  bool valid_move(int, int);


/**
 * @brief Imprime o tabuleiro para os jogadores
 */
  void show_board();

/**
 * @brief Verifica se o tabuleiro encheu de pecas.
 *
 * @return True se o tabuleiro encheu. False caso contrario.
 */
  bool is_board_full();
  void set_in_board(int, int, char);
  char get_in_board(int, int);
  int get_amount_of_char_in_board(char);
  std::vector<std::pair<int, int>> get_positions_of_char_in_board(char);
};

#endif
