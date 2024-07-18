#include <algorithm>
#include "../game.cpp"
#include "../../include/games/reversi.h"
#include "../../include/player.h"

bool compareTmp1(int j, int to, bool alt_desired_move) {
  return (alt_desired_move) ? (j > to) : (j < to);
}

void addOrSubtract(int & j, bool alt_desired_move) {
  if (alt_desired_move) j--;
  else j++;
}

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
  if (get_in_board(x, y) != '0') {
    return false;
  }

  char other_player_move = get_next_next_move_player_mark();
  std::vector<std::pair<int, int>> positions = get_positions_of_char_in_board(get_next_move_player_mark());
  
  bool valid = false;
  std::vector<std::pair<int, int>> to_change;

  auto add_positions_to_change = [&](int startX, int startY, int dx, int dy) {
    std::vector<std::pair<int, int>> temp_positions;
    int currentX = startX + dx;
    int currentY = startY + dy;
    int amount_of_other = 0;
    while (get_in_board(currentX, currentY) == other_player_move) {
      temp_positions.push_back({currentX, currentY});
      amount_of_other++;
      currentX += dx;
      currentY += dy;
    }
    if (get_in_board(currentX, currentY) == get_next_move_player_mark() && amount_of_other > 0) {
      to_change.insert(to_change.end(), temp_positions.begin(), temp_positions.end());
      return true;
    }
    return false;
  };

  for (auto& position : positions) {
    if (position.first == x) {
      if (add_positions_to_change(x, y, 0, (position.second < y) ? -1 : 1)) {
        valid = true; }
    } else if (position.second == y) {
      if (add_positions_to_change(x, y, (position.first < x) ? -1 : 1, 0)) {
        valid = true;
      }
    } else if (std::abs(position.first - x) == std::abs(position.second - y)) {
      int dx = (position.first < x) ? -1 : 1;
      int dy = (position.second < y) ? -1 : 1;
      if (add_positions_to_change(x, y, dx, dy)) {
        valid = true;
      }
    }
  }

  // Change the pieces if the move is valid
  if (valid) {
    char current_player_move = get_next_move_player_mark();
    for (auto& position : to_change) {
      set_in_board(position.first, position.second, current_player_move);
    }
  }

  return valid;
}

// redefinir nome; quebrar em duas funcoes;
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

void Reversi::apply_visual_move(int x, int y) {
  Reversi::move(x,y);
}
