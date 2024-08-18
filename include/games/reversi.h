#ifndef REVERSI_H
#define REVERSI_H

#include <string>
#include <vector>
#include "../game.h"
#include "../player.h"

class Reversi: public Game {
private:
  static constexpr int FIRST_PLAYER_ID = 1;
  static constexpr int SECOND_PLAYER_ID = 2;
  static constexpr int NO_PLAYER = 0;
  std::vector<Player> players; 
  Player next_move_player;
  int board_size;
  std::vector<std::string> board;
  virtual bool is_position_valid(std::pair<int,int> position) override;
  virtual bool game_ended() override;
  virtual void play_round() override;
  void apply_visual_move(int,int);
  void after_move();
  void mark_valid_moves();
  void clear_valid_moves();
  void move(int,int);
  void move_non_check(int, int);
  char get_next_move_player_mark();
  char get_next_next_move_player_mark();
  std::vector<std::pair<int,int>> get_positions_to_change(int, int);
  bool valid_move(int, int);


  void show_board();
  bool is_board_full();
  void set_in_board(int, int, char);
  char get_in_board(int, int);
  int get_amount_of_char_in_board(char);
  std::vector<std::pair<int, int>> get_positions_of_char_in_board(char);
public:
  void play() override;
  int get_winner() override;
  Reversi(Player, Player);
  Reversi(Reversi&);
  Reversi();
  ~Reversi();
};

#endif
