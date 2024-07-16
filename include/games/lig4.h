#ifndef LIG4_H
#define LIG4_H

#include <set>
#include <string>
#include <vector>
#include "../game.h"
#include "../player.h"




class Lig4 : public Game {
private:
  std::pair<Player,Player> players; 
  char current_player;
  char next_player;

  static constexpr char FIRST_PLAYER = '1';
  static constexpr char SECOND_PLAYER = '2';

  void play_round();
  

  std::set<int> get_valid_moves();


  bool all_positions_are_ocuppied();

  bool position_linked(int, int);
  bool position_linked_horizontally(int, int);
  bool position_linked_vertically(int, int);
  bool position_linked_diagonally(int, int);
  bool is_position_set_by_current_player(int, int);
  void execute_move(int j);

public:
  Lig4(Player, Player);
  bool game_ended() override;


};


#endif

