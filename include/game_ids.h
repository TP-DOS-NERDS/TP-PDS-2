#ifndef GAME_IDS_H
#define GAME_IDS_H

#include <string>
#include <vector>
#include <unordered_map>

enum class GameId {
    lig4 = 0,
    reversi = 1
};

std::string game_id_to_string(GameId id);


std::vector<GameId> all_game_ids();

#endif
