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

public:
  void apply_visual_move(int,int);
  Reversi(Player, Player);
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
};

#endif
