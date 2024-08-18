#include "../include/player_repository.h"
#include "../include/forbidden_action_exception.h"

PlayersRepository::PlayersRepository() {
  players = {};
}

bool PlayersRepository::has(std::string username) {
  return players.find(username) != players.end();
}

void PlayersRepository::add(Player player) {
  players.insert({player.get_username(), player});
}

void PlayersRepository::remove(std::string username) {
  players.erase(username);
}

Player* PlayersRepository::get(std::string username) {
  auto player = players.find(username);
  return &(player->second);
}

std::vector<const Player*> PlayersRepository::get_players() const {
  std::vector<const Player*> array;
  for(const auto& pair : players) {
    array.push_back(&pair.second);
  }

  return array;
}
