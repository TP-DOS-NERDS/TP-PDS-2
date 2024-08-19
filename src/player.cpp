#include "../include/player.h"

Player::Player(std::string username, std::string name) {
  this->username = username;
  this->name = name;
  
  for(auto& game_id : all_game_ids()) {
    wins.insert({ game_id, 0 });
    defeats.insert({ game_id, 0 });
  }
}



void Player::increase_wins(GameId game_id) {
  wins[game_id]++;
}

void Player::increase_defeats(GameId game_id) {
  defeats[game_id]++;
}

std::string Player::get_username() const {
  return username;
}

std::string Player::get_name() const {
  return name;
}

int Player::get_wins_count(GameId game_id) const {
  return wins.find(game_id)->second;
}

int Player::get_defeats_count(GameId game_id) const {
  return defeats.find(game_id)->second;
}


