#ifndef MINESWEEPER_H
#define MINESWEEPER_H


#include "../game.h"
#include "../IOHandler.h"
#include <vector>

class Minesweeper : public Game {

public:
  Minesweeper();
  ~Minesweeper();

  void play() override;
  int get_winner() override;

private:
  std::vector<std::vector<int>> bombs;
  std::vector<std::vector<int>> board; // 78 = ~ | 22 = F
  bool game_over = false;
  int board_size = 20;
  int winner = 2; // Loss
  int remaining_tiles;

  std::pair<char,std::pair<int, int>> take_input();
  bool is_position_valid(std::pair<int, int> position) override;
  bool game_ended() override;
  void play_round() override;

  void increase_close_tiles(int x, int y);
  void generate_bombs(int x, int y);

  bool first_move(int x, int y);

  int get_remaining_tiles();

  void reveal_tile(int x, int y);
  void place_flag(int x, int y);
  int count_close_flags(int x, int y);

  void lose();
  void win();
};



#endif
