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
  Reversi(Player, Player);
  bool valid_move(int,int);
  bool game_ended();
  void after_move();
  void move(int,int);
  void move_non_check(int x, int y);
  char get_next_move_player_mark();
  char get_next_next_move_player_mark();
  std::vector<std::pair<int,int>> valid_moves(char);
};

#endif
