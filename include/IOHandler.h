#ifndef IOHandler_H
#define IOHandler_H

#include "player.h"
#include "game_ids.h"
#include <iostream>
#include <vector>
#include <string>

namespace IOHandler {
  template <typename T>
  T get();

  template <typename T>
  void print(const T& value);

  template <typename T>
  void print(const Player& player);

  template <typename T>
  void print(const std::vector<const Player*>& players);

  template <typename T>
  void print(const std::vector<std::vector<int>>& board);
}

template <typename T>
T IOHandler::get() {
  T value;
  std::cin >> value;
  return value;
}

template <typename T>
void IOHandler::print(const T& value) {
  std::cout << value << std::endl;
}

template <typename T>
void IOHandler::print(const Player& player) {
  print<std::string>(player.get_username() + " " + player.get_name());
  for(auto& game_id : all_game_ids()) {
    print<std::string>(game_id_to_string(game_id) + ": - V: " + std::to_string(player.get_wins_count(game_id))
                       + " D: " + std::to_string(player.get_defeats_count(game_id)));
  }
}

template <typename T>
void IOHandler::print(const std::vector<const Player*>& players) {
  for(auto player : players) {
    print<Player>(*player);
    std::cout << std::endl;
  }
}

template <typename T>
void IOHandler::print(const std::vector<std::vector<int>>& board) {
  const int EMPTY_SPACE = 0;
  const std::string horizontal_line = std::string(30, '-');

  for(int i = 0; i < board.size(); i++) {
    std::string row = "| ";
    for(int j = 0; j < board[i].size(); j++) {
      board[i][j] == EMPTY_SPACE ? row.push_back(' ') : row.push_back(board[i][j] + '0');
      row += " | ";
    }

    std::cout << row << std::endl;
    std::cout << horizontal_line << std::endl;
  }
}


#endif

