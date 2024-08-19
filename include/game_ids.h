#ifndef GAME_IDS_H
#define GAME_IDS_H

#include <string>
#include <vector>
#include <unordered_map>

enum class GameId {
    not_found = -1,
    lig4 = 0,
    reversi = 1,
    snake = 2
};

std::string game_id_to_string(GameId id);

GameId string_to_game_id(std::string str);

bool game_exists(std::string name);

std::vector<GameId> all_game_ids();

#endif
