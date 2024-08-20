#ifndef IOHandler_H
#define IOHandler_H

#include "player.h"
#include "game_ids.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>

namespace IOHandler {
/**
 * @brief Lê um valor de um tipo T da entrada padrão.
 *
 * @return Retorna um valor do tipo T lido da entrada padrão.
 */
  template <typename T>
  T get();

/**
 * @brief Imprime um valor de um tipo T na saída padrão.
 */
  template <typename T>
  std::string get_line();

  template <typename T>
  void print(const T& value);

/**
 * @brief Imprime os dados de um objeto do tipo Player na saída padrão.
 */
  template <typename T>
  void print(const Player& player);

/**
 * @brief Imprime os dados de um vetor de ponteiro tipo Player na saída padrão.
 */
  template <typename T>
  void print(const std::vector<const Player*>& players);

/**
 * @brief Imprime os dados de uma matriz de inteiros. 
 */
  template <typename T>
  void print(const std::vector<std::vector<int>>& board);

  template <typename T>
  void print(const std::vector<std::string>& board);

  template <typename T>
  void print_players(const std::vector<const Player*>& players);

  template <typename T>
  void print_board(const std::vector<std::vector<int>>& board);

  template <typename T>
  void print_board_plus_zero(const std::vector<std::vector<int>>& board);

  template <typename T>
  void print(const std::vector<std::vector<char>>& board); 
}


template <typename T>
T IOHandler::get() {
  T value;
  if(!(std::cin >> value)) {
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
    return T();
  }
  return value;
}

template <typename T>
std::string IOHandler::get_line() {
  std::string string;
  std::getline(std::cin, string);

  return string;
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

template <typename T>
void IOHandler::print(const std::vector<std::string>& board) {
  const int EMPTY_SPACE = 0;
  const std::string horizontal_line = std::string(34, '-');

  auto get_mark = [&](char c) {
    if (c == '1') return 'X';
    if (c == '2') return 'O';
    if (c == '3') return '?';
    else return '.';
  };

  for(int i = 0; i < board.size(); i++) {
    std::string row = "| ";
    for(int j = 0; j < board[i].size(); j++) {
      board[i][j] == EMPTY_SPACE ? row.push_back(' ') : row.push_back(get_mark(board[i][j]));
      row += " | ";
    }

    std::cout << row << std::endl;
    std::cout << horizontal_line << std::endl;
  }
}
template <typename T>
void IOHandler::print_board(const std::vector<std::vector<int>>& board) {
  const int EMPTY_SPACE = 0;
  const std::string horizontal_line = std::string(board[0].size() * 4, '-');

  for(int i = 0; i < board.size(); i++) {
    std::string row = "| ";
    for(int j = 0; j < board[i].size(); j++) {
      board[i][j] == EMPTY_SPACE ? row.push_back(' ') : row.push_back(board[i][j]);
      row += " | ";
    }

    std::cout << row << std::endl;
    std::cout << horizontal_line << std::endl;
  }
}
template <typename T>
void IOHandler::print_board_plus_zero(const std::vector<std::vector<int>>& board) {
  const int EMPTY_SPACE = 0;
  const std::string horizontal_line = std::string(board[0].size() * 4, '-');

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
template <typename T>
void IOHandler::print_players(const std::vector<const Player*>& players) {
  for(auto player : players) {
    print<Player>(*player);
    std::cout << std::endl;
  }
}

template <typename T>
void IOHandler::print(const std::vector<std::vector<char>>& board) {
  for (int i = 0; i < 22; ++i) {
    std::string row;
    for (int j = 0; j < 22; ++j) {
      std::cout << board[i][j] << ' '; 
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

#endif
