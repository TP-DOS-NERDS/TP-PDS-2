#include <iostream>
#include "../include/game.h"

Game::Game() {
  board_size=8;

  for (int i = 0; i < board_size; i++) {
    board.push_back("00000000");
  }
}

void Game::set_in_board(int x, int y, char c) {
  if (x < 0 || x > board_size || y < 0 || y > board_size) {
    // tratar excecao do x e y sairem do board
  }
  board[x][y] = c;
}

bool Game::is_board_full() {
  int default_chars=0;
  for (int i = 0; i < board_size; i++) {
    for (int j = 0; j < board_size; j++) {
      if (board[i][j] == '0') {
        default_chars++;
      }
    }
  }

  return default_chars==0;
}

bool Game::is_position_valid(int i, int j) {
  return !(i < 0 || j < 0 || i >= board_size || j >= board_size);
}

void Game::show_board() {
  std:: cout << "  ";
  for (int i = 0; i < board_size; i++) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < board_size; i++) {
    std::cout << i << " ";
    for (int j = 0; j < board_size; j++) {
      char val = board[i][j];
      if (val == '1') val='O';
      else if (val == '2') val = 'X';
      else val = ' ';
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
}

char Game::get_in_board(int x, int y) {
  return board[x][y];
}

int Game::get_amount_of_char_in_board(char c) {
  int amount = 0;
  for (int i = 0; i < board_size; i++) {
    for (int j = 0; j < board_size; j++) {
      if (board[i][j] == c) {
        amount++;
      }
    }
  }

  return amount;
} 

std::vector<std::pair<int, int>> Game::get_positions_of_char_in_board(char c) {
  std::vector<std::pair<int, int>> positions;

  for (int i = 0; i < board_size; i++) {
    for (int j = 0; j < board_size; j++) {
      if (board[i][j] == c) {
        std::pair<int, int> position = {i, j};

        positions.push_back(position);
      }
    }
  }

  return positions;
}

