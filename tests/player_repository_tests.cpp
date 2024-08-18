#include "doctest.h"
#include <vector>
#include <algorithm>
#include "../include/player_repository.h"

TEST_SUITE("player_repository") {
  PlayersRepository player_repository = PlayersRepository();
  Player ace = Player("ace", "Portgaz D. Ace");
  Player luffy = Player("luffy", "Monkey D. Luffy");
  Player zoro = Player("zoro", "Ronronoa Zoro");

  TEST_CASE("contains") {
    SUBCASE("item is abscent") {
      player_repository.add(ace);

      CHECK_FALSE(player_repository.has(luffy.get_name()));
    }

    SUBCASE("empty repository contains nothing") {
      CHECK_FALSE(player_repository.has(ace.get_name()));
    }
  }
  
  // TODO: esse nome ta legal ??
  TEST_CASE("add") {
    SUBCASE("add one item") {
      player_repository.add(ace); 

      CHECK(player_repository.has(ace.get_name()));
    }

    SUBCASE("add multiple items") {
      std::vector<Player> players = { ace, luffy, zoro };

      for(auto& player : players) {
        player_repository.add(player);
      }

      for(auto& player : players) {
        CHECK(player_repository.has(player.get_name()));
      }
    }
  }

  TEST_CASE("remove") {
    SUBCASE("remove one item") {
      player_repository.add(ace); 
      player_repository.remove(ace.get_name());

      CHECK_FALSE(player_repository.has(ace.get_name()));
    }

    SUBCASE("remove multiple items") {
      std::vector<Player> players = { ace, luffy, zoro };

      for(auto& player : players) {
        player_repository.add(player);
      }

      for(auto& player : players) {
        player_repository.remove(player.get_name());
      } 

      for(auto& player : players) {
        CHECK_FALSE(player_repository.has(player.get_name()));
      }
    }
  }

  TEST_CASE("get players") {
    std::vector<Player> players = { ace, luffy, zoro };

    for(auto& player : players) {
      player_repository.add(player);
    }

    std::vector<const Player*> player_references = player_repository.get_players();

    for(auto& player : players) {
      CHECK(&player == &ace || &player == &luffy || &player == &zoro);
    }
  }
}

