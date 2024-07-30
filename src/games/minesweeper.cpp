#include "../../include/games/minesweeper.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Minesweeper::Minesweeper(Player& p) : Game(), player(p) {
  for (int i = 0; i < 8; i++)
    bombs.push_back("00000000");
}

Minesweeper::~Minesweeper() {}

void Minesweeper::show_board() {
  std::cout << "  ";
  for (int i = 0; i < 8; i++) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < 8; i++) {
    std::cout << i << " ";
    for (int j = 0; j < 8; j++) {
      if (get_in_board(i, j) == 'F')
        std::cout << "F ";
      else if (bombs[i][j] != 'R')
        std::cout << "~ ";
      else {
        char val = get_in_board(i, j);
        if (val == '0')
          val = ' ';
        std::cout << val << ' ';
      }
    }
    std::cout << std::endl;
  }
}

bool Minesweeper::game_ended() {
  return game_over;
}

bool Minesweeper::first_move(int x, int y) {
  if (!valid_move(x, y))
    return false;

  generate_bombs(x, y);
  reveal_tile(x, y);
  return true;
}

void Minesweeper::left_click(int x, int y) {
  if (!valid_move(x, y))
    return;
  if (get_in_board(x, y) == 'F')
    return;

  // Reveal a Tile
  if (bombs[x][y] != 'R')
    reveal_tile(x, y);

  // Press on a number (Reveal neraby tiles without flags)
  else if (bombs[x][y] == 'R' && get_in_board(x, y) >= '1' && get_in_board(x, y) <= '8') {

    // Reveal only if there are enough flags pointed by the number
    if (get_in_board(x, y) <= count_close_flags(x, y)) {

      for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
          if (!valid_move(i, j))
            continue;
          // Dont reveal if tile is flaged or revealed already
          if (get_in_board(i, j) == 'F' || bombs[i][j] == 'R')
            continue;
          reveal_tile(i, j);
        }
      }
    }
  }
}

void Minesweeper::right_click(int x, int y) {
  if (!valid_move(x, y))
    return;
  if (bombs[x][y] == 'R')
    return;

  place_flag(x, y);
}

int Minesweeper::get_remaining_tiles() {
  return remaining_tiles;
}

void Minesweeper::reveal_tile(int x, int y) {
  if (!valid_move(x, y))
    return;

  char tile = bombs[x][y];

  // Reveal an empty tile (and its neighbours)
  if (tile == '0') {
    bombs[x][y] = 'R';
    set_in_board(x, y, '0');
    remaining_tiles--;

    for (int i = x - 1; i <= x + 1; i++)
      for (int j = y - 1; j <= y + 1; j++)
        reveal_tile(i, j);
  }

  // Reveal an number
  else if (tile >= '1' && tile <= '8') {
    set_in_board(x, y, bombs[x][y]);
    bombs[x][y] = 'R';
    remaining_tiles--;
  }

  // Reveal an Bomb
  else if (tile == 'B') {
    set_in_board(x, y, 'B');
    bombs[x][y] = 'R';
    lose();
    return;
  }

  // Check for win
  if (remaining_tiles == 0)
    win();
}

void Minesweeper::place_flag(int x, int y) {
  if (!valid_move(x, y))
    return;
  
  // Remove if placed already
  if (get_in_board(x, y) == 'F')
    set_in_board(x, y, '~');

  // Place otherwise
  else if (bombs[x][y] != 'R')
    set_in_board(x, y, 'F');
}

bool Minesweeper::valid_move(int x, int y) {
  return (x >= 0 && x <= 7 && y >= 0 && y <= 7);
}

void Minesweeper::generate_bombs(int x, int y) {
  // Generating bombs
  int remaining_bombs = 10;
  int remaining_spaces = 64;
  remaining_tiles = remaining_spaces - remaining_bombs;

  // Removing safe space from the count
  if ((x == 0 || x == 7) && (y == 0 || y == 7))
    remaining_spaces -= 4;
  else if (x == 0 || x == 7 || y == 0 || y == 7)
    remaining_spaces -= 6;
  else
    remaining_spaces -= 9;


  // Loop through the board
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {

      // If close to initial tile, skip
      if (i >= x - 1 && i <= x + 1 && j >= y - 1 && j <= y + 1)
        continue;

      // Randomly put a bomb
      srand(time(NULL) * (i + 1) * (j + 1));
      if (rand() % remaining_spaces < remaining_bombs) {
        bombs[i][j] = 'B';
        increase_close_tiles(i, j);
        remaining_bombs--;
      }
      remaining_spaces--;
    }
  }
}

void Minesweeper::increase_close_tiles(int x, int y) {
  for (int i = x - 1; i <= x + 1; i++)
    for (int j = y - 1; j <= y + 1; j++)
      if (valid_move(i, j))
        if (bombs[i][j] != 'B')
          bombs[i][j]++;
}

char Minesweeper::count_close_flags(int x, int y) {
  char amount = '0';
  for (int i = x - 1; i <= x + 1; i++)
    for (int j = y - 1; j <= y + 1; j++)
      if (valid_move(i, j))
        if (bombs[i][j] != 'B')
          amount++;
  return amount;
}

void Minesweeper::lose() {
  show_board();

  std::cout << "You lose!" << std::endl << std::endl;
  player.increase_defeats();

  game_over = true;
}

void Minesweeper::win() {
  show_board();

  std::cout << "You win!" << std::endl << std::endl;
  player.increase_wins();

  game_over = true;
}
