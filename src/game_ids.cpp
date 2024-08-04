#include "../include/game_ids.h"
#include <iostream>

std::string game_id_to_string(GameId id) {
  if(id == GameId::lig4) return "LIG4";
  if(id == GameId::reversi) return "REVERSI";

  return "";
}


std::vector<GameId> all_game_ids() {
  return { GameId::lig4, GameId::reversi };
}
