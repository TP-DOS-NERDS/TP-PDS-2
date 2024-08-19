#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/player.h"

TEST_SUITE("player") {
  Player levi = Player("levi", "Levi Ackerman");

  TEST_CASE("wins count") {
    SUBCASE("increase wins count") {
      levi.increase_wins(GameId::lig4);

      CHECK(levi.get_wins_count(GameId::lig4) == 1);
    } 
  }

  TEST_CASE("defeats count") {
    SUBCASE("increase defeats count") {
      levi.increase_defeats(GameId::lig4);

      CHECK(levi.get_defeats_count(GameId::lig4) == 1);
    } 
  }

  TEST_CASE("Player Username") {
    SUBCASE("Return Username") {
      CHECK(levi.get_username() == "levi");
    } 
  }

  TEST_CASE("Player Name") {
    SUBCASE("Return Name") {
      CHECK(levi.get_name() == "Levi Ackerman");
    } 
  }
}
