#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "game_ids.h"



class Player {
private:
  std::string username;
  std::string name;

  std::unordered_map<GameId, int> wins;
  std::unordered_map<GameId, int> defeats;

public:
  Player(std::string username, std::string name);
  void increase_wins(GameId game_id);
  void increase_defeats(GameId game_id);
  std::string get_username() const;
  std::string get_name() const;
  int get_wins_count(GameId game_id) const;
  int get_defeats_count(GameId game_id) const;
};


#endif
