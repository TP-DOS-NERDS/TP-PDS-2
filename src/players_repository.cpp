#include "../include/players_repository.h"
#include "../include/forbidden_action_exception.h"

PlayersRepository::PlayersRepository() {
  players = {};
}

bool PlayersRepository::has(std::string username) {
  return players.find(username) != players.end();
}

void PlayersRepository::AddPlayer(Player player) {
  if(has(player.get_username())) {

  }
  players.insert({player.get_username(), player});
}

void PlayersRepository::RemovePlayer(std::string username) {
  players.erase(username);
}
