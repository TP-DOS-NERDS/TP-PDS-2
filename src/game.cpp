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

void Game::show_board() {
  for (int i = 0; i < board_size; i++) {
    std::cout << board[i] << std::endl;
  }
}

