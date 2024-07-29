#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "../game.h"
#include "../player.h"

class Minesweeper : public Game {

private:
  Player& player;
  std::vector<std::string> bombs;
  bool game_over = false;
  int remaining_tiles;

public:
  Minesweeper(Player& p);
  ~Minesweeper();
  void generate_bombs(int x, int y);

  void show_board() override;
  bool game_ended() override;
  
  void reveal_tile(int x, int y);
  int get_remaining_tiles();

private:
  bool valid_move(int x, int y);
  void increase_close_tiles(int x, int y);

  void lose();
  void win();
};



#endif
