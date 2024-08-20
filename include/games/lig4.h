#ifndef LIG4_H
#define LIG4_H

#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <exception>
#include "../game.h"


/**
 * @brief Classe que representa o jogo LIG4.
 */
class Lig4 : public Game {
public:
  Lig4();
  void play() override;
  int get_winner() override;

private:
  enum class InputError { invalid_move, invalid_input };
  class invalid_move_input_exception : public std::exception {
  public:
    InputError error; 
    invalid_move_input_exception(InputError error);
  };
    
  int winner;
  std::vector<std::vector<int>> board;
  int current_player;
  int next_player;

  static constexpr int NUMBER_OF_ROWS = 6;
  static constexpr int NUMBER_OF_COLUMNS = 7;

  static constexpr int FIRST_PLAYER_ID = 1;
  static constexpr int SECOND_PLAYER_ID = 2;
  static constexpr int NO_PLAYER = 0;


  bool is_position_valid(std::pair<int,int> position) override;
  bool game_ended() override;
  void play_round() override;

/**
 * @brief Lê da entrada padrão um movimento válido.
 *
 * @return A coordenada de um movimento válido escolhido pelo jogador. 
 */
  int get_valid_move_input();

/**
 * @brief Valida uma string referente a um movimento.
 *
 * @param move_input String referente ao movimento digitado por um jogador.
 */
  void validate_move_input(std::string move_input);

/**
 * @brief Executa um movimento.
 *
 * @param j A coluna na qual será posicionada uma "peça" no tabuleiro do Lig4.
 */
  void execute_move(int j);

/**
 * @brief Computa os movimentos possíveis em um determinado estado do jogo.
 *
 * @return Um conjunto com as colunas nas quais é possível jogar.
 */
  std::set<int> get_valid_moves();

/**
 * @brief Verifica se todas as posições do tabuleiro estão ocupadas.
 *
 * @return Uma flag booleana indicando se todas as posições estão ocupadas.
 */
  bool all_positions_are_ocuppied();

/**
 * @brief Verifica se existe uma posição no tabuleiro que está conectada. Ou seja, se existe uma sequência de 4 peças do mesmo jogador em um dos sentidos válidos (horizontal, vertial, diagonal).
 *
 * @return Uma flag booleana indicando se existe uma posição no tabuleiro que está conectada.
 */
  bool is_a_position_linked();

/**
 * @brief Verifica se uma determinada posição do tabuleiro está conectada. Ou seja, se é existe uma sequência de 4 peças do mesmo "valor" em um dos sentidos válidos (horizontal, vertical, diagonal) que passa pela posição.
 *
 * @param position A posição da peça na qual ocorrerá a verificação.
 * @return Uma flag booleana indicando se a peça está conectada.
 */
  bool position_linked(std::pair<int,int> position);

/**
 * @brief Verifica se uma posição do tabuleiro está conectada horizontalmente. Ou seja, se existe uma sequência de 4 peças do mesmo "valor" no sentido horizontal.

 *
 * @param position A posição da peça na qual ocorrerá a verificação.
 * @return Uma flag booleana indicando se a peça está conectada horizontalmente.
 */
  bool position_linked_horizontally(std::pair<int,int> position);

/**
 * @brief Verifica se uma posição do tabuleiro está conectada horizontalmente. Ou seja, se existe uma sequência de 4 peças do mesmo "valor" no sentido vertical.

 *
 * @param position A posição da peça na qual ocorrerá a verificação.
 * @return Uma flag booleana indicando se a peça está conectada verticalmente.
 */
  bool position_linked_vertically(std::pair<int,int> position);

/**
 * @brief Verifica se uma posição do tabuleiro está conectada horizontalmente. Ou seja, se existe uma sequência de 4 peças do mesmo "valor" no sentido diagonal.

 *
 * @param position A posição da peça na qual ocorrerá a verificação.
 * @return Uma flag booleana indicando se a peça está conectada diagonalmente.
 */
  bool position_linked_diagonally(std::pair<int,int> position);

/**
 * @brief Verifica se uma posição do tabuleiro está conectada horizontalmente. Ou seja, se existe uma sequência de 4 peças do mesmo "valor" no sentido diagonal.

 *
 * @param position A posição da peça na qual ocorrerá a verificação.
 * @return Uma flag booleana indicando se a peça está conectada diagonalmente.
 */
};


#endif
