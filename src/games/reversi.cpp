#include <algorithm>
#include <iostream>
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
  after_move();
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

std::vector<std::pair<int,int>> Reversi::get_valid_moves(int x, int y) {
  std::vector<std::pair<int, int>> to_change;
  char char_in_position = get_in_board(x,y);
  if (char_in_position != '0' && char_in_position != '3') {
    return to_change;
  }

  char other_player_move = get_next_next_move_player_mark();
  std::vector<std::pair<int, int>> positions = get_positions_of_char_in_board(get_next_move_player_mark());
  
  bool valid = false;

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

  return to_change;
}

bool Reversi::valid_move(int x, int y) {
  auto to_change = Reversi::get_valid_moves(x, y);

  bool valid = to_change.size() != 0;

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
  auto swap_current_player = [&](Reversi* reversi) {
    Player p1 = reversi->players[0], p2 = reversi->players[1];
    if (reversi->next_move_player.get_username() == p1.get_username()) {
      reversi->next_move_player=p2;
    } else {
      reversi->next_move_player=p1;
    }
  };

  swap_current_player(this);
 
  int valid_moves=0;

  for (int i = 0; i < board_size; i++) {
    for (int j = 0; j < board_size; j++) {
      std::vector<std::pair<int,int>> to_change = get_valid_moves(i, j);

      valid_moves += (int)to_change.size();

      if ((int)to_change.size() != 0) {
        set_in_board(i,j,'3');
      } else if (get_in_board(i,j) == '3') {
        set_in_board(i,j,'0');
      }
    }
  }

  if (valid_moves==0) {
    std::cout << "PASSOU A VEZ " << std::endl;
    swap_current_player(this);
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
  Player p1 = players[0], p2 = players[1];
  if (next_move_player.get_username() == p1.get_username()) {
    next_move_player=p2;
  } else {
    next_move_player=p1;
  }
}

void Reversi::apply_visual_move(int x, int y) {
  Reversi::move(x,y);
}

