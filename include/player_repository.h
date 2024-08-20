#ifndef PLAYERS_REPOSITORY_H
#define PLAYERS_REPOSITORY_H

#include <map>
#include <vector>
#include "./player.h"

/**
 * @brief Classe que gerencia os players, de maneira similar ao repository pattern
 */
class PlayersRepository {
private:
  std::map<std::string, Player> players;

public:
/**
 * Brief Construtor que instancia um repositório de jogadores com nenhum jogador.
 *
 * @return Um objeto do tipo PlayerRepository.
 */
  PlayersRepository();

/**
 * Brief Adiciona um objeto do tipo jogador no repositório.
 *
 * @param player O objeto do tipo jogador que será adicionado no respositório.
 */
  void add(Player player);

/**
 * Brief Remove um objeto do tipo jogador no repositório.
 *
 * @param username O apelido do jogador que será removido do repositório.
 */
  void remove(std::string username);

/**
 * Brief Verifica se existe um jogador no repositório com um determinado apelido.
 *
 * @param username O apelido do jogador que está sendo buscado.
 * @return Uma flag booleana indicando se o jogador está ou não no repositório.
 */
  bool has(std::string username);

/**
 * Brief Retorna a referência para um objeto do tipo Player que possuí um determinado apelido.
 *
 * @param username O apelido do jogador que está sendo buscado.
 * @return Um ponteiro para um objeto do tipo Player que possui o apelido passado como parâmetro.
 */
  Player* get(std::string username);

/**
 * Brief Retorna um vetor com os ponteiros para os objetos do tipo Player que estão no repositório.
 *
 * @return Um vetor de ponteiros para os objetos que estão no repositório.
 */
  std::vector<const Player*> get_players() const;
};

#endif
