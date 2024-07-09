#include <algorithm>
#include "../game.cpp"
#include "../../include/games/reversi.h"
#include "../../include/player.h"

Reversi::Reversi(Player p1, Player p2) : Game(), next_move_player(p1) {
  players.push_back(p1);
  players.push_back(p2);

  move_non_check(3,3); // p1
  move_non_check(3,4); // p2
  move_non_check(4,4); // p1
  move_non_check(4,3); // p2
}

char Reversi::get_next_move_player_mark() {
  // da pra simplificar em um unico statement
  Player p1 = players[0];

  if (next_move_player.get_username() == p1.get_username()) {
    return '1';
  } else {
    return '2';
  }
}

char Reversi::get_next_next_move_player_mark() {
  // da pra simplificar em um unico statement
  Player p1 = players[0];

  if (next_move_player.get_username() == p1.get_username()) {
    return '2';
  } else {
    return '1';
  }
}

// sera usado posteriormente para highlighting de posicoes validas de se jogar
std::vector<std::pair<int,int>> Reversi::valid_moves(char c) {
  std::vector<std::pair<int,int>> temp_empty;

  return temp_empty;
}

bool Reversi::valid_move(int x, int y) {
  // definir oq e um movimento valido 
  
  if (get_in_board(x,y) != '0') {
    return false;
  }

  char other_player_move = get_next_next_move_player_mark();

  // ve se tem uma peca q da pra usar p "contagiar"

  std::vector<std::pair<int, int>> positions = get_positions_of_char_in_board(get_next_move_player_mark());

  // indo pra diagonal inferior direita

  bool valid = 0;

  for (auto & position : positions) {
    int delta_x = std::abs(position.first-x);
    int delta_y = std::abs(position.second-y);

    int amount_of_other=0;

    // fazer uma fn auxiliar pra comparar msm linha ou msm coluna 
    if (delta_x == 0 && delta_y != 0) { // mesma linha
      // verifica se tem algum elemento vazio entre eles.
      int fromY = std::min(position.second, y);
      int toY = std::max(position.second, y);
      for (int j = fromY; j < toY; j++) {
        char element_in_x_j = get_in_board(x, j);
        if (element_in_x_j == '0') {
          valid=0;
          break;
        } else if (element_in_x_j == other_player_move) {
          amount_of_other++;
        }

        valid=1;
      }
    }

    if (valid && amount_of_other==0) {
      valid=0;
    }

    amount_of_other=0;
    if (!valid) {
      if (delta_x != 0 && delta_y == 0) { // mesma coluna
        // verifica se tem algum elemento vazio entre eles.
        int fromX = std::min(position.first, x);
        int toX = std::max(position.first, x);
        for (int j = fromX; j < toX; j++) {
          char element_in_j_y = get_in_board(x, j);
          if (element_in_j_y == '0') {
            valid=0;
            break;
          } else if (element_in_j_y == other_player_move) {
            amount_of_other++;
          }
          valid=1;
        }
      }
    }

    // validar diagonal
  }

  return valid;
}

bool Reversi::game_ended() {
  return (is_board_full() || (get_amount_of_char_in_board('1') == 0) || (get_amount_of_char_in_board('2') == 0));
}

void Reversi::after_move() {
  Player p1 = players[0], p2 = players[1];
  if (next_move_player.get_username() == p1.get_username()) {
    next_move_player=p2;
  } else {
    next_move_player=p1;
  }
}

void Reversi::move(int x, int y) {
  if (!valid_move(x, y)) {
    // excessao de movimento invalido
  
    std::cout << "MOVE NOT ALLOWED" << std::endl;
    return;
  }

  // logica do reversi de trocar as pecas
  
  char player_mark = get_next_move_player_mark();

  set_in_board(x, y, player_mark);
  after_move();

  if (game_ended()) {
    // tratar que a partida acabou
    std::cout << "FIM DE PARTIDA" << std::endl;
  }
}

void Reversi::move_non_check(int x, int y) {
  char player_mark = get_next_move_player_mark();
  set_in_board(x, y, player_mark);
  after_move();
}

