#include "../include/player.h"
#include "../include/players_repository.h"

int main() {
  PlayersRepository repo;
  Player p1("ullas", "ulisses");
  Player p2("tsuy", "rafael");

  repo.AddPlayer(p1);
  repo.AddPlayer(p2);

  

  return 0;
}
