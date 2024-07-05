#include "../include/player.h"

Player::Player(std::string username, std::string name) {
  this->username = username;
  this->name = name;
  this->wins_amount = 0;
  this->defeats_amount = 0;
}

void Player::increase_wins() {
  wins_amount++;
}

void Player::increase_defeats() {
  defeats_amount++;
}

std::string Player::get_username() const {
  return username;
}
