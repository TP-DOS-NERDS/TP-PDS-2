#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

class Game {
private:
  std::vector<std::string> board;
  int board_size;

public:
  Game();
  virtual void show_board();
  virtual bool game_ended()=0;

  bool is_board_full();
  void set_in_board(int, int, char);
};

#endif
