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
  }
  TEST_CASE("get all ids") {
    SUBCASE ("all game ids") {
      std::vector<GameId> ids = all_game_ids();
      for (auto id : ids) {
        bool exists = id == GameId::lig4 || id == GameId::reversi;
        CHECK(exists);
      }
    }
  }
}

