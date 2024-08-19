#ifndef GAME_IDS_H
#define GAME_IDS_H

#include <string>
#include <vector>
#include <unordered_map>

enum class GameId {
    lig4 = 0,
    reversi = 1
};

/**
 * @brief Transforma o ID enumerado em string.
 *
 * @param id Enumeracao ligada a um jogo disponivel.
 * @return String com o nome do jogo.
 */
std::string game_id_to_string(GameId id);

/**
 * @brief Transforma uma string com o nome de um jogo em uma ID enumerada.
 *
 * @param str Nome do jogo.
 * @return ID do jogo correspondente.
 */
GameId string_to_game_id(std::string str);

/**
 * @brief Garante que a string corresponde a um jogo existente.
 *
 * @param str Nome do jogo.
 * @return True se existir. False caso contrario.
 */
bool game_exists(std::string name);

/**
 * @brief Lista de todos os jogos disponiveis.
 *
 * @return Vetor de todos os jogos como IDs enumeradas.
 */
std::vector<GameId> all_game_ids();

#endif
