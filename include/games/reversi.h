#ifndef REVERSI_H
#define REVERSI_H

#include <string>
#include <vector>
#include "../game.h"
#include "../player.h"

/**
 * @brief Classe que representa o jogo de Reversi.
 */
class Reversi: public Game {
public:
    /**
     * @brief Construtor que inicializa um jogo de Reversi com dois jogadores.
     * 
     * @param p1 O primeiro jogador.
     * @param p2 O segundo jogador.
     */
    Reversi(Player, Player);

    /**
     * @brief Construtor de cópia para o jogo de Reversi.
     * 
     * @param other Outro objeto Reversi para ser copiado.
     */
    Reversi(Reversi&);

    /**
     * @brief Construtor padrão para o jogo de Reversi.
     */
    Reversi();

    /**
     * @brief Destrutor da classe Reversi.
     */
    ~Reversi();

    /**
     * @brief Inicia o jogo de Reversi.
     */
    void play() override;

    /**
     * @brief Obtém o vencedor do jogo.
     * 
     * @return int O ID do jogador vencedor.
     */
    int get_winner() override;

private:
    static constexpr int FIRST_PLAYER_ID = 1;
    static constexpr int SECOND_PLAYER_ID = 2;
    static constexpr int NO_PLAYER = 0;

    std::vector<Player> players; 
    Player next_move_player;
    int board_size;
    std::vector<std::string> board;

    /**
     * @brief Verifica se uma posição no tabuleiro é válida.
     * 
     * @param position A posição a ser verificada.
     * @return true Se a posição é válida.
     * @return false Se a posição não é válida.
     */
    bool is_position_valid(std::pair<int,int> position) override;

    /**
     * @brief Verifica se o jogo terminou.
     * 
     * @return true Se o jogo terminou.
     * @return false Se o jogo ainda está em andamento.
     */
    bool game_ended() override;

    /**
     * @brief Executa uma rodada do jogo.
     */
    void play_round() override;

    /**
     * @brief Aplica um movimento visualmente e atualiza o estado do jogo.
     * 
     * @param x A coordenada x do movimento.
     * @param y A coordenada y do movimento.
     */
    void apply_visual_move(int, int);

    /**
     * @brief Atualiza o estado do jogo após uma jogada.
     */
    void after_move();

    /**
     * @brief Marca os movimentos válidos no tabuleiro.
     */
    void mark_valid_moves();

    /**
     * @brief Limpa as marcações de movimentos válidos no tabuleiro.
     */
    void clear_valid_moves();

    /**
     * @brief Faz um movimento no tabuleiro e atualiza o estado do jogo.
     * 
     * @param x A coordenada x do movimento.
     * @param y A coordenada y do movimento.
     */
    void move(int, int);

    /**
     * @brief Faz um movimento no tabuleiro sem verificar se é válido.
     * 
     * @param x A coordenada x do movimento.
     * @param y A coordenada y do movimento.
     */
    void move_non_check(int, int);

    /**
     * @brief Obtém a marca do jogador que tem a próxima jogada.
     * 
     * @return char A marca do próximo jogador ('1' ou '2').
     */
    char get_next_move_player_mark();

    /**
     * @brief Obtém a marca do jogador que tem a jogada após a próxima.
     * 
     * @return char A marca do jogador subsequente ('1' ou '2').
     */
    char get_next_next_move_player_mark();

    /**
     * @brief Obtém as posições das peças que serão alteradas por um movimento.
     * 
     * @param x A coordenada x do movimento.
     * @param y A coordenada y do movimento.
     * @return std::vector<std::pair<int, int>> Um vetor com as posições a serem alteradas.
     */
    std::vector<std::pair<int,int>> get_positions_to_change(int, int);

    /**
     * @brief Verifica se um movimento é válido.
     * 
     * @param x A coordenada x do movimento.
     * @param y A coordenada y do movimento.
     * @return true Se o movimento for válido.
     * @return false Se o movimento não for válido.
     */
    bool valid_move(int, int);

    /**
     * @brief Exibe o tabuleiro no console.
     */
    void show_board();

    /**
     * @brief Verifica se o tabuleiro está cheio.
     * 
     * @return true Se o tabuleiro estiver cheio.
     * @return false Se ainda houver espaços vazios no tabuleiro.
     */
    bool is_board_full();

    /**
     * @brief Define um caractere no tabuleiro nas coordenadas especificadas.
     * 
     * @param x A coordenada x do tabuleiro.
     * @param y A coordenada y do tabuleiro.
     * @param c O caractere a ser definido.
     */
    void set_in_board(int, int, char);

    /**
     * @brief Obtém o caractere no tabuleiro nas coordenadas especificadas.
     * 
     * @param x A coordenada x do tabuleiro.
     * @param y A coordenada y do tabuleiro.
     * @return char O caractere na posição especificada.
     */
    char get_in_board(int, int);

    /**
     * @brief Obtém a quantidade de um caractere específico no tabuleiro.
     * 
     * @param c O caractere a ser contado.
     * @return int O número de vezes que o caractere aparece no tabuleiro.
     */
    int get_amount_of_char_in_board(char);

    /**
     * @brief Obtém as posições de um caractere específico no tabuleiro.
     * 
     * @param c O caractere a ser procurado.
     * @return std::vector<std::pair<int, int>> Um vetor de posições onde o caractere foi encontrado.
     */
    std::vector<std::pair<int, int>> get_positions_of_char_in_board(char);
};

#endif
