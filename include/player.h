#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
  std::string username;
  std::string name;
  int wins_amount;
  int defeats_amount;

public:
  Player(std::string username, std::string name);
  void increase_wins();
  void increase_defeats();
  std::string get_username() const;
};

struct PlayerHashFunction {
  size_t operator()(const Player& player) const {
    return std::hash<std::string>{}(player.get_username());
  }
};

#endif
