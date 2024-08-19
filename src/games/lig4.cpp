#include "../../include/game.h"
#include "../../include/games/lig4.h"
#include "../../include/player.h"
#include "../../include/IOHandler.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <utility>
#include <iostream>

Lig4::Lig4() {
  board = std::vector<std::vector<int>>(Lig4::NUMBER_OF_ROWS, std::vector<int>(Lig4::NUMBER_OF_COLUMNS));
  for(auto& row : board) {
    for(auto& value : row) {
      value = 0;
    }
  }

  current_player = Lig4::FIRST_PLAYER_ID;
  next_player = Lig4::SECOND_PLAYER_ID;
  winner = Lig4::NO_PLAYER;
}

Lig4::invalid_move_input_exception::invalid_move_input_exception(InputError error) {
  this->error = error; 
}

void Lig4::play() {
  while(!game_ended()) {
    play_round();
  } 

  if(current_player == FIRST_PLAYER_ID && is_a_position_linked()) {
    winner = SECOND_PLAYER_ID;
  } 

  if(current_player == SECOND_PLAYER_ID && is_a_position_linked()) {
    winner = FIRST_PLAYER_ID;
  }
}

int Lig4::get_winner() {
  return winner;
}

void Lig4::play_round() {
  IOHandler::print<std::vector<std::vector<int>>>(board);

  int column_index = get_valid_move_input();
  execute_move(column_index);  
    
  std::swap(current_player, next_player);
}

int Lig4::get_valid_move_input() {
  IOHandler::print("Jogada [Player " + std::to_string(current_player) + "]: Insira a coluna na qual voce deseja jogar"); 

  int column_index;
  bool move_input_is_invalid = true;

  while(move_input_is_invalid) {
    std::string move_input = IOHandler::get<std::string>();
//
    try {
      validate_move_input(move_input);
      move_input_is_invalid = false;
      column_index = std::stoi(move_input);
    }
    catch(invalid_move_input_exception& exception) {
      if(exception.error == InputError::invalid_input) IOHandler::print("Input invalido: Insira novamente a coluna na qual voce deseja jogar");
      if(exception.error == InputError::invalid_move) IOHandler::print("Coluna invalida: Insira novamente a coluna na qual voce deseja jogar");
    }
  }

  return column_index - 1;
}

void Lig4::validate_move_input(std::string move) {
  if(std::any_of(move.begin(), move.end(), [](char c) { return !std::isdigit(c); })) {
    throw invalid_move_input_exception(InputError::invalid_input);
  }

  int move_value = std::stoi(move);
  move_value--;

  std::set<int> valid_moves = get_valid_moves();

  if(valid_moves.find(move_value) == valid_moves.end()) {
    throw invalid_move_input_exception(InputError::invalid_move);
  }
}

void Lig4::execute_move(int j) {
  for(int i = Lig4::NUMBER_OF_ROWS - 1; i >= 0; i--) {
    if(board[i][j] == 0) {
      board[i][j] = current_player;
      return;
    } 
  }
}


std::set<int> Lig4::get_valid_moves() {
  std::set<int> valid_moves;
  
  for(int i = 0; i < Lig4::NUMBER_OF_COLUMNS; i++) {
    if(board[0][i] == 0) {
      valid_moves.insert(i);
    }
  }

  return valid_moves;
}

bool Lig4::game_ended() {
  return is_a_position_linked() || all_positions_are_ocuppied();
}

bool Lig4::is_a_position_linked() {
  for(int i = 0; i < Lig4::NUMBER_OF_ROWS; i++) {
    for(int j = 0; j < Lig4::NUMBER_OF_COLUMNS; j++) {
      if(board[i][j] == FIRST_PLAYER_ID || board[i][j] == SECOND_PLAYER_ID) {
        if(position_linked(std::make_pair(i,j))) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Lig4::all_positions_are_ocuppied() {
  for(auto& row : board) {
    for(auto& position_value : row) {
      if(position_value == 0) return false;
    }
  } 

  return true;
}

bool Lig4::position_linked(std::pair<int,int> position) {
  return position_linked_horizontally(position) || position_linked_vertically(position) || position_linked_diagonally(position);
}

bool Lig4::position_linked_horizontally(std::pair<int,int> position) {
  int links_on_right = 0, links_on_left = 0;

  for(int k = position.second + 1; k < Lig4::NUMBER_OF_COLUMNS && is_position_set_by_current_player(std::make_pair(position.first, k)); k++) {
    links_on_right++;
  }

  for(int k = position.second - 1; k >= 0 && is_position_set_by_current_player({ position.first, k }); k--) {
    links_on_left++;
  }

  int number_of_horizontal_links = links_on_right + links_on_left;

  return number_of_horizontal_links >= 3;
}
bool Lig4::position_linked_vertically(std::pair<int,int> position) {
  int links_above = 0, links_down = 0;

  for(int k = position.first - 1; k >= 0 && is_position_set_by_current_player(std::make_pair(k, position.second)); k--) {
    links_above++;
  }

  for(int k = position.first + 1; k < Lig4::NUMBER_OF_ROWS && is_position_set_by_current_player( std::make_pair(k, position.second)); k++) {
    links_down++;
  }

  int number_of_vertical_links = links_above + links_down;

  return number_of_vertical_links >= 3;
}

bool Lig4::position_linked_diagonally(std::pair<int,int> position) {
  int number_of_links_on_right_diagonal = 0;
  for(int k = 1; is_position_valid(std::make_pair(position.first + k, position.second + k)) && is_position_set_by_current_player(std::make_pair(position.first + k, position.second + k)); k++) {
    number_of_links_on_right_diagonal++;
  }
  for(int k = 1; is_position_valid(std::make_pair(position.first - k, position.second - k)) && is_position_set_by_current_player(std::make_pair(position.first - k, position.second - k)); k++) {
    number_of_links_on_right_diagonal++;
  }

  int number_of_links_on_left_diagonal = 0;
  for(int k = 1; is_position_valid(std::make_pair(position.first + k, position.second - k)) && is_position_set_by_current_player(std::make_pair(position.first + k, position.second - k)); k++) {
    number_of_links_on_left_diagonal++;
  }
  for(int k = 1; is_position_valid(std::make_pair(position.first - k, position.second + k)) && is_position_set_by_current_player(std::make_pair(position.first - k, position.second + k)); k++) {
    number_of_links_on_left_diagonal++;
  }

  return number_of_links_on_right_diagonal >= 3 || number_of_links_on_left_diagonal >= 3;
}

bool Lig4::is_position_valid(std::pair<int,int> position) {
  if(position.first < 0 || position.first >= Lig4::NUMBER_OF_ROWS || position.second < 0 || position.second >= Lig4::NUMBER_OF_COLUMNS) return false;

  return true;
}


bool Lig4::is_position_set_by_current_player(std::pair<int,int> position) {
  return board[position.first][position.second] == current_player;
}
