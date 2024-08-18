#include <iostream>
#include "../../include/games/reversi.h"

bool compareTmp1(int j, int to, bool alt_desired_move) {
  return (alt_desired_move) ? (j > to) : (j < to);
}

void addOrSubtract(int & j, bool alt_desired_move) {
  if (alt_desired_move) j--;
  else j++;
}

Reversi::Reversi(Player p1, Player p2) : next_move_player(p1) {
  players.push_back(p1);
  players.push_back(p2);
  board_size=8;

  for (int i = 0; i < board_size; i++) {
    board.push_back("00000000");
  }

  move_non_check(3,3); // p1
  move_non_check(3,4); // p2
  move_non_check(4,4); // p1
  move_non_check(4,3); // p2
  after_move();
}

Reversi::Reversi() : next_move_player(Player("Player1 Placeholder", "Player1 Placeholder")) {
  Player p1(this->next_move_player);
  Player p2("Player2 Placeholder", "Player2 Placeholder");

  players.push_back(p1);
  players.push_back(p2);
  next_move_player=p1;
  board_size=8;

  for (int i = 0; i < board_size; i++) {
    board.push_back("00000000");
  }

  move_non_check(3,3); // p1
  move_non_check(3,4); // p2
  move_non_check(4,4); // p1
  move_non_check(4,3); // p2
  after_move();
}

Reversi::Reversi(Reversi& old_game) : next_move_player(old_game.players[0]) {
  players.push_back(players[0]);
  players.push_back(players[1]);
  board_size=8;

  for (int i = 0; i < board_size; i++) {
    board.push_back(old_game.board[i]);
  }

  if (old_game.get_next_move_player_mark() == '2') {
    after_move();
  }
};

Reversi::~Reversi() {

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

std::vector<std::pair<int,int>> Reversi::get_positions_to_change(int x, int y) {
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
  auto to_change = Reversi::get_positions_to_change(x, y);

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
      std::vector<std::pair<int,int>> to_change = get_positions_to_change(i, j);

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



void Reversi::set_in_board(int x, int y, char c) {
  if (x < 0 || x > board_size || y < 0 || y > board_size) {
    // tratar excecao do x e y sairem do board
  }
  board[x][y] = c;
}

bool Reversi::is_board_full() {
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

void Reversi::show_board() {
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

char Reversi::get_in_board(int x, int y) {
  return board[x][y];
}

int Reversi::get_amount_of_char_in_board(char c) {
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

std::vector<std::pair<int, int>> Reversi::get_positions_of_char_in_board(char c) {
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

void Reversi::play() {
  while(!game_ended()) {
    this->play_round();
  }
}

void Reversi::play_round() {
  int x, y;
  while (std::cin >> x >> y) {
    this->move(x,y);
    std::cout << "JOGADOR DA VEZ : " << this->get_next_move_player_mark() << std::endl;
    this->show_board();
  }
}

int Reversi::get_winner() {
  int p1 = this->get_amount_of_char_in_board('1');
  int p2 = this->get_amount_of_char_in_board('2');

  if (p1 == p2) {
    return Reversi::NO_PLAYER;
  } else if (p1 > p2) {
    return Reversi::FIRST_PLAYER_ID;
  } else {
    return Reversi::SECOND_PLAYER_ID;
  }
}

