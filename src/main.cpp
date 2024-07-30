#include "../include/player.h"
#include "../include/players_repository.h"
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

  // Initial move
  int x, y;
  do {
    std::cout << "Digite uma casa (0-7):" << std::endl << "X: ";
    std::cin >> x;
    std::cout << "Y: ";
    std::cin >> y;
    std::cout << std::endl;
  } while (!game.first_move(x, y));
  
  // Main Loop
  while(!game.game_ended()) {

    std::cout << game.get_remaining_tiles() << " tiles remaining!" << std::endl;
    game.show_board();
    std::cout << std::endl;

    char click;
    std::cout << "R - Reveal a tile. F - Put a flag" << std::endl << "- ";
    std::cin >> click;

    std::cout << "Digite uma casa (0-7):" << std::endl << "X: ";
    std::cin >> x;
    std::cout << "Y: ";
    std::cin >> y;
    std::cout << std::endl;

    if (click == 'R')
      game.left_click(x, y);
    
    else if (click == 'F')
      game.right_click(x, y);
  }

  return 0;
}
