#include "../game.cpp"
#include "../../include/games/reversi.h"
#include "../../include/player.h"

Reversi::Reversi(Player p1, Player p2) : Game(), next_move_player(p1) {
  players.push_back(p1);
  players.push_back(p2);

  move(3,3); // p1
  move(3,4); // p2
  move(4,4); // p1
  move(4,3); // p2
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

bool Reversi::valid_move(int x, int y) {
  // definir oq e um movimento valido
  return true;
}

bool Reversi::game_ended() {
  return is_board_full();
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
  }

  // logica do reversi de trocar as pecas
  
  char player_mark = get_next_move_player_mark();

  set_in_board(x, y, player_mark);
  after_move();

  if (game_ended()) {
    // tratar que a partida acabou
  }
}

