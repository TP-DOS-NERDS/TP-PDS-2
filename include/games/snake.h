#ifndef SNAKE_H
#define SNAKE_H

#include <termios.h>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <csignal>
#include "../player.h"
#include "../game.h"
#include "../../include/IOHandler.h"
#include "../../include/terminal_handler.h"


class Snake : public Game {
private:
  std::vector<std::vector<char>> board;
  int snake[2][100];  // Snake coordinates
  int length; // Snake size
  int direction; // Snake direction
  int food_x, food_y;
  bool running;

struct termios original_termios;

  void init_board();
  void place_food();
  void print_board() const;
  bool move_snake(int dx, int dy);
  bool is_game_over(int x, int y) const;
  bool is_board_full() const;
  bool is_position_valid(std::pair<int,int> position);
  bool game_ended();
  void play_round();
  int score;



public:
  Snake(Player player);
  Snake();
  ~Snake();

  void play();
  int get_winner();
  void move();
  void change_direction(int new_direction);
  bool is_game_over() const;
  void wait(int milliseconds);
  int get_score() const;
};

#endif
