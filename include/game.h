#ifndef GAME2_H
#define GAME2_H

#include <vector>
#include <utility>

class Game {
public:
/**
 * Brief Inicia uma partida de um jogo.
 */
  virtual void play() = 0;
/**
 * Brief Obtêm qual jogador venceu o jogo.
 *
 * @return Retorna 1 se o primeiro jogador venceu, 2 se o segundo jogador venceu, 0 se ocorreu um empate (em jogos multiplayer)/o primeiro jogador perdeu (em jogos single player). 
 */
  virtual int get_winner() = 0;

private:
/**
 * Brief Verifica se uma posição no tabuleiro é valida.
 *
 * @param position A posição que  será validada.
 * @return Retorna um flag booleano indicando se a posição é válida.
 */
  virtual bool is_position_valid(std::pair<int,int> position) = 0;

/**
 * Brief Verifica se o jogo encerrou.
 *
 * @param position A posição que  será validada.
 * @return Retorna um flag booleano indicando se a posição é válida.
 */
  virtual bool game_ended() = 0;
  virtual void play_round() = 0;

};

#endif
