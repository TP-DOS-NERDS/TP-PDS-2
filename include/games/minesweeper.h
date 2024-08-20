#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "../game.h"
#include "../IOHandler.h"
#include <vector>

/**
 * @brief Classe que representa o jogo de Minesweeper.
 */
class Minesweeper : public Game {

public:
/**
 * Brief Construtor que instancia um Campo minado vazio.
 */
  Minesweeper();

/**
 * Brief Destrutor padrão.
 */
  ~Minesweeper();

/**
 * Brief Loop de jogo principal.
 */
  void play() override;

/**
 * Brief Retorna se houve vitoria.
 *
 * @return 1 se houve vitoria. 2 caso contrario.
 */
  int get_winner() override;

private:
  std::vector<std::vector<int>> bombs;
  std::vector<std::vector<int>> board; // 126 = ~ | 70 = F
  bool game_over = false;
  int board_size = 20;
  int winner = 2; // Loss
  int remaining_tiles;

/**
 * Brief Recebe o input do usuario, garantindo que esta dentro dos padroes.
 *
 * @return Um char com a opcao escolhida e um par de inteiros com a posicao da casa.
 */
  std::pair<char,std::pair<int, int>> take_input();

/**
 * Brief Determina se uma posicao eh valida.
 *
 * @param position Um par de inteiros com a posicao de uma casa.
 *
 * @return True se for dentro do tabuleiro. False caso contrario.
 */
  bool is_position_valid(std::pair<int, int> position) override;

/**
 * Brief Determina se todas as casas foram reveladas.
 *
 * @return True caso houver vitoria.
 */
  bool game_ended() override;

/**
 * Brief Organiza em etapas os eventos de uma rodada.
 */
  void play_round() override;

/**
 * Brief Aumenta o numero das casas vizinhas (util para casas com bombas).
 *
 * @param x Linha da casa.
 * @param y Coluna da casa.
 */
  void increase_close_tiles(int x, int y);

/**
 * Brief Gera um campo com bombas em casas aleatorias (Casa segura: garante que ela e suas vizinhas nao tenham bombas).
 *
 * @param x Linha da casa segura.
 * @param y Coluna da casa segura.
 */
  void generate_bombs(int x, int y);

/**
 * Brief Inicia o campo baseado na primeira casa escolhida pelo jogador.
 *
 * @param x Linha da casa.
 * @param y Coluna da casa.
 */
  bool first_move(int x, int y);

/**
 * Brief Retorna o numero de casas nao reveladas ainda.
 *
 * @return Numero de casas nao revelaadas (exceto bombas).
 */
  int get_remaining_tiles();

/**
 * Brief Revela a casa escolhida.
 *
 * @param x Linha da casa.
 * @param y Coluna da casa.
 */
  void reveal_tile(int x, int y);

/**
 * Brief Coloca ou retira uma bandeira na casa selecionada.
 *
 * @param x Linha da casa.
 * @param y Coluna da casa.
 */
  void place_flag(int x, int y);

/**
 * Brief Conta quantas bandeiras tem em casas vizinhas.
 *
 * @param x Linha da casa.
 * @param y Coluna da casa.
 *
 * @return Quantidade de bandeiras
 */
  int count_close_flags(int x, int y);

/**
 * Brief Acaba o jogo com uma derrota.
 */
  void lose();

/**
 * Brief Acaba o jogo com uma vitoria.
 */
  void win();
};



#endif
