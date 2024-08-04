#include "../include/IOHandler.h"

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
