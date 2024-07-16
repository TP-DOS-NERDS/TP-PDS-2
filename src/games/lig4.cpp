#include "../game.cpp"
#include "../../include/games/lig4.h"
#include "../../include/player.h"
#include <algorithm>
#include <utility>

Lig4::Lig4(Player first_player, Player second_player) : Game(), players(first_player, second_player), current_player('1'), next_player('2') {
}

void Lig4::play_round() {
  std::set<int> valid_moves = get_valid_moves();
  int column_index; 
  do {
    // TODO: ENCAPSULAR A ENTRADA PADRAO  
    std::cin >> column_index;

  } while(valid_moves.find(column_index) == valid_moves.end());

  execute_move(column_index);  
    
  std::swap(current_player, next_player);
}

void Lig4::execute_move(int j) {
  for(int i = board_size - 1; i >= 0; i--) {
    if(board[i][j] == '0') board[i][j] = current_player;
  }
}


std::set<int> Lig4::get_valid_moves() {
  std::set<int> valid_moves;
  for(int j = 0; j < board_size; j++) {
    if(board[0][j] == '0') {
      valid_moves.insert(j);
    }
  }

  return valid_moves;
}

bool Lig4::game_ended() {
  // criar uma funcao has_winner ?????
  for(int i = 0; i < board_size; i++) {
    for(int j = 0; j < board_size; j++) {
      if(board[i][j] == FIRST_PLAYER || board[i][j] == SECOND_PLAYER) {
        if(position_linked(i, j)) {
          return true;
        }
      }
    }
  }

  if(all_positions_are_ocuppied()) return true;

  return false;
}

bool Lig4::all_positions_are_ocuppied() {
  for(auto& row : board) {
    for(auto& position_value : row) {
      if(position_value == '0') return false;
    }
  } 

  return true;
}

bool Lig4::position_linked(int i, int j) {
  return position_linked_horizontally(i, j) || position_linked_vertically(i, j) || position_linked_diagonally(i, j);
}

bool Lig4::position_linked_horizontally(int i, int j) {
  int links_on_right = 0, links_on_left = 0;

  for(int k = j + 1; k < board_size && is_position_set_by_current_player(i, k); k++) {
    links_on_right++;
  }

  for(int k = j - 1; k >= 0 && is_position_set_by_current_player(i, k); k--) {
    links_on_left++;
  }

  int number_of_horizontal_links = links_on_right + links_on_left;

  return number_of_horizontal_links >= 3;
}
bool Lig4::position_linked_vertically(int i, int j) {
  int links_above = 0, links_down = 0;

  for(int k = i - 1; k >= 0 && is_position_set_by_current_player(i, k); k--) {
    links_above++;
  }

  for(int k = i + 1; k < board_size && is_position_set_by_current_player(i, k); k++) {
    links_down++;
  }

  int number_of_vertical_links = links_above + links_down;

  return number_of_vertical_links >= 3;
}

bool Lig4::position_linked_diagonally(int i, int j) {
  int number_of_links_on_right_diagonal = 0;
  for(int k = 1; is_position_valid(i + k, j + k) && is_position_set_by_current_player(i + k, j + k); k++) {
    number_of_links_on_right_diagonal++;
  }
  for(int k = 1; is_position_valid(i - k, j - k) && is_position_set_by_current_player(i - k, j - k); k++) {
    number_of_links_on_right_diagonal++;
  }

  int number_of_links_on_left_diagonal = 0;
  for(int k = 1; is_position_valid(i + k, j - k) && is_position_set_by_current_player(i + k, j - k); k++) {
    number_of_links_on_left_diagonal++;
  }
  for(int k = 1; is_position_valid(i - k, j + k) && is_position_set_by_current_player(i - k, j + k); k++) {
    number_of_links_on_left_diagonal++;
  }

  return number_of_links_on_right_diagonal >= 3 || number_of_links_on_left_diagonal >= 3;
}


bool Lig4::is_position_set_by_current_player(int i, int j) {
  return board[i][j] == current_player;
}
