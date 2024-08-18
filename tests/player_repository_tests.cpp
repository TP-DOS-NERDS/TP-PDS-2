#include "doctest.h"
#include <vector>
#include <algorithm>
#include "../include/player_repository.h"

TEST_SUITE("player_repository") {
  PlayersRepository player_repository = PlayersRepository();
  Player ace = Player("ace", "Portgaz D. Ace");
  Player luffy = Player("luffy", "Monkey D. Luffy");
  Player zoro = Player("zoro", "Ronronoa Zoro");

  TEST_CASE("Contains") {
    SUBCASE("item is abscent") {
      player_repository.add(ace);

      CHECK_FALSE(player_repository.has(luffy.get_username()));
      player_repository.remove(ace.get_username());
    }

    SUBCASE("empty repository contains nothing") {
      CHECK_FALSE(player_repository.has(ace.get_username()));
    }
  }
  
  TEST_CASE("Adding players") {
    SUBCASE("add one item") {
      player_repository.add(ace); 

      CHECK(player_repository.has(ace.get_username()));
    }

    SUBCASE("add multiple items") {
      std::vector<Player> players = { ace, luffy, zoro };

      for(auto& player : players) {
        player_repository.add(player);
      }

      for(auto& player : players) {
        CHECK(player_repository.has(player.get_username()));
      }
    }
  }

  TEST_CASE("remove") {
    SUBCASE("remove one item") {
      player_repository.add(ace); 
      player_repository.remove(ace.get_username());

      CHECK_FALSE(player_repository.has(ace.get_username()));
    }

    SUBCASE("remove multiple items") {
      std::vector<Player> players = { ace, luffy, zoro };

      for(auto& player : players) {
        player_repository.add(player);
      }

      for(auto& player : players) {
        player_repository.remove(player.get_username());
      } 

      for(auto& player : players) {
        CHECK_FALSE(player_repository.has(player.get_username()));
      }
    }
  }

  TEST_CASE("get players") {
    std::vector<Player> players = { ace, luffy, zoro };

    for(auto& player : players) {
      player_repository.add(player);
    }

    std::vector<const Player*> player_references = player_repository.get_players();

    for(auto& player : player_references) {
      bool exists = player->get_name() == ace.get_name() || player->get_name() == luffy.get_name() || player->get_name() == zoro.get_name();
      CHECK(exists);
    }
  }
}

