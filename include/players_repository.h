#ifndef PLAYERS_REPOSITORY_H
#define PLAYERS_REPOSITORY_H

#include <unordered_map>
#include "./player.h"

class PlayersRepository {
private:
  std::unordered_map<std::string, Player> players;
  bool has(std::string username);

public:
  PlayersRepository();
  void AddPlayer(Player player);
  void RemovePlayer(std::string username);
};

#endif
