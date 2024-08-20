#ifndef SNAKE_H
#define SNAKE_H

#include <termios.h>
#include <string>
#include <unistd.h>
#include <csignal>
#include "../player.h"
#include "../game.h"
#include "../../include/IOHandler.h"
#include "../../include/terminal_handler.h"


class Snake : public Game {
private:
  std::vector<std::vector<char>> board;
  int snake[2][100];  // Snake coordinates
  int length; // Snake size
  int direction; // Snake direction
  int food_x, food_y;
  bool running;

struct termios original_termios;


/**
 * Brief Inicializacao do tabuleiro.
 */
  void init_board();

/**
 * Brief Posiciona a fruta aleatoriamente.
 */
  void place_food();

/**
 * brief imprime o tabuleiro no terminal.
 */
  void print_board() const;

/**
 * Brief Movimenta a cobra em uma direcao.
 *
 * @param dx Direcao horizontal.
 * @param dy Direcao vertical.
 */
  bool move_snake(int dx, int dy);

/**
 * Brief Verifica se o jogo acabou.
 *
 * @param x Linha atual da cobra.
 * @param y Coluna atual do cobra.
 *
 * @return True se a cobra acertar uma parede ou si mesma. False caso contrario.
 */
  bool is_game_over(int x, int y) const;

/**
 * Brief Verifica se o tabuleiro encheu com a cobra.
 *
 * @return True se nao ha mais casas livres. False caso contrario.
 */
  bool is_board_full() const;

/**
 * Brief Determina se uma posicao eh valida.
 *
 * @param position Um par de inteiros com a posicao de uma casa.
 *
 * @return True se for dentro do tabuleiro. False caso contrario.
 */
  bool is_position_valid(std::pair<int,int> position);

/**
 * Brief Determina se a cobra morreu ou se ela ocupou todas as casas.
 *
 * @return True caso a cobra morreu, ou o tabuleiro encheu.
 */
  bool game_ended();

/**
 * Brief Organiza em etapas os eventos de uma rodada.
 */
  void play_round();
  int score;


public:

/**
 * Brief Construtor com jogador a quem sera atrelado o resultado.
 *
 * @param player Jogador da partida.
 */
  Snake(Player player);

/**
 * Brief Construtor padrao. Inicializa o Tabuleiro.
 */
  Snake();

/**
 * Brief Destrutor padrao.
 */
  ~Snake();

/**
 * Brief Loop principal do jogo.
 */
  void play();

/**
 * Brief Retorna a situacao de vitoria ou derrota
 *
 * @return 1 se vitoria. 0 se derrota
 */
  int get_winner();

/**
 * Brief Movimenta a cobra em quatro direcoes.
 */
  void move();

/**
 * Brief Altera a direcao em que a cobra se movimenta.
 *
 * @param new_direction Direcao da cobra.
 */
  void change_direction(int new_direction);

/**
 * Brief Verifica o se o jogo acabou.
 *
 * @return True se a cobra morre. False caso contrario.
 */
  bool is_game_over() const;

/**
 * Brief Para o sistema momentaneamente.
 *
 * @param miliseconds Tempo de pausa.
 */
  void wait(int milliseconds);

/**
 * Brief Retorna pontuacao baseado nas frutas colhidas.
 *
 * @return Inteiro representante da pontuacao.
 */
  int get_score() const;
};

#endif
