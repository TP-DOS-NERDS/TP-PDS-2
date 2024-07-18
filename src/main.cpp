#include "../include/player.h"
#include "../include/players_repository.h"
#include "../include/games/reversi.h"
//#include "../include/games/lig4.h"

#include <iostream>

// todo o código aqui é por hora provisório e deve ser usado apenas para testar
// as funcionalidades básicas.
// Após a primeira etapa de desenvolvimento, vamos fazer um menu e posteriormente extras (Talvez Menu 2D).
int main() {

  PlayersRepository repo;
  Player p1("ullas", "ulisses");
  Player p2("tsuy", "rafael");

  repo.AddPlayer(p1);
  repo.AddPlayer(p2);

//  Reversi game(p1,p2);

  Reversi game(p1, p2);
  game.render_board();
  
  return 0;
  game.show_board();
  std::cout << " -- FASE DE TESTES [INTERFACE E MENU A SEREM FEITOS] -- " << std::endl;
  std::cout << " Insira pares x e y para ir populando o tabuleiro do jogo Reversi. " << std::endl;

  int x, y;
  while (std::cin >> x >> y) {
    game.move(x, y);
//    std::cout << "JOGADOR DA VEZ : " << reversi.get_next_move_player_mark() << std::endl;
    game.show_board();
  }
  

  return 0;
}
