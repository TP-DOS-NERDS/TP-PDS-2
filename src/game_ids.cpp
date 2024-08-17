#include "../include/game_ids.h"
#include <iostream>

std::string game_id_to_string(GameId id) {
  if(id == GameId::lig4) return "lig4";
  if(id == GameId::reversi) return "reversi";

  return "";
}

GameId string_to_game_id(std::string str) {
  if(str == "lig4") return GameId::lig4;
  if(str == "reversi") return GameId::reversi;
}

bool game_exists(std::string name) {
  return name == "lig4" || name == "reversi"; 
}


std::vector<GameId> all_game_ids() {
  return { GameId::lig4, GameId::reversi };
}
