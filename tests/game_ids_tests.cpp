#include "doctest.h"
#include "../include/game_ids.h"

TEST_SUITE("game_ids") {
  TEST_CASE("id to string") {
    SUBCASE("lig4") {
      CHECK(game_id_to_string(GameId::lig4) == "lig4");
    }
    SUBCASE("reversi") {
      CHECK(game_id_to_string(GameId::reversi) == "reversi");
    }
    SUBCASE("snake") {
      CHECK(game_id_to_string(GameId::snake) == "snake");
    }
    SUBCASE("minesweeper") {
      CHECK(game_id_to_string(GameId::minesweeper) == "minesweeper");
    }
  }
  TEST_CASE("get all ids") {
    SUBCASE ("all game ids") {
      std::vector<GameId> ids = all_game_ids();
      for (auto id : ids) {
        bool exists = id == GameId::lig4 || id == GameId::reversi || id == GameId::snake || id == GameId::minesweeper;
        CHECK(exists);
      }
    }
  }
}


