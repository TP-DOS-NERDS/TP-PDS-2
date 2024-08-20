#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "game_ids.h"


/**
 * @brief Classe que descreve o player 
 */
class Player {
private:
  std::string username;
  std::string name;

  std::unordered_map<GameId, int> wins;
  std::unordered_map<GameId, int> defeats;

public:
/**
 * Brief Construtor que instancia um objeto do tipo player com o seu respectivo apelido e nome. É importante dizer que o jogador incialmente terá zero vitórias e zero derrotas.
 *
 * @param username O apelido atribuido ao jogador.
 * @param name O nome atribuido ao jogador.
 * @return Um objeto do tipo Player.
 */
  Player(std::string username, std::string name);

/**
 * Brief Incrementa o número de vitórias do jogador em um jogo.
 *
 * @param game_id Identificador do jogo no qual o número de vitórias será incrementado.
 */
  void increase_wins(GameId game_id);

/**
 * Brief Incrementa o número de derrotas do jogador em um jogo.
 *
 * @param game_id Identificador do jogo no qual o número de derrotas será incrementado.
 */
  void increase_defeats(GameId game_id);

/**
 * Brief Função que retorna o apelido do jogador.
 *
 * @return Uma string que representa o apelido do jogador.
 */
  std::string get_username() const;

/**
 * Brief Função que retorna o nome do jogador.
 *
 * @return Uma string que representa o nome do jogador.
 */
  std::string get_name() const;

/**
 * Brief Função que retorna o número de vitórias do jogador em um jogo.
 *
 * @param game_id Identificador do jogo no qual será obtido o número de vitórias.
 * @return O número de vitórias do jogador no jogo.
 */
  int get_wins_count(GameId game_id) const;

/**
 * Brief Função que retorna o número de derrotas do jogador em um jogo.
 *
 * @param game_id Identificador do jogo no qual será obtido o número de derrotas.
 * @return O número de derrotas do jogador no jogo.
 */
  int get_defeats_count(GameId game_id) const;
};


#endif
