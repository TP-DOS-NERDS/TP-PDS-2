#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

class Game {
protected:
  std::vector<std::string> board;
  int board_size;
  virtual void apply_visual_move(int,int)=0;

public:
  Game();
  void show_board();
  void render_board();
  virtual bool game_ended()=0;

  bool is_board_full();
  bool is_position_valid(int, int);
  void set_in_board(int, int, char);
  char get_in_board(int, int);
  int get_amount_of_char_in_board(char);

  /* SUGESTOES:
    * criar um metodo virtual para executar uma rodada do jogo
    * criar um metodo virtual chamado play para poder jogar o jogo
    * TROCAR as passagens de parametro i,j por pair<int,int>
    * criar uma classe para lidar com input/output
  */

//  std::vector<std::pair<int,int>> 
  std::vector<std::pair<int, int>> get_positions_of_char_in_board(char);
};
#endif
