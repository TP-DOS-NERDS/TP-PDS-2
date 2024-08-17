#ifndef LIG4_H
#define LIG4_H

#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <exception>
#include "../game.h"


class Lig4 : public Game {
public:
  Lig4();
  void play() override;


private:

  enum class InputError { invalid_move, invalid_input };
  class invalid_move_input_exception : public std::exception {
  public:
    InputError error; 
    invalid_move_input_exception(InputError error);
  };
    
  std::vector<std::vector<int>> board;
  int current_player;
  int next_player;

  static constexpr int NUMBER_OF_ROWS = 6;
  static constexpr int NUMBER_OF_COLUMNS = 7;

  static constexpr int FIRST_PLAYER_ID = 1;
  static constexpr int SECOND_PLAYER_ID = 2;


  bool is_position_valid(std::pair<int,int> position) override;
  bool game_ended() override;
  void play_round() override;

  int get_valid_move_input();
  void validate_move_input(std::string move_input);
  void execute_move(int j);

  std::set<int> get_valid_moves();
  bool all_positions_are_ocuppied();

  bool position_linked(std::pair<int,int> position);
  bool position_linked_horizontally(std::pair<int,int> position);
  bool position_linked_vertically(std::pair<int,int> position);
  bool position_linked_diagonally(std::pair<int,int> position);
  bool is_position_set_by_current_player(std::pair<int,int> position);



};


#endif
