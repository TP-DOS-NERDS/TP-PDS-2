#include "../../include/games/minesweeper.h"
#include <cstdlib>
#include <ctime>

Minesweeper::Minesweeper() : Game() {
  for (int i = 0; i < board_size; i++) {
    bombs.push_back(std::vector<int>(board_size, 0));
    board.push_back(std::vector<int>(board_size, 126));
  }
}

Minesweeper::~Minesweeper() {}

void Minesweeper::play() {
  int x, y;
  IOHandler::print("X: ");
  x = IOHandler::get<int>();
  IOHandler::print("Y: ");
  y = IOHandler::get<int>();
  x--; y--;

  while (!is_position_valid({x, y})) {
    IOHandler::print("Posicao Invalida! Tente Novamente.\nX: ");
    x = IOHandler::get<int>();
    IOHandler::print("Y: ");
    y = IOHandler::get<int>();
    x--; y--;
  }
  first_move(x, y);

  while(!game_ended()) {
    play_round();
  } 
}

int Minesweeper::get_winner() {
  return winner;
}

void Minesweeper::play_round() {
  IOHandler::print_board<std::vector<std::vector<int>>>(board);
  std::pair<char, std::pair<int, int>> tile = take_input();
  int x = tile.second.first; int y = tile.second.second;

  if (tile.first == 'F' || tile.first == 'f')
    place_flag(x, y);

  else if (tile.first == 'R' || tile.first == 'r') {
    // Reveal a Tile
    if (bombs[x][y] != -2)
      reveal_tile(x, y);

    // Press on a number (Reveal neraby tiles without flags)
    else if (bombs[x][y] == -2 && board[x][y] >= '1' && board[x][y] <= '8') {

      // Reveal only if there are enough flags pointed by the number
      if (board[x][y] - '0' == count_close_flags(x, y)) {

        for (int i = x - 1; i <= x + 1; i++) {
          for (int j = y - 1; j <= y + 1; j++) {
            if (!is_position_valid({i, j}))
              continue;
            // Dont reveal if tile is flaged or revealed already
            if (board[i][j] == 70 || bombs[i][j] == -2)
              continue;
            reveal_tile(i, j);
          }
        }
      }
    }
  }
}

bool Minesweeper::game_ended() {
  if (remaining_tiles == 0)
    win();

  return game_over;
}

std::pair<char,std::pair<int, int>> Minesweeper::take_input() {
  char opcao;
  IOHandler::print("R para revelar uma casa / F cara colocar uma bandeira: ");
  opcao = IOHandler::get<char>();
  while (opcao != 'R' && opcao != 'r' && opcao != 'F' && opcao != 'f') {
    IOHandler::print("Opcao Invalida! Tente Novamente.");
    IOHandler::print("R para revelar uma casa / F cara colocar uma bandeira: ");
    opcao = IOHandler::get<char>();
  }

  int x, y;
  IOHandler::print("X: ");
  x = IOHandler::get<int>();
  IOHandler::print("Y: ");
  y = IOHandler::get<int>();
  x--; y--;

  while (!is_position_valid({x, y})) {
    IOHandler::print("Posicao Invalida! Tente Novamente.\nX: ");
    x = IOHandler::get<int>();
    IOHandler::print("Y: ");
    y = IOHandler::get<int>();
    x--; y--;
  }

  return {opcao, {x, y}};
}

bool Minesweeper::first_move(int x, int y) {
  generate_bombs(x, y);
  reveal_tile(x, y);
  return true;
}

int Minesweeper::get_remaining_tiles() {
  return remaining_tiles;
}

void Minesweeper::reveal_tile(int x, int y) {
  int tile = bombs[x][y];
  
  // Reveal an empty tile (and its neighbours)
  if (tile == 0) {
    bombs[x][y] = -2;
    board[x][y] = 0;
    remaining_tiles--;

    for (int i = x - 1; i <= x + 1; i++)
      for (int j = y - 1; j <= y + 1; j++)
        if (is_position_valid({i, j}))
          reveal_tile(i, j);
  }

  // Reveal an number
  else if (tile >= 1 && tile <= 8) {
    board[x][y] = bombs[x][y] + '0';
    bombs[x][y] = -2;
    remaining_tiles--;
  }

  // Reveal an Bomb
  else if (tile == -1) {
    board[x][y] = 18;
    bombs[x][y] = -2;
    lose();
  }
}

void Minesweeper::place_flag(int x, int y) {
  // Remove if placed already
  if (board[x][y] == 70)
    board[x][y] = 126;

  // Place otherwise
  else if (bombs[x][y] != -2)
    board[x][y] = 70;
}

bool Minesweeper::is_position_valid(std::pair<int, int> position) {
  return (position.first >= 0 && position.first <= 7 && position.second >= 0 && position.second <= 7);
}

void Minesweeper::generate_bombs(int x, int y) {
  // Generating bombs
  int remaining_spaces = board_size * board_size;
  int remaining_bombs = remaining_spaces / 8;
  remaining_tiles = remaining_spaces - remaining_bombs;

  // Removing safe space from the count
  if ((x == 0 || x == board_size - 1) && (y == 0 || y == board_size - 1))
    remaining_spaces -= 4;
  else if (x == 0 || x == board_size - 1 || y == 0 || y == board_size - 1)
    remaining_spaces -= 6;
  else
    remaining_spaces -= 9;


  // Loop through the board
  for (int i = 0; i < board_size; i++) {
    for (int j = 0; j < board_size; j++) {

      // If close to initial tile, skip
      if (i >= x - 1 && i <= x + 1 && j >= y - 1 && j <= y + 1)
        continue;

      // Randomly put a bomb
      srand(time(NULL) * (i + 1) * (j + 1));
      if (rand() % remaining_spaces < remaining_bombs) {
        bombs[i][j] = -1;
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
      if (is_position_valid({i, j}))
        if (bombs[i][j] != -1)
          bombs[i][j]++;
}

int Minesweeper::count_close_flags(int x, int y) {
  int amount = 0;
  for (int i = x - 1; i <= x + 1; i++)
    for (int j = y - 1; j <= y + 1; j++)
      if (is_position_valid({i, j}))
        if (board[i][j] == 70)
          amount++;
  return amount;
}

void Minesweeper::lose() {
  IOHandler::print_board<std::vector<std::vector<int>>>(board);
  IOHandler::print("Voce perdeu!\n");

  game_over = true;
}

void Minesweeper::win() {
  IOHandler::print_board<std::vector<std::vector<int>>>(board);
  IOHandler::print("Voce ganhou!\n");
  winner = 1;

  game_over = true;
}
