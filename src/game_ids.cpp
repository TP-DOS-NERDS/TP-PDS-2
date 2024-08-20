#include "../include/game_ids.h"

std::string game_id_to_string(GameId id) {
  if(id == GameId::lig4) return "lig4";
  else if(id == GameId::minesweeper) return "minesweeper";
  else if(id == GameId::reversi) return "reversi";
  else if(id == GameId::snake) return "snake";
  return "";
}

GameId string_to_game_id(std::string str) {
  if(str == "lig4") return GameId::lig4;
  else if(str == "reversi") return GameId::reversi;
  else if(str == "minesweeper") return GameId::minesweeper;
  else if(str == "snake") return GameId::snake;
  else return GameId::not_found;
}

bool game_exists(std::string name) {
  return name == "lig4" || name == "reversi" || name == "snake" || name == "minesweeper"; 
}


std::vector<GameId> all_game_ids() {
  return { GameId::lig4, GameId::reversi, GameId::snake, GameId::minesweeper };
}
