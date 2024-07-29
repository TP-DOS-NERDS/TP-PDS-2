#include "../include/player.h"
#include "../include/players_repository.h"
#include "../include/games/reversi.h"
#include "../include/games/minesweeper.h"

#include <iostream>
#include <ostream>

// todo o código aqui é por hora provisório e deve ser usado apenas para testar
// as funcionalidades básicas.
// Após a primeira etapa de desenvolvimento, vamos fazer um menu e posteriormente extras (Talvez Menu 2D).
int main() {
  PlayersRepository repo;
  Player p1("Siul", "Luis Edu");

  Minesweeper game(p1);
  
  std::cout << " -- FASE DE TESTES [INTERFACE E MENU A SEREM FEITOS] -- " << std::endl << std::endl;

  int x, y;
  do {
    std::cout << "Digite uma casa (0-7):" << std::endl << "X: ";
    std::cin >> x;
    std::cout << "Y: ";
    std::cin >> y;
    std::cout << std::endl;
  } while (x < 0 || x > 7 || y < 0 || y > 7);
  game.generate_bombs(x, y);
  game.reveal_tile(x, y);
  
  while(!game.game_ended()) {

    std::cout << game.get_remaining_tiles() << " tiles remaining!" << std::endl;
    game.show_board();
    std::cout << std::endl;

    std::cout << "Digite uma casa (0-7):" << std::endl << "X: ";
    std::cin >> x;
    std::cout << "Y: ";
    std::cin >> y;
    std::cout << std::endl;

    game.reveal_tile(x, y);
  }

  return 0;
}
