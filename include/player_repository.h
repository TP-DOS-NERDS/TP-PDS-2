#ifndef PLAYERS_REPOSITORY_H
#define PLAYERS_REPOSITORY_H

#include <map>
#include <vector>
#include "./player.h"

class PlayersRepository {
private:
  std::map<std::string, Player> players;

public:
  PlayersRepository();
  void add(Player player);
  void remove(std::string username);
  bool has(std::string username);
  std::vector<const Player*> get_players() const;
};

#endif
